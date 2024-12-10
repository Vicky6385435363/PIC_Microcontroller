#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h> // Include the XC8 compiler header file for PIC microcontroller
#define _XTAL_FREQ 6000000 // Define the oscillator frequency for delay functions
#define CALIBRATION_VALUE 100 // Calibration value for converting ADC result to voltage
#define NUMBER_OF_BIT 1023 // Maximum ADC value for a 10-bit ADC as NUMBER_OF_BITS

void lcd_command(unsigned char); // Function to send command to the LCD
void lcd_init(void); // Function to initialize the LCD
void lcd_data(unsigned char); // Function to send data to the LCD
void lcd_output(unsigned int); // Function to output unsigned integer to the LCD 

unsigned char msg_1[9] = {"ADC RAW: "}; // Message for raw ADC value
unsigned char msg_2[9] = {"ADC CAL: "}; // Message for calibrated ADC value
unsigned int m, adc_low, adc_high; // Variables for ADC readings
unsigned long result, volt; // Variables for ADC result and voltage calculation
unsigned int d3, d4, d1, d2; // Variables for individual digits of the output

void main(void) {
    unsigned char i; // Loop variable
    // Load PR2 register with 93 for desired frequency 0101 1101
    lcd_init(); // Initialize the LCD

    lcd_command(0x80); // Set cursor to the beginning of the first line
    for (i = 0; i < 9; i++) {
        lcd_data(msg_1[i]); // Send each character of msg_1 to the LCD
    }

    lcd_command(0xC0); // Set cursor to the beginning of the second line
    for (i = 0; i < 9; i++) {
        lcd_data(msg_2[i]); // Send each character of msg_2 to the LCD
    }

    lcd_command(0xCD); // Move cursor to a specific position
    lcd_data(0x56); // Display character 'V' with ASCII of 0x56

    while (1) { // Infinite loop
        ADCON0 = 0x81; // Configure ADC: select channel and turn on ADC
        ADCON0 |= 0x04; // Start ADC conversion
        while (ADCON0 & 0x04); // Wait until conversion is complete

        adc_high = ADRESH; // Read high byte of ADC result
        adc_low = ADRESL; // Read low byte of ADC result
        result = ((unsigned long) adc_high << 8) | ((unsigned long) adc_low); // Combine high and low bytes to form the full ADC result

        volt = (unsigned long) ((result * CALIBRATION_VALUE) / NUMBER_OF_BIT); // Convert ADC result to voltage

        // Set duty cycle to 10%
        // Load low byte of duty cycle into CCP1CON 0010 1100   
        lcd_command(0x89); // Set cursor position for raw ADC result
        lcd_output(result); // Output raw ADC result to the LCD

        lcd_command(0xC9); // Set cursor position for calibrated voltage
        lcd_output(volt); // Output calibrated voltage to the LCD
        CCPR1L = volt >> 2;
        // Load high byte of duty cycle into CCPR1L 0000 1001
        CCP1CON = (CCP1CON & 0xCF) | ((volt & 0x03) << 4);
        // Delay for 100 milliseconds before the next reading
    }
}

void lcd_init(void) {
    // Configure I/O pins
    TRISA = 0x01; // Set RA2 as input (for ADC), others as output
    TRISC = 0x00; // Set PORTC as output (for LCD control)
    TRISD = 0x00; // Set PORTD as output (for LCD data)                // Set RC2 as output in PORTC and other pins as output for CCP1 1111 1011
    CCP1CON = 0x0F; // Configure CCP1 module for PWM mode
    T2CON = 0x06; // Configure Timer2: Prescaler is 1:16, Timer2 is on 0000 0110
    PR2 = 0x5D;

    ADCON0 = 0x81; // Turn on ADC and select channel
    ADCON1 = 0x8E; // Configure ADC reference voltage and digital I/O

    lcd_command(0x33); // Set LCD to 8-bit mode, 2 lines, 5x8 dots
    __delay_ms(100); // Delay for LCD to process command
    lcd_command(0x32); // Set LCD to 8-bit mode, 2 lines, 5x8 dots
    __delay_ms(100); // Delay for LCD to process command
    lcd_command(0x35); // Set LCD to 8-bit mode, 2 lines, 5x8 dots
    __delay_ms(100); // Delay for LCD to process command
    lcd_command(0x38); // Set LCD to 8-bit mode, 2 lines, 5x8 dots
    __delay_ms(100); // Delay for LCD to process command
    lcd_command(0x06); // Set cursor move direction (increment)
    __delay_ms(100); // Delay for LCD to process command
    lcd_command(0x0C); // Display ON, cursor OFF
    __delay_ms(100); // Delay for LCD to process command
    lcd_command(0x01); // Clear display
    __delay_ms(100); // Delay for LCD to process command
}

void lcd_command(unsigned char i) {
    PORTC &= ~(0x08); // Set RS to 0 for command mode at pin rc2
    PORTD = i; // Send command to the LCD
    PORTC |= 0x01; // Enable the LCD at pin rc0
    PORTC &= ~0x01; // Disable the LCD at pin rc0
    __delay_ms(100); // Delay for LCD to process command
}

void lcd_data(unsigned char i) {
    PORTC |= (0x08); // Set RS to 1 for data mode at pin rc2
    PORTD = i; // Send data to the LCD
    PORTC |= 0x01; // Enable the LCD at pin rc0
    PORTC &= ~0x01; // Disable the LCD at pin rc0
    __delay_ms(100); // Delay for LCD to process data
}

void lcd_output(unsigned int i) {
    unsigned int m; // Variable to hold the number
    m = i; // Assign input value i to m
    d4 = (unsigned char) (m / 1000); // Calculate the thousands digit
    d3 = (unsigned char) ((m - (d4 * 1000)) / 100); // Calculate the hundreds digit
    d2 = (unsigned char) ((m - (d4 * 1000)-(d3 * 100)) / 10); // Calculate the tens digit
    d1 = (unsigned char) (m - (d4 * 1000)-(d3 * 100)-(d2 * 10)); // Calculate the ones digit

    if (d4 > 0) {
        lcd_data(0x30 + d4); // Display thousands digit
    } else {
        lcd_data(0x20); // Display space for thousands digit if the condition fails
    }

    if (d3 > 0 || d4 > 0) { // Show hundreds if there are thousands or hundreds
        lcd_data(0x30 + d3); // Display hundreds digit
    } else {
        lcd_data(0x20); // Display space for hundreds digit if the condition fails
    }

    if (d2 > 0 || d3 > 0 || d4 > 0) { // Show tens if there are hundreds, thousands, or tens
        lcd_data(0x30 + d2); // Display tens digit
    } else {
        lcd_data(0x20); // Display space for tens digit if the condition fails
    }

    if (d4 > 0 || d3 > 0 || d2 > 0 || d1 > 0) {
        lcd_data(0x30 + d1); // Display ones digit
    } else {
        lcd_data(0x20); // Display space for ones digit if the condition fails
    }
}



#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000  //set clock frequency

void receive_init(void); //declare receive_init funtion
void lcd_init(void); //declare lcd_init funtion
void lcd_command(unsigned char); //declare lcd_command funtion
void lcd_data(unsigned char); //declare lcd_data funtion

unsigned char receive_value, i; //declare receive_value for switch case
unsigned char a[] = {"RECEIVED DATA:"}; //declare array a[] to print "RECEIVED DATA:" in LCD
unsigned char b[] = {"TRANSMIT DATA:"}; //declare array b[] to print "TRANSMIT DATA:" in LCD

void main() {
    receive_init(); //call receive_init function
    lcd_init(); //call lcd_init function for LCD display initialization
    lcd_command(0x80); //set LCD position of first row first column of 16x2 display
    for (i = 0; i < 14; i++) { //for loop for print array elements one by one
        lcd_data(a[i]); //print array a[i] in first column of LCD
    }
    lcd_command(0xC0); //set LCD position of second row first column of 16x2 display
    for (i = 0; i < 14; i++) { //for loop for print array elements one by one
        lcd_data(b[i]); //print array b[i] in first column of LCD
    }
    while (1) {
        if (PIR1 & 0x20) {
            receive_value = RCREG; //assign the value of RCREG to receive_value
            switch (receive_value) { //initialize switch case
                case 'A': //received character 'A'
                    TXREG = 'a'; //character 'a' should be transmitted via TXREG
                    lcd_command(0x8E); //LCD position to 0x8E
                    lcd_data(RCREG); //print the received value from RCREG
                    lcd_command(0xCE); //LCD position to 0xCE
                    lcd_data(TXREG); //print the transmitted value from TCREG
                    __delay_ms(200);
                    break;
                case 'B': //received character 'B'
                    TXREG = 'b'; //character 'b' should be transmitted via TXREG
                    lcd_command(0x8E); //LCD position to 0x8E
                    lcd_data(RCREG); //print the received value from RCREG
                    lcd_command(0xCE); //LCD position to 0xCE
                    lcd_data(TXREG); //print the transmitted value from TCREG
                    __delay_ms(200);
                    break;
                case 'C': //received character 'C'
                    TXREG = 'c'; //character 'c' should be transmitted via TXREG
                    lcd_command(0x8E); //LCD position to 0x8E
                    lcd_data(RCREG); //print the received value from RCREG
                    lcd_command(0xCE); //LCD position to 0xCE
                    lcd_data(TXREG); //print the transmitted value from TCREG
                    __delay_ms(200);
                    break;
                case 'D': //received character 'D'
                    TXREG = 'd'; //character 'd' should be transmitted via TXREG
                    lcd_command(0x8E); //LCD position to 0x8E
                    lcd_data(RCREG); //print the received value from RCREG
                    lcd_command(0xCE); //LCD position to 0xCE
                    lcd_data(TXREG); //print the transmitted value from TCREG
                    __delay_ms(200);
                    break;
            }
        }
    }
}

void receive_init(void) {
    TRISC = 0xC0; // Set PORTC RC6 and RC7 for UART communication
    TRISD = 0x00; // Set PORTD as output
    PORTD = 0x00; // Initialize PORTD 
    TRISB = 0x00; // Set TRIS for PORTB
    PORTB = 0x00; // Initialize PORTB
    TXSTA = 0x20; // Configure TXSTA register
    RCSTA = 0x90; // Configure RCSTA register
    SPBRG = 0x09; // Set baud rate of 9600 by calculation
}

void lcd_init(void) { //definition of lcd_init function
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

void lcd_command(unsigned char i) { //definition of lcd_command function to set position
    PORTD &= ~0x02; //reset RS to send lcd position
    PORTB = i; //send data to lcd
    PORTD |= 0x01; //set Enable at RD0
    PORTD &= ~0x01; //reset Enable at RD0
    __delay_ms(100); //delay of 100ms
}

void lcd_data(unsigned char i) { //definition of lcd_data function to print data
    PORTD |= 0x02; //reset RS to send lcd position
    PORTB = i; //send data to lcd
    PORTD |= 0x01; //set Enable at RD0
    PORTD &= ~0x01; //reset Enable at RD0
    __delay_ms(100); //delay of 100ms
}




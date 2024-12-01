#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000 // Define system clock frequency for delay functions

// Define constants for LCD control and data pins.
#define C1 RB0  // C1 connected to RB0 (used for keypad column 1)
#define C2 RB1  // C2 connected to RB1 (used for keypad column 2)
#define C3 RB2  // C3 connected to RB2 (used for keypad column 3)
#define R1 RB4  // R1 connected to RB4 (used for keypad row 1)
#define R2 RB5  // R2 connected to RB5 (used for keypad row 2)
#define R3 RB6  // R3 connected to RB6 (used for keypad row 3)
#define R4 RB7  // R4 connected to RB7 (used for keypad row 4)

void init(); // Function to initialize the LCD and keypad setup and LCD initialization
void lcd_Command(unsigned char); // Function to send a command to the LCD
void lcd_Data(unsigned char); // Function to send data (characters) to the LCD
char keypad_scanner(void); // Function to scan which key is pressed on the keypad
char switch_press_scan(void); // Function to detect if a key is pressed and return the value

unsigned char arr3[] = {"Key Pressed : "}; // String to display on LCD before showing the key pressed
unsigned char i; // Index variable for loops
char Key = 'n'; // Variable to store the key pressed

void main(void) {
    init(); // Initialize LCD and keypad
    lcd_Command(0x80); // Set cursor to the first line of LCD

    // Display the string "Key Pressed :" on the LCD
    for (i = 0; i < sizeof (arr3) - 1; i++) { // Loop through each character in the string
        lcd_Data(arr3[i]); // Send each character to the LCD
    }

    while (1) { // Infinite loop to continuously scan the keypad
        Key = switch_press_scan(); // Get the pressed key from the keypad
        lcd_Command(0x8E); // Move cursor to the 15th position of first line
        lcd_Data(Key); // Display the key pressed on the LCD
    }
}

void init() {
    TRISB = 0xF0; // Set RB4-RB7 as input for keypad rows and RB0-RB2 as output for columns
    PORTB = 0xF0; // Initialize PORTB for keypad scanning
    TRISC = 0x00; // Set PORTC as output for LCD
    PORTC = 0x00; // Initialize PORTC to zero
    TRISD = 0x00; // Set PORTD as output for LCD data signals
    PORTD = 0x00; // Initialize PORTD to zero
    OPTION_REG &= 0x7F; // Enable pull-ups for keypad rows

    // Initialize the LCD in 8-bit mode
    lcd_Command(0x33); // Send initialization sequence (8-bit mode)
    __delay_ms(100); // Wait for 100ms 
    lcd_Command(0x34); // Set number of lines and font
    __delay_ms(100); // Wait for 100ms
    lcd_Command(0x35); // Additional function set
    __delay_ms(100); // Wait for 100ms
    lcd_Command(0x38); // 16x2 mode, 5x8 dot matrix
    __delay_ms(100); // Wait for 100ms
    lcd_Command(0x0C); // Display on, cursor off
    __delay_ms(100); // Wait for 100ms
    lcd_Command(0x01); // Clear display
    __delay_ms(100); // Wait for 100ms
}

void lcd_Data(unsigned char i) {
    PORTC |= 0x01; // Set RS high for sending data
    PORTD = i; // Place character data on PORTD to send to LCD
    PORTC |= 0x08; // set Enable pin
    __delay_ms(1); // Short delay for LCD to process
    PORTC &= ~0x08; // Clear E pin
    __delay_ms(100); // Wait for 100ms
}

void lcd_Command(unsigned char i) {
    PORTC &= ~0x01; // Set RS low to select command 
    PORTD = i; // Place command on PORTD to send to LCD
    PORTC |= 0x08; // set Enable pin
    __delay_ms(1); // Short delay for LCD to process
    PORTC &= ~0x08; // Clear Enable pin
    __delay_ms(100); // Wait for 100ms
}

char keypad_scanner(void) {
    // Scanning the keypad by activating one column at a time
    char key = 'n'; // Default key value when no key is pressed
    C1 = 0;
    C2 = 1;
    C3 = 1; // Set column 1 active (low) and others inactive (high)

    if (R1 == 0) {
        while (R1 == 0);
        return '3';
    } // Check if '3' is pressed
    if (R2 == 0) {
        while (R2 == 0);
        return '6';
    } // Check if '6' is pressed
    if (R3 == 0) {
        while (R3 == 0);
        return '9';
    } // Check if '9' is pressed
    if (R4 == 0) {
        while (R4 == 0);
        return '#';
    } // Check if '#' is pressed

    C1 = 1;
    C2 = 0;
    C3 = 1; // Set column 2 active (low)

    if (R1 == 0) {
        while (R1 == 0);
        return '2';
    } // Check if '2' is pressed
    if (R2 == 0) {
        while (R2 == 0);
        return '5';
    } // Check if '5' is pressed
    if (R3 == 0) {
        while (R3 == 0);
        return '8';
    } // Check if '8' is pressed
    if (R4 == 0) {
        while (R4 == 0);
        return '0';
    } // Check if '0' is pressed

    C1 = 1;
    C2 = 1;
    C3 = 0; // Set column 3 active (low)

    if (R1 == 0) {
        while (R1 == 0);
        return '1';
    } // Check if '1' is pressed
    if (R2 == 0) {
        while (R2 == 0);
        return '4';
    } // Check if '4' is pressed
    if (R3 == 0) {
        while (R3 == 0);
        return '7';
    } // Check if '7' is pressed
    if (R4 == 0) {
        while (R4 == 0);
        return '*';
    } // Check if '*' is pressed

    return 'n'; // Return 'n' if no key is pressed
}

char switch_press_scan(void) {
    char key = 'n'; // Assume no key is pressed initially

    while (key == 'n') { // continuous scanning until a key is pressed
        key = keypad_scanner(); // Call keypad_scanner to check for key press
    }
    return key; // Return the pressed key
}



#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000 //clock frequency

void init();  // Declaration of an init function
void lcd_Command(unsigned char); // Declaration of an lcd_Command function
void lcd_Data(unsigned char); // Declaration of an lcd_Data function

unsigned char array[18] = "VIGNESH"; // Array declaration as an unsigned char datatype
unsigned char x; // Variable declaration as an unsigned char datatype

void main(void) {
    init(); // init function call
    unsigned char position1=0x82; // lcd_Command function call with position 0x82 which is the initial position of lcd cursor line1
    for(x = 0; x < 7; x++) {
        lcd_Command(position1++);
        lcd_Data(array[x]); // lcd_Data function call using for loop
    }
    
    // Print the array from right to left starting from position 0xCE
    unsigned char position2 = 0xCE; //assigning position as 
    for(x = 0;x < 7;x++) {
        lcd_Command(position2--); // Move the cursor to the left
        lcd_Data(array[x]); // lcd_Data function call to print character
    }

    while(1); // while used at last to stop the operation after completion of the for loop
}

void init() { // Defining init function
    TRISC = 0x00; // Initial setting the PORTC pins as output 0000 0000
    TRISD = 0x00; // Initial setting the PORTC pins as output 0000 0000
    lcd_Command(0x33); // Function set command for 8-bit  N=1 for 2-line display and F=0 for 5x7 dot matrix 0011 1000
    __delay_ms(100); // 100ms delay given so that no data transferred during this time
    lcd_Command(0x34); // Function set command for 8-bit  N=1 for 2-line display and F=0 for 5x7 dot matrix 0011 1000
    __delay_ms(100); // 100ms delay given so that no data transferred during this time
    lcd_Command(0x35); // Function set command for 8-bit  N=1 for 2-line display and F=0 for 5x7 dot matrix 0011 1000
    __delay_ms(100); // 100ms delay given so that no data transferred during this time
    lcd_Command(0x38); // Function set command for 8-bit  N=1 for 2-line display and F=0 for 5x7 dot matrix 0011 1000
    __delay_ms(100); // 100ms delay given so that no data transferred during this time
    lcd_Command(0x0C); // stops the cursor
    __delay_ms(100); // 100ms delay
    lcd_Command(0x01); // clear command
    __delay_ms(100); // 100ms delay
}

void lcd_Data(unsigned char i) { // Defining lcd_Data function
    PORTC |= 0x08; // set RS as 1 at RC3 pin for sending data
    PORTD = i; // PORTD is set with a parameter i
    PORTC |= 0x01; // Enable is ON
    PORTC &= ~0x01; // Enable is OFF
    __delay_ms(100); // 100ms delay
}

void lcd_Command(unsigned char i) { // Defining lcd_Command function
    PORTC &= ~0x08; // set RS as 0 at RC3 pin for sending command
    PORTD = i; // PORTD is set with a parameter i
    PORTC |= 0x01; // Enable is ON
    PORTC &= ~0x01; // Enable is OFF
    __delay_ms(100); // 100ms delay
}

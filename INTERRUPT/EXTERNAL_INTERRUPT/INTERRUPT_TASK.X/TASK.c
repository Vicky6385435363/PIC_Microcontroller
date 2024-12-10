#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000 //set clock frequency to 6MHz

unsigned char s; //declare character s

void main() { //initiate main function
    TRISB = 0x01; //select input and output for port B 0000 0001
    PORTB = 0x01;//configure port B as 0000 0001
    TRISD = 0x00;//select input and output for port  0000 0000
    PORTD = 0x00;//configure port D as output 0000 0000
    TRISC = 0x00;//select input and output for port 0000 0000
    PORTC = 0x00; //configure port C as output 0000 0000
    OPTION_REG &= 0x7F; //configure option register to enable internal Pull-Up on pin RB0
    INTCON = 0x90; //configure INTCON register using external intercept 1001 0000
    while (1) {
        PORTC = ~PORTC; //set all pin in PORTC as HIGH
        __delay_ms(500); //delay of 500ms
    }
}

void __interrupt()ISR() { //define __interrupt and ISR to enable interrupt function
    if (INTCON & 0x02) { //checking for interrupt activation by performing bitwise AND operation with 0x01 (RBIF)
        s = PORTB; //assign PORTB value to s
        if (s == 0x01) { //checks for switch RB0 pressed
            PORTD = ~PORTD; //set all the pins in PORTD as HIGH
        }
    }
    INTCON &= (~(0x02)); //clear the RBIF bit
    __delay_ms(3000); //delay for 3000ms
}



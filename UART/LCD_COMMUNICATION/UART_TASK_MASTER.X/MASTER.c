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

void transmit_init(void); //Declare transmit_init function
unsigned char value, value1; //Declaration of variables value and value1 for switch case

void main() {
    transmit_init(); //call transmit_init function
    while (1) { //while loop for continuous process
        value = PORTB; // assign PORTB to value
        //Pull-Up switch circuit
        switch (value) { //initiate switch case reading value
            case 0xE0: //if 1110 0000 as the RB4 switch if LOW state
                TXREG = 'A'; //transmit character A via TXREG register
                __delay_ms(200);
                break;
            case 0xD0: //if 1101 0000 as the RB5 switch if LOW state
                TXREG = 'B'; //transmit character B via TXREG register
                __delay_ms(200);
                break;
            case 0xB0: //if 1011 0000 as the RB6 switch if LOW state
                TXREG = 'C'; //transmit character C via TXREG register
                __delay_ms(200);
                break;
            case 0x70: //if 0111 0000 as the RB7 switch if LOW state
                TXREG = 'D'; //transmit character D via TXREG register
                __delay_ms(200);
                break;
        }

        // Check if data is received
        if (PIR1 & 0x20) { // Corrected interrupt flag check
            value1 = RCREG; // Read received data from RCREG register
            switch (value1) {
                case 'a':
                    PORTD = 0x02; // Set PORTD RD1 for 'a'
                    break;
                case 'b':
                    PORTD = 0x01; // Set PORTD RD0 for 'b'
                    break;
                case 'c':
                    PORTD = 0x03; // Set PORTD RD0 and RD1 for 'c'
                    break;
                case 'd':
                    PORTD = 0x00; // Set PORTD LOW for 'd'
                    break;
                default:
                    PORTD = 0x00; // Default case to set PORTD LOW
                    break;
            }
        }
    }
}

void transmit_init(void) { //defining transmit_init function
    OPTION_REG &= 0x7F; // Configure option register
    TRISC = 0xC0; // Set PORTC RC6 and RC7 for UART communication 1100 0000
    TRISD = 0x00; // Set PORTD as output
    PORTD = 0x00; // Initialize PORTD 
    TRISB = 0xF0; // Set TRIS for PORTB 1111 0000
    PORTB = 0x00; // Initialize PORTB
    TXSTA = 0x20; // Configure TXSTA register
    RCSTA = 0x90; // Configure RCSTA register
    SPBRG = 0x09; // Set baud rate of 9600 by calculation
}


#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000

void transmit_init(void);
unsigned char value;

void main() {
    transmit_init();
    while (1) {
        value = PORTB;
        switch (value) {
            case 0xE0:
                TXREG = 'a';
                __delay_ms(200);
                break;

            case 0xD0:
                TXREG = 'b';
                __delay_ms(200);
                break;

            case 0xB0:
                TXREG = 'c';
                __delay_ms(200);
                break;

            case 0x70:
                TXREG = 'd';
                __delay_ms(200);
                break;
        }

    }
}

void transmit_init(void) {
    OPTION_REG &= 0x7F;
    TRISC = 0xC0;
    TRISB = 0xF0;
    PORTB = 0x00;
    TXSTA = 0x20;
    RCSTA = 0x90;
    SPBRG = 0x09;
} 
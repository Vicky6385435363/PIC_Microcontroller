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

void receive_init(void);
unsigned char receive_value;

void main() {
    receive_init();
    while (1) {
        if (PIR1 & 0x20) {
            receive_value = RCREG;
            switch (receive_value) {
                case 'a':
                    PORTD = 0x10;
                    break;
                case 'b':
                    PORTD = 0x02;
                    break;
                case 'c':
                    PORTD = 0x12;
                    break;
                case 'd':
                    PORTD = 0x00;
                    break;
                default:
                    PORTD = 0x00;
            }
        }
    }
}

void receive_init(void) {
    TRISC = 0xC0;
    TRISD = 0x00;
    PORTD = 0x00;
    TXSTA = 0x20;
    RCSTA = 0x90;
    SPBRG = 0x09;
}
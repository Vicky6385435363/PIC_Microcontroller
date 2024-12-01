#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000 //6MHZ clock speed
void main(void) {
    TRISC=0XFB;  //setting pin RC2 as output 1111 1011 in TRISC
    while(1)
    {
    PORTC=0x04;  //selecting pin RC6 0000 0100 for output
    __delay_ms(200); //setting delay as 1000ms (1 second)
    PORTC=0x00;  //0000 0000 (making every pins OFF state)
    __delay_ms(200);  //setting delay as 1000ms (1 second)
    }
    
}

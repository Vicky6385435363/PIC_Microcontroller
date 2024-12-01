#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000 //clock frequency
void main(void) {
    TRISD=0xBD; //setting RD1 and RD6 as outputs 1011 1101
    while(1)
    {
        PORTD = 0x40; //setting condition that pins RD6=ON and RD1=OFF
        __delay_ms(3000); //Delay for 3 seconds
        PORTD = 0x00; //setting condition that pins RD6=OFF and RD1=OFF
        __delay_ms(3000);  //Delay for 3 seconds
        PORTD = 0x02; //setting condition that pins RD6=OFF and RD1=ON
        __delay_ms(3000);  //Delay for 3 seconds
        PORTD = 0x42; //setting condition that pins RD6=ON and RD1=ON
        __delay_ms(3000);  //Delay for 3 seconds
        
        
    }
}

#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000 //set clock frequency of 6MHZ

void main(void) {
    unsigned char value;
    TRISD=0x00;  //setting all pins of PORTD as output 0000 0000
    PORTD=0x00;  //initially setting PORTD pins as 0000 0000
    TRISC=0x0F;  //setting the inputs in PORTC 0000 1111
    PORTC=0x00;  //initially setting PORTC pins as 0000 0000
    while(1){
        value=PORTC;  //assigning the unsigned char value as PORTC pins
        switch(value){
            case 0x0E:  //assuming case 0x0E (that is the pin RC0 is in LOW state) 0000 1110
                PORTD=0x08;  //for this case setting PORTC pins RD5 as LOW  and RD3  as HIGH 0000 1000
                break;  //break the case for end the program
            case 0x0D:  //assuming case 0x0D (that is the pin RC1 is in LOW state) 0000 1101
                PORTD=0x00;  //for this case setting PORTC pins RD5  and RD3  as LOW 0000 0000
                break;  //break the case for end the program
            case 0x0B:  //assuming case 0x0B (that is the pin RC2 is in LOW state) 0000 1011
                PORTD=0x20;  //for this case setting PORTC pins RD5 as HIGH and RD3  as LOW 0010 0000
                break;  //break the case for end the program
            case 0x07:  //assuming case 0x07 (that is the pin RC3 is in LOW state) 0000 0111
                PORTD=0x28;  //for this case setting PORTC pins RD5 and RD3  as HIGH 0010 1000
                break;  //break the case for end the program
            case 0x0F:  //assuming case 0x0F as default  (that is all the input pins of PORTB as HIGH ) 0000 1111
                PORTD=0x00;  //for this default case setting PORTC pins RD5 and RD3  as LOW 0000 0000
                break;  //break the case for end the program            
        }
    }
}


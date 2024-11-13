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
unsigned char value; //assigning an unsigned char for switch case
void main(void) 
{
    TRISC = 0x00; //setting all pins of PORTC as output 0000 0000
    PORTC=0x00;  //initially setting PORTC pins as 0000 0000
    TRISB=0xF0;  //setting the inputs in PORTB 1111 0000
    PORTB=0x00;  //initially setting PORTB pins as 0000 0000
    while(1)
    {
        value = PORTB;  //assigning the unsigned char value as PORTB pins
        switch(value)  //using switch case for various values of PORTB
        {
            case 0xE0:  //assuming case 0xE0 (that is the pin RB4 is in LOW state) 1110 0000
                PORTC=0x04;  //for this case setting PORTC pins RC7 as LOW  and RC2  as HIGH 0000 0100
                break;  //break the case for end the program 
            case 0xD0:  //assuming case 0xD0 (that is the pin RB5 is in LOW state) 1101 0000
                PORTC=0x00;  //for this case setting PORTC pins RC7  and RC2  as LOW 0000 0000
                break;  //break the case for end the program
            case 0xB0:  //assuming case 0xB0 (that is the pin RB6 is in LOW state) 1011 0000
                PORTC=0x80;  //for this case setting PORTC pins RC7 as HIGH and RC2  as LOW 1000 0000
                break;  //break the case for end the program
            case 0x70:  //assuming case 0x70 (that is the pin RB7 is in LOW state) 0111 0000
                PORTC=0x84;  //for this case setting PORTC pins RC7 and RC2  as HIGH 1000 0100
                break;  //break the case for end the program
            case 0xF0:  //assuming case 0xF0 as default  (that is all the input pins of PORTB as HIGH ) 1111 0000
                PORTC=0x00;  //for this default case setting PORTC pins RC7 and RC2  as LOW 0000 0000
                break;  //break the case for end the program
                        
}
}
}

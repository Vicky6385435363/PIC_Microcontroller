#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>                  // standard header for PIC
#define _XTAL_FREQ 6000000       // system frequency of 6 MHz

void pwm(void);                  // Declaration of pwm Function
void initiate(void);             //  Declaration of initialization Function
unsigned char pwmlow10, pwmhigh10, pwmlow50, pwmhigh50, pwmlow80, pwmhigh80; // Declare PWM duty cycle variables

void main(void) {
    initiate();                  // Call initialization function
    while(1){                    // Infinite loop
        pwm();                   // Call PWM function
    }
}

void initiate(void){
    TRISC = 0xFB;                // Set RC2 as output in PORTC and other pins as output for CCP1 1111 1011
    CCP1CON = 0x0F;              // Configure CCP1 module for PWM mode
    T2CON = 0x06;                // Configure Timer2: Prescaler is 1:16, Timer2 is on 0000 0110
    PR2 = 0x5D;                  // Load PR2 register with 93 for desired frequency 0101 1101

    // Configure 10% duty cycle
    pwmlow10 = 0x02;             // Low byte for 10% duty cycle 0000 0010
    pwmlow10 = (pwmlow10 << 4);  // Shift to correct position 0010 0000
    pwmhigh10 = 0x09;            // High byte for 10% duty cycle 0000 1001

    // Configure 50% duty cycle
    pwmlow50 = 0x00;             // Low byte for 50% duty cycle 0000 0000
    pwmlow50 = (pwmlow50 << 4);  // Shift to correct position 0000 0000
    pwmhigh50 = 0x2F;            // High byte for 50% duty cycle 0010 1111

    // Configure 80% duty cycle
    pwmlow80 = 0x01;             // Low byte for 80% duty cycle 0000 0001 
    pwmlow80 = (pwmlow80 << 4);  // Shift to correct position 0001 0000
    pwmhigh80 = 0x4B;            // High byte for 80% duty cycle 0100 1011
}

void pwm(){
    // Set duty cycle to 10%
    CCPR1L = pwmhigh10;          // Load high byte of duty cycle into CCPR1L 0000 1001
    CCP1CON = (CCP1CON & 0xCF) | pwmlow10; // Load low byte of duty cycle into CCP1CON 0010 1100
    __delay_ms(3000);            // Delay for 3 seconds

    // Set duty cycle to 50%
    CCPR1L = pwmhigh50;          // Load high byte of duty cycle into CCPR1L 0010 1111
    CCP1CON = (CCP1CON & 0xCF) | pwmlow50; // Load low byte of duty cycle into CCP1CON 0000 1100
    __delay_ms(3000);            // Delay for 3 seconds

    // Set duty cycle to 80%
    CCPR1L = pwmhigh80;          // Load high byte of duty cycle into CCPR1L 0001 0000
    CCP1CON = (CCP1CON & 0xCF) | pwmlow80; // Load low byte of duty cycle into CCP1CON 0001 1100
    __delay_ms(3000);            // Delay for 3 seconds
}

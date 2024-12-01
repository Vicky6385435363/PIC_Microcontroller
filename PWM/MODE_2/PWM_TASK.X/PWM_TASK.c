#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>                  // Include standard header for PIC
#define _XTAL_FREQ 6000000       // Define the system frequency (6 MHz)

void pwm(void);                  // Declaration of pwm Function
void initiate(void);             //  Declaration of initialization Function
unsigned char pwmlow20, pwmhigh20, pwmlow60, pwmhigh60, pwmlow90, pwmhigh90; // Declare PWM duty cycle variables

void main(void) {
    initiate();                  // Call initialization function
    while(1){                    // Infinite loop
        pwm();                   // Call PWM function
    }
}

void initiate(void){
    TRISC = 0xFD;                // Set TRISC register: RC1 as output in PORTC (for PWM) 1111 1101
    CCP2CON = 0x0F;              // Configure CCP2 module for PWM mode 0000 1111
    T2CON = 0x06;                // Configure Timer2: Prescaler is 1:16, Timer2 is on 1111 0110
    PR2 = 0x2E;                  // Load PR2 register with 46 for 2kHz frequency 0010 1110

    // Configure 20% duty cycle
    pwmlow20 = 0x02;             // Low byte for 20% duty cycle 0000 0010
    pwmlow20 = (pwmlow20 << 4);  // Shift left by 4 positions 0010 0000
    pwmhigh20 = 0x09;            // High byte for 20% duty cycle 0000 1001   

    // Configure 60% duty cycle
    pwmlow60 = 0x01;             // Low byte for 60% duty cycle 0000 0001
    pwmlow60 = (pwmlow60 << 4);  // Shift left by 4 positions 0001 0000
    pwmhigh60 = 0x1C;            // High byte for 60% duty cycle 0001 1100

    // Configure 90% duty cycle
    pwmlow90 = 0x01;             // Low byte for 90% duty cycle 0000 0001
    pwmlow90 = (pwmlow90 << 4);  // Shift left by 4 positions 0001 0000
    pwmhigh90 = 0x2A;            // High byte for 90% duty cycle 0010 1010
}

void pwm(){
    // Set duty cycle to 20%
    CCPR2L = pwmhigh20;          // Load high byte of duty cycle into CCPR2L 0000 1001
    CCP2CON = (CCP2CON & 0xCF) | pwmlow20; // Load low byte of duty cycle into CCP2CON 0010 1100
    __delay_ms(3000);            // Delay for 3 seconds  

    // Set duty cycle to 60%
    CCPR2L = pwmhigh60;          // Load high byte of duty cycle into CCPR2L 0001 1100
    CCP2CON = (CCP2CON & 0xCF) | pwmlow60; // Load low byte of duty cycle into CCP2CON 0001 1100
    __delay_ms(3000);            // Delay for 3 seconds

    // Set duty cycle to 90%
    CCPR2L = pwmhigh90;          // Load high byte of duty cycle into CCPR2L 0010 1010
    CCP2CON = (CCP2CON & 0xCF) | pwmlow90; // Load low byte of duty cycle into CCP2CON 0001 1100
    __delay_ms(3000);            // Delay for 3 seconds
}

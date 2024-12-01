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

void initiate();
void lcd_data(unsigned char);
void lcd_command(unsigned char);
void lcd_out(float); // Corrected to use float for decimal representation
unsigned char v[20] = {"BATT VOLT:     "};
unsigned char c[15] = {"LOW MEDIUM HIGH"};
unsigned char value, x;
unsigned int d1, d2, d3, j = 0, i; // Initialize j to 0
void main() {
    initiate();
    while (1) {
        value = PORTB;
        switch (value) {
            case 0xE0:
                lcd_command(0x80);
                for (x = 0; x < 9; x++) {
                    lcd_data(v[x]);
                }
                lcd_command(0xC0);
                for (x = 0; x < 5; x++) {
                    lcd_data(v[x]);
                }
                lcd_command(0x8B);
                lcd_out(j);
                break;
            case 0xD0:
                j++;
                lcd_command(0x8B);
                lcd_out(j);
                if (j > 15.5 && j <= 17.5) {
                    lcd_command(0xC0); // Correct cursor position
                    for (x = 0; x < 3; x++) {
                        lcd_data(c[x]);
                    }
                } else if (j > 17.5 && j <= 20.5) {
                    lcd_command(0xC0); // Correct cursor position
                    for (x = 4; x < 10; x++) {
                        lcd_data(c[x]);
                    }
                } else if (j > 20.5 && j <= 22.5) {
                    lcd_command(0xC0); // Correct cursor position
                    for (x = 11; x < 15; x++) {
                        lcd_data(c[x]);
                    }
                }
                if (j > 22.5) {
                    j = 22.5; // Ensure maximum value
                }
                break;
            case 0xB0:
                j--;
                if (j < 15.5) {
                    j = 15.5; // Ensure minimum value
                } // Ensure minimum value
                }
                lcd_command(0x8B);
                lcd_out(j);
                break;
            case 0x70:
                j = 15.5;
                lcd_command(0x8B);
                lcd_out(j);
                break;
        }
    }
}

void initiate() {
    TRISC = 0x00;
    TRISB = 0xF0;
    TRISD = 0x00;
    PORTB = 0x00;
    OPTION_REG &= 0x7F;
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x38);
    __delay_ms(100);
    lcd_command(0x06);
    __delay_ms(100);
    lcd_command(0x0C);
    __delay_ms(100);
    lcd_command(0x01);
    __delay_ms(100);
    j = 17.5; // Set initial value
}

void lcd_data(unsigned char i) { // Define lcd_data function
    PORTC |= 0x08; // Set RS as 1 at RC3 pin for sending data
    PORTD = i; // PORTD is set with a parameter i
    PORTC |= 0x01; // Enable is ON
    PORTC &= ~0x01; // Enable is OFF
    __delay_ms(100); // 100ms delay
}

void lcd_command(unsigned char i) { // Define lcd_command function
    PORTC &= ~0x08; // Set RS as 0 at RC3 pin for sending command
    PORTD = i; // PORTD is set with a parameter i
    PORTC |= 0x01; // Enable is ON
    PORTC &= ~0x01; // Enable is OFF
    __delay_ms(100); // 100ms delay
}

void lcd_out(float i) { // Correct to use float for decimal representation
    unsigned char dot = '.';
    unsigned int int_part = (unsigned int) i;
    unsigned int frac_part = (unsigned int) ((i - int_part) * 10); // Get fractional part
    d3 = (unsigned char) (int_part / 10);
    d2 = (unsigned char) (int_part % 10);
    d1 = (unsigned char) (frac_part);
    lcd_command(0x8B);
    lcd_data(0x30 + d3);
    lcd_command(0x8C);
    lcd_data(0x30 + d2);
    lcd_command(0x8D);
    lcd_data(dot);
    lcd_command(0x8E);
    lcd_data(0x30 + d1);
}

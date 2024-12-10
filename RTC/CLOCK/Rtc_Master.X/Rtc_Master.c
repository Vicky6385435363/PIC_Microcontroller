#pragma config FOSC = HS     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON     // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial ProgramMinutesg Enable bit (RB3 is digital I/O, HV on MCLR must be used for programMinutesg)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define _XTAL_FREQ 20000000  // Define system clock frequency as 20 MHz
#define RS RC2               // Define RS pin for LCD
#define EN RC1               // Define EN pin for LCD
void init(void); // LCD initialization
void I2C_init(const unsigned long); // Initialize I2C with given frequency
void I2C_write(unsigned char); // Write data to I2C bus
int I2C_read(int); // Read data from I2C bus
void I2C_start(); // Generate I2C start condition
void I2C_wait(); // Wait for I2C operations to complete
void I2C_stop(); // Generate I2C stop condition
void lcd_command(unsigned char); // Send a command to LCD
void lcd_data(unsigned char); // Send data to LCD
int bcd_2_dec(int); // Convert BCD to decimal
int dec_2_bcd(int); // Convert decimal to BCD
void settime(void); // Set initial time in RTC
void upDate(void); // Update time from RTC
char msg1[5] = {"TIME:"}; // Message to display for time
char msg2[5] = {"DATE:"}; // Message to display for date
int i, j, k, l; // Loop counters
int Seconds = 55, Minutes = 59, Hours = 23; // Initial time values
int Date = 31, Month = 12, Year = 24; // Initial date values
char Seconds1, Seconds2, Minutes1, Minutes2, Hours1, Hours2, Date1, Date2, Month1, Month2, Year1, Year2; // Split digits for display

void main() {
    init(); // Initialize LCD
    I2C_init(100); // Initialize I2C at 100 kHz
    settime(); // Set initial time and date in RTC

    while (1) {
        upDate(); // Update time and date from RTC

        // Split digits for seconds
        Seconds1 = Seconds / 10;
        Seconds2 = Seconds % 10;

        // Split digits for minutes
        Minutes1 = Minutes / 10;
        Minutes2 = Minutes % 10;

        // Split digits for hours
        Hours1 = Hours / 10;
        Hours2 = Hours % 10;

        // Split digits for date
        Date1 = Date / 10;
        Date2 = Date % 10;

        // Split digits for month
        Month1 = Month / 10;
        Month2 = Month % 10;

        // Split digits for year
        Year1 = Year / 10;
        Year2 = Year % 10;


        lcd_command(0xC0); // Move cursor to second line
        for (i = 0; i < 5; i++) lcd_data(msg1[i]); // Display "TIME:"
        lcd_data(Hours1 + '0'); // Display hours (tens digit)
        lcd_data(Hours2 + '0'); // Display hours (units digit)
        lcd_data(0x2D); // Display colon ':'
        lcd_data(Minutes1 + '0'); // Display minutes (tens digit)
        lcd_data(Minutes2 + '0'); // Display minutes (units digit)
        lcd_data(0x2D); // Display colon ':'
        lcd_data(Seconds1 + '0'); // Display seconds (tens digit)
        lcd_data(Seconds2 + '0'); // Display seconds (units digit)

        // Display date on LCD
        lcd_command(0x80); // Move cursor to first line
        for (i = 0; i < 5; i++) lcd_data(msg2[i]); // Display "DATE:"
        lcd_data(Date1 + '0'); // Display date (tens digit)
        lcd_data(Date2 + '0'); // Display date (units digit)
        lcd_data(0x2D); // Display dash '-'
        lcd_data(Month1 + '0'); // Display month (tens digit)
        lcd_data(Month2 + '0'); // Display month (units digit)
        lcd_data(0x2D); // Display dash '-'
        lcd_data(Year1 + '0'); // Display year (tens digit)
        lcd_data(Year2 + '0'); // Display year (units digit)

        __delay_ms(100); // Delay for 500 ms before updating again
    }
}

void init(void) {
    TRISD = 0x00; // Set PORTD as output for LCD data
    TRISC = 0x18; // Set RC3 and RC4 as inputs (SCL, SDA for I2C)
    PORTD = 0x00; // Clear PORTD

    // Initialize LCD in 8-bit mode
    lcd_command(0x34);
    __delay_ms(10);
    lcd_command(0x33);
    __delay_ms(10);
    lcd_command(0x32);
    __delay_ms(10);
    lcd_command(0x38); // 8-bit, 2-line, 5x8 font
    __delay_ms(10);
    lcd_command(0x0C); // Display ON, cursor OFF
    __delay_ms(10);
    lcd_command(0x06); // Increment cursor
    __delay_ms(10);
    lcd_command(0x01); // Clear display
    __delay_ms(10);
}

void lcd_command(unsigned char i) {
    RS = 0; // Set RS to 0 for command
    PORTD = i; // Send command to PORTD
    EN = 1; // Generate a high-to-low pulse on EN
    EN = 0;
    __delay_ms(10); // Small delay for LCD to process command
}

void lcd_data(unsigned char i) {
    RS = 1; // Set RS to 1 for data
    PORTD = i; // Send data to PORTD
    EN = 1; // Generate a high-to-low pulse on EN
    EN = 0;
    __delay_ms(10); // Small delay for LCD to process data
}

void I2C_init(const unsigned long feq_k) {
    SSPCON = 0x28; // Enable I2C master mode
    SSPSTAT = 0x00; // Disable slew rate control
    SSPADD = (_XTAL_FREQ / (4 * feq_k * 100)) - 1; // Set baud rate
}

void I2C_wait() {
    while (SSPCON2 & 0x1F || SSPSTAT & 0x04); // Wait for I2C operations to finish
}

void I2C_start() {
    I2C_wait(); // Wait for I2C bus to be ready
    SSPCON2 = 0x01; // Generate start condition
}

void I2C_stop() {
    I2C_wait(); // Wait for I2C bus to be ready
    SSPCON2 = 0x04; // Generate stop condition
}

void I2C_write(unsigned char temp) {
    I2C_wait(); // Wait for I2C bus to be ready
    SSPBUF = temp; // Write data to SSPBUF
}

int I2C_read(int ack) {
    int value;
    I2C_wait(); // Wait for I2C bus to be ready
    SSPCON2 = 0x08; // Enable receive mode
    I2C_wait();
    value = SSPBUF; // Read received value
    I2C_wait();
    ACKDT = (ack) ? 0 : 1; // Acknowledge bit (0: ACK, 1: NACK)
    SSPCON2 = 0x10; // Send ACK/NACK
    return value; // Return received value
}

int dec_2_bcd(int temp) {
    return ((temp / 10) << 4) + (temp % 10); // Convert decimal to BCD
}

int bcd_2_dec(int temp) {
    return ((temp >> 4) * 10) + (temp & 0x0F); // Convert BCD to decimal
}

void settime(void) {
    I2C_start(); // Generate start condition
    I2C_write(0xD0); // Address RTC (write mode)
    I2C_write(0x00); // Set register pointer to 00h
    I2C_write(dec_2_bcd(Seconds)); // Set initial seconds
    I2C_write(dec_2_bcd(Minutes)); // Set initial minutes
    I2C_write(dec_2_bcd(Hours)); // Set initial hours
    I2C_write(0x00); // Skip day register
    I2C_write(dec_2_bcd(Date)); // Set initial date
    I2C_write(dec_2_bcd(Month)); // Set initial month
    I2C_write(dec_2_bcd(Year)); // Set initial year
    I2C_stop(); // Generate stop condition
}

void upDate(void) {
    I2C_start(); // Generate start condition
    I2C_write(0xD0); // Address RTC (write mode)
    I2C_write(0x00);
    I2C_stop(); // Set register pointer to 00h
    I2C_start(); // Restart condition
    I2C_write(0xD1); // Address RTC (read mode)
    Seconds = bcd_2_dec(I2C_read(1)); // Read seconds with ACK
    Minutes = bcd_2_dec(I2C_read(1)); // Read minutes with ACK
    Hours = bcd_2_dec(I2C_read(1)); // Read hours with ACK
    (I2C_read(1)); // Skip day register
    Date = bcd_2_dec(I2C_read(1)); // Read date with ACK
    Month = bcd_2_dec(I2C_read(1)); // Read month with ACK
    Year = bcd_2_dec(I2C_read(1)); // Read year with NACK
    I2C_stop(); // Generate stop condition
    I2C_start(); // Generate start condition
    I2C_write(0xD1); // Address RTC (read mode)
    I2C_read(1); // Skip day register
    I2C_stop(); // Generate stop condition
}


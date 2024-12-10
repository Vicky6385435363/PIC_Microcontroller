// Configuration settings for PIC microcontroller
#pragma config FOSC = EXTRC     // Select external RC oscillator
#pragma config WDTE = OFF       // Disable Watchdog Timer
#pragma config PWRTE = OFF      // Disable Power-up Timer
#pragma config BOREN = OFF      // Disable Brown-out Reset
#pragma config LVP = OFF        // Disable Low-Voltage Programming
#pragma config CPD = OFF        // Disable Data EEPROM Code Protection
#pragma config WRT = OFF        // Disable Flash Program Memory Write Protection
#pragma config CP = OFF         // Disable Flash Program Memory Code Protection

#include <xc.h>                 // Include processor-specific header file
#define _XTAL_FREQ 16000000     // Define oscillator frequency for delay functions
#define EEPROM_Address_R 0xA1   // EEPROM read address in I2C communication
#define EEPROM_Address_W 0xA0   // EEPROM write address in I2C communication

// Function declarations
void I2C_Master_init(const unsigned long baud); // Initialize I2C with specified baud rate
void I2C_Master_Wait(); // Wait for I2C operations to complete
void I2C_Master_Start(); // Send I2C start condition
void I2C_Master_RepeatedStart(); // Send I2C repeated start condition
void I2C_Master_Stop(); // Send I2C stop condition
unsigned char I2C_Master_Write(unsigned char data); // Write data over I2C
unsigned char I2C_Read_Byte(); // Read a byte of data over I2C
void I2C_NACK(void); // Send a Not-Acknowledge signal
void EEPROM_Write(unsigned int add, unsigned char data); // Write byte to EEPROM
unsigned char EEPROM_Read(unsigned int add); // Read byte from EEPROM

void main(void) {
    I2C_Master_init(100000); // Initialize I2C master at 100kHz baud rate
    unsigned int Address = 0x0020; // EEPROM address to start writing data
    unsigned char Data = 0x04; // Initial data value to write
    unsigned char ret1, ret2, ret3; // Variables to store read data from EEPROM

    // Write data to EEPROM at sequential addresses
    EEPROM_Write(Address++, Data++);
    __delay_ms(10); // Delay to allow EEPROM write to complete
    EEPROM_Write(Address++, Data++);
    __delay_ms(10);
    EEPROM_Write(Address, Data);
    __delay_ms(10);

    // Read back data from EEPROM
    Address = 0x0020; // Reset address to read back data
    TRISD = 0x00; // Set PORTD as output to display data
    ret1 = EEPROM_Read(Address++); // Read first byte from EEPROM
    PORTD = ret1; // Display first byte on PORTD
    __delay_ms(1000);
    ret2 = EEPROM_Read(Address++); // Read second byte from EEPROM
    PORTD = ret2; // Display second byte on PORTD
    __delay_ms(1000);
    ret3 = EEPROM_Read(Address); // Read third byte from EEPROM
    PORTD = ret3; // Display third byte on PORTD

    while (1) {
        // Endless loop
    }
    return;
}

// Initialize I2C Master mode with specified baud rate

void I2C_Master_init(const unsigned long baud) {
    SSPCON = 0x28; // Enable I2C master mode, clock = FOSC / (4 * (SSPADD + 1))
    SSPCON2 = 0x00; // Clear SSPCON2 register to reset control bits
    SSPADD = (_XTAL_FREQ / (4 * baud)) - 1; // Set baud rate for I2C communication
    SSPSTAT = 0x00; // Set SMP (Slew Rate Control) for standard speed
    TRISC = 0x18; // Set RC3 (SCL) and RC4 (SDA) as inputs
}

// Wait until the I2C bus is idle

void I2C_Master_Wait() {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); // Wait until I2C operations are complete
}

// Send I2C start condition

void I2C_Master_Start() {
    I2C_Master_Wait(); // Wait for idle bus
    SSPCON2 = 0x01; // Set SEN (Start Enable) bit to initiate start condition
}

// Send I2C repeated start condition

void I2C_Master_RepeatedStart() {
    I2C_Master_Wait(); // Wait for idle bus
    SSPCON2 = 0x02; // Set RSEN (Repeated Start Enable) bit
}

// Send I2C stop condition

void I2C_Master_Stop() {
    I2C_Master_Wait(); // Wait for idle bus
    SSPCON2 = 0x04; // Set PEN (Stop Enable) bit to end communication
}

// Write a byte of data over I2C

unsigned char I2C_Master_Write(unsigned char data) {
    I2C_Master_Wait(); // Wait for idle bus
    SSPBUF = data; // Load data into SSPBUF to send it
    while (!SSPIF); // Wait until data transfer is complete
    SSPIF = 0; // Clear SSPIF (interrupt flag)
    return ACKSTAT; // Return acknowledgment status (0 = ACK, 1 = NACK)
}

// Read a byte of data over I2C

unsigned char I2C_Read_Byte(void) {
    I2C_Master_Wait(); // Wait for idle bus
    SSPCON2 = 0x08; // Set RCEN (Receive Enable) bit to receive byte
    while (!SSPIF); // Wait until reception is complete
    SSPIF = 0; // Clear SSPIF (interrupt flag)
    I2C_Master_Wait(); // Wait for idle bus
    return SSPBUF; // Return received byte from SSPBUF
}

// Send an Acknowledge signal

void I2C_ACK(void) {
    ACKDT = 0; // Set ACKDT (Acknowledge Data) bit to 0 (ACK)
    I2C_Master_Wait(); // Wait for idle bus
    ACKEN = 1; // Set ACKEN (Acknowledge Sequence Enable) bit to send ACK
}

// Send a Not-Acknowledge (NACK) signal

void I2C_NACK(void) {
    ACKDT = 1; // Set ACKDT bit to 1 (NACK)
    I2C_Master_Wait(); // Wait for idle bus
    ACKEN = 1; // Set ACKEN bit to send NACK
}

// Write data byte to EEPROM at specified address

void EEPROM_Write(unsigned int add, unsigned char data) {
    I2C_Master_Start(); // Send I2C start condition
    while (I2C_Master_Write(EEPROM_Address_W)) // Send EEPROM write address; repeat start if ACK not received
        I2C_Master_RepeatedStart();
    I2C_Master_Write(add >> 8); // Send high byte of address
    I2C_Master_Write((unsigned char) add); // Send low byte of address
    I2C_Master_Write(data); // Write data byte to EEPROM
    I2C_Master_Stop(); // Send I2C stop condition
}

// Read data byte from EEPROM at specified address

unsigned char EEPROM_Read(unsigned int add) {
    unsigned char Data;
    I2C_Master_Start(); // Send I2C start condition
    while (I2C_Master_Write(EEPROM_Address_W)) // Send EEPROM write address for setting read address; repeat if no ACK
        I2C_Master_RepeatedStart();
    I2C_Master_Write(add >> 8); // Send high byte of address
    I2C_Master_Write((unsigned char) add); // Send low byte of address
    I2C_Master_RepeatedStart(); // Send repeated start to begin read
    I2C_Master_Write(EEPROM_Address_R); // Send EEPROM read address
    Data = I2C_Read_Byte(); // Read data byte from EEPROM
    I2C_NACK(); // Send NACK to end read
    I2C_Master_Stop(); // Send I2C stop condition
    return Data; // Return data byte
}



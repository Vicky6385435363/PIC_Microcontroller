// CONFIGURATION BITS
#pragma config FOSC = EXTRC     // Use external RC oscillator
#pragma config WDTE = OFF       // Disable Watchdog Timer
#pragma config PWRTE = OFF      // Disable Power-up Timer
#pragma config BOREN = OFF      // Disable Brown-out Reset
#pragma config LVP = OFF        // Disable Low-Voltage ICSP
#pragma config CPD = OFF        // Disable Data EEPROM memory code protection
#pragma config WRT = OFF        // Disable Flash program memory write protection
#pragma config CP = OFF         // Disable Flash program memory code protection

// Include necessary libraries
#include <xc.h>
#include <stdint.h>

// Define the oscillator frequency for delay
#define _XTAL_FREQ 4000000  

// IO Pin Definitions for Push Buttons
#define UP RB0                 // Button to increment data
#define Down RB1               // Button to decrement data
#define Slave1 RB2 
#define Slave2 RB3 
#define Slave3 RB4 
#define Slave4 RB5 // Button to send data via SPI

// Function Prototypes
void SPI_Master_Init(); // Function to initialize SPI in Master mode
void SPI_Write(uint8_t); // Function to write data to SPI

// Global variable to hold the data value
uint8_t Data = 0;

// Main Function

void main(void) {
    //--[ Configure Peripherals and IO Pins ]--
    SPI_Master_Init(); // Initialize SPI in Master mode
    TRISB = 0x1F; // Set RB0, RB1, RB2 as inputs for buttons
    TRISD = 0x00; // Set PORTD as output to display data
    PORTB = 0xE0; // Initialize PORTB to 0
    PORTD = 0x00; // Initialize PORTD to 0

    // Infinite loop for the main program logic
    while (1) {
        if (UP) // If UP button is pressed
        {
            Data++; // Increment the data value
            __delay_ms(250); // Add debounce delay for button press
        }

        if (Down) // If Down button is pressed
        {
            Data--; // Decrement the data value
            __delay_ms(250); // Add debounce delay for button press
        }

        if (Slave1) // If Send button is pressed
        {
            PORTB &= 0x7F;
            SPI_Write(Data);
             // Send the current data value via SPI
            __delay_ms(250);
            PORTB |= 0x80; // Add debounce delay for button press
        }
        if (Slave2) // If Send button is pressed
        {
             PORTB &= 0xBF;
            SPI_Write(Data);
            // Send the current data value via SPI
            __delay_ms(250);
            PORTB |= 0x40; // Add debounce delay for button press
        }
        if (Slave3) // If Send button is pressed
        {
            PORTB &= 0xDF;
            SPI_Write(Data);
             // Send the current data value via SPI
            __delay_ms(250);
            PORTB |= 0x20; // Add debounce delay for button press
        }
//        if (Slave4) // If Send button is pressed
//        {
//            SPI_Write(Data);
//            PORTB &= 0xFD; // Send the current data value via SPI
//            __delay_ms(250);
//            PORTB |= 0x20; // Add debounce delay for button press
//        }

        PORTD = Data; // Display the current data value on PORTD
    }

    return; // Program should never reach here
}

// Function to initialize SPI in Master mode

void SPI_Master_Init() {
    SSPCON = 0x20; // Configure SPI as Master, SCK = Fosc/4
    SSPSTAT = 0x00; // Clear the SSPSTAT register
    TRISC = 0x10; // Set SDO as output, SCK as output, and SDI as input
}

// Function to write data to SPI

void SPI_Write(uint8_t Data) {
    SSPBUF = Data; // Load data into the SSPBUF register to transmit
}

#include <xc.h>
#include "I2C_EEPROM.h"
#define _XTAL_FREQ 16000000
#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0

void I2C_Master_init(const unsigned long baud) {
    SSPCON = 0x28;
    SSPCON2 = 0;
    SSPADD(_XTAL_FREQ / (4 * baud)) - 1;
    SSPSTAT = 0;
    TRISC3 = 1;
    TRISC4 = 1;

}

void I2C_Master_Wait() {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_RepeatedStart(){
    I2C_Master_Wait();
    RSEN=1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN=1;
}

unsigned char I2C_Master_Write(unsigned char data){
    I2C_Master_Wait();
    SSPBUF=data;
    while(!SSPIF);
    SSPIF=0;
    return ACKSTAT;
}

unsigned char I2C_Read_Byte(void){
    I2C_Master_Wait();
    RCEN=1;
    while(!SSPIF);
    SSPIF=0;
    I2C_Master_Wait();
    
}

void I2C_ACK(void){
    ACKDT=0;
    I2C_Master_Wait();
    ACKEN=1;
}

void I2C_NACK(void){
    ACKDT=1;
    I2C_Master_Wait();
    ACKEN=1;
}

void EEPROM_Write(unsigned char add,unsigned char data)
{
    I2C_Master_Start();
    while(I2C_Master_Write(EEPROM_Address_W))
        I2C_Master_RepeatedStart();
    I2C_Master_Write(add>>8);
    I2C_Master_Write((unsigned char)add);
    I2C_Master_Write(data);
    I2C_Master_Stop();
}

void EEPROM_Write_Page(unsigned in add,unsigned char* data,unsigned char len){
    I2C_Master_Start();
    
}
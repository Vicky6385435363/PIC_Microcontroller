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

void initiate(void); //initiate function was declared 
void lcd_data(unsigned char); // lcd_data function is declared as unsigned char datatype
void lcd_command(unsigned char); //lcd_command function is declared as unsigned char datatype
void lcd_out(unsigned int); //lcd_out function declared as int datatype because the number may be positive or negative
unsigned char j,k[6],plus,minus,equal; //parameters are declared as unsigned char datatype
unsigned int num1,num2,n,m; //parameters are declared as unsigned char datatype
int sub; //sum is declared as int datatype because the output may be positive or negative

void main() { //defining main function
initiate(); //declaring initiate funtion 
num1=100; //declare first number num1=100
num2=545; //declare second number num2=545
plus='+'; //declare plus symbol
equal='='; //declare equal to symbol
minus='-'; //declare minus symbol
lcd_command(0x80); //initial position of the lcd display
lcd_out(num1); //call lcd_out function to process num1
lcd_data(minus); //declare minus symbol
lcd_out(num2); //call lcd_out function to process num2
lcd_data(equal); //declare equal to symbol
sub=num1-num2; //compute sub=num1-num2
if(sub<0){
    lcd_data(minus);//if the sub is negative then minus symbol is printed
    sub=-sub; //the negative value of sub is converted to positive value as the lcd_out function cannot process negative values
}
else{
    lcd_data(plus); //else the plus symbol will be printed
    sub=sub; //sub is positive so it is declared as positive value
}
lcd_out(sub);//call lcd_out function process sum
while(1); //used to process the loop continuously in the main function
}

void initiate(){ // Defining initiate function
    TRISC = 0x00; // Initial setting the PORTC pins as output 0000 0000
    TRISD = 0x00; // Initial setting the PORTC pins as output 0000 0000
    lcd_command(0x33); // Function set command for 8-bit  N=1 for 2-line display and F=0 for 5x7 dot matrix 0011 1000
    __delay_ms(100); // 100ms delay given so that no data transferred during this time
    lcd_command(0x34); // Function set command for 8-bit  N=1 for 2-line display and F=0 for 5x7 dot matrix 0011 1000
    __delay_ms(100); // 100ms delay given so that no data transferred during this time
    lcd_command(0x35); // Function set command for 8-bit  N=1 for 2-line display and F=0 for 5x7 dot matrix 0011 1000
    __delay_ms(100); // 100ms delay given so that no data transferred during this time
    lcd_command(0x38); // Function set command for 8-bit  N=1 for 2-line display and F=0 for 5x7 dot matrix 0011 1000
    __delay_ms(100); // 100ms delay given so that no data transferred during this time
    lcd_command(0x0C); // stops the cursor
    __delay_ms(100); // 100ms delay
    lcd_command(0x01); // clear command
    __delay_ms(100); // 100ms delay
}

void lcd_out(unsigned int i){ //defining lcd_out function
    unsigned char s,j=1; //Declaration of unsigned char s and j=1
    m=i; //Assign m=i
    while(m!=0){ //while condition of m!=0 which means the while loop perform the operation until the value of m tends to 0
        s=m-((m/10)*10); //compute s=m-((m/10)*10) arithmetic operation
        k[j]=s; //assigning position k[j]=s
        j++; //increment j
        m=m/10; //then m=m/10 then perform the operation
    }
    k[j]='\0'; //initially assign k[j]=0
    j=j-1; //decrement j by 1
    while(j!=0){ //while condition was performed until j equal to 0
        n=0x30+k[j]; //ASCII conversion using the given formula
        lcd_data(n); //lcd_data function is called to load the data on the display
        j--; //decrement j and perform the same operation until j becomes 0
    }
    }
void lcd_data(unsigned char i) { // Defining lcd_Data function
    PORTC |= 0x08; // set RS as 1 at RC3 pin for sending data
    PORTD = i; // PORTD is set with a parameter i
    PORTC |= 0x01; // Enable is ON
    PORTC &= ~0x01; // Enable is OFF
    __delay_ms(100); // 100ms delay
}

void lcd_command(unsigned char i) { // Defining lcd_Command function
    PORTC &= ~0x08; // set RS as 0 at RC3 pin for sending command
    PORTD = i; // PORTD is set with a parameter i
    PORTC |= 0x01; // Enable is ON
    PORTC &= ~0x01; // Enable is OFF
    __delay_ms(100); // 100ms delay
}



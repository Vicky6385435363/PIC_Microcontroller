#include <xc.h>
#include "led_header.h"
#define _XTAL_FREQ 6000000

void main(void) {
    led();
    while (1) {
        led_on();
        __delay_ms(3000);
        led_off();
        __delay_ms(3000);
    }
}

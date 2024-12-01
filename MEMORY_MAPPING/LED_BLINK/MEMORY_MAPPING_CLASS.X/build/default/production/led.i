# 1 "led.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "led.c" 2
unsigned char *ipop_select = (unsigned char*) 0x87;
unsigned char *ipop_decide = (unsigned char*) 0x07;

void led(void) {
    *ipop_select = 0x00;
}

void led_on(void) {
    *ipop_decide = 0x20;
}

void led_off(void) {
    *ipop_decide = 0x00;
}

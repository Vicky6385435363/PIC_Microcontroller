# 1 "led_switch.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "led_switch.c" 2
unsigned char *ipop_select = (unsigned char*) 0x87;
unsigned char *ipop_decide = (unsigned char*) 0x07;
unsigned char *switch_led = (unsigned char*) 0x86;
unsigned char *switchled = (unsigned char*) 0x06;
unsigned char *option_reg = (unsigned char*) 0x81;
void led() {
    *ipop_select = 0x00;
    *ipop_decide = 0xFC;
    *switch_led = 0xF0;
    *switchled = 0xF0;
    *option_reg &= 0x7F;
}
void l_switch() {
    unsigned char value;
    value = *switchled;
    switch (value) {
        case 0xE0:
            *ipop_decide = 0x01;
            break;
        case 0xD0:
            *ipop_decide = 0x02;
            break;
        case 0xB0:
            *ipop_decide = 0x03;
            break;
        case 0x70:
            *ipop_decide = 0x00;
            break;
        default:
            *ipop_decide = 0x00;
            break;
    }
}

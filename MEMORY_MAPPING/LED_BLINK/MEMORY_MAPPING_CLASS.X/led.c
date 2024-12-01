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


#include "rc.h"

static int16_t ch[8];

void rcInit() {
    uartInitMBUS();
}

void rcUpdate() {
    mbusRead(ch);
}

int16_t rcGet(uint8_t c) {
    return ch[c];
}

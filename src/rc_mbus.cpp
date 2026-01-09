#include "rc_mbus.h"

static mbus_t mbus;

void mbus_init(void) {
    for (int i = 0; i < MBUS_CHANNELS; i++) {
        mbus.ch[i] = 1500;
    }
    mbus.failsafe = false;
    mbus.frame_lost = false;
}

void mbus_update(void) {
    // TODO: decode MBUS/iBUS/SBUS thật
}

uint16_t mbus_get_channel(uint8_t ch) {
    if (ch >= MBUS_CHANNELS) return 1500;
    return mbus.ch[ch];
}

bool mbus_failsafe(void) {
    return mbus.failsafe;
}

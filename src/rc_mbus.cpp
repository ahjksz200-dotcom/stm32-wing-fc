#include "rc_mbus.h"

static mbus_t mbus;

void MBUS_Init(void)
{
    for (int i = 0; i < MBUS_CHANNELS; i++) {
        mbus.ch[i] = 1500;
    }
    mbus.failsafe = false;
}

uint8_t MBUS_ReadRaw(uint16_t *channels)
{
    // TODO: đọc UART SBUS / iBUS / CRSF sau
    // TẠM THỜI: giả lập để build FC

    for (int i = 0; i < MBUS_CHANNELS; i++) {
        channels[i] = mbus.ch[i];
    }

    return mbus.failsafe ? 0 : 1;
}

bool MBUS_Failsafe(void)
{
    return mbus.failsafe;
}

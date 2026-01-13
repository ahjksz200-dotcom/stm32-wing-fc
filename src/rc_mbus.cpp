#include "rc_mbus.h"
#include <string.h>

/* ================= LOCAL ================= */

static mbus_t mbus;

/* ================= API ================= */

void MBUS_Init(void)
{
    /* giá trị an toàn khi boot */
    for (int i = 0; i < MBUS_CHANNELS; i++)
        mbus.ch[i] = 1500;

    mbus.ch[2] = 1000;   // throttle
    mbus.failsafe = false;
}

/* Fake MBUS data để test FC */
uint8_t MBUS_ReadRaw(uint16_t *channels)
{
    memcpy(channels, mbus.ch, sizeof(uint16_t) * MBUS_CHANNELS);
    return 1;   // luôn coi như có tín hiệu
}

bool MBUS_Failsafe(void)
{
    return false;
}

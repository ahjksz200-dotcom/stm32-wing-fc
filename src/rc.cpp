#include "rc.h"
#include "rc_mbus.h"

void RC_Init(void)
{
    MBUS_Init();
}

uint8_t RC_Read(rc_data_t *rc)
{
    uint16_t ch[MBUS_CHANNELS];

    if (!MBUS_ReadRaw(ch))
        return 0;

    /* Map chuẩn RC */
    rc->roll     = ch[0];
    rc->pitch    = ch[1];
    rc->throttle = ch[2];
    rc->yaw      = ch[3];

    rc->arm = (ch[4] > 1500);  // AUX1

    return 1;
}

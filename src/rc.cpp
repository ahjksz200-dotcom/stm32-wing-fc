#include "rc.h"
#include "rc_mbus.h"

uint8_t RC_Read(rc_data_t *out)
{
    uint16_t ch[8];

    if (!MBUS_ReadRaw(ch))
        return 0;

    out->roll     = ch[0] - 1500;
    out->pitch    = ch[1] - 1500;
    out->yaw      = ch[2] - 1500;
    out->throttle = ch[3];
    out->arm      = (ch[4] > 1500);
    out->mode     = (ch[5] - 1000) / 500;

    return 1;
}

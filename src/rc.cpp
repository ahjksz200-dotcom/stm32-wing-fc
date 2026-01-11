#include "rc.h"
#include "rc_mbus.h"

void RC_Init(void)
{
    MBUS_Init();
}

uint8_t RC_Read(rc_data_t *out)
{
    uint16_t ch[MBUS_CHANNELS];

    if (!MBUS_ReadRaw(ch)) {
        return 0;
    }

    out->roll     = (int16_t)ch[0] - 1500;
    out->pitch    = (int16_t)ch[1] - 1500;
    out->yaw      = (int16_t)ch[2] - 1500;
    out->throttle = ch[3];

    out->arm = (ch[4] > 1500);

    return 1;
}

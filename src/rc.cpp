#include "rc.h"

void RC_Init(void)
{
    /* chưa làm gì – để build */
}

uint8_t RC_Read(rc_data_t *rc)
{
    /* giá trị giả để test FC */
    rc->throttle = 1000;
    rc->roll     = 1500;
    rc->pitch    = 1500;
    rc->yaw      = 1500;
    rc->arm      = 0;

    return 1; // RC OK
}

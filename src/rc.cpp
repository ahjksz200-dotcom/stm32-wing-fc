#include "rc.h"

void RC_Init(void) {}

bool RC_Read(rc_input_t *rc) {
    rc->roll = 0;
    rc->pitch = 0;
    rc->yaw = 0;
    rc->throttle = 0;
    rc->failsafe = false;
    return true;
}

#include "failsafe.h"

static failsafe_state_t fs;

void Failsafe_Init(void)
{
    fs.rc_lost  = false;
    fs.gps_lost = false;
    fs.active   = false;
}

void Failsafe_Update(bool rc_ok, bool gps_ok)
{
    fs.rc_lost  = !rc_ok;
    fs.gps_lost = !gps_ok;

    // failsafe kích hoạt nếu mất RC
    fs.active = fs.rc_lost;
}

failsafe_state_t Failsafe_GetState(void)
{
    return fs;
}

#include "failsafe.h"

static uint8_t fs_active = 0;

void failsafe_trigger(void)
{
    fs_active = 1;
}

uint8_t failsafe_active(void)
{
    return fs_active;
}

void failsafe_clear(void)
{
    fs_active = 0;
}

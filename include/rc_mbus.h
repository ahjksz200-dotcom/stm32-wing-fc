#pragma once
#include "stm32f4xx_hal.h"
#include <stdbool.h>

typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t throttle;
    bool arm;
} rc_data_t;

bool RC_Read(rc_data_t *rc);

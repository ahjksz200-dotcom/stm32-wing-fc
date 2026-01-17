#pragma once
#include <stdint.h>

typedef struct
{
    uint16_t roll;
    uint16_t pitch;
    uint16_t yaw;
    uint16_t throttle;
    uint8_t arm;
} rc_data_t;

void RC_Init(void);
uint8_t RC_Read(rc_data_t *rc);

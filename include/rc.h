#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    float roll;
    float pitch;
    float yaw;
    float throttle;
    bool  failsafe;
} rc_input_t;

void RC_Init(void);
bool RC_Read(rc_input_t *rc);

#pragma once
#include <stdint.h>
#include <stdbool.h>

/* ===== RC CONFIG ===== */
#define RC_CHANNELS 14

typedef struct
{
    uint16_t ch[RC_CHANNELS];

    uint16_t roll;
    uint16_t pitch;
    uint16_t yaw;
    uint16_t throttle;

} rc_data_t;

/* ===== API ===== */
void RC_Init(void);
bool RC_Read(rc_data_t *rc);

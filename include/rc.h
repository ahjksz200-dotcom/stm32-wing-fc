#pragma once
#include <stdint.h>

/* RC channel data (chuẩn FC) */
typedef struct
{
    uint16_t roll;
    uint16_t pitch;
    uint16_t yaw;
    uint16_t throttle;
    uint16_t aux1;
    uint16_t aux2;
    uint8_t  arm;
} rc_data_t;

/* API */
void RC_Init(void);
uint8_t RC_Read(rc_data_t *out);

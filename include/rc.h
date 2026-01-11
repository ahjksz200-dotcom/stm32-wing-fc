#pragma once
#include <stdint.h>

typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    uint16_t throttle;
    uint8_t arm;
} rc_data_t;

#ifdef __cplusplus
extern "C" {
#endif

void RC_Init(void);
uint8_t RC_Read(rc_data_t *out);

#ifdef __cplusplus
}
#endif

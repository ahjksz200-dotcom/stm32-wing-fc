#pragma once
#include <stdint.h>

typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int16_t throttle;
    uint8_t arm;
    uint8_t mode;
} rc_data_t;

#ifdef __cplusplus
extern "C" {
#endif

uint8_t RC_Read(rc_data_t *out);
void RC_Init(void);

#ifdef __cplusplus
}
#endif

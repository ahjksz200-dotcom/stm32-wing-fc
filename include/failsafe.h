#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// trạng thái failsafe
typedef struct {
    bool rc_lost;
    bool gps_lost;
    bool active;
} failsafe_state_t;

// API
void Failsafe_Init(void);
void Failsafe_Update(bool rc_ok, bool gps_ok);
failsafe_state_t Failsafe_GetState(void);

#ifdef __cplusplus
}
#endif

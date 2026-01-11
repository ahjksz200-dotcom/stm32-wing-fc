#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "imu.h"
#include "rc.h"

/* ===== PID OUTPUT ===== */
typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} pid_output_t;

/* ===== PID API ===== */
void PID_Update(const imu_data_t *imu,
                const rc_data_t  *rc,
                pid_output_t     *out);

#ifdef __cplusplus
}
#endif

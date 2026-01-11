#pragma once

#include "imu.h"
#include "rc.h"      // <-- THIẾU DÒNG NÀY

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} pid_output_t;

void PID_Update(const imu_data_t *imu,
                const rc_data_t  *rc,
                pid_output_t     *out);

#ifdef __cplusplus
}
#endif

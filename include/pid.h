#pragma once
#include <stdint.h>
#include "imu.h"
#include "rc.h"

typedef struct {
    float roll;
    float pitch;
    float yaw;
} pid_output_t;

void PID_Update(
    const imu_data_t *imu,
    const rc_data_t  *rc,
    pid_output_t     *out
);

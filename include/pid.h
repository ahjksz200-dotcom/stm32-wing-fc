#pragma once
#include "imu.h"
#include "rc_mbus.h"

typedef struct {
    int16_t roll;
    int16_t pitch;
} pid_output_t;

void PID_Init(void);
void PID_Update(const imu_data_t *imu,
                const rc_data_t *rc,
                pid_output_t *out);

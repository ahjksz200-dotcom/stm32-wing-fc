#pragma once
#include "stm32f4xx_hal.h"

typedef struct {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
} imu_data_t;

void IMU_Init(void);
void IMU_Read(imu_data_t *imu);

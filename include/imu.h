#pragma once
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;

    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;
} imu_data_t;

/* API */
void IMU_Init(void);
void IMU_Update(imu_data_t *imu);

#ifdef __cplusplus
}
#endif

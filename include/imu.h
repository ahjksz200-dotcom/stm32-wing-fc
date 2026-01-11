#pragma once
#include <stdint.h>

typedef struct {
    float roll;
    float pitch;
    float yaw;

    float gyro_x;
    float gyro_y;
    float gyro_z;

    float acc_x;
    float acc_y;
    float acc_z;
} imu_data_t;

#ifdef __cplusplus
extern "C" {
#endif

void IMU_Init(void);
void IMU_Update(imu_data_t *imu);

#ifdef __cplusplus
}
#endif

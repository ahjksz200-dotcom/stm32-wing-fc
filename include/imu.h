#pragma once

typedef struct {
    float gyro_x;
    float gyro_y;
    float gyro_z;
} imu_data_t;

void IMU_Init(void);
void IMU_Update(imu_data_t *imu);

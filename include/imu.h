#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* RAW SENSOR */
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;

    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;

    /* ATTITUDE (deg * 100) */
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} imu_data_t;

void IMU_Init(void);
void IMU_Update(imu_data_t *imu);

#ifdef __cplusplus
}
#endif

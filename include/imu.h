#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* IMU raw data */
typedef struct {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
} imu_raw_t;

/* IMU processed data (SI units) */
typedef struct {
    float ax, ay, az;   // m/s^2
    float gx, gy, gz;   // rad/s
} imu_data_t;

/* API */
bool IMU_Init(void);
void IMU_ReadRaw(imu_raw_t *raw);
void IMU_Read(imu_data_t *data);
void IMU_Calibrate(void);

#ifdef __cplusplus
}
#endif

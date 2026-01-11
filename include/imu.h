#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} imu_data_t;

void IMU_Init(void);
void IMU_Update(imu_data_t *imu);

#ifdef __cplusplus
}
#endif

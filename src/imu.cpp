#include "imu.h"

void IMU_Init(void) {}

void IMU_Update(imu_data_t *imu) {
    imu->gyro_x = 0;
    imu->gyro_y = 0;
    imu->gyro_z = 0;
}

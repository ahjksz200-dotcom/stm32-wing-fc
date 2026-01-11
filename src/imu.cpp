#include "imu.h"

void IMU_Init(void)
{
    // TODO: init MPU6500 (I2C/SPI)
}

void IMU_Update(imu_data_t *imu)
{
    // TẠM THỜI MOCK DATA – build pass trước
    imu->gyro_x = 0;
    imu->gyro_y = 0;
    imu->gyro_z = 0;

    imu->acc_x = 0;
    imu->acc_y = 0;
    imu->acc_z = 16384; // ~1G
}

#include "imu.h"

void IMU_Init(void)
{
    // TODO: init I2C/SPI + MPU6500
}

void IMU_Update(imu_data_t *imu)
{
    /* Fake data for now */
    imu->gyro_x = 0;
    imu->gyro_y = 0;
    imu->gyro_z = 0;

    imu->acc_x = 0;
    imu->acc_y = 0;
    imu->acc_z = 16384; // 1G

    imu->roll  = 0;
    imu->pitch = 0;
    imu->yaw   = 0;
}

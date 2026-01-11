#include "imu.h"

void IMU_Init(void)
{
    // TODO: init MPU6500
}

void IMU_Update(imu_data_t *imu)
{
    // TẠM THỜI: giả lập để build & test FC loop
    imu->gyro_x = 0;
    imu->gyro_y = 0;
    imu->gyro_z = 0;

    imu->acc_x = 0;
    imu->acc_y = 0;
    imu->acc_z = 1.0f;

    imu->roll  = 0.0f;
    imu->pitch = 0.0f;
    imu->yaw   = 0.0f;
}

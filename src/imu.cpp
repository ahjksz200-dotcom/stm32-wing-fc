#include "imu.h"
#include "i2c.h"

static float ax, ay, az;
static float gx, gy, gz;

void imuInit() {
    MPU6500_Init();
}

void imuUpdate() {
    int16_t raw_ax, raw_ay, raw_az;
    int16_t raw_gx, raw_gy, raw_gz;

    MPU6500_ReadRaw(&raw_ax,&raw_ay,&raw_az,&raw_gx,&raw_gy,&raw_gz);

    ax = raw_ax * 0.000488f;
    ay = raw_ay * 0.000488f;
    az = raw_az * 0.000488f;

    gx = raw_gx * 0.061f;
    gy = raw_gy * 0.061f;
    gz = raw_gz * 0.061f;
}

void imuGet(float* acc, float* gyro) {
    acc[0]=ax; acc[1]=ay; acc[2]=az;
    gyro[0]=gx; gyro[1]=gy; gyro[2]=gz;
}

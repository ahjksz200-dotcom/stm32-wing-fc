#include "ekf.h"

static float roll, pitch, yaw;

void ekfInit() {
    roll = pitch = yaw = 0;
}

void ekfUpdate() {
    float acc[3], gyro[3];
    imuGet(acc, gyro);

    float dt = 0.001f;

    roll  += gyro[0]*dt;
    pitch += gyro[1]*dt;
    yaw   += gyro[2]*dt;

    // correction nhẹ bằng acc
    roll  = roll  * 0.99f + atan2(acc[1], acc[2]) * 0.57f;
    pitch = pitch * 0.99f + atan2(-acc[0], acc[2]) * 0.57f;
}

void ekfGetAttitude(float* r, float* p, float* y) {
    *r=roll; *p=pitch; *y=yaw;
}

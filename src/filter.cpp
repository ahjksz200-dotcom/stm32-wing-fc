#include "filter.h"
#include <math.h>

static float roll, pitch;

void filterUpdate(float* acc, float* gyro, float dt) {
    float accRoll  = atan2(acc[1], acc[2]) * 57.3f;
    float accPitch = atan2(-acc[0], sqrt(acc[1]*acc[1]+acc[2]*acc[2])) * 57.3f;

    roll  = 0.98f * (roll  + gyro[0]*dt) + 0.02f * accRoll;
    pitch = 0.98f * (pitch + gyro[1]*dt) + 0.02f * accPitch;
}

void filterGet(float* r, float* p) {
    *r = roll;
    *p = pitch;
}

#include "ekf.h"

static ekf_state_t ekf;

void EKF_Init(void)
{
    ekf.roll  = 0.0f;
    ekf.pitch = 0.0f;
    ekf.yaw   = 0.0f;
}

void EKF_Update(float gx, float gy, float gz,
                float ax, float ay, float az,
                float dt)
{
    // EKF placeholder → gyro integrate
    ekf.roll  += gx * dt;
    ekf.pitch += gy * dt;
    ekf.yaw   += gz * dt;
}

ekf_state_t EKF_GetState(void)
{
    return ekf;
}

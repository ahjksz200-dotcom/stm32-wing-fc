#include "pid.h"

static float kp = 1.0f;
static float ki = 0.0f;
static float kd = 0.0f;

void PID_Update(const imu_data_t *imu,
                const rc_data_t  *rc,
                pid_output_t     *out)
{
    out->roll  = kp * (rc->roll  - imu->roll);
    out->pitch = kp * (rc->pitch - imu->pitch);
    out->yaw   = kp * (rc->yaw   - imu->yaw);
}

#include "pid.h"

void PID_Update(const imu_data_t *imu,
                const rc_data_t  *rc,
                pid_output_t     *out)
{
    out->roll  = rc->roll  - imu->roll;
    out->pitch = rc->pitch - imu->pitch;
    out->yaw   = 0;
}

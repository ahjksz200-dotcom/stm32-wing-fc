#include "fc.h"
#include "imu.h"
#include "pid.h"
#include "rc_mbus.h"
#include "pwm.h"
#include "failsafe.h"
#include "mixer.h"

static imu_data_t imu;
static rc_data_t rc;
static pid_output_t pid_out;

static uint8_t armed = 0;

void FC_Init(void)
{
    IMU_Init();
    PWM_Init();
    RC_Init();
}

void FC_Loop(void)
{
    if (!RC_Read(&rc)) {
        failsafe_trigger();
        return;
    }

    if (failsafe_active()) {
        PWM_DisarmESC();
        armed = 0;
        return;
    }

    IMU_Update(&imu);

    PID_Update(&imu, &rc, &pid_out);

    if (rc.arm && !armed) {
        PWM_ArmESC();
        armed = 1;
    }

    if (!rc.arm && armed) {
        PWM_DisarmESC();
        armed = 0;
    }

    if (armed) {
        mixer_elevon(&pid_out, rc.throttle);
    }
}

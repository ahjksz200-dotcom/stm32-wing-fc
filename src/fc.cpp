#include "fc.h"

#include "rc_mbus.h"
#include "imu.h"
#include "pid.h"
#include "pwm.h"
#include "failsafe.h"
#include "mixer.h"

static uint8_t armed = 0;

void FC_Init(void)
{
    RC_Init();
    IMU_Init();
    PID_Init();
    PWM_Init();
}

void FC_Loop(void)
{
    rc_data_t rc;

    if (!RC_Read(&rc)) {
        failsafe_trigger();
        return;
    }

    if (failsafe_active()) {
        PWM_DisarmESC();
        armed = 0;
        return;
    }

    if (rc.arm && !armed) {
        PWM_ArmESC();
        armed = 1;
    }

    if (!rc.arm && armed) {
        PWM_DisarmESC();
        armed = 0;
    }

    if (!armed) return;

    IMU_Update();
    PID_Update(rc.roll, rc.pitch);

    mix_elevon(rc.roll, rc.pitch);
}

#include "fc.h"
#include "imu.h"
#include "pid.h"
#include "rc_mbus.h"
#include "mixer.h"
#include "pwm.h"
#include "failsafe.h"

void FC_Init(void)
{
    HAL_Init();

    PWM_Init();
    IMU_Init();
    RC_MBUS_Init();
    PID_Init();
}

void FC_Loop(void)
{
    IMU_Update();        // EKF bên trong
    RC_MBUS_Update();    // đọc RX

    if (Failsafe_Check())
    {
        Failsafe_Execute();
        return;
    }

    PID_Update();
    Mixer_Elevon();
    PWM_Update();
}

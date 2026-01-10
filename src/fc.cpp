#include "fc.h"

#include "rc_mbus.h"
#include "failsafe.h"
#include "imu.h"
#include "pid.h"
#include "pwm.h"

/* ===== INTERNAL STATE ===== */
static bool armed = false;

/* ===== MIXER ===== */
static void mix_elevon(int16_t roll, int16_t pitch)
{
    int16_t left  = PWM_MID_US + pitch + roll;
    int16_t right = PWM_MID_US + pitch - roll;

    PWM_SetMicroseconds(PWM_CH2, left);
    PWM_SetMicroseconds(PWM_CH3, right);
}

/* ===== INIT ===== */
void FC_Init(void)
{
    IMU_Init();
    PID_Init();
    PWM_Init();
    PWM_DisarmESC();
}

/* ===== MAIN LOOP ===== */
void FC_Loop(void)
{
    rc_data_t rc;

    if (!RC_Read(&rc)) {
        failsafe_trigger();
        return;
    }

    if (failsafe_active()) {
        PWM_DisarmESC();
        armed = false;
        return;
    }

    if (rc.arm && !armed) {
        PWM_ArmESC();
        armed = true;
    }

    if (!rc.arm && armed) {
        PWM_DisarmESC();
        armed = false;
    }

    if (!armed) return;

    imu_data_t imu;
    IMU_Read(&imu);

    pid_output_t pid;
    PID_Update(&imu, &rc, &pid);

    mix_elevon(pid.roll, pid.pitch);
    PWM_SetMicroseconds(PWM_CH1, rc.throttle);
}

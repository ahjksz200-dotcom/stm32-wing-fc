#include "fc.h"

#include "imu.h"
#include "pid.h"
#include "rc_mbus.h"
#include "pwm.h"
#include "failsafe.h"
#include "mixer.h"

#include <stdint.h>

/* ================== DATA ================== */

static imu_data_t imu;
static rc_data_t  rc;
static pid_output_t pid_out;

static uint8_t armed = 0;

/* ================== INIT ================== */

void FC_Init(void)
{
    /* IMU (có thể để trống) */
    IMU_Init();

    /* PWM TIMER THẬT */
    PWM_Init();
    PWM_DisarmESC();

    /* MBUS qua UART */
    RC_Init();

    /* Failsafe */
    failsafe_clear();
}

/* ================== LOOP ================== */

void FC_Loop(void)
{
    /* -------- RC (MBUS UART) -------- */
    if (!RC_Read(&rc))
    {
        /* Không có frame mới */
        failsafe_trigger();
    }

    if (failsafe_active())
    {
        PWM_DisarmESC();
        armed = 0;
        return;
    }

    /* -------- ARM / DISARM --------
       throttle < 1050
       yaw phải  -> ARM
       yaw trái  -> DISARM
    */
    if (rc.throttle < 1050)
    {
        if (rc.yaw > 1900 && !armed)
        {
            PWM_ArmESC();
            armed = 1;
        }
        else if (rc.yaw < 1100 && armed)
        {
            PWM_DisarmESC();
            armed = 0;
        }
    }

    /* -------- IMU -------- */
    IMU_Update(&imu);

    /* -------- PID -------- */
    PID_Update(&imu, &rc, &pid_out);

    /* -------- OUTPUT (PWM thật) -------- */
    if (armed)
    {
        mixer_elevon(&pid_out, rc.throttle);
    }
    else
    {
        PWM_Write(PWM_ESC, 1000);
        PWM_Write(PWM_SERVO_L, 1500);
        PWM_Write(PWM_SERVO_R, 1500);
    }
}

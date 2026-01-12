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
    IMU_Init();
    PWM_Init();

    PWM_DisarmESC();   // an toàn khi boot

    RC_Init();         // MBUS init
    failsafe_init();
}

/* ================== LOOP ================== */

void FC_Loop(void)
{
    /* -------- RC -------- */
    if (!RC_Read(&rc))
    {
        failsafe_trigger();
    }

    if (failsafe_active())
    {
        PWM_DisarmESC();
        armed = 0;
        return;
    }

    /* -------- ARM / DISARM --------
       Điều kiện chuẩn RC:
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

    /* -------- PID (hiện để pass-through) -------- */
    PID_Update(&imu, &rc, &pid_out);

    /* -------- OUTPUT -------- */
    if (armed)
    {
        mixer_elevon(&pid_out, rc.throttle);
    }
    else
    {
        /* disarmed → giữ ESC an toàn */
        PWM_Write(PWM_ESC, 1000);
        PWM_Write(PWM_SERVO_L, 1500);
        PWM_Write(PWM_SERVO_R, 1500);
    }
}

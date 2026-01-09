#include "fc.h"

/* Core modules */
#include "imu.h"
#include "pid.h"
#include "rc.h"
#include "mixer.h"
#include "failsafe.h"
#include "pwm.h"

/* ================== Local state ================== */

static imu_data_t imu;
static rc_input_t rc;

static float pid_roll  = 0.0f;
static float pid_pitch = 0.0f;
static float pid_yaw   = 0.0f;

/* loop timing (1kHz default) */
static uint32_t last_loop_us = 0;
#define FC_LOOP_US 1000   // 1 kHz

/* ================== Init ================== */

void FC_Init(void)
{
    IMU_Init();
    PID_Init();
    RC_Init();
    PWM_Init();
    FAILSAFE_Init();

    last_loop_us = 0;
}

/* ================== Main FC loop ================== */

void FC_Loop(void)
{
    uint32_t now = HAL_GetTick() * 1000; // us (coarse but OK now)
    if ((now - last_loop_us) < FC_LOOP_US) {
        return;
    }
    float dt = (now - last_loop_us) * 1e-6f;
    last_loop_us = now;

    /* -------- RC -------- */
    if (!RC_Read(&rc)) {
        FAILSAFE_Trigger();
    }

    if (FAILSAFE_IsActive() || rc.failsafe) {
        PWM_Disarm();
        return;
    }

    /* -------- IMU -------- */
    IMU_Update(&imu);

    /* -------- PID -------- */
    pid_roll = PID_Update(
        PID_ROLL,
        rc.roll,
        imu.gyro_x,
        dt
    );

    pid_pitch = PID_Update(
        PID_PITCH,
        rc.pitch,
        imu.gyro_y,
        dt
    );

    pid_yaw = PID_Update(
        PID_YAW,
        rc.yaw,
        imu.gyro_z,
        dt
    );

    /* -------- Mixer (Elevon) -------- */
    mixer_output_t mix;
    Mixer_Elevon(
        rc.throttle,
        pid_roll,
        pid_pitch,
        &mix
    );

    /* -------- Output -------- */
    PWM_SetThrottle(rc.throttle);
    PWM_SetServo(0, mix.left);   // Left elevon
    PWM_SetServo(1, mix.right);  // Right elevon
}

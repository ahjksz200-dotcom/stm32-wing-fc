#include "fc.h"

#include "imu.h"
#include "pid.h"
#include "rc_mbus.h"
#include "mixer.h"
#include "pwm.h"
#include "failsafe.h"

/* ===== LOOP TIMING ===== */
#define FC_LOOP_HZ     500
#define FC_DT          (1.0f / FC_LOOP_HZ)

/* ===== STATES ===== */
static uint32_t last_loop_us = 0;

/* ===== RC INPUT ===== */
static rc_input_t rc;

/* ===== IMU ===== */
static imu_data_t imu;

/* ===== PID OUTPUT ===== */
static float pid_roll  = 0.0f;
static float pid_pitch = 0.0f;
static float pid_yaw   = 0.0f;

void FC_Init(void)
{
    IMU_Init();
    PID_Init();
    RC_MBUS_Init();
    FAILSAFE_Init();

    last_loop_us = HAL_GetTick();
}

void FC_Loop(void)
{
    /* ===== FIXED LOOP RATE ===== */
    uint32_t now = HAL_GetTick();
    if ((now - last_loop_us) < (1000 / FC_LOOP_HZ)) {
        return;
    }
    last_loop_us = now;

    /* ===== READ RC ===== */
    if (!RC_MBUS_Read(&rc)) {
        FAILSAFE_Trigger();
    }

    /* ===== FAILSAFE ===== */
    if (FAILSAFE_IsActive()) {
        PWM_DisarmESC();
        return;
    }

    /* ===== READ IMU ===== */
    IMU_Update(&imu);

    /* ===== PID ===== */
    pid_roll  = PID_Update(PID_ROLL,
                           rc.roll,
                           imu.gyro_x,
                           FC_DT);

    pid_pitch = PID_Update(PID_PITCH,
                           rc.pitch,
                           imu.gyro_y,
                           FC_DT);

    pid_yaw   = PID_Update(PID_YAW,
                           rc.yaw,
                           imu.gyro_z,
                           FC_DT);

    /* ===== MIXER (ELEVON) ===== */
    mixer_output_t mix;
    Mixer_Elevon(rc.throttle,
                 pid_roll,
                 pid_pitch,
                 &mix);

    /* ===== PWM OUTPUT ===== */
    PWM_SetMicroseconds(PWM_CH1, mix.throttle);   // ESC
    PWM_SetMicroseconds(PWM_CH2, mix.left);       // Elevon L
    PWM_SetMicroseconds(PWM_CH3, mix.right);      // Elevon R
}

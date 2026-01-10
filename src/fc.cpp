#include "fc.h"
#include "pwm.h"
#include "rc_mbus.h"
#include "failsafe.h"
#include "filter.h"
#include "ekf.h"
#include <string.h>

/* ===== INTERNAL STATE ===== */
static bool armed = false;

/* ===== MIXER (WING) ===== */
typedef struct {
    int16_t left;
    int16_t right;
} mix_t;

static mix_t mix;

/* ===== SIMPLE MIXER ===== */
static void mix_elevon(int16_t roll, int16_t pitch)
{
    mix.left  = PWM_MID_US + pitch + roll;
    mix.right = PWM_MID_US + pitch - roll;

    if (mix.left < PWM_MIN_US)  mix.left = PWM_MIN_US;
    if (mix.left > PWM_MAX_US)  mix.left = PWM_MAX_US;
    if (mix.right < PWM_MIN_US) mix.right = PWM_MIN_US;
    if (mix.right > PWM_MAX_US) mix.right = PWM_MAX_US;
}

/* ===== FC INIT ===== */
void FC_Init(void)
{
    PWM_Init();
    PWM_DisarmESC();
    armed = false;
}

/* ===== FC LOOP ===== */
void FC_Loop(void)
{
    rc_data_t rc;

    /* ---- Read RC ---- */
    if (!RC_Read(&rc)) {
        failsafe_trigger();
    }

    /* ---- Failsafe ---- */
    if (failsafe_active()) {
        PWM_DisarmESC();
        armed = false;
        return;
    }

    /* ---- Arm logic ---- */
    if (rc.arm && !armed) {
        PWM_ArmESC();
        armed = true;
    }

    if (!rc.arm && armed) {
        PWM_DisarmESC();
        armed = false;
        return;
    }

    if (!armed) {
        PWM_DisarmESC();
        return;
    }

    /* ---- MIX ---- */
    mix_elevon(rc.roll, rc.pitch);

    /* ---- OUTPUT ---- */
    PWM_SetMicroseconds(PWM_CH1, rc.throttle); // ESC
    PWM_SetMicroseconds(PWM_CH2, mix.left);    // Elevon Left
    PWM_SetMicroseconds(PWM_CH3, mix.right);   // Elevon Right
}

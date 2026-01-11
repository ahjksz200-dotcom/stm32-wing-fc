#include "mixer.h"
#include "pwm.h"

void mixer_elevon(const pid_output_t *pid, uint16_t throttle)
{
    int16_t left, right;

    left  = throttle + pid->pitch - pid->roll;
    right = throttle + pid->pitch + pid->roll;

    if (left < PWM_MIN_US)  left = PWM_MIN_US;
    if (left > PWM_MAX_US)  left = PWM_MAX_US;
    if (right < PWM_MIN_US) right = PWM_MIN_US;
    if (right > PWM_MAX_US) right = PWM_MAX_US;

    PWM_SetMicroseconds(PWM_CH2, left);
    PWM_SetMicroseconds(PWM_CH3, right);
}

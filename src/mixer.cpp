#include "mixer.h"
#include "pid.h"     // <<< BẮT BUỘC
#include "pwm.h"

void mixer_elevon(const pid_output_t *pid, uint16_t throttle)
{
    int16_t left  = 1500 + pid->roll + pid->pitch;
    int16_t right = 1500 - pid->roll + pid->pitch;

    PWM_Write(PWM_SERVO_L, left);
    PWM_Write(PWM_SERVO_R, right);
}

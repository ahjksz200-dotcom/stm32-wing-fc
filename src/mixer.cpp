#include "mixer.h"
#include "pwm.h"

void mixer_elevon(const pid_output_t *pid, uint16_t throttle)
{
    int16_t left = 1500 + pid->roll + pid->pitch;  // Tính toán tín hiệu cho servo trái
    int16_t right = 1500 - pid->roll + pid->pitch; // Tính toán tín hiệu cho servo phải

    // Gửi tín hiệu PWM tới servo và ESC
    PWM_Write(PWM_SERVO_L, left);
    PWM_Write(PWM_SERVO_R, right);
    PWM_Write(PWM_ESC, throttle); // Điều khiển ESC (throttle)
}

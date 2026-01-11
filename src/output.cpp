#include "pwm.h"

void outputUpdate(uint16_t esc, uint16_t servoL, uint16_t servoR)
{
    PWM_Write(PWM_ESC, esc);
    PWM_Write(PWM_SERVO_L, servoL);
    PWM_Write(PWM_SERVO_R, servoR);
}

#include "pwm.h"

extern uint16_t esc;
extern uint16_t servoL;
extern uint16_t servoR;

void outputInit(void)
{
    PWM_Init();
}

void outputUpdate(void)
{
    PWM_SetMicroseconds(PWM_CH1, esc);
    PWM_SetMicroseconds(PWM_CH2, servoL);
    PWM_SetMicroseconds(PWM_CH3, servoR);
}

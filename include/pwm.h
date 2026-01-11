#pragma once
#include <stdint.h>

/* Logical PWM channels */
typedef enum
{
    PWM_ESC = 0,
    PWM_SERVO_L,
    PWM_SERVO_R,
    PWM_AUX1
} pwm_channel_t;

/* Low-level timer channels */
typedef enum
{
    PWM_CH1 = 0,
    PWM_CH2,
    PWM_CH3,
    PWM_CH4
} pwm_ch_t;

/* API */
void PWM_Init(void);
void PWM_Write(pwm_channel_t ch, uint16_t us);

void PWM_ArmESC(void);
void PWM_DisarmESC(void);

#include "pwm.h"

/* Stub TIM handle (đủ để compile) */
TIM_HandleTypeDef htim3;

static uint16_t pwm_value[PWM_CH_TOTAL];

void PWM_Init(void)
{
    for (int i = 0; i < PWM_CH_TOTAL; i++) {
        pwm_value[i] = PWM_MIN_US;
    }
}

void PWM_SetMicroseconds(pwm_channel_t ch, uint16_t us)
{
    if (ch >= PWM_CH_TOTAL) return;

    if (us < PWM_MIN_US) us = PWM_MIN_US;
    if (us > PWM_MAX_US) us = PWM_MAX_US;

    pwm_value[ch] = us;

    /* TODO: map TIM channel thật sau */
    /* __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_x, us); */
}

void PWM_ArmESC(void)
{
    PWM_SetMicroseconds(PWM_CH1, PWM_MIN_US);
}

void PWM_DisarmESC(void)
{
    PWM_SetMicroseconds(PWM_CH1, PWM_MIN_US);
}

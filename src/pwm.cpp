#include "pwm.h"
#include "timer_pwm.h"

void PWM_Init(void)
{
    MX_TIM3_Init();

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void PWM_SetMicroseconds(pwm_channel_t ch, uint16_t us)
{
    if (us < PWM_MIN_US) us = PWM_MIN_US;
    if (us > PWM_MAX_US) us = PWM_MAX_US;

    switch (ch) {
        case PWM_CH1:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, us);
            break;
        case PWM_CH2:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, us);
            break;
        case PWM_CH3:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, us);
            break;
        default:
            break;
    }
}

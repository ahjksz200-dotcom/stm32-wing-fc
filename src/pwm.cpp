#include "pwm.h"
#include "timer_pwm.h"

void PWM_SetMicroseconds(pwm_ch_t ch, uint16_t us)
{
    if (us < 1000) us = 1000;
    if (us > 2000) us = 2000;

    uint32_t ccr = us; // nếu timer chạy 1MHz (1us = 1 tick)

    switch (ch)
    {
        case PWM_CH1: __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ccr); break;
        case PWM_CH2: __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ccr); break;
        case PWM_CH3: __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, ccr); break;
        case PWM_CH4: __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, ccr); break;
    }
}

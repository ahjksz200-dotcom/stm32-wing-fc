#include "pwm.h"
#include "stm32f4xx_hal.h"

/* =========================================================
   Timer handle
   → PHẢI được define ở timer_pwm.cpp hoặc main.c
   ========================================================= */
extern TIM_HandleTypeDef htim3;

/* =========================================================
   Low-level PWM write (timer channel)
   ========================================================= */
void PWM_SetMicroseconds(pwm_ch_t ch, uint16_t us)
{
    if (us < 900)  us = 900;
    if (us > 2100) us = 2100;

    switch (ch)
    {
        case PWM_CH1:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, us);
            break;
        case PWM_CH2:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, us);
            break;
        case PWM_CH3:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, us);
            break;
        case PWM_CH4:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, us);
            break;
        default:
            break;
    }
}

/* =========================================================
   Logical channel → timer channel mapping
   ========================================================= */
static pwm_ch_t pwm_map(pwm_channel_t ch)
{
    switch (ch)
    {
        case PWM_ESC:     return PWM_CH1;
        case PWM_SERVO_L: return PWM_CH2;
        case PWM_SERVO_R: return PWM_CH3;
        case PWM_AUX1:    return PWM_CH4;
        default:          return PWM_CH1;
    }
}

/* =========================================================
   High-level PWM API (dùng ở mixer / output)
   ========================================================= */
void PWM_Write(pwm_channel_t ch, uint16_t us)
{
    PWM_SetMicroseconds(pwm_map(ch), us);
}

/* =========================================================
   Init PWM (start timer channels)
   ========================================================= */
void PWM_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

    /* Safe default */
    PWM_DisarmESC();
    PWM_Write(PWM_SERVO_L, 1500);
    PWM_Write(PWM_SERVO_R, 1500);
}

/* =========================================================
   ESC helpers
   ========================================================= */
void PWM_ArmESC(void)
{
    PWM_Write(PWM_ESC, 1000);
}

void PWM_DisarmESC(void)
{
    PWM_Write(PWM_ESC, 900);
}

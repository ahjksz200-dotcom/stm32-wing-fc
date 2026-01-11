#include "pwm.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim3;

static uint32_t pwm_channel_map[PWM_CH_MAX] = {
    TIM_CHANNEL_1, // ESC
    TIM_CHANNEL_2, // Servo L
    TIM_CHANNEL_3  // Servo R
};

static inline uint32_t us_to_ccr(uint16_t us)
{
    // TIM chạy 1 MHz → 1us = 1 count
    return us;
}

void PWM_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

    PWM_DisarmESC();
}

void PWM_ArmESC(void)
{
    PWM_Write(PWM_ESC, PWM_MIN_US);
}

void PWM_DisarmESC(void)
{
    PWM_Write(PWM_ESC, PWM_MIN_US);
    PWM_Write(PWM_SERVO_L, 1500);
    PWM_Write(PWM_SERVO_R, 1500);
}

void PWM_Write(pwm_ch_t ch, uint16_t us)
{
    if (ch >= PWM_CH_MAX) return;

    if (us < PWM_MIN_US) us = PWM_MIN_US;
    if (us > PWM_MAX_US) us = PWM_MAX_US;

    __HAL_TIM_SET_COMPARE(
        &htim3,
        pwm_channel_map[ch],
        us_to_ccr(us)
    );
}

#include "pwm.h"

/*
 * PWM mapping:
 * CH1 -> ESC
 * CH2 -> Servo Left
 * CH3 -> Servo Right
 */

static TIM_HandleTypeDef htim3;

/* ================= LOW LEVEL ================= */

static uint32_t us_to_ticks(uint16_t us)
{
    // Timer @ 1 MHz → 1 tick = 1 us
    return us;
}

static void timer_init(void)
{
    __HAL_RCC_TIM3_CLK_ENABLE();

    htim3.Instance = TIM3;
    htim3.Init.Prescaler     = 84 - 1;   // 84MHz / 84 = 1MHz
    htim3.Init.CounterMode   = TIM_COUNTERMODE_UP;
    htim3.Init.Period        = 20000 - 1; // 20ms (50Hz)
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_PWM_Init(&htim3);

    TIM_OC_InitTypeDef sConfig = {};
    sConfig.OCMode = TIM_OCMODE_PWM1;
    sConfig.Pulse  = us_to_ticks(PWM_MIN_US);
    sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfig.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfig, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfig, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfig, TIM_CHANNEL_3);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

/* ================= PUBLIC API ================= */

void PWM_Init(void)
{
    timer_init();

    PWM_DisarmESC();
}

void PWM_SetMicroseconds(pwm_channel_t ch, uint16_t us)
{
    if (us < PWM_MIN_US) us = PWM_MIN_US;
    if (us > PWM_MAX_US) us = PWM_MAX_US;

    uint32_t ticks = us_to_ticks(us);

    switch (ch) {
    case PWM_CH1:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ticks);
        break;
    case PWM_CH2:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ticks);
        break;
    case PWM_CH3:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, ticks);
        break;
    default:
        break;
    }
}

void PWM_ArmESC(void)
{
    PWM_SetMicroseconds(PWM_CH1, PWM_MIN_US);
}

void PWM_DisarmESC(void)
{
    PWM_SetMicroseconds(PWM_CH1, PWM_MIN_US);
}

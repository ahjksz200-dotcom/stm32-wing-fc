#include "pwm.h"

TIM_HandleTypeDef htim3;

/*
 * TIM3:
 * CH1 -> PA6  (ESC)
 * CH2 -> PA7  (Servo L)
 * CH3 -> PB0  (Servo R)
 */

static uint32_t pwm_us_to_ccr(uint16_t us)
{
    return us;  // 1 tick = 1us
}

void PWM_Init(void)
{
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};

    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = GPIO_AF2_TIM3;

    gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &gpio);

    gpio.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOB, &gpio);

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 84 - 1;   // 84MHz / 84 = 1MHz
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 20000 - 1;   // 20ms = 50Hz
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim3);

    TIM_OC_InitTypeDef oc = {0};
    oc.OCMode = TIM_OCMODE_PWM1;
    oc.Pulse = pwm_us_to_ccr(PWM_MIN_US);
    oc.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&htim3, &oc, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim3, &oc, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&htim3, &oc, TIM_CHANNEL_3);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void PWM_SetMicroseconds(pwm_channel_t ch, uint16_t us)
{
    if (us < PWM_MIN_US) us = PWM_MIN_US;
    if (us > PWM_MAX_US) us = PWM_MAX_US;

    uint32_t pulse = pwm_us_to_ccr(us);

    switch (ch) {
    case PWM_CH1:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);
        break;
    case PWM_CH2:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse);
        break;
    case PWM_CH3:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pulse);
        break;
    default:
        break;
    }
}

void PWM_ArmESC(void)
{
    PWM_SetMicroseconds(PWM_CH1, PWM_MIN_US);
    HAL_Delay(2000);
}

void PWM_DisarmESC(void)
{
    PWM_SetMicroseconds(PWM_CH1, PWM_MIN_US);
}

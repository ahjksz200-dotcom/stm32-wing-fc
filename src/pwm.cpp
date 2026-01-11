#include "pwm.h"
#include "stm32f4xx_hal.h"

/*
 * TIM3 dùng làm PWM output
 * - CH1: ESC (Throttle)
 * - CH2: Servo Left
 * - CH3: Servo Right
 * - CH4: Dự phòng
 *
 * Giả sử:
 *  TIM3 prescaler + period đã set để:
 *  1 tick = 1 us
 *  ARR = 20000 (20ms / 50Hz)
 */

extern TIM_HandleTypeDef htim3;

/* ===== CONFIG ===== */
#define PWM_MIN_US     900
#define PWM_MAX_US     2100
#define ESC_ARM_US     1000
#define ESC_DISARM_US  900

/* ===== INTERNAL ===== */
static inline uint16_t constrain_us(uint16_t us)
{
    if (us < PWM_MIN_US) return PWM_MIN_US;
    if (us > PWM_MAX_US) return PWM_MAX_US;
    return us;
}

/* ===== API ===== */

void PWM_Init(void)
{
    /* Start PWM channels */
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

    /* Safe output */
    PWM_DisarmESC();
    PWM_SetMicroseconds(PWM_CH2, 1500);
    PWM_SetMicroseconds(PWM_CH3, 1500);
}

void PWM_SetMicroseconds(pwm_ch_t ch, uint16_t us)
{
    us = constrain_us(us);

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

/* ===== ESC CONTROL ===== */

void PWM_ArmESC(void)
{
    /* ESC arm bằng tín hiệu thấp ổn định */
    PWM_SetMicroseconds(PWM_CH1, ESC_ARM_US);
}

void PWM_DisarmESC(void)
{
    PWM_SetMicroseconds(PWM_CH1, ESC_DISARM_US);
}

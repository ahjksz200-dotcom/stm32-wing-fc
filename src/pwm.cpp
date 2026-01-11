#include "pwm.h"
#include "stm32f4xx_hal.h"

static TIM_HandleTypeDef htim3;  // Tạo handle cho timer

void PWM_Init(void)
{
    __HAL_RCC_TIM3_CLK_ENABLE();  // Kích hoạt clock cho TIM3

    htim3.Instance = TIM3;         // Sử dụng TIM3
    htim3.Init.Prescaler = 84 - 1; // Prescaler cho 1 MHz (84MHz/84)
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 20000 - 1; // Period cho PWM (50Hz)
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.RepetitionCounter = 0;
    
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
    {
        // Handle error
    }

    // Configure PWM channels
    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 1500;  // Giá trị trung tâm cho ESC/Servo (1500us)

    // PWM ESC on Channel 1
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
    // PWM Servo Left on Channel 2
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
    // PWM Servo Right on Channel 3
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);
    // PWM AUX1 on Channel 4
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void PWM_Write(pwm_channel_t ch, uint16_t us)
{
    uint32_t pulse = us * (htim3.Init.Prescaler + 1);  // Tính giá trị pulse tương ứng với thời gian PWM

    switch (ch)
    {
    case PWM_ESC:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);
        break;
    case PWM_SERVO_L:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse);
        break;
    case PWM_SERVO_R:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pulse);
        break;
    case PWM_AUX1:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pulse);
        break;
    default:
        break;
    }
}

void PWM_ArmESC(void)
{
    // Cài đặt PWM cho ESC (1500us là throttle thấp)
    PWM_Write(PWM_ESC, 1500);
}

void PWM_DisarmESC(void)
{
    // Cài đặt PWM cho ESC (1000us là throttle thấp)
    PWM_Write(PWM_ESC, 1000);
}

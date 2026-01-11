#pragma once
#include <stdint.h>

typedef enum {
    PWM_ESC = 0,
    PWM_SERVO_L,
    PWM_SERVO_R,
    PWM_CH_MAX
} pwm_ch_t;

#define PWM_MIN_US 1000
#define PWM_MAX_US 2000

void PWM_Init(void);
void PWM_ArmESC(void);
void PWM_DisarmESC(void);
void PWM_Write(pwm_ch_t ch, uint16_t us);

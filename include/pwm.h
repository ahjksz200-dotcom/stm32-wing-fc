#pragma once
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ===== PWM CONFIG ===== */
#define PWM_MIN_US     1000
#define PWM_MAX_US     2000
#define PWM_MID_US     1500

/* ===== CHANNEL INDEX ===== */
typedef enum {
    PWM_CH1 = 0,   // ESC
    PWM_CH2,       // Servo Left
    PWM_CH3,       // Servo Right
    PWM_CH4,       // Reserve
    PWM_CH_TOTAL
} pwm_channel_t;

/* ===== API ===== */
void PWM_Init(void);
void PWM_SetMicroseconds(pwm_channel_t ch, uint16_t us);
void PWM_ArmESC(void);
void PWM_DisarmESC(void);

#ifdef __cplusplus
}
#endif

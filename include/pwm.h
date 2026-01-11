#ifndef PWM_H
#define PWM_H

#include <stdint.h>

typedef enum {
    PWM_CH1 = 0,
    PWM_CH2,
    PWM_CH3,
    PWM_CH4
} pwm_ch_t;

void PWM_Init(void);
void PWM_SetMicroseconds(pwm_ch_t ch, uint16_t us);

/* ESC control */
void PWM_ArmESC(void);
void PWM_DisarmESC(void);

#endif

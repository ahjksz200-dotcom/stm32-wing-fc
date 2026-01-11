#pragma once
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void PWM_Init(void);
void PWM_ArmESC(void);
void PWM_DisarmESC(void);

#ifdef __cplusplus
}
#endif

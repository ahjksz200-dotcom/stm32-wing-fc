#pragma once
#include <stdint.h>

#define PWM_MIN_US 1000
#define PWM_MAX_US 2000
#define PWM_MID_US 1500

void pwmInit(void);
void pwmWrite(uint8_t ch, uint16_t us);

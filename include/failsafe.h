#pragma once
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void failsafe_trigger(void);
uint8_t failsafe_active(void);

#ifdef __cplusplus
}
#endif

#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void failsafe_trigger(void);
uint8_t failsafe_active(void);
void failsafe_clear(void);

#ifdef __cplusplus
}
#endif

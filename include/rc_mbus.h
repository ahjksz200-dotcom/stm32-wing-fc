#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MBUS_CHANNELS 16

void MBUS_Init(void);
uint8_t MBUS_ReadRaw(uint16_t *ch);
bool MBUS_Failsafe(void);

#ifdef __cplusplus
}
#endif

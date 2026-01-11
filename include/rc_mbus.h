#pragma once
#include <stdint.h>

void MBUS_Init(void);
uint8_t MBUS_ReadRaw(uint16_t *channels);

#pragma once
#include <stdint.h>
#include <stdbool.h>

#define MBUS_CHANNELS 16

void MBUS_Init(void);
bool MBUS_Update(void);              // gọi trong loop
uint16_t MBUS_Read(uint8_t ch);      // 0–15

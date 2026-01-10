#pragma once
#include "stm32f4xx_hal.h"

void I2C_Init(void);
HAL_StatusTypeDef I2C_Read(uint8_t dev,
                           uint8_t reg,
                           uint8_t *buf,
                           uint16_t len);

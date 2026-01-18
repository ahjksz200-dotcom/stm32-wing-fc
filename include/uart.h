#pragma once
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/* ===== MBUS UART ===== */
void UART_Init_MBUS(void);
bool UART_ReadByte_MBUS(uint8_t *b);

/* HAL callback */
void USART1_IRQHandler(void);

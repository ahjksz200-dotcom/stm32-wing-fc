#include "uart.h"

UART_HandleTypeDef huart1;

void UART_Init(void)
{
    __HAL_RCC_USART1_CLK_ENABLE();

    huart1.Instance = USART1;
    huart1.Init.BaudRate   = 115200;   // MBUS
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits   = UART_STOPBITS_1;
    huart1.Init.Parity     = UART_PARITY_NONE;
    huart1.Init.Mode       = UART_MODE_RX;
    huart1.Init.HwFlowCtl  = UART_HWCONTROL_NONE;

    HAL_UART_Init(&huart1);
}

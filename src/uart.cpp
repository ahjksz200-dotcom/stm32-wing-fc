#include "uart.h"

/* ================= UART1 for MBUS ================= */

UART_HandleTypeDef huart1;

/* Ring buffer */
#define MBUS_RX_BUF_SIZE 128
static volatile uint8_t rx_buf[MBUS_RX_BUF_SIZE];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;

static uint8_t rx_byte;

/* ================= INIT ================= */
void UART_Init_MBUS(void)
{
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};

    /* PA10 = USART1_RX */
    gpio.Pin       = GPIO_PIN_10;
    gpio.Mode      = GPIO_MODE_AF_PP;
    gpio.Pull      = GPIO_PULLUP;
    gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &gpio);

    huart1.Instance        = USART1;
    huart1.Init.BaudRate   = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits   = UART_STOPBITS_1;
    huart1.Init.Parity     = UART_PARITY_NONE;
    huart1.Init.Mode       = UART_MODE_RX;
    huart1.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&huart1);

    /* Enable RX interrupt */
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);

    HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/* ================= READ BYTE ================= */
bool UART_ReadByte_MBUS(uint8_t *b)
{
    if (rx_head == rx_tail)
        return false;

    *b = rx_buf[rx_tail];
    rx_tail = (rx_tail + 1) % MBUS_RX_BUF_SIZE;
    return true;
}

/* ================= IRQ ================= */
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1);
}

/* ================= HAL CALLBACK ================= */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        uint16_t next = (rx_head + 1) % MBUS_RX_BUF_SIZE;
        if (next != rx_tail)
        {
            rx_buf[rx_head] = rx_byte;
            rx_head = next;
        }

        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
}

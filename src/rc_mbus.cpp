#include "rc_mbus.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

static uint8_t mbus_buf[25];
static uint16_t channels[MBUS_CHANNELS];
static uint8_t idx = 0;

/* Decode 25-byte frame */
static void mbus_decode(uint8_t *b)
{
    channels[0]  = (b[1]       | b[2]  << 8) & 0x07FF;
    channels[1]  = (b[2] >> 3  | b[3]  << 5) & 0x07FF;
    channels[2]  = (b[3] >> 6  | b[4]  << 2 | b[5] << 10) & 0x07FF;
    channels[3]  = (b[5] >> 1  | b[6]  << 7) & 0x07FF;
    channels[4]  = (b[6] >> 4  | b[7]  << 4) & 0x07FF;
    channels[5]  = (b[7] >> 7  | b[8]  << 1 | b[9] << 9) & 0x07FF;
    channels[6]  = (b[9] >> 2  | b[10] << 6) & 0x07FF;
    channels[7]  = (b[10]>> 5  | b[11] << 3) & 0x07FF;
    channels[8]  = (b[12]      | b[13] << 8) & 0x07FF;
    channels[9]  = (b[13]>> 3  | b[14] << 5) & 0x07FF;
    channels[10] = (b[14]>> 6  | b[15] << 2 | b[16] << 10) & 0x07FF;
    channels[11] = (b[16]>> 1  | b[17] << 7) & 0x07FF;
    channels[12] = (b[17]>> 4  | b[18] << 4) & 0x07FF;
    channels[13] = (b[18]>> 7  | b[19] << 1 | b[20] << 9) & 0x07FF;
    channels[14] = (b[20]>> 2  | b[21] << 6) & 0x07FF;
    channels[15] = (b[21]>> 5  | b[22] << 3) & 0x07FF;
}

void MBUS_Init(void)
{
    idx = 0;
}

bool MBUS_Update(void)
{
    uint8_t byte;

    while (HAL_UART_Receive(&huart2, &byte, 1, 0) == HAL_OK)
    {
        if (idx == 0 && byte != 0x0F)
            continue;

        mbus_buf[idx++] = byte;

        if (idx == 25)
        {
            idx = 0;
            mbus_decode(mbus_buf);
            return true;
        }
    }
    return false;
}

uint16_t MBUS_Read(uint8_t ch)
{
    if (ch >= MBUS_CHANNELS) return 1024;
    return channels[ch];
}

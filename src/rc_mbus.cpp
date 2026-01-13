#include "rc_mbus.h"
#include "stm32f4xx_hal.h"

/* ================= UART HANDLE ================= */
extern UART_HandleTypeDef huart1;

/* ================= LOCAL ================= */
static mbus_t mbus;

static uint8_t rx_byte;
static uint8_t frame[MBUS_FRAME_LEN];
static uint8_t idx = 0;

/* ================= MBUS DECODE ================= */

static void mbus_decode(uint8_t *buf)
{
    /* MBUS: 16 channels, 11-bit packed */
    mbus.ch[0]  = ((buf[1]     | buf[2]  << 8) & 0x07FF);
    mbus.ch[1]  = ((buf[2]>>3  | buf[3]  << 5) & 0x07FF);
    mbus.ch[2]  = ((buf[3]>>6  | buf[4]  << 2 | buf[5]<<10) & 0x07FF);
    mbus.ch[3]  = ((buf[5]>>1  | buf[6]  << 7) & 0x07FF);
    mbus.ch[4]  = ((buf[6]>>4  | buf[7]  << 4) & 0x07FF);
    mbus.ch[5]  = ((buf[7]>>7  | buf[8]  << 1 | buf[9]<<9) & 0x07FF);
    mbus.ch[6]  = ((buf[9]>>2  | buf[10] << 6) & 0x07FF);
    mbus.ch[7]  = ((buf[10]>>5 | buf[11] << 3) & 0x07FF);

    mbus.ch[8]  = ((buf[12]    | buf[13] << 8) & 0x07FF);
    mbus.ch[9]  = ((buf[13]>>3 | buf[14] << 5) & 0x07FF);
    mbus.ch[10] = ((buf[14]>>6 | buf[15] << 2 | buf[16]<<10) & 0x07FF);
    mbus.ch[11] = ((buf[16]>>1 | buf[17] << 7) & 0x07FF);
    mbus.ch[12] = ((buf[17]>>4 | buf[18] << 4) & 0x07FF);
    mbus.ch[13] = ((buf[18]>>7 | buf[19] << 1 | buf[20]<<9) & 0x07FF);
    mbus.ch[14] = ((buf[20]>>2 | buf[21] << 6) & 0x07FF);
    mbus.ch[15] = ((buf[21]>>5 | buf[22] << 3) & 0x07FF);

    mbus.failsafe = buf[23] & (1 << 3);

    /* scale 172–1811 → 1000–2000 */
    for (int i = 0; i < MBUS_CHANNELS; i++)
    {
        mbus.ch[i] = (mbus.ch[i] - 172) * 1000 / (1811 - 172) + 1000;
    }
}

/* ================= API ================= */

void MBUS_Init(void)
{
    idx = 0;
    mbus.failsafe = false;

    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}

uint8_t MBUS_ReadRaw(uint16_t *channels)
{
    for (int i = 0; i < MBUS_CHANNELS; i++)
    {
        channels[i] = mbus.ch[i];
    }
    return mbus.failsafe ? 0 : 1;
}

bool MBUS_Failsafe(void)
{
    return mbus.failsafe;
}

/* ================= UART IRQ CALLBACK ================= */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart != &huart1) return;

    if (idx == 0 && rx_byte != 0x0F)
    {
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
        return;
    }

    frame[idx++] = rx_byte;

    if (idx >= MBUS_FRAME_LEN)
    {
        mbus_decode(frame);
        idx = 0;
    }

    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}

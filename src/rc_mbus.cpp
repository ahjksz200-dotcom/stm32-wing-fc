#include "rc_mbus.h"
#include "uart.h"

uint16_t rc_channels[RC_CHANNELS];

static uint8_t frame[32];
static uint8_t idx = 0;

void RC_MBUS_Init(void)
{
    UART_Init_MBUS();
}

static uint8_t mbus_checksum_ok(uint8_t *buf)
{
    uint16_t sum = 0xFFFF;
    for (int i = 0; i < 30; i++)
        sum -= buf[i];

    uint16_t rx = buf[30] | (buf[31] << 8);
    return (sum == rx);
}

void RC_MBUS_Read(void)
{
    uint8_t b;

    while (UART_ReadByte_MBUS(&b))
    {
        frame[idx++] = b;

        if (idx == 2)
        {
            if (frame[0] != 0x20 || frame[1] != 0x40)
                idx = 0;
        }

        if (idx >= 32)
        {
            if (mbus_checksum_ok(frame))
            {
                for (int ch = 0; ch < RC_CHANNELS; ch++)
                {
                    rc_channels[ch] =
                        frame[2 + ch * 2] |
                        (frame[3 + ch * 2] << 8);
                }
            }
            idx = 0;
        }
    }
}

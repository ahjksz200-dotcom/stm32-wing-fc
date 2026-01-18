#include "rc_mbus.h"
#include "uart.h"

static uint16_t rc_channels[RC_CHANNELS];

/* ================= INIT ================= */
void RC_MBUS_Init(void)
{
    UART_Init_MBUS();
}

/* ================= READ ================= */
bool RC_MBUS_Read(rc_data_t *rc)
{
    static uint8_t buf[32];
    static uint8_t idx = 0;
    uint8_t b;

    while (UART_ReadByte_MBUS(&b))
    {
        if (idx == 0 && b != 0x20)
            continue;

        buf[idx++] = b;

        if (idx >= 32)
        {
            idx = 0;

            /* Parse 14 channels */
            for (int ch = 0; ch < RC_CHANNELS; ch++)
            {
                rc_channels[ch] =
                    ((buf[2 + ch * 2]) |
                    (buf[3 + ch * 2] << 8)) & 0x07FF;
            }

            /* Map channels */
            for (int i = 0; i < RC_CHANNELS; i++)
                rc->ch[i] = rc_channels[i];

            rc->roll     = rc_channels[0];
            rc->pitch    = rc_channels[1];
            rc->yaw      = rc_channels[2];
            rc->throttle = rc_channels[3];

            return true;
        }
    }
    return false;
}

#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MBUS_CHANNELS   16

typedef struct
{
    uint16_t ch[MBUS_CHANNELS];  // giá trị 1000–2000us
    bool     failsafe;
} mbus_t;

/* API */
void    MBUS_Init(void);
uint8_t MBUS_ReadRaw(uint16_t *channels);
bool    MBUS_Failsafe(void);

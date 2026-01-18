#pragma once
#include <stdint.h>

#define RC_CHANNELS 14

extern uint16_t rc_channels[RC_CHANNELS];

void RC_MBUS_Init(void);
void RC_MBUS_Read(void);

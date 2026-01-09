#pragma once
#include <stdint.h>
#include <stdbool.h>

#define RC_CH 8

void rc_init(void);
void rc_update(void);
uint16_t rc_read(uint8_t ch);
bool rc_lost(void);

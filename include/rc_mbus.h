#pragma once
#include <stdint.h>
#include <stdbool.h>

#define MBUS_CHANNELS 16

typedef struct {
    uint16_t ch[MBUS_CHANNELS];
    bool failsafe;
    bool frame_lost;
} mbus_t;

// init UART + mbus
void mbus_init(void);

// đọc frame MBUS
void mbus_update(void);

// lấy giá trị kênh
uint16_t mbus_get_channel(uint8_t ch);

// trạng thái failsafe
bool mbus_failsafe(void);

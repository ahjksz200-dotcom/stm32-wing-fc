#pragma once
#include <stdint.h>
#include <stdbool.h>

#define MBUS_CHANNELS 8

typedef struct {
    uint16_t ch[MBUS_CHANNELS];
    bool failsafe;
} mbus_t;

#ifdef __cplusplus
extern "C" {
#endif

void MBUS_Init(void);
uint8_t MBUS_ReadRaw(uint16_t *channels);
bool MBUS_Failsafe(void);

#ifdef __cplusplus
}
#endif

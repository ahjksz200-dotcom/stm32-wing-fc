#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ===== RC DATA (STUB – TẠM THỜI) ===== */
typedef struct
{
    uint16_t throttle;
    uint16_t roll;
    uint16_t pitch;
    uint16_t yaw;
    uint8_t  arm;
} rc_data_t;

/* ===== API ===== */
void RC_Init(void);
uint8_t RC_Read(rc_data_t *rc);

#ifdef __cplusplus
}
#endif

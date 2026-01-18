#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "rc.h"

/* ===== MBUS ===== */
void RC_MBUS_Init(void);
bool RC_MBUS_Read(rc_data_t *rc);

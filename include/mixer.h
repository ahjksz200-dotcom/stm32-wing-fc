#pragma once
#include "pid.h"

#ifdef __cplusplus
extern "C" {
#endif

void mixer_elevon(const pid_output_t *pid, uint16_t throttle);

#ifdef __cplusplus
}
#endif

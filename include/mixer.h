#pragma once
#include <stdint.h>
#include "pid.h"     // <<< BẮT BUỘC

void mixer_elevon(const pid_output_t *pid, uint16_t throttle);

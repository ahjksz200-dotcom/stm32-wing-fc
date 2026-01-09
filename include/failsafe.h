#pragma once
#include <stdbool.h>

void FAILSAFE_Init(void);
void FAILSAFE_Trigger(void);
bool FAILSAFE_IsActive(void);

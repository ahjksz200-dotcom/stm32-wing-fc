#include "failsafe.h"

static bool fs = false;

void FAILSAFE_Init(void) { fs = false; }
void FAILSAFE_Trigger(void) { fs = true; }
bool FAILSAFE_IsActive(void) { return fs; }

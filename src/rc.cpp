#include "rc.h"
#include "rc_mbus.h"

void RC_Init(void)
{
    RC_MBUS_Init();
}

void RC_Read(void)
{
    RC_MBUS_Read();
}

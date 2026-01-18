#include "rc.h"
#include "rc_mbus.h"

void RC_Init(void)
{
    RC_MBUS_Init();
}

bool RC_Read(rc_data_t *rc)
{
    return RC_MBUS_Read(rc);
}

#include "fc.h"

int main(void)
{
    FC_Init();

    while (1)
    {
        FC_Loop();
    }
}

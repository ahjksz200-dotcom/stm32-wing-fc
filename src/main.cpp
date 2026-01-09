#include "fc.h"
#include "pwm.h"

int main(void)
{
    HAL_Init();

    FC_Init();
    PWM_Init();
    PWM_ArmESC();

    while (1)
    {
        FC_Loop();   // đọc IMU → PID → mixer → PWM
    }
}

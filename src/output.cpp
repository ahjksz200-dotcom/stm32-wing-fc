#include "output.h"
#include "pwm.h"

uint16_t esc = 1000;
uint16_t servoL = 1500;
uint16_t servoR = 1500;

void outputInit()
{
    pwmInit();
}

void outputUpdate()
{
    pwmWrite(0, esc);
    pwmWrite(1, servoL);
    pwmWrite(2, servoR);
}

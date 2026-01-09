#include "output.h"

void outputInit() {
    pwmInit();
}

void outputUpdate() {
    pwmWrite(0, esc);
    pwmWrite(1, servoL);
    pwmWrite(2, servoR);
}

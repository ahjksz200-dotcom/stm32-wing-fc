#include "mixer.h"

void mixerElevon(float throttle, float roll, float pitch,
                 float* left, float* right) {
    *left  = throttle + pitch + roll;
    *right = throttle + pitch - roll;

    if(*left>1) *left=1;
    if(*right>1)*right=1;
}

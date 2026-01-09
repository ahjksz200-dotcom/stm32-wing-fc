#include "mixer.h"

void Mixer_Elevon(float throttle,
                  float roll,
                  float pitch,
                  mixer_output_t *out) {
    out->left  = throttle + pitch + roll;
    out->right = throttle + pitch - roll;
}

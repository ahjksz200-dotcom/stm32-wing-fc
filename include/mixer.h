#pragma once

typedef struct {
    float left;
    float right;
} mixer_output_t;

void Mixer_Elevon(float throttle,
                  float roll,
                  float pitch,
                  mixer_output_t *out);

#pragma once

typedef struct {
    float roll;
    float pitch;
    float yaw;
    float throttle;
} control_t;

typedef struct {
    float left;
    float right;
} elevon_t;

elevon_t mixer_elevon(control_t in);

#pragma once

typedef struct {
    float kp;
    float ki;
    float kd;
    float i;
    float prev;
} pid_t;

void pid_init(pid_t* p, float kp, float ki, float kd);
float pid_update(pid_t* p, float sp, float mea, float dt);

#pragma once

typedef enum {
    PID_ROLL,
    PID_PITCH,
    PID_YAW
} pid_axis_t;

void PID_Init(void);

float PID_Update(pid_axis_t axis,
                 float setpoint,
                 float measurement,
                 float dt);

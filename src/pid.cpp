#include "pid.h"

typedef struct {
    float kp, ki, kd;
    float i;
    float prev;
} PID;

static PID pidRoll = {4.0f,0.02f,0.08f};
static PID pidPitch= {4.0f,0.02f,0.08f};

float pidUpdate(PID* p, float target, float current, float dt) {
    float err = target - current;
    p->i += err * dt;
    float d = (err - p->prev)/dt;
    p->prev = err;
    return p->kp*err + p->ki*p->i + p->kd*d;
}

void pidAttitude(float tr, float tp, float cr, float cp, float* outR, float* outP) {
    *outR = pidUpdate(&pidRoll, tr, cr, 0.001f);
    *outP = pidUpdate(&pidPitch,tp, cp, 0.001f);
}

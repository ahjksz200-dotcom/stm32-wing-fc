#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float roll;
    float pitch;
    float yaw;
} ekf_state_t;

void EKF_Init(void);
void EKF_Update(float gx, float gy, float gz,
                float ax, float ay, float az,
                float dt);
ekf_state_t EKF_GetState(void);

#ifdef __cplusplus
}
#endif

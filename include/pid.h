#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ================= IMU DATA ================= */
typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} imu_data_t;

/* ================= RC DATA ================= */
typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    uint16_t throttle;
    uint8_t arm;
} rc_data_t;

/* ================= PID OUTPUT ================= */
typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} pid_output_t;

/* ================= PID API ================= */
/*
 * imu  : dữ liệu IMU (roll/pitch/yaw)
 * rc   : input từ RC
 * out  : output PID đưa sang mixer
 */
void PID_Update(const imu_data_t *imu,
                const rc_data_t  *rc,
                pid_output_t     *out);

#ifdef __cplusplus
}
#endif

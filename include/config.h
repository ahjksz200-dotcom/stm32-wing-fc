#pragma once

// ===== FEATURES =====
#define USE_IMU
#define USE_GPS
#define USE_COMPASS
#define USE_EKF
#define USE_RTH
#define USE_ALT_HOLD

// ===== LOOP RATE =====
#define LOOP_HZ        1000
#define IMU_HZ         1000
#define RC_HZ          200
#define GPS_HZ         10

// ===== LIMITS =====
#define MAX_ROLL_ANGLE   45.0f
#define MAX_PITCH_ANGLE  30.0f

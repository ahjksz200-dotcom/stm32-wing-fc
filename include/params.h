#pragma once

/* ===== PID ===== */
#define PID_ROLL_P   4.0f
#define PID_ROLL_I   0.02f
#define PID_ROLL_D   0.08f

#define PID_PITCH_P  4.0f
#define PID_PITCH_I  0.02f
#define PID_PITCH_D  0.08f

/* ===== LIMITS ===== */
#define MAX_ROLL_DEG    45.0f
#define MAX_PITCH_DEG   30.0f

/* ===== FAILSAFE ===== */
#define FAILSAFE_THROTTLE   0.35f
#define FAILSAFE_DELAY_MS  800

/* ===== ALT HOLD ===== */
#define ALT_P         1.5f
#define ALT_I         0.04f
#define ALT_D         0.1f

/* ===== RTH ===== */
#define RTH_ALTITUDE  60.0f     // meters
#define RTH_RADIUS   20.0f
#define RTH_THROTTLE 0.45f

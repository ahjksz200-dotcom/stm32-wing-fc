#include "fc.h"
#include "imu.h"
#include "pid.h"
#include "rc_mbus.h"
#include "pwm.h"
#include "failsafe.h"
#include "mixer.h"

static imu_data_t imu;   // Dữ liệu IMU
static rc_data_t rc;     // Dữ liệu RC
static pid_output_t pid_out;  // Kết quả PID điều khiển

static uint8_t armed = 0; // Trạng thái vũ khí (armed/disarmed)

void FC_Init(void)
{
    // Khởi tạo các thành phần của FC
    IMU_Init();     // Khởi tạo IMU
    PWM_Init();     // Khởi tạo PWM cho ESC và servo
    RC_Init();      // Khởi tạo điều khiển RC
}

void FC_Loop(void)
{
    // Đọc dữ liệu RC
    if (!RC_Read(&rc)) {
        failsafe_trigger(); // Nếu không đọc được RC, kích hoạt failsafe
        return;
    }

    // Kiểm tra tình trạng failsafe
    if (failsafe_active()) {
        PWM_DisarmESC(); // Nếu failsafe, ngắt ESC
        armed = 0;       // Đặt lại trạng thái armed
        return;
    }

    // Cập nhật dữ liệu IMU
    IMU_Update(&imu);

    // Cập nhật PID
    PID_Update(&imu, &rc, &pid_out);

    // Kiểm tra nếu RC arm đã kích hoạt và máy bay chưa được armed
    if (rc.arm && !armed) {
        PWM_ArmESC(); // Kích hoạt ESC
        armed = 1;    // Đặt trạng thái armed
    }

    // Nếu RC arm tắt và máy bay đã được armed
    if (!rc.arm && armed) {
        PWM_DisarmESC(); // Tắt ESC
        armed = 0;       // Đặt lại trạng thái armed
    }

    // Nếu máy bay đang armed, tiến hành điều khiển servo và ESC
    if (armed) {
        // Điều khiển servo trái và phải, với tín hiệu từ PID và RC throttle
        mixer_elevon(&pid_out, rc.throttle);
    }

    // Xuất PWM cho ESC (PWM_ESC) và servo (PWM_SERVO_L, PWM_SERVO_R)
    PWM_Write(PWM_ESC, rc.throttle);      // PWM cho ESC
    PWM_Write(PWM_SERVO_L, rc.roll);     // PWM cho servo trái
    PWM_Write(PWM_SERVO_R, rc.pitch);    // PWM cho servo phải
}

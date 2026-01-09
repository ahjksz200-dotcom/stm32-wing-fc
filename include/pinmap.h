#pragma once
#include "stm32f4xx_hal.h"

/* ===== I2C ===== */
#define PIN_I2C_SCL     GPIO_PIN_8    // PB8
#define PIN_I2C_SDA     GPIO_PIN_9    // PB9

/* ===== MPU6500 ===== */
#define MPU_I2C         I2C1

/* ===== RC M.BUS ===== */
#define PIN_MBUS_RX     GPIO_PIN_10   // PB10
#define MBUS_UART       USART3

/* ===== PWM OUTPUT ===== */
#define PIN_ESC         GPIO_PIN_8    // PA8  TIM1_CH1
#define PIN_SERVO_L     GPIO_PIN_9    // PA9  TIM1_CH2
#define PIN_SERVO_R     GPIO_PIN_10   // PA10 TIM1_CH3

/* ===== GPS ===== */
#define PIN_GPS_TX      GPIO_PIN_6    // PA6
#define PIN_GPS_RX      GPIO_PIN_7    // PA7
#define GPS_UART        USART2

/* ===== COMPASS (I2C) ===== */
#define COMPASS_ADDR    0x1E

/* ===== LED / BUZZER ===== */
#define PIN_LED         GPIO_PIN

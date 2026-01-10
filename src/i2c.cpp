#include "i2c.h"

I2C_HandleTypeDef hi2c1;

void I2C_Init(void) {
    // init sau
}

HAL_StatusTypeDef I2C_Read(uint8_t dev,
                           uint8_t reg,
                           uint8_t *buf,
                           uint16_t len) {
    return HAL_I2C_Mem_Read(&hi2c1,
                            dev << 1,
                            reg,
                            I2C_MEMADD_SIZE_8BIT,
                            buf,
                            len,
                            100);
}

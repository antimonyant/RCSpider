#pragma once

#include <I2C.h>

#define PCA1 0x41
#define PCA2 0x40

// Registers
#define MODE1 0x00

//float prevCmd[18];

void reset(I2C_HandleTypeDef *hi2c1, uint8_t devAddr);

void setPWMFreq(I2C_HandleTypeDef *hi2c1, uint8_t devAddr); //Hardcoded 50Hz

void writePWMDutyCycle(I2C_HandleTypeDef *hi2c1, uint8_t num, float dutyCycle); //0 - 100

void setServoAngle(I2C_HandleTypeDef *hi2c1, uint8_t num, float angle);

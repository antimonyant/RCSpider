#pragma once
#include "stm32l4xx_hal.h"

void writeI2CByte(I2C_HandleTypeDef *hi2c1, uint8_t devAddr, uint8_t regAddr, uint8_t data);

uint8_t readI2CByte(I2C_HandleTypeDef *hi2c1, uint8_t devAddr, uint8_t regAddr);


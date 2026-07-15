#include <I2C.h>

void writeI2CByte(I2C_HandleTypeDef *hi2c1, uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
	uint8_t buffer[2] = {regAddr, data};

	HAL_I2C_Master_Transmit(hi2c1, devAddr, &buffer[0], 2, 1000);
}

uint8_t readI2CByte(I2C_HandleTypeDef *hi2c1, uint8_t devAddr, uint8_t regAddr)
{
	uint8_t buffer[2];
	buffer[0] = regAddr;

	HAL_I2C_Master_Transmit(hi2c1, devAddr, &buffer[0], 1, 1000);

	HAL_I2C_Master_Receive(hi2c1, devAddr, &buffer[0], 1, 1000);

	return buffer[0];
}

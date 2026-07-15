#include <PCA9685.h>

void reset(I2C_HandleTypeDef *hi2c1, uint8_t devAddr)
{
	devAddr = devAddr << 1;
	writeI2CByte(hi2c1, devAddr, MODE1, 0x80);
}

void setPWMFreq(I2C_HandleTypeDef *hi2c1, uint8_t devAddr) //Hardcoded 50Hz
{
	devAddr = devAddr << 1;
	uint8_t prescaler = 121;

	// First sleep the device
	uint8_t oldmode = readI2CByte(hi2c1, devAddr, 0);
	uint8_t newmode = (oldmode & ~0x80) | 0x10; // Disable restart and sleep

	//printf("Middle: %d\n", readI2CByte(devAddr, 0));

	writeI2CByte(hi2c1, devAddr, 0, newmode);

	// Set the prescaler
	writeI2CByte(hi2c1, devAddr, 0xFE, prescaler);

	// Wake Device
	writeI2CByte(hi2c1, devAddr, 0, (oldmode | 0x80 | 0x20 | 1));

	//printf("End: %d\n", readI2CByte(devAddr, 0));
	//printf("End: %d\n", readI2CByte(devAddr, 0xFE));
}

void writePWMDutyCycle(I2C_HandleTypeDef *hi2c1, uint8_t num, float dutyCycle) //0 - 100
{
	uint16_t CCR = (uint16_t)((dutyCycle/100.0) * 4096.0);

	uint8_t buffer[5] = {0x06 + (4 * (num % 16)),
						0,
						0,
						(uint8_t)(CCR & 0xFF),
						(uint8_t)(CCR >> 8)};

	if(num > 15)
	{
		//HAL_I2C_Master_Transmit(&hi2c1, (PCA2 << 1), &buffer[0], 1, 1000);
		HAL_I2C_Master_Transmit(hi2c1, (PCA2 << 1), &buffer[0], 5, 1000);
	}
	else
	{
		//HAL_I2C_Master_Transmit(&hi2c1, (PCA1 << 1), &buffer[0], 1, 1000);
		HAL_I2C_Master_Transmit(hi2c1, (PCA1 << 1), &buffer[0], 5, 1000);
	}
}

void setServoAngle(I2C_HandleTypeDef *hi2c1, uint8_t num, float angle)
{
	writePWMDutyCycle(hi2c1, num, ((angle / 18.0) + 7.5));
}


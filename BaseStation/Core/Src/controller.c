#include "controller.h"
#include "display.h"

extern uint8_t mode;

// unused now
uint8_t msb_to_lsb(uint8_t num)
{
	uint8_t count = sizeof(num) * 8 - 1;
	uint8_t reverse_num = num;

	num >>= 1; // shift num right by 1, to handle the loop from here
	while(num)
	{
	   reverse_num <<= 1;
	   reverse_num |= num & 1;
	   num >>= 1;
	   count--;
	}
	reverse_num <<= count; // shift when num is exhausted
	return reverse_num;
}

void CONTROLLER_init(){
	  //CONFIG TRANSACTION (to get to analog mode)
	  //CC default high
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	  //set low to start transaction
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	  //enter config mode to switch to analog
	  HAL_SPI_TransmitReceive(&hspi1, CONTROLLER_config, CONTROLLER_config_receive, 21, 100);
	  //set back high
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	  //set CC low (again)
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	  //switch to analog mode
	  HAL_SPI_TransmitReceive(&hspi1, CONTROLLER_analog, CONTROLLER_analog_receive, 9, 100);
	  //set back high (again)
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	  //set CC low (again again)
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	  //get out of config mode
	  HAL_SPI_TransmitReceive(&hspi1, CONTROLLER_config_leave, CONTROLLER_config_receive, 21, 100);
	  //set back high (again again)
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}

void CONTROLLER_update(){
	//CC default high
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	//set low to start transaction
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	//send data to slave
	HAL_SPI_TransmitReceive(&hspi1, CONTROLLER_send, CONTROLLER_receive, 21, 100);
	//set back high
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	//convert info
	//	  int digital1 = receive[3];
	//	  int digital2 = receive[4];

	int analogRX = CONTROLLER_receive[5];
	int analogRY = CONTROLLER_receive[6];
	int analogLX = CONTROLLER_receive[7];
	int analogLY = CONTROLLER_receive[8];
	uint8_t modePlusOne = mode + 1;

	uint8_t buffer[7] = {'(', analogRX, analogRY, analogLX, analogLY, modePlusOne, ')'};

	//print info
	printf("%d %d %d %d %d\n", analogRX, analogRY, analogLX, analogLY, modePlusOne);
	HAL_UART_Transmit(&CONTROLLER_UART_PORT, &buffer, sizeof(buffer), 1000);

//	CONTROLLER_buffer[0] = analogRX;
//	CONTROLLER_buffer[1] = analogRY;
//	CONTROLLER_buffer[2] = analogLX;
//	CONTROLLER_buffer[3] = analogLY;
//
//	//print info
//	printf("%d %d %d %d\n", analogRX, analogRY, analogLX, analogLY);
}

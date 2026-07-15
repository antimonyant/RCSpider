#include "main.h"
#include "stm32l4xx_hal.h"
#include "stdio.h"
#include <stdint.h>

#define CONTROLLER_SPI_PORT hspi1
#define CONTROLLER_UART_PORT huart3
extern SPI_HandleTypeDef CONTROLLER_SPI_PORT;
extern UART_HandleTypeDef CONTROLLER_UART_PORT;


#define CONTROLLER_CC_PORT	GPIOB
#define CONTROLLER_CC_PIN	GPIO_PIN_6


//data
static uint8_t CONTROLLER_send[21] = {0x01, 0x42, 0x00, 0x00, 0x00};
static uint8_t CONTROLLER_receive[21];

//send to enter config mode
static uint8_t CONTROLLER_config[21] = {0x01, 0x43, 0x00, 0x01, 0x00};
//static uint8_t CONTROLLER_config[21] = {0x00, 0x80, 0x00, 0xC2, 0x80};
static uint8_t CONTROLLER_config_receive[21];

//send to enter analog mode
static uint8_t CONTROLLER_analog[9] = {0x01, 0x44, 0x00, 0x01, 0x00};
static uint8_t CONTROLLER_analog_receive[9];

//send to exit config mode
static uint8_t CONTROLLER_config_leave[21] = {0x01, 0x43, 0x00, 0x00, 0x00};

// controller buffer
static uint8_t CONTROLLER_buffer[4]={0,0,0,0};

void CONTROLLER_init();
void CONTROLLER_update();
uint8_t msb_to_lsb(uint8_t num);

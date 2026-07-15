#include "stm32l4xx_hal.h"
#include "stdio.h"
#include <string.h>
#include <stdarg.h>
#include "ili9341.h"
#include "ili9341_touch.h"
#include "fonts.h"

// TODO: Change for board START

// Define the ports and pins. Note that MSB is on the left
#define NUMPAD_WIRE7_PORT	GPIOE
#define NUMPAD_WIRE7_PIN	GPIO_PIN_6
#define NUMPAD_WIRE6_PORT	GPIOD
#define NUMPAD_WIRE6_PIN	GPIO_PIN_7
#define NUMPAD_WIRE5_PORT	GPIOF
#define NUMPAD_WIRE5_PIN	GPIO_PIN_9
#define NUMPAD_WIRE4_PORT	GPIOF
#define NUMPAD_WIRE4_PIN	GPIO_PIN_8
#define NUMPAD_WIRE3_PORT	GPIOF
#define NUMPAD_WIRE3_PIN	GPIO_PIN_5
#define NUMPAD_WIRE2_PORT	GPIOF
#define NUMPAD_WIRE2_PIN	GPIO_PIN_3
#define NUMPAD_WIRE1_PORT	GPIOE
#define NUMPAD_WIRE1_PIN	GPIO_PIN_5
#define NUMPAD_WIRE0_PORT	GPIOE
#define NUMPAD_WIRE0_PIN	GPIO_PIN_4

// Change for board END



// Set the bits for the numpad
#define NUMPAD_KEY0			0
#define NUMPAD_KEY1			1
#define NUMPAD_KEY2			2
#define NUMPAD_KEY3			3
#define NUMPAD_KEY4			4
#define NUMPAD_KEY5			5
#define NUMPAD_KEY6			6
#define NUMPAD_KEY7			7
#define NUMPAD_KEY8			8
#define NUMPAD_KEY9			9
#define NUMPAD_KEYA			10
#define NUMPAD_KEYB			11
#define NUMPAD_KEYC			12
#define NUMPAD_KEYD			13
#define NUMPAD_KEYASTK		14
#define NUMPAD_KEYPOUND		15

void NUMPAD_init();

void NUMPAD_update();

void NUMPAD_reset();
void NUMPAD_set();

void NUMPAD_callback(uint16_t numpad);

uint16_t NUMPAD_read();

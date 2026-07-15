#include "numpad.h"
#include "display.h"

// initalize
void NUMPAD_init(){
	NUMPAD_callback(0);
	NUMPAD_set();
}

// Run numpad code from loop
void NUMPAD_update(){
	uint16_t numpad = 0;
	numpad = NUMPAD_read();
	NUMPAD_callback(numpad);
}

// Set up the numpad default state
void NUMPAD_reset(){
	// Pull down the columns high
	HAL_GPIO_WritePin(NUMPAD_WIRE0_PORT, NUMPAD_WIRE0_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(NUMPAD_WIRE1_PORT, NUMPAD_WIRE1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(NUMPAD_WIRE2_PORT, NUMPAD_WIRE2_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(NUMPAD_WIRE3_PORT, NUMPAD_WIRE3_PIN, GPIO_PIN_RESET);
}

void NUMPAD_set(){
	// Pull down the columns high
	HAL_GPIO_WritePin(NUMPAD_WIRE0_PORT, NUMPAD_WIRE0_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(NUMPAD_WIRE1_PORT, NUMPAD_WIRE1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(NUMPAD_WIRE2_PORT, NUMPAD_WIRE2_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(NUMPAD_WIRE3_PORT, NUMPAD_WIRE3_PIN, GPIO_PIN_SET);
}


// Code for what each button does
void NUMPAD_callback(uint16_t numpad){
	// TODO: BANDAID FIX - Discard if all keys are pressed
	if (numpad & (0b1 << NUMPAD_KEYA) && numpad & (0b1 << NUMPAD_KEY3) && numpad & (0b1 << NUMPAD_KEY2) && numpad & (0b1 << NUMPAD_KEY1)){
		return;
	}
	// Functions for what to do when the numpad is pressed
	// Note this is bitwise down the rows
//	if (numpad & (0b1 << NUMPAD_KEYA)){
//			ILI9341_WriteString(0,16*10,"key A",Font_11x18,ILI9341_GREEN,ILI9341_BLACK);
//		}
	if (numpad & (0b1 << NUMPAD_KEY3)){
		DISPLAY_change_mode(DISPLAY_mode3);
		printf("KEY3\n");
	}

	if (numpad & (0b1 << NUMPAD_KEY2)){
		DISPLAY_change_mode(DISPLAY_mode2);
		printf("KEY2\n");
	}

	if (numpad & (0b1 << NUMPAD_KEY1)){
		DISPLAY_change_mode(DISPLAY_mode1);
		printf("KEY1\n");
	}
}


// Read which buttons are pressed (logic + probing)
uint16_t NUMPAD_read(){
	uint16_t numpad = 0;
	// Pull down the columns high
	NUMPAD_set();

	// Set each column and probe rows
	HAL_GPIO_WritePin(NUMPAD_WIRE0_PORT, NUMPAD_WIRE0_PIN, GPIO_PIN_RESET);
	numpad = numpad | (((~HAL_GPIO_ReadPin(NUMPAD_WIRE7_PORT, NUMPAD_WIRE7_PIN))&0b1) << NUMPAD_KEYA); // Read Key A
//	numpad = numpad | (((~HAL_GPIO_ReadPin(NUMPAD_WIRE6_PORT, NUMPAD_WIRE6_PIN))&0b1) << NUMPAD_KEYB); // Read Key B
//	numpad = numpad | (((~HAL_GPIO_ReadPin(NUMPAD_WIRE5_PORT, NUMPAD_WIRE5_PIN))&0b1) << NUMPAD_KEYC); // Read Key C
//	numpad = numpad | (((~HAL_GPIO_ReadPin(NUMPAD_WIRE4_PORT, NUMPAD_WIRE4_PIN))&0b1) << NUMPAD_KEYD); // Read Key D
	HAL_GPIO_WritePin(NUMPAD_WIRE0_PORT, NUMPAD_WIRE0_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(NUMPAD_WIRE1_PORT, NUMPAD_WIRE1_PIN, GPIO_PIN_RESET);
	numpad = numpad | (((~HAL_GPIO_ReadPin(NUMPAD_WIRE7_PORT, NUMPAD_WIRE7_PIN))&0b1) << NUMPAD_KEY3); // Read Key 3
	HAL_GPIO_WritePin(NUMPAD_WIRE1_PORT, NUMPAD_WIRE1_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(NUMPAD_WIRE2_PORT, NUMPAD_WIRE2_PIN, GPIO_PIN_RESET);
	numpad = numpad | (((~HAL_GPIO_ReadPin(NUMPAD_WIRE7_PORT, NUMPAD_WIRE7_PIN))&0b1) << NUMPAD_KEY2); // Read Key 2
	HAL_GPIO_WritePin(NUMPAD_WIRE2_PORT, NUMPAD_WIRE2_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(NUMPAD_WIRE3_PORT, NUMPAD_WIRE3_PIN, GPIO_PIN_RESET);
	numpad = numpad | (((~HAL_GPIO_ReadPin(NUMPAD_WIRE7_PORT, NUMPAD_WIRE7_PIN))&0b1) << NUMPAD_KEY1); // Read Key 1
	HAL_GPIO_WritePin(NUMPAD_WIRE3_PORT, NUMPAD_WIRE3_PIN, GPIO_PIN_SET);

	printf(" %f \n", (float)numpad);
	return numpad;
}

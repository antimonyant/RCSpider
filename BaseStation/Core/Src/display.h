#include "main.h"
#include "stm32l4xx_hal.h"
#include "stdio.h"
#include <string.h>
#include <stdarg.h>
#include "ili9341.h"
#include "ili9341_touch.h"
#include "fonts.h"


// Holds the variable for the mode. Note that this should olyy be values 1 2 or 3
extern uint8_t mode;
static uint8_t tilt = 2;

// Define the locations onscreen
#define DISPLAY_height_tilt  24*10
#define DISPLAY_width_tilt	 15*10
#define DISPLAY_height_mode  27*10
#define DISPLAY_color_selected_mode ILI9341_GREEN
#define DISPLAY_color_unselected_mode ILI9341_YELLOW

// Modes. note that mode 1 is the default
#define DISPLAY_mode1	0
#define DISPLAY_mode2	1
#define DISPLAY_mode3	2

// Tilt
#define DISPLAY_color_tilt_threshold	1
#define DISPLAY_color_tilt_good			ILI9341_GREEN
#define DISPLAY_color_tilt_bad			ILI9341_RED

void DISPLAY_init();

void DISPLAY_background();

void DISPLAY_change_mode(uint8_t mode);

void DISPLAY_mode(uint8_t mode, uint16_t color);

void DISPLAY_tilt(double tilt);


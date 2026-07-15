#include "display.h"
#include <stdlib.h>

uint8_t mode = 1;

const uint8_t DISPLAY_width_mode[3] = {12*10,15*10,18*10};
char DISPLAY_text_mode[3][2] = {"1","2","3"};

void DISPLAY_init(){
	DISPLAY_background();
	DISPLAY_change_mode(DISPLAY_mode1);
	DISPLAY_tilt(0);
}

void DISPLAY_background(){
	// Draw the title
	ILI9341_FillScreen(ILI9341_BLACK);
	ILI9341_WriteString(5*10,0,"Spiderpeople!",Font_11x18,ILI9341_RED,ILI9341_BLACK);
	ILI9341_WriteString(1*10,3*10,"Lena-Anthony-Richard",Font_11x18,ILI9341_GREEN,ILI9341_BLACK);
	// Draw the label for tilt
	ILI9341_WriteString(1*10,DISPLAY_height_tilt,"Tilt:",Font_11x18,ILI9341_GREEN,ILI9341_BLACK);
	// Draw the label for Mode
	ILI9341_WriteString(1*10,DISPLAY_height_mode,"Mode:",Font_11x18,ILI9341_GREEN,ILI9341_BLACK);
	// Spider Pic
//	ILI9341_DrawImage(3*10, 10*10, uint16_t w, uint16_t h, const uint16_t* data);
}

// Draw the mode numbers. Note that only one can be selected at once
void DISPLAY_change_mode(uint8_t new_mode){
	// update the mode
	mode = new_mode;

	// update the display
	DISPLAY_mode(new_mode, DISPLAY_color_selected_mode);
	if (new_mode != DISPLAY_mode1){
		DISPLAY_mode(DISPLAY_mode1, DISPLAY_color_unselected_mode);
	}
	if (new_mode != DISPLAY_mode2){
		DISPLAY_mode(DISPLAY_mode2, DISPLAY_color_unselected_mode);
	}
	if (new_mode != DISPLAY_mode3){
		DISPLAY_mode(DISPLAY_mode3, DISPLAY_color_unselected_mode);
	}

}

void DISPLAY_mode(uint8_t mode, uint16_t color){
	ILI9341_WriteString(DISPLAY_width_mode[mode],DISPLAY_height_mode,DISPLAY_text_mode[mode],Font_11x18,color,ILI9341_BLACK);
}

void DISPLAY_tilt(double new_tilt){
//	__enable_irq(); // enable all interrupts
	// Determine the color (if at risk of tilting)
	uint16_t tilt_color;
	if (abs(new_tilt) < DISPLAY_color_tilt_threshold){
		new_tilt = 0;
		tilt_color = DISPLAY_color_tilt_good;
	}
	else{
		new_tilt = 1;
		tilt_color = DISPLAY_color_tilt_bad;
	}
	// Convert to string
	if (tilt!=new_tilt){
//		char tilt_str[20];
//		sprintf(tilt_str, "%f deg", tilt);
		// Display
		ILI9341_FillRectangle(DISPLAY_width_tilt, DISPLAY_height_tilt, 15, 15, tilt_color);
		tilt = new_tilt;
	}

//	__disable_irq(); // disable all interrupts
}




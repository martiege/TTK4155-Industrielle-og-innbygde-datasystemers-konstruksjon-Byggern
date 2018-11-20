#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <stdint.h>

/*****************************************
User Input module

Converts the ADC values to usable formats, 
and implements the structs Position and 
Slider to hold the values.

The functions implemented are:

	user_input_joystick_position()
		
		Reads the ADC values to determine
		the joystick position. Returns 
		these values as the struct 
		Position. 
		
	user_input_joystick_direction()
		
		Reads the ADC values to determine
		the joystick direction. Returns
		this value as the enum Direction. 
		
	user_input_slider_position()
	
		Reads the ADC values to determine
		slider values. Returns the these 
		values as the struct Slider. 
		
	user_input_joystick_button()
	
		Reads the value of the joystick
		button. Returns 1 if the button 
		is pushed, 0 if not. 
		
	user_input_leftbutton()
	
		Reads the value of the left slider
		button. Returns 1 if the button 
		is pushed, 0 if not. 

	user_input_joystick_print_direction(
				Direction d)
	
		Prints the direction given by the
		parameter d to the UART. 
		
*****************************************/

typedef struct Position 
{
    int8_t X;
    int8_t Y;
} Position;

typedef struct Slider 
{
    uint8_t left;
    uint8_t right;
} Slider;

typedef enum Direction { NEUTRAL, LEFT, RIGHT, UP, DOWN } Direction;



Position user_input_joystick_position();

Direction user_input_joystick_direction();

Slider user_input_slider_position();

uint8_t user_input_joystick_button();

uint8_t user_input_leftbutton();

void user_input_joystick_print_direction(Direction d);

#endif
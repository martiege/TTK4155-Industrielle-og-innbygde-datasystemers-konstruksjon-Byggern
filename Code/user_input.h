#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <stdint.h>

typedef struct Position 
{
    uint8_t X;
    uint8_t Y;
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

void user_input_joystick_print_direction(Direction d);

#endif
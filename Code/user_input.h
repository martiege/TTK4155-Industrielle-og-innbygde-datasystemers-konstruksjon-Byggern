#ifndef USER_INPUT_H
#define USER_INPUT_H

typedef struct Position 
{
    int X;
    int Y;
} Position;

typedef struct Slider 
{
    int left;
    int right;
} Slider;

typedef enum Direction { NEUTRAL, LEFT, RIGHT, UP, DOWN } Direction;



Position user_input_joystick_position();

Direction user_input_joystick_direction();

Slider user_input_slider_position();

int user_input_joystick_button();

void user_input_joystick_print_direction(Direction d);

#endif
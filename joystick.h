#ifndef JOYSTICK_H
#define JOYSTICK_H

typedef struct Position{
    int X = 0;
    int Y = 0;
} Position;

enum Direction{ NEUTRAL, LEFT, RIGHT, UP, DOWN };


Position joystick_position()

Direction joystick_direction();

#endif
#ifndef JOYSTICK_H
#define JOYSTICK_H

typedef struct Position{
    int X = 0;
    int Y = 0;
} Position;

enum Direction{ NEUTRAL, LEFT, RIGHT, UP, DOWN };

// initilization function, need to note the offset when
// the function is executed, so that position can be
// used as zero (subtract init value)
void joystick_init();

Position joystick_position()

Direction joystick_direction();

#endif
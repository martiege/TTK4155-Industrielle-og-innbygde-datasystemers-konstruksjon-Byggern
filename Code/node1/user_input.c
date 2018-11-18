#include "user_input.h"
#include "ADC.h"
#include <avr/io.h>


Position user_input_joystick_position()
{    
    Position p;
    int x;
    int y;
    x  = (int)ADC_read_channel(CH1);
    y  = (int)ADC_read_channel(CH2);

    //printf("X: %d\tY: %d\n", x, y);

    x -= 136; // målt midtpunkt
    x *= 200;
    x /= 256;
    
    if (x < -10)
    {
        x += 3;
    }
    if (x > 10)
    {
        x += 4;
    }
    p.X = x;

    y -= 135; // målt midtpunkt
    y *= 200;
    y /= 256;

    if (y < -10)
    {
        y += 2;
    }
    if (y > 10)
    {
        y += 4;
    }
    p.Y = y;

    

    return p;
}

Direction user_input_joystick_direction()
{
    Position p = user_input_joystick_position();
    if (p.X > 2 && p.X >= abs(p.Y))
    {
        return RIGHT;
    }
    else if (p.X < -2 && p.X <= -abs(p.Y)) 
    {
        return LEFT;
    }
    else if (p.Y > 2 && p.Y > abs(p.X))
    {
        return UP;
    }
    else if (p.Y < -2 && p.Y < -abs(p.X)) 
    {
        return DOWN;
    }
    else
    {
        return NEUTRAL;
    }
}

Slider user_input_slider_position()
{
    Slider s;
    s.left = ADC_read_channel(CH3);
    s.right = ADC_read_channel(CH4);
    return s;
}

uint8_t user_input_joystick_button()
{
    return !(PINB & 1);
}

void user_input_joystick_print_direction(Direction d)
{
    switch (d)
    {
        case UP:
            printf("UP\n");
            break;
        case DOWN:
            printf("DOWN\n");
            break;
        case LEFT:
            printf("LEFT\n");
            break;
        case RIGHT:
            printf("RIGHT\n");
            break;
        case NEUTRAL:
            printf("NEUTRAL\n");
            break;
        default:
            printf("...");
            break;
    }
}

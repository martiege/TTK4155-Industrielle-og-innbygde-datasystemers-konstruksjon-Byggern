#include "user_input.h"
#include "ADC.h"
#include <avr/io.h>


Position user_input_joystick_position()
{
    Position p;
    p.X  = ADC_read_channel(CH1);
    p.X -= 132; // målt midtpunkt
    p.X *= 200;
    p.X /= 256;
    if (p.X < -10)
    {
        p.X += 3;
    }
    if (p.X > 10)
    {
        p.X += 4;
    }

    p.Y  = ADC_read_channel(CH2);
    p.Y -= 131; // målt midtpunkt
    p.Y *= 200;
    p.Y /= 256;
    if (p.Y < -10)
    {
        p.Y += 2;
    }
    if (p.Y > 10)
    {
        p.Y += 4;
    }

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

int user_input_joystick_button()
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


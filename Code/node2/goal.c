#include "goal.h"
#include "../lib/timer.h"
#include "../lib/UART.h"
#include "ADC_internal.h"

//------------------------------

static uint8_t goals;
static int already_goal; //bool

//------------------------------
void goal_interruptfunc();


void goal_init()
{
    goals = 0;
    already_goal = 0;

    timer_init(2, goal_interruptfunc);
    timer_set_period(50, 2);
    timer_start(2);
}

uint8_t goal_get_goals()
{
    return goals;
}

int goal_read()
{   
    return (ADC_internal_status() < 50);
}



void goal_interruptfunc()
{
    if (goal_read())
    {
        if (!(already_goal))
        {
            CAN_message msg;
            msg.id = TRANSFERRED_GOALS;
            msg.length = 1;
            msg.data[0] = 1;

            goals++;
            timer_set_period(500, 2); 
            already_goal = 1;
        }
    } 
    else //!goal
    {
        if (already_goal)
        {
            already_goal = 0;
            timer_set_period(50, 2);
        }
    }
}
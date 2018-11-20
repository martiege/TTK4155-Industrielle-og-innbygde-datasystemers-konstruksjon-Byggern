#include "goal.h"
#include "../lib/timer.h"
#include "../lib/UART.h"
#include "../lib/CAN.h"
#include "ADC_internal.h"
#include <avr/interrupt.h>
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
    timer_set_period(200, 2);
    timer_start(2);
}

uint8_t goal_get_goals()
{
    return goals;
}

int goal_read()
{       
    return (ADC_internal_status() < 800);
}



void goal_interruptfunc()
{
    if (goal_read())
    {   
        printf("already_goal: %d\n", already_goal);
        if (!(already_goal))
        {
            already_goal = 1;            
            CAN_message msg;
            msg.id = TRANSFERRED_GOALS;
            msg.length = 1;
            msg.data[0] = 1;
            CAN_send(&msg);
            goals++;
            timer_set_period(700, 2); 
        }
    } 
    else //!goal
    {
        if (already_goal)
        {
            already_goal = 0;
            timer_set_period(200, 2);
        }
    }
}
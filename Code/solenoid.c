#include "solenoid.h"
#include "defines.h"
#include <util/delay.h>

static uint8_t solenoid_shot;


void solenoid_deactivate()
{
    //SOLENOID_PORT &= ~(1 << SOLENOID_PIN);
    SOLENOID_PORT |= (1 << SOLENOID_PIN);
}

void solenoid_activate()
{
    //SOLENOID_PORT |= (1 << SOLENOID_PIN);
    SOLENOID_PORT &= ~(1 << SOLENOID_PIN);
}

void solenoid_init()
{
    // set pin  as output
    SOLENOID_DDR |= (1 << SOLENOID_PIN);

    solenoid_shot = 0;

    solenoid_deactivate();
}

void solenoid_shoot()
{
    solenoid_shot = 1;
    solenoid_activate();
    _delay_ms(75);
    solenoid_deactivate();
}

uint8_t solenoid_get_shot()
{
    return solenoid_shot;
}

void solenoid_clear_shot()
{
    solenoid_shot = 0;
}



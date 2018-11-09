#include "solenoid.h"
#include "defines.h"
#include <util/delay.h>


void soleniod_init()
{
    // set pin  as output
    SOLENOID_PORT |= (1 << SOLENOID_PIN);

    solenoid_deactivate();
}

void solenoid_shoot()
{
    solenoid_activate();
    _delay_ms_(20);
    solenoid_deactivate();
}

void solenoid_activate()
{
    SOLENOID_PORT |= (1 << SOLENOID_PIN);
}

void solenoid_deactivate()
{
    SOLENOID_PORT &= ~(1 << SOLENOID_PIN);
}
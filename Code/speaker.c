//#include "speaker.h"

#include <util/delay.h>

const int buzzer = 9; //regarding arduino pin 

void setup()
{
    pinMode(buzzer, OUTOUT); // Set buzzer - pin 9 as an output
}

void loop()
{
    tone(buzzer, 1000); // Send 1KHz sound signal
    _delay_ms(1000); // ...for 1 sec
    noTone(buzzer); // Stop sound
    _delay_ms(1000);
}

//https://www.instructables.com/id/How-to-use-a-Buzzer-Arduino-Tutorial/
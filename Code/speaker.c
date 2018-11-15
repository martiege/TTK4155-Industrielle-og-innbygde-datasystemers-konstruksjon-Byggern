#include "speaker.h"
#include "defines.h"
#include <util/delay.h>
#include "pwm.h"

static int frequency_on; //bool

void speaker_init()
{
    pwm_stop_frequency();
    frequency_on = 0;
}


void speaker_tone(float frequency)
{
    if(!frequency_on)
    {
        pwm_start_frequency();
        frequency_on = 1;
    }
    pwm_set_frequency(frequency);
}

void speaker_no_tone()
{
    pwm_stop_frequency();
    frequency_on = 0;
}
 

void speaker_loop()
{
    speaker_tone(1000); // Send 1KHz sound signal
    _delay_ms(1000); // ...for 1 sec
    speaker_no_tone(); // Stop sound
    _delay_ms(1000);
}

//https://www.instructables.com/id/How-to-use-a-Buzzer-Arduino-Tutorial/
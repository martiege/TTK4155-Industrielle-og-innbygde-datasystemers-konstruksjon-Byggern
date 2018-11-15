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
 
//test
void speaker_loop()
{
    speaker_tone(1000); // Send 1KHz sound signal
    _delay_ms(1000); // ...for 1 sec
    speaker_no_tone(); // Stop sound
    _delay_ms(1000);
}

void speaker_play_song(Song song)
{
    switch(song)
    {
        case MARIO:
            for(int tone = 0; tone < (sizeof(MARIO_melody)/sizeof(float)); tone++)
            {
                speaker_tone(MARIO_melody[tone]);
                _delay_ms(1000/MARIO_tempo[tone]);
                speaker_no_tone();
                _delay_ms(1300/MARIO_tempo[tone]);
            }
        break;
    }

    //GENERELL?:
    /*
    for(int tone = 0; tone < (sizeof(song_melody)/sizeof(float)); tone++)
    {
        speaker_tone(song_melody[tone]);
        _delay_ms(1000/song_tempo[tone]);
        //evt: if(tone = 0), hold kjeft
        //hvis  liten stopp mellom hver tone, kanskje mest for mario:
        speaker_no_tone();
        _delay_ms(1300/song_tempo[tone]);
    }*/
}

//https://www.instructables.com/id/How-to-use-a-Buzzer-Arduino-Tutorial/
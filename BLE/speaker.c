#include "speaker.h"
#include "pwm.h"
#include "util.h"
#include "ubit.h"
//#include "tone_defs.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


/* __________ SONGS __________ */
const static int MARIO_song[78] = 
{
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};

const static int MARIO_tempo[78] = 
{
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

static int frequency_on; //bool

void speaker_init()
{
    //pwm_pause_frequency();
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
    //pwm_stop_frequency();
    pwm_pause_frequency();
    frequency_on = 0;
}
 
//test
void speaker_loop()
{
    speaker_tone(1000); // Send 1KHz sound signal
    util_delay_ms(1000); // ...for 1 sec
    speaker_no_tone(); // Stop sound
    util_delay_ms(1000);
}

void speaker_play_song(Song song)
{
    switch(song)
    {
        case MARIO:
            for(int tone = 0; tone < 78; tone++)
            {
                if (MARIO_song[tone])
                {
                    speaker_tone(MARIO_song[tone]);
                    ubit_uart_print("tone: %d\n\r", MARIO_song[tone]);
                }
                else
                {
                    speaker_no_tone();
                }
                util_delay_ms(100);
                /*
                speaker_tone(MARIO_song[tone]);
                util_delay_ms(1000/MARIO_tempo[tone]);
                speaker_no_tone();
                util_delay_ms(1300/MARIO_tempo[tone]);
                */
            }
        break;
    }

    speaker_no_tone();

    //GENERELL?:
    /*
    for(int tone = 0; tone < (sizeof(song_melody)/sizeof(float)); tone++)
    {
        speaker_tone(song_melody[tone]);
        util_delay_ms(1000/song_tempo[tone]);
        //evt: if(tone = 0), hold kjeft
        //hvis  liten stopp mellom hver tone, kanskje mest for mario:
        speaker_no_tone();
        util_delay_ms(1300/song_tempo[tone]);
    }*/
}


void speaker_test()
{
    speaker_tone(1760); //E7
    util_delay_ms(500);
    speaker_no_tone();
	util_delay_ms(500);

	speaker_tone(1976); //E7
    util_delay_ms(500);
    speaker_no_tone();
	util_delay_ms(500);

	speaker_tone(2093); //E7
    util_delay_ms(500);
    speaker_no_tone();
	util_delay_ms(500);

	speaker_tone(2349); //C7
    util_delay_ms(500);
    speaker_no_tone();
    util_delay_ms(500);

    speaker_tone(2637); //E7
    util_delay_ms(500);
    speaker_no_tone();
	util_delay_ms(500);

    speaker_tone(2794); //G7
    util_delay_ms(500);
    speaker_no_tone();
	util_delay_ms(500);

    speaker_no_tone();


}




//https://www.instructables.com/id/How-to-use-a-Buzzer-Arduino-Tutorial/
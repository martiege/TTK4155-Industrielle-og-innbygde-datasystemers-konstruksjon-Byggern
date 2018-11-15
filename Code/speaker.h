#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>
#include "tone_defs.h"

void speaker_init();

void speaker_tone(float frequency);

void speaker_no_tone();

void speaker_loop();

void speaker_play_song(float song_melody, float song_tempo);

#endif
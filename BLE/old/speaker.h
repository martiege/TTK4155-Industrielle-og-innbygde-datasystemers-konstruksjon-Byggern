#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

/*All available songs*/
typedef enum Song{ MARIO } Song;

void speaker_init();

void speaker_tone(float frequency);

void speaker_no_tone();

void speaker_loop();

void speaker_play_song(Song song);


void speaker_test();

#endif
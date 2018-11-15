#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

//typedef enum Tone {C, CX, D, DX, E, F, FX, G, GX, A, AX, B};
/*
const float Tones[12][9] = 
{
    {16.35, 32.70, 65.41, 130.81, 261.63, 523.25, 1046.50, 2093.00, 4186.01},
    {17.32, 34.65, 69.30, 138.59, 277.18, 554.37, 1108.73, 2217.46, 4434.92},
    {18.35,	36.71, 73.42, 146.83, 293.66, 587.33, 1174.66, 2349.32, 4698.64},
    {19.45 	38.89 	77.78 	155.56 	311.13,  622.25, 1244.51, 2489.02, 4978.03},
};
*/

void speaker_init();

void speaker_tone(float frequency);

void speaker_no_tone();

void speaker_loop();

#endif
#ifndef ADC_H
#define ADC_H

#include "../lib/defines.h"
#include "memory_map.h"
#include <stdlib.h>
#include <stdio.h>

uint8_t ADC_read_channel(CHANNEL c);

#endif
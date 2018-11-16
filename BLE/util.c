#include "util.h"


void util_delay_ms(int ms)
{
    int i = 2000*ms;
	while (i--) { asm(""); }; 
}

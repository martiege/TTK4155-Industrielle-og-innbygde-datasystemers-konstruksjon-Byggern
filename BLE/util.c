#include "util.h"


void util_delay_ms(int ms)
{
	// based on emperic data, multiply 
	// ms by 2000 to delay for ms
	// milliseconds
    int i = 2000 * ms;
	while (i--) { asm(""); }; 
}

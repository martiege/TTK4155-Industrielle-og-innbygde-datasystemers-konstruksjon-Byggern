#include <stdint.h>
#include "gpiote.h"
#include "ppi.h"
#include "timer.h"


int main(){
	// Configure GPIOTE
	GPIOTE->CONFIG[0] = 3 | (22 << 8) | (3 << 16) | (1 << 20);

	// Configure PPI
	PPI->PPI_CH[0].EEP = (uint32_t)&(TIMER0->COMPARE[0]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[0]);
	PPI->PPI_CH[1].EEP = (uint32_t)&(TIMER0->COMPARE[1]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[0]);

	// Configure timer
	TIMER0->MODE = 0;			// Timer mode
	TIMER0->BITMODE = 3;		// 32 bit
	TIMER0->SHORTS = (1 << 1);	// Clear on CC[1]
	TIMER0->PRESCALER = 9;		// 31250 Hz
	TIMER0->CC[1] = 625;
	TIMER0->CC[0] = 62;
	TIMER0->START = 1;

	// Enable PPI
	PPI->CHENSET = (1 << 0) | (1 << 1);

	while(1){
		int delay = 10000;
		while(--delay);
	}

	return 0;
}

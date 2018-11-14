#include <stdint.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure GPIOTE
	GPIOTE->CONFIG[0] = 3 | (13 << 8) | (3 << 16) | (1 << 20);
	GPIOTE->CONFIG[1] = 3 | (14 << 8) | (3 << 16) | (1 << 20);
	GPIOTE->CONFIG[2] = 3 | (15 << 8) | (3 << 16) | (1 << 20);
	GPIOTE->CONFIG[3] = 1 | (17 << 8) | (2 << 16);

	// Configure PPI
	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[3]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[0]);
	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[3]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[1]);
	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[3]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[2]);
	PPI->CHENSET = (1 << 0) | (1 << 1) | (1 << 2);

	while(1){
		// Do nothing
		int i = 10000;
		while(--i);
	}

	return 0;
}

#include <stdint.h>
#include <stdlib.h>
#include "uart.h"
#include "gpio.h"

int main(){

	uart_init();

	GPIO->PIN_CNF[17] = 0; // Button A
	GPIO->PIN_CNF[26] = 0; // Button B

	while(1){
		if(!(GPIO->IN & (1 << 17))){
			uart_send('A');
			uart_send('\n');
			uart_send('\r');
		}
		if(!(GPIO->IN & (1 << 26))){
			uart_send('B');
			uart_send('\n');
			uart_send('\r');
		}
	}

	return 0;
}

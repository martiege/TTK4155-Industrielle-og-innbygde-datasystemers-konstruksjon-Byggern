#include <stdint.h>
#include "uart.h"
#include "gpio.h"


int main(){

	uart_init();

	int led_on = 0;
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	char letter;
	while(1){
		letter = uart_read();
		if(letter != '\0'){
			uart_send(letter);
			uart_send('\n');
			uart_send('\r');

			led_on ^= 1;
			if(led_on){
				GPIO->OUTSET = (7 << 13);
			}
			else{
				GPIO->OUTCLR = (7 << 13);
			}
		}
	}

	return 0;
}

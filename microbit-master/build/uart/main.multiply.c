#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"

ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

int main(){
	uart_init();

	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int a;
	int b;
	int state = 0;

	while(1){
		a = 0;
		b = 0;

		while(state == 0){
			if(!(GPIO->IN & (1 << 17))){
				a++;
				while(!(GPIO->IN & (1 << 17)));
			}
			if(!(GPIO->IN & (1 << 26))){
				state = 1;
				while(!(GPIO->IN & (1 << 26)));
			}
		}
		b++;
		while(state == 1){
			if(!(GPIO->IN & (1 << 26))){
				b++;
				while(!(GPIO->IN & (1 << 26)));
			}
			if(!(GPIO->IN & (1 << 17))){
				state = 0;
				while(!(GPIO->IN & (1 << 17)));
			}
		}

		iprintf("%d * %d = %d\n\r", a, b, a * b);
	}

	return 0;
}

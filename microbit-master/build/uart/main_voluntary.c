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

ssize_t _read(int fd, void *buf, size_t count){
	char *str = (char *)(buf);
	char letter;

	do {
		letter = uart_read();
	} while(letter == '\0');

	*str = letter;
	return 1;
}

int main(){
	uart_init();

	int a;
	int b;

	while(1){
		iprintf("Enter two numbers:\n\r");
		scanf("%d %d", &a, &b);
		iprintf("%d * %d = %d\n\r", a, b, a * b);
	}

	return 0;
}

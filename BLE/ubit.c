#include "ubit.h"


void ubit_led_matrix_init(){
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	} 
}


void ubit_led_matrix_turn_on(){
	GPIO->OUTSET = (1 << 13 | 1 << 14 | 1 << 15);
}

void ubit_led_matrix_turn_off(){
	GPIO->OUTCLR = (1 << 13 | 1 << 14 | 1 << 15);
}

void ubit_buttons_init(){
	GPIO->PIN_CNF[BUTTON_A_PIN] = 0;
	GPIO->PIN_CNF[BUTTON_B_PIN] = 0;
}

int ubit_button_press_a(){
	return !(GPIO->IN & (1 << BUTTON_A_PIN));
}

int ubit_button_press_b(){
	return !(GPIO->IN & (1 << BUTTON_B_PIN));
}

void ubit_uart_init(){
	GPIO->PIN_CNF[UART_TXD_PIN] = 1;
	GPIO->PIN_CNF[UART_RXD_PIN] = 0;

	UART->PSELRTS = 0xFFFFFFFF;
	UART->PSELCTS = 0xFFFFFFFF;

	UART->PSELTXD = UART_TXD_PIN;
	UART->PSELRXD = UART_RXD_PIN;

	UART->BAUDRATE = 0x00275000;

	UART->ENABLE = 4;

	/* This library does not implement receiving, */
	/* but STARTRX is necessary for correct UART*/
	/* peripheral behavior */
	UART->STARTRX = 1;
}

void ubit_helper_put_char(char letter)
{
	UART->STARTTX = 1;
	UART->TXD = letter;
	while(!UART->TXDRDY);
	UART->TXDRDY = 0;
	UART->STOPTX = 1;
}

char ubit_helper_get_char()
{
	if (!UART->RXDRDY)
	{
		return '\0';
	}

	char received;
	UART->RXDRDY = 0;
	received = UART->RXD;
	return received;
}

static void ubit_helper_put_int(int number){
	if(number == 0){
		ubit_helper_put_char('0');
		return;
	}

	int digits = 0;
	int reverse = 0;
	int has_negative_sign = 0;

	if(number < 0){
		has_negative_sign = 1;
		number = -number;
	}

	while(number != 0){
		reverse *= 10;
		reverse += (number % 10);
		number /= 10;
		digits++;
	}

	if(has_negative_sign){
		ubit_helper_put_char('-');
	}

	while(reverse != 0){
		char digit_char = (char)((reverse % 10) + '0');
		ubit_helper_put_char(digit_char);
		reverse /= 10;
		digits--;
	}

	while(digits != 0){
		ubit_helper_put_char('0');
		digits--;
	}
}

static int ubit_helper_get_requested_width(char * p_letter){
	int requested_width = 0;
	while(*p_letter != 'd'){
		requested_width *= 10;
		requested_width += (*p_letter - '0');
		p_letter++;
	}
	return requested_width;
}

static int ubit_helper_get_required_width(int number){
	if(number == 0){
		return 1;
	}

	int required_width = 0;
	if(number < 0){
		required_width++;
	}
	while(number != 0){
		required_width++;
		number /= 10;
	}

	return required_width;
}

void ubit_uart_print(char * p_format, ...){
	va_list p_arg;
	va_start(p_arg, p_format);

	int number;
	int requested_width;
	int required_width;
	char * p_letter;

	for(p_letter = p_format; *p_letter != '\0'; p_letter++){
		if(*p_letter != '%'){
			ubit_helper_put_char(*p_letter);
			continue;
		}

		number = va_arg(p_arg, int);
		p_letter++;

		requested_width = ubit_helper_get_requested_width(p_letter);
		required_width = ubit_helper_get_required_width(number);

		while(*p_letter != 'd'){
			p_letter++;
		}

		while(required_width < requested_width){
			ubit_helper_put_char(' ');
			required_width++;
		}

		ubit_helper_put_int(number);
	}

	va_end(p_arg);
}

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdio.h>

// initialize USART
void USART_Init(unsigned int ubrr);

// send one character
void USART_Transmit(unsigned char data);

// recieve one character
char USART_Receive();

// put_char - function, also adds a '\r' if '\n' is transmitted
int put_char(char data, FILE* file);

// get_char - function
int get_char(FILE* file);

#endif

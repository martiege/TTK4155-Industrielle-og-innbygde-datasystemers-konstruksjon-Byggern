#ifndef UART_H
#define UART_H
#include <avr/io.h>
//#define F_CPU 1000000UL
#include <stdio.h>

void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

char USART_Receive();

void USART_Send(unsigned char data);

//FILE* fdevopen(int(*)(char,FILE *) put, int(*)(FILE *) get); 

int put_char(char data, FILE* file);

int get_char(FILE* file);

#endif

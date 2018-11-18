#ifndef UART_H
#define UART_H



#include <avr/io.h>
#include <stdio.h>


/* USART module for ATmega162 and ATmega 2560*/

void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

char USART_Receive();

void USART_Send(unsigned char data);

int put_char(char data, FILE* file);

int get_char(FILE* file);

#endif
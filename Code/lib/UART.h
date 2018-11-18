#ifndef UART_H
#define UART_H



#include <avr/io.h>
#include <stdio.h>


/* UART module for ATmega162 and ATmega 2560*/

void UART_Init(unsigned int ubrr);

void UART_Transmit(unsigned char data);

char UART_Receive();

void UART_Send(unsigned char data);

int put_char(char data, FILE* file);

int get_char(FILE* file);

#endif

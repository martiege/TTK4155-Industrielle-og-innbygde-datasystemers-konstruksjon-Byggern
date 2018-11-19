#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/****
Serial Peripheral Interface (SPI) Master module

Implements the SPI master for the nRF51 series

Using pins 		16, 21, 22 and 23
Breakoutboard	16, 15, 14 and 13


*****/


void SPI_init();

void SPI_cs(uint8_t i);

uint8_t SPI_MasterTransmit(char cData);


#endif
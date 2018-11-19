#ifndef SPI_H
#define SPI_H


void SPI_init();

void SPI_cs(uint8_t i);

uint8_t SPI_MasterTransmit(char cData);


#endif
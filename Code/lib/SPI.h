#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/*Communication between MCU and CAN controller*/

void SPI_MasterInit();

uint8_t SPI_MasterTransmit(char cData);



#endif
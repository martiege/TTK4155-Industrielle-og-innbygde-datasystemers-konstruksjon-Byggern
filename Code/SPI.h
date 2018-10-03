#ifndef SPI_H
#define SPI_H

/*Communication between MCU and CAN controller*/

void SPI_MasterInit();

void SPI_MasterTransmit(char cData);



#endif
#include "spi_slave.h"
#include "ubit.h"

#define SPI_SLAVE ((NRF_SPI_SLAVE_REG*)0x40004000)


typedef struct {
	uint32_t RESERVED0[9];
	// Tasks
	uint32_t ACQUIRE;
	uint32_t RELEASE;
	// Events
	uint32_t RESERVED1[54];
	uint32_t END;
	uint32_t RESERVED2[8];
	uint32_t ACQUIRED;
	// Registers
	uint32_t RESERVED3[53];
	uint32_t SHORTS;
	uint32_t RESERVED4[63];
	uint32_t INTEN;
	uint32_t INTENSERT;
	uint32_t INTENCLR;
	uint32_t RESERVED5[61];
	uint32_t SEMSTAT;
	uint32_t RESERVED6[15];
	uint32_t STATUS;
	uint32_t RESERVED7[47];
	uint32_t ENABLE;
	uint32_t RESERVED8[1];
	uint32_t PSELSCK;
	uint32_t PSELMISO;
	uint32_t PSELMOSI;
	uint32_t PSELCSN;
	uint32_t RESERVED9[7];
	uint32_t RXDPTR;
	uint32_t MAXRX;
	uint32_t AMOUNTRX;
	uint32_t RESERVED10[1];
	uint32_t TXDPTR;
	uint32_t MAXTX;
	uint32_t AMOUNTTX;
	uint32_t DEF;
	uint32_t RESERVED11[24];
	uint32_t ORC;
} NRF_SPI_SLAVE_REG;

// CPU PINS				// breakout board pins
#define SPI_SS_PIN   16 // pin 16
#define SPI_MOSI_PIN 21 // pin 15
#define SPI_MISO_PIN 22 // pin 14
#define SPI_SCK_PIN  23 // pin 13


void spi_init()
{
	//GPIO->
	
	SPI_SLAVE->PSELSCK = SPI_SCK_PIN;
	SPI->PSELCSN = SPI_SS_PIN;
	SPI->PSELMOSI = SPI_MOSI_PIN;
	SPI->PSELMISO = SPI_MISO_PIN; // hight impedance when not SS
	
	
}


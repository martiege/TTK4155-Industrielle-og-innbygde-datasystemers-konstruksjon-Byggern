#include "SPI.h"
#include "ubit.h"
#include <stdint.h>

#define SPI ((NRF_SPI_REG*)0x40003000)

// CPU PINS				// breakout board pins
#define SPI_SS_PIN   16 // pin 16
#define SPI_MOSI_PIN 21 // pin 15
#define SPI_MISO_PIN 22 // pin 14
#define SPI_SCK_PIN  23 // pin 13


typedef struct {
	uint32_t RESERVED0[66];
	// Events
	uint32_t READY;
	// Registers
	uint32_t RESERVED1[125];
	uint32_t INTEN;
	uint32_t INTENSET;
	uint32_t INTENCLR;
	uint32_t RESERVED2[125];
	uint32_t ENABLE;
	uint32_t RESERVED3[1];
	uint32_t PSELSCK;
	uint32_t PSELMOSI;
	uint32_t PSELMISO;
	uint32_t RESERVED4[1];
	uint32_t RXD;
	uint32_t TXD;
	uint32_t RESERVED5[1];
	uint32_t FREQUENCY;
	uint32_t RESERVED6[11];
	uint32_t CONFIG;
} NRF_SPI_REG;


void SPI_init()
{
	// output 1, input 0
	GPIO->PIN_CNF[SPI_SCK_PIN]  = 1;
	GPIO->PIN_CNF[SPI_MOSI_PIN] = 1;
	GPIO->PIN_CNF[SPI_MISO_PIN] = 0;
	GPIO->PIN_CNF[SPI_SS_PIN]   = 1;
	
	SPI->PSELSCK  = SPI_SCK_PIN;
	SPI->PSELMOSI = SPI_MOSI_PIN;
	SPI->PSELMISO = SPI_MISO_PIN;
	
	// as with node 1 and 2, set frequency
	// to f_cpu / 16
	SPI->FREQUENCY = 0x10000000;
	
	SPI->ENABLE = 1;
}
#include <stdint.h>

#define GPIO ((NRF_GPIO_REG*)0x50000000)
#define UART ((NRF_UART_REG*)0x40002000)
/* #define NRF_GPIOTE ((NRF_GPIOTE_Type*)0x40006000) */

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REG;

typedef struct {
	// Tasks
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t RESERVED0[3];
	volatile uint32_t SUSPEND;
	// Events
	volatile uint32_t RESERVED1[56];
	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t RESERVED2[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t RESERVED3;
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED4[7];
	volatile uint32_t RXTO;
	// Registers
	volatile uint32_t RESERVED5[110];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED6[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED7[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED8;
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED9;
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED10[17];
	volatile uint32_t CONFIG;
} NRF_UART_REG;

/* typedef struct{ */
/* 	volatile uint32_t OUT[4];			// Tasks */
/* 	volatile uint32_t RESERVED0[60]; */
/* 	volatile uint32_t IN[4];			// Events */
/* 	volatile uint32_t RESERVED1[27]; */
/* 	volatile uint32_t PORT;				// Event, multiple pins */
/* 	volatile uint32_t RESERVED2[96]; */
/* 	volatile uint32_t INTEN;			// Interrupt control */
/* 	volatile uint32_t INTENSET;			// Enable interrupt */
/* 	volatile uint32_t INTENCLR;			// Disable interrupt */
/* 	volatile uint32_t RESERVED3[129]; */
/* 	volatile uint32_t CONFIG[4];		// Channel config */
/* } NRF_GPIOTE_Type; */

void init_uart(){
	UART->PSELRTS = 0xFFFFFFFF; // Disable RTS
	UART->PSELCTS = 0xFFFFFFFF; // Disable CTS

	UART->PSELTXD = 24;
	UART->PSELRXD = 25;

	UART->BAUDRATE = 0x00275000; // 9600 baud

	GPIO->PIN_CNF[24] |= 1; // Configure output
	GPIO->PIN_CNF[25] &= ~1; // Configure input

	UART->ENABLE = 4; // 4: Enable, 0: Disable
}

int main(){
	init_uart();

	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	char letter = 'A';

	volatile int sleep = 0;
	while(1){
		/* GPIO->OUTSET = (7 << 13); */

		/* sleep = 1000000; */
		/* while(--sleep); */

		/* GPIO->OUTCLR = (7 << 13); */

		/* sleep = 1000000; */
		/* while(--sleep); */

		/* while(!UART->TXDRDY); */
		UART->TXD = letter;
		UART->STARTTX = 1;
		while(!UART->TXDRDY);
		sleep = 10000;
		while(--sleep);
		if(++letter > 'Z'){
			letter = 'A';
			UART->TXD = '\r';
			UART->STARTTX;
			while(!UART->TXDRDY);
			sleep = 10000;
			while(--sleep);

			UART->TXD = '\n';
			UART->STARTTX;
			while(!UART->TXDRDY);
			sleep = 10000;
			while(--sleep);

			GPIO->OUTSET = (7 << 13);
			sleep = 1000000;
			while(--sleep);
			GPIO->OUTCLR = (7 << 13);
		}
		GPIO->OUTCLR = (7 << 13);
	}
	return 0;
}

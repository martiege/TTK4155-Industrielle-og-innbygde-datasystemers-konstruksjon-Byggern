#ifndef UBIT_H
#define UBIT_H

#include <stdint.h>
#include <stdarg.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)
#define UART ((NRF_UART_REGS*)0x40002000)
#define BUTTON_A_PIN 17
#define BUTTON_B_PIN 26
#define UART_TXD_PIN 24
#define UART_RXD_PIN 25

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
} NRF_GPIO_REGS;

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
} NRF_UART_REGS;

void ubit_led_matrix_init();

void ubit_led_matrix_turn_on();

void ubit_led_matrix_turn_off();


void ubit_buttons_init();

int ubit_button_press_a();

int ubit_button_press_b();


void ubit_uart_init();

void ubit_helper_put_char(char letter);

char ubit_helper_get_char();

void ubit_uart_print(char * p_format, ...);

#endif

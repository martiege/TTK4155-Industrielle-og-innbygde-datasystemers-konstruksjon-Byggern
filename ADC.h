#ifndef UART_H
#define UART_H

enum CHANNEL {CH1 = 0b0100, CH2 = 0b0101, CH3 = 0b0110, CH4 = 0b0111};

int ADC_read_channel(CHANNEL c);

#endif

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ubit.h"
#include "util.h"

#include "SPI.h"
#include "MCP.h"
#include "MCP2515.h"
#include "CAN.h"

#include "bluetooth.h"
#include "pwm.h"
#include "speaker.h"

int main(){
	ubit_uart_init();
	ubit_led_matrix_init();

	ubit_uart_print("spi\n\r");
	SPI_init();
	ubit_uart_print("mcp\n\r");
	MCP_reset();
	ubit_uart_print("can\n\r");
	CAN_init();
	ubit_uart_print("done\n\r");

	/*
	CAN_message m;
	m.id = BLUETOOTH_MSG;
	m.length = 1;
	m.data[0] = 15;
	while (1)
	{
		ubit_uart_print("ID: %d\n\r", m.id);
		CAN_send(&m);
		util_delay_ms(200);
	}
	*/
	
	util_delay_ms(1000);
	ubit_led_matrix_turn_off();


	uint32_t err_code = 0;

	err_code = bluetooth_init();
	if (err_code) { ubit_uart_print("BLE Enable error code: %d\n\r", err_code);	}

	err_code = bluetooth_gap_advertise_start();
	if (err_code) { ubit_uart_print("Advertise start error code: %d\n\r", err_code); }

	err_code = bluetooth_gatts_start();
	if (err_code) { ubit_uart_print("GATTS start error code: %d\n\r", err_code); }
	
	bluetooth_serve_forever();
	return 0;
}

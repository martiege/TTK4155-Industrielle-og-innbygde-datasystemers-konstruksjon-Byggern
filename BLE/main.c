#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ubit.h"

#include "bluetooth.h"
#include "pwm.h"


int main(){
	ubit_uart_init();
	ubit_led_matrix_init();

	pwm_init(9, 31250, 15625);

	pwm_set_frequency(1);

	ubit_led_matrix_turn_off();

	uint32_t err_code = 0;

	err_code = bluetooth_init();
	if (err_code) { ubit_uart_print("BLE Enable error code: %d\n\r", err_code);	}

	err_code = bluetooth_gap_advertise_start();
	if (err_code) { ubit_uart_print("Advertise start error code: %d\n\r", err_code); }

	err_code = bluetooth_gatts_start();
	if (err_code) { ubit_uart_print("newGATTS start error code: %d\n\r", err_code);	}
	
	bluetooth_serve_forever();
	return 0;
}

#include <stdint.h>
#include <stdlib.h>
#include "uart.h"
#include "twi.h"
#include "utility.h"
#include "accel.h"
#include "ubit_led_matrix.h"

int main(){
	uart_init();
	twi_init();
	accel_init();
	ubit_led_matrix_init();

	int * data_buffer;
	data_buffer = (int *)malloc(3 * sizeof(int));

	int x_accel, y_accel, z_accel;
	int x_dot, y_dot;
	while (1){
		accel_read_x_y_z(data_buffer);

		x_accel = data_buffer[0];
		y_accel = data_buffer[1];
		z_accel = data_buffer[2];

		x_dot = x_accel / 50;
		y_dot = -y_accel / 50;

		ubit_led_matrix_light_only_at(x_dot, y_dot);

		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r",
				x_accel, y_accel, z_accel);

	}

	return 0;
}

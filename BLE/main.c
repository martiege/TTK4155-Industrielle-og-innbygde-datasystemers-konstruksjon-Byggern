#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ubit.h"
#include "util.h"

#include "bluetooth.h"
#include "pwm.h"
#include "speaker.h"

//ta vekk:
//#include "tone_defs.h"

int main(){
	ubit_uart_init();
	ubit_led_matrix_init();
	
	pwm_init(9, 31250);
	speaker_init();

	speaker_tone(1760);
	//speaker_tone(1760);
    util_delay_ms(1000);
    speaker_no_tone();

	speaker_play_song(MARIO);

	speaker_no_tone();
	

	util_delay_ms(1000);
	//speaker_tone(1760);
    //util_delay_ms(1300/12);
	//
	//speaker_tone(1976);
    //util_delay_ms(1000/12);
    //speaker_no_tone();
    //util_delay_ms(1300/12);
	//
	//speaker_tone(2093);
    //util_delay_ms(1000/5);
    //speaker_no_tone();




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

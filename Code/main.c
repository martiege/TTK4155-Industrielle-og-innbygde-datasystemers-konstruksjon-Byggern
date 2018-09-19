#define F_CPU 4915200UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "SRAM_test.h"
#include "ADC.h"
#include "user_input.h"
#include "OLED.h"
#include "memory_map.h"

int main()
{
    USART_Init(MYUBRR);

    MCUCR |= (1 << SRE);
    SFIOR |= (1 << XMM2);

    SRAM_test();

    OLED_init();

    printf("Starting...\n");
    
    while(1)
    {
        /*
        Position p = user_input_joystick_position();
        Slider s = user_input_slider_position();
        printf("\n");
        printf("Joystick X: %d\n", p.X);
        printf("Joystick Y: %d\n", p.Y);
        printf("Slider Right: %d\n", s.right);
        printf("Slider Left: %d\n", s.left);
        printf("Button: %d\n", user_input_joystick_button());
        user_input_joystick_print_direction(user_input_joystick_direction());
        */

        //printf("Hei\n");
        memory_write_oled_data(0xaf);

        _delay_ms(1);

    }

    printf("Stopping...\n");

}

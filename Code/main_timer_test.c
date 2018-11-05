#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <avr/pgmspace.h>
#include "SPI.h"
#include "MCP.h"
#include "CAN.h"
#include "input_com.h"
#include "timer.h"

#ifdef __AVR_ATmega162__
    #include "user_input.h"
    #include "ADC.h"
    #include "SRAM_test.h"
#elif __AVR_ATmega2560__
    #include "pwm.h"
    #include "ADC_internal.h"
    //#include <avr/interrupt.h> //bare for den cli(); testen
#endif

void func1()
{
    printf("Func 1!\n");
}

void func2()
{
    printf("Func 2!\n");
}

int main()
{
    /*Init start*/
    USART_Init(MYUBRR);

    MCUCR |= (1 << SRE);
    //SFIOR |= (1 << XMM2);

    printf("Starting...\n");

    SPI_MasterInit();
    CAN_init();
    input_com_init();

    timer_init(1, func1);
    timer_init(2, func2);

    timer_set_period(1000, 1);
    timer_set_period(2000, 2);

    timer_start(1);
    timer_start(2);
    
    #ifdef __AVR_ATmega2560__
        // receive
        // CAN_message rec;
        USER_DATA us;

        pwm_init();
        ADC_internal_init();
        
        int angle = 0;

        while (1)
        {
            printf("ATmega2560\n");
            //printf("Goal: %d\n", ADC_internal_status());
            
            _delay_ms(200);   
        }

    #elif __AVR_ATmega162__
        // send
        
        //SFIOR |= (1 << XMM2);
        SFIOR |= (1 << XMM2);

        SRAM_test();

        //Position p = user_input_joystick_position();
        //CAN_message joystick_values;
        //int8_t d[8] = { p.X, p.Y };
        USER_DATA us;
        
        while (1)
        {
            printf("ATmega162\n");
            us = input_com_send();
        
            _delay_ms(100);
            //printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            
        }
        

    #endif
    printf("Stopping...\n");


}


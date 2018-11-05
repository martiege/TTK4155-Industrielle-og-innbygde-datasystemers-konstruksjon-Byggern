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
    #include "goal.h"
#endif

int main()
{
    /*Init start*/
    USART_Init(MYUBRR);
    MCUCR |= (1 << SRE);

    printf("Starting...\n");

    SPI_MasterInit();
    CAN_init();
    input_com_init();

    
    #ifdef __AVR_ATmega2560__
        pwm_init();
        ADC_internal_init();
        goal_init();
        
        int angle = 0;

        while (1)
        {
            //printf("ATmega2560\n");
            printf("Goal: %d\n", goal_get_goals());
            _delay_ms(200);   
        }

    #elif __AVR_ATmega162__
        SFIOR |= (1 << XMM2);
        SRAM_test();
        
        while (1)
        {
            printf("ATmega162\n");
            _delay_ms(100);            
        }
        

    #endif
    printf("Stopping...\n");


}


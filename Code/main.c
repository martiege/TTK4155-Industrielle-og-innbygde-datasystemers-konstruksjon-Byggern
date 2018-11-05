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
    #include "DAC.h"
    #include "TWI_Master.h"
    //#include <avr/interrupt.h>
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
        TWI_Master_Initialise();

        int DAC_val = 0;

        while (1)
        {
            //printf("ATmega2560\n");

            if(DAC_val < 256 ) DAC_val+=10;
            else DAC_val = 0;
            printf("DAC: %d\n", DAC_val);
            DAC_send_pos(DAC_val);
        
            _delay_ms(1000);   
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


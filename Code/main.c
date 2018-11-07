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
    #include "motor.h"
    #include "TWI_Master.h"
#endif

int main()
{
    /*Init start*/
    USART_Init(MYUBRR);
    MCUCR |= (1 << SRE);

    printf("Starting...\n");

    SPI_MasterInit();
    MCP_reset(); 
    //printf("CANSTAT: %x\n", MCP_read(MCP_CANSTAT)); 

    CAN_init();
    input_com_init();

    
    #ifdef __AVR_ATmega2560__
        pwm_init();
        ADC_internal_init();
        goal_init();
        
        TWI_Master_Initialise();
        motor_init();
        USER_DATA us;
        while (1)
        {   
            //printf("ATmega2560\n");
            //us = input_com_recieve();
            //pwm_set_angle(us.pos_X);
            //motor_set_speed(us.pos_Y);
            //printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            //printf("Goal: %d\n", goal_get_goals());
            //printf("Pos: %d\n", motor_encoder_read());
            //DAC_send_speed(70);
            motor_set_speed(70);
            _delay_ms(1000);   
            motor_set_speed(-70);
            //PORTH &= ~(1 << PH1);
           _delay_ms(1000);
            //DAC_send_speed(0);
            //PORTH |= (1 << PH1);
            //_delay_ms(500);  
        }

    #elif __AVR_ATmega162__
        SFIOR |= (1 << XMM2);
        //SRAM_test();
        USER_DATA us;

        

        while (1)
        {
            printf("ATmega162\n");
            printf("ADC: %d\n", memory_read_ADC(CH2));
            //us = input_com_send();
            //printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            _delay_ms(500);            
        }
        

    #endif
    printf("Stopping...\n");


}


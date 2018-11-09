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
    #include "OLED.h"
    #include "OLED_SRAM.h"
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
    CAN_init();
    input_com_init();

    
    #ifdef __AVR_ATmega2560__
        pwm_init();
        ADC_internal_init();
        goal_init();
        
        TWI_Master_Initialise();
        motor_init();
        controller_init(3, 0, 0);

        USER_DATA us;
        while (1)
        {   
            printf("ATmega2560\n");
            //us = input_com_recieve();
            //pwm_set_angle(us.pos_X);
            //motor_set_speed(us.pos_Y);
            //printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            printf("Goal: %d\n", goal_get_goals());
            printf("Pos: %d\n", motor_encoder_read());
            printf("Ref: %d\n", controller_get_reference());
            printf("Speed: %d\n", motor_speed);
            //DAC_send_speed(70);
            //motor_set_speed(70);
            _delay_ms(1000);   
            //motor_set_speed(-70);
            //PORTH &= ~(1 << PH1);
            //_delay_ms(1000);
            //DAC_send_speed(0);
            //PORTH |= (1 << PH1);
            //_delay_ms(500);  
            
        }

    #elif __AVR_ATmega162__
        SFIOR |= (1 << XMM2);

        SRAM_test();

        OLED_init();

/*
        for (int page = 0; page < 8; ++page)
        {
            for (int col = 0; col < 128; ++col)
            {
                printf("%d ", OLED_SRAM_read(page, col));
            }
            printf("\n");
        }
*/
        USER_DATA us;
        
        /*
        OLED_print("Line 1\n");
        _delay_ms(500); 
        OLED_print("Line 2\n");
        _delay_ms(500); 

        

        OLED_print("Line 3\n");
        _delay_ms(500); 
        OLED_print("Line 4\n");
        _delay_ms(500); 
        OLED_print("Line 5\n");
        _delay_ms(500); 
        OLED_print("Line 6\n");
        _delay_ms(500); 
        OLED_print("Line 7\n");
        _delay_ms(500); 
        OLED_print("Line 8\n");
        _delay_ms(500); 

        

        for (int page = 0; page < 8; ++page)
        {
            for (int col = 0; col < 128; ++col)
            {
                printf("%d ", OLED_SRAM_read(page, col));
            }
            printf("\n");
        }    
        */    

        while (1)
        {
            
            printf("ATmega162\n");
            //printf("ADC: %d\n", memory_read_ADC(CH2));
            us = input_com_send();
            printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            
            _delay_ms(100);            
            
        }
        

    #endif
    printf("Stopping...\n");


}


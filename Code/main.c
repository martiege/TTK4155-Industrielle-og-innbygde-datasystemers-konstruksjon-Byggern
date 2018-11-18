#include "lib/defines.h"
#include "lib/UART.h"

/*
#include "lib/SPI.h"
#include "lib/MCP.h"
#include "lib/CAN.h"
#include "lib/input_com.h"
#include "lib/timer.h"
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
*/

#ifdef __AVR_ATmega162__
    #include "node1/node1.h"
/*
    #include "node1/user_input.h"
    #include "node1/ADC.h"
    #include "node1/SRAM_test.h"
    #include "node1/OLED.h"
    #include "node1/OLED_SRAM.h"
*/
#elif __AVR_ATmega2560__
    #include "node2/node2.h"
/*
    #include "node2/pwm.h"
    #include "node2/ADC_internal.h"
    #include "node2/goal.h"
    #include "node2/motor.h"
    #include "node2/TWI_Master.h"
    #include "node2/solenoid.h"
    #include "node2/controller.h"
*/
#endif

int main()
{
    /*Init start*/
    /*
    UART_Init(MYUBRR);
    MCUCR |= (1 << SRE);

    printf("Starting...\n");

    SPI_MasterInit();
    MCP_reset();
    CAN_init();
    input_com_init();
    */
    
    #ifdef __AVR_ATmega2560__
        pwm_init();
        ADC_internal_init();
        goal_init();
        solenoid_init();
        
        TWI_Master_Initialise();
        motor_init();
        controller_init(4, 0, 4);
        speaker_init();
        //controller_init(1, 0, 0);

        USER_DATA us;
        //speaker_tone(1000);
        //speaker_loop();

        while (1)
        {   
            //printf("CANSTAT: %x\n", MCP_read(MCP_CANSTAT));
            //printf("ATmega2560\n");
            //us = input_com_recieve();
            //pwm_set_angle(us.pos_X);
            //motor_set_speed(us.pos_Y);
            //printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            //printf("Goal: %d\n", goal_get_goals());
            //printf("Pos: %d\n", motor_encoder_read());
            //printf("Ref: %d\n", controller_get_reference());
            //DAC_send_speed(70);
            //motor_set_speed(70);
            _delay_ms(100);   
            controller_update();
            //motor_set_speed(-70);
            //PORTH &= ~(1 << PH1);
            //DAC_send_speed(0);
            //PORTH |= (1 << PH1);
            //_delay_ms(500);  
            
        }

    #elif __AVR_ATmega162__
        node1_init();
        node1_main();
    /*
        SFIOR |= (1 << XMM2);

        SRAM_test();

        OLED_init();
        */

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
        //USER_DATA us;
        
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
       /*
        while (1)
        {
            
            printf("ATmega162\n");
            //printf("ADC: %d\n", memory_read_ADC(CH2));
            //printf("CANCTRL %x\n", MCP_read(MCP_CANCTRL));
            //us = input_com_send();
            //printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            char input = USART_Receive();
            if (input)
            {
                printf("bluetooth: %x\n", input);
            }
            
            _delay_ms(100);            
            
        }
        */

    #endif
    printf("Stopping...\n");


}


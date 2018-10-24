#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <avr/pgmspace.h>
#include "SPI.h"
#include "MCP.h"
#include "CAN.h"
#include "input_com.h"

#ifdef __AVR_ATmega162__
    #include "user_input.h"
    #include "ADC.h"
    #include "SRAM_test.h"
#elif __AVR_ATmega2560__
    #include "timer.h"
#endif

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
    
    #ifdef __AVR_ATmega2560__
        // receive
        // CAN_message rec;
        USER_DATA us;

        timer_init();
        
        while (1)
        {
            printf("ATmega2560\n");
            _delay_ms(20);

            set_duty_cycle(50);

            us = input_com_recieve();
            //printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            //_delay_ms(1000);
            //CAN_receive(&rec);

            //printf("X: %d\tY: %d\n", (int8_t)rec.data[0], (int8_t)rec.data[1]);
            
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
        
            _delay_ms(1000);
            printf("X: %d\tY: %d\tL: %d\tR: %d\tB: %d\n", us.pos_X, us.pos_Y, us.sli_left, us.sli_right, us.but);
            
            //p = user_input_joystick_position();
            //printf("X: %d\tY: %d\n", p.X, p.Y);
            
            /*
            d[0] = p.X;
            d[1] = p.Y;

            joystick_values.id = 0;
            joystick_values.length = 8;
            for (int i = 0; i < 8; ++i)
            {
                joystick_values.data[i] = (uint8_t)d[i];
            }            

            printf("X: %d\tY: %d\n", joystick_values.data[0], joystick_values.data[1]);


            CAN_send(&joystick_values);
            //MCP_request_to_send();

            _delay_ms(1000);
            */
        }
        

    #endif
    /*init end*/
    //uint8_t *d = { 2 };
    /*
    uint8_t *e = { 3 };

    CAN_message m;
    m.id = 5;
    m.length = 1;
    m.data = d;

    CAN_message n;
    */

    //CAN_send(&m);
    //m.id = 2;
    /*
    int ctr = 0;
    while(1)
    {
        _delay_ms(1000);
        CAN_send(&m);
        _delay_ms(500);
        CAN_receive(&n);
        _delay_ms(500);
        printf("ID: %x\n", n.id);
        

        //printf("Register: %x\n", MCP_read(MCP_CANSTAT));

        //MCP_reset();
        // printf("status %x\n", MCP_read_status());
        // printf("CANINTF %x\n", MCP_read(MCP_CANINTF));
 
        
       // printf("status %x ctr: %d \n", MCP_read_status(), ctr++);
        printf("status: %d\n", MCP_read_status());
        _delay_ms(5);
        CAN_receive(&n);
        printf("ID: %d\n", n.id);

        _delay_ms(500);
        
        if (MCP_read(MCP_CANINTF) & 1)
        {
            printf("rec\n");
        }
        //m.id = 1;
        CAN_send(&m);
        //m.id = 2;
        
    }*/

    printf("Stopping...\n");


}


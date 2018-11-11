#include "CAN.h"
#include "MCP.h"
#include "MCP2515.h"
#include "defines.h"

#ifdef __AVR_ATmega2560__
    #include "pwm.h"
    #include "motor.h"
    #include "controller.h"
    #include "solenoid.h"
#endif

#include <util/delay.h>
#include <avr/interrupt.h>

#define MCP_TXB0SIDH	0x31
#define MCP_TXB0SIDL	0x32
#define MCP_TXB0DLC     0x35
#define MCP_TXB0D0  	0x36

#define MCP_RXB0SIDH	0x61
#define MCP_RXB0SIDL	0x62
#define MCP_RXB0DLC     0x65
#define MCP_RXB0D0  	0x66

void CAN_init()
{
    MCP_reset(); 

    received = 0;

    uint8_t mode = MCP_read(MCP_CANSTAT);
    if (mode & MODE_MASK != MODE_CONFIG)
    {
        MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
    }

    CAN_intr_init();    

    // loopback mode
    // MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
    // normal mode
    MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

}


void CAN_intr_init()
{
    #ifdef __AVR_ATmega2560__
        DDRD &= ~(1 << PD2);
    #endif

    cli();

    INTRREG  |= (1 << INTRSEL);
    INTRSET  |= (1 << INTRSC);

    sei();

    received = 0;
    
    //send interrupt
    //MCP_bit_modify(MCP_CANINTE, 0x03, 0x00);
    //MCP_bit_modify(MCP_CANINTE, 0x03, 0xFF);

    //Receive interrupt
    MCP_bit_modify(MCP_CANINTE, 0x01, 0x00);
    MCP_bit_modify(MCP_CANINTE, 0x01, 0xFF);


    // reset interrupt
    MCP_bit_modify(MCP_CANINTF, 0x01, 0x00);

    if (MCP_read(MCP_CANINTF) & 1)
    {
        received = 1;
    }

  
}

ISR(INT2_vect)
{
    //printf("INTR start\n");
    if (MCP_read(MCP_CANINTF) & 1)
    {
        received = 1;
    }
    MCP_bit_modify(MCP_CANINTF, 0x01, 0x00);
    
    // TODO
    // HANDLE EACH ID SEPERATELY

    CAN_message m;
    
    CAN_receive(&m);

    if (m.id == INPUT_COM)
    {
        #ifdef __AVR_ATmega2560__
            cli();
            pwm_set_angle((int8_t)m.data[0]);
            //pwm_set_angle((int16_t)m.data[3] - 128);
            //controller_set_reference(0);
            controller_set_reference(m.data[3]*40);
            //motor_set_speed((int8_t)m.data[0]);
            if (m.data[4] && !(solenoid_get_shot()))
            {
                //printf("Start shot\n");
                solenoid_shoot();
                //_delay_ms(50);
                //solenoid_clear_shot();
                //printf("Stop shot\n");
            }
            else if (!m.data[4])
            {
                solenoid_clear_shot();
            }
            sei();
        #endif
    }

    //printf("INTR done\n");
}


void CAN_send(const CAN_message* msg)
{

    while (MCP_read(MCP_TXB0CTRL) & (1 << 3)){ _delay_ms(1); }

    MCP_write(MCP_TXB0SIDH, msg->id >> 3);
    MCP_write(MCP_TXB0SIDL, msg->id << 5);
    MCP_write(MCP_TXB0DLC, msg->length & 0x0F);

    for (int i = 0; i < msg->length; ++i)
    {
        MCP_write(MCP_TXB0D0 + i, (msg->data)[i]);
    }

    /*Ready to transmit, highest priority*/
    MCP_bit_modify(MCP_TXB0CTRL, 0x0B, 0xFF);

}


void CAN_receive(CAN_message* msg)
{
    //printf("rec func entered\n"); //works!
    //if !INT pin

    if ((MCP_read(MCP_CANINTF) & 1) || received) //(received)
    {
        //printf("Recieved!\n");
        // read id
        msg->id  = MCP_read(MCP_RXB0SIDH) << 3;
        msg->id |= MCP_read(MCP_RXB0SIDL) >> 5;

        // read length
        msg->length = MCP_read(MCP_RXB0DLC) & 0x0F;

        // read data
        for (int i = 0; i < msg->length; ++i)
        {
            (msg->data)[i] = MCP_read(MCP_RXB0D0 + i);
        }

        /*Clear CANINTF.RX0IF after read*/
        MCP_bit_modify(MCP_CANINTF, 0x01, 0);

        // clear flags
        received = 0;
    }  
    
}
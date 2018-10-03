#include "CAN.h"
#include "MCP.h"



void CAN_init()
{
    MCP_reset(); 

    uint8_t mode = MCP_read(MCP_CANSTAT);
    if (mode & MODE_MASK != MODE_CONFIG)
    {
        MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
    }

    
    // loopback mode
    MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);

    //noe mer??
}


void CAN_send(CAN_message data)
{
    //SOF bit
    //arbitration field:
        //11 bit identifier
        //remote transmittion request bit (1=data frame, 0=remote frame)
    //control field:
        //1 bit identifier extension - "must be dominant to specify a standard frame"
        //RB0 = 1
        //4 bit data length code (0-8 bytes)
    //data field


}


void CAN_receive()
{

}
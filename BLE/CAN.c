#include "CAN.h"
#include "MCP.h"
#include "MCP2515.h"

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

    uint8_t mode = MCP_read(MCP_CANSTAT);
    if ((mode & MODE_MASK) != MODE_CONFIG)
    {
        MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
    }
		
    // loopback mode
    // MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
    // normal mode
    MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

}

void CAN_send(const CAN_message* msg)
{
    while (MCP_read(MCP_TXB0CTRL) & (1 << 3));

    MCP_write(MCP_TXB0SIDH, msg->id >> 3);
    MCP_write(MCP_TXB0SIDL, msg->id << 5);
    MCP_write(MCP_TXB0DLC, msg->length & 0x0F);

    for (int i = 0; i < msg->length; ++i)
    {
        MCP_write(MCP_TXB0D0 + i, (msg->data)[i]);
    }

    // ready to transmit, highest priority
    MCP_bit_modify(MCP_TXB0CTRL, 0x0B, 0xFF);
}


void CAN_receive(CAN_message* msg)
{
    // if received
    if ((MCP_read(MCP_CANINTF) & 1)) 
    {
        //Read id
        msg->id  = MCP_read(MCP_RXB0SIDH) << 3;
        msg->id |= MCP_read(MCP_RXB0SIDL) >> 5;

        //Read length
        msg->length = MCP_read(MCP_RXB0DLC) & 0x0F;

        //Read data
        for (int i = 0; i < msg->length; ++i)
        {
            (msg->data)[i] = MCP_read(MCP_RXB0D0 + i);
        }

        //Clear CANINTF.RX0IF after read
        MCP_bit_modify(MCP_CANINTF, 0x01, 0);
    }  
}
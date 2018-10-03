#ifndef CAN_H
#define CAN_H

typedef struct CAN_message
{
    uint8_t id;
    uint8_t length;
    uint8_t* data; //0-8 bytes

} CAN_message;



void CAN_init();


void CAN_send(CAN_message data);


void CAN_receive();



#endif
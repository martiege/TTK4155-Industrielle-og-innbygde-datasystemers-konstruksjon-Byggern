#ifndef INPUT_COM_H
#define INPUT_COM_H

#include "CAN.h"

/*
#ifdef __AVR_ATmega162__
    typedef struct USER_DATA 
    { 
        Position pos;
        Slider sli;
        uint8_t but;
    } USER_DATA;
#endif
*/


typedef struct USER_DATA 
{ 
    int8_t  pos_X;
    int8_t  pos_Y;
    uint8_t sli_left;
    uint8_t sli_right;
    uint8_t but;
} USER_DATA;

static USER_DATA user_data;


static CAN_message input_message;


void input_com_init();

#ifdef __AVR_ATmega162__
USER_DATA input_com_send();
#endif

USER_DATA input_com_recieve(/*CAN_message &msg*/);



#endif
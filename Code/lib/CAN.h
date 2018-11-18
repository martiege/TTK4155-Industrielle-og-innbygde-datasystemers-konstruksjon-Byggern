#ifndef CAN_H
#define CAN_H

#include <stdint.h>

typedef struct CAN_message
{
    uint8_t id;
    uint8_t length;
    uint8_t data[8]; //0-8 bytes

} CAN_message;

typedef enum CAN_ID { INPUT_COM, CONTROLLER_SETTINGS, GAME_DIFFICULTY } CAN_ID;

static uint8_t received;


void CAN_init();


void CAN_intr_init();


void CAN_send(const CAN_message* msg);


void CAN_receive(CAN_message* msg);

#endif
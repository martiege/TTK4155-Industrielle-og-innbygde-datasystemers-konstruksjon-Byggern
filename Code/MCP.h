#ifndef MCP_H
#define MCP_H

#include <stdio.h>
#include "MCP2515.h"

/* MCP2515 manipulation */ 



uint8_t MCP_read(uint8_t adr);


void MCP_write(uint8_t data);


void MCP_request_to_send();


uint8_t MCP_read_status();


void MCP_bit_modify(uint8_t adr, uint8_t mask, uint8_t data);


void MCP_reset();

#endif
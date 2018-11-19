#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdint.h>

/**************************************
Bluetooth module

Implements the Bluetooth module for 
the nRF51 series.

Adds functionality to recieve Bluetooth
messages. Sends those values through
the CAN bus to the rest of the nodes.

The functions implemented are:

	bluetooth_init()
	
		Initializes the Bluetooth 
		module. Returns any error
		values according to the BLE
		standard. 
		
	bluetooth_gap_advertise_start()
	
		Start the Bluetooth GAP 
		advertisment and set 
		advertise data. Returns any 
		error values according to the 
		BLE standard. 
		
	bluetooth_gatts_start()
		
		Start GATTS, allow for 
		recieving Bluetooth messages. 
		Returns any error values 
		according to the BLE standard. 
		
	bluetooth_serve_forever()
	
		Continously looks for 
		Bluetooth messages, and send
		them over the CAN bus. Also 
		reads all CAN messages and 
		discards them, as we do not
		send any messages to the 
		Microbit. 


**************************************/

uint32_t bluetooth_init();

uint32_t bluetooth_gap_advertise_start();

uint32_t bluetooth_gatts_start();

void bluetooth_serve_forever();

#endif

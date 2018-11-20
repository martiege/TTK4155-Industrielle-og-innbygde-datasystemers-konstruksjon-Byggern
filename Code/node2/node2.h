#ifndef NODE2_H
#define NODE2_H

/***************************************
Node 2 module

Implements main functionality of node 2
of the system in this lab.

The functions implemented are:

	node2_init()
	
		Initializes the modules used in 
		Node 2. 
		
	node2_main()
	
		Runs the main code for Node 2. 
		Updates the controller module 
		every 100 ms. All other modules
		are implemented through
		interrupts. 

***************************************/

void node2_init();

void node2_main();

#endif
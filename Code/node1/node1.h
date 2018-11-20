#ifndef NODE1_H
#define NODE1_H

#include <stdint.h>

/***************************************
Node 1 module

Implements main functionality of node 1 
of the system in this lab.

Also implements a "life" system, 
which is used to set the diffuculty 
of the game and count the goals scored
against the player. 

The functions implemented are:

	decrease_lives()
	
		Decreases the number of lives
		by 1. 
		
	get_number_of_lives()
	
		Returns the remaining number of
		lives.
		
	set_number_of_lives(uint8_t n_lives)
	
		Sets the number of lives to the
		value of the parameter n_lives. 
		
	node1_init()
	
		Initializes the modules used in 
		Node 1. 
		
	node1_main()
	
		Excecutes the code for Node 1.
		
***************************************/

void decrease_lives();
uint8_t get_number_of_lives();
void set_number_of_lives(uint8_t n_lives);

void node1_init();

void node1_main();

#endif
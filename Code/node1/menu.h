#ifndef MENU_H
#define MENU_H

/*************************************
Menu module

Implements ability to use 
OLED as a menu to the system. 

Includes several submenus, 
which are called from menu_main.

A menu is defined by an array of
strings, start and length. Start 
defines the start of the interactive
part of the menu, length the length
of the interactive part of the menu. 

The functions implemented are:

	menu_print(const char **menu, 
			   int start, int length, 
			   int cursorpos)
			   
		Prints the strings in the 
		parameter menu, and adds 
		a cursor position '*'
		at the line cursorpos. 
		
	menu_select(const char **menu, 
				int start, int length)
		
		Selects the line the user 
		presses the joystick button 
		on, and returns that line
		number. 
		
	menu_main()
	
		Runs the main menu, see the
		menydiagram for all features. 

*************************************/

void menu_print(const char **menu, int start, int length, int cursorpos);

int menu_select(const char **menu, int start, int length);

void menu_welcome();

void menu_main();

#endif
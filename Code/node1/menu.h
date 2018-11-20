#ifndef MENU_H
#define MENU_H



void menu_print(const char **menu, int start, int length, int cursorpos);

int menu(const char **menu, int start, int length);

void menu_welcome();

void menu_main();

#endif
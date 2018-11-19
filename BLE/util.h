#ifndef UTIL_H
#define UTIL_H

/*************************************************
util.h
Utility library

Implements an approximate delay function for nRF51

util_delay_ms(int ms) occupies the CPU
for approximatly ms milliseconds. 

**************************************************/ 

void util_delay_ms(int ms);


#endif
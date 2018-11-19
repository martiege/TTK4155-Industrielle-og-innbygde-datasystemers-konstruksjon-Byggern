#ifndef UTIL_H
#define UTIL_H

/****************************************
util.h
Utility library for nRF51

Implements an approximate delay function

util_delay_ms(int ms) occupies the CPU
for approximatly ms milliseconds. 
****************************************/ 

void util_delay_ms(int ms);


#endif
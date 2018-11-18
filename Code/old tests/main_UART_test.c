#include <avr/io.h>

//#define F_CPU 1000000UL
#define F_CPU 4915200UL
#include <util/delay.h>
#include "UART.h"
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


int main()
{
    UART_Init(MYUBRR);
    
    //char* q = "a";
    
    while(1){
      _delay_ms(1000);
      UART_Transmit('\n');
      UART_Transmit('\r');
      
      if (PORTA == 0xFF)
      {
          PORTA = 0;
          UART_Transmit('A');
          printf(", HEY STUDASS ;)");
      }
      else
      {
          PORTA = 0xFF;
          UART_Transmit('B');   
          //char* port_A = PORTA;
          printf("%x%s",PORTA, "s4ever?");
      }
      
      //char hey = UART_Receive();
      //_delay_ms(1000);
      //UART_Transmit(hey);
        
    }

    
    
    return 0;
   
}

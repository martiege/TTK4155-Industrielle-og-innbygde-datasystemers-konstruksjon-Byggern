#include <avr/io.h>

//#define F_CPU 1000000UL
#define F_CPU 4915200UL
#include <util/delay.h>
#include "UART.h"
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


int main()
{
    USART_Init(MYUBRR);
    
    //char* q = "a";
    
    while(1){
      _delay_ms(1000);
      USART_Transmit('\n');
      USART_Transmit('\r');
      
      if (PORTA == 0xFF)
      {
          PORTA = 0;
          USART_Transmit('A');
          printf(", HEY STUDASS ;)");
      }
      else
      {
          PORTA = 0xFF;
          USART_Transmit('B');   
          //char* port_A = PORTA;
          printf("%x%s",PORTA, "s4ever?");
      }
      
      //char hey = USART_Receive();
      //_delay_ms(1000);
      //USART_Transmit(hey);
        
    }

    
    
    return 0;
   
}

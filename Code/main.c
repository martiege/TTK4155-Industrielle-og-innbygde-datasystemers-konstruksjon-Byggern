#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <avr/pgmspace.h>

int main()
{
    USART_Init(MYUBRR);
    
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

}


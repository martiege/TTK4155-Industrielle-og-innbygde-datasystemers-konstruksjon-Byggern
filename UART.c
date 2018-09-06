//#include <avr/io.h>
#include "UART.h"

void USART_Init(unsigned int ubrr)
{
    
    /*Set baud rate*/
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    
    /*Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
    
	/* Set the UCSRA register to zero */
    UCSR0A = 0 << U2X0;
    
    /*Enable receiver and transmitter*/
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
	/* link to put_char and get_char functions */ 
    fdevopen(put_char, get_char);
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */ 
    while ( !( UCSR0A & (1 << UDRE0)) ) {}
    /* Put data into buffer, sends the data */
    
    UDR0 = data;

}

char USART_Receive()
{
    /* Wait for the data to be recieved */
    while ( !(UCSR0A & (1 << RXC0)) ) {}
    
    /* Get and return recieved data from buffer */ 
    return UDR0;
}


int put_char(char data, FILE* file){
	/* Also add '\r' if endline is transmitted */
    if(data=='\n'){
        USART_Transmit('\r');
    }
	
	/* Transmit the character */
    USART_Transmit(data);
    return 0;

}

int get_char(FILE* file){
	/* Recieves the character */
    return USART_Receive();

}

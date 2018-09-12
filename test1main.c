#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>


int main()
{
    PORTA = 0xFF;
    
    while(1){
        _delay_ms(1000);
        if (PORTA == 0xFF)
        {
            PORTA = 0;
        }
        else
        {
            PORTA = 0xFF;
        }
        
    }
    
    
    return 0;
   
}

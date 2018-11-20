#include "lib/defines.h"
#include "lib/UART.h"


#ifdef __AVR_ATmega162__
    #include "node1/node1.h"
#elif __AVR_ATmega2560__
    #include "node2/node2.h"
    #include "node2/controller.h"
    #include <util/delay.h>
#endif

int main()
{
    
    #ifdef __AVR_ATmega2560__
        node2_init();    

        while (1)
        { 
            _delay_ms(100);   
            controller_update();            
        }

    #elif __AVR_ATmega162__
        
		node1_init();
        node1_main();

    #endif
    printf("Stopping...\n");


}


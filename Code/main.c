#include "lib/defines.h"
#include "lib/UART.h"


#ifdef __AVR_ATmega162__
    #include "node1/node1.h"
#elif __AVR_ATmega2560__
    #include "node2/node2.h"
#endif

int main()
{
    
    #ifdef __AVR_ATmega2560__
	
        node2_init();    
		node2_main();

    #elif __AVR_ATmega162__
        
		node1_init();
        node1_main();

    #endif
    printf("Stopping...\n");


}


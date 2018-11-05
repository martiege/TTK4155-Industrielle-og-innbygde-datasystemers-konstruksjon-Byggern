#include "DAC.h"
#include "TWI_Master.h"

void DAC_send_pos(uint8_t val)
{
    /*package with slave address 0101000, output = DAC0, value*/
    unsigned char package[3] = {(0b0101 << 4 ), 0x00 , val};
    printf("start\n");
    for (int i = 0; i < 3 ; i++)
    {
        printf("%d\n", package[i]);
    }
    printf("\n");
    TWI_Start_Transceiver_With_Data(package, 3);

}


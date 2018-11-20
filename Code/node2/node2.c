#include "node2.h"
#include "../lib/defines.h"
#include "../lib/UART.h"
#include "../lib/SPI.h"
#include "../lib/MCP.h"
#include "../lib/CAN.h"
#include "../lib/input_com.h"

#include "pwm.h"
#include "ADC_internal.h"
#include "goal.h"
#include "solenoid.h"
#include "TWI_Master.h"
#include "motor.h"
#include "controller.h"


void node2_init()
{
    UART_Init(MYUBRR);
    MCUCR |= (1 << SRE);

    printf("Initializing...\n");

    SPI_MasterInit();
    MCP_reset();
    CAN_init();    

    input_com_init();

    pwm_init();
    ADC_internal_init();
    solenoid_init();
    TWI_Master_Initialise();
    motor_init();
    controller_init(4, 0, 4);

    printf("Initialized!\n");
}
#include <sys/platform.h>
//#include <drivers/uart/adi_uart.h>
//#include <drivers/pwr/adi_pwr.h>
#include "uart.h"
#include <drivers/rtc/adi_rtc.h>
#include <string.h>
#include "adi_initialize.h"
#include "uart_sleep.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

//uart variables
//uint8_t uartMemory[ADI_UART_BIDIR_MEMORY_SIZE];
//uint32_t uart_hErrors;
//ADI_UART_HANDLE uartDevice;
//uint8_t* rx_buffer;
//uint8_t rx_buffer_size = 0;
char* cmd;




int main(int argc, char *argv[])
{
	cmd = (char*)calloc(5, sizeof(char));

	//setup
	adi_initComponents();

	//power setup
	ADI_PWR_RESULT pwrResult  = powerSetup();
	if(pwrResult)
	{
		DEBUG_MESSAGE("%i", pwrResult);
		return pwrResult;
	}

	//uart setup
	ADI_UART_RESULT uartResult = uartSetup(9600);
	if(uartResult)
	{
		DEBUG_MESSAGE("%i", uartResult);
		return uartResult;
	}

	do
	{
		adi_pwr_EnterLowPowerMode(ADI_PWR_MODE_SHUTDOWN , NULL, 0);
		if(uart_available==4)
		{
			cmd = (char*)uartReadBuffer(4);
			DEBUG_MESSAGE("Buffer is empty");
			uartWriteBuffer((uint8_t*)cmd, 5);
		}
	} while(strcmp(cmd, "exit") != 0);

	adi_uart_Close(uartDevice);

	return 0;
}


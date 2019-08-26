#include <sys/platform.h>
#include "uart.h"
#include <drivers/rtc/adi_rtc.h>
#include <string.h>
#include "adi_initialize.h"
#include "uart_sleep.h"
#include "common.h"
#include <stdio.h>


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
		if(uart_available()==4)
		{
			uartReadBuffer((uint8_t*)cmd, 4);
			uartWriteBuffer((uint8_t*)cmd, 5);
		}
	} while(strcmp(cmd, "exit") != 0);

	adi_uart_Close(uartDevice);

	return 0;
}


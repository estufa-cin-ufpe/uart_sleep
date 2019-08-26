#include <sys/platform.h>
#include "uart.h"
#include <drivers/rtc/adi_rtc.h>
#include <string.h>
#include "adi_initialize.h"
#include "uart_sleep.h"
#include "pwr.h"
#include "common.h"
#include <stdio.h>

char* cmd;
uint8_t available_buffer;

int main(int argc, char *argv[])
{
	cmd = (char*)calloc(256, sizeof(char));

	//setup
	adi_initComponents();

	//power setup
	ADI_PWR_RESULT pwrResult  = pwrSetup();
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
		if((available_buffer = uart_available()) > 0)
		{
			uartReadBuffer((uint8_t*)cmd, available_buffer);
			uartWriteBuffer((uint8_t*)cmd, available_buffer);
		}
	} while(strcmp(cmd, "exit") != 0);

	adi_uart_Close(uartDevice);

	return 0;
}


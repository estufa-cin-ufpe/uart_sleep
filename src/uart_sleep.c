#include <sys/platform.h>
#include <drivers/uart/adi_uart.h>
#include <drivers/pwr/adi_pwr.h>
#include <drivers/rtc/adi_rtc.h>
#include <string.h>
#include "adi_initialize.h"
#include "uart_sleep.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

//uart variables
uint8_t uartMemory[ADI_UART_BIDIR_MEMORY_SIZE];
ADI_UART_HANDLE uartDevice;
uint8_t* rx;
bool rxa = true;

ADI_PWR_RESULT powerSetup()
{
	ADI_PWR_RESULT result;

	if((result = adi_pwr_Init()) != ADI_PWR_SUCCESS)
	{
		return result;
	}
	if((result = adi_pwr_SetClockDivider(ADI_CLOCK_HCLK, 1u)) != ADI_PWR_SUCCESS)
	{
		return result;
	}
	if((result = adi_pwr_SetClockDivider(ADI_CLOCK_PCLK, 1u)) != ADI_PWR_SUCCESS)
	{
		return result;
	}

	return ADI_PWR_SUCCESS;
}

ADI_UART_RESULT uartSetup(uint32_t baudrate, const ADI_CALLBACK cbf)
{
	ADI_UART_RESULT result;

	if((result = adi_uart_Open(0, ADI_UART_DIR_BIDIRECTION, uartMemory, ADI_UART_BIDIR_MEMORY_SIZE, &uartDevice)) != ADI_UART_SUCCESS)
	{
		return result;
	}
	if((result = adi_uart_RegisterCallback(uartDevice, cbf, NULL)) != ADI_UART_SUCCESS)
	{
		return result;
	}
	if((result = adi_uart_SetConfiguration(uartDevice, ADI_UART_NO_PARITY, ADI_UART_ONE_STOPBIT, ADI_UART_WORDLEN_8BITS)) != ADI_UART_SUCCESS)
	{
		return result;
	}

	switch(baudrate)
	{
		case 9600:
			result = adi_uart_ConfigBaudRate(uartDevice, 22, 3, 1734, 3);
			break;

		case 19200:
			result = adi_uart_ConfigBaudRate(uartDevice, 11, 3, 1735, 3);
			break;

		case 38400:
			result = adi_uart_ConfigBaudRate(uartDevice, 17, 1, 501, 3);
			break;

		case 57600:
			result = adi_uart_ConfigBaudRate(uartDevice, 7, 2, 31, 3);
			break;

		case 115200:
			result = adi_uart_ConfigBaudRate(uartDevice, 7, 2, 31, 2);
			break;

		case 230400:
			result = adi_uart_ConfigBaudRate(uartDevice, 7, 2, 31, 1);
			break;

		case 460800:
			result = adi_uart_ConfigBaudRate(uartDevice, 7, 2, 31, 0);
			break;

		default:
			return ADI_UART_INVALID_PARAMETER;
	}
	if(result)
	{
		return result;
	}

	return ADI_UART_SUCCESS;
}

static void callback(void* pAppHandle, uint32_t nEvent, void* pArg)
{
	switch (nEvent)
	{
		case ADI_UART_EVENT_TX_BUFFER_PROCESSED:
			break;
		case ADI_UART_EVENT_RX_BUFFER_PROCESSED:
			DEBUG_MESSAGE("Exiting sleep mode.");
			adi_pwr_ExitLowPowerMode(NULL);
			DEBUG_MESSAGE("%s", rx);
			rxa = true;
			break;
		default:
			break;
	}
}

int main(int argc, char *argv[])
{
		rx = (uint8_t*)calloc(5, sizeof(uint8_t));
		//setup
		adi_initComponents();

		//power setup
		ADI_PWR_RESULT pwrResult  = powerSetup();
		if(pwrResult)
		{
			return pwrResult;
		}

		//uart setup
		ADI_UART_RESULT uartResult = uartSetup();
		if(uartResult)
		{
			return uartResult;
		}

		do
		{
			if(rxa)
			{
				rxa = false;
				adi_uart_SubmitRxBuffer(uartDevice, rx, 4, 0u);
				adi_pwr_EnterLowPowerMode(ADI_PWR_MODE_SHUTDOWN , NULL, 0);
				DEBUG_MESSAGE("Exited sleep mode.");
			}
		} while(strcmp(rx, "exit") != 0);

		adi_uart_Close(uartDevice);

	    return 0;
}


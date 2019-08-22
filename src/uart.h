#ifndef UART_H_
#define UART_H_

#ifndef ADI_UART_H
#include <drivers/uart/adi_uart.h>
#endif

#ifndef ADI_PWR_H
#include <drivers/pwr/adi_pwr.h>
#endif

#ifndef _STDLIB_H_
#include <stdlib.h>
#endif

#define uart_available rx_buffer_size

//uart control variables
extern uint8_t uartMemory[ADI_UART_BIDIR_MEMORY_SIZE];
extern uint32_t uart_hErrors;
extern ADI_UART_HANDLE uartDevice;
extern uint8_t* rx_buffer;
extern uint8_t rx_buffer_size;

void callback(void* pAppHandle, uint32_t nEvent, void* pArg);

ADI_PWR_RESULT powerSetup();

ADI_UART_RESULT uartSetup(uint32_t baudrate);

uint8_t* uartRead();

uint8_t* uartReadBuffer(uint8_t len);

ADI_UART_RESULT uartWrite(uint8_t byte);

ADI_UART_RESULT uartWriteBuffer(uint8_t* buffer, uint8_t len);

ADI_UART_RESULT async_uartWrite(uint8_t byte);

ADI_UART_RESULT async_uartWriteBuffer(uint8_t* buffer, uint8_t len);

#endif /* UART_H_ */

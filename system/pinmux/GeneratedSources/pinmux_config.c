/*
 **
 ** Source file generated on Agosto 17, 2019 at 19:53:44.	
 **
 ** Copyright (C) 2011-2019 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in 
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** UART0 (Tx, Rx, UART_SOUT_EN)
 ** RTC (RTC_SS1)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** P0_10, P0_11, P0_12, P2_11
 */

#include <sys/platform.h>
#include <stdint.h>

#define UART0_TX_PORTP0_MUX  ((uint32_t) ((uint32_t) 1<<20))
#define UART0_RX_PORTP0_MUX  ((uint32_t) ((uint32_t) 1<<22))
#define UART0_UART_SOUT_EN_PORTP0_MUX  ((uint32_t) ((uint32_t) 3<<24))
#define RTC_RTC_SS1_PORTP2_MUX  ((uint32_t) ((uint32_t) 3<<22))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX Registers
 */
int32_t adi_initpinmux(void) {
    /* PORTx_MUX registers */
    *((volatile uint32_t *)REG_GPIO0_CFG) = UART0_TX_PORTP0_MUX | UART0_RX_PORTP0_MUX
     | UART0_UART_SOUT_EN_PORTP0_MUX;
    *((volatile uint32_t *)REG_GPIO2_CFG) = RTC_RTC_SS1_PORTP2_MUX;

    return 0;
}


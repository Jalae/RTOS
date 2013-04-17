#ifndef UARTDRV
#define UARTDRV

#include "myincludes.h"


extern void initUART(UART_MODULE port, uint32_t baud);
extern void vUartPutC(UART_MODULE port, char c);
extern void vUartPutStr(UART_MODULE port, char * s, int len);
#endif

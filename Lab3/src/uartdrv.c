#include "uartdrv.h"

void initUART(UART_MODULE port, uint32_t baud)
{
    UARTSetDataRate(port, (uint32_t)configPERIPHERAL_CLOCK_HZ, baud);
    UARTEnable(port, UART_ENABLE_FLAGS(UART_PERIPHERAL|UART_TX));
}

void vUartPutC(UART_MODULE port, char c)
{
    while(!UARTTransmitterIsReady(port))
    {
        vTaskDelay(2);
    }
    UARTSendDataByte(port, c);
}

void vUartPutStr(UART_MODULE port, char * s, int len)
{
    int i = 0;
    for(i; i < len; i++)
    {
        vUartPutC(port, s[i]);
    }
}



#include "myUART.h"
#include "uartdrv.h"
void UARTTask(void *pvParameters)
{
    xTaskParameter_t *pxTaskParameter;
    pxTaskParameter = (xTaskParameter_t *) pvParameters;
    char string[50];
    initUART(UART1, 9600);
    while(1)
    {
        xQueueReceive(pxTaskParameter->uart, (void *)&string, portMAX_DELAY);
        int len = strlen(string);
        vUartPutStr(UART1, string, len);
    }
}

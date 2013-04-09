
#include "myled.h"

void taskTECHNOPARTY(void *pvParameters)
{
    xTaskParameter_t *pxTaskParameter;
    portTickType xStartTime;

    /* The parameter points to an xTaskParameters_t structure. */
    pxTaskParameter = (xTaskParameter_t *) pvParameters;
    int statepattern[4];
    switch(pxTaskParameter->function)
    {
        case 1:
            statepattern [0] = 0;
            statepattern [1] = 1;
            statepattern [2] = 2;
            statepattern [3] = 4;
            break;
        case 2:
            statepattern [0] = 0;
            statepattern [1] = 4;
            statepattern [2] = 2;
            statepattern [3] = 1;
            break;
        case 3:
            statepattern [0] = 2;
            statepattern [1] = 4;
            statepattern [2] = 2;
            statepattern [3] = 1;
            break;
    }
    int currentstate = 0;
    while (1)
    {
        /* Note the time before entering the while loop.  xTaskGetTickCount()
        is a FreeRTOS API function. */
        xStartTime = xTaskGetTickCount();

        while ((xTaskGetTickCount() - xStartTime) < pxTaskParameter->xToggleRate);
        mPORTDClearBits(BIT_0 | BIT_1 | BIT_2);
        if(statepattern[currentstate])
        mPORTDToggleBits(statepattern[currentstate]);
        currentstate = currentstate + 1;
        if(currentstate>=4)
            currentstate = 0;
    }
}

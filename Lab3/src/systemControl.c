
#include "systemControl.h"

char msg[3][50] = { "LED 0 IS NOW ACTIVE\r\n",
                    "LED 1 IS NOW ACTIVE\r\n",
                    "LED 2 IS NOW ACTIVE\r\n"};

void systemControlTask(void *pvParameters)
{
    xTaskParameter_t *pxTaskParameter;
    pxTaskParameter = (xTaskParameter_t *) pvParameters;
    started = 1;
    while(1)
    {
        if(mybtngetstatus(1))
        {
            int up = 1;
            vQueueSendToBack(pxTaskParameter->queue, &up, 0);
        }
        if(mybtngetstatus(2))
        {
            int down = 2;
            vQueueSendToBack(pxTaskParameter->queue, &down, 0);
        }
        if(mybtngetstatus(3))
        {
            vQueueSendToBack(pxTaskParameter->uart,msg[pxTaskParameter->function],0);
            vTaskResume(pxTaskParameter->next);
            vTaskSuspend(NULL);
        }
        vTaskDelay(100);
    }
}

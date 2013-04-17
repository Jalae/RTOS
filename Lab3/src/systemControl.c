
#include "systemControl.h"

char msg[3][50] = { "LED 0 IS NOW ACTIVE\r\n",
                    "LED 1 IS NOW ACTIVE\r\n",
                    "LED 2 IS NOW ACTIVE\r\n"};

void systemControlTask(void *pvParameters)
{
    xTaskParameter_t *pxTaskParameter;
    pxTaskParameter = (xTaskParameter_t *) pvParameters;
    while(1)
    {
        if(mybtngetstatus(1))
        {
            int up = 1;
            xQueueSendToBack(pxTaskParameter->queue, &up, 0);
        }
        if(mybtngetstatus(2))
        {
            int down = 2;
            xQueueSendToBack(pxTaskParameter->queue, &down, 0);
        }
        if(mybtngetstatus(3))
        {
            xQueueSendToBack(pxTaskParameter->uart,msg[pxTaskParameter->function],0);
            vTaskResume(pxTaskParameter->next);
            vTaskSuspend(NULL);
        }
        vTaskDelay(100);
    }
}

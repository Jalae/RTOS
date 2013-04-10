
#include "systemControl.h"

#define MAXTASKS 3

static int numTasks;
static xTaskHandle pvTasks[MAXTASKS];
static int started;
static const xTaskParameter_t params[MAXTASKS] = {
                                            {0, (400 / portTICK_RATE_MS)} ,
                                            {1, (400 / portTICK_RATE_MS)} ,
                                            {2, (400 / portTICK_RATE_MS)}
                                            };
void systemControlTask(void *pvParameters)
{
    started = 1;
    while(1)
    {
        if(mybtngetstatus(1))
        {
            if(numTasks < MAXTASKS)
            {
                
                xTaskCreate(myledblink,
                        "Blink",
                        configMINIMAL_STACK_SIZE,
                        (void *) &(params[numTasks]),
                        1,
                        &(pvTasks[numTasks] ) );
                numTasks = numTasks + 1;
            }
        }
        if(mybtngetstatus(2))
        {
            if(numTasks > 0)
            {
                numTasks = numTasks - 1;
                vTaskDelete(pvTasks[numTasks]);
            }
        }
        if(mybtngetstatus(3))
        {
            int i;
            if(started)
                for(i = 0; i < numTasks; i++)
                    vTaskSuspend(pvTasks[i]);
            else
                for(i = 0; i < numTasks; i++)
                    vTaskResume(pvTasks[i]);

            started = !started;
        }
        vTaskDelay(100);
    }
}

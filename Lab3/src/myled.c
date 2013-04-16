
#include "myled.h"
#define LED_MAXRATE 1000
#define LED_MINRATE 200
#define LED_INCVAL 50
#define LED_DEFVAL 500
void myledblink(void *pvParameters)
{
    xTaskParameter_t *pxTaskParameter;
    pxTaskParameter = (xTaskParameter_t *) pvParameters;
    portTickType xToggleRate = LED_DEFVAL;
    while(1)
    {
        if(uxQueueMessagesWaiting(pxTaskParameter->queue) > 0)
        {
            int val;
            xQueueRecieve(pxTaskParameter->queue, (void)&val, 0);
            switch(val)
            {
                case 1:
                        xToggleRate = (xToggleRate+LED_INCVAL > LED_MAXRATE ? LED_MAXRATE : xToggleRate+LED_INCVAL);
                        break;
                case 2:
                        xToggleRate = (xToggleRate-LED_INCVAL < LED_MINRATE ? LED_MINRATE : xToggleRate-LED_INCVAL);
                        break;
                default:
            }
        }
        mPORTDToggleBits(1<<pxTaskParameter->function);
        vTaskDelay(xToggleRate);
    }
}

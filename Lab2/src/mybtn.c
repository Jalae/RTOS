
#include "mybtn.h"
static const int buttonport[3] = {6,7,13};
static int old[3];
int mybtngetstatus(int btn)
{
    btn = btn - 1;
    int val1 = PORTD;
    int val2;
    val2 = val1 & (1 << buttonport[btn]);
    if (val2 == old[btn])
    {
        return 0;
    }
    vTaskDelay(10);
    val1 = PORTD;
    old[btn] = val1 = val1 & (1 << buttonport[btn]);
    return !(val1 && val2);
    
}

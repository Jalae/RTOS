
#include "mybtn.h"
static const int buttonport[] = {6,7,13};

int mybtngetstatus(int btn)
{
    btn = btn - 1;
    int val1 = LATD;
    int val2;
    val2 = val1 & 1 << buttonport[btn];
    vTaskDelay(10);
    val1 = LATD;
    val1 = val1 & 1 << buttonport[btn];
    return val1 && val2;
}

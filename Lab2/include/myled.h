#ifndef MYLEDDEF
#define MYLEDDEF

#include "myincludes.h"

extern void taskTECHNOPARTY(void *pvParameters);

extern void myledblink(void *pvParameters);

typedef struct xTASK_PARAMETER {
    uint16_t function;                   /* The number of the LED to toggle. */
    portTickType xToggleRate;               /* The rate at which the LED should be toggle. */
} xTaskParameter_t;

#endif

#ifndef LAINPROJ1

#define LAINPROJ1
/* Hardware include. */
#include <xc.h>

/* Standard includes. */
#include <stdint.h>
#include <plib.h>

/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"

/*-----------------------------------------------------------*/
/* Functions used by this demo.                              */
/*-----------------------------------------------------------*/
/* A task that toggles an LED at a fixed frequency.  This time, the LED to
toggle and the rate at which the LED is toggled are passed into the task
using the task parameter.  This allows the same task function to be used to
create multiple tasks that each behave slightly differently. */
extern void taskTECHNOPARTY(void *pvParameters);

extern void myledblink(void *pvParameters)
/*-----------------------------------------------------------*/
/* Structures used by this demo.                             */
/*-----------------------------------------------------------*/
/* The structure that is passed into tasks that use the prvToggleAnLED() task function.
 The structure lets the task know which LED to toggle, and at which rate. */
typedef struct xTASK_PARAMETER {
    uint16_t function;                   /* The number of the LED to toggle. */
    portTickType xToggleRate;               /* The rate at which the LED should be toggle. */
} xTaskParameter_t;

#endif

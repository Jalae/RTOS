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

typedef struct xTASK_PARAMETER {
    uint16_t function;                   /* The number of the LED to toggle. */
    xQueueHandle queue;               /* The rate at which the LED should be toggle. */
} xTaskParameter_t;

#include "systemControl.h"

#endif

/*
    FreeRTOS V7.1.1 - Copyright (C) 2012 Real Time Engineers Ltd.


 ***************************************************************************
 *                                                                       *
 *    FreeRTOS tutorial books are available in pdf and paperback.        *
 *    Complete, revised, and edited pdf reference manuals are also       *
 *    available.                                                         *
 *                                                                       *
 *    Purchasing FreeRTOS documentation will not only help you, by       *
 *    ensuring you get running as quickly as possible and with an        *
 *    in-depth knowledge of how to use FreeRTOS, it will also help       *
 *    the FreeRTOS project to continue with its mission of providing     *
 *    professional grade, cross platform, de facto standard solutions    *
 *    for microcontrollers - completely free of charge!                  *
 *                                                                       *
 *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
 *                                                                       *
 *    Thank you for using FreeRTOS, and thank you for your support!      *
 *                                                                       *
 ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

 ***************************************************************************
 *                                                                       *
 *    Having a problem?  Start by reading the FAQ "My application does   *
 *    not run, what could be wrong?                                      *
 *                                                                       *
 *    http://www.FreeRTOS.org/FAQHelp.html                               *
 *                                                                       *
 ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest information,
    license and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/* My Includes */
#include "myincludes.h"


/* Hardware configuration. */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2, CP = OFF, BWP = OFF
#pragma config PWP = OFF /*, UPLLEN = OFF, FSRSSEL = PRIORITY_7 */

/* Time is measured in "ticks".  The tick rate is set by the configTICK_RATE_HZ
configuration parameter (defined in FreeRTOSConfig.h).  If configTICK_RATE_HZ
is equal to or less than 1000 (1KHz) then portTICK_RATE_MS can be used to
convert a time in milliseconds into a time in ticks. */
#define mainTOGGLE_PERIOD ( 200UL / portTICK_RATE_MS )


/* Performs the hardware initialisation to ready the hardware to run this example */
static void prvSetupHardware(void);

int main(void) {
    /* Perform any hardware initialisation that may be necessary. */
    prvSetupHardware();
    //create queues
    xQueueHandle ql0 = xQueueCreate(5, 4);
    xQueueHandle ql1 = xQueueCreate(5, 4);
    xQueueHandle ql2 = xQueueCreate(5, 4);
    xQueueHandle quart = xQueueCreate(5, 50);

    xTaskParameter_t MCP1= {1, ql0, quart, NULL};
    xTaskParameter_t MCP2= {2, ql1, quart, NULL};
    xTaskParameter_t MCP3= {0, ql2, quart, NULL};
    xTaskParameter_t pUART= {0, NULL, quart, NULL};
    xTaskParameter_t LED0= {0, ql0, NULL, NULL};
    xTaskParameter_t LED1= {1, ql1, NULL, NULL};
    xTaskParameter_t LED2= {2, ql2, NULL, NULL};

    xTaskHandle next1;
    xTaskHandle next2;
    xTaskHandle next3;
    xTaskCreate(systemControlTask,
            "MCP 1",
            configMINIMAL_STACK_SIZE,
            (void*)&MCP1,
            1,
            &next3);

    xTaskCreate(systemControlTask,
            "MCP 2",
            configMINIMAL_STACK_SIZE,
            (void*)&MCP2,
            1,
            &next1);

    xTaskCreate(systemControlTask,
            "MCP 3",
            configMINIMAL_STACK_SIZE,
            (void*)&MCP3,
            1,
            &next2);

    xTaskCreate(myledblink,
            "LED 0",
            configMINIMAL_STACK_SIZE,
            (void *)&LED0,
            1,
            NULL);

    xTaskCreate(myledblink,
            "LED 1",
            configMINIMAL_STACK_SIZE,
            (void *)&LED1,
            1,
            NULL);

    xTaskCreate(myledblink,
            "LED 2",
            configMINIMAL_STACK_SIZE,
            (void *)&LED2,
            1,
            NULL);
    xTaskCreate(UARTTask,
            "UART",
            configMINIMAL_STACK_SIZE,
            (void *)&pUART,
            1,
            NULL);

    MCP1.next = next1;
    MCP2.next = next2;
    MCP3.next = next3;

    vTaskSuspend(next1);
    vTaskSuspend(next2);
    /* Start the scheduler so the tasks start executing.  This function should not return. */
    vTaskStartScheduler();
}

/*-----------------------------------------------------------*/
static void prvSetupHardware(void) {
    /* Setup the CPU clocks, and configure the interrupt controller. */
    SYSTEMConfigPerformance(configCPU_CLOCK_HZ);
    mOSCSetPBDIV(OSC_PB_DIV_2);
    INTEnableSystemMultiVectoredInt();

    /* LEDs off. */
    mPORTDClearBits(BIT_0 | BIT_1 | BIT_2);

    /* LEDs are outputs. */
    mPORTDSetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2);

    ConfigCNPullups(CN15_PULLUP_ENABLE | CN16_PULLUP_ENABLE | CN19_PULLUP_ENABLE);
}


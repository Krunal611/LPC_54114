/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_power.h"
#include "board.h"
#include "fsl_inputmux.h"
#include "fsl_pint.h"

#include "pin_mux.h"
#include <stdbool.h>
#if configUSE_TICKLESS_IDLE
#include "fsl_rtc.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO BOARD_LED_GREEN_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_GREEN_GPIO_PIN

#define BOARD_SW_GPIO BOARD_SW3_GPIO
#define BOARD_SW_PORT BOARD_SW3_GPIO_PORT
#define BOARD_SW_GPIO_PIN BOARD_SW3_GPIO_PIN
#define BOARD_SW_IRQ BOARD_SW3_IRQ
#define BOARD_SW_IRQ_HANDLER BOARD_SW3_IRQ_HANDLER
#define BOARD_SW_NAME BOARD_SW3_NAME

/* @brief FreeRTOS tickless timer configuration. */
#define TICKLESS_RTC_BASE_PTR RTC  /*!< Tickless timer base address. */
#define TICKLESS_RTC_IRQn RTC_IRQn /*!< Tickless timer IRQ number. */

#define BOARD_PINT_PIN_INT_SRC kINPUTMUX_GpioPort0Pin4ToPintsel
/* Task priorities. */
/* clang-format off */
#define tickless_task_PRIORITY   ( configMAX_PRIORITIES - 2 )
#define SW_task_PRIORITY   ( configMAX_PRIORITIES - 1 )
#define TIME_DELAY_SLEEP      5000

/* Interrupt priorities. */
#define SW_NVIC_PRIO 2

/* clang-format on */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void vPortRtcIsr(void);
IRQn_Type vPortGetRtcIrqn(void);
RTC_Type *vPortGetRtcBase(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static void Tickless_task(void *pvParameters);
static void SW_task(void *pvParameters);
void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status);
SemaphoreHandle_t xSWSemaphore = NULL;
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Interrupt service fuction of LPT timer.
 *
 * This function to call vPortRtcIsr
 */
void RTC_IRQHandler(void)
{
    vPortRtcIsr();
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

/*!
 * @brief Fuction of LPT timer.
 *
 * This function to return LPT timer base address
 */

RTC_Type *vPortGetRtcBase(void)
{
    return TICKLESS_RTC_BASE_PTR;
}

/*!
 * @brief Fuction of LPT timer.
 *
 * This function to return LPT timer interrupt number
 */

IRQn_Type vPortGetRtcIrqn(void)
{
    return TICKLESS_RTC_IRQn;
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* enable clock for IOCON */
    CLOCK_EnableClock(kCLOCK_Iocon);

    /* enable clock for GPIO*/
    CLOCK_EnableClock(kCLOCK_Gpio0);

    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);

#if configUSE_TICKLESS_IDLE

    /* enable clock for UTICK*/
    CLOCK_EnableClock(kCLOCK_Rtc);

    /* Enable the RTC 32K Oscillator */
    SYSCON->RTCOSCCTRL |= SYSCON_RTCOSCCTRL_EN_MASK;

    /* Initialize RTC timer */
    RTC_Init(RTC);

    /* enable RTC interrupt */
    RTC_EnableInterrupts(RTC, RTC_CTRL_WAKE1KHZ_MASK);
    EnableIRQ(RTC_IRQn);
#endif

    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("Tickless Demo example\r\n");
    PRINTF("Press %s to wake up the CPU\r\n", BOARD_SW_NAME);

    /* Connect trigger sources to PINT */
    INPUTMUX_Init(INPUTMUX);
    INPUTMUX_AttachSignal(INPUTMUX, kPINT_PinInt0, BOARD_PINT_PIN_INT_SRC);

    /* Initialize PINT */
    PINT_Init(PINT);
    /* Setup Pin Interrupt 0 for falling edge */
    PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableFallEdge, pint_intr_callback);
    NVIC_SetPriority(BOARD_SW_IRQ, SW_NVIC_PRIO);
    EnableIRQ(BOARD_SW_IRQ);

    /*Create tickless task*/
    if (xTaskCreate(Tickless_task, "Tickless_task", configMINIMAL_STACK_SIZE + 10, NULL, tickless_task_PRIORITY,
                    NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
    if (xTaskCreate(SW_task, "Switch_task", configMINIMAL_STACK_SIZE + 10, NULL, SW_task_PRIORITY, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
    /*Task Scheduler*/
    vTaskStartScheduler();
    for (;;)
        ;
}

/* Tickless Task */
static void Tickless_task(void *pvParameters)
{
    PRINTF("\r\nTick count :\r\n");
    for (;;)
    {
        PRINTF("%d\r\n", xTaskGetTickCount());
        vTaskDelay(TIME_DELAY_SLEEP);
    }
}

/* Switch Task */
static void SW_task(void *pvParameters)
{
    xSWSemaphore = xSemaphoreCreateBinary();
    /* Enable callbacks for PINT */
    PINT_EnableCallback(PINT);

    for (;;)
    {
        if (xSemaphoreTake(xSWSemaphore, portMAX_DELAY) == pdTRUE)
        {
            PRINTF("CPU waked up by EXT interrupt\r\n");
        }
    }
}

/*!
* @brief Call back for PINT Pin interrupt 0-7.
*/
void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status)
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    /* Clear external interrupt flag. */
    PINT_PinInterruptClrFallFlag(PINT, kPINT_PinInt0);
    xSemaphoreGiveFromISR(xSWSemaphore, &xHigherPriorityTaskWoken);
}

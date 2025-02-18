/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_sctimer.h"

#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SCTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define DEMO_FIRST_SCTIMER_OUT kSCTIMER_Out_4
#define DEMO_SECOND_SCTIMER_OUT kSCTIMER_Out_2
#define GPIO_PORT 0U
#define Left_PIN1 18U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    sctimer_config_t sctimerInfo;
    gpio_pin_config_t led_config = {
           kGPIO_DigitalInput,
       };
    sctimer_pwm_signal_param_t pwmParam;
    uint32_t stateNumber;
    uint32_t eventFirstNumberOutput, eventSecondNumberOutput, eventNumberInput;
    uint32_t sctimerClock;
    uint32_t pin1;
    /* Board pin, clock, debug console init */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* enable clock for GPIO*/
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();
    GPIO_PortInit(GPIO, GPIO_PORT);
    GPIO_PinInit(GPIO, GPIO_PORT, Left_PIN1, &led_config);
    pin1= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1);
    sctimerClock = SCTIMER_CLK_FREQ;

    /* Print a note to terminal */
    PRINTF("\r\nSCTimer example to output edge-aligned PWM signal\r\n");
    PRINTF("\r\nWhen user presses a switch the PWM signal will be seen from Out 2  ");
    PRINTF("\r\nWhen user presses the switch again PWM signal on Out 2 will turn off ");
    PRINTF("\r\nThe PWM signal from Out 4 will remain active all the time ");

    /* Default configuration operates the counter in 32-bit mode */
    SCTIMER_GetDefaultConfig(&sctimerInfo);

    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);

    stateNumber = SCTIMER_GetCurrentState(SCT0);

    /* Configure PWM params with frequency 24kHZ from first output */
    pwmParam.output = DEMO_FIRST_SCTIMER_OUT;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent = 10;

    /* Schedule events in current state; State 0 */
    /* Schedule events for generating a 24KHz PWM with 10% duty cycle from first Out in the current state */
    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm, 24000U, sctimerClock, &eventFirstNumberOutput) ==
        kStatus_Fail)
    {
        return -1;
    }

    /* Schedule an event to look for a rising edge on input 1 in this state */
    if (SCTIMER_CreateAndScheduleEvent(SCT0, kSCTIMER_InputFallEvent,1, pin1, kSCTIMER_Counter_L,
                                       &eventNumberInput) == kStatus_Fail)
    {
        return -1;
    }

    /* Transition to next state when a rising edge is detected on input 1 */
    SCTIMER_SetupNextStateAction(SCT0, stateNumber + 1, eventNumberInput);

    /* Go to next state; State 1 */
    SCTIMER_IncreaseState(SCT0);

    /* Schedule events in State 1 */
    /* Schedule events for generating a 24KHz PWM with 50% duty cycle from second Out in this new state */
    pwmParam.output = DEMO_SECOND_SCTIMER_OUT;
    pwmParam.dutyCyclePercent = 50;
    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm, 24000U, sctimerClock, &eventSecondNumberOutput) ==
        kStatus_Fail)
    {
        return -1;
    }

    /* Re-enable PWM coming out from Out 4 by scheduling the PWM events in this new state */
    /* To get a PWM, the SCTIMER_SetupPwm() function creates 2 events; 1 for the pulse period and
     * and 1 for the pulse, we need to schedule both events in this new state
     */
    /* Schedule the period event for the PWM */
    SCTIMER_ScheduleEvent(SCT0, eventFirstNumberOutput);
    /* Schedule the pulse event for the PWM */
    SCTIMER_ScheduleEvent(SCT0, eventFirstNumberOutput + 1);

    /* Schedule an event to look for a rising edge on input 1 in this state */
    if (SCTIMER_CreateAndScheduleEvent(SCT0, kSCTIMER_InputFallEvent,1,pin1, kSCTIMER_Counter_L,
                                       &eventNumberInput) == kStatus_Fail)
    {
        return -1;
    }

    /* Transition back to State 0 when a rising edge is detected on input 1 */
    /* State 0 has only 1 PWM active, there will be no PWM from Out 2 */
    SCTIMER_SetupNextStateAction(SCT0, stateNumber, eventNumberInput);

    /* Start the timer, use counter L as we are operating counter in 32-bit mode */
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);

    while (1)
    {
    }
}

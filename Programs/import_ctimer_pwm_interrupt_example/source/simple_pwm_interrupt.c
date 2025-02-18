/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_ctimer.h"

#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CTIMER CTIMER0                 /* Timer 0 */
#define CTIMER_MAT_OUT kCTIMER_Match_1 /* Match output 1 */
#define CTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_AsyncApbClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void pwm_match_callback(uint32_t flags);

/*******************************************************************************
* Variables
******************************************************************************/
static uint8_t dutyCycle = 99;
volatile uint32_t g_pwmPeriod = 0U;
volatile uint32_t g_pulsePeriod = 0U;

static ctimer_callback_t ctimer_callback[] = {pwm_match_callback};

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t CTIMER_GetPwmPeriodValue(uint32_t pwmFreqHz, uint8_t dutyCyclePercent, uint32_t timerClock_Hz)
{
    /* Calculate PWM period match value */
    g_pwmPeriod = (timerClock_Hz / pwmFreqHz) - 1;

    /* Calculate pulse width match value */
    if (dutyCyclePercent == 0)
    {
        g_pulsePeriod = g_pwmPeriod + 1;
    }
    else
    {
        g_pulsePeriod = (g_pwmPeriod * (100 - dutyCyclePercent)) / 100;
    }
    return kStatus_Success;
}
status_t CTIMER_UpdatePwmPulsePeriodValue(uint8_t dutyCyclePercent)
{
    /* Calculate pulse width match value */
    /* For 0% dutycyle, make pulse period greater than period so the event will never occur */
    if (dutyCyclePercent == 0)
    {
        g_pulsePeriod = g_pwmPeriod + 1;
    }
    else
    {
        g_pulsePeriod = (g_pwmPeriod * (100 - dutyCyclePercent)) / 100;
    }

    return kStatus_Success;
}

void pwm_match_callback(uint32_t flags)
{
    static uint32_t count = 0;
    static uint8_t decrement = 1;

    if ((flags & (1 << CTIMER_MAT_OUT)) && (++count > 100))
    {
        count = 0;
        /* Update pulse width match value after the PWM duty cycle is changed */
        CTIMER_UpdatePwmPulsePeriodValue(dutyCycle);
        CTIMER_UpdatePwmPulsePeriod(CTIMER, CTIMER_MAT_OUT, g_pulsePeriod);
        dutyCycle = dutyCycle + 1 - decrement * 2;
        if (dutyCycle == 69)
        {
            decrement = 0;
        }
        else if (dutyCycle == 99)
        {
            decrement = 1;
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    ctimer_config_t config;
    uint32_t srcClock_Hz;
    uint32_t timerClock;

    /* Init hardware*/
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* Enable the asynchronous bridge */
    SYSCON->ASYNCAPBCTRL = 1;

    /* Use 12 MHz clock for some of the Ctimers */
    CLOCK_AttachClk(kFRO12M_to_ASYNC_APB);

    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    /* CTimer0 counter uses the AHB clock, some CTimer1 modules use the Aysnc clock */
    srcClock_Hz = CTIMER_CLK_FREQ;

    PRINTF("CTimer example to generate a PWM signal\r\n");
    PRINTF("This example uses interrupts to update the PWM duty cycle\r\n");

    CTIMER_GetDefaultConfig(&config);
    timerClock = srcClock_Hz / (config.prescale + 1);

    CTIMER_Init(CTIMER, &config);

    CTIMER_RegisterCallBack(CTIMER, &ctimer_callback[0], kCTIMER_SingleCallback);
    /* Get the PWM period match value and pulse width match value of 2Khz PWM signal */
    CTIMER_GetPwmPeriodValue(2000, dutyCycle, timerClock);
    CTIMER_SetupPwmPeriod(CTIMER, CTIMER_MAT_OUT, g_pwmPeriod, g_pulsePeriod, true);
    CTIMER_StartTimer(CTIMER);

    while (1)
    {
    }
}

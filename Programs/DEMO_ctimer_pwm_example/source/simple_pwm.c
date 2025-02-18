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
#define CTIMER CTIMER0
#define CTIMER_1 CTIMER1 /* Timer 0 */
#define CTIMER_MAT_OUT kCTIMER_Match_1 /* Match output 1 */
#define CTIMER_MAT_OUT1 kCTIMER_Match_2
#define CTIMER_MAT1_OUT kCTIMER_Match_0
#define CTIMER_MAT1_OUT1 kCTIMER_Match_1
#define CTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_AsyncApbClk)
#define GPIO_PORT 0U
#define Left_Forward 10U
#define Left_Reverse 14U
#define Right_Forward 15U
#define Right_Reverse 16U
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/
volatile uint32_t g_pwmPeriod = 0U;
volatile uint32_t g_pulsePeriod = 0U;

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

/*!
 * @brief Main function
 */
int main(void)
{
    ctimer_config_t config;
    gpio_pin_config_t GPIO_config = {
    	        kGPIO_DigitalInput,
    	    };
    uint32_t srcClock_Hz,speed = 60;
    uint32_t timerClock;
    uint8_t a ,Right=0;
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

    CTIMER_GetDefaultConfig(&config);
    timerClock = srcClock_Hz / (config.prescale + 1);

    CTIMER_Init(CTIMER, &config);
    CTIMER_Init(CTIMER_1, &config);
    GPIO_PortInit(GPIO, GPIO_PORT);
    GPIO_PinInit(GPIO, GPIO_PORT, Left_Forward, &GPIO_config);
    GPIO_PinInit(GPIO, GPIO_PORT, Left_Reverse, &GPIO_config);
    GPIO_PinInit(GPIO, GPIO_PORT, Right_Forward, &GPIO_config);


    GPIO_PinInit(GPIO, GPIO_PORT, Right_Reverse, &GPIO_config);
    /* Get the PWM period match value and pulse width match value of 20Khz PWM signal with 20% dutycycle */
    CTIMER_GetPwmPeriodValue(20000, 20, timerClock);
    CTIMER_SetupPwmPeriod(CTIMER, CTIMER_MAT_OUT, g_pwmPeriod, g_pulsePeriod, false);
    CTIMER_GetPwmPeriodValue(20000, 40, timerClock);
    CTIMER_SetupPwmPeriod(CTIMER, CTIMER_MAT_OUT1, g_pwmPeriod, g_pulsePeriod, false);
    //CTIMER_GetPwmPeriodValue(20000, 60, timerClock);
    //CTIMER_SetupPwmPeriod(CTIMER_1, CTIMER_MAT1_OUT, g_pwmPeriod, g_pulsePeriod, false);
   // CTIMER_GetPwmPeriodValue(20000, 45, timerClock);
   // CTIMER_SetupPwmPeriod(CTIMER_1, CTIMER_MAT1_OUT1, g_pwmPeriod, g_pulsePeriod, false);




    while(1)
    {

    if(GPIO_PinRead(GPIO, GPIO_PORT, Left_Forward)==0)
    {
    	a=a+1;
    	 if(a=1)
    	{
    		Right = 1;
    		printf("%d\n",a);
    	}
    	else if(a=2)
    	{
    		Right = 2;
    	}
    	else if(a=3)
    	{
    		Right =3 ;
    	}
    	else
    	{
    		a = 0;
    		Right =0;
    	}
    	}
    printf("%d\n",Right);
    while(Right==1)
    {
        CTIMER_UpdatePwmDutycycle(CTIMER, CTIMER_MAT_OUT,0);
        CTIMER_UpdatePwmDutycycle(CTIMER, CTIMER_MAT_OUT1, 0);
    }
    while(Right==2)
    {
        CTIMER_UpdatePwmDutycycle(CTIMER, CTIMER_MAT_OUT,0);
        CTIMER_UpdatePwmDutycycle(CTIMER, CTIMER_MAT_OUT1, speed);
    }
    while(Right==3)
    {
        CTIMER_UpdatePwmDutycycle(CTIMER, CTIMER_MAT_OUT,speed);



        CTIMER_UpdatePwmDutycycle(CTIMER, CTIMER_MAT_OUT1, 0);
    }

    CTIMER_StartTimer(CTIMER);
    CTIMER_StartTimer(CTIMER_1);
    while (1)
    {
    }
}
}

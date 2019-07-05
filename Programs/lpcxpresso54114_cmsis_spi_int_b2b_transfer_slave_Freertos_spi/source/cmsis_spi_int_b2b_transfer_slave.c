/*
 * Copyright 2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_spi_cmsis.h"
#include "board.h"

#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DRIVER_SLAVE_SPI Driver_SPI3

#define TRANSFER_SIZE 64U /* Transfer dataSize */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* SPI user SlaveSignalEvent */
void SPI_SlaveSignalEvent_t(uint32_t event);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t slaveRxData[TRANSFER_SIZE] = {0};
uint8_t slaveTxData[TRANSFER_SIZE] = {0};

volatile bool isTransferCompleted = false;
/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t SPI3_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Flexcomm3);
}
void SPI_SlaveSignalEvent_t(uint32_t event)
{
    /* user code */
    isTransferCompleted = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* attach 12 MHz clock to FLEXCOMM3 (SPI3 master) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);

    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC3_RST_SHIFT_RSTn);

    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    PRINTF("SPI CMSIS driver board to board interrupt example.\r\n");

    uint32_t i = 0U;
    uint32_t errorCount = 0U;

    /*SPI slave init*/
    DRIVER_SLAVE_SPI.Initialize(SPI_SlaveSignalEvent_t);
    DRIVER_SLAVE_SPI.PowerControl(ARM_POWER_FULL);
    DRIVER_SLAVE_SPI.Control(ARM_SPI_MODE_SLAVE, false);

    PRINTF("\r\n Slave example is running...\r\n");

    /* Reset the send and receive buffer */
    for (i = 0U; i < TRANSFER_SIZE; i++)
    {
        slaveRxData[i] = 0U;
        slaveTxData[i] = i % 256;
    }

    isTransferCompleted = false;
    /* Set slave transfer to receive and send data */
    DRIVER_SLAVE_SPI.Transfer(slaveTxData, slaveRxData, TRANSFER_SIZE);
    /* Wait until transfer completed */
    while (!isTransferCompleted)
    {
    }

    for (i = 0; i < TRANSFER_SIZE; i++)
    {
        if (slaveRxData[i] != i)
        {
            PRINTF("\n\rThe %d number is wrong! It is %dn\r", i, slaveRxData[i]);
            errorCount++;
        }
    }

    PRINTF("\r\n");
    if (errorCount == 0)
    {
        PRINTF("\r\n Slave receive:");
        for (i = 0; i < TRANSFER_SIZE; i++)
        {
            /* Print 16 numbers in a line */
            if ((i & 0x0FU) == 0U)
            {
                PRINTF("\r\n    ");
            }
            PRINTF(" %02X", slaveRxData[i]);
        }
        PRINTF("\r\n");
        PRINTF("Succeed!\n\r");
    }
    else
    {
        PRINTF("Error occurd in SPI transfer!\n\r");
    }
    while (1)
    {
    }
}

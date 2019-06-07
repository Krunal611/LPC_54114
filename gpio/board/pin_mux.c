/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v5.0
processor: LPC54114J256
package_id: LPC54114J256BD64
mcu_data: ksdk2_0
processor_version: 5.0.1
board: LPCXpresso54114
pin_labels:
- {pin_num: '36', pin_signal: PIO0_2/FC0_CTS_SDA_SSEL0/FC2_SSEL3/CTIMER2_CAP1, label: 'J9[1]/P0_2-GPIO_SPI_CS', identifier: gpio}
- {pin_num: '61', pin_signal: PIO0_21/CLKOUT/FC0_TXD_SCL_MISO/CTIMER3_MAT0, label: 'J2[2]/P0_21-CLKOUT-SPIFI_CLK', identifier: in}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: '58', peripheral: GPIO, signal: 'PIO0, 18', pin_signal: PIO0_18/FC5_TXD_SCL_MISO/SCT0_OUT0/CTIMER0_MAT0, direction: INPUT, mode: pullUp}
  - {pin_num: '59', peripheral: GPIO, signal: 'PIO0, 19', pin_signal: PIO0_19/FC5_SCK/SCT0_OUT1/CTIMER0_MAT1, direction: INPUT, mode: pullUp}
  - {pin_num: '60', peripheral: GPIO, signal: 'PIO0, 20', pin_signal: PIO0_20/FC5_RXD_SDA_MOSI/FC0_SCK/CTIMER3_CAP0, direction: INPUT}
  - {pin_num: '61', peripheral: GPIO, signal: 'PIO0, 21', pin_signal: PIO0_21/CLKOUT/FC0_TXD_SCL_MISO/CTIMER3_MAT0, direction: INPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO0 module */
    CLOCK_EnableClock(kCLOCK_Gpio0);

    gpio_pin_config_t SPI_FLASH_MISO_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_18 (pin 58)  */
    GPIO_PinInit(BOARD_INITPINS_SPI_FLASH_MISO_GPIO, BOARD_INITPINS_SPI_FLASH_MISO_PORT, BOARD_INITPINS_SPI_FLASH_MISO_PIN, &SPI_FLASH_MISO_config);

    gpio_pin_config_t SPI_FLASH_SCK_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_19 (pin 59)  */
    GPIO_PinInit(BOARD_INITPINS_SPI_FLASH_SCK_GPIO, BOARD_INITPINS_SPI_FLASH_SCK_PORT, BOARD_INITPINS_SPI_FLASH_SCK_PIN, &SPI_FLASH_SCK_config);

    gpio_pin_config_t SPI_FLASH_MOSI_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_20 (pin 60)  */
    GPIO_PinInit(BOARD_INITPINS_SPI_FLASH_MOSI_GPIO, BOARD_INITPINS_SPI_FLASH_MOSI_PORT, BOARD_INITPINS_SPI_FLASH_MOSI_PIN, &SPI_FLASH_MOSI_config);

    gpio_pin_config_t in_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_21 (pin 61)  */
    GPIO_PinInit(BOARD_INITPINS_in_GPIO, BOARD_INITPINS_in_PORT, BOARD_INITPINS_in_PIN, &in_config);

    IOCON->PIO[0][18] = ((IOCON->PIO[0][18] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT018 (pin 58) is configured as PIO0_18. */
                         | IOCON_PIO_FUNC(PIO018_FUNC_ALT0)

                         /* Selects function mode (on-chip pull-up/pull-down resistor control).
                          * : Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO018_MODE_PULL_UP)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO018_DIGIMODE_DIGITAL));

    IOCON->PIO[0][19] = ((IOCON->PIO[0][19] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT019 (pin 59) is configured as PIO0_19. */
                         | IOCON_PIO_FUNC(PIO019_FUNC_ALT0)

                         /* Selects function mode (on-chip pull-up/pull-down resistor control).
                          * : Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO019_MODE_PULL_UP)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO019_DIGIMODE_DIGITAL));

    IOCON->PIO[0][20] = ((IOCON->PIO[0][20] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT020 (pin 60) is configured as PIO0_20. */
                         | IOCON_PIO_FUNC(PIO020_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO020_DIGIMODE_DIGITAL));

    IOCON->PIO[0][21] = ((IOCON->PIO[0][21] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT021 (pin 61) is configured as PIO0_21. */
                         | IOCON_PIO_FUNC(PIO021_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO021_DIGIMODE_DIGITAL));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

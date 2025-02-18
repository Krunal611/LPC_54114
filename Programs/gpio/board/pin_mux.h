/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Select Analog/Digital mode.: Digital mode. */
#define PIO018_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO018_FUNC_ALT0 0x00u
/*!
 * @brief Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-up. Pull-up resistor enabled. */
#define PIO018_MODE_PULL_UP 0x02u
/*!
 * @brief Select Analog/Digital mode.: Digital mode. */
#define PIO019_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO019_FUNC_ALT0 0x00u
/*!
 * @brief Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-up. Pull-up resistor enabled. */
#define PIO019_MODE_PULL_UP 0x02u
/*!
 * @brief Select Analog/Digital mode.: Digital mode. */
#define PIO020_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO020_FUNC_ALT0 0x00u
/*!
 * @brief Select Analog/Digital mode.: Digital mode. */
#define PIO021_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO021_FUNC_ALT0 0x00u

/*! @name PIO0_18 (number 58), J1[11]/U5[2]/P0_18-FC5_TXD_SCL_MISO
  @{ */
#define BOARD_INITPINS_SPI_FLASH_MISO_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_INITPINS_SPI_FLASH_MISO_PORT 0U   /*!<@brief PORT device name: 0U */
#define BOARD_INITPINS_SPI_FLASH_MISO_PIN 18U   /*!<@brief 0U pin index: 18 */
                                                /* @} */

/*! @name PIO0_19 (number 59), J1[9]/J2[8]/U5[6]/P0_19-FC5_SCK-SPIFI_CSn
  @{ */
#define BOARD_INITPINS_SPI_FLASH_SCK_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_INITPINS_SPI_FLASH_SCK_PORT 0U   /*!<@brief PORT device name: 0U */
#define BOARD_INITPINS_SPI_FLASH_SCK_PIN 19U   /*!<@brief 0U pin index: 19 */
                                               /* @} */

/*! @name PIO0_20 (number 60), J1[13]/U5[5]/P0_20-FC5_RXD_SDA_MOSI
  @{ */
#define BOARD_INITPINS_SPI_FLASH_MOSI_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_INITPINS_SPI_FLASH_MOSI_PORT 0U   /*!<@brief PORT device name: 0U */
#define BOARD_INITPINS_SPI_FLASH_MOSI_PIN 20U   /*!<@brief 0U pin index: 20 */
                                                /* @} */

/*! @name PIO0_21 (number 61), J2[2]/P0_21-CLKOUT-SPIFI_CLK
  @{ */
#define BOARD_INITPINS_in_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_INITPINS_in_PORT 0U   /*!<@brief PORT device name: 0U */
#define BOARD_INITPINS_in_PIN 21U   /*!<@brief 0U pin index: 21 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M4F */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

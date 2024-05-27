/*
 * MSPI_Config.h
 *
 *  Created on: 3 May 2024
 *      Author: User
 */

#ifndef MSPI_CONFIG_H_
#define MSPI_CONFIG_H_

/*Set TImeout for your functions*/
#define SPI_uint32TIMEOUT					100000UL

/*Select Master/Slave
 * choose between
 * 1. SPI_MASTER
 * 2. SPI_SLAVE
 */
#define SPI_MASTER_SLAVE_SELECT				SPI_MASTER

/* Select SPI Master Mode
 * 1. SPI_MODE_FULL_DUPLEX
 * 2. SPI_MODE_HALF_DUPLEX_RX
 * 3. SPI_MODE_HALF_DUPLEX_TX
 * 4. SPI_MODE_SIMPLEX_RX
 */
#define SPI_MASTER_MODE_SELECT				SPI_MODE_FULL_DUPLEX

/*
 * 1. SPI_SS_OUTPUT_MULTIMASTER_DISABLED
 * 2. SPI_SS_INPUT_MULTIMASTER_ENABLED
 */
#define SPI_MASTER_SS_PIN_MODE				SPI_SS_INPUT_MULTIMASTER_ENABLED

/* Select SPI Slave Mode
 * 1. SPI_SSM_DISABLED
 * 2. SPI_SSM_ENABLED
 */
#define SPI_SOFTWARE_SLAVE_MANAGEMENT		SPI_SSM_ENABLED

/*Set Data Order
 * choose between
 * 1. SPI_DATA_LSB_FIRST
 * 2. SPI_DATA_MSP_FIRST
 */
#define SPI_DATA_ORDER						SPI_DATA_MSP_FIRST

/*Set Data Size
 * choose between
 *1. SPI_DATA_8_BIT
 *2. SPI_DATA_16_BIT
 */
#define SPI_DATA_SIZE						SPI_DATA_8_BIT


/*Set Clock Polarity
 * choose between
 * 1. SPI_RISING_LEADING_FALLING_TRAILING
 * 2. SPI_FALLING_LEADING_RISING_TRAILING
 */
#define SPI_CLOCK_POLARITY					SPI_FALLING_LEADING_RISING_TRAILING

/*Set Clock Phase
 * choose between
 * 1. SPI_SAMPLE_LEADING_SETUP_TRAILING
 * 2. SPI_SETUP_LEADING_SAMPLE_TRAILING
 */
#define SPI_CLOCK_PHASE						SPI_SETUP_LEADING_SAMPLE_TRAILING

/*Set Clock Rate Divide
 * 1. SPI_FREQ_DIVIDED_BY_2
 * 2. SPI_FREQ_DIVIDED_BY_4
 * 3. SPI_FREQ_DIVIDED_BY_8
 * 4. SPI_FREQ_DIVIDED_BY_16
 * 5. SPI_FREQ_DIVIDED_BY_32
 * 6. SPI_FREQ_DIVIDED_BY_64
 * 7. SPI_FREQ_DIVIDED_BY_128
 */
#define SPI_CLOCK_RATE						SPI_FREQ_DIVIDED_BY_2

/*Set SPI Tx buffer empty Interrupt Enable
 * choose between
 * 1. SPI_TXE_INTERRUPT_DISABLE
 * 2. SPI_TXE_INTERRUPT_ENABLE
 */
#define SPI_TXE_INTERRUPT_ENABLE_MODE		SPI_TXE_INTERRUPT_DISABLE

/*Set SPI RX buffer not empty Interrupt Enable
 * choose between
 * 1. SPI_RXNE_INTERRUPT_DISABLE
 * 2. SPI_RXNE_INTERRUPT_ENABLE
 */
#define SPI_RXNE_INTERRUPT_ENABLE_MODE		SPI_RXNE_INTERRUPT_DISABLE
/*Set SPI1 Enable
 * choose between
 * 1. SPI_DISABLE
 * 2. SPI_ENABLE
 */
#define SPI_ENABLE_MODE						SPI_ENABLE

/*Set SPI Enable
 * choose between
 * 1. SPI1_ENABLE
 * 2. SPI2_ENABLE
 * 3. SPI3_ENABLE
 */
#define SPI_ENABLE_SELECT					SPI1_ENABLE



#endif /* MSPI_CONFIG_H_ */

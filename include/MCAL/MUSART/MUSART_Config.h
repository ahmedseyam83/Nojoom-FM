#ifndef MUSART_CONFIG_H_
#define MUSART_CONFIG_H_



/* Set System Frequency*/
#define SYSTEM_FREQUENCY					16000000UL

/* Set Baud Rate */
#define USART_BAUD_RATE						9600UL

/*Set Mode
 * 1.ASYNCHRONOUS
 * 2.SYNCHRONOUS
 * */
#define USART_MODE							ASYNCHRONOUS

/* Set System Mode
 * 1. DISABLE
 * 2. ENABLE
 * */
#define USART_HARWARE_CONTROL 				DISABLE

/*Set USART Enable
 * choose between
 * 1. USART1_ENABLE
 * 2. USART2_ENABLE
 * 3. USART6_ENABLE
 */
#define USART_ENABLE_SELECT					USART1_ENABLE

/* Set Timeout for your function */
#define USART_TIMEOUT						10000


/* Set the over sample desired
 * 1.OVER_SAMPLE16
 * 2.OVER_SAMPLE8
 */
#define OVER_SAMPLE							OVER_SAMPLE16

/* Set Data packet size
 * 1. DATA_SIZE_8_BIT
 * 2. DATA_SIZE_9_BIT
 */
#define USART_DATA_SIZE						DATA_SIZE_8_BIT

/* Set Multi_processor Mode
 * 1. ENABLE
 * 2. DISABLE
 * */
#define USART_ADRESS_MODE 					DISABLE

/*UART ADDRESS*/
#define USART_ADDRESS						3

/* Set Receiver Enable)
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_RECEIVER_ENABLE				ENABLE

/* Set Transmitter Enable)
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_TRANSMITTER_ENABLE			ENABLE



/* Set Parity Mode
 * 1. DISABLE
 * 2. EVEN_PARITY
 * 3. ODD_PARITY
 */
#define USART_PARITY_MODE					DISABLE

/* Set Stop Bits
 * 1. STOP_BIT_0_5
 * 2. STOP_BIT_1
 * 3. STOP_BIT_1_5
 * 4. STOP_BIT_2
 */
#define USART_STOP_BIT						STOP_BIT_1

/* Set Clock Polarity (Synchronous mode only)
 * 1. XCK_RISING_TX_XCH_FALLING_RX
 * 2. XCK_RISING_RX_XCH_FALLING_TX
 */
#define USART_CLOCK_POLARITY				XCK_RISING_TX_XCH_FALLING_RX

/* Set Clock Phase (Synchronous mode only)
 * 1. CAPTURE_LEADING_SAMPLE_TRAILING
 * 2. SAMPLE_LEADING_CAPTURE_TRAILING
 */
#define USART_CLOCK_PHASE				CAPTURE_LEADING_SAMPLE_TRAILING

/* Set USART Hardware Control Enable
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_HARWARE_CONTROL				DISABLE

/* Set RX Complete Interrupt Enable
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_RX_COMPLETE_INTERRUPT			DISABLE

/* Set TX Complete Interrupt Enable
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_TX_COMPLETE_INTERRUPT			DISABLE

/* Set TX Complete Interrupt Enable
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_TX_BUFFER_EMPTY_INTERRUPT		DISABLE


/* Set CTS Interrupt Enable
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_CTS_INTERRUPT					DISABLE


#endif /* MUSART_CONFIG_H_ */

/*
 * stm32_uart.h
 *
 *  Created on: Apr 10, 2021
 *      Author: vishweshgm
 */

#ifndef HC05_INC_STM32_UART_H_
#define HC05_INC_STM32_UART_H_
#include "main.h"
#include "vartypes.h"
#define UART_RX_BUFFER_SIZE			(1)
#define UART_TX_BUFFER_SIZE			(10)
void stm32Uart_IRQHandler(UART_HandleTypeDef* huart);
void stm32Uart_TxInterruptEnable(UART_HandleTypeDef* huartp, uint8_t enable);
void stm32Uart_RxInterruptEnable(UART_HandleTypeDef* huartp, uint8_t enable);

extern volatile uint8_t vishwaUartRX_buffer[UART_RX_BUFFER_SIZE];
extern volatile uint8_t vishwaUartTX_buffer[UART_TX_BUFFER_SIZE];
extern volatile uint8_t RxByteCount, TxByteCount, Appl_u8TxLength;
extern volatile uint8_t Appl_u8UartTxCompleteFlag, Appl_u8UartRxCompleteFlag;



#endif /* HC05_INC_STM32_UART_H_ */

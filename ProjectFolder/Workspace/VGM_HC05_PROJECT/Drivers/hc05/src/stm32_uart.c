/*
 * stm32_uart.c
 *
 *  Created on: Apr 10, 2021
 *      Author: vishweshgm
 */
#include "stm32_uart.h"
volatile uint8_t vishwaUartRX_buffer[UART_RX_BUFFER_SIZE] = {0};
volatile uint8_t vishwaUartTX_buffer[UART_TX_BUFFER_SIZE] = {0};
volatile uint8_t RxByteCount = 0, TxByteCount = 0, Appl_u8TxLength = 0;
volatile uint8_t Appl_u8UartTxCompleteFlag = 1, Appl_u8UartRxCompleteFlag = 0;

static inline void stm32Uart_RxProcessingAppl(UART_HandleTypeDef* huartp);
static inline void stm32Uart_TxProcessingAppl(UART_HandleTypeDef* huartp);

void stm32Uart_IRQHandler(UART_HandleTypeDef* huartp){
	uint32_t isrflags   = READ_REG(huartp->Instance->SR);
	uint32_t cr1its     = READ_REG(huartp->Instance->CR1);
	uint32_t cr3its     = READ_REG(huartp->Instance->CR3);
	uint32_t errorflags = 0x00U;

	/* If no error occurs */
	errorflags = (isrflags & (uint32_t)(USART_SR_PE | USART_SR_FE | USART_SR_ORE | USART_SR_NE));
	if (errorflags == RESET)
	{
		/*Check if the Interrupt is due to Receive*/
		if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
		{
			stm32Uart_RxProcessingAppl(huartp);
			return;
		}
	}
	else
	{
		RxByteCount=0;
	}
	if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
	{
		stm32Uart_TxProcessingAppl(huartp);
		return;
	}


	if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
	{
		stm32Uart_TxProcessingAppl(huartp);
		return;
	}
}

static inline void stm32Uart_RxProcessingAppl(UART_HandleTypeDef* huartp){
	uint8_t ubUDR;
	if(Appl_u8UartRxCompleteFlag == 0)
	{
		if (huartp->Init.WordLength == UART_WORDLENGTH_9B)
		{
			ubUDR = (uint16_t)(huartp->Instance->DR & (uint16_t)0x00FF);
		}
		else
		{
			if (huartp->Init.Parity == UART_PARITY_NONE)
			{
				ubUDR = (uint8_t)(huartp->Instance->DR & (uint8_t)0x00FF);
			}
			else
			{
				ubUDR = (uint8_t)(huartp->Instance->DR & (uint8_t)0x007F);
			}
		}
		vishwaUartRX_buffer[RxByteCount] = ubUDR;
		RxByteCount++;
		if(RxByteCount >= UART_RX_BUFFER_SIZE)
		{
			RxByteCount = 0;
			Appl_u8UartRxCompleteFlag = 1;
		}
		else
		{
			stm32Uart_RxInterruptEnable(huartp,1);
		}
	}
}

static inline void stm32Uart_TxProcessingAppl(UART_HandleTypeDef* huartp){
	static uint8_t ubTxByte;

	if(TxByteCount<Appl_u8TxLength)
	{
		ubTxByte = vishwaUartTX_buffer[TxByteCount];
		TxByteCount++;
		if (huartp->Init.WordLength == UART_WORDLENGTH_9B)
		{
			huartp->Instance->DR = (uint16_t)(ubTxByte & (uint16_t)0x01FF);
		}
		else
		{
			huartp->Instance->DR = (uint8_t)(ubTxByte & (uint8_t)0x00FF);
		}

		if(TxByteCount >= Appl_u8TxLength)
		{
	        /* Disable the UART Register Empty Interrupt */
	        __HAL_UART_DISABLE_IT(huartp, UART_IT_TXE);

	        /* Enable the UART Transmit Complete Interrupt */
	        __HAL_UART_ENABLE_IT(huartp, UART_IT_TC);
		}
		else
		{
			stm32Uart_TxInterruptEnable(huartp,1);
		}
	}
	else
	{
		Appl_u8UartTxCompleteFlag = 1;
        /* Disable the UART Register Empty Interrupt */
        __HAL_UART_DISABLE_IT(huartp, UART_IT_TXE);

        /* Enable the UART Transmit Complete Interrupt */
        __HAL_UART_DISABLE_IT(huartp, UART_IT_TC);
	}

}

void stm32Uart_RxInterruptEnable(UART_HandleTypeDef* huartp, uint8_t enable){
	if(enable == 1)
	{
		//	__HAL_UART_ENABLE_IT(huartp, UART_IT_PE);
		//	__HAL_UART_ENABLE_IT(huartp, UART_IT_ERR);
			__HAL_UART_ENABLE_IT(huartp, UART_IT_RXNE);
		//	__HAL_UART_ENABLE_IT(huartp, UART_IT_TXE);
	}
	else
	{
		//	__HAL_UART_DISABLE_IT(huartp, UART_IT_PE);
		//	__HAL_UART_DISABLE_IT(huartp, UART_IT_ERR);
			__HAL_UART_DISABLE_IT(huartp, UART_IT_RXNE);
		//	__HAL_UART_DISABLE_IT(huartp, UART_IT_TXE);
	}

}

void stm32Uart_TxInterruptEnable(UART_HandleTypeDef* huartp, uint8_t enable){
	if(enable == 1)
	{
		//	__HAL_UART_ENABLE_IT(huartp, UART_IT_PE);
		//	__HAL_UART_ENABLE_IT(huartp, UART_IT_ERR);
		//	__HAL_UART_ENABLE_IT(huartp, UART_IT_RXNE);
			__HAL_UART_ENABLE_IT(huartp, UART_IT_TXE);
	}
	else
	{
		//	__HAL_UART_DISABLE_IT(huartp, UART_IT_PE);
		//	__HAL_UART_DISABLE_IT(huartp, UART_IT_ERR);
		//	__HAL_UART_DISABLE_IT(huartp, UART_IT_RXNE);
			__HAL_UART_DISABLE_IT(huartp, UART_IT_TXE);
	}

}


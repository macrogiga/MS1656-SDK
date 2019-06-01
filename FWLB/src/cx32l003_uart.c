/**
  ******************************************************************************
  * @file    cx32l003_uart.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the UART firmware functions.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, XMC SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_uart.h"
#include "cx32l003_rcc.h"

/**
  * @brief  Deinitializes the UARTx peripheral registers to their default reset values.
  * @param  UARTx: Select the UART or the UART peripheral. 
  *         This parameter can be one of the following values: UART0, UART1.      
  * @retval None
  */
void UART_DeInit(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  if (UARTx == UART0)
  {
   	/* Enable UART0 reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_UART0RST, ENABLE);
		/* Release UART0 from reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_UART0RST, DISABLE);
  }
  else if(UARTx == UART1)
	{		
		/* Enable UART1 reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_UART1RST, ENABLE);
		/* Release UART1 from reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_UART1RST, DISABLE);
			
  }
	else 
	{ 
		; /*!< No more uarts*/
	}
}

/**
  * @brief  Initializes the UARTx peripheral according to the specified
  *         parameters in the UART_InitStruct .
  * @param  UARTx: Select the UART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UART0, UART1.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         that contains the configuration information for the specified UART 
  *         peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef* UARTx, TIM_TypeDef* TIMx,UART_InitTypeDef* UART_InitStruct)
{
	/* Check the parameters */
	float baudrate = 0;
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));  
	assert_param(IS_UART_MODE(UART_InitStruct->UART_Mode));

	/*Initialize BIT6 and BIT7*/
	UARTx->SCON  &= ~(UART_SCON_SM1|UART_SCON_SM0);
	UARTx->SCON  &=  ~UART_SCON_DBAUD;

	/*Configure MODE0 and MODE1 with fixed baud rate*/
	if((UART_InitStruct->UART_Mode==UART_MODE0)||(UART_InitStruct->UART_Mode==UART_MODE2))
	{
		UARTx->SCON |= (UART_InitStruct->UART_Mode <<6);
		UARTx->SCON |= (UART_InitStruct->UART_BaudRateDbaud_Enable<<9);
	} 
	else 
	{
	  /*Configuration MODE0 and MODE1, baud rate can be matched, need to turn on TIM10/TIM11*/
		if((UART_InitStruct->UART_Mode==UART_MODE1)||(UART_InitStruct->UART_Mode==UART_MODE3))
		{
			UARTx->SCON |= (UART_InitStruct->UART_Mode<<6);
			UARTx->SCON |= (UART_InitStruct->UART_BaudRateDbaud_Enable<<9);
			if(UART_InitStruct->UART_BaudRateTimer_Selected)
			{
				/*Close TIM10/TIM11 interrupt*/
				NVIC_DisableIRQ(TIMER10_IRQn);
				NVIC_DisableIRQ(TIMER11_IRQn);
				
				UARTx->BRG  &= ~UART_SELF_BRG;
				/*Calculating UART baud rate: 4 homes and 5 entries*/
				baudrate = (1.0)*Fpclk*(UART_InitStruct->UART_BaudRateDbaud_Enable+1) /\
																					(UART_InitStruct->UART_BaudRate*32) +0.5;
				/*Configuration TIMER LOAD register*/
				TIMx->LOAD = (0x01<<16) - (int16_t)baudrate;
			
				/*Configuration TIMER BGLOAD register*/
				TIMx->BGLOAD =(0x01<<16) - (int16_t)baudrate;
			
				/*Turn on TIMER counter*/
				TIMx->CON = UART_TIM_EABLE;
			}
		 else
		 {
				UARTx->BRG = 0x00;
				UARTx->BRG  |= UART_SELF_BRG;
				/*Calculating UART baud rate: 4 homes and 5 entries*/
				baudrate =(1.0) *Fpclk*(UART_InitStruct->UART_BaudRateDbaud_Enable+1)/\
																						(UART_InitStruct->UART_BaudRate*32) +0.5;
				UARTx->BRG |= (int16_t)baudrate -1;
		}
	 }
  }		
}

/**
  * @brief  Fills each UART_InitStruct member with its default value.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
  /* UART_InitStruct members default value */
  UART_InitStruct->UART_BaudRate = 9600;
	UART_InitStruct->UART_Mode=UART_MODE0;
  UART_InitStruct->UART_BaudRateDbaud_Enable = 0x00; 
  UART_InitStruct->UART_BaudRateTimer_Selected = 0x00;
}	
/**
  * @brief  Enables or disables the specified UART peripheral.
  * @param  UARTx: Select the UART or the UART peripheral. 
  *         This parameter can be one of the following values:
  *           UART0, UART1.
  * @param  NewState: new state of the UARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_Cmd(UART_TypeDef* UARTx,uint16_t FuncState, FunctionalState NewState)
{
	/* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  UARTx->SCON &= ~UART_SCON_REN;
	
  if(FuncState == UART_RXEN_EABLE)	
	{
		/*Receive or receive/send*/
		if (NewState != DISABLE) 
		{
			/* Enable the selected UART by setting the REN bit in the SCON register */
			UARTx->SCON |= UART_SCON_REN;
		}
		else 
		{
			/*Send enable*/
			UARTx->SCON &= (uint16_t)~((uint16_t)UART_SCON_REN);
		}
  }
	else 
	{    /*Send enable*/
			UARTx->SCON &= (uint16_t)~((uint16_t)UART_SCON_REN);
  }
}

/**
  * @brief  Enables or disables the specified UART interrupts.
  * @param  UARTx: Select the UART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UART0, UART1, 
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg UART_IT_RIEN:  CTS change interrupt 
  *     @arg UART_IT_TIEN:  LIN Break detection interrupt
  * @param  NewState: new state of the specified UARTx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{
	 /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_IT(UART_IT));

  if(NewState != DISABLE)
	{
		/*Interrupt enable*/
    UARTx->SCON  |= UART_IT;
	}
	else
	{
		/*Interrupt disable*/
		UARTx->SCON  &= ~UART_IT;	
	}
}

/**
  * @brief  Sets the address of the UART node.
  * @param  UARTx: Select the UART or the UART peripheral. 
  *   This parameter can be one of the following values: UART0, UART1.   
  * @param  UART_Address: Indicates the address of the UART node.
  * @retval None
  */
void UART_SetAddress(UART_TypeDef* UARTx, uint8_t UART_Address,uint8_t UART_Address_Enable)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_ADDRESS(UART_Address)); 
    
  /* Clear the UART address */
  UARTx->SADDR &= UART_Address_Mask;
  /* Set the UART address node */
  UARTx->SADDR |= UART_Address;
	
	/* Clear the UART Address enable*/
  UARTx->SADEN &= UART_Address_Mask;
	/* Clear the UART Address enable*/
  UARTx->SADEN |= UART_Address_Enable;
}
/**
  * @brief  Enables or disables the UART  Recive Mode.
  * @param  UARTx: Select the UART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UART0, UART1
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  * @param  NewState: new state of the UART mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ReciveCmd(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct,FunctionalState NewState)
{
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	/*recive enable*/
	if(NewState) 
	{
			 /*Mode0/1 Recive enable*/
			if((UART_InitStruct->UART_Mode == UART_MODE0)||(UART_InitStruct->UART_Mode == UART_MODE1))
			{
					UARTx->SCON |= UART_SCON_REN;
					UARTx->ISR &= ~UART_ISR_RI;
			}
			/*Mode2/3 Recive enable*/
			else if((UART_InitStruct->UART_Mode == UART_MODE2)||(UART_InitStruct->UART_Mode == UART_MODE3))
			{
				 UARTx->ISR &= ~UART_ISR_RI;
			}
			else 
			{
				/*No more uart mode*/
			}
			
	}
 else 
 {
		  /*Send enable*/
			UARTx->SCON &= UART_SCON_REN;
 }
}



/**
  * @brief  Transmits single data through the UARTx peripheral.
  * @param  UARTx: Select the UART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UART0, UART1.
  * @param  Data: the data to transmit.
  * @retval None
  */
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
    
  /* Transmit Data */
  UARTx->SBUF = (uint32_t)Data;
}

/**
  * @brief  Returns the most recent received data by the UARTx peripheral.
  * @param  UARTx: Select the UART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UART0, UART1.
  * @retval The received data.
  */
uint8_t UART_ReceiveData(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
	
  /* Receive Data */
  return (uint8_t)(UARTx->SBUF& (uint8_t)0xFF);
}


/**
  * @brief  Enables or disables the UART TB8 function.
  * @param  UARTx: where x can be 0, 1 to select the UART or 
  *         UART peripheral.
  * @param  NewState: new state of the TB8 MODE.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_TB8Cmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState != DISABLE)
  {
    /* Enable the TB8 mode by setting the TB8 bit in the SCON register */
    UARTx->SCON |= UART_SCON_TB8;
  }
  else
  {
    /* Disable the IrDA mode by clearing the TB8 bit in the SCON register */
    UARTx->SCON &= ~UART_SCON_TB8;
  }
}

/**
  * @brief  Enables or disables the UART RB8 function.
  * @param  USARTx: where x can be 0, 1 to select the UART or 
  *         UART peripheral.
  * @param  NewState: new state of the RB8 MODE .
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_RB8Cmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    UARTx->SCON |= UART_SCON_RB8;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    UARTx->SCON &= ~UART_SCON_RB8;
  }
}

/**
  * @brief  Configures the USART's IrDA interface.
  * @param  USARTx: where x can be 0, 1 to select the UART or 
  *         UART peripheral.
  * @param  USART_IrDAMode: specifies the IrDA mode.
  *          This parameter can be one of the following values:
  *            @arg USART_IrDAMode_LowPower
  *            @arg USART_IrDAMode_Normal
  * @retval None
  */
void UART_IrDAConfig(UART_TypeDef* UARTx, UART_IRDInitTypeDef* UART_IRDInitStruct)
{ 
	uint16_t temp = 0;
	/* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
	
	/*parameters set*/
	temp = UART_IRDInitStruct->UART_IRDIRLPMOD| \
	       UART_IRDInitStruct->UART_IRDIRRXINV| \
	       UART_IRDInitStruct->UART_IRDIRTXINV| \
	       UART_IRDInitStruct->UART_IRDPSC;
	
  /*parameters set*/
  UARTx->IRDACR = temp;
}

/**
  * @brief  Enables or disables the USART's IrDA interface.
  * @param  USARTx: where x can be 0, 1 to select the UART or 
  *         UART peripheral.
  * @param  NewState: new state of the IrDA CMD.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    UARTx->IRDACR |= (uint16_t)UART_IRDACR_IREN;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    UARTx->IRDACR &= (uint16_t)~((uint16_t)UART_IRDACR_IREN);
  }
}
/**
  * @brief  Checks whether the specified UART interrupt has occurred or not.
  * @param  UARTx: Select the UART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UART0, UART1.
  * @param  UART_IT: specifies the UART interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg UART_ISR_RI:  Recive Data interrupution
  *     @arg UART_ISR_TI:  Tansmit Data Register empty interruption
  *     @arg UART_ISR_FEI: Receiving frame error interruption
  * @retval The new state of UART_IT (SET or RESET).
  */
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, uint16_t UART_IT)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  if ((UARTx->ISR & UART_IT) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the UARTx's interrupt pending bits.
  * @param  UARTx: Select the UART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   UART0, UART1.
  * @retval None
  */
void UART_ClearITBit(UART_TypeDef* UARTx, uint16_t UART_IT)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
	/*Clear interrupt pending bit*/
  UARTx->ICR = (uint32_t)UART_IT;
}


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/

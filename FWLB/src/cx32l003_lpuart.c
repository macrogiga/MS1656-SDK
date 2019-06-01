/**
  ******************************************************************************
  * @file    cx32l003_uart.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the LPUART firmware functions.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_lpuart.h"
#include "cx32l003_rcc.h"

uint8_t LPUART_FLAG = 0; 
/**
  * @brief  Deinitializes the LPUARTx peripheral registers to their default reset values.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *         This parameter can be one of the following values: 
  *         LPUART.
  * @retval None
  */
void LPUART_DeInit(LPUART_TypeDef* LPUARTx)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  if (LPUARTx == LPUART)
  {
		/* Enable LPUART reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_LPUARTRST, ENABLE);
		/* Release LPUART from reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_LPUARTRST, DISABLE);
  }

}

/**
  * @brief  Initializes the LPUARTx peripheral according to the specified
  *         parameters in the LPUART_InitStruct .
  * @param  LPUARTx: Select the LPUART peripheral. 
  *   This parameter can be one of the following values:LPUART
  * @param  LPUART_InitStruct: pointer to a LPUART_InitTypeDef structure
  *         that contains the configuration information for the specified LPUART 
  *         peripheral.
  * @param  LPModeState: new state of the LPUART peripheral. 
  * 	This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void LPUART_Init(LPUART_TypeDef* LPUARTx, LPTIMER_TypeDef* TIMERx,LPUART_InitTypeDef* LPUART_InitStruct,FunctionalState LPModeState)
{
	float baudrate = 0;
	
	/* Check the parameters */
	assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));
	assert_param(IS_LPUART_BAUDRATE(LPUART_InitStruct->LPUART_BaudRate));  
	assert_param(IS_LPUART_MODE(LPUART_InitStruct->LPUART_Mode));
	assert_param(IS_LPUART_SCLK(LPUART_InitStruct->LPUART_SCLKSEL));
	assert_param(IS_LPUART_SCLK(LPUART_InitStruct->LPUART_SCLKSEL));

	/*Initialization lpuart mode of work*/
	LPUARTx->SCON  &= ~(LPUART_SCON_SM1|LPUART_SCON_SM0);
	LPUARTx->SCON  &=  ~LPUART_SCON_DBAUD;

  /*config mode0/mode2  fixed baud*/
	if((LPUART_InitStruct->LPUART_Mode==LPUART_MODE0)||\
		        (LPUART_InitStruct->LPUART_Mode==LPUART_MODE2))
	{
		LPUARTx->SCON |= (LPUART_InitStruct->LPUART_Mode <<6);
		LPUARTx->SCON |= (LPUART_InitStruct->LPUART_BaudRateDbaud_Enable<<9);
	} 
	else	
	{
	 /*config mode1/mode3  variable baud*/
	if((LPUART_InitStruct->LPUART_Mode==LPUART_MODE1)||\
		           (LPUART_InitStruct->LPUART_Mode==LPUART_MODE3))
	{
		LPUARTx->SCON |= (LPUART_InitStruct->LPUART_Mode<<6);
		LPUARTx->SCON |= (LPUART_InitStruct->LPUART_BaudRateDbaud_Enable<<9);
		
    if(LPModeState != ENABLE)
		{  
			  LPUARTx->SCON &= ~LPUART_SCON_LPMODE;
			   /*Use LPTIMER to set baud rate*/
			  if(LPUART_InitStruct->LPUART_BaudRateTimer_Selected) 	
				{
					/*Close lptimer interrupt enable*/
					NVIC_DisableIRQ(LPTIMER_IRQn);
					LPUARTx->BRG  &= ~LPUART_SELF_BRG;
					/*Calculating baud rate,4 homes and 5 entries*/
					baudrate = (1.0)*Fpclk*(LPUART_InitStruct->LPUART_BaudRateDbaud_Enable+1) /\
																						(LPUART_InitStruct->LPUART_BaudRate*32) +0.5;
				  /*config lptimer load register*/
					LPTIMER->LOAD = (0x01<<16) - (int16_t)baudrate;
					/*config lptimer BGLOAD register*/
					LPTIMER->BGLOAD =(0x01<<16) - (int16_t)baudrate;
					/*config lptimer CR register*/
					LPTIMER->CR = LPUART_LPTIM_EABLE;
					/*open lptimer*/
					LPTIMER->CR |= LPUART_LPTIMRUN_EABLE;
				}
				/*Setting Baud Rate with Self Clock*/
				else 
				{
					LPUART->BRG  |= LPUART_SELF_BRG;
					/*Calculating baud rate,4 homes and 5 entries*/
					baudrate =(1.0) *Fpclk*(LPUART_InitStruct->LPUART_BaudRateDbaud_Enable+1)/\
																							(LPUART_InitStruct->LPUART_BaudRate*32) +0.5;
					LPUART->BRG |= (int16_t)baudrate -1;
				}
		}
		else
		{
			  LPUARTx->SCON |= LPUART_SCON_LPMODE;
				LPUARTx->SCON |= (LPUART_InitStruct->LPUART_Mode<<6);
		    LPUARTx->SCON &= ~LPUART_SCLK_MASK;
			  LPUARTx->SCON &= ~LPUART_SCLK_DIV_MASK;
			  /*Configuration Clock Selection*/
			  LPUARTx->SCON |= LPUART_InitStruct->LPUART_SCLKSEL;
			  /*Configuring Clock Frequency Division*/
			  LPUARTx->SCON |= LPUART_InitStruct->LPUART_SCLKPRS;
		}
	}
 }		
}

/**
  * @brief  Fills each LPUART_InitStruct member with its default value.
  * @param  LPUART_InitStruct: pointer to a LPUART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void LPUART_StructInit(LPUART_InitTypeDef* LPUART_InitStruct)
{
  /* LPUART_InitStruct members default value */
  LPUART_InitStruct->LPUART_BaudRate = 9600;
	LPUART_InitStruct->LPUART_Mode=LPUART_MODE0;
  LPUART_InitStruct->LPUART_BaudRateDbaud_Enable = 0x00; 
}	

/**
  * @brief  Enables or disables the specified LPUART peripheral.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *         This parameter can be one of the following values:
  *           LPUART
  * @param  NewState: new state of the LPUARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @param  FuncState: Lpuart function status
  * @retval None
  */
void LPUART_Cmd(LPUART_TypeDef* LPUARTx,uint16_t FuncState, FunctionalState NewState)
{
	  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(LPUARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  LPUARTx->SCON &= ~LPUART_SCON_REN;
	
  if(FuncState == LPUART_RXEN_EABLE)	
	{
		if (NewState != DISABLE) 
		{
			/* Enable the selected LPUART by setting the REN bit in the SCON register */
			LPUARTx->SCON |= LPUART_SCON_REN;
		}
		else 
		{
			LPUARTx->SCON &= ~LPUART_SCON_REN;
		}
  }
 else 
 {    /*Send function*/
			LPUARTx->SCON &= (uint16_t)~((uint16_t)LPUART_SCON_REN);
 }
}

/**
  * @brief  Enables or disables  LPUART LowPower mode.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *         This parameter can be one of the following values:
  *           LPUART.
  * @param  NewState: new state of the LPUARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_LowPowerCmd(LPUART_TypeDef* LPUARTx,FunctionalState NewState)
{
	  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(LPUARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/*Open LPUART LowPower mode*/
		LPUARTx->SCON |= LPUART_SCON_LPEN;
	}
	else 
	{
		/*Close LPUART LowPower mode*/
		LPUARTx->SCON &= ~LPUART_SCON_LPEN;
	}
 
}

/**
  * @brief  Enables or disables the specified LPUART interrupts.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *   This parameter can be one of the following values:
  *   LPUART, 
  * @param  LPUART_IT: specifies the LPUART interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg LPUART_IT_RIEN:  CTS change interrupt (not available for LPUART4 and LPUART5)
  *     @arg LPUART_IT_TIEN:  LIN Break detection interrupt
  * @param  NewState: new state of the specified LPUARTx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_ITConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT, FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(LPUARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_LPUART_ITENABLE(LPUART_IT));
	
	if(NewState != DISABLE)
	{
		/*Enable the lpuart interrupts*/
		LPUARTx->SCON |= LPUART_IT;
	}
	else
	{
		/*Close the lpuart interrupts*/
		LPUARTx->SCON &= ~LPUART_IT;
	}
}

/**
  * @brief  Sets the address of the LPUART node.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *   This parameter can be one of the following values:LPUART
  * @param  LPUART_Address: Indicates the address of the LPUART node.
  * @param  LPUART_Address_Enable: LPUART Address Enable parameters.
  * @retval None
  */
void LPUART_SetAddress(LPUART_TypeDef* LPUARTx, uint8_t LPUART_Address,uint8_t LPUART_Address_Enable)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));
  assert_param(IS_LPUART_ADDRESS(LPUART_Address)); 
    
  /* Clear the LPUART address */
  LPUARTx->SADDR &= LPUART_Address_Mask;
  /* Set the LPUART address node */
  LPUARTx->SADDR |= LPUART_Address;
	
	/* Clear the LPUART Address enable*/
  LPUARTx->SADEN &= LPUART_Address_Mask;
	/* Clear the LPUART Address enable*/
  LPUARTx->SADEN |= LPUART_Address_Enable;
}


/**
  * @brief  Enables or disables the LPUART’s LIN mode.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *   This parameter can be one of the following values:LPUART
  * @param  LPUART_InitStruct:  pointer to a LPUART_InitTypeDef structure
  *         which will be configed.
  * @param  NewState: new state of the LPUART mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_ReciveCmd(LPUART_TypeDef* LPUARTx, LPUART_InitTypeDef* LPUART_InitStruct,FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState) 
	{
			 /*Setting Receive Enables*/
			if((LPUART_InitStruct->LPUART_Mode == LPUART_MODE0)||\
				      (LPUART_InitStruct->LPUART_Mode == LPUART_MODE1))
			{
					LPUARTx->SCON |= LPUART_SCON_REN;
					LPUARTx->ISR &= ~LPUART_ISR_RI;
			}
			else 
			{
				  if((LPUART_InitStruct->LPUART_Mode == LPUART_MODE2)||\
						   (LPUART_InitStruct->LPUART_Mode == LPUART_MODE3))
					  LPUARTx->ISR &= ~LPUART_ISR_RI;
			}
	}
	else 
	{
		  /*Setting Send Enables*/
			LPUARTx->SCON &= LPUART_SCON_REN;
	}
}



/**
  * @brief  Transmits single data through the LPUARTx peripheral.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *   This parameter can be one of the following values: LPUART
  * @param  Data: the data to transmit.
  * @retval None
  */
void LPUART_SendData(LPUART_TypeDef* LPUARTx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));
    
  /* Transmit Data */
  LPUARTx->SBUF = (uint32_t)Data;
}

/**
  * @brief  Returns the most recent received data by the LPUARTx peripheral.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *   This parameter can be one of the following values: LPUART
  * @retval The received data.
  */
uint8_t LPUART_ReceiveData(LPUART_TypeDef* LPUARTx)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));
	
  /* Receive Data */
  return (uint8_t)(LPUARTx->SBUF& (uint8_t)0xFF);
}


/**
  * @brief  Checks whether the specified LPUART interrupt has occurred or not.
  * @param  LPUARTx: Select the LPUART or the LPUART peripheral. 
  *   This parameter can be one of the following values:
  *   LPUART
  * @param  LPUART_IT: specifies the LPUART interrupt source to check.
  *   This parameter can be one of the following values:
 	*					@argLPUART_ICR_RI      (uint32_t)0x00000001
	*					@argLPUART_ICR_TI      (uint32_t)0x00000002
	*					@argLPUART_ICR_FEI     (uint32_t)0x00000004
	*					@argLPUART_ICR_TE      (uint32_t)0x00000008
  * @retval The new state of LPUART_IT (SET or RESET).
  */
FlagStatus LPUART_GetFlagStatus(LPUART_TypeDef* LPUARTx, uint16_t LPUART_Flag)
{
    FlagStatus bitstatus = RESET;
	
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));
	assert_param(IS_LPUART_ISR(LPUART_Flag));

  if ((LPUARTx->ISR & LPUART_Flag) != (uint16_t)RESET)
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
  * @brief  Clears the LPUARTx's interrupt pending bits.
  * @param  LPUARTx:     Select the LPUART or the LPUART peripheral. 
  * @param  LPUART_Flag: LPUART Interrupt flag. 
  *   This parameter can be one of the following values:
	*					@argLPUART_ICR_RI      (uint32_t)0x00000001
	*					@argLPUART_ICR_TI      (uint32_t)0x00000002
	*					@argLPUART_ICR_FEI     (uint32_t)0x00000004
	*					@argLPUART_ICR_TE      (uint32_t)0x00000008
	*					@argLPUART_ICR_ALL     (uint32_t)0x0000000f
  * @retval None
  */
void LPUART_ClearITFlag(LPUART_TypeDef* LPUARTx, uint16_t LPUART_Flag)
{
 /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));
	assert_param(IS_LPUART_ICR(LPUART_Flag));
	
	/*clear it falg*/
  LPUARTx->ICR = (uint32_t)LPUART_Flag;
}




/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */

/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/

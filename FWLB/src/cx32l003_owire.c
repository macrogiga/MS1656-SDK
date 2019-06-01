/**
  ******************************************************************************
  * @file    cx32l003_owire.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides all the owire firmware functions.
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
#include "cx32l003_owire.h"
#include "cx32l003_rcc.h"

/**
  * @brief  Initializes the OWIRE peripheral according to the specified 
  *         parameters in the OWIRE_InitStruct.
  * @param  WIREx:Selects the OWIRE peripheral
  * @param  WIRE_InitStruct: pointer to a OWIRE_InitTypeDef structure that
  *         contains the configuration information for the specified OWIRE peripheral.
  * @retval None
  */
void OWIRE_Init(OWIRE_TypeDef* WIREx, OWIRE_InitTypeDef* WIRE_InitStruct)
{
	
	uint32_t tmpreg = 0,tmp = 0,clkdiv = 0,temp = 0; 
	 /* Check the parameters */
	assert_param(IS_OWIRE_ALL_PERIPH(WIREx));
  assert_param(IS_OWIRE_ALL_COUNTCLK( WIRE_InitStruct->WIRE_COUNTCLK));

	
	/* read the register of CR */
	tmpreg = WIREx->CR;
	tmpreg &= OWIRE_CR_MASK;
	
	/*---------------------------- OWIRE CR Configuration ------------------------*/
	/*set value of parameters*/
	if(WIRE_InitStruct->WIRE_COUNTCLK <= 0x02)
  {		
		/*clock div1 div2 div4*/
	  tmp = WIRE_InitStruct->WIRE_COUNTCLK;
    /*clock div */		
    clkdiv = 	(uint16_t)(0x01<< (WIRE_InitStruct->WIRE_COUNTCLK));
	}
	else 
  {	
    tmp = WIRE_InitStruct->WIRE_COUNTCLK;		
		/*clock div */		
		clkdiv = 	(uint16_t)0x10; 
	}
		

	/*Config WIRE_MSBFIRST to the register of CR*/
	/*Config WIRE_SIZE to the register of CR*/
	/*Config WIRE_COUNTCLK to the register of CR*/
	/*Config WIRE_EN to the register of CR*/
	/*Config WIRE_RDMODE to the register of CR*/
	
	tmpreg |= ((WIRE_InitStruct->WIRE_MSBFIRST)|\
	          (WIRE_InitStruct->WIRE_SIZE)|\
					  (tmp)|\
	          (WIRE_InitStruct->WIRE_EN)|\
	          (WIRE_InitStruct->WIRE_RDMODE));

	/*Set the value to the register of CR*/
	WIREx->CR = tmpreg;
	
	
  /*---------------------------- OWIRE  other registers  Configuration ------------------------*/
	/*Clear parameter to zero*/
	tmpreg = 0;
	/*config the NFCR register*/
	/*Set NFEN to the NFCR*/
	/*Set NFDIV to the NFCR*/
	tmpreg = WIRE_InitStruct->WIRE_NFEN |\
	         WIRE_InitStruct->WIRE_NFDIV;
	/*Set the vlaue to the NFCR register*/
	WIREx->NFCR = tmpreg;

	/*Set the vlaue to the RESCNT register*/
	temp = (1.0*(Fpclk/1000000/clkdiv*(WIRE_InitStruct->WIRE_RESCNT))+ 0.5);
  WIREx->RSTCNT = temp;
	/*Set the vlaue to the PRESCNT register*/
	temp = (1.0*(Fpclk/1000000/clkdiv*(WIRE_InitStruct->WIRE_PRESCNT))+ 0.5);
	WIREx-> PRESCNT  = temp;
	
	/*Set width of bit_pulse*/
	temp = (1.0*(Fpclk/1000000/clkdiv*(WIRE_InitStruct->WIRE_BITRATECNT))+ 0.5);

	WIREx->BITRATECNT = temp;
	
	/*Set count of driver*/
	temp = (1.0*(Fpclk/1000000/clkdiv*(WIRE_InitStruct->WIRE_DRVCNT))+ 0.5);
	WIREx->DRVCNT = temp;
	
	/*Set time of read for master*/
	temp = (1.0*(Fpclk/1000000/clkdiv*(WIRE_InitStruct->WIRE_RDSMPCNT))+ 0.5);
	WIREx->RDSMPCNT = temp ;
	
	/*Set the vlaue to  RECCNT register*/
	temp = (1.0*(Fpclk/1000000/clkdiv*(WIRE_InitStruct->WIRE_RECCNT))+ 0.5);
	WIREx->RECCNT = temp;
}


/**
  * @brief  Enables or disables the specified OWIRE peripheral function.
  * @param  WIREx: Selects the OWIRE peripheral
  * @param  NewState: new state of the OWIRE peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OWIRE_Cmd(OWIRE_TypeDef* WIREx, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_OWIRE_ALL_PERIPH(WIREx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	/*--------OWIRE CMD Configuration ----------*/
  if (NewState != DISABLE)
  {
    /* Enable the selected OWIRE peripheral */
    WIREx->CR |= OWIREENABLE;
  }
  else
  {
    /* Disable the selected OWIRE peripheral */
    WIREx->CR &= ~OWIREENABLE;
  }
}


/**
  * @brief  Config command to command register
  * @param  WIREx:Selects the OWIRE peripheral
  * @param  Command: the command to be transmitted..
  * @retval None
  */
void OWIRE_Command(OWIRE_TypeDef* WIREx, uint8_t Command)
{
	/* Check the parameters */
	assert_param(IS_OWIRE_ALL_PERIPH(WIREx));
	
	/* Set command to the command register*/
  WIREx->COMMAND = Command;
}

/**
  * @brief  Sends a data byte through the OWIRE peripheral.
  * @param  WIREx:Selects the OWIRE peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void OWIRE_SendData(OWIRE_TypeDef* WIREx, uint8_t Data)
{
	/*Check the parameters*/
	assert_param(IS_OWIRE_ALL_PERIPH(WIREx));
	
	/*Write in the DR register the data to be sent*/
  WIREx->DATA = Data;
}

/**
  * @brief  Returns the most recent received data by the OWIRE peripheral.
  * @param  WIREx:Selects the OWIRE peripheral.
  * @retval The value of the received data.
  */
uint8_t OWIRE_ReceiveData(OWIRE_TypeDef* WIREx)
{
	 /*Check the parameters*/
	 assert_param(IS_OWIRE_ALL_PERIPH(WIREx));

	/* Return the data in the DR register */
	 return (uint8_t) WIREx->DATA;
}


/**
  * @brief  Enables or disables the specified OWIRE interrupts..
  * @param  WIREx: select the OWIRE peripheral.
  * @param  OWIRE_IT: specifies the OWIRE interrupts sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg OWIRE_FLAG_RXDONE: Recive done interrupt flag
  *            @arg OWIRE_FLAG_TXDONE: Send done interrupt flag
  *            @arg OWIRE_FLAG_INITDONE:Initializes done interrupt flag
  *            @arg OWIRE_FLAG_ACKERR: ACK return errot interrupt flag
  *            @arg OWIRE_FLAG_TRXDONE: Recive and Send interrupt flag
  * @retval None.
  */
void OWIRE_ITConfig(OWIRE_TypeDef* WIREx, uint32_t OWIRE_IT, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_OWIRE_ALL_PERIPH(WIREx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_OWIRE_ALL_FLAG(OWIRE_IT));
	
	
  /*-------- Enable owire interrupt ------*/
  if (NewState != DISABLE)
  {
    /*Enable the selected OWIRE interrupts */
    WIREx->INTEN |= OWIRE_IT;
  }
  else
  {
    /*Disable the selected OWIRE interrupts */
    WIREx->INTEN &= ~(uint32_t)OWIRE_IT;
  }
}
/**
  * @brief  Checks whether the specified UART interrupt has occurred or not.
  * @param  WIREx: select the OWIRE peripheral.
  * @param  OWIRE_FLAG: select the OWIRE peripheral.
  * This parameter can be any combination of the following values:
  *            @arg OWIRE_FLAG_RXDONE: Recive done interrupt flag
  *            @arg OWIRE_FLAG_TXDONE: Send done interrupt flag
  *            @arg OWIRE_FLAG_INITDONE:Initializes done interrupt flag
  *            @arg OWIRE_FLAG_ACKERR: ACK return errot interrupt flag
  *            @arg OWIRE_FLAG_TRXDONE: Recive and Send interrupt flag
  * @retval The new state of UART_IT (SET or RESET).
  */
FlagStatus OWIRE_GetFlagStatus(OWIRE_TypeDef* WIREx, uint32_t OWIRE_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
	assert_param(IS_OWIRE_ALL_FLAG(OWIRE_FLAG));
	
  /* Check the status of the specified OWIRE flag */
  if ((WIREx->STATUS & OWIRE_FLAG) != (uint16_t)RESET)
  {
    /* OWIRE_FLAG is set */
     bitstatus = SET;
  }
  else
  {
    /* OWIRE_FLAG is reset */
     bitstatus = RESET;
  }
  /* Return the OWIRE_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clear the IT Flag 
  * @param  WIREx: select the OWIRE peripheral.
  * @param  OWIRE_IT: specifies the OWIRE interrupts sources to be enabled or disabled. 
  * This parameter can be any combination of the following values:
  *            @arg OWIRE_FLAG_RXDONE: Recive done interrupt flag
  *            @arg OWIRE_FLAG_TXDONE: Send done interrupt flag
  *            @arg OWIRE_FLAG_INITDONE:Initializes done interrupt flag
  *            @arg OWIRE_FLAG_ACKERR: ACK return errot interrupt flag
  *            @arg OWIRE_FLAG_TRXDONE: Recive and Send interrupt flag
  * @retval None.
  */
void OWIRE_ITClear(OWIRE_TypeDef* WIREx, uint16_t OWIRE_IT)
{
	/* Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
	assert_param(IS_OWIRE_ALL_FLAG(OWIRE_IT));
	/* Clear the interrupt flag of OWIRE */
	WIREx->INTCLR  = OWIRE_IT;
}


/**
  * @}
  */

/**
  * @}
  */
/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/



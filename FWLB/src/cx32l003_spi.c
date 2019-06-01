/**
  ******************************************************************************
  * @file    cx32l003_spi.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the SPI firmware functions.
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
#include "cx32l003_spi.h"
#include "cx32l003_rcc.h"

/**
  * @brief  Deinitializes the SPI peripheral registers to their default
  *         reset values .
  * @param  SPIx:Select the SPI peripheral.
  * @retval None
  */
void SPI_DeInit(SPI_TypeDef* SPIx)
{
	/* Enable SPI reset state */
	RCC_PeriphResetCmd(RCC,RCC_APBPeriph_SPIRST, ENABLE);
	/* Release SPI from reset state */
	RCC_PeriphResetCmd(RCC,RCC_APBPeriph_SPIRST, DISABLE);
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *         parameters in the SPI_InitStruct.
  * @param  SPIx:Select the SPI peripheral 
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
  *         contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  uint32_t tmpreg = 0;
  /* Check the SPI parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx)); 
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));

/*---------------------------- SPIx CR1 Configuration ------------------------*/
  /* Configure SPIx: direction, BaudRate prescaler
     master/salve mode, CPOL and CPHA */
  /* Set CPOL bit according to SPI_CPOL value */
  /* Set CPHA bit according to SPI_CPHA value */
  tmpreg |= (uint32_t) ((SPI_InitStruct->SPI_Mode) |\
	                      (SPI_InitStruct->SPI_CPOL) |\
                        (SPI_InitStruct->SPI_CPHA) |\
	                      (SPI_InitStruct->SPI_BaudRatePrescaler));
  /* Write to SPIx CR */
  SPIx->CR = tmpreg;
}

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct : pointer to a SPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
/*--------------- Reset SPI init structure parameters values -----------------*/
  /* initialize the SPI_Mode member */
  SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
  /* Initialize the SPI_CPOL member */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  /* Initialize the SPI_CPHA member */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  /* Initialize the SPI_BaudRatePrescaler member */
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
}

/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: Select the SPI peripheral
  * @param  NewState: new state of the SPIx peripheral. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral */
    SPIx->CR |= SPI_SPEN_ENABLE;
  }
  else
  {
    /* Disable the selected SPI peripheral */
    SPIx->CR &= ~SPI_SPEN_ENABLE;
  }
}

/**
  * @brief  Transmits a Data through the SPI peripheral.
  * @param  SPIx:  Select the SPI peripheral
  * @param  Data : Data to be transmitted.
  * @retval None
  */
void SPI_SendData(SPI_TypeDef* SPIx, uint32_t Data)
{  
  /*Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
	/*Write in the DR register the data to be sent */
  SPIx->DATA = Data;
}

/**
  * @brief  Returns the most recent received data by the SPI peripheral. 
  * @param  SPIx: Select the SPI peripheral
  * @retval The value of the received data.
  */
uint8_t SPI_ReceiveData(SPI_TypeDef* SPIx)
{
  /*Return the data in the DR register */
  return (SPIx->DATA);
}



/**
  * @brief  Enables or disables the SSN output for the selected SPI.
  * @param  SPIx: Select the SPI peripheral
  * @param  NewState: new state of the SPI SSN output. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /*Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /*Enable the selected SPI SS output */
    SPIx->SSN &= SPI_SSN_Low;
  }
  else
  {
    /*Disable the selected SPI SS output */
    SPIx->SSN |= SPI_SSN_High;
  }
}

/**
  * @brief  Checks whether the specified SPI flag is set or not.
  * @param  SPIx: Select the SPI peripheral
  * @param  SPI_FLAG: specifies the SPI flag to check. 
  *   This parameter can be one of the following values:
  *     @arg SPI_FLAG_SPIF: End of transmission interrupt flag
  *     @arg SPI_FLAG_WCOL: Write Conflict Interruption flag
  *     @arg SPI_FLAG_SSERR:Slave SSN error flag
  *     @arg SPI_FLAG_MDF:  Slave mode error flag
  * @retval The new state of SPI_FLAG (SET or RESET).
  */
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG)
{
	FlagStatus bitstatus = RESET;
	/*Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_FLAG(SPI_FLAG));
	/*Check the status of the specified SPI flag */
	if ((SPIx->STAT & SPI_FLAG) != (uint16_t)RESET)
	{
		/*SPI_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/*SPI_FLAG is reset */
		bitstatus = RESET;
	}
	/*Return the SPI_FLAG status */
	return  bitstatus;
}

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/


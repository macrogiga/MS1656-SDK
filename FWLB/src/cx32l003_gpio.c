/**
  ******************************************************************************
  * @file    cx32l003_gpio.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides all the GPIO firmware functions.
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
#include "cx32l003_gpio.h"
#include "cx32l003_rcc.h"

/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
   assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  if (GPIOx == GPIOA)
  {
    RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_GPIOARST, ENABLE);
    RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_GPIOARST, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_GPIOBRST, ENABLE);
    RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_GPIOBRST, DISABLE);
  }
  else if (GPIOx == GPIOC)
  {
    RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_GPIOCRST, ENABLE);
    RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_GPIOCRST, DISABLE);
  }  
  else
  {
    if (GPIOx == GPIOD)
    {
			RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_GPIODRST, ENABLE);
			RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_GPIODRST, DISABLE);
    }
  }
}

/**
  * @brief  Deinitializes the Alternate Functions (remap, event control
  *   and EXTI configuration) registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_AFIODeInit(void)
{
	GPIOA->AFR = (uint32_t)0x0;
	GPIOB->AFR = (uint32_t)0x0;
	GPIOC->AFR = (uint32_t)0x0;
	GPIOD->AFR = (uint32_t)0x0;
	
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef * GPIO_InitStruct)
{
	uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
	assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

	/* ------------------------- Configure the port pins ---------------- */
	/*-- GPIO Mode Configuration --*/
	for (pinpos = 0x00; pinpos < 0x08; pinpos++)
	{
		pos = ((uint32_t)0x01) << pinpos;
		/* Get the port pins position */
		currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

		if (currentpin == pos)
		{
			GPIOx->AFR  &= ~(GPIO_MODER_MODER0 << (pinpos * 4));
			if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
			{
				/*set gpio direction*/
				GPIOx->DIR &= ~(GPIO_PIN_OUT_MODE<<(uint8_t)pinpos);
				GPIOx->DIR |= (GPIO_PIN_OUT_MODE<<(uint8_t)pinpos);
				/* Output mode configuration*/
				GPIOx->OTYP &= ~((GPIO_OTYPER_OT_0) << ((uint8_t)pinpos)) ;
				GPIOx->OTYP |= (uint32_t)(((uint32_t)GPIO_InitStruct->GPIO_OType) << ((uint8_t)pinpos));
			}
			else
			{
				if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)
				{
				   /*set gpio direction*/
				   GPIOx->DIR &= ~(GPIO_PIN_OUT_MODE<<(uint8_t)pinpos);
				}
			}
			/* Pull-up Pull down resistor configuration*/
			GPIOx->PUPD &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
			GPIOx->PUPD |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
	}
 }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /*Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->DI & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO input data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((uint8_t)GPIOx->DI);
}


/**
  * @brief  Enable the specified GPIO port DB of SYNC_EN.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  NewState: new state of the sync_en.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_DBSyncCmd(GPIO_TypeDef* GPIOx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
	{
		GPIOx->DIDB  |= GPIO_DIDB_SYNCEN;
	}
	else
	{
		GPIOx->DIDB  &= ~GPIO_DIDB_SYNCEN;
	}
}

/**
  * @brief  Set the specified GPIOx peripheral pins DB function .
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  NewState: new state of DB function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_DBPinSyncCmd(GPIO_TypeDef* GPIOx,uint32_t DB_Pin,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
	{
		GPIOx->DIDB  |= DB_Pin;
	}
	else
	{
		GPIOx->DIDB  &= ~DB_Pin;
	}
}

/**
  * @brief  Open the specified GPIO port DB Clock enable.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  NewState: new state of DB CLock enable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void GPIO_DBClkCmd(GPIO_TypeDef* GPIOx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
	{
		GPIOx->DBCLK  |= GPIO_DBCLK_EN;
	}
	else
	{
		GPIOx->DBCLK  &= ~GPIO_DBCLK_EN;
	}
}
/**
  * @brief  Set the specified GPIO port DB Clock
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  DBClk: DB Clock of cycle .
  * @retval None.
  */
void GPIO_SetDBClk(GPIO_TypeDef* GPIOx,uint32_t DBClk)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx)) ;
	assert_param(IS_GPIO_DBCLK_CYCLE(DBClk));
	/*Set the specified GPIO port DB Clock */
	GPIOx->DBCLK  &= ~GPIO_DBCLK_CYCLEMASK;
  GPIOx->DBCLK  |= DBClk;
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if (((GPIOx->DO) & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
  return ((uint8_t)GPIOx->DO);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
   /*Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->DOSE = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /*Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->DOCL = GPIO_Pin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *         This parameter can be one of the BitAction enum values:
  * @arg    Bit_RESET: to clear the port pin
  * @arg    Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->DOSE = GPIO_Pin;
  }
  else
  {
    GPIOx->DOCL= GPIO_Pin ;
  }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  GPIOx->DO = PortVal;
}



/**
  * @brief  Toggles the specified GPIO pins..
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral 
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).                  
  * @retval None
  */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /*Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->DO ^= GPIO_Pin;
}


/**
  * @brief  Enables or disables pu pd 
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral 
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @param  GPIO_PUPD: set the GPIO peripheral port pin Pu or Pd
  * @retval None
  */
void GPIO_PinPuPdCmd(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin,uint8_t GPIO_PUPD)
{
	 /*Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
	assert_param(IS_GPIO_PUPD(GPIO_PUPD));
	
	/*set the GPIO peripheral port pin Pu or Pd*/
	GPIOx->PUPD &= ~(GPIO_PuPd_ALL << (GPIO_Pin*2));
	GPIOx->PUPD |= (GPIO_PUPD << (GPIO_Pin *2));
}

/**
  * @brief  Enables or disables DR 
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral 
	* @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @param  NewState: new state of Port DRIVER enable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_PortDRCmd(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState ==DISABLE)
	{
	  GPIOx->DR |= ((uint32_t)0x01<<GPIO_Pin);
	} 
	else 
	{
		GPIOx->DR &= ~((uint32_t)0x01<<GPIO_Pin);
	}
}


/**
  * @brief  Changes the mapping of the specified pin.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral
  * @param  GPIO_AFR: new state of the port pin remapping.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_PinRemapConfig(GPIO_TypeDef* GPIOx,uint8_t GPIO_AFR, uint8_t GPIO_Pin)
{
	uint32_t temp = 0x00,tmp = 0x00;
  /* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param( IS_GPIO_AF(GPIO_AFR));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
	
	/*Changes the mapping of the specified pin*/
	temp = GPIOx->AFR &(~((uint32_t)0x0f << GPIO_Pin));
	tmp = temp | (GPIO_AFR << (GPIO_Pin*4));
  GPIOx->AFR  = tmp;
}

/**
  * @brief   Changes the mapping of the specified pin.
  * @param   GPIOx: where x can be (A..D) to select the GPIO peripheral                    
  * @param   GPIO_PinSource: specifies the pin for the Alternate function.
  *          This parameter can be GPIO_PinSourcex where x can be (0..7).
  * @param   GPIO_AF: selects the pin to used as Alternate function.
  *          This parameter can be can be (0..7,0x0F):
  * @retval  None
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t temp = 0x00,tmp = 0x00;

  /*Check the parameters*/
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_param(IS_GPIO_AF(GPIO_AF));
  
  temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  GPIOx->AFR &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  tmp = (GPIOx->AFR )| temp;
  GPIOx->AFR  = tmp;
}
  
/**
  * @}
  */
/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/


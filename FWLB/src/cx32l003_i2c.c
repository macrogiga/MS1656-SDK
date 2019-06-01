/**
  ******************************************************************************
  * @file    cx32l003_i2c.c
  * @author  mcu Application Team
  * @version V0.0.0
  * @date    13-July-2018
  * @brief   This file provides all the I2C firmware functions.
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
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_i2c.h"
#include "cx32l003_rcc.h"




/**
  * @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
  * @param  I2Cx: select the I2C peripheral.
  * @retval None
  */
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
  if (I2Cx == I2C)
  {
		/* Enable I2C reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_I2CRST, ENABLE);
		/* Release I2C from reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_I2CRST, DISABLE);
  }

}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified 
  *   parameters in the I2C_InitStruct.
  * @param  I2Cx: select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *   contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  uint32_t tmpreg = 0; //freqrange = 0
  uint32_t result = 0x04;
	
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));
  assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
  assert_param(IS_I2C_OWN_ADDRESS(I2C_InitStruct->I2C_OwnAddress));
  assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->I2C_Ack));
 
/*----- I2Cx CR Configuration -------*/
  tmpreg = 0;

  /* Configure speed in standard mode */
  if (I2C_InitStruct->I2C_ClockSpeed <= 100000 )
  {
    /* Standard mode speed calculate */
    result = (uint16_t)(1.0*Fpclk / ((I2C_InitStruct->I2C_ClockSpeed+1) *8)+0.5-1);
		if (result < 0x04)
    {
				/* Set minimum allowed value */
				result = 0x04;  
    }
    /* Test if CCR value is under 0x4*/
    /* Set speed value for standard mode */
    tmpreg |= result;	
     //close 1M enable		
		I2Cx->CR &= 0xfe;
  }
  /* Configure speed in fast mode */
  else /*(I2C_InitStruct->I2C_ClockSpeed <= 400000)*/
  {
    if (I2C_InitStruct->I2C_ClockSpeed <= 400000)
    {
      /* Fast mode speed calculate: Tlow/Thigh = 2 */
      result = (uint16_t)(1.0*Fpclk / ((I2C_InitStruct->I2C_ClockSpeed+1) * 8)+0.5-1);
			if (result < 0x04)
      {
					/* Set minimum allowed value */
					result = 0x04;  
      }
			tmpreg |= result;	
     //close 1M enable
			 I2Cx->CR |= 0x01;
    }
    else /*I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_16_9*/
    {
      /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
       I2Cx->CR |= 0x01;
    }   
  }
  /* Write to I2Cx CCR */
  I2Cx->TM = tmpreg;
 

/*---------------------------- I2Cx CR1 Configuration ------------------------*/
  /* Get the I2Cx CR1 value */
  tmpreg = I2Cx->CR;

  /* Configure I2Cx: mode and acknowledgement */
  /* Set SMBTYPE and SMBUS bits according to I2C_Mode value */
  /* Set ACK bit according to I2C_Ack value */
  tmpreg |= (uint16_t)((uint32_t)I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack);
  /* Write to I2Cx CR1 */
  I2Cx->CR = tmpreg;

/*---------------------------- I2Cx OAR1 Configuration -----------------------*/
  /* Slave set self address */
	if((uint32_t)I2C_InitStruct->I2C_Mode == I2C_Mode_Slave)
  I2Cx->ADDR = I2C_InitStruct->I2C_OwnAddress|I2C_InitStruct->I2C_BroadcastAddress_Response;
}

/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
/*---------------- Reset I2C init structure parameters values ----------------*/
  /* initialize the I2C_ClockSpeed member */
  I2C_InitStruct->I2C_ClockSpeed = 100000;
  /* Initialize the I2C_Mode member */
  I2C_InitStruct->I2C_Mode = I2C_Mode_Slave;
  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct->I2C_OwnAddress = 0;
  /* Initialize the I2C_Ack member */
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct->I2C_BroadcastAddress_Response = 0x01;
}

/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
	
	/* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
			/* Enable the selected I2C peripheral */

			I2Cx->CR  |= CR_ENS_Set;
  }
  else
  {
			/* Disable the selected I2C peripheral */

			I2Cx->CR  &= ~CR_ENS_Set;
  }
}
/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_MasterSendCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
/* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
			/* Enable the selected I2C peripheral */
			I2Cx->TMRUN |= I2C_TMRUN_TME_Set;
			I2Cx->CR  |= CR_STA_Set;
  }
  else
  {
			/* Disable the selected I2C peripheral */
			I2Cx->TMRUN &= I2C_TMRUN_TME_Reset;
			I2Cx->CR  &= CR_STA_Set;
  }
}

/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx:select the I2C peripheral.
  * @param  NewState: new state of the I2C START condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2Cx->CR |= CR_STA_Set;
  }
  else
  {
    /* Disable the START condition generation */
    I2Cx->CR &=  CR_STA_Reset;
  }
}

/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2C STOP condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2Cx->CR |= CR_STO_Set;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2Cx->CR &= CR_STO_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C acknowledge feature.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2C Acknowledgement.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    I2Cx->CR |= CR_AA_Set;
  }
  else
  {
    /* Disable the acknowledgement */
    I2Cx->CR &= CR_AA_Reset;
  }
}

/**
  * @brief  Configures the specified I2C own address.
  * @param  I2Cx:  select the I2C peripheral.
  * @param  Address: specifies the 7bit I2C own address2.
  * @retval None.
  */
void I2C_OwnAddressConfig(I2C_TypeDef* I2Cx, uint8_t Address)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  tmpreg = I2Cx->ADDR;

  /* Reset I2Cx Own address2 bit [7:1] */
  tmpreg &= I2C_ADDR_Reset;

  /* Set I2Cx Own address2 */
  tmpreg |= (uint32_t)((uint32_t)Address & (uint32_t)0x000000FE);

  /* Store the new register value */
  I2Cx->ADDR = tmpreg;
}

/**
  * @brief  Enables or disables the specified I2C general call feature.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2C General call.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable generall call */
    I2Cx->ADDR |= I2C_ADDR_ENGC_Set;
  }
  else
  {
    /* Disable generall call */
    I2Cx->ADDR &= I2C_ADDR_ENGC_Reset;
  }
}

/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  select the I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Write in the DR register the data to be sent */
  I2Cx->DATA = Data;
}

/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: select the I2C peripheral.
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Return the data in the DR register */
  return (uint8_t)I2Cx->DATA;
}

/**
  * @brief  Transmits the address byte to select the slave device.
  * @param  I2Cx: select the I2C peripheral.
  * @param  Address: specifies the slave address which will be transmitted
  * @param  I2C_Direction: specifies whether the I2C device will be a
  *   Transmitter or a Receiver. This parameter can be one of the following values
  *     @arg I2C_Direction_Transmitter: Transmitter mode
  *     @arg I2C_Direction_Receiver: Receiver mode
  * @retval None.
  */
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));
  /* Test on the direction to set/reset the read/write bit */
   if (I2C_Direction != I2C_Direction_Transmitter)
  {
    /* Set the address bit0 for read */
    Address |= I2C_ADDR_Set;
  }
  else
  {
    /* Reset the address bit0 for write */
    Address &= I2C_ADDR_Reset;
  }
  /* Send the address */
  I2Cx->DATA = Address;
}

/**
  * @brief  Reads the specified I2C register and returns its value.
  * @param  I2C_Register: specifies the register to read.
  *   This parameter can be one of the following values:
  *     @arg I2C_Register_CR:  CR register.
  *     @arg I2C_Register_DATA:   DATA register.
  *     @arg I2C_Register_ADDR:  ADDR register.
  *     @arg I2C_Register_STAT:  OAR2 register.
  *     @arg I2C_Register_TMRUN: TMRUN register.
  *     @arg I2C_Register_TM:    TM register.
  * @retval The value of the read register.
  */
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint32_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));

  tmp = (uint32_t) I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint32_t *) tmp);
}

/**
  * @brief  Selects the specified I2C NACK position in master receiver mode.
  *         This function is useful in I2C Master Receiver mode when the number
  *         of data to be received is equal to 2. In this case, this function 
  *         should be called (with parameter I2C_NACKPosition_Next) before data 
  *         reception starts,as described in the 2-byte reception procedure 
  *         recommended in Reference Manual in Section: Master receiver.                
  * @param  I2Cx: select the I2C peripheral.
  * @param  I2C_NACKPosition: specifies the NACK position. 
  *   This parameter can be one of the following values:
  *     @arg I2C_NACKPosition_Next: indicates that the next byte will be the last
  *          received byte.  
  *     @arg I2C_NACKPosition_Current: indicates that current byte is the last 
  *          received byte.
  *            
  * @note    This function configures the same bit (POS) as I2C_PECPositionConfig() 
  *          but is intended to be used in I2C mode while I2C_PECPositionConfig() 
  *          is intended to used in SMBUS mode. 
  *            
  * @retval None
  */
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_NACK_POSITION(I2C_NACKPosition));
  
  /* Check the input parameter */
  if (I2C_NACKPosition == I2C_Ack_Enable)
  {
    /* Next byte in shift register is the last received byte */
    I2Cx->CR |= CR_AA_Set;
  }
  else
  {
    /* Current byte in shift register is the last received byte */
    I2Cx->CR &= CR_AA_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx:   select the I2C peripheral.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_IT_BUF: Buffer interrupt mask
  *            @arg I2C_IT_EVT: Event interrupt mask
  *            @arg I2C_IT_ERR: Error interrupt mask
  * @param  NewState: new state of the specified I2C interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->CR |= I2C_IT_ENABLE;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->CR &= (uint32_t)~I2C_IT_ENABLE;
  }
}

/**
  * @brief  Returns the last I2Cx Event.
  * @param  I2Cx:  select the I2C peripheral.
  *     
  * @note: For detailed description of Events, please refer to section 
  *    I2C_Events in stm32f10x_i2c.h file.
  *    
  * @retval The last event
  */
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Read the I2Cx status register */
  flag1 = I2Cx->STAT;

  /* Get the last event value from I2C status register */
  lastevent =  flag1  & FLAG_Mask;

  /* Return status */
  return lastevent;
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/


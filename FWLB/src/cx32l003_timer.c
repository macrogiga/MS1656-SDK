/**
  ******************************************************************************
  * @file    cx32l003_timer.c
  * @author  XMC Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the TIM firmware functions.
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
#include "cx32l003_timer.h"
#include "cx32l003_rcc.h"


uint8_t  basetimer0_flg = 0;
uint8_t  basetimer1_flg = 0;
/**
  * @brief  Deinitializes the TIMx peripheral registers to their default reset values.
  * @param  TIMx: Select the SPI peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @retval None
  */
void TIM_DeInit(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx)); 
 
  if (TIMx == TIM10 ||TIMx == TIM11 )
  {
		/*Enable SPI reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_BASETIMRST, ENABLE);
		/*Release SPI from reset state */
		RCC_PeriphResetCmd(RCC,RCC_APBPeriph_BASETIMRST, DISABLE);
  }     
}


/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for the 
  *         specified TIM peripheral.
  * @retval None
  */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  uint32_t tmp = 0;
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
  assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
  assert_param(IS_TIM_PRESCALE_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));
	
	/*read timer con value*/
	tmp = TIMx->CON;
	
	/*Control register value MASK Initialization*/
  tmp = tmp&TMRxCON_MASK;
	
	/*Control register value Initialization*/
  tmp	 |= (TIM_TimeBaseInitStruct->TIM_GATE_Polarity)|\
	        (TIM_TimeBaseInitStruct->TIM_GATE)|\
	        (TIM_TimeBaseInitStruct->TIM_TMRSZ)|\
	        (TIM_TimeBaseInitStruct->TIM_TMRMS)|\
          (TIM_TimeBaseInitStruct->TIM_CounterMode)|\
	        (TIM_TimeBaseInitStruct->TIM_TMROS)|\
          (TIM_TimeBaseInitStruct->TIM_ClockDivision);


  /* Generate an update event to reload the Prescaler and the Repetition counter
     values immediately */
  TIMx->CON = tmp;           
}

/**
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  TIM_TimeBaseInitStruct : pointer to a TIM_TimeBaseInitTypeDef structure which will be initialized.
  * @retval None
  */
void TIM_StructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
/*--------------- ResetTIM init structure parameters values -----------------*/
  /* initialize theTIM_ClockDivision */
  TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_Prescale_DIV0;
  /* Initialize the TIM_CounterMode */
  TIM_TimeBaseInitStruct->TIM_CounterMode= TIM_CT_COUNTER;
  /* Initialize the >TIM_GATE */
  TIM_TimeBaseInitStruct->TIM_GATE = TIM_GATE_DISABLE;
  /* Initialize the TIM_GATE_Polarity */
  TIM_TimeBaseInitStruct->TIM_GATE_Polarity = TIM_GATE_Polarity_Low;
	/* Initialize the TIM_TMRMS*/
	TIM_TimeBaseInitStruct->TIM_TMRMS=TIM_Counter_TMRMS_PERIODIC;
	/* Initialize the TIM_TMROS */
	TIM_TimeBaseInitStruct->TIM_TMROS=TIM_Counter_TMR0S_ONESHOT;
	/* Initialize the TIM_TMRSZ */
	TIM_TimeBaseInitStruct->TIM_TMRSZ= TIM_Counter_TMRSZ_32BIT;
}

/**
  * @brief  Enables or disables the specified TIM peripheral TR function.
  * @param  TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @param  NewState: new state of the TIMx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
	
  if (NewState != DISABLE)
  {
    /*Enable the TIM Counter */
    TIMx->CON |= TIM_TR_ENABLE;
  }
  else
  {
    /*Disable the TIM Counter */
    TIMx->CON   &= ~TIM_TR_ENABLE;
  }
}

/**
  * @brief  Enables or disables the specified TIM peripheral TOG function.
  * @param  TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @param  NewState: new state of the TIMx peripheral.
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_TogCmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /*Enable the TIM TOG Function*/
    TIMx->CON |= TIM_TOG_NE;
  }
  else
  {
    /*Disable the TIM TOG Function */
    TIMx->CON  &= ~TIM_TOG_NE;
  }
}


/**
  * @brief  Enables or disables the specified TIM interrupts.
  * @param  TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @param  NewState: specifies the TIM interrupts sources to be enabled or disabled.
  */
void TIM_ITConfig(TIM_TypeDef* TIMx,  FunctionalState NewState)
{  
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIMx->CON |= TIM_IT_ENABLE;
  }
  else
  {
		/* Disable the Interrupt sources */
		TIMx->CON &= ~TIM_IT_ENABLE;
  }
}


/**
  * @brief  Config TIM Counter the specified Mode  
  * @param  TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: 
  * TMER0,TMER1.
  * @param  TIM_CounterMode: specifies the Counter Mode or Timer Mode
  * @retval None
  */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint32_t TIM_CounterMode)
{
	/* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
	/*Clear function bit to zero*/
	TIMx->CON &= ~TIM_CT_COUNTER; 
	
	/*Set the specifies the Mode*/
	TIMx->CON |= TIM_CounterMode; 
}


/**
  * @brief  Select  TIMX Gate Polarity
  * @param  TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1
  * @param  TIM_GatePolarity: The Input Gate Polarity .
  * This parameter can be one of the following values:
  *     @arg TIM_GATE_Polarity_High
  *     @arg TIM_GATE_Polarity_Low         
  * @retval None 
  */
void TIM_SelectGatePolarity(TIM_TypeDef* TIMx, uint32_t TIM_GatePolarity)
{
	/*Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
	/*Clear function bit to zero*/
	TIMx->CON &= ~TIM_GATE_Polarity_Low; 
	
	/*Set the specifies the Gate polarity*/
	TIMx->CON |= ~TIM_GatePolarity;
}


/**
  * @brief  Sets the TIMx Clock Division value.
  * @param TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @param  TIM_DIV: specifies the clock division value.
  * This parameter can be one of the following value:
  *     @arg TIM_Prescale_DIV0:   TIM_DIV = Tck_tim
  *     @arg TIM_Prescale_DIV2:   TIM_DIV = Tck_tim/2
  *     @arg TIM_Prescale_DIV4:   TIM_DIV = Tck_tim/4
  *     @arg TIM_Prescale_DIV8:   TIM_DIV = Tck_tim/8
  *     @arg TIM_Prescale_DIV16:  TIM_DIV = Tck_tim/16
  *     @arg TIM_Prescale_DIV32:  TIM_DIV = Tck_tim/32
  *     @arg TIM_Prescale_DIV64:  TIM_DIV = Tck_tim/64
  *     @arg TIM_Prescale_DIV128: TIM_DIV = Tck_tim/128
  * @retval None
  */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint32_t TIM_DIV)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_PRESCALE_DIV(TIM_CKD));
  /* Reset the TIM DIV Bits */
  TIMx->CON &= ~(uint32_t)TIM_Prescale_DIV128;
  /* Set the TIM DIV value */
  TIMx->CON |= (uint32_t)TIM_DIV;
}


/**
  * @brief Gets the TIMx Prescaler value.
  * @param TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @retval Prescaler Register value.
  */
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
  /* Get the Prescaler Register value */
  return  (uint16_t)(TIMx->CON&0x07);
}


/**
  * @brief  Set Timer Load Register value
  * @param  TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @param  TIM_Value: Set to the LOAD/BGLOAD register of value
  * @retval None.
  */
void TIM_SetTimerLoadRegister(TIM_TypeDef* TIMx, uint32_t TIM_Value)
{
	/* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
	/*Set the value to the Load register*/
	TIMx->LOAD =  (uint32_t)TIM_Value ; 
	
	/*Set the value to the BGLoad register*/
	TIMx->BGLOAD = (uint32_t)TIM_Value ; 
}


/**
  * @brief  Gets the Timer Load Register's value
  * @param  TIMx: Select the TIM peripheral 
	* This parameter can be one of the following values: TMER0,TMER1.
  * @retval Counter Register value.
  */
uint32_t TIM_GetTimerLoadRegister(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
  /* Get the Timer Load Register value */
  return (TIMx->LOAD);
}


/**
  * @brief  Set the vlaue to the specified Count Register
  * @param  TIMx: Select the TIM peripheral
	* This parameter can be one of the following values: TMER0,TMER1.
  * @param  TIM_Value: Set the value into the TMRxVAL
  * @retval None
  */ 
void TIM_SetCountRegister(TIM_TypeDef* TIMx, uint32_t TIM_Value)
{
	/*Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
  /* Set the value into Counter Register*/
	TIMx->VAL = TIM_Value ;
}


/**
  * @brief  Gets the Timer count Register's value
  * @param  TIMx: Select the TIM peripheral
	* This parameter can be one of the following values: TMER0,TMER1.
  * @retval Counter Register value.
  */
uint32_t TIM_GetCountRegister(TIM_TypeDef* TIMx)
{
	/* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
  /* Get the Counter Register value */
	return  (uint32_t)(TIMx->VAL); 
}


/**
  * @brief  Gets ITSource Flag Status
  * @param  TIMx: Select the TIM peripheral
	* This parameter can be one of the following values: TMER0,TMER1.
  * @retval  The new state of TIM_ITFLAG (SET or RESET). 
  */
ITStatus TIM_GetITSourceFlagStatus(TIM_TypeDef* TIMx, uint32_t TIM_ITFLAG)
{ 
  ITStatus bitstatus = RESET;  
	
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
  
  if ((TIMx->RIS & TIM_ITFLAG) != (uint16_t)RESET)
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
  * @brief  Gets IT Flag shield Status
  * @param  TIMx: Select the TIM peripheral
	* This parameter can be one of the following values: TMER0,TMER1.
  * @retval The new state of TIM_ITFLAG (SET or RESET).
  */
ITStatus TIM_GetITShieldFlagStatus(TIM_TypeDef* TIMx, uint32_t TIM_ITFLAG)
{ 
  ITStatus bitstatus = RESET;  
	
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
  
  if ((TIMx->MIS & TIM_ITFLAG) != (uint16_t)RESET)
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
  * @brief  Clear the IT Flag 
  * @param  TIMx: Select the TIM peripheral
	* This parameter can be one of the following values: TMER0,TMER1.
  * @param  TIM_ITFLAG: The state of TIM_ITFLAG
  */
void TIM_ClearITFlag(TIM_TypeDef* TIMx, uint32_t TIM_ITFLAG)
{  
  /* Check the parameters */
  assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
  /* Clear the flags */
  TIMx->ICLR = (uint32_t)(0x01&TIM_ITFLAG);
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/

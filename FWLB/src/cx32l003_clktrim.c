/**
  ******************************************************************************
  * @file    cx32l003_clktrim.c
  * @author  clktrim Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the TIM peripheral:
  *            + TimeBase management
  *            + Output Compare management
  *            + Input Capture management
  *            + Advanced-control timers (TIM1 and TIM8) specific features  
  *            + Interrupts, DMA and flags management
  *            + Clocks management
  *            + Synchronization management
  *            + Specific interface management
  *            + Specific remapping management      
  *              
  @verbatim   
 ===============================================================================
 */
 
 /* Includes ------------------------------------------------------------------*/
#include  "cx32l003_clktrim.h"

/**
  * @brief  Config the clk trim 
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  Refclk: Reference clock
  * @param  Calclk: Calibration clock
  * @retval None
  */
void ClkTrim_ClkConfig(CLKTRIM_TypeDef*CLKTRIMx,uint32_t Refclk,uint32_t Calclk)
{
    uint32_t tmpreg = 0;
	
	/* Check the parameters */
	assert_param(IS_CLKTRMI_REFCLK_SET(Refclk));
	assert_param(IS_CLKTRMI_CALCLK_SET(Calclk));
	assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	
	tmpreg = CLKTRIMx->CR;
	
	/*Set Reference clock*/
	tmpreg  &= ~REFCLK_MASK;
	tmpreg  |= Refclk;
	
	/*Set Calibration clock*/
	tmpreg  &= ~CALCLK_MASK;
	tmpreg  |= Calclk;
	
	/*Set value to CR register*/
	CLKTRIMx->CR = tmpreg;
}

/**
  * @brief  Enable clktrim start function
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  NewState: new state of the CLKTRIM peripheral. 
  *         This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void ClkTrim_StartCmd(CLKTRIM_TypeDef*CLKTRIMx,FunctionalState NewState)
{
	  /* Check the parameters*/
	 assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	 assert_param(IS_FUNCTIONAL_STATE(NewState));
	 
  
   if(NewState != DISABLE)
	 {
		   /*enable clktrim function*/
		  CLKTRIMx->CR |= CLK_TMRIM_START;
	 }
	 else
	 {
		  /*disable clktrim function*/
		  CLKTRIMx->CR &= ~CLK_TMRIM_START;
	 }
}

/**
  * @brief  Enable clktrim Monitor function
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  NewState: new state of the CLKTRIM peripheral. 
  *         This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */ 
void ClkTrim_MonitorCmd(CLKTRIM_TypeDef*CLKTRIMx,FunctionalState NewState)
{
	  /* Check the parameters */
	 assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	 assert_param(IS_FUNCTIONAL_STATE(NewState));
	 
	
   if(NewState != DISABLE)
	 {
		  /*enable the Monitor function*/
		  CLKTRIMx->CR |= CLK_MON_ENABLE;
	 }
	 else
	 {
		  /*disable the Monitor function*/
		  CLKTRIMx->CR &= ~CLK_MON_ENABLE;
	 }
}

/**
  * @brief  Enable clktrim clk function
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  NewState: new state of the CLKTRIM peripheral. 
  *         This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */ 
void ClkTrim_ClkCmd(CLKTRIM_TypeDef*CLKTRIMx,FunctionalState NewState)
{
	 /* Check the parameters */
	 assert_param(IS_FUNCTIONAL_STATE(NewState));
	 assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	
   if(NewState != DISABLE)
	 {
		  /* enable clk function */
		  CLKTRIMx->CR |= CLK_REFCALCLK_ENABLE;
	 }
	 else
	 {
		  /* disable clk function */
		  CLKTRIMx->CR &= ~CLK_REFCALCLK_ENABLE;
	 }
}

/**
  * @brief  Set Rload count value
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  Value: 
  * @retval None
  */ 
void ClkTrim_SetRcntValue(CLKTRIM_TypeDef*CLKTRIMx,uint32_t Value)
{
	 /* Check the parameters */
	 assert_param(IS_CLKTRMI_RCNT_VALUE(Value));
	 assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	
	/*Set value to REFCON register*/
   CLKTRIMx->REFCON = Value;
}


/**
  * @brief  Set clktrim clk function
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  Value: the value of Calibration
  * @retval None
  */ 
void ClkTrim_SetCalValue(CLKTRIM_TypeDef*CLKTRIMx,uint32_t Value)
{
	 /* Check the parameters */
	 assert_param(IS_CLKTRMI_CAL_VALUE(Value));
	 assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	/*Set the value to calcon register*/
   CLKTRIMx->CALCON = Value;
}


/**
  * @brief  Gets clktrim Reference count register 
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @retval None
  */ 
uint32_t ClkTrim_GetRefValue(CLKTRIM_TypeDef*CLKTRIMx)
{
	 /* Check the parameters */
	 assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	
	 /* Return clktrim refcnt value */
   return (CLKTRIMx->REFCNT);
}

/**
  * @brief  Gets clktrim Calibration count register 
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  NewState: new state of the CLKTRIM peripheral. 
  *         This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */ 
uint32_t ClkTrim_GetCalValue(CLKTRIM_TypeDef*CLKTRIMx)
{
	 /* Check the parameters */
	 assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	
   /* Return clktrim Calibration value */
   return(CLKTRIMx->CALCNT);
}

/**
  * @brief  enable clktrim interrupt function 
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  NewState: new state of the CLKTRIM peripheral. 
  *         This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */ 
uint32_t ClkTrim_ITCmd(CLKTRIM_TypeDef*CLKTRIMx,FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));

	if(NewState!= DISABLE)
	{
		/*enable clktrim interrupt*/
		CLKTRIMx->CR |= CLKTRIM_IE_ENABLE;
	}
	else
	{
		/*disable clktrim interrupt*/
		CLKTRIMx->CR &= ~CLKTRIM_IE_ENABLE;
	}
    
    return 1;
}

/**
  * @brief  Gets CLKTRIM flag status
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  CLKTRIM_FLAG: 
	*				@arg CLKTRIM_FLAG_STOP       ((uint32_t)0x00000001)
	*				@arg CLKTRIM_FLAG_CALCNTOF   ((uint32_t)0x00000002)
	*				@arg CLKTRIM_FLAG_LXTFAULT   ((uint32_t)0x00000004)
	*				@arg CLKTRIM_FLAG_HXTFAULT   ((uint32_t)0x00000008)
	*				@arg CLKTRIM_FLAG_HXTSTOP    ((uint32_t)0x00000010)
	*				@arg CLKTRIM_FLAG_X32KSTOP   ((uint32_t)0x00000020)
  * @retval The new state of CLKTRIM_FLAG (SET or RESET).
  */ 
FlagStatus ClkTrim_GetFlagStatus(CLKTRIM_TypeDef*CLKTRIMx, uint16_t CLKTRIM_FLAG)
{
    FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	assert_param(IS_CLKTRMI_FLAG(CLKTRIM_FLAG));
	
  /*GET FLAG VALUE*/
  if ((CLKTRIMx->IFR & CLKTRIM_FLAG) != (uint16_t)RESET)
  {
			bitstatus = SET;
  }
  else
  {
			bitstatus = RESET;
  }
	
  return bitstatus;
}

/** @brief  Clear the interrupt flag
  * @param  CLKTRIMx: Set the CLKTRIM peripheral.
  * @param  CLKTRIM_FLAG: 
	*				@arg CLKTRIM_FLAG_STOP       ((uint32_t)0x00000001)
	*				@arg CLKTRIM_FLAG_CALCNTOF   ((uint32_t)0x00000002)
	*				@arg CLKTRIM_FLAG_LXTFAULT   ((uint32_t)0x00000004)
	*				@arg CLKTRIM_FLAG_HXTFAULT   ((uint32_t)0x00000008)
	*				@arg CLKTRIM_FLAG_HXTSTOP    ((uint32_t)0x00000010)
	*				@arg CLKTRIM_FLAG_X32KSTOP   ((uint32_t)0x00000020)
  * @retval None
  */
void ClkTrim_ClearFlagStatus(CLKTRIM_TypeDef*CLKTRIMx, uint16_t CLKTRIM_FLAG)
{
	 /* Check the parameters */
  assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	assert_param(IS_CLKTRMI_FLAG(CLKTRIM_FLAG));
	
	/*clear clktrim flag*/
  CLKTRIMx->ICLR  = CLKTRIM_FLAG;
}

/************************ (C) COPYRIGHT cx32l003 *****END OF FILE****/


















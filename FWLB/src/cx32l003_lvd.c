/**
  ******************************************************************************
  * @file    cx32l003_lvd.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    15-10-2018
  * @brief   This file provides all the lvd firmware functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/*Includes -------------------------*/
#include "cx32l003_lvd.h"


/** @brief  LVD  partial pressure coefficient setting
  * @param  LVDx:Selects the lvd peripheral
	* @param  LEVELDIV:partial pressure coefficient
	* @retval None
  */
void LVD_DIV_SEL(LVD_TypeDef *LVDx,uint32_t  LEVELDIV)
{
	uint32_t tmgreg = 0;
	/* Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
	
	/*Read the value of lvd CR register*/
	tmgreg = LVD->CR;
	
   /*Reset the lvd level bit to zero*/
	tmgreg &= ~LVD_LEVEL_DIV_MASK;
	
	/*Set the value of level division*/
	tmgreg |= LEVELDIV;
	
	/*Set the value of level division to the CR register*/
	LVD->CR = tmgreg;
}


/** @brief  Enables LVD function
  * @param  LVDx:Selects the lvd peripheral
  * @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_Cmd(LVD_TypeDef *LVDx,FunctionalState NewState)
{	
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
	{
		/*Enable the lvd function*/
		LVD->CR |= LVD_ENABLE;
	}
	else
	{  
		/*Disable the lvd function*/
		LVD->CR &= ~LVD_ENABLE;
	} 
}

/** @brief  Enables LVD ACT RESET function  
  * @param  LVDx:Selects the lvd peripheral
  * @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_ActResetCmd(LVD_TypeDef *LVDx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
  if(NewState != DISABLE)
	{
		/*Enable the act reset function*/
		LVD->CR  |= LVD_ACT_RESET;
	}
	else
	{
	  /*Enable the act interrupt function*/
		LVD->CR  &= ~LVD_ACT_RESET;
	}
}

/** @brief Enables LVD ACT Interrupt function  
  * @param  LVDx:Selects the lvd peripheral
  * @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_ActIntCmd(LVD_TypeDef *LVDx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if(NewState != DISABLE)
	{
		/*Enable the act interrupt function*/
		LVD->CR  &= ~LVD_ACT_RESET;
	}
	else
	{
		/*Enable the act reset function*/
		LVD->CR  |= LVD_ACT_RESET;
	}
}

/** @brief Enable the FLT Function
  * @param  LVDx:Selects the lvd peripheral
  * @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_FLTEnCmd(LVD_TypeDef *LVDx,FunctionalState NewState)
{
  /*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*Open the flt function*/
		LVD->CR |= LVD_FLT_ENABLE;
	else
		/*Close the flt function*/
		LVD->CR &= ~LVD_FLT_ENABLE;
}

/** @brief  Set the flt clk function
  * @param  LVDx:Selects the lvd peripheral
  * @param  FltClk: the value of flt clock
  * @retval None
  */
void LVD_SetFltClk(LVD_TypeDef *LVDx,uint32_t FltClk)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FLTCLK_SEL(FltClk));
	
	/*Set debounce time bit*/
	LVD->CR &= ~FLTCLK_SEL_MASK;
	/*Set funciton debounce time*/
	LVD->CR |= FltClk;
}

/** @brief LVD Set Debounce Time 
  * @param  LVDx:Selects the lvd peripheral
  * @param  FltNum:Selects the lvd flt parameter
  * @retval None
  */
void LVD_SetFltNum(LVD_TypeDef *LVDx,uint32_t FltNum)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FLT_NUM(FltNum));
	/*set DEBOUNCE TIME bit->0*/
	LVD->CR  &= ~FLT_NUM_MASK;
	/*set funciton DEBOUNCE TIME*/
	LVD->CR |= FltNum;
}

/** @brief  Enable lvd fall interrupt mode 
  * @param  LVDx:Selects the lvd peripheral
  * @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_FallITCmd(LVD_TypeDef *LVDx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*enable fall interrupt */
		LVD->CR |= LVD_FALLINT_ENABLE;
	else
		/*disable fall interrupt */
	  LVD->CR &= ~LVD_FALLINT_ENABLE;
}

/** @brief  Enable lvd rise interrupt mode 
  * @param  LVDx:Selects the lvd peripheral
  * @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_RiseITCmd(LVD_TypeDef *LVDx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*enable rise interrupt */
		LVD->CR |= LVD_RISEINT_ENABLE;
	else
		/*disable rise interrupt */
	  LVD->CR &= ~LVD_RISEINT_ENABLE;
}

/** @brief  Enable lvd high interrupt mode 
  * @param  LVDx:Selects the lvd peripheral
  * @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_HighITCmd(LVD_TypeDef *LVDx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*enable high interrupt */
		LVD->CR |= LVD_HIGHINT_ENABLE;
	else
		/*disable high interrupt */
	  LVD->CR &= ~LVD_HIGHINT_ENABLE;
}

/** @brief  Enable lvd interrupt mode 
  * @param  LVDx:Selects the lvd peripheral
  * @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_ITConfig(LVD_TypeDef *LVDx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*enable interrupt */
		LVD->CR |= LVD_TI_ENABLE;
	else
		/*disable interrupt */
	  LVD->CR &= ~LVD_TI_ENABLE;
}


/**
  * @brief  Checks whether the interrupt flag is set or not.
  * @param  LVDx:Selects the lvd peripheral
  * @param  LVD_FLAG: Lvd interrupt flag
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
  */
FlagStatus LVD_GetFlagStatus(LVD_TypeDef *LVDx,uint16_t LVD_FLAG)
{
  FlagStatus bitstatus = RESET;
	
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
    
  if (((LVD->IR)&LVD_FLAG) != (uint32_t)RESET)
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
  * @brief  Clear the interrupt flag 
  * @param  LVDx:Selects the lvd peripheral
  * @retval None
  */
void LVD_ClearITFlag(LVD_TypeDef *LVDx)
{
	/*Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
	/*Clear the lvd interrupt flag*/
  LVD->IR = 0x00;
}





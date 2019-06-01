/**
  ******************************************************************************
  * @file    cx32l003_vc.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    15-10-2018
  * @brief   This file provides all the vc firmware functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under mcu Liberty SW License Agreement V2, (the "License");
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
#include "cx32l003_vc.h"

/** @brief  Config vc gpio pin
  * @param  VCx:Selects the vc peripheral
	* @param  PIN:Selects gpio pin
	* @retval None
  */
void VC_SetPin(VC_TypeDef *VCx,uint32_t PIN)
{
	/*Check the parameters*/
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(VC_PIN_SEL(PIN));
	
	/*Set Pin Mask*/
	VCx->PCR &= ~VC_PIN_MASK;
	/*Set Pin*/
	VCx->PCR |= PIN;	
}

/** @brief  Config vc gpio  pin of NA
  * @param  VCx:Selects the vc peripheral
	* @param  PIN:Selects gpio pin
	* @retval None
  */
void VC_SetNin(VC_TypeDef *VCx,uint32_t NIN)
{
	/*Check the parameters*/
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(VC_NIN_SEL(NIN));
	
	/*Set Nin Mask*/
	VCx->PCR &= ~VC_NIN_MASK;
	/*Set Nin*/
	VCx->PCR |= NIN;	
}

/** @brief  Config vc divsion
  * @param  VCx:Selects the vc peripheral
	* @param  V25DIV:config parameters
	* @retval None
  */
void VC_SetV25Div(VC_TypeDef *VCx,uint32_t V25DIV)
{
	/*Check the parameters*/
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(VC_V25DIV_SEL(V25DIV));
	
	/*Set Nin Mask*/
	VCx->PCR &= ~VC_V25DIV_MASK;
	/*Set Nin*/
	VCx->PCR |= V25DIV;	
}

/** @brief  enable vc25 divsion
  * @param  VCx:Selects the vc peripheral
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_V25DivCmd(VC_TypeDef *VCx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*open v25div */
		VCx->PCR |= V25DIV_ENABLE;
	else
		/*close v25div */
		VCx->PCR &= ~V25DIV_ENABLE;   
}

/** @brief  enable vc function
  * @param  VCx:Selects the vc peripheral
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_Cmd(VC_TypeDef *VCx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*enable vc function */
		VCx->CR |= VC_ENABLE;
	else
		/*disable vc function */
		VCx->CR &= ~VC_ENABLE;   
}

/** @brief  Set vc flt clock
  * @param  VCx:Selects the vc peripheral
	* @param  FLTCLK: the flt clock
	* @retval None
  */
void VC_SetFltClk(VC_TypeDef *VCx,uint32_t FLTCLK)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(VC_FLTCLK_SEL(FLTCLK));
	
	/*Set flt clock */
	VCx->CR &=  ~VC_FLTCLK_MASK;
	VCx->CR |=  FLTCLK;
}

/** @brief  Enable flt function
  * @param  VCx:Selects the vc peripheral
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_FLTCmd(VC_TypeDef *VCx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*enable flt function */
		VCx->CR |= VC_FLT_ENABLE;
	else
		/*disable flt function */
		VCx->CR &= ~VC_FLT_ENABLE;   
}

/** @brief  Enable Fall interrupt function
  * @param  VCx:Selects the vc peripheral
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_FallITCmd(VC_TypeDef *VCx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*Enable fall interrupt function*/
		VCx->CR |= VC_FALLINT_ENABLE;
	else
		/*Disable fall interrupt function*/
	  VCx->CR &= ~VC_FALLINT_ENABLE;
}

/** @brief  Enable Rise interrupt function
  * @param  VCx:Selects the vc peripheral
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_RiseITCmd(VC_TypeDef *VCx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*Enable the rise interrupt function*/
		VCx->CR |= VC_RISEINT_ENABLE;
	else
		/*Disable the rise interrupt function*/
	  VCx->CR &= ~VC_RISEINT_ENABLE;
}

/** @brief  Enable High interrupt function
  * @param  VCx:Selects the vc peripheral
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_HighITCmd(VC_TypeDef *VCx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*Enable the high interrupt function*/
		VCx->CR |= VC_HIGHINT_ENABLE;
	else
		/*Disable the high interrupt function*/
	  VCx->CR &= ~VC_HIGHINT_ENABLE;
}

/** @brief  Enable High interrupt function
  * @param  VCx:Selects the vc peripheral
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_SetFltNum(VC_TypeDef *VCx,uint32_t FltNum)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_VC_FLTNUM(FltNum));
	
	/*Set the flt parameters */
	VCx->CR &= ~VC_FLTNUM_MASK;
	VCx->CR |= FltNum;
}


/** @brief  Enable out config function
  * @param  VCx:Selects the vc peripheral
  * @param  OutCfgStatus:the value of out config
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_OutConfigCmd(VC_TypeDef *VCx,uint32_t OutCfgStatus,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_VC2_Status(OutCfgStatus));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*Enable the out  config */
		VCx->OUTCFG  |= OutCfgStatus;
	else
		/*Disable the out  config */
		VCx->OUTCFG  &= ~OutCfgStatus;
}

/** @brief  Enable vc interrupt function
  * @param  VCx:Selects the vc peripheral
	* @param  NewState: new state of the LVDx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
	* @retval None
  */
void VC_ITConfig(VC_TypeDef *VCx,FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
		/*Enable the  interrupt*/
		VCx->CR |= VC_TI_ENABLE;
	else
		/*Disable the  interrupt*/
	  VCx->CR &= ~VC_TI_ENABLE;
}

/**
  * @brief  Checks whether the interrupt flag is set or not.
  * @param  VCx:Selects the vc peripheral
  * @param  VC_FLAG: VC interrupt flag
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
  */
FlagStatus VC_GetFlagStatus(VC_TypeDef *VCx,uint16_t VC_FLAG)
{
  FlagStatus bitstatus = RESET;
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    
  if (((VCx->IR)&VC_FLAG) != (uint32_t)RESET)
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
  * @param  VCx:Selects the vc peripheral
  * @retval None
  */
void VC_ClearITFlag(VC_TypeDef *VCx)
{
	/*Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
	/*Clear the vc interrupt flag */
  VCx->IR = 0x00;
}











 






/**
  ******************************************************************************
  * @file    cx32l003_LPTIMER.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file provides firmware functions to manage the SYSCFG peripheral.
  *
 @verbatim
    
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..] This driver provides functions for:
            
       (#) Remapping the memory accessible in the code area using SYSCFG_MemoryRemapConfig()
            
       (#) Swapping the internal flash Bank1 and Bank2 this features is only visible for 
           STM32F42xxx/43xxx devices Devices. 
                
       (#) Manage the EXTI lines connection to the GPIOs using SYSCFG_EXTILineConfig()
              
       (#) Select the ETHERNET media interface (RMII/RII) using SYSCFG_ETH_MediaInterfaceConfig()
  
       -@- SYSCFG APB clock must be enabled to get write access to SYSCFG registers,
           using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
                   
 @endverbatim      
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

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_lptimer.h"

/**
  * @brief  read cnt register
  * @param  None
  * @retval the cnt register value
  */
uint32_t LPTIMER_ReadCnt(void)
{
   return  ((uint32_t)(LPTIMER->CNT));
}

/**
  * @brief  Initializes the LPTIMERx Time Base Unit peripheral according to 
  *         the specified parameters in the LPTIMER_InitStruct.
  * @param  LPTIMERx:Selects the LPTIMER peripheral
  * @param  LPTIMER_InitStruct: pointer to a LPTIMER_InitTypeDef structure that contains 
  *         the configuration information for the RTC peripheral.
  * @retval None
  */
void  LPTIMER_Init(LPTIMER_TypeDef* LPTIMERx, LPTIMER_InitTypeDef * LPTIMER_InitStruct)
{
  uint32_t tmpreg;
	/* Check the parameters */
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
  assert_param(IS_LPTIMER_MODE(LPTIMER_InitStruct->LPTIMER_Mode));
	assert_param(IS_LPTIMER_CT(	LPTIMER_InitStruct->LPTIMER_CTEN));
	assert_param(IS_LPTIMER_TCLK(LPTIMER_InitStruct->LPTIMER_TCLK));
	assert_param(IS_LPTIMER_GATE(LPTIMER_InitStruct->LPTIMER_GATEEN));
	assert_param(IS_LPTIMER_GATEPOLE(LPTIMER_InitStruct->LPTIMER_GATEPOLE));
	assert_param(IS_LPTIMER_CUT(LPTIMER_InitStruct->LPTIMER_TCLKCUTEN));
	
	/*read cr register*/
	tmpreg = LPTIMERx->CR;
	
  /*set mode*/
	tmpreg &= ~LPTIMER_Mode_MASK;
	tmpreg |= LPTIMER_InitStruct->LPTIMER_Mode;
	
	/*set CT*/
	tmpreg &= ~LPTIMER_CT_MASK;
	tmpreg |= LPTIMER_InitStruct->LPTIMER_CTEN;
	
	/*set TCKL*/
	tmpreg &= ~LPTIMER_TCLK_MASK;
	tmpreg |= LPTIMER_InitStruct->LPTIMER_TCLK;
	
	/*set GATE*/
	tmpreg &= ~LPTIMER_GATE_MASK;
	tmpreg |= LPTIMER_InitStruct->LPTIMER_GATEEN;
	
	/*set GATEPOLE*/
	tmpreg &= ~LPTIMER_GATEPOLE_MASK;
	tmpreg |= LPTIMER_InitStruct->LPTIMER_GATEPOLE;
	
	/*set TCLKCUT*/
	tmpreg &= ~LPTIMER_TCLKCUT_MASK;
	tmpreg |= LPTIMER_InitStruct->LPTIMER_TCLKCUTEN;
	
	LPTIMERx->CR = tmpreg;
}

/**
  * @brief  Enable LPTIMER function
  * @param  LPTIMERx:Selects the LPTIMER peripheral
  * @param  NewState: new state of the LPTIMER peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIMER_Cmd(LPTIMER_TypeDef* LPTIMERx,FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
	{
		/*set lptimer run enable*/
		LPTIMERx->CR |= LPTIMER_RUN_ENABLE;
	}
	else
	{
		/*set lptimer run disable*/
		LPTIMERx->CR &= ~LPTIMER_RUN_ENABLE;
	}
}

/**
  * @brief  Enable LPTIMER tog function
  * @param  LPTIMERx:Selects the LPTIMER peripheral
  * @param  NewState: new state of the LPTIMER peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIMER_TogCmd(LPTIMER_TypeDef* LPTIMERx,FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
	{
		/*set lptimer run enable*/
		LPTIMERx->CR |= LPTIMER_TOG_ENABLE;
	}
	else
	{
		/*set lptimer run disable*/
		LPTIMERx->CR &= ~LPTIMER_TOG_ENABLE;
	}
}

/**
  * @brief  Config LPTIMER  Interrupt
  * @param  LPTIMERx: Selects the LPTIMER peripheral
  * @param  NewState: new state of the LPTIMER peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIMER_ITConfig(LPTIMER_TypeDef* LPTIMERx,FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
	{
		/*set lptimer run enable*/
		LPTIMERx->CR |= LPTIMER_IT_ENABLE;
	}
	else
	{
		/*set lptimer run disable*/
		LPTIMERx->CR &= ~LPTIMER_IT_ENABLE;
	}
}

/**
  * @brief  Gets the WT Flags of LPTIMER
  * @param  LPTIMERx:Selects the LPTIMER peripheral
  * @retval The new state of FlagStatus (SET or RESET).
  */
FlagStatus LPTIMER_GetWTFlagStatus(LPTIMER_TypeDef* LPTIMERx)
{
	FlagStatus bitstatus = RESET;
	
	/* Check the parameters*/
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
	
  if ((LPTIMERx->CR & LPTIMER_WT_FLAG) != (uint16_t)RESET)
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
  * @brief  Config LPTIMER bgload
  * @param  LPTIMERx:Selects the LPTIMER peripheral
  * @param  Value: Set value to BGLOAD register
  * @retval None
  */
void LPTIMER_BGloadConfig(LPTIMER_TypeDef* LPTIMERx, uint32_t Value)
{
	__IO uint32_t initcounter = 0x00;
  uint32_t initstatus = 0x00;
	/* Check the parameters */
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
	assert_param(IS_LPTIMER_BGLOAD(Value));
	
	/* Wait till LPTIMERx WT FLAG  be cleared zero */
	do
	{
		initstatus = LPTIMERx->CR & LPTIMER_WT_FLAG;
	} while(initstatus == LPTIMER_WT_FLAG);
	
	/* set LPTIMERx VALUE */
	LPTIMERx->BGLOAD = Value;
}


/**
  * @brief  Config LPTIMER Load
  * @param  LPTIMERx:Selects the LPTIMER peripheral
  * @param  Value: Set value to LOAD register
  * @retval None
  */
void LPTIMER_LoadConfig(LPTIMER_TypeDef* LPTIMERx, uint32_t Value)
{
	__IO uint32_t initcounter = 0x00;
  uint32_t initstatus = 0x00;
	/* Check the parameters */
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
	assert_param(IS_LPTIMER_LOAD(Value));
	
	/* Wait till LPTIMERx WT FLAG  be cleared zero */
	do
	{
		initstatus = LPTIMERx->CR & LPTIMER_WT_FLAG;
	} while(initstatus == LPTIMER_WT_FLAG);
	/* set LPTIMERx VALUE */
	LPTIMERx->LOAD = Value;
}

/**
  * @brief  Get LPTIMER ITStatus
  * @param  LPTIMERx:Selects the LPTIMER peripheral
  * @param  IntFlag: LPTIMER interruption of flag
  * @retval None
  */
ITStatus LPTIMER_GetITStatus(LPTIMER_TypeDef* LPTIMERx, uint32_t IntFlag)
{
	ITStatus bitstatus = RESET;
	/* Check the parameters */
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
	assert_param(IS_LPTIMER_IT(IntFlag));
	
	/*get the it flag*/
	if((LPTIMERx->IR)& IntFlag)
	{
	  bitstatus = SET;
	}
	else
	{
	  bitstatus = RESET;
	}
	/*return the it flag*/
  return bitstatus;
}


/**
  * @brief  Clear LPTIMER ITStatus flag
  * @param  LPTIMERx:Selects the LPTIMER peripheral
  * @param  IntFlag:LPTIMER interruption of flag
  * @retval None
  */
void LPTIMER_ClearITFlag(LPTIMER_TypeDef* LPTIMERx ,uint32_t IntFlag)
{
	/*Check the parameters */
	assert_param(IS_LPTIMER_ALL_PERIPH(LPTIMERx));
	assert_param(IS_LPTIMER_IT(IntFlag));
	
  /*Clear IT Flag*/
  LPTIMERx->ICLR = IntFlag;

}


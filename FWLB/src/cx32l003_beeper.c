/**
  ******************************************************************************
  * @file    cx32l003_beeper.c
  * @author  MCU Application Team
  * @version V1.4.0
  * @date    15-10-2018
  * @brief   This file provides all the CRC firmware functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include  "cx32l003_beeper.h"
#include  "cx32l003_rcc.h"

/**
  * @brief  Deinitializes the BEEPER peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void BEEPER_DeInit(void)
{
	/*Enable Beeper reset state */
	RCC_PeriphResetCmd(RCC,RCC_APBPeriph_BEEPRST, ENABLE);
	/*Release Beeper from reset state */
	RCC_PeriphResetCmd(RCC,RCC_APBPeriph_BEEPRST, DISABLE);  
}



/** @brief Set Beeper_Prescaler
  * @param  BEEPERx: Selects the BEEPER peripheral
  * @param  BeeperPrescaler: Selects the BEEPER Prescaler
  * @retval None
  */
void BEEPER_SetPrescaler(BEEPER_TypeDef *BEEPERx,uint32_t BeeperPrescaler)
{
  /* Check the parameters */
	assert_param(IS_BEEPER_ALL_PERIPH(BEEPERx));
	assert_param(IS_BEEPER_PRESCALER(BeeperPrescaler));
	/*Set the value to the CSR register*/
  BEEPERx->BEEP_CSR &= ~BEEPERDIV_MASK; 
	BEEPERx->BEEP_CSR |= BeeperPrescaler;
}


/** @brief  BEEPER select prescaler
  * @param  BEEPERx: Selects the BEEPER peripheral
  * @param  PreClk:  Selects the BEEPER peripheral output frequency
  * @retval None
  */
void BEEPER_SelectPrescaler(BEEPER_TypeDef *BEEPERx,uint32_t PreClk)
{
  /* Check the parameters */
	assert_param(IS_BEEPER_ALL_PERIPH(BEEPERx));
	assert_param(IS_BEEPER_CLOCKSEL(PreClk));
	
	/*Set the output frequency of beeper*/
  BEEPERx->BEEP_CSR &= ~BEEPERSELECT_MASK; 
	BEEPERx->BEEP_CSR |= PreClk;
}

/** @brief Enables BEEPER peripheral
  * @param  BEEPERx: Selects the BEEPER peripheral
  * @param  NewState: new state of the WWDG peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  */
void BEEPER_Cmd(BEEPER_TypeDef *BEEPERx,FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState!= DISABLE)
	{
		/* Enable beeper function */
		BEEPERx->BEEP_CSR |= BEEPER_ENABLE;
	} 
	else 
	{
		/* Disable beeper function */
		BEEPERx->BEEP_CSR &= ~BEEPER_ENABLE;
	}
}


/** @brief Set Beeper Clock
  * @param  BEEPERx: Selects the BEEPER peripheral
  * @param  CLK: Selects the BEEPER peripheral
  * @{
  */
void BEEPER_SetClock(BEEPER_TypeDef *BEEPERx,uint32_t CLK)
{
  /* Check the parameters */
	assert_param(IS_BEEPER_SELECLOCK(CLK));
	
	/* Set Clock  parameters to the CSR register*/
	BEEPERx->BEEP_CSR  &=  ~BEEPERCLOCK_MASK;
	BEEPERx->BEEP_CSR  |=  CLK;
}

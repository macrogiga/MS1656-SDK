/**
  ******************************************************************************
  * @file    cx32l003_syscon.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the syscon firmware functions.
  *
 @verbatim
    
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..] This driver provides functions for:
            
       (#) Remapping the memory accessible in the code area using SYSCFG_MemoryRemapConfig()
            
       (#) Swapping the internal flash Bank1 and Bank2 this features is only visible for 
           cx32l003 devices Devices. 
                
       (#) Manage the EXTI lines connection to the GPIOs using SYSCFG_EXTILineConfig()
              
       (#) Select the ETHERNET media interface (RMII/RII) using SYSCFG_ETH_MediaInterfaceConfig()
  
       -@- SYSCFG APB clock must be enabled to get write access to SYSCFG registers,
           using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
                   
 @endverbatim      
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
#include "cx32l003_syscon.h"
#include "cx32l003_rcc.h"

/**
  * @brief  Deinitializes the SYSCTRL Functions 
  *   registers to their default reset values.
  * @param  None
  * @retval None
  */
void SYSCTRL_DeInit(void)
{
   RCC_PeriphResetCmd(RCC,RCC_APBPeriph_SYSCONRST, ENABLE);
   RCC_PeriphResetCmd(RCC,RCC_APBPeriph_SYSCONRST, DISABLE);
}

/**
  * @brief  Enables M0 Lock up function
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  NewState: new state of the LPUART mode.
  *   This parameter can be: ENABLE or DISABLE.    
  * @retval None
  */
void SYSCTRL_CortexM0LockUpCmd(SYSCON_TypeDef *SYSCTRLx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	
	 /*Close lock */
  SYSCTRLx->SYSCON_UNLOCK = SYSCTRL_UNLOCKKEY;
	
	if(NewState != DISABLE)
	{
	  SYSCTRLx->SYSCTRLCFG0 |= SYSCTRL_LOCKUP_EN;
	}
	else
	{
		SYSCTRLx->SYSCTRLCFG0 &= ~SYSCTRL_LOCKUP_EN;
	}
	
	 /*Open lock */
	SYSCTRLx->SYSCON_UNLOCK = SYSCTRL_LOCKKEY;
}

/**
  * @brief  Enables or disables the Deep sleep Port interrupts.
  *   
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  NewState: new state of the LPUART mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_DeepsleepPortITCmd(SYSCON_TypeDef *SYSCTRLx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	
	if(NewState != DISABLE)
	{
	  SYSCTRLx->PORTINTMODE |= SYSCTRL_DEEPSLEEPPORTINT_EN;
	}
	else
	{
		SYSCTRLx->SYSCTRLCFG0 &= ~SYSCTRL_DEEPSLEEPPORTINT_EN;
	}
}

/**
  * @brief  Enables or disables Active Sleep Port interrupts
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  NewState: new state of the Active Sleep Port.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_ActiveSleepPortITCmd(SYSCON_TypeDef *SYSCTRLx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	
	if(NewState != DISABLE)
	{
	  SYSCTRLx->PORTINTMODE &= SYSCTRL_ACTIVESLEEPPORTINT_EN;
	}
	else
	{
		SYSCTRLx->SYSCTRLCFG0  |= ~SYSCTRL_ACTIVESLEEPPORTINT_EN;
	}
}

/**
  * @brief  Config the SPI peripheral cs singnal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  SYSCTRL_SPINSS_PIN : selects the GPIO port pin to be used as 
            SPI peripheral cs signal
  * @retval None
  */
void SYSCTRL_SPICSConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_SPINSS_PIN)
{
  /* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
  assert_param(IS_SPINSS_PORT_PIN(SPINSS_PIN));
	/*SET SPINSS*/
	SYSCTRLx->PORTCTRL0  &= ~SPINSS_SEL_MASK;
	SYSCTRLx->PORTCTRL0  |= SYSCTRL_SPINSS_PIN;
}

/**
  * @brief  Config TIM10 GATE singnal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  SYSCTRL_TIM10_GATE: TIM10 GATE signal parameter
  * @retval None 
  */
void SYSCTRL_TIM10_GateConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_TIM10_GATE) 
{ 
	/* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
  assert_param(IS_TIM0_GATE_SEL(SYSCTRL_TIM0_GATE)); 
	
  /* Configure TIM0 GATE selection PIN */ 
	SYSCTRLx->PORTCTRL0  &=  ~TIM10_GATE_MASK;
	SYSCTRLx->PORTCTRL0  |=  SYSCTRL_TIM10_GATE;
}


/**
  * @brief  Config TIM11 GATE singnal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  SYSCTRL_TIM10_GATE: TIM11 GATE signal parameter
  * @retval None 
  */
void SYSCTRL_TIM11_GateConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_TIM11_GATE) 
{ 
	/* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
  assert_param(IS_TIM1_GATE_SEL(SYSCTRL_TIM11_GATE)); 
	
  /* Configure TIM1 GATE selection PIN */ 
	SYSCTRLx->PORTCTRL0  &=  ~TIM11_GATE_MASK;
	SYSCTRLx->PORTCTRL0  |=  SYSCTRL_TIM11_GATE;
}

/**
  * @brief  Config LPTIM GATE singnal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  SYSCTRL_IPTIM_GATE: LPTIM GATE signal parameter
  * @retval None 
  */
void SYSCTRL_IPTIM_GateConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_IPTIM_GATE) 
{ 
	/* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
  assert_param(IS_IPTIM_GATE_SEL(SYSCTRL_IPTIM_GATE)); 
	
  /* Configure IPTIM GATE selection PIN */ 
	SYSCTRLx->PORTCTRL0  &=  ~IPTIM_GATE_MASK;
	SYSCTRLx->PORTCTRL0  |=  SYSCTRL_IPTIM_GATE;
}

/**
  * @brief  Config PCA Capture mux config
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  SYSCTRL_CAP_CHANNEL: PCA Capture channel
  * @param  SYSCTRL_CAP_SINGNAL: PCA Capture singnal
  * @retval None 
  */
void SYSCTRL_PCACapMuxConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_CAP_CHANNEL ,uint32_t SYSCTRL_CAP_SINGNAL)
{
  /* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	assert_param(IS_PCA_CHANNEL_SET(SYSCTRL_CAP_CHANNEL)); 
	assert_param(IS_CAP_CHANNEL_SEL(SYSCTRL_CAP_SINGNAL)); 
	
	/* set PCA CAPMUX */
	SYSCTRLx->PCA_CAPMUX &= ~(uint32_t)(PCA_CH_MASK<<(SYSCTRL_CAP_CHANNEL*2));
	SYSCTRLx->PCA_CAPMUX |= (SYSCTRL_CAP_SINGNAL<<(SYSCTRL_CAP_CHANNEL*2));
}

/**
  * @brief  Config tim1 input signal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  SYSCTRL_INPUT_CHANNEL: SYSCTRL INPUT CHANNEL PARAMETER
  * @param  SYSCTRL_INPUT_SINGNAL: SYSCTRL INPUT SINGNAL PARAMETER
  * @retval None 
  */
void SYSCTRL_TIM1_InputSignalConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_INPUT_CHANNEL ,uint32_t SYSCTRL_INPUT_SINGNAL)
{
  /* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	assert_param(IS_TIM_CHANNEL_SET(SYSCTRL_INPUT_CHANNEL)); 
	assert_param(IS_TIM_INPUTSIGNAL_SEL(SYSCTRL_INPUT_SINGNAL)); 
	
	/* Set TIM1 CHINMUX */
	SYSCTRLx->TIM1_CHINMUX &= ~(uint32_t)(TIM_CH_MASK<<(SYSCTRL_INPUT_CHANNEL*4));
	SYSCTRLx->TIM1_CHINMUX |= (SYSCTRL_INPUT_SINGNAL<<(SYSCTRL_INPUT_CHANNEL*4));
}

/**
  * @brief  Config tim1 ETR signal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  SYSCTRL_INPUT_SINGNAL: SYSCTRL INPUT SINGNAL PARAMETER
  * @retval None 
  */
void SYSCTRL_TIM1_ETRSignalConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_INPUT_SINGNAL)
{
  /* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	assert_param(IS_TIMETR_ETR_SET(SYSCTRL_INPUT_SINGNAL)); 

	
	/* Set TIM1 CHINMUX */
	SYSCTRLx->TIM1_CHINMUX &= ~TIM_ETR_MASK;
	
	SYSCTRLx->TIM1_CHINMUX |= SYSCTRL_INPUT_SINGNAL;
}

/**
  * @brief  Config tim1 Break Stm
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @retval None 
  */
void SYSCTRL_TIM1_SetBreakSTM(SYSCON_TypeDef *SYSCTRLx)
{
	 /*Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	/* Set TIM1 CHINMUX */
	SYSCTRLx->TIM1_CHINMUX &= TIM1_BREAK_ZERO;
	SYSCTRLx->TIM1_CHINMUX |= TIM1_BREAK_STM;
}

/**
  * @brief  Config Break Zero
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @retval None 
  */
void SYSCTRL_TIM1_SetBreakZERO(SYSCON_TypeDef *SYSCTRLx)
{
	 /*Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	/* Set TIM1 CHINMUX */
	SYSCTRLx->TIM1_CHINMUX &= TIM1_BREAK_ZERO;
}

/**
  * @brief  Config tim2 input signal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  SYSCTRL_INPUT_CHANNEL: SYSCTRL INPUT CHANNEL PARAMETER
  * @param  SYSCTRL_INPUT_SINGNAL: SYSCTRL INPUT SINGNAL PARAMETER
  * @retval None 
  */
void SYSCTRL_TIM2_InputSignalConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_INPUT_CHANNEL ,uint32_t SYSCTRL_INPUT_SINGNAL)
{
  /* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	assert_param(IS_TIM_CHANNEL_SET(SYSCTRL_INPUT_CHANNEL)); 
	assert_param(IS_TIM_INPUTSIGNAL_SEL(SYSCTRL_INPUT_SINGNAL)); 
	
	/* Set TIM1 CHINMUX */
	SYSCTRLx->TIM2_CHINMUX &= ~(uint32_t)(TIM_CH_MASK<<(SYSCTRL_INPUT_CHANNEL*4));
	SYSCTRLx->TIM2_CHINMUX |= (SYSCTRL_INPUT_SINGNAL<<(SYSCTRL_INPUT_CHANNEL*4));
}

/**
  * @brief  Config tim2 ETR signal
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  SYSCTRL_INPUT_SINGNAL: SYSCTRL INPUT SINGNAL PARAMETER
  * @retval None 
  */
void SYSCTRL_TIM2_ETRSignalConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_INPUT_SINGNAL)
{
  /* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	assert_param(IS_TIMETR_ETR_SET(SYSCTRL_INPUT_SINGNAL)); 

	/* Set TIM1 CHINMUX */
	SYSCTRLx->TIM2_CHINMUX &= ~TIM_ETR_MASK;
	SYSCTRLx->TIM2_CHINMUX |= SYSCTRL_INPUT_SINGNAL;
}

/**
  * @brief  Config Lpuart clock 
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  SYSCTRL_LPUART_CLK: Config lpuart clock
  * @retval None 
  */
void SYSCTRL_LPUART_CLKConfig(SYSCON_TypeDef *SYSCTRLx,uint32_t SYSCTRL_LPUART_CLK)
{
	uint32_t tmpreg=0;
  /* Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
	assert_param(IS_LPUART_CLK_SEL(SYSCTRL_LPUART_CLK)); 
	
	/*Close lock */
  SYSCTRLx->SYSCON_UNLOCK = SYSCTRL_UNLOCKKEY;

	tmpreg = (((SYSCTRLx->LPUARTCON)&SYSCTRL_LPUARTKEY_MASK)|SYSCTRL_LPUARTKEY);
	tmpreg  = ((tmpreg&(~LPUARTCLK_MASK))|SYSCTRL_LPUART_CLK);
	/* Set TIM1 CHINMUX */
	SYSCTRLx->LPUARTCON = tmpreg;

	/*open lock */
  SYSCTRLx->SYSCON_UNLOCK = SYSCTRL_LOCKKEY;
}

/**
  * @brief  Enables SYSCTRL LPUART Clock
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral. 
  * @param  NewState: new state of the LPUARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_LPUART_CLKCmd(SYSCON_TypeDef *SYSCTRLx,FunctionalState NewState)
{
	uint32_t tmpreg=0;
  /*Check the parameters */
	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
		/*Close lock */
  SYSCTRLx->SYSCON_UNLOCK = SYSCTRL_UNLOCKKEY;
	
	tmpreg = (((SYSCTRLx->LPUARTCON)&SYSCTRL_LPUARTKEY_MASK)|SYSCTRL_LPUARTKEY);
 
	/* Set TIM1 CHINMUX */
	if(NewState != DISABLE)
	{
		tmpreg |= (uint32_t)LPUARTCLK_EN;
		SYSCTRLx->LPUARTCON = tmpreg;
	}
	else
	{
		tmpreg &= ~(uint32_t)LPUARTCLK_EN;
		SYSCTRLx->LPUARTCON = tmpreg;
	}
	/*open lock */
  SYSCTRLx->SYSCON_UNLOCK = SYSCTRL_LOCKKEY;
}


/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */
/************************ (C) COPYRIGHT XMC *****END OF FILE****/   

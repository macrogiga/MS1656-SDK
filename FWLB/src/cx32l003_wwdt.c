/**
  ******************************************************************************
  * @file    cx32l003_wwdg.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Window watchdog (WWDG) peripheral:           
  *           + Prescaler, Refresh window and Counter configuration
  *           + WWDG activation
  *           + Interrupts and flags management
  *             
 @verbatim    
 ===============================================================================
                           ##### WWDG features #####
 ===============================================================================
    [..]                                      
        Once enabled the WWDG generates a system reset on expiry of a programmed
        time period, unless the program refreshes the counter (downcounter) 
        before to reach 0x3F value (i.e. a reset is generated when the counter
        value rolls over from 0x40 to 0x3F). 
        An MCU reset is also generated if the counter value is refreshed
        before the counter has reached the refresh window value. This 
        implies that the counter must be refreshed in a limited window.
              
        Once enabled the WWDG cannot be disabled except by a system reset.
          
        WWDGRST flag in RCC_CSR register can be used to inform when a WWDG
        reset occurs.
             
        The WWDG counter input clock is derived from the APB clock divided 
        by a programmable prescaler.
                
        WWDG counter clock = PCLK1 / Prescaler
        WWDG timeout = (WWDG counter clock) * (counter value)
                       
        Min-max timeout value @42 MHz(PCLK1): ~97.5 us / ~49.9 ms
                             
                      ##### How to use this driver #####
 ===============================================================================
    [..]
      (#) Enable WWDG clock using RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE) function
              
      (#) Configure the WWDG prescaler using WWDG_SetPrescaler() function
                             
      (#) Configure the WWDG refresh window using WWDG_SetWindowValue() function
              
      (#) Set the WWDG counter value and start it using WWDG_Enable() function.
          When the WWDG is enabled the counter value should be configured to 
          a value greater than 0x40 to prevent generating an immediate reset.     
              
      (#) Optionally you can enable the Early wakeup interrupt which is 
          generated when the counter reach 0x40.
          Once enabled this interrupt cannot be disabled except by a system reset.
                  
      (#) Then the application program must refresh the WWDG counter at regular
          intervals during normal operation to prevent an MCU reset, using
          WWDG_SetCounter() function. This operation must occur only when
          the counter value is lower than the refresh window value, 
          programmed using WWDG_SetWindowValue().         
  
    @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 XMC</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_wwdt.h"
#include "cx32l003_rcc.h"


uint8_t wwdt_flg=0;

/**
  * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WWDG_DeInit(void)
{
	/*Enable CRC reset state */
	RCC_PeriphResetCmd(RCC,RCC_APBPeriph_WWDTRST, ENABLE);
	/*Release CRC from reset state */
	RCC_PeriphResetCmd(RCC,RCC_APBPeriph_WWDTRST, DISABLE);  
}

/**
  * @brief  Sets the WWDG Prescaler.
  * @param  WWDG_Prescaler: specifies the WWDG Prescaler.
  *   This parameter can be one of the following values:
  *     @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
  *     @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
  *     @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
  *     @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
  * @retval None
  */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
  /* Clear WDGTB[1:0] bits */
  tmpreg = WWDG->CTL & CTL_WDGTB_MASK;
  /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
  tmpreg |= (WWDG_Prescaler<<8);
  /* Store the new value */
  WWDG->CTL = tmpreg;
}

/**
  * @brief  Sets the WWDG window value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  *   This parameter value must be lower than 0x80.
  * @retval None
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
  /* Clear W[6:0] bits */

  tmpreg = WWDG->CTL& CTL_W_MASK;

  /* Set W[6:0] bits according to WindowValue value */
  tmpreg |= WindowValue & (uint32_t) BIT_MASK;

  /* Store the new value */
  WWDG->CTL = tmpreg;
}

/**
  * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
  * @note   Once enabled this interrupt cannot be disabled except by a system reset.
  * @param  NewState: new state of the WWDG peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WWDG_EnableIT(FunctionalState NewStatus)
{
	if(NewStatus != DISABLE)
		/* Enables the interrupt */
		WWDG->INTEN |= WWDG_INT_ENABLE;
	else
		/* Disable the interrupt */
		WWDG->INTEN &= ~WWDG_INT_ENABLE;
}

/**
  * @brief  Sets the WWDG counter value.
  * @param  Rldcnt: specifies the watchdog counter value.
  * @retval None
  */
void WWDG_SetRldCnt(uint8_t Rldcnt)
{
  /* set the vlaue to the RLDCNT*/
  WWDG->RLDCNT = Rldcnt & BIT_MASK;
}


/**
  * @brief  Enables WWDG counter function.                  
  * @param  NewState: new state of the WWDG peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WWDG_Cmd(FunctionalState NewStatus)
{
  /* Check the parameters */
  if(NewStatus == ENABLE)
   WWDG->CTL |= WWDG_CTL_ENBLE ;
	else
	 WWDG->CTL &= ~WWDG_CTL_ENBLE ;
}
/**
  * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
  * @param  WWDG_FLAG:specifies the WWDG FLAG to check. 
  * This parameter can be one of the following values:
  *     @arg WWDG_INT_FLAG: wwdg interrupt flag
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
  */
FlagStatus WWDG_GetFlagStatus(uint16_t WWDG_FLAG)
{
  FlagStatus bitstatus = RESET;
    
  if (((WWDG->STATUS)&WWDG_FLAG) != (uint32_t)RESET)
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
  * @brief  Clears Early Wakeup interrupt flag.
  * @param  None
  * @retval None
  */
void WWDG_ClearFlag(void)
{
	/*Clear the flag interrupt*/
  WWDG->ICLR =  WWDG_CRL_STATUS;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT XMC *****END OF FILE****/

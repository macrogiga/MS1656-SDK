/**
  ******************************************************************************
  * @file    cx32l003_debug.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides firmware functions to manage the debug peripheral.
  *
 @verbatim
    
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..] This driver provides functions for:
            
       (#)KEIL DEBUG FUNCTION
            
      
 @endverbatim      
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under MCU Liberty SW License Agreement V2, (the "License");
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
#include "cx32l003_debug.h"


/**
  * @brief  Enables debug function
  * @param  DEBUGx:Select the LPUART or the debug peripheral.
	* @param  DEBUG_InitStruct: pointer to a LPUART_InitTypeDef structure
  *         which will be configed.
  * @retval None
  */
void  DEBUG_DebugCmd(DEBUG_TypeDef *DEBUGx,DEBUG_InitTypeDef *DEBUG_InitStruct)
{
	/* Check the parameters */
  uint32_t tmpreg =0,tmp =0;
	
	/*The key value */
	uint32_t key = 0x5a690000;
	
	/*Set debug parameter*/
	tmp = ((DEBUG_InitStruct->TIMER10DEGSTOP<<0)|\
	       (DEBUG_InitStruct->TIMER11DEGSTOP<<1)|\
	       (DEBUG_InitStruct->LPTIMDEGSTOP<<2)|\
	       (DEBUG_InitStruct->PCADEGSTOP<<4)|\
	       (DEBUG_InitStruct->TIM1DESTOP<<5)|\
	       (DEBUG_InitStruct->RTCDEGSTOP<<6)|\
	       (DEBUG_InitStruct->AWKDEGSTOP<<7)|\
	       (DEBUG_InitStruct->BEEPDEGSTOP<<8)|\
	       (DEBUG_InitStruct->IWDTDEGSTOP<<9)|\
	       (DEBUG_InitStruct->WWDTDEGSTOP<<10)|\
	       (DEBUG_InitStruct->TIM2DEGSTOP<<11));
	
	/*The key value */
	tmpreg = key|tmp;
	
  /*Set the value to the APBFZ register*/
	DEBUGx->APBFZ = tmpreg;

}

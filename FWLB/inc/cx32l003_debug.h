/**
  ******************************************************************************
  * @file    cx32l003_debug.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file contains all the functions prototypes for the DEBUG firmware
  *          library. 
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32l003_DEBUG_H
#define __CX32l003_DEBUG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	 
/** @defgroup DEBUG_InitTypeDef
  * @{
  */
typedef struct
{
  uint8_t TIMER10DEGSTOP;   /*!< TIMER10 DEBUG */
  uint8_t TIMER11DEGSTOP;   /*!< TIMER11 DEBUG */
  uint8_t LPTIMDEGSTOP;     /*!< LPTIMER DEBUG */
  uint8_t PCADEGSTOP;       /*!< PCA DEBUG */
	uint8_t TIM1DESTOP;       /*!< TIM1 DEBUG */
	uint8_t RTCDEGSTOP;       /*!< RTC DEBUG */
	uint8_t AWKDEGSTOP;       /*!< RTC DEBUG */
	uint8_t BEEPDEGSTOP;      /*!< RTC BEEP DEBUG */
	uint8_t IWDTDEGSTOP;      /*!< IWDT BEEP DEBUG */
	uint8_t WWDTDEGSTOP;      /*!< WWDT BEEP DEBUG */
	uint8_t TIM2DEGSTOP;      /*!< TIM2 BEEP DEBUG */
}DEBUG_InitTypeDef;
	 

/** @defgroup LPUART_Exported_Functions
  * @{
  */
void  DEBUG_DebugCmd(DEBUG_TypeDef *DEBUGx,DEBUG_InitTypeDef *DEBUG_InitStruct);	 
	 
#ifdef __cplusplus
}
#endif

#endif /*__CX32l003_DEBUG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    cx32l003_wwdt.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the wwdt firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under XMC Liberty SW License Agreement V2, (the "License");
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
	
/* Define to prevent recursive inclusion -----------*/
#ifndef __CX32l003_WWDG_H
#define __CX32l003_WWDG_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"



/* --------------------- WWDG registers bit mask ------------------------ */
/* CFR register bit mask */
#define CTL_WDGTB_MASK    ((uint32_t)0xF00000FF)
#define CTL_W_MASK        ((uint32_t)0xFFFFFF00)
#define BIT_MASK          ((uint32_t)0x000000FF)



#define  WWDG_CTL_ENBLE                       ((uint32_t)0x10000000)               /*!< Activation bit */
#define  WWDG_CRL_STATUS                      ((uint32_t)0x00000001)               /*!< Activation bit */
#define  WWDG_INT_FLAG                        ((uint32_t)0x00000001)               /*!< Activation bit */
#define  WWDG_INT_ENABLE                      ((uint32_t)0x00000001)               /*!< Activation bit */
  
	
/** @defgroup WWDG_Prescaler 
  * @{
  */

#define IS_WWDG_PRESCALER(PRESCALER)   (((PRESCALER) >= 0) && ((PRESCALER)<= 0xfffff))
                                    
																			
																			
/* Exported functions -----------------------------*/ 																			
void WWDG_DeInit(void);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_EnableIT(FunctionalState NewStatus);
void WWDG_SetRldCnt(uint8_t Rldcnt);
void WWDG_Cmd(FunctionalState NewStatus);
FlagStatus WWDG_GetFlagStatus(uint16_t WWDG_FLAG);
void WWDG_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif /*__CX32l003_WWDG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT XMC *****END OF FILE****/

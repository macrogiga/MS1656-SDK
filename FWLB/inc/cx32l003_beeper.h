/**
  ******************************************************************************
  * @file    cx32l003_beeper.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file contains all the functions prototypes for the BEEPER 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under XMC Liberty SW License Agreement V2, (the "License");
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
#ifndef __CX32l003_BEEPER_H
#define __CX32l003_BEEPER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	 
	 /* Exported types ------------------------------------------------------------*/
#define IS_BEEPER_ALL_PERIPH(PERIPH) ((PERIPH) == BEEPER)

/**
  * @}BEEPER MASK
  */
#define BEEPERDIV_MASK     (uint32_t)0x00000fff
#define BEEPERSELECT_MASK  (uint32_t)(0x03<<16)
#define BEEPERCLOCK_MASK   (uint32_t)(0x03<<20)
#define BEEPER_ENABLE      (uint32_t)(0x01<<18)
#define IS_BEEPER_PRESCALER(PRESCALER)           ((PRESCALER<=0xfff)&&(PRESCALER>=0))
	 
	 
	 
/**
  * @}BEEPER_CLOCKSEL DIV
  */	 
#define BEEPER_CLOCKSEL_1KHZ         (uint32_t)0x00000000
#define BEEPER_CLOCKSEL_2KHZ         (uint32_t)0x00010000
#define BEEPER_CLOCKSEL_4KHZ         (uint32_t)0x00020000
#define BEEPER_CLOCKSEL_4KHZBACK     (uint32_t)0x00030000
#define  IS_BEEPER_CLOCKSEL(CLK)       			((CLK==BEEPER_CLOCKSEL_1KHZ) ||\
                                             (CLK==BEEPER_CLOCKSEL_2KHZ) ||\
                                             (CLK==BEEPER_CLOCKSEL_4KHZ) ||\
																						 (CLK==BEEPER_CLOCKSEL_4KHZBACK))
/**
  * @}BEEPER CLK SELECTION
  */	 
#define BEEPER_CLKSEL_STOP         (uint32_t)0x00000000	 
#define BEEPER_CLKSEL_LICR         (uint32_t)0x00100000	 
#define BEEPER_CLKSEL_EXT          (uint32_t)0x00200000	 
#define BEEPER_CLKSEL_PCLK         (uint32_t)0x00300000	
#define  IS_BEEPER_SELECLOCK(CLK)       			((CLK==BEEPER_CLKSEL_STOP) ||\
                                               (CLK==BEEPER_CLKSEL_LICR) ||\
                                               (CLK==BEEPER_CLKSEL_EXT)  ||\
																							 (CLK==BEEPER_CLKSEL_PCLK))
																							 
																							 

/* Exported functions --------------------------------------------------------*/
void BEEPER_SetPrescaler(BEEPER_TypeDef *BEEPERx,uint32_t BeeperPrescaler);
void BEEPER_SelectPrescaler(BEEPER_TypeDef *BEEPERx,uint32_t PreClk);
void BEEPER_Cmd(BEEPER_TypeDef *BEEPERx,FunctionalState NewState);
void BEEPER_SetClock(BEEPER_TypeDef *BEEPERx,uint32_t CLK);

#ifdef __cplusplus
}
#endif

#endif /*__CX32l003_BEEPER_H*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT XMC *****END OF FILE****/

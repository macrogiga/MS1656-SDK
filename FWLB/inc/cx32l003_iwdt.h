/**
  ******************************************************************************
  * @file    cx32l003_iwdg.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32l003_IWDG_H
#define __CX32l003_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"

/** @defgroup IWDG_WriteAccess
  * @{
  */
#define IWDG_WriteAccess_Enable     0x55AA6698
#define IWDG_WriteAccess_Disable    0x55AA6699
#define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable)||\
                                      ((ACCESS) == IWDG_WriteAccess_Disable))


/* KR register bit mask */
#define COMMAND_IWDT_RELOAD     ((uint32_t)0x000000AA)
#define COMMAND_IWDT_ENABLE     ((uint32_t)0x00000055)
#define COMMAND_WDTINTCLR_ENBLE ((uint32_t)0x00000001)
#define COMMAND_WDTINTSHIELD_ENBLE ((uint32_t)0x00000002)
#define COMMAND_WDT_RESET ((uint32_t)0x00000000)
#define COMMAND_WDT_INT ((uint32_t)0x00000001)
#define IWDG_INT_FLAG  (uint32_t)0x00000001	
#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0x000FFFFF)


/* Exported functions --------------------------------------------------------*/
/* Prescaler and Counter configuration functions ******************************/
void IWDG_WriteAccessCmd(uint32_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint32_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_SetWdtMode(uint32_t Mode);
uint32_t IWDG_GetReload(void);
void IWDG_WdtITShieldCmd(FunctionalState NewStatus);
void IWDG_RELOAD(void);

/* IWDG activation function ***************************************************/
void IWDG_Cmd(void);

/* Flag management function ***************************************************/
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

/* WDG Inti Clear function ***************************************************/
void IWDG_WdtITClear(void);

#ifdef __cplusplus
}
#endif

#endif /* __CX32l003_IWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT XMC *****END OF FILE****/

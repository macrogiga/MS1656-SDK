/**
  ******************************************************************************
  * @file    cx32l003_lvd.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file contains all the functions prototypes for the LVD firmware
  *          library. 
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32l003_LVD_H
#define __CX32l003_LVD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	 
	 
/* Exported types ------------------------------------------------------------*/
#define IS_LVD_ALL_PERIPH(PERIPH) (((PERIPH) == LVD) 
	 
	 
#define LVD_LEVEL_DIV_MASK   (uint32_t)0x0000001f
	 
#define LVD_INTENABLE   (uint32_t)0x00010000
#define LVD_INTDISABLE  (uint32_t)0x00000000
#define IS_LVD_INT(NewStauts)  ((NewStauts== LVD_INTENABLE) ||\
	                              (NewStauts == LVD_INTDISABLE))
	 
#define LVD_ENABLE    (uint32_t)0x00000020
#define LVD_DISABLE   (uint32_t)0x00000000
#define IS_LVD_CMD(NewStauts)  ((NewStauts== LVD_ENABLE) ||\
	                              (NewStauts == LVD_DISABLE))
	 

#define LVD_ACT_MASK    (uint32_t)0x00000040 
#define LVD_ACT_RESET   (uint32_t)0x00000040
#define LVD_ACT_TI      (uint32_t)0x00000000
#define IS_LVD_ACT(ACT)  ((ACT== LVD_ACT_RESET)||\
                          (ACT == LVD_ACT_TI))
	 

#define LVD_FLT_ENABLE    (uint32_t)0x0000000080
#define LVD_FLT_DISABLE   (uint32_t)0x00000000
#define IS_LVD_FLT(NewStauts)  ((NewStauts== LVD_FLT_ENABLE) ||\
	                              (NewStauts == LVD_FLT_DISABLE))
	 
#define LVD_FALLINT_ENABLE    (uint32_t)0x00001000
#define LVD_FALLINT_DISABLE   (uint32_t)0x00000000
#define IS_LVD_FALLINT(NewStauts)  ((NewStauts== LVD_FALLINT_ENABLE) ||\
                                    (NewStauts == LVD_FALLINT_DISABLE))

#define LVD_RISEINT_ENABLE    (uint32_t)0x00002000
#define LVD_RISEINT_DISABLE   (uint32_t)0x00000000
#define IS_LVD_RISEINT(NewStauts)  ((NewStauts== LVD_RISEINT_ENABLE) ||\
                                    (NewStauts == LVD_RISEINT_DISABLE))
																												
#define LVD_HIGHINT_ENABLE    (uint32_t)0x00004000
#define LVD_HIGHINT_DISABLE   (uint32_t)0x00000000
#define IS_LVD_HIGHINT(NewStauts)  ((NewStauts== LVD_HIGHINT_ENABLE) ||\
                                    (NewStauts == LVD_HIGHINT_DISABLE))
																												
																												
#define LVD_TI_ENABLE    (uint32_t)0x00008000
#define LVD_TI_DISABLE   (uint32_t)0x00000000

	 
#define FLTCLK_SEL_MASK        ((uint32_t)0x00000300)
#define IS_FLTCLK_SEL(FLTCLK)  ((FLTCLK>= 0x0000)&&(FLTCLK <= 0x0300))


#define FLT_NUM_MASK      ((uint32_t)0xffff0000)
#define IS_FLT_NUM(NUM)  ((NUM>= 0x00000000)&&(NUM <= 0xffff0000))
#define LVD_IRFLAG   ((uint32_t)0x00000001)


/*define function block*****/
void LVD_DIV_SEL(LVD_TypeDef *LVDx,uint32_t  LEVELDIV);
void LVD_Cmd(LVD_TypeDef *LVDx,FunctionalState NewState);
void LVD_ActResetCmd(LVD_TypeDef *LVDx,FunctionalState NewState);
void LVD_ActIntCmd(LVD_TypeDef *LVDx,FunctionalState NewState);
void LVD_FLTEnCmd(LVD_TypeDef *LVDx,FunctionalState NewState);
void LVD_SetDebounceTime(LVD_TypeDef *LVDx,uint32_t DEBOUNCETIME);
void LVD_FallITCmd(LVD_TypeDef *LVDx,FunctionalState NewState);
void LVD_RiseITCmd(LVD_TypeDef *LVDx,FunctionalState NewState);
void LVD_HighITCmd(LVD_TypeDef *LVDx,FunctionalState NewState);
void LVD_SetFltNum(LVD_TypeDef *LVDx,uint32_t FltNum);
FlagStatus LVD_GetFlagStatus(LVD_TypeDef *LVDx,uint16_t LVD_FLAG);
void LVD_ClearITFlag(LVD_TypeDef *LVDx);
void LVD_ITConfig(LVD_TypeDef *LVDx,FunctionalState NewState);
void LVD_SetFltClk(LVD_TypeDef *LVDx,uint32_t FltClk);

#ifdef __cplusplus
}
#endif

#endif

/**
  * @}
  */

/**
  * @}
  */


/************************(C) COPYRIGHT XMC*****END OF FILE****/







	 
	 




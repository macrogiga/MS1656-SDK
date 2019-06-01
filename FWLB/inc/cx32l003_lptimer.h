/**
  ******************************************************************************
  * @file    cx32l003_lptimer.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file contains all the functions prototypes for the SYSCFG firmware
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
#ifndef __CX32l003_LPTIMER_H
#define __CX32l003_LPTIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	 
typedef struct
{
  uint32_t LPTIMER_Mode;     /*LPTIMER WORK MODE*/        
	uint32_t LPTIMER_CTEN;     /*LPTIMER SEL FUNCTION*/
	uint32_t LPTIMER_TCLK;     /*LPTIMER SEL CLOCK*/
	uint32_t LPTIMER_GATEEN;   /*LPTIMER gate enable*/
	uint32_t LPTIMER_GATEPOLE; /*LPTIMER gate pole*/
	uint32_t LPTIMER_TCLKCUTEN;/*LPTIMER gate*/                                  
} LPTIMER_InitTypeDef;

/* Exported types ------------------------------------------------------------*/
#define IS_LPTIMER_ALL_PERIPH(PERIPH) (((PERIPH) == LPTIMER) 

/*mask set*/
#define LPTIMER_Mode_MASK      ((uint32_t)0x01<<1)
#define LPTIMER_CT_MASK        ((uint32_t)0x01<<2)
#define LPTIMER_TCLK_MASK      ((uint32_t)0x03<<4)
#define LPTIMER_GATE_MASK      ((uint32_t)0x01<<6)
#define LPTIMER_GATEPOLE_MASK  ((uint32_t)0x01<<7)
#define LPTIMER_TCLKCUT_MASK   ((uint32_t)0x01<<9)

/*para mode set*/
#define LPTIMER_MODE1    ((uint32_t)0x00<<1)
#define LPTIMER_MODE2    ((uint32_t)0x01<<1)
#define IS_LPTIMER_MODE(MODE)  ((MODE == LPTIMER_MODE1)||\
                                (MODE==LPTIMER_MODE2))

/*para CT set*/
#define LPTIMER_COUNT    ((uint32_t)0x01<<2)
#define LPTIMER_TIMER    ((uint32_t)0x00<<2)
#define IS_LPTIMER_CT(CT)  ((CT == LPTIMER_COUNT)||\
                            (CT==LPTIMER_TIMER))

/*para TCLK set*/
#define LPTIMER_TCLK_PCLK     ((uint32_t)0x00<<4)
#define LPTIMER_TCLK_LXT      ((uint32_t)0x02<<4)
#define LPTIMER_TCLK_LIRC     ((uint32_t)0x03<<4)
#define IS_LPTIMER_TCLK(TCLK)  ((TCLK == LPTIMER_TCLK_PCLK)||\
                                (TCLK==LPTIMER_TCLK_LXT))  ||\
                                (TCLK==LPTIMER_TCLK_LIRC))
																																				
/*para GATE set*/
#define LPTIMER_GATE    ((uint32_t)0x01<<6)
#define LPTIMER_NGATE   ((uint32_t)0x00<<6)
#define IS_LPTIMER_GATE(GATE)  ((GATE == LPTIMER_GATE)||\
                                (GATE==LPTIMER_NGATE))

/*para GATE LEVEL set*/
#define LPTIMER_GATE_HIGH    ((uint32_t)0x00<<7)
#define LPTIMER_GATE_LOW     ((uint32_t)0x01<<7)
#define IS_LPTIMER_GATEPOLE(GATE)  ((GATE == LPTIMER_GATE_HIGH)||\
                                    (GATE==LPTIMER_GATE_LOW))

/*para TICK CUT set*/
#define LPTIMER_TICK_CUTENABLE    ((uint32_t)0x01<<9)
#define LPTIMER_TICK_CUTDISABLE   ((uint32_t)0x00<<9)
#define IS_LPTIMER_CUT(CUT)  ((CUT == LPTIMER_TICK_CUTENABLE)||\
                              (CUT==LPTIMER_TICK_CUTDISABLE))

/*para LPTIMER RUN set*/
#define LPTIMER_RUN_ENABLE    ((uint32_t)0x01)
#define LPTIMER_RUN_DISABLE   ((uint32_t)0x00)

#define LPTIMER_TOG_ENABLE     ((uint32_t)0x01<<3)
#define LPTIMER_TOG_DISABLE     ((uint32_t)0x00<<3)


#define LPTIMER_IT_ENABLE     ((uint32_t)0x01<<8)
#define LPTIMER_IT_DISABLE    ((uint32_t)0x00<<8)

#define LPTIMER_WT_FLAG      ((uint32_t)0x01<<16)

#define LPTIMER_IT_FLAG      (uint32_t)0x01 
#define IS_LPTIMER_IT(FLAG)   (FLAG == LPTIMER_IT_FLAG)

#define IS_LPTIMER_LOAD(VALUE)   ((VALUE>= 0x00)||\
                                  (VALUE <= 2^15))
#define IS_LPTIMER_BGLOAD(VALUE)   ((VALUE>= 0x00)||\
                                    (VALUE <= 2^15))


/*define function*/
uint32_t LPTIMER_ReadCnt(void);
void  LPTIMER_Init(LPTIMER_TypeDef* LPTIMERx, LPTIMER_InitTypeDef * LPTIMER_InitStruct);
void LPTIMER_Cmd(LPTIMER_TypeDef* LPTIMERx,FunctionalState NewState);
void LPTIMER_TogCmd(LPTIMER_TypeDef* LPTIMERx,FunctionalState NewState);
void LPTIMER_ITConfig(LPTIMER_TypeDef* LPTIMERx,FunctionalState NewState);
FlagStatus LPTIMER_GetWTFlagStatus(LPTIMER_TypeDef* LPTIMERx);
void LPTIMER_BGloadConfig(LPTIMER_TypeDef* LPTIMERx, uint32_t Value);
void LPTIMER_LoadConfig(LPTIMER_TypeDef* LPTIMERx, uint32_t Value);
ITStatus LPTIMER_GetITStatus(LPTIMER_TypeDef* LPTIMERx, uint32_t IntFlag);
void LPTIMER_ClearITFlag(LPTIMER_TypeDef* LPTIMERx ,uint32_t IntFlag);

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

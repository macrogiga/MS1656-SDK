/**
  ******************************************************************************
  * @file    cx32l003_tim.h
  * @author  XMC Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file contains all the functions prototypes for the TIM firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, XMC SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32l003_TIM_H
#define __CX32l003_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"

/** 
  * @brief  TIM Time Base Init structure definition
  * @note   This structure is used with TIM10/11 
  */
typedef struct
{
	uint32_t TIM_GATE_Polarity;         /*!<Port polarity control */
	
  uint32_t TIM_GATE;                  /*!<Gate control */

  uint32_t TIM_CounterMode;           /*!<TIM working mode:timering/counting*/

  uint32_t TIM_TMRMS;                 /*!<TIM mode select:free-running/periodic*/ 

  uint32_t TIM_TMRSZ;                 /*!<Counting mode:16bits/32bits*/ 
	
  uint32_t TIM_TMROS;                 /*!<Counting mode:wrapping/one_shot */ 
	
  uint32_t TIM_ClockDivision;         /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */
} TIM_TimeBaseInitTypeDef;       

/*Control register Mask*/
#define TMRxCON_MASK  (uint32_t)0x00000280

/** @defgroup TIM_Exported_constants 
  * @{
  */
#define IS_BASETIM_ALL_PERIPH(PERIPH) (((PERIPH) == TMER10)||\
                                       ((PERIPH) == TMER11))
                                                                                                                                                                                                                                                            
/** @defgroup TIM_Clock_Division_CKD 
  * @{
  */
#define TIM_Prescale_DIV0                       ((uint32_t)0x00000000)
#define TIM_Prescale_DIV2                       ((uint32_t)0x00000001)
#define TIM_Prescale_DIV4                       ((uint32_t)0x00000002)
#define TIM_Prescale_DIV8                       ((uint32_t)0x00000003)
#define TIM_Prescale_DIV16                      ((uint32_t)0x00000004)
#define TIM_Prescale_DIV32                      ((uint32_t)0x00000005)
#define TIM_Prescale_DIV64                      ((uint32_t)0x00000006)
#define TIM_Prescale_DIV128                     ((uint32_t)0x00000007)

#define IS_TIM_PRESCALE_DIV(DIV) (((DIV) == TIM_Prescale_DIV0)  ||\
																	((DIV) == TIM_Prescale_DIV2)  ||\
																	((DIV) == TIM_Prescale_DIV4)  ||\
																	((DIV) == TIM_Prescale_DIV8)  ||\
																	((DIV) == TIM_Prescale_DIV16) ||\
																	((DIV) == TIM_Prescale_DIV32) ||\
																	((DIV) == TIM_Prescale_DIV64) ||\
																  ((DIV) == TIM_Prescale_DIV128))														

/** @defgroup TIM_Counter_Mode 
  * @{
  */
/*set free_runing/periodic */
#define TIM_Counter_TMRMS_FREERUN                ((uint32_t)0x00000000) 
#define TIM_Counter_TMRMS_PERIODIC               ((uint32_t)0x00000040) 

/*set TIM interrupt enable */
#define TIM_Counter_TMRIE_DISABLE                ((uint32_t)0x00000000)  
#define TIM_Counter_TMRIE_ENABLE                 ((uint32_t)0x00000020)

/*set 16bits/32bits's counting */
#define TIM_Counter_TMRSZ_16BIT                  ((uint32_t)0x00000000) 
#define TIM_Counter_TMRSZ_32BIT                  ((uint32_t)0x00000010) 

/*set wrapping/one_shot*/
#define TIM_Counter_TMROS_WRAPPING               ((uint32_t)0x00000000) 
#define TIM_Counter_TMR0S_ONESHOT                ((uint32_t)0x00000008)

#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_Counter_TMRMS_FREERUN)  ||\
                                   ((MODE) == TIM_Counter_TMRMS_PERIODIC) ||\
                                   ((MODE) == TIM_Counter_TMRIE_DISABLE)  ||\
                                   ((MODE) == TIM_Counter_TMRIE_ENABLE)   ||\
                                   ((MODE) == TIM_Counter_TMRSZ_16BIT)    ||\
																	 ((MODE) == TIM_Counter_TMRSZ_32BIT)    ||\
																	 ((MODE) == TIM_Counter_TMROS_WRAPPING) ||\
																	 ((MODE) == TIM_Counter_TMR0S_ONESHOT))
																	 
/** @defgroup TIM_CT_MODE
  * @{
  */
#define TIM_CT_TIMER          ((uint32_t)0x00000000)
#define TIM_CT_COUNTER        ((uint32_t)0x00000100)
#define IS_TIM_CT_MODE(MODE) (((MODE) == TIM_CT_TIMER) ||\
                              ((MODE) == TIM_CT_COUNTER))

/** @defgroup TIM_TOG_Output
  * @{
  */
/*TOG and TOGN Output the same value "0"*/
#define TIM_TOG_EN               ((uint32_t)0x000000000) 
/*TOG and TOGN Output the contrary value*/
#define TIM_TOG_NE               ((uint32_t)0x000000200) 
#define IS_TIM_TOG_EN(TOGEN)     (((TOGEN) == TIM_TOG_EN) ||\
                                  ((TOGEN) == TIM_TOG_NE))

/** @defgroup TIM_Gate_Control
  * @{
  */
#define TIM_GATE_DISABLE        ((uint32_t)0x000000000) 
#define TIM_GATE_ENABLE         ((uint32_t)0x000000400)  
#define IS_GATE_STATE(STATE) (((STATE) == TIM_GATE_DISABLE) ||\
                              ((STATE) == TIM_GATE_ENABLE))
/**
  * @}TIM_TR_ENABLE
  */
/*TR close*/
#define TIM_TR_DISABLE        ((uint32_t)0x000000000)  
/*TR run*/
#define TIM_TR_ENABLE         ((uint32_t)0x000000080)  
#define IS_TR_STATE(STATE)    (((STATE) == TIM_TR_DISABLE) ||\
                               ((STATE) == TIM_TR_ENABLE))	
																																										
/**
  * @}TIM_IT_Enable
  */
#define TIM_IT_DISABLE        ((uint32_t)0x000000000)  
#define TIM_IT_ENABLE         ((uint32_t)0x000000020)  
#define IS_IT_STATE(STATE)    (((STATE) == TIM_TR_DISABLE) ||\
                               ((STATE) == TIM_TR_ENABLE))	
																							
/**
  * @}TIM_IT_FLAG
  */
#define TIM_IT_FLAG          ((uint32_t)0x000000001)  


/** @defgroup TIM_GATE_Polarity 
  * @{
  */
/*Gate active high*/
#define TIM_GATE_Polarity_High        ((uint32_t)0x000000000)
/*Gate active low*/
#define TIM_GATE_Polarity_Low         ((uint32_t)0x000000800)  
#define TIM_GATE_POLARITY_STATE(STATE) (((STATE) == TIM_GATE_Polarity_High) ||\
                                        ((STATE) == TIM_GATE_Polarity_Low))

/** @defgroup TIM_Exported_Functions
  * @{
  */
void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_StructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx,  FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint32_t TIM_EventSource);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint32_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint32_t TIM_CounterMode);
void TIM_SelectGatePolarity(TIM_TypeDef* TIMx, uint32_t TIM_GatePolarity);
void TIM_SetTimerLoadRegister(TIM_TypeDef* TIMx, uint32_t TIM_Value);
void TIM_SetCountRegister(TIM_TypeDef* TIMx, uint32_t TIM_Value);
uint32_t TIM_GetCountRegister(TIM_TypeDef* TIMx);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint32_t TIM_DIV);
uint32_t TIM_GetTimerLoadRegister(TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
ITStatus TIM_GetITSourceFlagStatus(TIM_TypeDef* TIMx, uint32_t TIM_ITFLAG);
ITStatus TIM_GetITShieldFlagStatus(TIM_TypeDef* TIMx, uint32_t TIM_ITFLAG);
void TIM_ClearITFlag(TIM_TypeDef* TIMx, uint32_t TIM_ITFLAG);
void TIM_TogCmd(TIM_TypeDef* TIMx, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /*__CX32l003_TIM_H */

/**
  * @}
  */

/**
  * @}
  */
/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/

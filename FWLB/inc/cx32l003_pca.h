/**
  ******************************************************************************
  * @file    cx32l003_pca.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the pca firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32LOO3_PCA_H
#define __CX32LOO3_PCA_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	 
	 
	 
/** @addtogroup
  * @{
  */
#define   pca_counterclk_mask  (uint32_t)0x0000000E	
#define   pca_ccf0_mask        (uint32_t)0x000000fe
#define   pca_ccf1_mask        (uint32_t)0x000000fd
#define   pca_ccf2_mask        (uint32_t)0x000000fb
#define   pca_ccf3_mask        (uint32_t)0x000000f7
#define   pca_ccf4_mask        (uint32_t)0x000000ef

#define  PCA_MAT_ENABLE    (uint32_t)0x00000008
#define  PCA_MAT_DISABLE   (uint32_t)0x00000000

#define  PCA_TOG_ENABLE    (uint32_t)0x00000004
#define  PCA_TOG_DISABLE   (uint32_t)0x00000000

#define  PCA_CCIE_ENABLE   (uint32_t)0x00000001
#define  PCA_CCIE_DISABLE  (uint32_t)0x00000000

#define PCA_OUTPUT_ENABLE   (uint32_t)0x00000001
#define PCA_OUTPUT_DISABLE  (uint32_t)0x00000000

#define PCA_PWM_ENABLE   (uint32_t)0x00000002
#define PCA_PWM_DISABLE  (uint32_t)0x00000000

#define PCA_PWMTOGGLE_ENABLE   (uint32_t)0x00000100
#define PCA_PWMTOGGLE_DISABLE  (uint32_t)0x00000000


/** @defgroup ADC_Exported_Constants
  * @{
  */ 
#define IS_PCA_ALL_PERIPH(PERIPH) (((PERIPH) == PCA))

	 	
/**
  * @} TMER RIGSTER
  */
typedef enum {
	PCA_Channel0  =  0,  /*pca channel0*/
	PCA_Channel1  ,      /*pca channel1*/    
	PCA_Channel2  ,      /*pca channel2*/    
	PCA_Channel3 ,       /*pca channel3*/     
	PCA_Channel4 ,       /*pca channel4*/    
}PCA_Channel;

#define IS_PCA_CHANNEL(CHANNEL) (((CHANNEL) == PCA_Channel0) ||\
                                 ((CHANNEL) == PCA_Channel1) ||\
                                 ((CHANNEL) == PCA_Channel2) ||\
                                 ((CHANNEL) == PCA_Channel3) ||\
                                 ((CHANNEL) == PCA_Channel4))
																			

/**
  * @} TMER RIGSTER
  */
typedef enum {
	PCA_Counter_Function  =  0, /*pca counter Function*/
	PCA_Capture_Function  ,  /*pca Capture Function*/   
	PCA_Compare_Function  ,  /*pca Compare Function*/   
	PCA_SoftWare_Function ,  /*pca SoftWare Function*/     
	PCA_HighSpeedOutput_Function ,   /*pca HighSpeedOutput Function*/
  PCA_Pca4WDT_Function ,   /*pca Pca4WDT Function*/	
	PCA_PWM_Function ,   /*pca PWM Function*/
}PCA_Function;

#define IS_PCA_FUNCTION(FUNCTION) (((FUNCTION) == PCA_Counter_Function) || \
                                   ((FUNCTION) == PCA_Capture_Function) ||\
                                   ((FUNCTION) == PCA_Compare_Function) ||\
                                   ((FUNCTION) == PCA_SoftWare_Function) ||\
                                   ((FUNCTION) == PCA_HighSpeedOutput_Function)||\
																	 ((FUNCTION) == PCA_Pca4WDT_Function)||\
																	 ((FUNCTION) == PCA_PWM_Function))

	 
/**
  * @} TMER RIGSTER
  */
typedef struct
{
 
  uint16_t PCA_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

  uint16_t PCA_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */

  uint8_t PCA_ThresholdCounter;  /*!< Specifies the Threshold counter value*/
                                    
                                      
} PCA_CountTimerInitTypeDef; 

/**
  * @} TMER RIGSTER
  */
typedef struct
{

  uint16_t PCA_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

  uint16_t PCA_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint16_t PCA_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

} PCA_ICInitTypeDef;



/**
  * @} TMER RIGSTER
  */
typedef struct
{
  uint16_t PCA_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint16_t PCA_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_State */

  uint16_t PCA_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint32_t PCA_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t PCA_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint16_t PCA_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16_t PCA_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16_t PCA_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
} PCA_OCInitTypeDef;


/** @defgroup PCA_Clock_Division
  * @{
  */
#define PCA_Prescale_DIV32                       ((uint32_t)0x00000000)
#define PCA_Prescale_DIV16                       ((uint32_t)0x00000002)
#define PCA_Prescale_DIV8                        ((uint32_t)0x00000004)
#define PCA_Prescale_DIV4                        ((uint32_t)0x00000006)
#define PCA_Prescale_DIV2                        ((uint32_t)0x00000008)
#define PCA_Prescale_TIM0OVERFLOW                ((uint32_t)0x0000000A)
#define PCA_Prescale_TIM1OVERFLOW                ((uint32_t)0x0000000C)
#define PCA_Prescale_ECI                         ((uint32_t)0x0000000E)


#define IS_PCA_PRESCALE_DIV(DIV) (((DIV) == PCA_Prescale_DIV32) || \
																	((DIV) == PCA_Prescale_DIV16) || \
																	((DIV) == PCA_Prescale_DIV8) ||\
																	((DIV) == PCA_Prescale_DIV4) ||\
																	((DIV) == PCA_Prescale_DIV2) ||\
																	((DIV) == PCA_Prescale_TIM0OVERFLOW) ||\
																	((DIV) == PCA_Prescale_TIM1OVERFLOW) ||\
																  ((DIV) == PCA_Prescale_ECI))	
																	
#define IS_PCA_CNT_VALUE(VALUE)   ((VALUE>= 0x00000000)&&(VALUE<=0x0000ffff))


#define PCA_CR_DISABLE        ((uint32_t)0x00000000)  /*!< TR DISABLE */
#define PCA_CR_ENABLE         ((uint32_t)0x00000040)  /*!< TR ENABLE */
#define PCA_TI_DISABLE        ((uint32_t)0x00000000)  /*!< TI DISABLE */
#define PCA_TI_ENABLE         ((uint32_t)0x00000001)  /*!< TI ENABLE */




#define PCA_TI_CF_FLAG      ((uint32_t)0x00000080)  /*!< TI TI CF FLAG */
#define PCA_TI_CCF0_FLAG    ((uint32_t)0x00000001)  /*!< TI TI CCF0 FLAG */
#define PCA_TI_CCF1_FLAG    ((uint32_t)0x00000002)  /*!< TI TI CCF1 FLAG */
#define PCA_TI_CCF2_FLAG    ((uint32_t)0x00000004)  /*!< TI TI CCF2 FLAG */
#define PCA_TI_CCF3_FLAG    ((uint32_t)0x00000008)  /*!< TI TI CCF3 FLAG */
#define PCA_TI_CCF4_FLAG    ((uint32_t)0x00000010)  /*!< TI TI CCF4 FLAG */


#define  PCA_CAP_RISE_Edge     ((uint32_t)0x00000020)
#define  PCA_CAP_FALL_Edge     ((uint32_t)0x00000010)
#define  PCA_CAP_ALL_Edge      ((uint32_t)0x00000030)

#define IS_PCA_CAP_Edge(Edge) (((Edge) == PCA_CAP_RISE_Edge) ||\
															 ((Edge) == PCA_CAP_FALL_Edge) ||\
															 ((Edge) == PCA_CAP_ALL_Edge))
													
/** @addtogroup function define
  * @{
  */
void PCA_CountTimerInit(PCA_TypeDef* PCAx, PCA_CountTimerInitTypeDef* PCA_CountTimerInitInitStruct);
void PCA_CountTimercmd(PCA_TypeDef* PCAx, FunctionalState NewState);
void PCA_CountTimerITCmd(PCA_TypeDef* PCAx, FunctionalState NewState);
void PCA_ITClear(PCA_TypeDef* PCAx, uint32_t PCA_TI_FLAG);
void PCA_CaptureInit(PCA_TypeDef* PCAx, PCA_ICInitTypeDef* PCA_ICInitStruct);
void PCA_CaptureITCmd(PCA_TypeDef* PCAx,PCA_ICInitTypeDef* PCA_ICInitStruct, FunctionalState NewState);
void PCA_SetSoftCompare(PCA_TypeDef* PCAx,PCA_Channel channel,uint16_t value);
void PCA_ClearSoftCompare(PCA_TypeDef* PCAx,PCA_Channel channel,uint16_t value);
void PCA_SetHighSpeed_output(PCA_TypeDef* PCAx,PCA_Channel channel,uint16_t value,uint8_t bit);
void PCA_SetPwm_output(PCA_TypeDef* PCAx,PCA_Channel channel,uint8_t valuel,uint8_t valueh,FunctionalState NewStatus);

#ifdef __cplusplus
}
#endif

#endif /* __CX32LOO3_PCA_H */

/**
  * @}
  */

/**
  * @}
  */






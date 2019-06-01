/**
  ******************************************************************************
  * @file    cx32l003_adc.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file contains all the functions prototypes for the ADC firmware 
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
#ifndef __CX32l003_ADC_H
#define __CX32l003_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"



/** @defgroup ADC_Exported_Constants
  * @{
  */ 
#define IS_ADC_ALL_PERIPH(PERIPH) (((PERIPH) == ADC))   

/** 
  * @brief   ADC Init structure definition  
  */ 
typedef struct
{
	uint32_t ADC_ClkSel;                                                                                     
	uint32_t ADC_ChannelSel;                                                                                        
	uint32_t ADC_SamSel;                                                                                                                                                                                                                                            
}ADC_InitTypeDef;
  
/** 
  * @brief   ADC Common Init structure definition  
  */ 
typedef struct 
{
  uint32_t  ADC_CtMode;                      /*!< Configures the ADC to operate in 
                                               independent or multi mode. */
  uint32_t  ADC_Trigs0Sel;                                                 
	uint32_t  ADC_Trigs1Sel; 
	uint32_t  ADC_CircleMode; 	             /* This parameter can be a value of @ref ADC_Common_mode */                                              
 	uint32_t  ADC_SetAdcCnt;                 /*!< Select the frequency of the clock 
                                               to the ADC. The clock is common for all the ADCs This parameter can be a value of @ref ADC_Prescaler */  
}ADC_CommonInitTypeDef;
                        
/** @defgroup ADC_Common_mode 
  * @{
  */ 
#define ADC_Mode_Independent                       ((uint32_t)0x00000000) 
#define ADC_Mode_Circle                            ((uint32_t)0x00010000)   

#define IS_ADC_MODE(MODE) (((MODE) == ADC_Mode_Independent) ||\
                           ((MODE) == ADC_Mode_Circle))


/** @defgroup ADC_Common_mode 
  * @{
  */ 
#define ADC_Ct_Single                       ((uint32_t)0x00000000) 
#define ADC_Ct_Contine                      ((uint32_t)0x00000400)   
#define IS_ADC_CT(MODE)   (((MODE) == ADC_Ct_Single) ||\
                           ((MODE) == ADC_Ct_Contine))
                           
/**
  * @}CR0_MASK
  */ 
#define ADC_CLKSEL_MASK       ((uint32_t)0x00000070)
#define ADC_ChannelEL_MASK    ((uint32_t)0x00000700)
#define ADC_SamCycle_MASK     ((uint32_t)0x00000080)
#define ADC_CR0_MASK          ((uint32_t)0x000007F0)

/**
  * @}CR1_ACC
  */ 
#define ADC_ACC_EN            ((uint32_t)0x00000800)
#define ADC_ACC_DISABLE       ((uint32_t)0x00000000)
#define ADC_ACCResult_Clear   ((uint32_t)0x00008000)

/**
  * @}CR1_MASK
  */ 
#define ADC_CT_MASK           ((uint32_t)0x00000400)
#define ADC_TRIGS1_MASK       ((uint32_t)0x000003E0)
#define ADC_TRIGS0_MASK       ((uint32_t)0x0000001F)
#define ADC_CR1_MASK          ((uint32_t)0x000007FF)


/**
  * @}CR2_MASK
  */ 
#define ADC_CIRCLEMODE_MASK   ((uint32_t)0x00010000)
#define ADC_ADCCNT_MASK       ((uint32_t)0x0000FF00)
#define ADC_CR2_MASK          ((uint32_t)0x0001FF00)


/** @defgroup ADC_Prescaler 
  * @{
  */ 
#define ADC_Prescaler_Div1                         ((uint32_t)0x00000000)
#define ADC_Prescaler_Div2                         ((uint32_t)0x00000010)
#define ADC_Prescaler_Div4                         ((uint32_t)0x00000020)
#define ADC_Prescaler_Div8                         ((uint32_t)0x00000030)
#define ADC_Prescaler_Div16                        ((uint32_t)0x00000040)
#define ADC_Prescaler_Div32                        ((uint32_t)0x00000050)
#define ADC_Prescaler_Div64                        ((uint32_t)0x00000060)
#define ADC_Prescaler_Div128                       ((uint32_t)0x00000070)

#define IS_ADC_PRESCALER(PRESCALER) (((PRESCALER) == ADC_Prescaler_Div1) || \
                                     ((PRESCALER) == ADC_Prescaler_Div2) || \
                                     ((PRESCALER) == ADC_Prescaler_Div4) || \
                                     ((PRESCALER) == ADC_Prescaler_Div8) || \
																		 ((PRESCALER) == ADC_Prescaler_Div16) || \
																		 ((PRESCALER) == ADC_Prescaler_Div32) || \
																		 ((PRESCALER) == ADC_Prescaler_Div64) || \
																		 ((PRESCALER) == ADC_Prescaler_Div128))
	
	
/** @defgroup ADC_trigger1_edge_for_regular_channels_conversion 
  * @{
  */ 
#define ADC_Trigs1_DISABLE           ((uint32_t)0x00000000)
#define ADC_Trigs1_TIMER10           ((uint32_t)0x00000020)
#define ADC_Trigs1_TIMER11           ((uint32_t)0x00000040)
#define ADC_Trigs1_NC0_              ((uint32_t)0x00000060)
#define ADC_Trigs1_LPTIMER           ((uint32_t)0x00000080)
#define ADC_Trigs1_TIM1              ((uint32_t)0x000000A0)
#define ADC_Trigs1_TIM2              ((uint32_t)0x000000C0)
#define ADC_Trigs1_NC1               ((uint32_t)0x000000E0)
#define ADC_Trigs1_UART0             ((uint32_t)0x00000100)
#define ADC_Trigs1_UART1             ((uint32_t)0x00000120)
#define ADC_Trigs1_LPUART            ((uint32_t)0x00000140)
#define ADC_Trigs1_VC0               ((uint32_t)0x00000160)
#define ADC_Trigs1_NC2               ((uint32_t)0x00000180)
#define ADC_Trigs1_RTC               ((uint32_t)0x000001A0)
#define ADC_Trigs1_PCA               ((uint32_t)0x000001C0)
#define ADC_Trigs1_SPI               ((uint32_t)0x000001E0)
#define ADC_Trigs1_PA1               ((uint32_t)0x00000200)
#define ADC_Trigs1_PA2               ((uint32_t)0x00000220)
#define ADC_Trigs1_PA3               ((uint32_t)0x00000240)
#define ADC_Trigs1_PB4               ((uint32_t)0x00000260)
#define ADC_Trigs1_PB5               ((uint32_t)0x00000280)
#define ADC_Trigs1_PC3               ((uint32_t)0x000002A0)
#define ADC_Trigs1_PC4               ((uint32_t)0x000002C0)
#define ADC_Trigs1_PC5               ((uint32_t)0x000002E0)
#define ADC_Trigs1_PC6               ((uint32_t)0x00000300)
#define ADC_Trigs1_PC7               ((uint32_t)0x00000320)
#define ADC_Trigs1_PD1               ((uint32_t)0x00000340)
#define ADC_Trigs1_PD2               ((uint32_t)0x00000360)
#define ADC_Trigs1_PD3               ((uint32_t)0x00000380)
#define ADC_Trigs1_PD4               ((uint32_t)0x000003A0)
#define ADC_Trigs1_PD5               ((uint32_t)0x000003C0)
#define ADC_Trigs1_PD6               ((uint32_t)0x000003E0)

#define IS_ADC_TRIG1_EDGE(EDGE)  (((EDGE) == ADC_Trigs1_DISABLE) || \
																	((EDGE) == ADC_Trigs1_TIMER10) || \
																	((EDGE) == ADC_Trigs1_TIMER11) || \
																	((EDGE) == ADC_Trigs1_NC0_) || \
																	((EDGE) == ADC_Trigs1_LPTIMER) || \
																	((EDGE) == ADC_Trigs1_TIM1) || \
																	((EDGE) == ADC_Trigs1_TIM2) || \
																	((EDGE) == ADC_Trigs1_NC1) || \
																	((EDGE) == ADC_Trigs1_UART0) || \
																	((EDGE) == ADC_Trigs1_UART1) || \
																	((EDGE) == ADC_Trigs1_LPUART) || \
																	((EDGE) == ADC_Trigs1_VC0) || \
																	((EDGE) == ADC_Trigs1_NC2) || \
																	((EDGE) == ADC_Trigs1_RTC) || \
																	((EDGE) == ADC_Trigs1_PCA) || \
																	((EDGE) == ADC_Trigs1_SPI) || \
																	((EDGE) == ADC_Trigs1_PA1) || \
																	((EDGE) == ADC_Trigs1_PA2) || \
																	((EDGE) == ADC_Trigs1_PA3) || \
																	((EDGE) == ADC_Trigs1_PB4) || \
																	((EDGE) == ADC_Trigs1_PB5) || \
																	((EDGE) == ADC_Trigs1_PC3) || \
																	((EDGE) == ADC_Trigs1_PC4) || \
																	((EDGE) == ADC_Trigs1_PC5) || \
																	((EDGE) == ADC_Trigs1_PC6) || \
																	((EDGE) == ADC_Trigs1_PC7) || \
																	((EDGE) == ADC_Trigs1_PD1) || \
																	((EDGE) == ADC_Trigs1_PD2) || \
																	((EDGE) == ADC_Trigs1_PD3) || \
																	((EDGE) == ADC_Trigs1_PD4) || \
																	((EDGE) == ADC_Trigs1_PD5) || \
																	((EDGE) == ADC_Trigs1_PD6))
																																										 
														 
														 
														 
/** @defgroup ADC_trigger0_edge_for_regular_channels_conversion 
  * @{
  */ 
#define ADC_Trigs0_DISABLE           ((uint32_t)0x00000000)
#define ADC_Trigs0_TIMER10           ((uint32_t)0x00000001)
#define ADC_Trigs0_TIMER11           ((uint32_t)0x00000002)
#define ADC_Trigs0_NC0_              ((uint32_t)0x00000003)
#define ADC_Trigs0_LPTIMER           ((uint32_t)0x00000004)
#define ADC_Trigs0_TIM1              ((uint32_t)0x00000005)
#define ADC_Trigs0_TIM2              ((uint32_t)0x00000006)
#define ADC_Trigs0_NC1               ((uint32_t)0x00000007)
#define ADC_Trigs0_UART0             ((uint32_t)0x00000008)
#define ADC_Trigs0_UART1             ((uint32_t)0x00000009)
#define ADC_Trigs0_LPUART            ((uint32_t)0x0000000A)
#define ADC_Trigs0_VC0               ((uint32_t)0x0000000B)
#define ADC_Trigs0_NC2               ((uint32_t)0x0000000C)
#define ADC_Trigs0_RTC               ((uint32_t)0x0000000D)
#define ADC_Trigs0_PCA               ((uint32_t)0x0000000E)
#define ADC_Trigs0_SPI               ((uint32_t)0x0000000F)
#define ADC_Trigs0_PA1               ((uint32_t)0x00000010)
#define ADC_Trigs0_PA2               ((uint32_t)0x00000011)
#define ADC_Trigs0_PA3               ((uint32_t)0x00000012)
#define ADC_Trigs0_PB4               ((uint32_t)0x00000013)
#define ADC_Trigs0_PB5               ((uint32_t)0x00000014)
#define ADC_Trigs0_PC3               ((uint32_t)0x00000015)
#define ADC_Trigs0_PC4               ((uint32_t)0x00000016)
#define ADC_Trigs0_PC5               ((uint32_t)0x00000017)
#define ADC_Trigs0_PC6               ((uint32_t)0x00000018)
#define ADC_Trigs0_PC7               ((uint32_t)0x00000019)
#define ADC_Trigs0_PD1               ((uint32_t)0x0000001A)
#define ADC_Trigs0_PD2               ((uint32_t)0x0000001B)
#define ADC_Trigs0_PD3               ((uint32_t)0x0000001C)
#define ADC_Trigs0_PD4               ((uint32_t)0x0000001D)
#define ADC_Trigs0_PD5               ((uint32_t)0x0000001E)
#define ADC_Trigs0_PD6               ((uint32_t)0x0000001F)

#define IS_ADC_TRIG0_EDGE(EDGE)  (((EDGE) == ADC_Trigs0_DISABLE) || \
																	((EDGE) == ADC_Trigs0_TIMER10) || \
																	((EDGE) == ADC_Trigs0_TIMER11) || \
																	((EDGE) == ADC_Trigs0_NC0_) || \
																	((EDGE) == ADC_Trigs0_LPTIMER) || \
																	((EDGE) == ADC_Trigs0_TIM1) || \
																	((EDGE) == ADC_Trigs0_TIM2) || \
																	((EDGE) == ADC_Trigs0_NC1) || \
																	((EDGE) == ADC_Trigs0_UART0) || \
																	((EDGE) == ADC_Trigs0_UART1) || \
																	((EDGE) == ADC_Trigs0_LPUART) || \
																	((EDGE) == ADC_Trigs0_VC0) || \
																	((EDGE) == ADC_Trigs0_NC2) || \
																	((EDGE) == ADC_Trigs0_RTC) || \
																	((EDGE) == ADC_Trigs0_PCA) || \
																	((EDGE) == ADC_Trigs0_SPI) || \
																	((EDGE) == ADC_Trigs0_PA1) || \
																	((EDGE) == ADC_Trigs0_PA2) || \
																	((EDGE) == ADC_Trigs0_PA3) || \
																	((EDGE) == ADC_Trigs0_PB4) || \
																	((EDGE) == ADC_Trigs0_PB5) || \
																	((EDGE) == ADC_Trigs0_PC3) || \
																	((EDGE) == ADC_Trigs0_PC4) || \
																	((EDGE) == ADC_Trigs0_PC5) || \
																	((EDGE) == ADC_Trigs0_PC6) || \
																	((EDGE) == ADC_Trigs0_PC7) || \
																	((EDGE) == ADC_Trigs0_PD1) || \
																	((EDGE) == ADC_Trigs0_PD2) || \
																	((EDGE) == ADC_Trigs0_PD3) || \
																	((EDGE) == ADC_Trigs0_PD4) || \
																	((EDGE) == ADC_Trigs0_PD5) || \
																	((EDGE) == ADC_Trigs0_PD6))


/** @defgroup ADC_channels 
  * @{
  */ 
#define ADC_Channel0                               ((uint32_t)0x0000)
#define ADC_Channel1                               ((uint32_t)0x0100)
#define ADC_Channel2                               ((uint32_t)0x0200)
#define ADC_Channel3                               ((uint32_t)0x0300)
#define ADC_Channel4                               ((uint32_t)0x0400)
#define ADC_Channel5                               ((uint32_t)0x0500)
#define ADC_Channel6                               ((uint32_t)0x0600)
#define ADC_Channel7                               ((uint32_t)0x0700)

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel0) || \
                                 ((CHANNEL) == ADC_Channel1) || \
                                 ((CHANNEL) == ADC_Channel2) || \
                                 ((CHANNEL) == ADC_Channel3) || \
                                 ((CHANNEL) == ADC_Channel4) || \
                                 ((CHANNEL) == ADC_Channel5) || \
                                 ((CHANNEL) == ADC_Channel6) || \
                                 ((CHANNEL) == ADC_Channel7))
																 
																 
/** @defgroup ADC_channels 
  * @{
  */ 
#define ADC_Channel0_ENABLE                               ((uint32_t)0x0001)
#define ADC_Channel1_ENABLE                               ((uint32_t)0x0002)
#define ADC_Channel2_ENABLE                               ((uint32_t)0x0004)
#define ADC_Channel3_ENABLE                               ((uint32_t)0x0008)
#define ADC_Channel4_ENABLE                               ((uint32_t)0x0010)
#define ADC_Channel5_ENABLE                               ((uint32_t)0x0020)
#define ADC_Channel6_ENABLE                               ((uint32_t)0x0040)
#define ADC_Channel7_ENABLE                               ((uint32_t)0x0080)

#define IS_ADC_CHANNEL_CMD(NewStatus) (((NewStatus) == ADC_Channel0_ENABLE)|| \
                                      ((NewStatus) == ADC_Channel1_ENABLE) || \
                                      ((NewStatus) == ADC_Channel2_ENABLE) || \
                                      ((NewStatus) == ADC_Channel3_ENABLE) || \
                                      ((NewStatus) == ADC_Channel4_ENABLE) || \
                                      ((NewStatus) == ADC_Channel5_ENABLE) || \
                                      ((NewStatus) == ADC_Channel6_ENABLE) || \
                                      ((NewStatus) == ADC_Channel7_ENABLE))
                               
                               
/**
  * @}ADC_IMCSMASK
  */ 
#define ADC_IMCSCHANNEL0MASK_ENABLE    ((uint32_t)0x0001)
#define ADC_IMCSCHANNEL1MASK_ENABLE    ((uint32_t)0x0002)
#define ADC_IMCSCHANNEL2MASK_ENABLE    ((uint32_t)0x0004)
#define ADC_IMCSCHANNEL3MASK_ENABLE    ((uint32_t)0x0008)
#define ADC_IMCSCHANNEL4MASK_ENABLE    ((uint32_t)0x0010)
#define ADC_IMCSCHANNEL5MASK_ENABLE    ((uint32_t)0x0020)
#define ADC_IMCSCHANNEL6MASK_ENABLE    ((uint32_t)0x0040)
#define ADC_IMCSCHANNEL7MASK_ENABLE    ((uint32_t)0x0080)
#define ADC_LLTIMCSMASK_ENABLE           ((uint32_t)0x0100)
#define ADC_HHTIMCSMASK_ENABLE           ((uint32_t)0x0200)
#define ADC_REGIMCSMASK_ENABLE           ((uint32_t)0x0400)
#define ADC_CONTIMCSMASK_ENABLE          ((uint32_t)0x0800)

#define IS_ADC_TIMASK(MASK)      (((MASK) == ADC_IMCSCHANNEL0MASK_ENABLE)|| \
                                 ((MASK) == ADC_IMCSCHANNEL1MASK_ENABLE) || \
                                 ((MASK) == ADC_IMCSCHANNEL2MASK_ENABLE) || \
                                 ((MASK) == ADC_IMCSCHANNEL3MASK_ENABLE) || \
                                 ((MASK) == ADC_IMCSCHANNEL4MASK_ENABLE) || \
                                 ((MASK) == ADC_IMCSCHANNEL5MASK_ENABLE) || \
                                 ((MASK) == ADC_IMCSCHANNEL6MASK_ENABLE) || \
                                 ((MASK) == ADC_IMCSCHANNEL7MASK_ENABLE) || \
																 ((MASK) == ADC_LLTIMCSMASK_ENABLE) || \
																 ((MASK) == ADC_HHTIMCSMASK_ENABLE) || \
																 ((MASK) == ADC_REGIMCSMASK_ENABLE) || \
																 ((MASK) == ADC_CONTIMCSMASK_ENABLE))

/** @defgroup ADC_sampling_times 
  * @{
  */ 
#define IS_ADC_SAMPLE_TIMES(TIMES) (((TIMES) >= 0x00) || \
                                    ((TIMES) <= 0xff))
																		
#define IS_ADC_COMPARE_VALUES(VALUE) (((VALUE) >= 0x0000) || \
	                                    ((VALUE) <= 0x0fff))
                                 
                                 
/**
  * @}
  */ 
#define ADC_SAMPLE_4CYCLE        ((uint32_t)0x00000000)  
#define ADC_SAMPLE_16CYCLE       ((uint32_t)0x00000800)  
#define IS_ADC_SAMPLE_CYCLE(CYCLE)  ((CYCLE == ADC_SAMPLE_4CYCLE) ||\
                                     (CYCLE == ADC_SAMPLE_16CYCLE))

/** @defgroup ADC_interrupts_definition 
  * @{
  */
#define ADC_CR0_ADON         ((uint32_t)0x00000001) 
#define ADC_CR0_ADOFF        ((uint32_t)0x00000000)  
#define ADC_CR0_SWSTART      ((uint32_t)0x00000002)
#define ADC_CR0_STATERST     ((uint32_t)0x00008000)

#define ADC_CR1_RACCEN       ((uint32_t)0x00000800)
#define ADC_CR1_LTCMPEN      ((uint32_t)0x00001000)
#define ADC_CR1_HTCMPEN      ((uint32_t)0x00002000)
#define ADC_CR1_REGCMPEN     ((uint32_t)0x00004000)
#define ADC_CR1_RACCCLREN    ((uint32_t)0x00008000)
#define IS_ADC_CR1_CMD(NewStatus)  ((NewStatus == ADC_CR1_RACCEN)    ||\
                                     (NewStatus == ADC_CR1_LTCMPEN)  ||\
																		 (NewStatus == ADC_CR1_HTCMPEN)  ||\
																		 (NewStatus == ADC_CR1_REGCMPEN) ||\
																		 (NewStatus == ADC_CR1_RACCCLREN))
																		 

/**
  * @}ADC_IMCSMASK
  */ 
#define ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
#define ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
#define ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
#define ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
#define ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
#define ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
#define ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
#define ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
#define ADC_TILLT_FLAG         ((uint32_t)0x0100)
#define ADC_TIHHT_FLAG         ((uint32_t)0x0200)
#define ADC_TIREG_FLAG         ((uint32_t)0x0400)
#define ADC_TICONT_FLAG         ((uint32_t)0x0800)

#define IS_ADC_FLAG(FLAG)       (((FLAG) == ADC_TICHANNEL0_FLAG) || \
                                 ((FLAG) == ADC_TICHANNEL1_FLAG) || \
                                 ((FLAG) == ADC_TICHANNEL2_FLAG) || \
                                 ((FLAG) == ADC_TICHANNEL3_FLAG) || \
                                 ((FLAG) == ADC_TICHANNEL4_FLAG) || \
                                 ((FLAG) == ADC_TICHANNEL5_FLAG) || \
                                 ((FLAG) == ADC_TICHANNEL6_FLAG) || \
                                 ((FLAG) == ADC_TICHANNEL7_FLAG) || \
																 ((FLAG) == ADC_TILLT_FLAG) || \
																 ((FLAG) == ADC_TIHHT_FLAG) || \
																 ((FLAG) == ADC_TIREG_FLAG) || \
																 ((FLAG) == ADC_TICONT_FLAG))
																 
														


/* Exported functions --------------------------------------------------------*/  
/* Function used to set the ADC configuration to the default reset state *****/  
void ADC_DeInit(void);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_CommonInit(ADC_TypeDef* ADCx,ADC_CommonInitTypeDef* ADC_CommonInitStruct);
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, uint32_t ADC_CircleMode, uint32_t ADC_SampleTime);
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ContinuousConverChannelCmd(ADC_TypeDef* ADCx,uint32_t Channel_Enable,FunctionalState NewState);
void ADC_ContinuousConverRstCmd(ADC_TypeDef* ADCx,uint32_t NewState);
void ADC_DisContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint32_t ADC_GetConversionValue(ADC_TypeDef* ADCx);
uint32_t ADC_GetChannelConversionValue(ADC_TypeDef* ADCx,uint32_t Channel);
uint32_t ADC_SetCompareHtValue(ADC_TypeDef* ADCx,uint32_t HtValue);
uint32_t ADC_SetCompareLtValue(ADC_TypeDef* ADCx,uint32_t LtValue);
uint32_t ADC_CompareControl(ADC_TypeDef* ADCx,uint32_t ADC_ControlCmd,FunctionalState NewState);
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ITCmd(ADC_TypeDef* ADCx, uint32_t ADC_FLAG, FunctionalState NewState);
FlagStatus ADC_GetRISFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
FlagStatus ADC_GetMISFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_AccCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_AccResultClear(ADC_TypeDef* ADCx,FunctionalState NewState);
uint32_t ADC_GetAccResult(ADC_TypeDef* ADCx);

#ifdef __cplusplus
}
#endif

#endif /*__CX32l003_ADC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT XMC *****END OF FILE****/

/**
  ******************************************************************************
  * @file    cx32l003_awk.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the AWK firmware 
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
#ifndef __CX32LOO3_AWK_H
#define __CX32LOO3_AWK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	 
	 
/**
  * @} TMER RIGSTER
  */
typedef struct
{
  uint32_t AWK_XTLPRSC;           /*!<AWK external clock frequency division*/   
                                  
  uint32_t AWK_SeleteClkSource;   /*!< AWK clock source Selection*/

  uint32_t AWK_CounterClkDiv;     /*!< AWK count clock frequency division Selection*/
                                  
}AWK_InitTypeDef;


/** @defgroup TIM_Exported_constants 
  * @{
  */
#define IS_AWK_ALL_PERIPH(PERIPH) ((PERIPH) == AWK)
                                      



/** @defgroup AWK_CLK_SELECTION
  * @{
  */
#define AWK_CLKMASK    (uint32_t)0x00000060
#define AWK_CLKLIRC    (uint32_t)0x00000020
#define AWK_CLKXTL     (uint32_t)0x00000040
#define IS_AWK_SELCLK(CLK) (((CLK) == AWK_CLKMASK) ||\
														((CLK) == AWK_CLKLIRC) ||\
														((CLK) == AWK_CLKXTL))

/** @defgroup AWK_Enable
  * @{
  */
#define AWK_ENABLE   0x10
#define AWK_DISABLE  0x00
#define AWK_TI_CLEAR 0x01

/** @defgroup AWK_Enable
  * @{
  */
#define AWK_CR_MASK   (uint32_t)0x00000010

																	
/** @defgroup AWK_Exported_Functions
  * @{
  */
void AWK_Init(AWK_TypeDef *AWKx, AWK_InitTypeDef* AWK_InitStruct);
void AWK_Cmd(AWK_TypeDef *AWKx,FunctionalState NewState);
void AWK_SetRldval(AWK_TypeDef *AWKx,uint8_t value);
void AWK_ClearITFlag(AWK_TypeDef *AWKx); 
void AWK_SelClk(AWK_TypeDef *AWKx,uint8_t AWKClk);

#ifdef __cplusplus
}
#endif

#endif /*__CX32LOO3_AWK_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************(C)COPYRIGHT XMC*********END OF FILE***************************************/

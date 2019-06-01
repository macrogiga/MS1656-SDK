/**
  ******************************************************************************
  * @file    cx32l003_clktrim.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the clktrim firmware 
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
  * <h2><center>&copy; COPYRIGHT 2018 XMC </center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32LOO3_CLKTRIM_H
#define __CX32LOO3_CLKTRIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	
/**
  * @} TMER CLKTRMI_RCNT
  */	 
#define CLK_TMRIM_START ((uint32_t)0x00000001)
#define CLK_TMRIM_STOP  ((uint32_t)0x00000000)

#define CLK_MON_ENABLE   ((uint32_t)0x00000040)
#define CLK_MON_DISABLE  ((uint32_t)0x00000000)

#define CLK_REFCALCLK_ENABLE  ((uint32_t)0x00000100) 
#define CLK_REFCALCLK_DISABLE ((uint32_t)0x00000000)

#define CLKTRIM_IE_ENABLE   ((uint32_t)0x00000080)
#define CLKTRIM_IE_DISABLE  ((uint32_t)0x00000000)


/** @defgroup CLKTRIM_Exported_Constants
  * @{
  */ 
#define IS_CLKTRIM_ALL_PERIPH(PERIPH)  (PERIPH == CLKTRIM)
                                   
/**
  * @} TMER REFCLK
  */
#define REFCLK_RCH   ((uint32_t)0x00000000)
#define REFCLK_XTH   ((uint32_t)0x00000002)
#define REFCLK_RCL   ((uint32_t)0x00000004)
#define REFCLK_XTL   ((uint32_t)0x00000006)
#define REFCLK_EXT   ((uint32_t)0x00000008)
#define REFCLK_MASK  ((uint32_t)0x0000000e)
	 
#define IS_CLKTRMI_REFCLK_SET(CLK) (((CLK) == REFCLK_RCH)||\
																	 ((CLK) == REFCLK_XTH) ||\
																	 ((CLK) == REFCLK_RCL) ||\
																	 ((CLK) == REFCLK_XTL) ||\
																	 ((CLK) == REFCLK_EXT))
																	
/**
  * @} TMER CALCLK
  */
#define CALCLK_RCH   ((uint32_t)0x00000000)
#define CALCLK_XTH   ((uint32_t)0x00000010)
#define CALCLK_RCL   ((uint32_t)0x00000020)
#define CALCLK_XTL   ((uint32_t)0x00000030)
#define CALCLK_MASK  ((uint32_t)0x00000030)
#define IS_CLKTRMI_CALCLK_SET(CLK) (((CLK) == CALCLK_RCH)||\
																	  ((CLK) == CALCLK_XTH)||\
																	  ((CLK) == CALCLK_RCL)||\
																	  ((CLK) == CALCLK_XTL))
/**
  * @} TMER CLKTRMI_RCNT
  */
#define IS_CLKTRMI_RCNT_VALUE(VALUE)  ((VALUE>=0x00000000)&&(VALUE<= 0xffffffff))
#define IS_CLKTRMI_CAL_VALUE(VALUE)   ((VALUE>=0x00000000)&&(VALUE<= 0x0000ffff))


/**
  * @} TMER CLKTRIM_FLAG
  */
#define  CLKTRIM_FLAG_STOP       ((uint32_t)0x00000001)
#define  CLKTRIM_FLAG_CALCNTOF   ((uint32_t)0x00000002)
#define  CLKTRIM_FLAG_LXTFAULT   ((uint32_t)0x00000004)
#define  CLKTRIM_FLAG_HXTFAULT   ((uint32_t)0x00000008)
#define  CLKTRIM_FLAG_HXTSTOP    ((uint32_t)0x00000010)
#define  CLKTRIM_FLAG_X32KSTOP   ((uint32_t)0x00000020)

#define IS_CLKTRMI_FLAG(FLAG)  ((FLAG == CLKTRIM_FLAG_STOP)    ||\
                                (FLAG == CLKTRIM_FLAG_CALCNTOF)||\
                                (FLAG == CLKTRIM_FLAG_LXTFAULT)||\
																(FLAG == CLKTRIM_FLAG_HXTFAULT)||\
																(FLAG == CLKTRIM_FLAG_HXTSTOP) ||\
																(FLAG == CLKTRIM_FLAG_X32KSTOP))
																	
																	
/**
  * @} function define
  */																	
void ClkTrim_ClkConfig(CLKTRIM_TypeDef*CLKTRIMx,uint32_t Refclk,uint32_t Calclk);
void ClkTrim_StartCmd(CLKTRIM_TypeDef*CLKTRIMx,FunctionalState NewState);
void ClkTrim_MonitorCmd(CLKTRIM_TypeDef*CLKTRIMx,FunctionalState NewState);
void ClkTrim_ClkCmd(CLKTRIM_TypeDef*CLKTRIMx,FunctionalState NewState);
void ClkTrim_SetRcntValue(CLKTRIM_TypeDef*CLKTRIMx,uint32_t Value);
void ClkTrim_SetCalValue(CLKTRIM_TypeDef*CLKTRIMx,uint32_t Value);
uint32_t ClkTrim_GetRefValue(CLKTRIM_TypeDef*CLKTRIMx);
uint32_t ClkTrim_GetCalValue(CLKTRIM_TypeDef*CLKTRIMx);
uint32_t ClkTrim_ITCmd(CLKTRIM_TypeDef*CLKTRIMx,FunctionalState NewState);
FlagStatus ClkTrim_GetFlagStatus(CLKTRIM_TypeDef*CLKTRIMx, uint16_t CLKTRIM_FLAG);
void ClkTrim_ClearFlagStatus(CLKTRIM_TypeDef*CLKTRIMx, uint16_t CLKTRIM_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __CX32LOO3_CLKTRIM_H */


/************************ (C) COPYRIGHT cx32l003 *****END OF FILE****/

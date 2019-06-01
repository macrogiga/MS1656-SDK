/**
  ******************************************************************************
  * @file    cx32l003_uart.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    15-10-2018
  * @brief   This file contains all the functions prototypes for the LPUART 
  *          firmware library.
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
#ifndef __CX32l003_LPLPUART_H
#define __CX32l003_LPLPUART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */
typedef struct
{
  uint32_t LPUART_BaudRate;            /*!< This member configures the LPUART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (LPUART_InitStruct->LPUART_BaudRate)))
                                        - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */
	
	uint32_t LPUART_BaudRateDbaud_Enable; /*baud rate double enable*/
	
	
  uint32_t LPUART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref LPUART_Mode */
	
	uint32_t LPUART_BaudRateTimer_Selected; /*Select lptimer*/
	
	uint32_t LPUART_SCLKSEL;         /*Select the lpuart sclk*/
	
	uint32_t LPUART_SCLKPRS;         /*lpuart Prescale Vlaue*/
	
	
} LPUART_InitTypeDef;

/** 
  * @brief  LPUART Clock Init Structure definition  
  */ 
  
typedef struct
{
  uint16_t LPUART_SetSCLK;       /*Set the lpuart sclk*/     
	
	uint16_t LPUART_PreDivSCLK;    /*Set the lpuart PreDivSCLK*/    

} LPUART_ClockInitTypeDef;



/** @defgroup LPUART_Exported_Constants
  * @{
  */ 
  
#define IS_LPUART_ALL_PERIPH(PERIPH)    (PERIPH) == LPUART)
                                      
/** @defgroup LPUART_Clock 
  * @{
  */ 
#define LPUART_Clock_Disable                  ((uint16_t)0x00000000)
#define LPUART_Clock_Enable                   ((uint16_t)0x00000800)
#define IS_LPUART_CLOCK(CLOCK) (((CLOCK) == LPUART_Clock_Disable)||\
                                ((CLOCK) == LPUART_Clock_Enable))
															 
															 
															 
/** @defgroup LPUART_MODE 
  * @{
  */ 															 
#define  LPUART_MODE0   (uint16_t)0x00000000
#define  LPUART_MODE1   (uint16_t)0x00000001
#define  LPUART_MODE2   (uint16_t)0x00000002
#define  LPUART_MODE3   (uint16_t)0x00000003
#define IS_LPUART_MODE(MODE) (((MODE) == LPUART_MODE0)||\
                              ((MODE) == LPUART_MODE1)||\
                              ((MODE) == LPUART_MODE2)||\
															((MODE) == LPUART_MODE3))
														
														
														
#define IS_LPUART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0044AA21))														
#define LPUART_Address_Mask          ((uint16_t)0xFF00)  /*!< USART address Mask */													
#define IS_LPUART_ADDRESS(ADDRESS)   ((ADDRESS) <= 0xFF)

/** @defgroup LPUART_SCLK 
  * @{
  */ 
#define  LPUART_SCLK_MASK    ((uint32_t)0x00000003<<11)
#define  LPUART_SCLK_PCLK    ((uint32_t)0x00000000<<11)
#define  LPUART_SCLK_PCLK1   ((uint32_t)0x00000001<<11)
#define  LPUART_SCLK_LXT     ((uint32_t)0x00000002<<11)
#define  LPUART_SCLK_LIRC    ((uint32_t)0x00000003<<11)
#define IS_LPUART_SCLK(CLK)  ((CLK == LPUART_SCLK_PCLK) ||\
                              (CLK == LPUART_SCLK_PCLK1)||\
                              (CLK == LPUART_SCLK_LXT)  ||\
														  (CLK == LPUART_SCLK_LIRC))
															 
/** @defgroup LPUART_SCLK_DIV 
  * @{
  */ 															 
#define  LPUART_SCLK_DIV_MASK  ((uint32_t)0x00000007<<13)														 								 
#define  LPUART_SCLK_DIV128    ((uint32_t)0x00000000<<13)
#define  LPUART_SCLK_DIV64     ((uint32_t)0x00000001<<13)
#define  LPUART_SCLK_DIV32     ((uint32_t)0x00000002<<13)
#define  LPUART_SCLK_DIV16     ((uint32_t)0x00000003<<13)
#define  LPUART_SCLK_DIV8      ((uint32_t)0x00000004<<13)
#define  LPUART_SCLK_DIV4      ((uint32_t)0x00000005<<13)
#define  LPUART_SCLK_DIV2      ((uint32_t)0x00000006<<13)
#define  LPUART_SCLK_DIV1      ((uint32_t)0x00000007<<13)
#define IS_LPUART_SCLKDIV(CLKDIV)   ((CLKDIV == LPUART_SCLK_DIV128)||\
                                     (CLKDIV == LPUART_SCLK_DIV64) ||\
                                     (CLKDIV == LPUART_SCLK_DIV32) ||\
																		 (CLKDIV == LPUART_SCLK_DIV16) ||\
																		 (CLKDIV == LPUART_SCLK_DIV8)  ||\
																		 (CLKDIV == LPUART_SCLK_DIV4)  ||\
																		 (CLKDIV == LPUART_SCLK_DIV2)  ||\
																		 (CLKDIV == LPUART_SCLK_DIV1))
																			 
/** @defgroup LPUART_SCLK_LP_MODE 
  * @{
  */ 																			 
#define   LPUART_SCON_LPENABLE     ((uint32_t)0x00000001<<16)
#define   LPUART_SCON_LPDISABLE    ((uint32_t)0x00000000<<16)


/**
  * @}
  */
/******************  Bit definition for USART_SCON register  *******************/
#define  LPUART_SCON_RIEN                        (uint32_t)0x00000001
#define  LPUART_SCON_TIEN                        (uint32_t)0x00000002
#define  LPUART_SCON_RB8                         (uint32_t)0x00000004
#define  LPUART_SCON_TB8                         (uint32_t)0x00000008
#define  LPUART_SCON_REN                         (uint32_t)0x00000010
#define  LPUART_SCON_SM2                         (uint32_t)0x00000020
#define  LPUART_SCON_SM1                         (uint32_t)0x00000040
#define  LPUART_SCON_SM0                         (uint32_t)0x00000080
#define  LPUART_SCON_TEEN                        (uint32_t)0x00000100
#define  LPUART_SCON_DBAUD                       (uint32_t)0x00000200
#define  LPUART_SCON_LPMODE                      (uint32_t)0x00000400
#define  LPUART_SCON_LPEN                        (uint32_t)0x00010000


#define  LPUART_SCON_MODE0                       ~(LPUART_SCON_SM1|LPUART_SCON_SM0)
#define  LPUART_SCON_MODE1                       LPUART_SCON_SM1
#define  LPUART_SCON_MODE2                       LPUART_SCON_SM0
#define  LPUART_SCON_MODE3                       LPUART_SCON_SM1|LPUART_SCON_SM0

/******************  Bit definition for USART_ISR register  *******************/
#define  LPUART_ISR_RI                       (uint32_t)0x00000001
#define  LPUART_ISR_TI                       (uint32_t)0x00000002
#define  LPUART_ISR_FEI                      (uint32_t)0x00000004
#define  LPUART_ISR_TE                       (uint32_t)0x00000008
#define IS_LPUART_ISR(FLAG)                  ((FLAG ==LPUART_ISR_RI) ||\
                                              (FLAG==LPUART_ISR_TI)  ||\
                                              (FLAG ==LPUART_ISR_FEI)||\
																		          (FLAG==LPUART_ISR_TE))

/******************  Bit definition for USART_ICR register  *******************/
#define  LPUART_ICR_RI                       (uint32_t)0x00000001
#define  LPUART_ICR_TI                       (uint32_t)0x00000002
#define  LPUART_ICR_FEI                      (uint32_t)0x00000004
#define  LPUART_ICR_TE                       (uint32_t)0x00000008
#define  LPUART_ICR_ALL                      (uint32_t)0x0000000f
#define IS_LPUART_ICR(FLAG)                  ((FLAG ==LPUART_ICR_RI) ||\
                                              (FLAG==LPUART_ICR_TI)  ||\
                                              (FLAG ==LPUART_ICR_FEI)||\
																		          (FLAG==LPUART_ICR_TE)  ||\
																		          (FLAG ==LPUART_ICR_ALL))


#define LPUART_SELF_BRG                      (uint32_t)0x00010000
#define  LPUART_RXEN_EABLE                   (uint32_t)0x00000001
#define  LPUART_TXEN_EABLE                   (uint32_t)0x00000002
#define  LPUART_RIEN_EABLE                   (uint32_t)0x00000001
#define  LPUART_TIEN_EABLE                   (uint32_t)0x00000002
#define  LPUART_REEN_EABLE                   (uint32_t)0x00000010
#define  IS_LPUART_ITENABLE(ITENABLE)        ((ITENABLE==LPUART_RIEN_EABLE)||\
                                              (ITENABLE==LPUART_TIEN_EABLE)||\
                                              (ITENABLE==LPUART_REEN_EABLE))
                                        


#define  LPUART_LPTIM_EABLE                      (uint32_t)0x0000020B
#define  LPUART_LPTIMRUN_EABLE                   (uint32_t)0x00000001

#define LPUART_TE_ENABLE                     ((uint32_t)0x00000001<<8)
#define LPUART_TE_DISABLE                    ((uint32_t)0x00000000<<8)
#define IS_LPUART_TE(NewStatus)   ((NewStatus == LPUART_TE_ENABLE)||\
                                   (NewStatus == LPUART_TE_DISABLE))






/** @defgroup LPUART_Exported_Functions
  * @{
  */
void LPUART_DeInit(LPUART_TypeDef* LPUARTx);
void LPUART_Init(LPUART_TypeDef* LPUARTx, LPTIMER_TypeDef* TIMERx,LPUART_InitTypeDef* LPUART_InitStruct,FunctionalState LPModeState);
void LPUART_StructInit(LPUART_InitTypeDef* LPUART_InitStruct);
void LPUART_ClockInit(LPUART_TypeDef* LPUARTx, LPUART_ClockInitTypeDef* LPUART_ClockInitStruct);
void LPUART_ClockStructInit(LPUART_ClockInitTypeDef* LPUART_ClockInitStruct);
void LPUART_Cmd(LPUART_TypeDef* LPUARTx,uint16_t FuncState, FunctionalState NewState);
void LPUART_ITConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT, FunctionalState NewState);
void LPUART_LowPowerCmd(LPUART_TypeDef* LPUARTx,  FunctionalState NewState);
void LPUART_SetAddress(LPUART_TypeDef* LPUARTx, uint8_t LPUART_Address,uint8_t LPUART_Address_Enable);
void LPUART_ModeConfig(LPUART_TypeDef* LPUARTx, uint32_t LpuartMode);
void LPUART_ReciveCmd(LPUART_TypeDef* LPUARTx, LPUART_InitTypeDef* LPUART_InitStruct,FunctionalState NewState);
void LPUART_SendData(LPUART_TypeDef* LPUARTx, uint8_t Data);
uint8_t LPUART_ReceiveData(LPUART_TypeDef* LPUARTx);
FlagStatus LPUART_GetFlagStatus(LPUART_TypeDef* LPUARTx, uint16_t LPUART_Flag);
void LPUART_ClearITFlag(LPUART_TypeDef* LPUARTx, uint16_t LPUART_Flag);


#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_LPUART_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/

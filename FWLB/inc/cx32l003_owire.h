/**
  ******************************************************************************
  * @file    cx32l003_owire.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the OWIRE firmware 
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
#ifndef __CX32LOO3_OWIRE_H
#define __CX32LOO3_OWIRE_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"

/** 
  * @brief  struct OWIRE_InitTypeDef 
  */
typedef struct
{
	uint16_t WIRE_RDMODE;     /*!<byte mode bit send order*/ 
	
  uint16_t WIRE_MSBFIRST;   /*!<byte mode bit send order*/ 

  uint16_t WIRE_EN;         /*!<Data Processing Control Bit*/  	

  uint16_t WIRE_SIZE;       /*!<Data Size Settings*/           

  uint16_t WIRE_COUNTCLK;   /*!<Counting Clock Source Selection*/
	
  uint16_t WIRE_NFEN;       /*!<Filter function control bit*/
	
	uint16_t WIRE_NFDIV;      /*!<Selection of filter clock source*/
	
	uint16_t WIRE_RESCNT;     /*!<Master reset pulse of counte value of us*/
	
	uint16_t WIRE_PRESCNT;    /*!<Device presence pluse of counte value of us*/
	
	uint16_t WIRE_BITRATECNT; /*!<Setting counter of one bit time of us*/
	
	uint16_t WIRE_DRVCNT;     /*!<Drive time count value of us*/
	
	uint16_t WIRE_RDSMPCNT;   /*!<Read Sampling Time of Main Device of us*/
	
	uint16_t WIRE_RECCNT;     /*!<Counting Interval Value of us*/
	
}OWIRE_InitTypeDef;



/** @defgroup OWIRE_Exported_constants 
  * @{
  */
#define IS_OWIRE_ALL_PERIPH(PERIPH) ((PERIPH) == OWIRE)


/** 
  * @brief  COUNTCLKDIV 
  */
#define    COUNTCLKDIV      (uint32_t)0x00000000  /*!<Clock source div1*/
#define    COUNTCLKDIV2     (uint32_t)0x00000001  /*!<Clock source div2*/
#define    COUNTCLKDIV4     (uint32_t)0x00000002  /*!<Clock source div4*/
#define    COUNTCLKDIV16    (uint32_t)0x00000003  /*!<Clock source div16*/
#define    IS_OWIRE_ALL_COUNTCLK(CLK) (((CLK) == COUNTCLKDIV) ||\
                                       ((CLK) == COUNTCLKDIV2)||\
                                       ((CLK) == COUNTCLKDIV4)||\
																			 ((CLK) == COUNTCLKDIV16))
                                        
/** 
  * @brief  NFCLKDIV 
  */
#define    NFCLKDIV      (uint32_t)0x00000000   /*!<Input terminal filter clock div1 */
#define    NFCLKDIV2     (uint32_t)0x00000001   /*!<Input terminal filter clock div2*/
#define    NFCLKDIV4     (uint32_t)0x00000002   /*!<Input terminal filter clock div4*/
#define    NFCLKDIV8     (uint32_t)0x00000003   /*!<Input terminal filter clock div8*/
#define    IS_OWIRE_ALL_NFCLK(CLK)    (((CLK) == NFCLKDIV) ||\
                                       ((CLK) == NFCLKDIV2)||\
                                       ((CLK) == NFCLKDIV4)||\
																			 ((CLK) == NFCLKDIV8))

/** 
	* @brief  OWIR CMD 
	*/
#define  OWIREENABLE      (uint32_t)0x00000020
#define  OWIREDISABLE     (uint32_t)0x00000000


/** 
	* @brief Set the width of pluse
	*/
#define  OWIRE1bit      (uint32_t)0x00000000
#define  OWIRE8bit      (uint32_t)0x00000010
	
	
/** 
	* @brief  
	*/
#define  MSBFIRST     (uint32_t)0x00000040 /*High priority transmission*/
#define  LSBFIRST     (uint32_t)0x00000000 /*LOW priority transmission*/

/** 
	* @brief  Set Reading Mode
	*/
#define  RDMODE      (uint32_t)0x00000080   /*Equal BIT Reading Mode*/
#define  NRDMODE     (uint32_t)0x00000000  /*Ordinary reading mode*/
	

/** 
  * @brief Filter enabling control
  */
#define  NFENABLE      (uint32_t)0x00000010
#define  NFDISABLE     (uint32_t)0x00000000
	
	
/** 
  * @brief  COMMAND
  */
#define  COMMANDINITIAL      (uint32_t)0x00000001
#define  COMMANDTX           (uint32_t)0x00000002
#define  COMMANDRX           (uint32_t)0x00000003
#define    IS_OWIRE_ALL_COMMAND(COMMAND)    (((COMMAND) == COMMANDINITIAL)||\
																						 ((COMMAND) == COMMANDTX)     ||\
																						 ((COMMAND) == COMMANDRX))
																						
	
/** 
  * @brief  COMMAND
  */
	
#define   OWIRE_FLAG_RXDONE        (uint32_t)0x00000008
#define   OWIRE_FLAG_TXDONE        (uint32_t)0x00000004
#define   OWIRE_FLAG_INITDONE      (uint32_t)0x00000002
#define   OWIRE_FLAG_ACKERR        (uint32_t)0x00000001
#define   OWIRE_FLAG_TRXDONE       (uint32_t)0x0000000C
#define   IS_OWIRE_ALL_FLAG(FLAG)  (((FLAG) == OWIRE_FLAG_RXDONE)  ||\
																		((FLAG) == OWIRE_FLAG_TXDONE)  ||\
																		((FLAG) == OWIRE_FLAG_INITDONE)||\
																		((FLAG) == OWIRE_FLAG_ACKERR)  ||\
																		((FLAG) == OWIRE_FLAG_TRXDONE))
																		
/** 
  * @brief  OWIRE_CR_MASK
  */
#define OWIRE_CR_MASK   (uint32_t)0x00000020
																		


	
/** @defgroup OWIRE_Exported_Functions
  * @{
  */
void OWIRE_Init(OWIRE_TypeDef* OWIREx, OWIRE_InitTypeDef* OWIRE_InitStruct);
void OWIRE_Cmd(OWIRE_TypeDef* WIREx, FunctionalState NewState);
void  OWIRE_Initial(OWIRE_TypeDef* WIREx, uint8_t Data);
void OWIRE_SendData(OWIRE_TypeDef* WIREx, uint8_t Data);
uint8_t OWIRE_ReceiveData(OWIRE_TypeDef* WIREx);
void OWIRE_ITConfig(OWIRE_TypeDef* WIREx, uint32_t OWIRE_IT, FunctionalState NewState);
FlagStatus OWIRE_GetFlagStatus(OWIRE_TypeDef* WIREx, uint32_t OWIRE_FLAG);
void OWIRE_ITClear(OWIRE_TypeDef* WIREx, uint16_t OWIRE_IT);
void OWIRE_Command(OWIRE_TypeDef* WIREx, uint8_t Command);



#ifdef __cplusplus
}
#endif

#endif /*__CX32LOO3_OWIRE_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************(C)COPYRIGHT XMC*********END OF FILE***************************************/

	
	
	
	
	
	
	




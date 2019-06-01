/**
  ******************************************************************************
  * @file    cx32l003_i2c.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the I2C firmware 
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
  * <h2><center>&copy; COPYRIGHT 2018 XMC </center></h2>
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32LOO3_I2C_H
#define __CX32LOO3_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"


/** @addtogroup struct I2C_EveType 
  * @{
  */
	typedef struct
{
	uint16_t  I2C_Master_Send;  /*!< Master send*/
	uint16_t  I2C_Master_Recive; /*!<Master Recive*/
	uint16_t  I2C_Slave_Send;  /*!<Slave Send*/
	uint16_t  I2C_Slave_Recive; /*!<Slave Recive*/
	uint16_t  I2C_Rest_Eve; /*!<Rest Eve*/
}I2C_EveTypeDef;


/** @addtogroup struct I2C_InitType 
  * @{
  */
typedef struct
{
  uint32_t I2C_ClockSpeed;          /*!< Specifies the clock frequency.
                                         This parameter must be set to a value lower than 400kHz */
  uint16_t I2C_Mode;                /*!< Specifies the I2C mode.
                                         This parameter can be a value of  I2C_mode */
  uint16_t I2C_OwnAddress;         /*!< Specifies the first device own address.
                                         This parameter can be a 7-bit or 10-bit address. */
  uint16_t I2C_Ack;                 /*!< Enables or disables the acknowledgement.
                                         This parameter can be a value of I2C_acknowledgement */
  uint16_t I2C_BroadcastAddress_Response; /*!< Enables or disables the BroadcastAddress Response .
                                         This parameter can be a value of the BroadcastAddress Response */
}I2C_InitTypeDef;


/* Exported types ------------------------*/
#define IS_I2C_ALL_PERIPH(PERIPH) (((PERIPH) == I2C) 




/* I2C AA mask */
#define CR_AA_Set           ((uint32_t)0x00000004)
#define CR_AA_Reset         ((uint32_t)0xFFFFFFFB)

/* I2C SI mask */
#define CR_SI_Set           ((uint32_t)0x00000008)
#define CR_SI_Reset         ((uint32_t)0xFFFFFFF7)

/* I2C STO mask */
#define CR_STO_Set          ((uint32_t)0x00000010)
#define CR_STO_Reset        ((uint32_t)0xFFFFFFEF)

/* I2C STA mask */
#define CR_STA_Set          ((uint32_t)0x00000020)
#define CR_STA_Reset        ((uint32_t)0xFFFFFFDF)

/* I2C ENS mask */
#define CR_ENS_Set          ((uint32_t)0x00000040)
#define CR_ENS_Reset        ((uint32_t)0xFFFFFFBF)


/* I2C ADDR mask */
#define I2C_ADDR_ENGC_Set   ((uint32_t)0x00000001)
#define I2C_ADDR_ENGC_Reset ((uint32_t)0xFFFFFFFE)

/* I2C ADDR mask */
#define I2C_ADDR_Set           ((uint32_t)0x00000001)
#define I2C_ADDR_Reset         ((uint32_t)0x000000FE)




/* I2C TMRUN */
#define I2C_TMRUN_TME_Set      ((uint32_t)0x00000001)
#define I2C_TMRUN_TME_Reset    ((uint32_t)0xFFFFFFFE)


/* I2C FLAG mask */
#define FLAG_Mask               ((uint32_t)0x000000FF)


/** @defgroup I2C_mode 
  * @{
  */
#define I2C_Mode_Master            ((uint32_t)0x40)
#define I2C_Mode_Slave             ((uint32_t)0x44)
#define IS_I2C_MODE(MODE)          (((MODE) == I2C_Mode_Master)||\
                                    ((MODE) == I2C_Mode_Slave)) 
                         
/** @defgroup I2C_ACK Enable/Disable
  * @{
  */
#define I2C_Ack_Enable              ((uint32_t)0x0004)
#define I2C_Ack_Disable             ((uint32_t)0x0000)
#define IS_I2C_ACK_STATE(STATE)     (((STATE) == I2C_Ack_Enable) ||\
                                      ((STATE) == I2C_Ack_Disable))


/** @defgroup I2C_Module Enable/Disable
  * @{
  */
#define I2C_Module_Enable           ((uint32_t)0x00000040)
#define I2C_Module_Disable          ((uint32_t)0x000000BF)
#define IS_I2C_Module_STATE(STATE)  (((STATE) == I2C_Module_Enable) ||\
                                     ((STATE) == I2C_Module_Disable))

/** @defgroup I2C_transfer_direction 
  * @{
  */
#define  I2C_Direction_Transmitter      ((uint32_t)0x00000000)
#define  I2C_Direction_Receiver         ((uint32_t)0x00000001)
#define IS_I2C_DIRECTION(DIRECTION)     (((DIRECTION) == I2C_Direction_Transmitter) ||\
                                         ((DIRECTION) == I2C_Direction_Receiver))

/** @defgroup I2C_acknowledged_address 
  * @{
  */
#define I2C_ENBROADCAST_Bit    ((uint32_t)0x00000001)


/** @defgroup I2C_registers 
  * @{
  */
#define I2C_Register_CR                 ((uint32_t)0x00000000)
#define I2C_Register_DATA               ((uint32_t)0x00000004)
#define I2C_Register_ADDR               ((uint32_t)0x00000008)
#define I2C_Register_STAT               ((uint32_t)0x0000000C)
#define I2C_Register_TMRUN              ((uint32_t)0x00000010)
#define I2C_Register_TM                 ((uint32_t)0x00000014)
#define IS_I2C_REGISTER(REGISTER) (((REGISTER) == I2C_Register_CR)   || \
                                   ((REGISTER) == I2C_Register_DATA) || \
                                   ((REGISTER) == I2C_Register_ADDR) || \
                                   ((REGISTER) == I2C_Register_STAT) || \
                                   ((REGISTER) == I2C_Register_TMRUN)|| \
                                   ((REGISTER) == I2C_Register_TM)) 
																	 
/** @defgroup I2C_interrupts_definition 
  * @{
  */
#define I2C_IT_ENABLE                     ((uint32_t)0x00000008)


/** @defgroup I2C_own_address 
  * @{
  */
#define IS_I2C_OWN_ADDRESS(ADDRESS) ((ADDRESS) <= 0x7F)


/** @defgroup I2C_clock_speed 
  * @{
  */
#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) >= 0x1) && ((SPEED) <= 400000))


/** @defgroup I2C_Exported_Functions
  * @{
  */
void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_MasterSendCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddressConfig(I2C_TypeDef* I2Cx, uint8_t Address);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Broadcast_Respone);
void I2C_ITConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint32_t I2C_Register);

#ifdef __cplusplus
}
#endif

#endif /*__CX32LOO3_I2C_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE*********************/



/**
  *****************************************************************************
  * @file    cx32l003_gpio.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    27-July-2018
  * @brief   This file contains all the functions prototypes for the GPIO firmware
  *          library.  
  *****************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32l003_GPIO_H
#define __CX32l003_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	 
/* Exported types ------------------------------------------------------------*/
#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD))

/** 
  * @brief  GPIO Configuration Mode enumeration 
  */   
typedef enum
{ 
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog Mode */
}GPIOMode_TypeDef;
#define IS_GPIO_MODE(MODE)  (((MODE) == GPIO_Mode_IN)  || \
                             ((MODE) == GPIO_Mode_OUT) || \
                             ((MODE) == GPIO_Mode_AF)  || \
                             ((MODE) == GPIO_Mode_AN))

/** 
  * @brief  GPIO Output type enumeration 
  */  
typedef enum
{ 
  GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;
#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || \
                              ((OTYPE) == GPIO_OType_OD))

/** 
  * @brief  GPIO  Output speed enumeration
  */  
typedef enum
{ 
  GPIO_Low_Speed     = 0x00, /*!< Low speed    */
  GPIO_Medium_Speed  = 0x01, /*!< Medium speed */
  GPIO_Fast_Speed    = 0x02, /*!< Fast speed   */
  GPIO_High_Speed    = 0x03  /*!< High speed   */
}GPIOSpeed_TypeDef;

/* Add legacy definition */
#define  GPIO_Speed_2MHz    GPIO_Low_Speed    
#define  GPIO_Speed_25MHz   GPIO_Medium_Speed 
#define  GPIO_Speed_50MHz   GPIO_Fast_Speed 
#define  GPIO_Speed_100MHz  GPIO_High_Speed  
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Low_Speed)   || \
                              ((SPEED) == GPIO_Medium_Speed)|| \
                              ((SPEED) == GPIO_Fast_Speed)  || \
                              ((SPEED) == GPIO_High_Speed)) 

/** 
  * @brief  GPIO Configuration PullUp PullDown enumeration 
  */ 
typedef enum
{ 
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02,
	GPIO_PuPd_ALL    = 0x03
}GPIOPuPd_TypeDef;
#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL)||\
                            ((PUPD) == GPIO_PuPd_UP)    ||\
                            ((PUPD) == GPIO_PuPd_DOWN)) ||\
                            ((PUPD) == GPIO_PuPd_ALL)) 

/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */ 
typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET
}BitAction;
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) ||\
                                    ((ACTION) == Bit_SET))
/** 
  * @brief   GPIO Init structure definition  
  */ 
typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */

  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef */

  GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef */

  GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef */
}GPIO_InitTypeDef;


/** @defgroup GPIO_pins_define 
  * @{
  */ 
#define GPIO_Pin_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_All               ((uint16_t)0x00FF)  /* All pins selected */
#define GPIO_PIN_MASK              ((uint32_t)0x00FF) /* PIN mask for assert test */
#define IS_GPIO_PIN(PIN)           (((PIN) & GPIO_PIN_MASK ) != (uint32_t)0x00)
#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7))
                              
/** @defgroup GPIO_Pin_sources 
  * @{
  */ 
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7))
																			 
																			 

/** @defgroup GPIO_Pin_direction_mode
  * @{
  */ 
#define  GPIO_PIN_OUT_MODE    ((uint32_t)0x00000001) 
#define  GPIO_PIN_IN_MODE     ((uint32_t)0x00000000)  
#define IS_GPIO_PIN_DIRECTION(PINMODE) (((PINMODE) == GPIO_PIN_OUT_MODE)|| \
                                        ((PINMODE) == GPIO_PIN_IN_MODE))



/******************  Bits definition for GPIO_MODER register  *****************/
#define GPIO_MODER_MODER0                    ((uint32_t)0x0000000f)
#define GPIO_MODER_MODER0_0                  ((uint32_t)0x00000000)
#define GPIO_MODER_MODER0_1                  ((uint32_t)0x00000001)
#define GPIO_MODER_MODER0_2                  ((uint32_t)0x00000002)
#define GPIO_MODER_MODER0_3                  ((uint32_t)0x00000003)
#define GPIO_MODER_MODER0_4                  ((uint32_t)0x00000004)
#define GPIO_MODER_MODER0_5                  ((uint32_t)0x00000005)
#define GPIO_MODER_MODER0_6                  ((uint32_t)0x00000006)
#define GPIO_MODER_MODER0_7                  ((uint32_t)0x00000007)


#define GPIO_MODER_MODER1                    ((uint32_t)0x000000f0)
#define GPIO_MODER_MODER1_0                  ((uint32_t)0x00000000)
#define GPIO_MODER_MODER1_1                  ((uint32_t)0x00000010)
#define GPIO_MODER_MODER1_2                  ((uint32_t)0x00000020)
#define GPIO_MODER_MODER1_3                  ((uint32_t)0x00000030)
#define GPIO_MODER_MODER1_4                  ((uint32_t)0x00000040)
#define GPIO_MODER_MODER1_5                  ((uint32_t)0x00000050)
#define GPIO_MODER_MODER1_6                  ((uint32_t)0x00000060)
#define GPIO_MODER_MODER1_7                  ((uint32_t)0x00000070)


#define GPIO_MODER_MODER2                    ((uint32_t)0x00000f00)
#define GPIO_MODER_MODER2_0                  ((uint32_t)0x00000000)
#define GPIO_MODER_MODER2_1                  ((uint32_t)0x00000100)
#define GPIO_MODER_MODER2_2                  ((uint32_t)0x00000200)
#define GPIO_MODER_MODER2_3                  ((uint32_t)0x00000300)
#define GPIO_MODER_MODER2_4                  ((uint32_t)0x00000400)
#define GPIO_MODER_MODER2_5                  ((uint32_t)0x00000500)
#define GPIO_MODER_MODER2_6                  ((uint32_t)0x00000600)
#define GPIO_MODER_MODER2_7                  ((uint32_t)0x00000700)


#define GPIO_MODER_MODER3                    ((uint32_t)0x0000f000)
#define GPIO_MODER_MODER3_0                  ((uint32_t)0x00000000)
#define GPIO_MODER_MODER3_1                  ((uint32_t)0x00001000)
#define GPIO_MODER_MODER3_2                  ((uint32_t)0x00002000)
#define GPIO_MODER_MODER3_3                  ((uint32_t)0x00003000)
#define GPIO_MODER_MODER3_4                  ((uint32_t)0x00004000)
#define GPIO_MODER_MODER3_5                  ((uint32_t)0x00005000)
#define GPIO_MODER_MODER3_6                  ((uint32_t)0x00006000)
#define GPIO_MODER_MODER3_7                  ((uint32_t)0x00007000)


#define GPIO_MODER_MODER4                    ((uint32_t)0x000f0000)
#define GPIO_MODER_MODER4_0                  ((uint32_t)0x00000000)
#define GPIO_MODER_MODER4_1                  ((uint32_t)0x00010000)
#define GPIO_MODER_MODER4_2                  ((uint32_t)0x00020000)
#define GPIO_MODER_MODER4_3                  ((uint32_t)0x00030000)
#define GPIO_MODER_MODER4_4                  ((uint32_t)0x00040000)
#define GPIO_MODER_MODER4_5                  ((uint32_t)0x00050000)
#define GPIO_MODER_MODER4_6                  ((uint32_t)0x00060000)
#define GPIO_MODER_MODER4_7                  ((uint32_t)0x00070000)



#define GPIO_MODER_MODER5                    ((uint32_t)0x00f00000)
#define GPIO_MODER_MODER5_0                  ((uint32_t)0x00000000)
#define GPIO_MODER_MODER5_1                  ((uint32_t)0x00100000)
#define GPIO_MODER_MODER5_2                  ((uint32_t)0x00200000)
#define GPIO_MODER_MODER5_3                  ((uint32_t)0x00300000)
#define GPIO_MODER_MODER5_4                  ((uint32_t)0x00400000)
#define GPIO_MODER_MODER5_5                  ((uint32_t)0x00500000)
#define GPIO_MODER_MODER5_6                  ((uint32_t)0x00600000)
#define GPIO_MODER_MODER5_7                  ((uint32_t)0x00700000)



#define GPIO_MODER_MODER6                    ((uint32_t)0x0f000000)
#define GPIO_MODER_MODER6_0                  ((uint32_t)0x00000000)
#define GPIO_MODER_MODER6_1                  ((uint32_t)0x01000000)
#define GPIO_MODER_MODER6_2                  ((uint32_t)0x02000000)
#define GPIO_MODER_MODER6_3                  ((uint32_t)0x03000000)
#define GPIO_MODER_MODER6_4                  ((uint32_t)0x04000000)
#define GPIO_MODER_MODER6_5                  ((uint32_t)0x05000000)
#define GPIO_MODER_MODER6_6                  ((uint32_t)0x06000000)
#define GPIO_MODER_MODER6_7                  ((uint32_t)0x07000000)



#define GPIO_MODER_MODER7                    ((uint32_t)0xf0000000)
#define GPIO_MODER_MODER7_0                  ((uint32_t)0x00000000)
#define GPIO_MODER_MODER7_1                  ((uint32_t)0x10000000)
#define GPIO_MODER_MODER7_2                  ((uint32_t)0x20000000)
#define GPIO_MODER_MODER7_3                  ((uint32_t)0x30000000)
#define GPIO_MODER_MODER7_4                  ((uint32_t)0x40000000)
#define GPIO_MODER_MODER7_5                  ((uint32_t)0x50000000)
#define GPIO_MODER_MODER7_6                  ((uint32_t)0x60000000)
#define GPIO_MODER_MODER7_7                  ((uint32_t)0x70000000)


/******************  Bits definition for GPIO_OTYPER register  ****************/
#define GPIO_OTYPER_OT_0                     ((uint32_t)0x00000001)
#define GPIO_OTYPER_OT_1                     ((uint32_t)0x00000002)
#define GPIO_OTYPER_OT_2                     ((uint32_t)0x00000004)
#define GPIO_OTYPER_OT_3                     ((uint32_t)0x00000008)
#define GPIO_OTYPER_OT_4                     ((uint32_t)0x00000010)
#define GPIO_OTYPER_OT_5                     ((uint32_t)0x00000020)
#define GPIO_OTYPER_OT_6                     ((uint32_t)0x00000040)
#define GPIO_OTYPER_OT_7                     ((uint32_t)0x00000080)



/******************  Bits definition for GPIO_PUPDR register  *****************/
#define GPIO_PUPDR_PUPDR0                    ((uint32_t)0x00000003)
#define GPIO_PUPDR_PUPDR0_0                  ((uint32_t)0x00000001)
#define GPIO_PUPDR_PUPDR0_1                  ((uint32_t)0x00000002)
#define GPIO_PUPDR_PUPDR1                    ((uint32_t)0x0000000C)
#define GPIO_PUPDR_PUPDR1_0                  ((uint32_t)0x00000004)
#define GPIO_PUPDR_PUPDR1_1                  ((uint32_t)0x00000008)
#define GPIO_PUPDR_PUPDR2                    ((uint32_t)0x00000030)
#define GPIO_PUPDR_PUPDR2_0                  ((uint32_t)0x00000010)
#define GPIO_PUPDR_PUPDR2_1                  ((uint32_t)0x00000020)
#define GPIO_PUPDR_PUPDR3                    ((uint32_t)0x000000C0)
#define GPIO_PUPDR_PUPDR3_0                  ((uint32_t)0x00000040)
#define GPIO_PUPDR_PUPDR3_1                  ((uint32_t)0x00000080)
#define GPIO_PUPDR_PUPDR4                    ((uint32_t)0x00000300)
#define GPIO_PUPDR_PUPDR4_0                  ((uint32_t)0x00000100)
#define GPIO_PUPDR_PUPDR4_1                  ((uint32_t)0x00000200)
#define GPIO_PUPDR_PUPDR5                    ((uint32_t)0x00000C00)
#define GPIO_PUPDR_PUPDR5_0                  ((uint32_t)0x00000400)
#define GPIO_PUPDR_PUPDR5_1                  ((uint32_t)0x00000800)
#define GPIO_PUPDR_PUPDR6                    ((uint32_t)0x00003000)
#define GPIO_PUPDR_PUPDR6_0                  ((uint32_t)0x00001000)
#define GPIO_PUPDR_PUPDR6_1                  ((uint32_t)0x00002000)
#define GPIO_PUPDR_PUPDR7                    ((uint32_t)0x0000C000)
#define GPIO_PUPDR_PUPDR7_0                  ((uint32_t)0x00004000)
#define GPIO_PUPDR_PUPDR7_1                  ((uint32_t)0x00008000)

/******************  Bits definition for GPIO_PUPDR register  *****************/
#define GPIO_DIDB_SYNCEN                     ((uint32_t)0x00000100)
#define GPIO_DIDB_PIN0EN                     ((uint32_t)0x00000001)
#define GPIO_DIDB_PIN1EN                     ((uint32_t)0x00000002)
#define GPIO_DIDB_PIN2EN                     ((uint32_t)0x00000004)
#define GPIO_DIDB_PIN3EN                     ((uint32_t)0x00000008)
#define GPIO_DIDB_PIN4EN                     ((uint32_t)0x00000010)
#define GPIO_DIDB_PIN5EN                     ((uint32_t)0x00000020)
#define GPIO_DIDB_PIN6EN                     ((uint32_t)0x00000040)
#define GPIO_DIDB_PIN7EN                     ((uint32_t)0x00000080)
#define GPIO_DIDB_PINMASK                    ((uint32_t)0x000000FF)


/****************** GPIO DBCLK set register *****************/
#define GPIO_DBCLK_EN                        ((uint32_t)0x00000010)
#define GPIO_DBCLK_1CYCLE                    ((uint32_t)0x00000000)
#define GPIO_DBCLK_2CYCLE                    ((uint32_t)0x00000001)
#define GPIO_DBCLK_4CYCLE                    ((uint32_t)0x00000002)
#define GPIO_DBCLK_8CYCLE                    ((uint32_t)0x00000003)
#define GPIO_DBCLK_16CYCLE                   ((uint32_t)0x00000004)
#define GPIO_DBCLK_32CYCLE                   ((uint32_t)0x00000005)
#define GPIO_DBCLK_64CYCLE                   ((uint32_t)0x00000006)
#define GPIO_DBCLK_128CYCLE                  ((uint32_t)0x00000007)
#define GPIO_DBCLK_256CYCLE                  ((uint32_t)0x00000008)
#define GPIO_DBCLK_512CYCLE                  ((uint32_t)0x00000009)
#define GPIO_DBCLK_1024CYCLE                 ((uint32_t)0x0000000A)
#define GPIO_DBCLK_2048CYCLE                 ((uint32_t)0x0000000B)
#define GPIO_DBCLK_4096CYCLE                 ((uint32_t)0x0000000C)
#define GPIO_DBCLK_8192CYCLE                 ((uint32_t)0x0000000D)
#define GPIO_DBCLK_16384CYCLE                ((uint32_t)0x0000000E)
#define GPIO_DBCLK_32768CYCLE                ((uint32_t)0x0000000F)
#define GPIO_DBCLK_CYCLEMASK                 ((uint32_t)0x0000000F)
#define IS_GPIO_DBCLK_CYCLE(CYCLE)    (((CYCLE) == GPIO_DBCLK_1CYCLE)    || \
                                       ((CYCLE) == GPIO_DBCLK_2CYCLE)    || \
                                       ((CYCLE) == GPIO_DBCLK_4CYCLE)    || \
                                       ((CYCLE) == GPIO_DBCLK_8CYCLE)    || \
                                       ((CYCLE) == GPIO_DBCLK_16CYCLE)   || \
                                       ((CYCLE) == GPIO_DBCLK_32CYCLE)   || \
                                       ((CYCLE) == GPIO_DBCLK_64CYCLE)   || \
                                       ((CYCLE) == GPIO_DBCLK_128CYCLE)  || \
																			 ((CYCLE) == GPIO_DBCLK_256CYCLE)  || \
                                       ((CYCLE) == GPIO_DBCLK_1024CYCLE) || \
                                       ((CYCLE) == GPIO_DBCLK_2048CYCLE) || \
                                       ((CYCLE) == GPIO_DBCLK_4096CYCLE) || \
                                       ((CYCLE) == GPIO_DBCLK_8192CYCLE) || \
                                       ((CYCLE) == GPIO_DBCLK_16384CYCLE)|| \
                                       ((CYCLE) == GPIO_DBCLK_32768CYCLE) )



/** @defgroup GPIO_Alternat_function_selection_define 
  * @{
  */ 
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF_NRST         ((uint8_t)0x00)  /* NRST Alternate Function mapping */
#define GPIO_AF_OSCIN        ((uint8_t)0x00)  /* OSCIN Alternate Function mapping */
#define GPIO_AF_OSCOUT       ((uint8_t)0x00)  /* OSCOUT Alternate Function mapping */
#define GPIO_AF_X32KOUT      ((uint8_t)0x00)  /* X32KOUT Alternate Function mapping */
#define GPIO_AF_X32KIN       ((uint8_t)0x00)  /* X32KIN Alternate Function mapping */
#define GPIO_AF_SWDIO        ((uint8_t)0x00)  /* SWDIO Alternate Function mapping */
#define GPIO_AF_SWDCLK       ((uint8_t)0x00)  /* SWDCLK Alternate Function mapping */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF_PWM2_CHB_PA1          ((uint8_t)0x01)  /* PWM2 Alternate Function mapping */
#define GPIO_AF_PWM3_CHA_PA2          ((uint8_t)0x01)  /* PWM3 Alternate Function mapping */
#define GPIO_AF_PWM3_CHB_PA3          ((uint8_t)0x01)  /* PWM3 Alternate Function mapping */
#define GPIO_AF_PWM_BRK_PB5           ((uint8_t)0x01)  /* PWM Alternate Function mapping */
#define GPIO_AF_TIM1_BKIN_PB5         ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_TIM1_ETR_PB3          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM_ECI_PB3           ((uint8_t)0x01)  /* PWM Alternate Function mapping */
#define GPIO_AF_TIM1_CH3N_PB2         ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM3_CHB_PB2          ((uint8_t)0x01)  /* PWM3 Alternate Function mapping */
#define GPIO_AF_TIM1_CH2N_PB1         ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM2_CHB_PB1          ((uint8_t)0x01)  /* PWM2 Alternate Function mapping */
#define GPIO_AF_TIM1_CH1N_PB0         ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM1_CHB_PB0          ((uint8_t)0x01)  /* PWM1 Alternate Function mapping */
#define GPIO_AF_TIM1_CH1_PC1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM1_CHA_PC1          ((uint8_t)0x01)  /* PWM1 Alternate Function mapping */
#define GPIO_AF_TIM1_CH2_PC2          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM2_CHA_PC2          ((uint8_t)0x01)  /* PWM2 Alternate Function mapping */
#define GPIO_AF_TIM1_CH3_PC3          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM3_CHA_PC3          ((uint8_t)0x01)  /* PWM3 Alternate Function mapping */
#define GPIO_AF_TIM1_CH4_PC4          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM4_CHA_PC4          ((uint8_t)0x01)  /* PWM4 Alternate Function mapping */
#define GPIO_AF_TIM1_BKIN_PC5         ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM_BPK_PC5           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF_TIM1_CH1_PC6          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM1_CHA_PC6          ((uint8_t)0x01)  /* PWM1 Alternate Function mapping */
#define GPIO_AF_TIM2_CH1_PC7          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF_PWM2_CHA_PC7          ((uint8_t)0x01)  /* PWM2 Alternate Function mapping */
#define GPIO_AF_TIM1_BKIN_PD0         ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM_BPK_PD0           ((uint8_t)0x01)  /* PWM Alternate Function mapping */
#define GPIO_AF_TIM1_CH2_PD2          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM2_CHA_PD2          ((uint8_t)0x01)  /* PWM2 Alternate Function mapping */
#define GPIO_AF_PWM3_CHB_PD3          ((uint8_t)0x01)  /* PWM3 Alternate Function mapping */
#define GPIO_AF_PWM1_CHA_PD4          ((uint8_t)0x01)  /* PWM1 Alternate Function mapping */
#define GPIO_AF_PWM1_CHB_PD5          ((uint8_t)0x01)  /* PWM1 Alternate Function mapping */
#define GPIO_AF_PWM2_CHA_PD6          ((uint8_t)0x01)  /* PWM2 Alternate Function mapping */
#define GPIO_AF_PWM4_CHA_PD7          ((uint8_t)0x01)  /* PWM4 Alternate Function mapping */
#define GPIO_AF_TIM1_CH4_PD7          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_LPTIMER_GATE_PB4      ((uint8_t)0x01)  /* LPTIMER GATE Function mapping */


/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF_TIM2_CH3_PA3          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF_PCA_CH1_PA4           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_CH2_PB7           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_CH3_PB6           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_CH4_PB5           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_ECI_PB4           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_ECI_PC0           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_TIM1_CH1N_PC3         ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM1_CHB_PC3          ((uint8_t)0x02)  /* PWM1 Alternate Function mapping */
#define GPIO_AF_TIM1_CH2N_PC4         ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_PWM2_CHB_PC4          ((uint8_t)0x02)  /* PWM2 Alternate Function mapping */
#define GPIO_AF_TIM2_CH1_PC5          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF_PCA_CH0_PC5           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_TIM2_CH4_PC6          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF_PCA_CH3_PC6           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_CH4_PC7           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_ECI_PD1           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_TIM2_CH3_PD2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF_PCA_CH2_PD2           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_TIM2_CH2_PD3          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF_PCA_CH1_PD3           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_TIM2_CH1_PD4          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF_PCA_CH0_PD4           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_CH2_PD5           ((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF_PCA_CH3_PD6           ((uint8_t)0x02)  /* PCA Alternate Function mapping */


/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF_SPI_CLK_PA1          ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_NSS_PA2          ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_NSS_PA3          ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_CLK_PB5          ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_NSS_PB4          ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_NSS_PC0          ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_CLK_PC5          ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_MOSI_PC6         ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_MISO_PC7         ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_MISO_PD2         ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_MOSI_PD3         ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_RTC_OUT1HZ_PD4       ((uint8_t)0x03)  /* RTC Alternate Function mapping */
#define GPIO_AF_SPI_MISO_PD5         ((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF_SPI_M0SI_PD6         ((uint8_t)0x03)  /* SPI Alternate Function mapping */


/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF_I2C_SDA_PA1          ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_I2C_SCL_PA2          ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_RTC_OUT1HZ_PA3       ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_I2C_SDA_PB5          ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_I2C_SCL_PB4          ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_I2C_SDA_PC3          ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_I2C_SCL_PC4          ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_RTC_OUT1HZ_PD2       ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_I2C_SCL_PD5          ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_I2C_SDA_PD6          ((uint8_t)0x04)  /* I2C Alternate Function mapping */
#define GPIO_AF_TIM0_TOG_PD4         ((uint8_t)0x04)  /* TIM0 Alternate Function mapping */
#define GPIO_AF_HXTL_OUT_PD3         ((uint8_t)0x04)  /* HXT Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF_UART0_RX_PA1          ((uint8_t)0x05)  /* UART0 Alternate Function mapping */
#define GPIO_AF_UART0_TX_PA2          ((uint8_t)0x05)  /* UART0 Alternate Function mapping */
#define GPIO_AF_UART0_RX_PB5          ((uint8_t)0x05)  /* UART0 Alternate Function mapping */
#define GPIO_AF_UART0_TX_PB4          ((uint8_t)0x05)  /* UART0 Alternate Function mapping */
#define GPIO_AF_UART1_TX_PC3          ((uint8_t)0x05)  /* UART1 Alternate Function mapping */
#define GPIO_AF_UART1_RX_PC4          ((uint8_t)0x05)  /* UART1 Alternate Function mapping */
#define GPIO_AF_UART0_RX_PD3          ((uint8_t)0x05)  /* UART0 Alternate Function mapping */
#define GPIO_AF_UART0_TX_PD4          ((uint8_t)0x05)  /* UART0 Alternate Function mapping */
#define GPIO_AF_UART1_TX_PD5          ((uint8_t)0x05)  /* UART1 Alternate Function mapping */
#define GPIO_AF_UART1_RX_PD6          ((uint8_t)0x05)  /* UART1 Alternate Function mapping */
#define GPIO_AF_LPUART_TX_PC5         ((uint8_t)0x05)  /* LPUART Alternate Function mapping */
#define GPIO_AF_LPUART_RX_PC6         ((uint8_t)0x05)  /* LPUART Alternate Function mapping */
#define GPIO_AF_LPUART_TX_PD2         ((uint8_t)0x05)  /* LPUART Alternate Function mapping */
#define GPIO_AF_LPUART_RX_PA3         ((uint8_t)0x05)  /* LPUART Alternate Function mapping */

/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF_TIM0_TOG_PA1          ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_TIM0_TOGN_PA2         ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_PCA_ECI_PA3           ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_TIM1_TOG_PB5          ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_TIM1_TOGN_PB6         ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_PCA_CH1_PC3           ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_PCA_CH0_PC4           ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_TIM1_GATE_PC5         ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_TIM1_EXT_PC6          ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_TIM0_EXT_PD4          ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_TIM0_GATE_PD5         ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_PCA_ECI_PD7           ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_LIRC_OUT_PC7          ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_HIRC_OUT_PD1          ((uint8_t)0x06)  /*TIM0 Alternate Function mapping */
#define GPIO_AF_LPTIMER_EXT_PD6       ((uint8_t)0x06)  /*LPTIMER Alternate Function mapping */
#define GPIO_AF_LPTIMER_TOG_PD2       ((uint8_t)0x06)  /*LPTIMER TOG Alternate Function mapping */
#define GPIO_AF_LPTIMER_TOGN_PD3      ((uint8_t)0x06)  /*LPTIMER TOGN Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF_VCO_OUT_PA3         ((uint8_t)0x07)  /* VCO Alternate Function mapping  */
#define GPIO_AF_ADC_ETR_PB5         ((uint8_t)0x07)  /* ADC Alternate Function mapping  */
#define GPIO_AF_CLK_CCO_PC4         ((uint8_t)0x07)  /* CLK Alternate Function mapping  */
#define GPIO_AF_LVD_OUT_PC5         ((uint8_t)0x07)  /* LVD Alternate Function mapping */
#define GPIO_AF_CLK_CCO_PC6         ((uint8_t)0x07)  /* CLK Alternate Function mapping  */
#define GPIO_AF_CLK_CCO_PD0         ((uint8_t)0x07)  /* CLK Alternate Function mapping  */
#define GPIO_AF_VCO_OUT_PD1         ((uint8_t)0x07)  /* VCO Alternate Function mapping  */
#define GPIO_AF_1_WIRE_PD2          ((uint8_t)0x07)  /* 1_WIRE Alternate Function mapping  */
#define GPIO_AF_1_WIRE_PC3          ((uint8_t)0x07)  /* 1_WIRE Alternate Function mapping  */
#define GPIO_AF_ADC_ETR_PD3         ((uint8_t)0x07)  /* ADC Alternate Function mapping  */
#define GPIO_AF_BEEP_PD4            ((uint8_t)0x07)  /* BEEP Alternate Function mapping  */
#define GPIO_AF_CLKMCO_PC4          ((uint8_t)0x07)  /* BEEP Alternate Function mapping  */
#define GPIO_AF_CLKMCO_PC6          ((uint8_t)0x07)  /* BEEP Alternate Function mapping  */
#define GPIO_AF_LVDOUT_PC5          ((uint8_t)0x07)  /* BEEP Alternate Function mapping  */
#define GPIO_AF_LVDOUT_PB5          ((uint8_t)0x07)  /* BEEP Alternate Function mapping  */
#define GPIO_AF_X32K_OUT_PC7        ((uint8_t)0x07)  /* X32K Alternate Function mapping */


/** 
  * @brief   AF F selection  
  */ 
#define GPIO_AF_AIN0_PC6        ((uint8_t)0x0F)  /* AIN0 Alternate Function mapping  */
#define GPIO_AF_AIN1_PC3        ((uint8_t)0x0F)  /* AIN1 Alternate Function mapping  */
#define GPIO_AF_AIN2_PC4        ((uint8_t)0x0F)  /* AIN2 Alternate Function mapping  */
#define GPIO_AF_AIN3_PD2        ((uint8_t)0x0F)  /* AIN3 Alternate Function mapping  */
#define GPIO_AF_AIN4_PD3        ((uint8_t)0x0F)  /* AIN4 Alternate Function mapping  */
#define GPIO_AF_AIN5_PD5        ((uint8_t)0x0F)  /* AIN5 Alternate Function mapping  */
#define GPIO_AF_AIN6_PD6        ((uint8_t)0x0F)  /* AIN6 Alternate Function mapping  */
#define GPIO_AF_VCIN_PD2        ((uint8_t)0x0F)  /* VCIN Alternate Function mapping  */
#define GPIO_AF_VCIN_PC5        ((uint8_t)0x0F)  /* VCIN Alternate Function mapping  */
#define GPIO_AF_VCIN_PD4        ((uint8_t)0x0F)  /* VCIN Alternate Function mapping  */

#define IS_GPIO_AF(GPIO_AF)     (((GPIO_AF >= 0) &&(GPIO_AF<= 7))||\
                                 (GPIO_AF== 0x0f))

/*Function used to set the GPIO configuration to the default reset state ****/
void GPIO_DeInit(GPIO_TypeDef* GPIOx);
/* Initialization and Configuration functions *********************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Read and Write functions **********************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);

void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);
void GPIO_DBSyncCmd(GPIO_TypeDef* GPIOx,FunctionalState NewState);
void GPIO_DBPinSyncCmd(GPIO_TypeDef* GPIOx,uint32_t DB_Pin,FunctionalState NewState);
void GPIO_DBClkCmd(GPIO_TypeDef* GPIOx,FunctionalState NewState);
void GPIO_SetDBClk(GPIO_TypeDef* GPIOx,uint32_t DBClk);

#ifdef __cplusplus
}
#endif

#endif /*_cx32l003_GPIO_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************(C)COPYRIGHT XMC*********END OF FILE***************************************/

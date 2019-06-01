/**
  ******************************************************************************
  * @file    stm32f0xx.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for STM32F0xx devices.  
  *          
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE 
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f0xx
  * @{
  */
    
#ifndef __CX32l003_H
#define __CX32l003_H

#ifdef __cplusplus
 extern "C" {
#endif 
	 
typedef unsigned      int vu32;
typedef unsigned      short int vu16;
typedef unsigned      char vu8;
  
/**
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application 
   
   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */

#if !defined  (HICR_STABLE_TIMEOUT)
#define HICR_STABLE_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /*HICR_STABLE_TIMEOUT */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup 
   Timeout value 
   */
#if !defined  (HXT_STABLE_TIMEOUT)
#define HXT_STABLE_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /* HSI_STARTUP_TIMEOUT */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup 
   Timeout value 
   */
#if !defined  (LICR_STABLE_TIMEOUT)
#define LICR_STABLE_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */*/
#endif /* HSI_VALUE */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup 
   Timeout value 
   */
#if !defined  (LXT_STABLE_TIMEOUT)
#define LXT_STABLE_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /* HSI14_VALUE */


/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup 
   Timeout value 
   */
#if !defined  (SYSTEMTICKTIMER_SKEW_TIMEOUT)
#define SYSTEMTICKTIMER_SKEW_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /* HSI14_VALUE */


/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup 
   Timeout value 
   */
#if !defined  (Fpclk) 
#define Fpclk  ((uint32_t)24000000)    /*!< Value of the External Low Speed oscillator in Hz */
//#define Fpclk  ((uint32_t)16000000) 
#endif /* LSE_VALUE */
 
/**
 * @brief STM32F0xx Standard Peripheral Library version number V1.4.0
   */
#define __CX32S003_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __CX32S003_STDPERIPH_VERSION_SUB1   (0x05) /*!< [23:16] sub1 version */
#define __CX32S003_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __CX32S003_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __CX32S003_STDPERIPH_VERSION        ((__CX32S003_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__CX32S003_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__CX32S003_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__CX32S003_STDPERIPH_VERSION_RC))
																						 
/**
 * @brief STM32F0xx Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */
#define __CM0_REV                 0 /*!< Core Revision r0p0                            */
#define __MPU_PRESENT             0 /*!< STM32F0xx do not provide MPU                  */
#define __NVIC_PRIO_BITS          2 /*!< STM32F0xx uses 2 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0 /*!< Set to 1 if different SysTick Config is used  */

/*!< Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ******************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                        */
  SVC_IRQn                    = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                          */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                          */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                      */

  GPIOA_IRQn                  = 0,
  GPIOB_IRQn                  = 1,
  GPIOC_IRQn                  = 2,
  GPIOD_IRQn                  = 3,
  UART0_IRQn                  = 6,
  UART1_IRQn                  = 7,
	LPUART_IRQn                 = 8,
  SPI0COMB_IRQn               = 10,
  SPI_DUMMYCOMB_IRQn          = 11,
  I2C0_IRQn                   = 12,
  I2C_DUMMY_IRQn              = 13,
  TIMER10_IRQn                 = 14,
  TIMER11_IRQn                 = 15,
	LPTIMER_IRQn                = 16,
  PWM_IRQn                    = 18,
	ADVTIM_IRQn                = 19,	
  PCA_IRQn                    = 21,
  WWDT_IRQn                   = 22,
  IWDT_IRQn                   = 23,
  ADC0_IRQn                   = 24,
	LVD_IRQn                    = 25,
	VC_IRQn                     = 26,
	AWK_IRQn                    = 28,
	ONEWIRE_IRQn                = 29,
  RTC_MATCH0_IRQn             = 30,
  CLKTRIM_IRQn                = 31                            

}IRQn_Type;

/**
  * @}
  */

#include <stdint.h>
#include "core_cm0.h"
#include "system_cx32l003.h"


/** @addtogroup Exported_types
  * @{
  */  
/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2016 Brite Semiconductor Co., Ltd. All rights reserved.                */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/** @addtogroup Peripheral_registers_structures
  * @{
  */  

/**
  * @}addtogroup SYSCON_TypeDef
  */
typedef struct
{
	__IO uint32_t SYSCTRLCFG0;
	__IO uint32_t PORTINTMODE;
	__IO uint32_t PORTCTRL0;
	__IO uint32_t PCA_CAPMUX;
	__IO uint32_t TIM1_CHINMUX;
	__IO uint32_t TIM2_CHINMUX;
	__IO uint32_t LPUARTCON;
	__IO uint32_t   RESERVED0;       /*!< Reserved, */
	__IO uint32_t   RESERVED1;       /*!< Reserved, */
	__IO uint32_t   RESERVED2;       /*!< Reserved, */
	__IO uint32_t   RESERVED3;       /*!< Reserved, */
	__IO uint32_t   RESERVED4;       /*!< Reserved, */
	__IO uint32_t   RESERVED5;       /*!< Reserved, */
	__IO uint32_t   RESERVED6;       /*!< Reserved, */
	__IO uint32_t   RESERVED7;       /*!< Reserved, */
	__IO uint32_t   RESERVED8;       /*!< Reserved, */
	__IO uint32_t   RESERVED9;       /*!< Reserved, */
	__IO uint32_t   RESERVED10;       /*!< Reserved, */
	__IO uint32_t   RESERVED11;       /*!< Reserved, */
	__IO uint32_t   RESERVED12;       /*!< Reserved, */
	__IO uint32_t SYSCON_UNLOCK;
}SYSCON_TypeDef;



/**
  * @}addtogroup LPTIMER_TypeDef
  */
typedef struct
{
	__IO uint32_t CNT;
	__IO uint32_t CR;
	__IO uint32_t LOAD;
	__IO uint32_t IR;
	__IO uint32_t ICLR;	
	__IO uint32_t BGLOAD;
}LPTIMER_TypeDef;


/**
  * @}addtogroup LVD_TypeDef
  */
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t IR;
	
}LVD_TypeDef;


/**
  * @}addtogroup VC_TypeDef
  */
typedef struct
{
	__IO uint32_t PCR;
	__IO uint32_t CR;
	__IO uint32_t OUTCFG;
	__IO uint32_t IR;
}VC_TypeDef;

/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
  
typedef struct
{
	__IO uint32_t SCON; /*!<UART¿ØÖÆ¼Ä´æÆ÷*/
	__IO uint32_t SBUF; /*!<UARTÊý¾Ý¼Ä´æÆ÷*/
	__IO uint32_t SADDR; /*!<UARTµØÖ·¼Ä´æÆ÷*/
	__IO uint32_t SADEN; /*!<UARTµØÖ·ÑÚÂë¼Ä´æÆ÷*/
	__IO uint32_t ISR; /*!<UART±êÖ¾¼Ä´æÆ÷*/
	__IO uint32_t ICR; /*!<UART±êÖ¾Çå³ý¼Ä´æÆ÷*/
	__IO uint32_t BRG;/*!<UART²¨ÌØÂÊ¿ØÖÆ¼Ä´æÆ÷*/
	__IO uint32_t IRDACR;/*!<IrDA¿ØÖÆ¼Ä´æÆ÷*/
}UART_TypeDef;


/** 
  * @brief LPUART_TypeDef
  */
  
typedef struct
{
	__IO uint32_t SBUF; /*!<LPUARTÊý¾Ý¼Ä´æÆ÷*/
	__IO uint32_t SCON; /*!<LPUART¿ØÖÆ¼Ä´æÆ÷*/
	__IO uint32_t SADDR; /*!<LPUARTµØÖ·¼Ä´æÆ÷*/
	__IO uint32_t SADEN; /*!<LPUARTµØÖ·ÑÚÂë¼Ä´æÆ÷*/
	__IO uint32_t ISR; /*!<LPUART±êÖ¾¼Ä´æÆ÷*/
	__IO uint32_t ICR; /*!<LPUART±êÖ¾Çå³ý¼Ä´æÆ÷*/
	__IO uint32_t BRG;/*!<LPUART²¨ÌØÂÊ¿ØÖÆ¼Ä´æÆ÷*/
}LPUART_TypeDef;


/** 
  * @brief I2C registers  structures
  */
typedef struct
{
  __IO uint16_t CR;    /*!< I2C Control register , Address offset: 0x00 */ 
  uint16_t  RESERVED0;
  __IO uint16_t DATA;  /*!< I2C Data register , Address offset: 0x04 */ 
  uint16_t  RESERVED2;
  __IO uint16_t ADDR;  /*!< I2C Address register , Address offset: 0x08 */ 
  uint16_t  RESERVED3;
  __IO uint16_t STAT; /*!< I2C Status register , Address offset: 0x0C */
  uint16_t  RESERVED4;
  __IO uint16_t TMRUN; /*!< I2C Baud rate counter enabled register , Address offset: 0x10 */
  uint16_t  RESERVED5;
  __IO uint16_t TM;    /*!< I2C Baud rate counter configuration register , Address offset: 0x14 */
  uint16_t  RESERVED6;
} I2C_TypeDef;
/** 
  * @brief Window WATCHDOG
  */
typedef struct
{
  __IO uint32_t RLDCNT;   /*!< WWDG Control register,       Address offset: 0x00 */
  __IO uint32_t CTL;  /*!< WWDG Configuration register, Address offset: 0x04 */
  __IO uint32_t INTEN;   /*!< WWDG Status register,        Address offset: 0x08 */
	__IO uint32_t STATUS;
	__IO uint32_t ICLR;
	__IO uint32_t CNT;
} WWDG_TypeDef;

/** 
  * @brief Window IWATCHDOG
  */
typedef struct
{
	__IO uint32_t COMMAND;   /*!< IWDG Control register,       Address offset: 0x00 */
	__IO uint32_t CFG;  /*!< IWDG Configuration register, Address offset: 0x04 */
	__IO uint32_t RLOAD;   /*!< IWDG Rload counter register,        Address offset: 0x08 */
	__IO uint32_t CNTVAL;   /*!< IWDG count value register,        Address offset: 0x08 */
	__IO uint32_t INTS;   /*!< IWDG TI Status register,        Address offset: 0x08 */
	__IO uint32_t INTCLR;   /*!< IWDG TI CLear Status register,        Address offset: 0x08 */
	__IO uint32_t LOCK;   /*!< IWDG resigter protect  register,        Address offset: 0x08 */
} IWDG_TypeDef;
/**
  * @} GPIO_TypeDef
  */
typedef struct
{
	__IO uint32_t DIR; 
	__IO uint32_t OTYP;
	__IO uint32_t DO;  
	__IO uint32_t DI;  
	__IO uint32_t IEN; 
	__IO uint32_t RIS; 
	__IO uint32_t MIS;
	__IO uint32_t ICLR;
	__IO uint32_t ITYP;
	__IO uint32_t IVAL;
	__IO uint32_t IANY;
	__IO uint32_t DOSE;
	__IO uint32_t DOCL;
	__IO uint32_t DIDB;
	__IO uint32_t DBCLK;
	__IO uint32_t PUPD;
	__IO uint32_t SR;  
	__IO uint32_t DR;  
	__IO uint32_t AFR; 
}GPIO_TypeDef;
/**
  * @} TMER RIGSTER
  */
typedef struct
{
	__IO uint32_t CON;
	__IO uint32_t LOAD;
	__IO uint32_t VAL;
	__IO uint32_t RIS;
	__IO uint32_t MIS;
	__IO uint32_t ICLR;
	__IO uint32_t BGLOAD;
} TIM_TypeDef;


/** 
* @brief ADVTIM1: advanced timer1
  */

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SMCR;
  __IO uint32_t DIER;
  __IO uint32_t SR;
  __IO uint32_t EGR;
  __IO uint32_t CCMR1;
  __IO uint32_t CCMR2;
  __IO uint32_t CCER;
  __IO uint32_t CNT;
  __IO uint32_t PSC;
  __IO uint32_t ARR;
  __IO uint32_t RCR;
  __IO uint32_t CCR1;
  __IO uint32_t CCR2;
  __IO uint32_t CCR3;
  __IO uint32_t CCR4;
  __IO uint32_t BDTR;
  __IO uint32_t DCR;
  __IO uint32_t DMAR;
} ADVTIM_TypeDef;	

/**
  * @} SPI_TypeDef
  */
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t SSN;
	__IO uint32_t STAT;
	__IO uint32_t DATA;
}SPI_TypeDef;
/**
  * @} TMER RIGSTER
  */
typedef struct
{
	__IO uint32_t  CCON  ;     
	__IO uint32_t  CMOD  ;     
	__IO uint32_t  CNT   ;     
	__IO uint32_t  ICLR  ;     
	__IO uint32_t  CCAPM0 ;    
	__IO uint32_t  CCAPM1 ;    
	__IO uint32_t  CCAPM2 ;    
	__IO uint32_t  CCAPM3 ;    
	__IO uint32_t  CCAPM4 ;    
	__IO uint32_t  RESERVED0 ; 
	__IO uint32_t  RESERVED1 ; 
	__IO uint32_t  RESERVED2	; 
	__IO uint32_t  CCAP0L ;    
	__IO uint32_t  CCAP0H ;    
	__IO uint32_t  CCAP1L ;    
	__IO uint32_t  CCAP1H ;    
	__IO uint32_t  CCAP2L ;    
	__IO uint32_t  CCAP2H ;    
	__IO uint32_t  CCAP3L ;    
	__IO uint32_t  CCAP3H ;    
	__IO uint32_t  CCAP4L ;    
	__IO uint32_t  CCAP4H ;    
	__IO uint32_t  CCAPO  ;    
	__IO uint32_t  POCON  ;    
	__IO uint32_t  CCAP0  ;    
	__IO uint32_t  CCAP1  ;    
	__IO uint32_t  CCAP2  ;    
	__IO uint32_t  CCAP3  ;    
	__IO uint32_t  CCAP4  ;    
}PCA_TypeDef;
/**
  * @} AWK_TypeDef
  */
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t RLDVAL;
	__IO uint32_t STATUS;
	__IO uint32_t INTCLR;
}AWK_TypeDef;

/**
  * @} CLKTRIM_TypeDef
  */
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t REFCON;
	__IO uint32_t REFCNT;
	__IO uint32_t CALCNT;
	__IO uint32_t IFR;
	__IO uint32_t ICLR;
	__IO uint32_t CALCON;
}CLKTRIM_TypeDef;
/**
  * @} OWIRE_TypeDef
  */
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t NFCR;
	__IO uint32_t RSTCNT;
	__IO uint32_t PRESCNT;
	__IO uint32_t BITRATECNT;
	__IO uint32_t DRVCNT;
	__IO uint32_t RDSMPCNT;
	__IO uint32_t RECCNT;
	__IO uint32_t DATA;
	__IO uint32_t COMMAND;
	__IO uint32_t INTEN;
	__IO uint32_t STATUS;
	__IO uint32_t INTCLR;	
}OWIRE_TypeDef;
/**
  * @} RTC_TypeDef
  */
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t CLKCR;
	__IO uint32_t TIME;
	__IO uint32_t DATE;
	__IO uint32_t ALTIME;
	__IO uint32_t ALDATE;
	__IO uint32_t ALPR;
	__IO uint32_t CKTR;
	__IO uint32_t ISR;
	__IO uint32_t INTCLR;
	__IO uint32_t WPR;
} RTC_TypeDef;  
/**
  * @} RCC_TypeDef
  */
typedef struct
{
	__IO uint32_t AHBCLKDIV;
	__IO uint32_t APBCLKDIV;
	__IO uint32_t AHBCLKEN;
	__IO uint32_t APBCLKEN;
	__IO uint32_t MCO;
	__IO uint32_t RESERVED0;
	__IO uint32_t RSTCON;
	__IO uint32_t RSTSTAT;
	__IO uint32_t CLKCON;
	__IO uint32_t CLKSEL;
	__IO uint32_t HIRCCR;
	__IO uint32_t HXTCR;
	__IO uint32_t LIRCCR;
	__IO uint32_t LXTCR;
	__IO uint32_t IRQLATENCY;
	__IO uint32_t STCALIB;
	__IO uint32_t IOMUX;
	__IO uint32_t RERIRST;
	__IO uint32_t RTCRST;	
	__IO uint32_t RESERVED1;
	__IO uint32_t RESERVED2;
	__IO uint32_t RESERVED3;
	__IO uint32_t RESERVED4;
	__IO uint32_t RESERVED5;
	__IO uint32_t REGLOCK;
	
} RCC_TypeDef;


/**
  * @} DEBUG_TypeDef
  */
typedef struct
{
	__IO uint32_t APBFZ;
} DEBUG_TypeDef;


/**
  * @} BEEPER_TypeDef
  */
typedef struct
{
	__IO uint32_t BEEP_CSR;

} BEEPER_TypeDef;




/**
  * @} ADC_TypeDef
  */
typedef struct
{
	__IO uint32_t CR0;
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t RESULT0;
	__IO uint32_t RESULT1;
	__IO uint32_t RESULT2;
	__IO uint32_t RESULT3;
	__IO uint32_t RESULT4;
	__IO uint32_t RESULT5;
	__IO uint32_t RESULT6;
	__IO uint32_t RESULT7;
	__IO uint32_t RESULT;
	__IO uint32_t RESULTACC;
	__IO uint32_t HT;
	__IO uint32_t LT;
	__IO uint32_t IFR;
	__IO uint32_t INTC;
	__IO uint32_t IEN;
	__IO uint32_t ICLR;	
	__IO uint32_t RIS;
	__IO uint32_t MIS;
} ADC_TypeDef;

/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           BASE ADDRESS DEFINE, DEFINE ALL MODE.....                                               */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#define PERIPH_BASE     ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */
#define	RTC_BASE		    (PERIPH_BASE + 0x00003000)
#define SYSCON_BASE     (PERIPH_BASE + 0x00001C00)
#define	WWDT_BASE		    (PERIPH_BASE + 0x00002000)
#define	IWDT_BASE		    (PERIPH_BASE + 0x00002400)
#define	UART0_BASE		  (PERIPH_BASE + 0x00000000)
#define	UART1_BASE		  (PERIPH_BASE + 0x00000400)
#define SPI0_BASE       (PERIPH_BASE + 0x00000800)
#define	I2C0_BASE		    (PERIPH_BASE + 0x00000C00)
#define PWM_BASE		    (PERIPH_BASE + 0x00001000)
#define PCA_BASE        (PERIPH_BASE + 0x00001400)
#define TMR10_BASE	    (PERIPH_BASE + 0x00001800)
#define TMR11_BASE	    (PERIPH_BASE + 0x00001900)
#define ADVTIM1_BASE		(PERIPH_BASE + 0x00001000)	//Advanced timer (pwm function)	
#define ADVTIM2_BASE		(PERIPH_BASE + 0x00003C00)	//Advanced timer	
#define AWK_BASE	      (PERIPH_BASE + 0x00002800)
#define CLKTRIM_BASE    (PERIPH_BASE + 0x00003400)
#define PWR_BASE        (PERIPH_BASE + 0x00007000)
#define ACMP_BASE		    (PERIPH_BASE + 0x00007C00)
#define	AFIO_BASE		    (PERIPH_BASE + 0x00010000)
#define	GPIOA_BASE		  (PERIPH_BASE + 0x00021000)
#define	GPIOB_BASE		  (PERIPH_BASE + 0x00021400)
#define	GPIOC_BASE		  (PERIPH_BASE + 0x00021800)
#define	GPIOD_BASE		  (PERIPH_BASE + 0x00021C00)
#define QSPI_BASE		    (PERIPH_BASE + 0x00014400)
#define OWIRE_BASE		  (PERIPH_BASE + 0x00003800)
#define CRC_BASE        (PERIPH_BASE + 0x00020800) 
#define RCC_BASE        (PERIPH_BASE + 0x00020000)
#define BEEPER_BASE     (PERIPH_BASE + 0x00004800)
#define LPTIMER_BASE    (PERIPH_BASE + 0x00004400)
#define LPUART_BASE     (PERIPH_BASE + 0x00005000)
#define LVD_BASE        (PERIPH_BASE + 0x00004000)
#define VC_BASE         (PERIPH_BASE + 0x00004080)
#define DEBUG_BASE      (PERIPH_BASE + 0x00004C00)
#define ADC_BASE        (PERIPH_BASE + 0x00002C00)






/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           BASE ADDRESS DEFINE, DEFINE ALL MODE......                                           */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#define I2C                 ((I2C_TypeDef *)I2C0_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define UART0               ((UART_TypeDef *) UART0_BASE)
#define UART1               ((UART_TypeDef *) UART1_BASE)
#define TMER0               ((TIM_TypeDef *) TMR0_BASE)
#define TMER1               ((TIM_TypeDef *) TMR1_BASE)
#define SPI                 ((SPI_TypeDef *)SPI0_BASE)
#define ADVTIM1							((ADVTIM_TypeDef *) ADVTIM1_BASE)	
#define ADVTIM2							((ADVTIM_TypeDef *) ADVTIM2_BASE)
#define IWDG                ((IWDG_TypeDef *)IWDT_BASE)
#define WWDG                ((WWDG_TypeDef *)WWDT_BASE)
#define PCA                 ((PCA_TypeDef *)PCA_BASE)
#define AWK                 ((AWK_TypeDef *)AWK_BASE)
#define CLKTRIM             ((CLKTRIM_TypeDef *)CLKTRIM_BASE)
#define OWIRE               ((OWIRE_TypeDef *)OWIRE_BASE)
#define RTC                 ((RTC_TypeDef *)RTC_BASE) 
#define RCC                 ((RCC_TypeDef *)RCC_BASE) 
#define TIM10               ((TIM_TypeDef *)TMR10_BASE) 
#define TIM11               ((TIM_TypeDef *)TMR11_BASE) 
#define BEEPER              ((BEEPER_TypeDef *)BEEPER_BASE) 
#define SYSCTRL             ((SYSCON_TypeDef *)SYSCON_BASE) 
#define LPTIMER             ((LPTIMER_TypeDef *)LPTIMER_BASE) 
#define LVD                 ((LVD_TypeDef *)LVD_BASE) 
#define VC                  ((VC_TypeDef *)VC_BASE) 
#define LPUART              ((LPUART_TypeDef *)LPUART_BASE) 
#define DEBUG               ((DEBUG_TypeDef *)DEBUG_BASE) 
#define ADC                 ((ADC_TypeDef *)ADC_BASE) 









/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*          RESIGTER ADDRESS DEFINE, DEFINE ALL MODE......                                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#define CRC_RESULT        (*(uint32_t *)(CRC_BASE+0x04))
#define CRC_DATA_8        (*(uint8_t  *)(CRC_BASE+0x80))
#define CRC_DATA_16       (*(uint16_t *)(CRC_BASE+0x80))
#define CRC_DATA_32       (*(uint32_t *)(CRC_BASE+0x80))


#define	REMAP            (*((vu32*)(RCC_BASE + 0x208)))
#define	HIRCSTABC        (*((vu32*)(RCC_BASE + 0x390)))

/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN                         ((uint16_t)0x0001)            /*!< Counter enable */
#define  TIM_CR1_UDIS                        ((uint16_t)0x0002)            /*!< Update disable */
#define  TIM_CR1_URS                         ((uint16_t)0x0004)            /*!< Update request source */
#define  TIM_CR1_OPM                         ((uint16_t)0x0008)            /*!< One pulse mode */
#define  TIM_CR1_DIR                         ((uint16_t)0x0010)            /*!< Direction */

#define  TIM_CR1_CMS                         ((uint16_t)0x0060)            /*!< CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0                       ((uint16_t)0x0020)            /*!< Bit 0 */
#define  TIM_CR1_CMS_1                       ((uint16_t)0x0040)            /*!< Bit 1 */

#define  TIM_CR1_ARPE                        ((uint16_t)0x0080)            /*!< Auto-reload preload enable */

#define  TIM_CR1_CKD                         ((uint16_t)0x0300)            /*!< CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0                       ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_CR1_CKD_1                       ((uint16_t)0x0200)            /*!< Bit 1 */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define  TIM_CR2_CCPC                        ((uint16_t)0x0001)            /*!< Capture/Compare Preloaded Control */
#define  TIM_CR2_CCUS                        ((uint16_t)0x0004)            /*!< Capture/Compare Control Update Selection */
#define  TIM_CR2_CCDS                        ((uint16_t)0x0008)            /*!< Capture/Compare DMA Selection */

#define  TIM_CR2_MMS                         ((uint16_t)0x0070)            /*!< MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS_0                       ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CR2_MMS_1                       ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CR2_MMS_2                       ((uint16_t)0x0040)            /*!< Bit 2 */

#define  TIM_CR2_TI1S                        ((uint16_t)0x0080)            /*!< TI1 Selection */
#define  TIM_CR2_OIS1                        ((uint16_t)0x0100)            /*!< Output Idle state 1 (OC1 output) */
#define  TIM_CR2_OIS1N                       ((uint16_t)0x0200)            /*!< Output Idle state 1 (OC1N output) */
#define  TIM_CR2_OIS2                        ((uint16_t)0x0400)            /*!< Output Idle state 2 (OC2 output) */
#define  TIM_CR2_OIS2N                       ((uint16_t)0x0800)            /*!< Output Idle state 2 (OC2N output) */
#define  TIM_CR2_OIS3                        ((uint16_t)0x1000)            /*!< Output Idle state 3 (OC3 output) */
#define  TIM_CR2_OIS3N                       ((uint16_t)0x2000)            /*!< Output Idle state 3 (OC3N output) */
#define  TIM_CR2_OIS4                        ((uint16_t)0x4000)            /*!< Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define  TIM_SMCR_SMS                        ((uint16_t)0x0007)            /*!< SMS[2:0] bits (Slave mode selection) */
#define  TIM_SMCR_SMS_0                      ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_SMCR_SMS_1                      ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TIM_SMCR_SMS_2                      ((uint16_t)0x0004)            /*!< Bit 2 */

#define  TIM_SMCR_TS                         ((uint16_t)0x0070)            /*!< TS[2:0] bits (Trigger selection) */
#define  TIM_SMCR_TS_0                       ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_SMCR_TS_1                       ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_SMCR_TS_2                       ((uint16_t)0x0040)            /*!< Bit 2 */

#define  TIM_SMCR_MSM                        ((uint16_t)0x0080)            /*!< Master/slave mode */

#define  TIM_SMCR_ETF                        ((uint16_t)0x0F00)            /*!< ETF[3:0] bits (External trigger filter) */
#define  TIM_SMCR_ETF_0                      ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_SMCR_ETF_1                      ((uint16_t)0x0200)            /*!< Bit 1 */
#define  TIM_SMCR_ETF_2                      ((uint16_t)0x0400)            /*!< Bit 2 */
#define  TIM_SMCR_ETF_3                      ((uint16_t)0x0800)            /*!< Bit 3 */

#define  TIM_SMCR_ETPS                       ((uint16_t)0x3000)            /*!< ETPS[1:0] bits (External trigger prescaler) */
#define  TIM_SMCR_ETPS_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_SMCR_ETPS_1                     ((uint16_t)0x2000)            /*!< Bit 1 */

#define  TIM_SMCR_ECE                        ((uint16_t)0x4000)            /*!< External clock enable */
#define  TIM_SMCR_ETP                        ((uint16_t)0x8000)            /*!< External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define  TIM_DIER_UIE                        ((uint16_t)0x0001)            /*!< Update interrupt enable */
#define  TIM_DIER_CC1IE                      ((uint16_t)0x0002)            /*!< Capture/Compare 1 interrupt enable */
#define  TIM_DIER_CC2IE                      ((uint16_t)0x0004)            /*!< Capture/Compare 2 interrupt enable */
#define  TIM_DIER_CC3IE                      ((uint16_t)0x0008)            /*!< Capture/Compare 3 interrupt enable */
#define  TIM_DIER_CC4IE                      ((uint16_t)0x0010)            /*!< Capture/Compare 4 interrupt enable */
#define  TIM_DIER_COMIE                      ((uint16_t)0x0020)            /*!< COM interrupt enable */
#define  TIM_DIER_TIE                        ((uint16_t)0x0040)            /*!< Trigger interrupt enable */
#define  TIM_DIER_BIE                        ((uint16_t)0x0080)            /*!< Break interrupt enable */
#define  TIM_DIER_UDE                        ((uint16_t)0x0100)            /*!< Update DMA request enable */
#define  TIM_DIER_CC1DE                      ((uint16_t)0x0200)            /*!< Capture/Compare 1 DMA request enable */
#define  TIM_DIER_CC2DE                      ((uint16_t)0x0400)            /*!< Capture/Compare 2 DMA request enable */
#define  TIM_DIER_CC3DE                      ((uint16_t)0x0800)            /*!< Capture/Compare 3 DMA request enable */
#define  TIM_DIER_CC4DE                      ((uint16_t)0x1000)            /*!< Capture/Compare 4 DMA request enable */
#define  TIM_DIER_COMDE                      ((uint16_t)0x2000)            /*!< COM DMA request enable */
#define  TIM_DIER_TDE                        ((uint16_t)0x4000)            /*!< Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define  TIM_SR_UIF                          ((uint16_t)0x0001)            /*!< Update interrupt Flag */
#define  TIM_SR_CC1IF                        ((uint16_t)0x0002)            /*!< Capture/Compare 1 interrupt Flag */
#define  TIM_SR_CC2IF                        ((uint16_t)0x0004)            /*!< Capture/Compare 2 interrupt Flag */
#define  TIM_SR_CC3IF                        ((uint16_t)0x0008)            /*!< Capture/Compare 3 interrupt Flag */
#define  TIM_SR_CC4IF                        ((uint16_t)0x0010)            /*!< Capture/Compare 4 interrupt Flag */
#define  TIM_SR_COMIF                        ((uint16_t)0x0020)            /*!< COM interrupt Flag */
#define  TIM_SR_TIF                          ((uint16_t)0x0040)            /*!< Trigger interrupt Flag */
#define  TIM_SR_BIF                          ((uint16_t)0x0080)            /*!< Break interrupt Flag */
#define  TIM_SR_CC1OF                        ((uint16_t)0x0200)            /*!< Capture/Compare 1 Overcapture Flag */
#define  TIM_SR_CC2OF                        ((uint16_t)0x0400)            /*!< Capture/Compare 2 Overcapture Flag */
#define  TIM_SR_CC3OF                        ((uint16_t)0x0800)            /*!< Capture/Compare 3 Overcapture Flag */
#define  TIM_SR_CC4OF                        ((uint16_t)0x1000)            /*!< Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define  TIM_EGR_UG                          ((uint8_t)0x01)               /*!< Update Generation */
#define  TIM_EGR_CC1G                        ((uint8_t)0x02)               /*!< Capture/Compare 1 Generation */
#define  TIM_EGR_CC2G                        ((uint8_t)0x04)               /*!< Capture/Compare 2 Generation */
#define  TIM_EGR_CC3G                        ((uint8_t)0x08)               /*!< Capture/Compare 3 Generation */
#define  TIM_EGR_CC4G                        ((uint8_t)0x10)               /*!< Capture/Compare 4 Generation */
#define  TIM_EGR_COMG                        ((uint8_t)0x20)               /*!< Capture/Compare Control Update Generation */
#define  TIM_EGR_TG                          ((uint8_t)0x40)               /*!< Trigger Generation */
#define  TIM_EGR_BG                          ((uint8_t)0x80)               /*!< Break Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define  TIM_CCMR1_CC1S                      ((uint16_t)0x0003)            /*!< CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TIM_CCMR1_CC1S_0                    ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_CCMR1_CC1S_1                    ((uint16_t)0x0002)            /*!< Bit 1 */

#define  TIM_CCMR1_OC1FE                     ((uint16_t)0x0004)            /*!< Output Compare 1 Fast enable */
#define  TIM_CCMR1_OC1PE                     ((uint16_t)0x0008)            /*!< Output Compare 1 Preload enable */

#define  TIM_CCMR1_OC1M                      ((uint16_t)0x0070)            /*!< OC1M[2:0] bits (Output Compare 1 Mode) */
#define  TIM_CCMR1_OC1M_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CCMR1_OC1M_1                    ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CCMR1_OC1M_2                    ((uint16_t)0x0040)            /*!< Bit 2 */

#define  TIM_CCMR1_OC1CE                     ((uint16_t)0x0080)            /*!< Output Compare 1Clear Enable */

#define  TIM_CCMR1_CC2S                      ((uint16_t)0x0300)            /*!< CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TIM_CCMR1_CC2S_0                    ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_CCMR1_CC2S_1                    ((uint16_t)0x0200)            /*!< Bit 1 */

#define  TIM_CCMR1_OC2FE                     ((uint16_t)0x0400)            /*!< Output Compare 2 Fast enable */
#define  TIM_CCMR1_OC2PE                     ((uint16_t)0x0800)            /*!< Output Compare 2 Preload enable */

#define  TIM_CCMR1_OC2M                      ((uint16_t)0x7000)            /*!< OC2M[2:0] bits (Output Compare 2 Mode) */
#define  TIM_CCMR1_OC2M_0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_CCMR1_OC2M_1                    ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_CCMR1_OC2M_2                    ((uint16_t)0x4000)            /*!< Bit 2 */

#define  TIM_CCMR1_OC2CE                     ((uint16_t)0x8000)            /*!< Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR1_IC1PSC                    ((uint16_t)0x000C)            /*!< IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TIM_CCMR1_IC1PSC_0                  ((uint16_t)0x0004)            /*!< Bit 0 */
#define  TIM_CCMR1_IC1PSC_1                  ((uint16_t)0x0008)            /*!< Bit 1 */

#define  TIM_CCMR1_IC1F                      ((uint16_t)0x00F0)            /*!< IC1F[3:0] bits (Input Capture 1 Filter) */
#define  TIM_CCMR1_IC1F_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CCMR1_IC1F_1                    ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CCMR1_IC1F_2                    ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TIM_CCMR1_IC1F_3                    ((uint16_t)0x0080)            /*!< Bit 3 */

#define  TIM_CCMR1_IC2PSC                    ((uint16_t)0x0C00)            /*!< IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  TIM_CCMR1_IC2PSC_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  TIM_CCMR1_IC2PSC_1                  ((uint16_t)0x0800)            /*!< Bit 1 */

#define  TIM_CCMR1_IC2F                      ((uint16_t)0xF000)            /*!< IC2F[3:0] bits (Input Capture 2 Filter) */
#define  TIM_CCMR1_IC2F_0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_CCMR1_IC2F_1                    ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_CCMR1_IC2F_2                    ((uint16_t)0x4000)            /*!< Bit 2 */
#define  TIM_CCMR1_IC2F_3                    ((uint16_t)0x8000)            /*!< Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define  TIM_CCMR2_CC3S                      ((uint16_t)0x0003)            /*!< CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  TIM_CCMR2_CC3S_0                    ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_CCMR2_CC3S_1                    ((uint16_t)0x0002)            /*!< Bit 1 */

#define  TIM_CCMR2_OC3FE                     ((uint16_t)0x0004)            /*!< Output Compare 3 Fast enable */
#define  TIM_CCMR2_OC3PE                     ((uint16_t)0x0008)            /*!< Output Compare 3 Preload enable */

#define  TIM_CCMR2_OC3M                      ((uint16_t)0x0070)            /*!< OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TIM_CCMR2_OC3M_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CCMR2_OC3M_1                    ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CCMR2_OC3M_2                    ((uint16_t)0x0040)            /*!< Bit 2 */

#define  TIM_CCMR2_OC3CE                     ((uint16_t)0x0080)            /*!< Output Compare 3 Clear Enable */

#define  TIM_CCMR2_CC4S                      ((uint16_t)0x0300)            /*!< CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TIM_CCMR2_CC4S_0                    ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_CCMR2_CC4S_1                    ((uint16_t)0x0200)            /*!< Bit 1 */

#define  TIM_CCMR2_OC4FE                     ((uint16_t)0x0400)            /*!< Output Compare 4 Fast enable */
#define  TIM_CCMR2_OC4PE                     ((uint16_t)0x0800)            /*!< Output Compare 4 Preload enable */

#define  TIM_CCMR2_OC4M                      ((uint16_t)0x7000)            /*!< OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR2_OC4M_0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_CCMR2_OC4M_1                    ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_CCMR2_OC4M_2                    ((uint16_t)0x4000)            /*!< Bit 2 */

#define  TIM_CCMR2_OC4CE                     ((uint16_t)0x8000)            /*!< Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR2_IC3PSC                    ((uint16_t)0x000C)            /*!< IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TIM_CCMR2_IC3PSC_0                  ((uint16_t)0x0004)            /*!< Bit 0 */
#define  TIM_CCMR2_IC3PSC_1                  ((uint16_t)0x0008)            /*!< Bit 1 */

#define  TIM_CCMR2_IC3F                      ((uint16_t)0x00F0)            /*!< IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TIM_CCMR2_IC3F_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CCMR2_IC3F_1                    ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CCMR2_IC3F_2                    ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TIM_CCMR2_IC3F_3                    ((uint16_t)0x0080)            /*!< Bit 3 */

#define  TIM_CCMR2_IC4PSC                    ((uint16_t)0x0C00)            /*!< IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TIM_CCMR2_IC4PSC_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  TIM_CCMR2_IC4PSC_1                  ((uint16_t)0x0800)            /*!< Bit 1 */

#define  TIM_CCMR2_IC4F                      ((uint16_t)0xF000)            /*!< IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TIM_CCMR2_IC4F_0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_CCMR2_IC4F_1                    ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_CCMR2_IC4F_2                    ((uint16_t)0x4000)            /*!< Bit 2 */
#define  TIM_CCMR2_IC4F_3                    ((uint16_t)0x8000)            /*!< Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E                       ((uint16_t)0x0001)            /*!< Capture/Compare 1 output enable */
#define  TIM_CCER_CC1P                       ((uint16_t)0x0002)            /*!< Capture/Compare 1 output Polarity */
#define  TIM_CCER_CC1NE                      ((uint16_t)0x0004)            /*!< Capture/Compare 1 Complementary output enable */
#define  TIM_CCER_CC1NP                      ((uint16_t)0x0008)            /*!< Capture/Compare 1 Complementary output Polarity */
#define  TIM_CCER_CC2E                       ((uint16_t)0x0010)            /*!< Capture/Compare 2 output enable */
#define  TIM_CCER_CC2P                       ((uint16_t)0x0020)            /*!< Capture/Compare 2 output Polarity */
#define  TIM_CCER_CC2NE                      ((uint16_t)0x0040)            /*!< Capture/Compare 2 Complementary output enable */
#define  TIM_CCER_CC2NP                      ((uint16_t)0x0080)            /*!< Capture/Compare 2 Complementary output Polarity */
#define  TIM_CCER_CC3E                       ((uint16_t)0x0100)            /*!< Capture/Compare 3 output enable */
#define  TIM_CCER_CC3P                       ((uint16_t)0x0200)            /*!< Capture/Compare 3 output Polarity */
#define  TIM_CCER_CC3NE                      ((uint16_t)0x0400)            /*!< Capture/Compare 3 Complementary output enable */
#define  TIM_CCER_CC3NP                      ((uint16_t)0x0800)            /*!< Capture/Compare 3 Complementary output Polarity */
#define  TIM_CCER_CC4E                       ((uint16_t)0x1000)            /*!< Capture/Compare 4 output enable */
#define  TIM_CCER_CC4P                       ((uint16_t)0x2000)            /*!< Capture/Compare 4 output Polarity */
#define  TIM_CCER_CC4NP                      ((uint16_t)0x8000)            /*!< Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define  TIM_CNT_CNT                         ((uint16_t)0xFFFF)            /*!< Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define  TIM_PSC_PSC                         ((uint16_t)0xFFFF)            /*!< Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define  TIM_ARR_ARR                         ((uint16_t)0xFFFF)            /*!< actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define  TIM_RCR_REP                         ((uint8_t)0xFF)               /*!< Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define  TIM_CCR1_CCR1                       ((uint16_t)0xFFFF)            /*!< Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define  TIM_CCR2_CCR2                       ((uint16_t)0xFFFF)            /*!< Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define  TIM_CCR3_CCR3                       ((uint16_t)0xFFFF)            /*!< Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define  TIM_CCR4_CCR4                       ((uint16_t)0xFFFF)            /*!< Capture/Compare 4 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define  TIM_BDTR_DTG                        ((uint16_t)0x00FF)            /*!< DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TIM_BDTR_DTG_0                      ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_BDTR_DTG_1                      ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TIM_BDTR_DTG_2                      ((uint16_t)0x0004)            /*!< Bit 2 */
#define  TIM_BDTR_DTG_3                      ((uint16_t)0x0008)            /*!< Bit 3 */
#define  TIM_BDTR_DTG_4                      ((uint16_t)0x0010)            /*!< Bit 4 */
#define  TIM_BDTR_DTG_5                      ((uint16_t)0x0020)            /*!< Bit 5 */
#define  TIM_BDTR_DTG_6                      ((uint16_t)0x0040)            /*!< Bit 6 */
#define  TIM_BDTR_DTG_7                      ((uint16_t)0x0080)            /*!< Bit 7 */

#define  TIM_BDTR_LOCK                       ((uint16_t)0x0300)            /*!< LOCK[1:0] bits (Lock Configuration) */
#define  TIM_BDTR_LOCK_0                     ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_BDTR_LOCK_1                     ((uint16_t)0x0200)            /*!< Bit 1 */

#define  TIM_BDTR_OSSI                       ((uint16_t)0x0400)            /*!< Off-State Selection for Idle mode */
#define  TIM_BDTR_OSSR                       ((uint16_t)0x0800)            /*!< Off-State Selection for Run mode */
#define  TIM_BDTR_BKE                        ((uint16_t)0x1000)            /*!< Break enable */
#define  TIM_BDTR_BKP                        ((uint16_t)0x2000)            /*!< Break Polarity */
#define  TIM_BDTR_AOE                        ((uint16_t)0x4000)            /*!< Automatic Output enable */
#define  TIM_BDTR_MOE                        ((uint16_t)0x8000)            /*!< Main Output enable */

/*******************  Bit definition for TIM_DCR register  ********************/
#define  TIM_DCR_DBA                         ((uint16_t)0x001F)            /*!< DBA[4:0] bits (DMA Base Address) */
#define  TIM_DCR_DBA_0                       ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_DCR_DBA_1                       ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TIM_DCR_DBA_2                       ((uint16_t)0x0004)            /*!< Bit 2 */
#define  TIM_DCR_DBA_3                       ((uint16_t)0x0008)            /*!< Bit 3 */
#define  TIM_DCR_DBA_4                       ((uint16_t)0x0010)            /*!< Bit 4 */

#define  TIM_DCR_DBL                         ((uint16_t)0x1F00)            /*!< DBL[4:0] bits (DMA Burst Length) */
#define  TIM_DCR_DBL_0                       ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_DCR_DBL_1                       ((uint16_t)0x0200)            /*!< Bit 1 */
#define  TIM_DCR_DBL_2                       ((uint16_t)0x0400)            /*!< Bit 2 */
#define  TIM_DCR_DBL_3                       ((uint16_t)0x0800)            /*!< Bit 3 */
#define  TIM_DCR_DBL_4                       ((uint16_t)0x1000)            /*!< Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define  TIM_DMAR_DMAB                       ((uint16_t)0xFFFF)            /*!< DMA register for burst accesses */

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __CX32S003_H */

/**
  * @}
  */

  /**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

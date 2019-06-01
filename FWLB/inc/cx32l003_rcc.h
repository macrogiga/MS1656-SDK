/**
  ******************************************************************************
  * @file   cx32l003_rcc.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the RCC firmware 
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
#ifndef __CX32l003_RCC_H
#define __CX32l003_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"

/** @defgroup RCC_ClocksTypeDef
  * @{
  */
typedef struct
{
  uint32_t SYSCLK_Frequency;  /*!< returns SYSCLK clock frequency expressed in Hz */
  uint32_t HCLK_Frequency;    /*!< returns HCLK clock frequency expressed in Hz */
  uint32_t PCLK_Frequency;   /*!< returns PCLK1 clock frequency expressed in Hz */
  uint32_t ADCCLK_Frequency;  /*!< returns ADCCLK clock frequency expressed in Hz */
}RCC_ClocksTypeDef;


/** @defgroup RCC_ClocksTypeDef
  * @{
  */
typedef struct
{
  uint32_t LXPORT;   /*!< returns SYSCLK clock frequency expressed in Hz */
  uint32_t LXAON;    /*!< returns HCLK clock frequency expressed in Hz */
  uint32_t LXTBYP;   /*!< returns PCLK1 clock frequency expressed in Hz */
  uint32_t LXTEN;    /*!< returns ADCCLK clock frequency expressed in Hz */
	uint32_t LXTSTARTUP;
	uint32_t LXTDIV;
}LXT_InitTypeDef;



/* Exported types ------------------------------------------------------------*/
#define IS_RCC_ALL_PERIPH(PERIPH) ((PERIPH) == RCC)


/** @defgroup RCC_Exported_Constants
  * @{
  */
#define  RCC_CLK_KEYMASK    (uint32_t)0xffff0000
#define  RCC_CLKCONKEY      (uint32_t)0x5A690000
#define  RCC_LXTCLK_KEY     (uint32_t)0x5A690000
#define  RCC_HIRCCLK_KEY    (uint32_t)0x5A690000
#define  RCC_HXTCLK_KEY     (uint32_t)0x5A690000
#define  RCC_LIRCCLK_KEY    (uint32_t)0x5A690000
#define  RCC_SYSCLKSEL_KEY  (uint32_t)0x5A690000
#define  RCC_REGLOCKKEY   (uint32_t)0x55aa6699
#define  RCC_RESGLOCKKEY  (uint32_t)0x55aa6698
#define RCC_APBPeriph_RTCRSTKEY  (uint32_t)0x5A690000
#define RCC_RSTKEY     (uint32_t)0x55AA6698




/** @defgroup AHBCLKEN_configuration 
  * @{
  */
#define RCC_AHB_CLKMASK                       ((uint32_t)0x0000001F)
#define RCC_APB_CLKMASK                       ((uint32_t)0x001FFFFF)

/** @defgroup System_clock_source 
  * @{
  */
#define RCC_SYSCLKSource_HIRC           ((uint32_t)0x00000001)
#define RCC_SYSCLKSource_HXT            ((uint32_t)0x00000002)
#define RCC_SYSCLKSource_LIRC           ((uint32_t)0x00000004)
#define RCC_SYSCLKSource_LXRC           ((uint32_t)0x00000100)

#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HIRC)|| \
                                      ((SOURCE) == RCC_SYSCLKSource_HXT) || \
                                      ((SOURCE) == RCC_SYSCLKSource_LIRC)||\
																			((SOURCE) == RCC_SYSCLKSource_LXRC))

                      
/** @defgroup System_clock_source 
  * @{
  */
#define RCC_SYSCLKSource_HIRC_EN            ((uint32_t)0x00000001)
#define RCC_SYSCLKSource_HXT_EN             ((uint32_t)0x00000002)
#define RCC_SYSCLKSource_LIRC_EN            ((uint32_t)0x00000004)
#define RCC_SYSCLKSource_LXRC_EN            ((uint32_t)0x00000100)
#define RCC_SYSCLKSource_EN_MASK            ((uint32_t)0x00000007)
#define RCC_LXTCLKSource_EN_MASK            ((uint32_t)0x00000100)


																			
/** @defgroup AHB_clock_source 
  * @{
  */
#define IS_RCC_SYSCLK_DIV(SYSHCLK)  ((SYSHCLK>= 0x00) ||\
                                     (SYSHCLK<= 0xff))
#define IS_RCC_HCLK_DIV(SYSPCLK)    ((SYSPCLK>= 0x00) ||\
                                     (SYSPCLK<= 0xff))
#define IS_RCC_FCLK_DIV(SYSPCLK)    ((SYSPCLK>= 0x00) ||\
                                     (SYSPCLK<= 0xff))

#define RCC_FCLK_DIV_MASK   0xff
                          
/** @defgroup AHB_clock_source 
  * @{
  */
#define RCC_SYSCLKOSEL_HIRC            (uint32_t)(0x00<<8)
#define RCC_SYSCLKOSEL_EXT             (uint32_t)(0x01<<8)
#define RCC_SYSCLKOSEL_LIRC            (uint32_t)(0x02<<8)
#define RCC_SYSCLKOSEL_LXT             (uint32_t)(0x03<<8)
#define RCC_SYSCLKOSEL_SYS             (uint32_t)(0x04<<8)
#define RCC_SYSCLKOSEL_FCLK            (uint32_t)(0x05<<8)
#define RCC_SYSCLKOSEL_MASK            (uint32_t)(0x07<<8)

#define IS_RCC_SYSCLKOSEL_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKOSEL_HIRC)||\
																					((SOURCE) == RCC_SYSCLKOSEL_EXT) ||\
																					((SOURCE) == RCC_SYSCLKOSEL_LIRC)||\
																					((SOURCE) == RCC_SYSCLKOSEL_LXT) ||\
																					((SOURCE) == RCC_SYSCLKOSEL_SYS) ||\
																					((SOURCE) == RCC_SYSCLKOSEL_FCLK))
																					
																					
#define  RCC_SYSCLKOUTPUT_ENABLE   0x1000

/** @defgroup AHB_peripheral_CLK 
  * @{
  */
#define RCC_AHBPeriph_GPIOAEN                ((uint32_t)0x00000001)
#define RCC_AHBPeriph_GPIOBEN                ((uint32_t)0x00000002)
#define RCC_AHBPeriph_GPIOCEN                ((uint32_t)0x00000004)
#define RCC_AHBPeriph_GPIODEN                ((uint32_t)0x00000008)
#define RCC_AHBPeriph_CRCEN                  ((uint32_t)0x00000010)
#define RCC_AHBPeriph_FLASHCE                ((uint32_t)0x00000080)
#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFF00) == 0x00)&&((PERIPH) != 0x00))



/** @defgroup APB_peripheral_CLKEN
  * @{
  */
#define RCC_APBPeriph_UART0CKEN              ((uint32_t)0x00000001)
#define RCC_APBPeriph_UART1CKEN              ((uint32_t)0x00000002)
#define RCC_APBPeriph_I2CCKEN                ((uint32_t)0x00000004)
#define RCC_APBPeriph_LPUARTCKEN             ((uint32_t)0x00000008)
#define RCC_APBPeriph_SPICKEN                ((uint32_t)0x00000010)
#define RCC_APBPeriph_LPTIMCKEN              ((uint32_t)0x00000020)
#define RCC_APBPeriph_BASETIMCKEN            ((uint32_t)0x00000040)
#define RCC_APBPeriph_SYSCONCKEN             ((uint32_t)0x00000080)
#define RCC_APBPeriph_PCACKEN                ((uint32_t)0x00000100)
#define RCC_APBPeriph_ONEWIRECKEN            ((uint32_t)0x00000200)
#define RCC_APBPeriph_PWMCKEN                ((uint32_t)0x00000400)
#define RCC_APBPeriph_IWDTCKEN               ((uint32_t)0x00000800)
#define RCC_APBPeriph_WWDTCKEN               ((uint32_t)0x00001000)
#define RCC_APBPeriph_ADCCKEN                ((uint32_t)0x00002000)
#define RCC_APBPeriph_AWKCKEN                ((uint32_t)0x00004000)
#define RCC_APBPeriph_RTCCKEN                ((uint32_t)0x00008000)
#define RCC_APBPeriph_TRIMCKEN               ((uint32_t)0x00010000)
#define RCC_APBPeriph_LVDVCCKEN              ((uint32_t)0x00040000)
#define RCC_APBPeriph_BEEPCKEN               ((uint32_t)0x00080000)
#define RCC_APBPeriph_MCUDBGCKEN             ((uint32_t)0x00100000)
#define IS_RCC_APB_PERIPH(PERIPH) ((((PERIPH) & 0xFFE00000) == 0x00) && ((PERIPH) != 0x00))


/** @defgroup APB_peripheral 
  * @{
  */
#define RCC_APBPeriph_UART0RST               ((uint32_t)0x00000001)
#define RCC_APBPeriph_UART1RST               ((uint32_t)0x00000002)
#define RCC_APBPeriph_I2CRST                 ((uint32_t)0x00000004)
#define RCC_APBPeriph_LPUARTRST              ((uint32_t)0x00000008)
#define RCC_APBPeriph_SPIRST                 ((uint32_t)0x00000010)
#define RCC_APBPeriph_LPTIMRST               ((uint32_t)0x00000020)
#define RCC_APBPeriph_BASETIMRST             ((uint32_t)0x00000040)
#define RCC_APBPeriph_SYSCONRST              ((uint32_t)0x00000080)
#define RCC_APBPeriph_PCARST                 ((uint32_t)0x00000100)
#define RCC_APBPeriph_ONEWIRERST             ((uint32_t)0x00000200)
#define RCC_APBPeriph_TIM1RST                ((uint32_t)0x00000400)
#define RCC_APBPeriph_TIM2RST                ((uint32_t)0x00000800)

#define RCC_APBPeriph_WWDTRST                ((uint32_t)0x00001000)
#define RCC_APBPeriph_ADCRST                 ((uint32_t)0x00002000)
#define RCC_APBPeriph_AWKRST                 ((uint32_t)0x00004000)

#define RCC_APBPeriph_TRIMRST                ((uint32_t)0x00010000)
#define RCC_APBPeriph_LVDVCRST               ((uint32_t)0x00040000)
#define RCC_APBPeriph_BEEPRST                ((uint32_t)0x00080000)
#define RCC_APBPeriph_MCUDBGRST              ((uint32_t)0x00100000)

#define RCC_AHBPeriph_GPIOARST               ((uint32_t)0x01000000)
#define RCC_AHBPeriph_GPIOBRST               ((uint32_t)0x02000000)
#define RCC_AHBPeriph_GPIOCRST               ((uint32_t)0x04000000)
#define RCC_AHBPeriph_GPIODRST               ((uint32_t)0x08000000)
#define RCC_AHBPeriph_CRCRST                 ((uint32_t)0x10000000)
#define IS_RCC_PERIPHRST(PERIPH)  ((((PERIPH) & 0x1f1d7fff) == PERIPH) && ((PERIPH) != 0x00))


#define  RCC_RTCPeriph_RSTEABLE       ((uint32_t)0x01) 
#define  RCC_RTCPeriph_RSTDISABLE     ((uint32_t)0x00) 



/** @defgroup RST MODEL
  * @{
  */
#define RCC_MCURST  0x01
#define RCC_CPURST  0x02
#define IS_RCC_RST(RST)  ((RST== RCC_MCURST) ||\
                          (RST == RCC_CPURST))


/** @defgroup GET RCC FLAG 
  * @{
  */
#define RCC_FLAG_MCURST      ((uint32_t)0x00000001)
#define RCC_FLAG_CPURST      ((uint32_t)0x00000002)
#define RCC_FLAG_WWDTRST     ((uint32_t)0x00000004)
#define RCC_FLAG_IWDTRST     ((uint32_t)0x00000008)
#define RCC_FLAG_LVDRST      ((uint32_t)0x00000010)
#define RCC_FLAG_PORRST      ((uint32_t)0x00000020)
#define RCC_FLAG_LOCKUPRST   ((uint32_t)0x00000040)
#define RCC_FLAG_PADRST      ((uint32_t)0x00000080)
#define IS_RCC_FLAG_RST(FLAG) ((((FLAG) & 0xFFFFFF00) == 0x00) && ((FLAG) != 0x00))

/** @defgroup GET RCC FLAG 
  * @{
  */
#define RCC_FLAG_HIRCRDY                 ((uint32_t)0x00001000)
#define RCC_FLAG_HXTRDY                  ((uint32_t)0x00000040)
#define RCC_FLAG_LIRCRDY                 ((uint32_t)0x00001000)
#define RCC_FLAG_LXTRDY                  ((uint32_t)0x00000040)

/** @defgroup GET RCC FLAG 
  * @{
  */
#define RCC_HXT_20M30M    ((uint32_t)(0x03<<2))
#define RCC_HXT_12M20M    ((uint32_t)(0x02<<2)) 
#define RCC_HXT_6M12M     ((uint32_t)(0x01<<2)) 
#define RCC_HXT_4M6M      ((uint32_t)(0x00<<2)) 
#define IS_RCC_HXT_CLK(CLK) (((CLK & 0xFFFFFFF0) == 0x00 ) &&(CLK >= 0x00))


#define RCC_HXT_DRIVER_LEVEL3    ((uint32_t)0x03)
#define RCC_HXT_DRIVER_LEVEL2    ((uint32_t)0x02) 
#define RCC_HXT_DRIVER_LEVEL1    ((uint32_t)0x01) 
#define RCC_HXT_DRIVER_LEVEL0    ((uint32_t)0x00) 
#define IS_RCC_HXT_DRIVER(LEVEL) (((LEVEL & 0xFFFFFFF0) == 0x00) &&(LEVEL >= 0x00))

#define RCC_HIRC_TRIM_MASK       ((uint32_t)0x0000007FF)
#define RCC_LIRC_TRIM_MASK       ((uint32_t)0x0000003FF)

#define RCC_HXT_DRIVER_MASK    ((uint32_t)0x0000000F)
#define RCC_HXT_STARTUP_MASK   ((uint32_t)0x00000030)
#define RCC_LIRC_STARTUP_MASK  ((uint32_t)0x000000C0)
#define RCC_LXT_STARTUP_MASK   ((uint32_t)0x000000C0)
#define RCC_LXT_DRIVER_MASK    ((uint32_t)0x0000000F)

#define RCC_LXT_AON_MASK       ((uint32_t)0x00000400)
#define RCC_LXT_AON_EN         ((uint32_t)0x00000100)
#define RCC_LXT_BYP_EN         ((uint32_t)0x00000200)

#define RCC_X32K_PORT_EN       ((uint32_t)0x00000800)
#define RCC_SYSTEMTICKTIMER_STCALIB_MASK  ((uint32_t)0x01FFFFFF)

#define RCC_SYSTEMTICKTIMER_REFCORE_CLOCK ((uint32_t)0x02000000)


#define RCC_HIRC_STARTUP_PERIOD0     (uint32_t)0x00
#define RCC_HIRC_STARTUP_PERIOD2     (uint32_t)0x01
#define RCC_HIRC_STARTUP_PERIOD4     (uint32_t)0x02
#define RCC_HIRC_STARTUP_PERIOD32    (uint32_t)0x03
#define RCC_HIRC_STARTUP_PERIOD256   (uint32_t)0x04
#define RCC_HIRC_STARTUP_PERIOD1024  (uint32_t)0x05
#define RCC_HIRC_STARTUP_PERIOD4096  (uint32_t)0x06
#define RCC_HIRC_STARTUP_PERIOD8192  (uint32_t)0x07
#define IS_RCC_HIRC_STARTUP_PERIOD(PERIOD) (((PERIOD & 0xFFFFFFFF8) == 0x00) &&((PERIOD >= 0x00)))



#define RCC_HXT_STARTUP_PERIOD256   ((uint32_t)(0x00<<4))
#define RCC_HXT_STARTUP_PERIOD1024  ((uint32_t)(0x01<<4))
#define RCC_HXT_STARTUP_PERIOD4096  ((uint32_t)(0x02<<4))
#define RCC_HXT_STARTUP_PERIOD16384 ((uint32_t)(0x03<<4))
#define IS_RCC_HXT_STARTUP_PERIOD(PERIOD) (((PERIOD & 0xFFFFFFCF) == 0x00) &&((PERIOD >= 0x00)))

#define RCC_LIRC_STARTUP_PERIOD256   ((uint32_t)(0x03<<10))
#define RCC_LIRC_STARTUP_PERIOD64    ((uint32_t)(0x02<<10))
#define RCC_LIRC_STARTUP_PERIOD16    ((uint32_t)(0x01<<10))
#define RCC_LIRC_STARTUP_PERIOD4     ((uint32_t)(0x00<<10))
#define IS_RCC_LIRC_STARTUP_PERIOD(PERIOD) (((PERIOD & 0xFFFFFF3F) == 0x00) &&((PERIOD >= 0x00)))

#define RCC_LXT_STARTUP_PERIOD256   ((uint32_t)(0x00<<4))
#define RCC_LXT_STARTUP_PERIOD1024  ((uint32_t)(0x01<<4))
#define RCC_LXT_STARTUP_PERIOD4096  ((uint32_t)(0x02<<4))
#define RCC_LXT_STARTUP_PERIOD16384 ((uint32_t)(0x03<<4))
#define IS_RCC_LXT_STARTUP_PERIOD(PERIOD) (((PERIOD & 0xFFFFFFCF) == 0x00) &&((PERIOD >= 0x00)))

#define PIN_SWD_FUNCTION   ((uint32_t)0x01)
#define PIN_GPIO_FUNCTION   ((uint32_t)0x00)
#define IS_PIN_FUNCTION(FUNCTION)  ((FUNCTION == PIN_SWD_FUNCTION)||(FUNCTION == PIN_GPIO_FUNCTION))


/* Exported functions --------------------------------------------------------*/
void RCC_DeInit(void);
void RCC_HIRCTrim(RCC_TypeDef *RCCx,uint32_t RCC_HIRCCR);
void RCC_LIRCTrim(RCC_TypeDef *RCCx,uint32_t RCC_LIRCCR);
void RCC_SetHXTDrive(RCC_TypeDef *RCCx,uint32_t HXTCKL,uint32_t HXTDRIVER);
void RCC_SetLXTDrive(RCC_TypeDef *RCCx,uint8_t LXTAM,uint8_t LXTDRIVER);
ErrorStatus RCC_WaitForHIRCStable(RCC_TypeDef *RCCx);
ErrorStatus RCC_WaitForHXTStable(RCC_TypeDef *RCCx,uint8_t PERIOD);
ErrorStatus RCC_WaitForLIRCStable(RCC_TypeDef *RCCx,uint8_t PERIOD);
ErrorStatus RCC_WaitForLXTStable(RCC_TypeDef *RCCx,uint8_t PERIOD);
void RCC_LXTCmd(RCC_TypeDef *RCCx,LXT_InitTypeDef *LXT_InitStruct);
void RCC_SetM0IRQLatency(RCC_TypeDef *RCCx,uint32_t IRQLATENCY);
void RCC_SystemTickTimerConfig(RCC_TypeDef *RCCx,uint8_t SKEW, uint32_t TICKTIMERSTCALIB);
void RCC_SetSystemTickTimerCoreRefClockcmd(RCC_TypeDef *RCCx,FunctionalState NewState);
void RCC_SysclkCmd(RCC_TypeDef *RCCx,uint32_t RCC_SYSCLKSource,FunctionalState NewState);
void RCC_SelSysclk(RCC_TypeDef *RCCx,uint32_t RCC_SYSCLKSource);
void RCC_SysclkOutputConfig(RCC_TypeDef *RCCx,uint32_t RCC_SYSCLKSource);
void RCC_SysclkOutputCmd(RCC_TypeDef *RCCx,FunctionalState NewState);
void RCC_SysclkFclkDiv(RCC_TypeDef *RCCx,uint8_t RCC_SYSCLKSource_DIV);
uint8_t RCC_GetSysclkSource(RCC_TypeDef *RCCx);
void RCC_SetHclkDiv(RCC_TypeDef *RCCx,uint8_t RCC_SYSCLK_DIV);
void RCC_SetPclkDiv(RCC_TypeDef *RCCx,uint8_t RCC_HCLK_DIV);
void RCC_GetClocksFreq(RCC_TypeDef *RCCx,RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(RCC_TypeDef *RCCx,uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APBPeriphClockCmd(RCC_TypeDef *RCCx,uint32_t RCC_APBPeriph, FunctionalState NewState);
void RCC_PeriphResetCmd(RCC_TypeDef *RCCx,uint32_t RCC_PeriphRst, FunctionalState NewState);
void RCC_RTCResetCmd(RCC_TypeDef *RCCx, FunctionalState NewState);
void RCC_ResetCmd(RCC_TypeDef *RCCx,uint32_t RCC_RSTModle,FunctionalState NewState);
FlagStatus RCC_GetFlagStatus(RCC_TypeDef *RCCx,uint32_t RCC_FLAG_RST);
void RCC_SetIoMux(RCC_TypeDef *RCCx,uint32_t function);
#ifdef __cplusplus
}
#endif

#endif

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


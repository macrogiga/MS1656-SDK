/**
  ******************************************************************************
  * @file    cx32l003_rcc.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides all the RCC firmware functions.
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

/* Includes ------------------------------------------------------------------*/
#include  "cx32l003_rcc.h"

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @param  None
  * @retval None
  */
void RCC_DeInit(void)
{
	/*Close AHB Clock*/
	RCC->AHBCLKEN  &= ~RCC_AHB_CLKMASK;
	
	/*Close APB Clock*/
	RCC->AHBCLKEN  &= ~RCC_APB_CLKMASK;
}

/**
  * @brief  Configures HIRC Triming vlaue.
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_HIRCCR: The HIRC Triming value
  * @retval None
  */
void RCC_HIRCTrim(RCC_TypeDef *RCCx,uint32_t RCC_HIRCCR)
{
	uint32_t HIRC_KEY;
	/*Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	HIRC_KEY = RCC_HIRCCLK_KEY;
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	/*Set the Triming value to the HIRCCR register*/
	RCCx->HIRCCR = HIRC_KEY|RCC_HIRCCR;
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;
}

/**
  * @brief  Configures LIRC Triming vlaue.
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_LIRCCR: The LIRC Triming value
  * @retval None
  */
void RCC_LIRCTrim(RCC_TypeDef *RCCx,uint32_t RCC_LIRCCR)
{
	   uint32_t LIRC_KEY;
		/*Check the parameters */
	  assert_param(IS_RCC_ALL_PERIPH(RCCx));
	  LIRC_KEY = RCC_LIRCCLK_KEY;
	  /*Close the lock of register*/
	  RCCx->REGLOCK = RCC_REGLOCKKEY;
	
	  /*Set the Triming value to the LIRCCR register*/
		RCCx->LIRCCR = LIRC_KEY|RCC_LIRCCR;
	  
	  /*Open the lock of register*/
	  RCCx->REGLOCK = RCC_RESGLOCKKEY;
}
/**
  * @brief  Set the HXT DRIVE function
  * @param  RCCx: Selects the RCC peripheral
  * @param  HXTCKL: Selects the hxt clk
  * @param  HXTDRIVER: Set the value to the HXT DRIVER of register
  * @retval None
  */
void RCC_SetHXTDrive(RCC_TypeDef *RCCx,uint32_t HXTCKL,uint32_t HXTDRIVER)
{
	 uint32_t HXTDRIVER1 = 0;

	/*Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	assert_param(IS_RCC_HXT_CLK(HXTCKL));
	assert_param(IS_RCC_HXT_DRIVER(HXTDRIVER));
	
	/*Set the value of HXT DRIVER*/
	HXTDRIVER1 = (uint32_t)(HXTCKL|HXTDRIVER);
	
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	
	/*Set the value of driver to the HXTCR register*/

	RCCx->HXTCR  = RCC_HXTCLK_KEY|HXTDRIVER1;
	
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;	
}

/**
  * @brief  Set the LXT DRIVE function
  * @param  RCCx: Selects the RCC peripheral
  * @param  LXTAM: Selects the lxt clk
  * @param  LXTDRIVER: Set the value to the LXT DRIVER of register
  * @retval None
  */
void RCC_SetLXTDrive(RCC_TypeDef *RCCx,uint8_t LXTAM,uint8_t LXTDRIVER)
{
	 uint32_t LXTDRIVER1 = 0;
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	
	/*Set the value of LXT DRIVER*/
	LXTDRIVER1 = (uint32_t)(LXTAM|LXTDRIVER);
	
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	
	/*Set the value of driver to the LXTCR register*/
	RCCx->LXTCR  = RCC_LXTCLK_KEY|LXTDRIVER1;
	
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;	
}

/**
  * @brief  Waits for HIRC Stable.
  * @param  RCCx: Selects the RCC peripheral
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: HSE oscillator is stable and ready to use
  * - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHIRCStable(RCC_TypeDef *RCCx)
{
  __IO uint32_t StartUpCounter = 0;
	uint32_t HIRCStatus = 0;
  ErrorStatus status = ERROR;
	
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));

  /* Wait till HICR STABLE*/
  do
  {
    HIRCStatus = (RCCx->HIRCCR & RCC_FLAG_HIRCRDY);
    StartUpCounter++;  
  } while((StartUpCounter != HICR_STABLE_TIMEOUT) && (HIRCStatus == RCC_FLAG_HIRCRDY));
  
  if (HIRCStatus == RCC_FLAG_HIRCRDY)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
  return (status);
}

/**
  * @brief  Waits for HXT Stable.
  * @param  RCCx: Selects the RCC peripheral
  * @param  PERIOD: the time of HXT stable
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: HSE oscillator is stable and ready to use
  * - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHXTStable(RCC_TypeDef *RCCx,uint8_t PERIOD)
{
  __IO uint32_t StartUpCounter = 0;
	uint32_t HXTStatus = 0;
  ErrorStatus status = ERROR;
	
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_HXT_STARTUP_PERIOD(PERIOD));
	
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	/*Set HXT STARTUP*/

	RCCx->HXTCR = RCC_HXTCLK_KEY|PERIOD;
	
  /* Wait till HXT STABLE*/
  do
  {
    HXTStatus = (RCCx->HXTCR & RCC_FLAG_HXTRDY);
    StartUpCounter++;  
  } while((StartUpCounter != HXT_STABLE_TIMEOUT) && (HXTStatus == RCC_FLAG_HXTRDY));
  
  if (HXTStatus == RCC_FLAG_HXTRDY)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
	
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;	
  return (status);
}

/**
  * @brief  Waits for LIRC Stable.
  * @param  RCCx: Selects the RCC peripheral
  * @param  PERIOD: the time of LIRC stable
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: HSE oscillator is stable and ready to use
  * - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForLIRCStable(RCC_TypeDef *RCCx,uint8_t PERIOD)
{
  __IO uint32_t StartUpCounter = 0;
	uint32_t LIRCStatus = 0;
  ErrorStatus status = ERROR;
	
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_LIRC_STARTUP_PERIOD(PERIOD));
	
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	/*Set LIRC STARTUP*/

	RCCx->LIRCCR = RCC_LIRCCLK_KEY|PERIOD;
	
  /* Wait till LIRC STABLE*/
  do
  {
    LIRCStatus = (RCCx->LIRCCR & RCC_FLAG_LIRCRDY);
    StartUpCounter++;  
  }while((StartUpCounter != HXT_STABLE_TIMEOUT) && (LIRCStatus == RCC_FLAG_LIRCRDY));
  
  if (LIRCStatus == RCC_FLAG_LIRCRDY)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
	
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;	
  return (status);
}

/**
  * @brief  Waits for LXT Stable.
  * @param  RCCx: Selects the RCC peripheral
  * @param  PERIOD: the time of LXT stable
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: HSE oscillator is stable and ready to use
  * - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForLXTStable(RCC_TypeDef *RCCx,uint8_t PERIOD)
{
  __IO uint32_t StartUpCounter = 0;
	uint32_t LXTStatus = 0;
  ErrorStatus status = ERROR;
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_LXT_STARTUP_PERIOD(PERIOD));
	
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;

  /* Wait till HXT STABLE*/
  do
  {
    LXTStatus = (RCCx->LXTCR & RCC_FLAG_LXTRDY);
    StartUpCounter++;  
  }while((StartUpCounter != LXT_STABLE_TIMEOUT) && (LXTStatus == RCC_FLAG_LXTRDY));
  
  if (LXTStatus == RCC_FLAG_LXTRDY)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
	
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;	
  return (status);
}

/**
  * @brief  Enables LXT function
  * @param  RCCx: Selects the RCC peripheral
  * @param  LXT_InitStruct: pointer to a SPI_InitTypeDef structure which will be used.
  * @retval None
  */
void RCC_LXTCmd(RCC_TypeDef *RCCx,LXT_InitTypeDef *LXT_InitStruct)
{
	/*Check the parameters */
  uint32_t tmp =0,tmp1 =0;

	
	/*Set the parameters of LXT register */
	tmp1 = ((LXT_InitStruct->LXAON<<10)|\
	       (LXT_InitStruct->LXPORT<<11)|\
	       (LXT_InitStruct->LXTBYP<<9)|\
	       (LXT_InitStruct->LXTDIV<<0)|\
	       (LXT_InitStruct->LXTEN<<8)|\
	       (LXT_InitStruct->LXTSTARTUP<<4));
	
  /*Set the vlaue for lxt */	
	tmp = RCC_LXTCLK_KEY|tmp1;
	
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	RCCx->LXTCR = tmp;
	
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;	
		
}



/**
  * @brief  Set the port of 32k 
  * @param  RCCx: Selects the RCC peripheral
  * @param  NewState: new state of the 32k port. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_SetX32KPort(RCC_TypeDef *RCCx,FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	
	if(NewState!= DISABLE)
		/*Enable the 32k port*/
		RCCx->LXTCR  = RCC_LXTCLK_KEY|RCC_X32K_PORT_EN; 
	else
		/*Enable the GPIO port*/
		RCCx->LXTCR  = RCC_LXTCLK_KEY;
	
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;	
}

/**
  * @brief  Set M0 IRQ Latency.
  * @param  RCCx: Selects the RCC peripheral
  * @param  IRQLATENCY: The value of IRQ LATENCY
  * @retval None
  */
void RCC_SetM0IRQLatency(RCC_TypeDef *RCCx,uint32_t IRQLATENCY)
{
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	
	/*Close the lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	
	/*Set value to IRQ latency register*/
  RCCx->IRQLATENCY = IRQLATENCY;
	
	/*Open the lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;	
}


/**
  * @brief config system tick timer
  * @param  RCCx: Selects the RCC peripheral
	* @param  SKEW:
	* @param  TICKTIMERSTCALIB: 
  * @retval None
  */
void RCC_SystemTickTimerConfig(RCC_TypeDef *RCCx,uint8_t SKEW, uint32_t TICKTIMERSTCALIB)
{
		/*Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	
	/*Set the value to STCALIB register*/
	RCCx->STCALIB  &= ~RCC_SYSTEMTICKTIMER_STCALIB_MASK;
	RCCx->STCALIB  |= (SKEW<<24);
	RCCx->STCALIB  |= TICKTIMERSTCALIB;
}

/**
  * @brief  Enables system tick timer core ref clock 
  * @param  RCCx: Selects the RCC peripheral
  * @param  NewState: new state of the 32k port. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_SetSystemTickTimerCoreRefClockcmd(RCC_TypeDef *RCCx,FunctionalState NewState)
{
	 /*Check the parameters */
	 assert_param(IS_RCC_ALL_PERIPH(RCCx));
	
   RCCx->STCALIB &= ~RCC_SYSTEMTICKTIMER_REFCORE_CLOCK;
	
	 if(NewState != DISABLE)
		  /*set core clock */
		 RCCx->STCALIB |= RCC_SYSTEMTICKTIMER_REFCORE_CLOCK; 
	 else
		  /*set sclk/4*/
		 RCCx->STCALIB &= ~RCC_SYSTEMTICKTIMER_REFCORE_CLOCK; 
}

/**
  * @brief  Enables the system clock (SYSCLK).
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock.
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLKSource_HIRC:  source is hirc
  *     @arg RCC_SYSCLKSource_HXT:   source is hxt
  *     @arg RCC_SYSCLKSource_LIRC:  source is lirc
  *     @arg RCC_SYSCLKSource_LXRC:  source is lxrc
  * @retval None
  */
void RCC_SysclkCmd(RCC_TypeDef *RCCx,uint32_t RCC_SYSCLKSource,FunctionalState NewState)
{
  uint32_t tmpreg = 0;
	uint32_t tmpreg1 = 0;
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
  tmpreg = RCCx->CLKCON;
	tmpreg1= RCCx->LXTCR;
	
	//set keyflag
	tmpreg &= ~RCC_CLK_KEYMASK;
	tmpreg |= RCC_CLKCONKEY;
	tmpreg1 &= ~RCC_CLK_KEYMASK;
	tmpreg1 |= RCC_CLKCONKEY;
	
	if(RCC_SYSCLKSource == RCC_SYSCLKSource_HIRC)
	{
		if(NewState != DISABLE)
		/*RCC_SYSCLKSource value */
		tmpreg |= RCC_SYSCLKSource_HIRC_EN;
		else
		tmpreg &= ~RCC_SYSCLKSource_HIRC_EN;
	}
	else if(RCC_SYSCLKSource == RCC_SYSCLKSource_HXT)
	{
	  if(NewState != DISABLE)
		/*RCC_SYSCLKSource value */
		tmpreg |= RCC_SYSCLKSource_HXT_EN;
		else
		tmpreg &= ~RCC_SYSCLKSource_HXT_EN;
	}
	else if(RCC_SYSCLKSource == RCC_SYSCLKSource_LIRC)
	{
	  if(NewState != DISABLE)
		/*RCC_SYSCLKSource value */
		tmpreg |= RCC_SYSCLKSource_LIRC_EN;
		else
		tmpreg &= ~RCC_SYSCLKSource_LIRC_EN;
	} else {
		if(RCC_SYSCLKSource == RCC_SYSCLKSource_LXRC)
		{
			if(NewState != DISABLE)
			/*RCC_SYSCLKSource value */
			tmpreg1 |= RCC_SYSCLKSource_LXRC_EN;
			else
			tmpreg1 &= ~RCC_SYSCLKSource_LXRC_EN;
		}	
	}
	/*close lock*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	/*set clock source*/
	RCCx->CLKCON = tmpreg;
	RCCx->LXTCR  =  tmpreg1;
	/*open lock*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;
}

/**
  * @brief  Configures the system clock (SYSCLK).
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock.
  *  This parameter can be one of the following values:
  *     @arg RCC_SYSCLKSource_HIRC:  source is hirc
  *     @arg RCC_SYSCLKSource_HXT:   source is hxt
  *     @arg RCC_SYSCLKSource_LIRC:  source is lirc
  *     @arg RCC_SYSCLKSource_LXRC:  source is lxrc
  * @retval None
  */
void RCC_SelSysclk(RCC_TypeDef *RCCx,uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
  /*RCC_SYSCLKSource value */
  tmpreg |= RCC_SYSCLKSource;
  /*set clkcon  key */
	tmpreg |= RCC_SYSCLKSEL_KEY;
	/*close lock*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	/*set clock source*/
	RCCx->CLKSEL  =  tmpreg;
	/*open lock*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;
}
/**
  * @brief  Configures the system clock output function
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock.
  *  This parameter can be one of the following values:
  *     @arg RCC_SYSCLKSource_HIRC:  source is hirc
  *     @arg RCC_SYSCLKSource_HXT:   source is hxt
  *     @arg RCC_SYSCLKSource_LIRC:  source is lirc
  *     @arg RCC_SYSCLKSource_LXRC:  source is lxrc
  * @retval None
  */
void RCC_SysclkOutputConfig(RCC_TypeDef *RCCx,uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_SYSCLKOSEL_SOURCE(RCC_SYSCLKSource));
  tmpreg = RCCx->MCO;
  /*RCC_SYSCLKSource value */
	tmpreg &= ~RCC_SYSCLKOSEL_MASK;
  tmpreg |=  RCC_SYSCLKSource;
	/*set clock source*/
	RCCx->MCO  =  tmpreg;
}

/**
  * @brief  Enables the function of sysclk output 
  * @param  RCCx: Selects the RCC peripheral
  * @param  NewState: new state of the Sysclk Output. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_SysclkOutputCmd(RCC_TypeDef *RCCx,FunctionalState NewState)
{
  uint32_t tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	/*read CLKOCON */
	tmpreg = RCCx->MCO;
  if(NewState != DISABLE)
	{
		/*RCC_SYSCLKOUTPUT_ENABLE*/
		tmpreg |= RCC_SYSCLKOUTPUT_ENABLE;
	} 
	else 
	{
		/*RCC_SYSCLKOUTPUT_DISABLE*/
		tmpreg &= ~RCC_SYSCLKOUTPUT_ENABLE;
	}
	/*set clock source*/
	RCCx->MCO  =  tmpreg;
}
/**
  * @brief  Configures the fclk division frequery
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_SYSCLKSource_DIV: Set clock division parameters
  * @retval None
  */
void RCC_SysclkFclkDiv(RCC_TypeDef *RCCx,uint8_t RCC_SYSCLKSource_DIV)
{
  uint32_t tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_FCLK_DIV(RCC_SYSCLKSource_DIV));
	/*read CLKOCON */
	tmpreg = RCCx->MCO;
	/*set fclk div */
  tmpreg &= ~RCC_FCLK_DIV_MASK;
	tmpreg |= RCC_SYSCLKSource_DIV;
	/*set fclk value*/
	RCCx->MCO  =  tmpreg;
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  RCCx: Selects the RCC peripheral
  * @retval the value of CLKCON register
  */
uint8_t RCC_GetSysclkSource(RCC_TypeDef *RCCx)
{
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  return ((uint8_t)(RCCx->CLKCON&RCC_SYSCLKSource_EN_MASK));
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_SYSCLK_DIV: defines the AHB clock divider. This clock is derived from 
  *   the system clock (SYSCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLK_Div0: AHB clock = SYSCLK
        @arg RCC_SYSCLK_Div1~255: AHB clock = SYSCLK/(2*DIV)
  *
  * @retval None
  */
void RCC_SetHclkDiv(RCC_TypeDef *RCCx,uint8_t RCC_SYSCLK_DIV)
{
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_SYSCLK_DIV(RCC_SYSCLK_DIV));
  /* Store the new value */
  RCCx->AHBCLKDIV = (uint32_t)RCC_SYSCLK_DIV;
}

/**
  * @brief  Configures the Low Speed APB clock (PCLK).
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_PCLK_DIV: defines the APB clock divider. This clock is derived from 
  *   the APB clock (PCLK).
  *   This parameter can be one of the following values:
        @arg RCC_AHB_Div0: APB clock = AHBCLK
        @arg RCC_AHB_Div1~255: APB clock = AHBCLK/(2*DIV)
  * @retval None
  */
void RCC_SetPclkDiv(RCC_TypeDef *RCCx,uint8_t RCC_PCLK_DIV)
{
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  /* Check the parameters */
  assert_param(IS_RCC_HCLK_DIV(RCC_PCLK_DIV));
  /* Store the new value */
  RCCx->APBCLKDIV = (uint32_t)RCC_PCLK_DIV;
}
/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.   
  * this parameter can be any combination of the following values:        
				@arg RCC_AHBPeriph_GPIOAEN :      Enables GPIOA         
				@arg RCC_AHBPeriph_GPIOBEN  :     Enables GPIOB  
				@arg RCC_AHBPeriph_GPIOCEN :      Enables GPIOC        
				@arg RCC_AHBPeriph_GPIODEN  :     Enables GPIOD         
				@arg RCC_AHBPeriph_CRCEN   :      Enables CRC           
				@arg RCC_AHBPeriph_FLASHCE :      Enables FLASH 
  * @param  NewState: new state of the AHB Periph clock. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(RCC_TypeDef *RCCx,uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCCx->AHBCLKEN|= RCC_AHBPeriph;
  }
  else
  {
    RCCx->AHBCLKEN &= ~RCC_AHBPeriph;
  }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
        @arg RCC_APBPeriph_UART0CKEN :            ((uint32_t)0x00000001)
				@arg RCC_APBPeriph_UART1CKEN              ((uint32_t)0x00000002)
				@arg RCC_APBPeriph_I2CCKEN                ((uint32_t)0x00000004)
				@arg RCC_APBPeriph_LPUARTCKEN             ((uint32_t)0x00000008)
				@arg RCC_APBPeriph_SPICKEN                ((uint32_t)0x00000010)
				@arg RCC_APBPeriph_LPTIMCKEN              ((uint32_t)0x00000020)
				@arg RCC_APBPeriph_BASETIMCKEN            ((uint32_t)0x00000040)
				@arg RCC_APBPeriph_SYSCONCKEN             ((uint32_t)0x00000080)
				@arg RCC_APBPeriph_PCACKEN                ((uint32_t)0x00000100)
				@arg RCC_APBPeriph_ONEWIRECKEN            ((uint32_t)0x00000200)
				@arg RCC_APBPeriph_PWMCKEN                ((uint32_t)0x00000400)
				@arg RCC_APBPeriph_IWDTCKEN               ((uint32_t)0x00000800)
				@arg RCC_APBPeriph_WWDTCKEN               ((uint32_t)0x00001000)
				@arg RCC_APBPeriph_ADCCKEN                ((uint32_t)0x00002000)
				@arg RCC_APBPeriph_AWKCKEN                ((uint32_t)0x00004000)
				@arg RCC_APBPeriph_RTCCKEN                ((uint32_t)0x00008000)
				@arg RCC_APBPeriph_TRIMCKEN               ((uint32_t)0x00010000)
				@arg RCC_APBPeriph_LVDVCCKEN              ((uint32_t)0x00040000)
				@arg RCC_APBPeriph_BEEPCKEN               ((uint32_t)0x00080000)
				@arg RCC_APBPeriph_MCUDBGCKEN             ((uint32_t)0x00100000)
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APBPeriphClockCmd(RCC_TypeDef *RCCx,uint32_t RCC_APBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCCx->APBCLKEN |= RCC_APBPeriph;
  }
  else
  {
    RCCx->APBCLKEN &= ~RCC_APBPeriph;
  }

}
/**
  * @brief  Forces or releases AHB peripheral reset.
  * @note   This function applies only to STM32 Connectivity line devices.
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_PeriphRst: specifies the AHB peripheral to reset.
  * @param  NewState: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PeriphResetCmd(RCC_TypeDef *RCCx,uint32_t RCC_PeriphRst, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_PERIPHRST(RCC_PeriphRst));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	/*close lock*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;

  if (NewState != DISABLE)
  {
    RCCx->RERIRST |= RCC_PeriphRst;
  }
  else
  {
    RCCx->RERIRST &= ~RCC_PeriphRst;
  }
	
  /*open lock*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;
}

/**
  * @brief  Forces or releases rtc peripheral reset.
  * @param  RCCx: Selects the RCC peripheral
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCResetCmd(RCC_TypeDef *RCCx, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_PERIPHRST(RCC_RTCPeriphRST));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
  /*close lock*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	
  if (NewState != DISABLE)
  {
    RCCx->RTCRST = (RCC_APBPeriph_RTCRSTKEY|RCC_RTCPeriph_RSTEABLE);
  }
  else
  {
    RCCx->RTCRST = (RCC_APBPeriph_RTCRSTKEY|RCC_RTCPeriph_RSTDISABLE);
  }
	
	/*open lock*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;
}

/**
  * @brief  Forces or releases the Backup domain reset.
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_RSTModle: rcc reset mode
  * @param  NewState: new state of the Backup domain reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ResetCmd(RCC_TypeDef *RCCx,uint32_t RCC_RSTModle,FunctionalState NewState)
{
	 uint32_t RCC_RSTMODLE;
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	assert_param(IS_RCC_RST(RCC_RSTModle));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	RCC_RSTMODLE = RCC_RSTModle | RCC_RSTKEY;
	
	/*close lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;

  if (NewState != DISABLE)
  {
    RCCx->RSTCON |= RCC_RSTMODLE;
  }
  else
  {
    RCCx->RSTCON &= ~RCC_RSTMODLE;
  }
	
	/*open lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCCx: Selects the RCC peripheral
  * @param  RCC_FLAG: specifies the flag to check. 
			@arg RCC_FLAG_MCURST      ((uint32_t)0x00000001)
			@arg RCC_FLAG_CPURST      ((uint32_t)0x00000002)
			@arg RCC_FLAG_WWDTRST     ((uint32_t)0x00000004)
			@arg RCC_FLAG_IWDTRST     ((uint32_t)0x00000008)
			@arg RCC_FLAG_LVDRST      ((uint32_t)0x00000010)
			@arg RCC_FLAG_PORRST      ((uint32_t)0x00000020)
			@arg RCC_FLAG_LOCKUPRST   ((uint32_t)0x00000040)
			@arg RCC_FLAG_PADRST      ((uint32_t)0x00000080)
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(RCC_TypeDef *RCCx,uint32_t RCC_FLAG_RST)
{
  uint32_t tmp = 0;
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_RCC_FLAG_RST(RCC_FLAG_RST));

  /* Get the RCC Reset Value */
  tmp =  RCCx->RSTSTAT ;

  if((tmp & RCC_FLAG_RST)!= (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}


/**
  * @brief  Set IO MUX function
  * @param  RCCx: Selects the RCC peripheral
  * @param  I0_MUX: IO_MUX function
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_SetIoMux(RCC_TypeDef *RCCx,uint32_t I0_MUX)
{
	uint32_t tmpreg = 0x5a690000; //KEY
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
  assert_param(IS_PIN_FUNCTION(I0_MUX));
	tmpreg  |= I0_MUX;
	
	/*close lock of register*/
	RCCx->REGLOCK = RCC_REGLOCKKEY;
	
	/*set the value to the IOMUX register*/
	RCCx->IOMUX = tmpreg;
	
	/*open lock of register*/
	RCCx->REGLOCK = RCC_RESGLOCKKEY;
}
/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/

















/**
  ******************************************************************************
  * @file    cx32l003_rtc.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Real-Time Clock (RTC) peripheral:
  *           + Initialization
  *           + Calendar (Time and Date) configuration
  *           + Alarms (Alarm A and Alarm B) configuration
  *           + WakeUp Timer configuration
  *           + Daylight Saving configuration
  *           + Output pin Configuration
  *           + Coarse digital Calibration configuration
  *           + Smooth digital Calibration configuration
  *           + Backup Data Registers configuration
  *           + Shift control synchronisation    
  *           + RTC Tamper and TimeStamp Pins Selection and Output Type Config configuration
  *           + Interrupts and flags management
  *
@verbatim

 ===================================================================
              ##### Backup Domain Operating Condition #####
 ===================================================================
 [..] The real-time clock (RTC), the RTC backup registers, and the backup 
      SRAM (BKP SRAM) can be powered from the VBAT voltage when the main 
      VDD supply is powered off.
      To retain the content of the RTC backup registers, backup SRAM, and supply 
      the RTC when VDD is turned off, VBAT pin can be connected to an optional 
      standby voltage supplied by a battery or by another source.

       
                   ##### Backup Domain Reset #####
 ===================================================================
 [..] The backup domain reset sets all RTC registers and the RCC_BDCR register 
      to their reset values. The BKPSRAM is not affected by this reset. The only
      way of resetting the BKPSRAM is through the Flash interface by requesting 
      a protection level change from 1 to 0.
 [..] A backup domain reset is generated when one of the following events occurs:
   (#) Software reset, triggered by setting the BDRST bit in the 
       RCC Backup domain control register (RCC_BDCR). You can use the
       RCC_BackupResetCmd().
   (#) VDD or VBAT power on, if both supplies have previously been powered off.
  

                   ##### Backup Domain Access #####
 ===================================================================
 [..] After reset, the backup domain (RTC registers, RTC backup data 
      registers and backup SRAM) is protected against possible unwanted write 
      accesses. 
 [..] To enable access to the RTC Domain and RTC registers, proceed as follows:
   (+) Enable the Power Controller (PWR) APB1 interface clock using the
       RCC_APB1PeriphClockCmd() function.
   (+) Enable access to RTC domain using the PWR_BackupAccessCmd() function.
   (+) Select the RTC clock source using the RCC_RTCCLKConfig() function.
   (+) Enable RTC Clock using the RCC_RTCCLKCmd() function.
  
  
                  ##### How to use RTC Driver #####
 ===================================================================
 [..] 
   (+) Enable the RTC domain access (see description in the section above)
   (+) Configure the RTC Prescaler (Asynchronous and Synchronous) and RTC hour 
       format using the RTC_Init() function.
  
 *** Time and Date configuration ***
 ===================================
 [..] 
   (+) To configure the RTC Calendar (Time and Date) use the RTC_SetTime()
       and RTC_SetDate() functions.
   (+) To read the RTC Calendar, use the RTC_GetTime() and RTC_GetDate() functions.
   (+) Use the RTC_DayLightSavingConfig() function to add or sub one
       hour to the RTC Calendar.    
  
 *** Alarm configuration ***
 ===========================
 [..]
   (+) To configure the RTC Alarm use the RTC_SetAlarm() function.
   (+) Enable the selected RTC Alarm using the RTC_AlarmCmd() function
   (+) To read the RTC Alarm, use the RTC_GetAlarm() function.
   (+) To read the RTC alarm SubSecond, use the RTC_GetAlarmSubSecond() function.
  
 *** RTC Wakeup configuration ***
 ================================
 [..] 
   (+) Configure the RTC Wakeup Clock source use the RTC_WakeUpClockConfig()
       function.
   (+) Configure the RTC WakeUp Counter using the RTC_SetWakeUpCounter() function  
   (+) Enable the RTC WakeUp using the RTC_WakeUpCmd() function  
   (+) To read the RTC WakeUp Counter register, use the RTC_GetWakeUpCounter() 
       function.
  
 *** Outputs configuration ***
 =============================
 [..] The RTC has 2 different outputs:
   (+) AFO_ALARM: this output is used to manage the RTC Alarm A, Alarm B
       and WaKeUp signals. To output the selected RTC signal on RTC_AF1 pin, use the 
       RTC_OutputConfig() function.                
   (+) AFO_CALIB: this output is 512Hz signal or 1Hz. To output the RTC Clock on 
       RTC_AF1 pin, use the RTC_CalibOutputCmd() function.
  
 *** Smooth digital Calibration configuration ***
 ================================================    
 [..]
   (+) Configure the RTC Original Digital Calibration Value and the corresponding
       calibration cycle period (32s,16s and 8s) using the RTC_SmoothCalibConfig() 
       function.
  
 *** Coarse digital Calibration configuration ***
 ================================================
 [..]
   (+) Configure the RTC Coarse Calibration Value and the corresponding
       sign using the RTC_CoarseCalibConfig() function.
   (+) Enable the RTC Coarse Calibration using the RTC_CoarseCalibCmd() function  
  

 *** Backup Data Registers configuration ***
 ===========================================
 [..]
   (+) To write to the RTC Backup Data registers, use the RTC_WriteBackupRegister()
       function.  
   (+) To read the RTC Backup Data registers, use the RTC_ReadBackupRegister()
       function.
 
 ##### Selection of RTC_AF1 alternate functions #####
 ===================================================================
 [..] The RTC_AF1 pin (PC13) can be used for the following purposes:
   (+) AFO_ALARM output
   (+) AFO_CALIB output
   (+) AFI_TAMPER
   (+) AFI_TIMESTAMP
 
  
 @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
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

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_rtc.h"
#include "cx32l003_rcc.h"

uint8_t  rtc_flg = 0x00;

/** @defgroup RTC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
             ##### Initialization and Configuration functions #####
 ===============================================================================
 
 [..] This section provide functions allowing to initialize and configure the RTC
      Prescaler (Synchronous and Asynchronous), RTC Hour format, disable RTC registers
      Write protection, enter and exit the RTC initialization mode, RTC registers
      synchronization check and reference clock detection enable.
  
   (#) The RTC Prescaler is programmed to generate the RTC 1Hz time base. It is
       split into 2 programmable prescalers to minimize power consumption.
       (++) A 7-bit asynchronous prescaler and A 13-bit synchronous prescaler.
       (++) When both prescalers are used, it is recommended to configure the 
            asynchronous prescaler to a high value to minimize consumption.

   (#) All RTC registers are Write protected. Writing to the RTC registers
       is enabled by writing a key into the Write Protection register, RTC_WPR.

   (#) To Configure the RTC Calendar, user application should enter initialization
       mode. In this mode, the calendar counter is stopped and its value can be 
       updated. When the initialization sequence is complete, the calendar restarts 
       counting after 4 RTCCLK cycles.

   (#) To read the calendar through the shadow registers after Calendar initialization,
       calendar update or after wakeup from low power modes the software must first 
       clear the RSF flag. The software must then wait until it is set again before 
       reading the calendar, which means that the calendar registers have been 
       correctly copied into the RTC_TR and RTC_DR shadow registers.
       The RTC_WaitForSynchro() function implements the above software sequence 
       (RSF clear and RSF check).

@endverbatim
  * @{
  */
	
/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  Value: Byte to be converted.
  * @retval Converted byte
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
  uint8_t bcdhigh = 0;
  
  while (Value >= 10)
  {
    bcdhigh++;
    Value -= 10;
  }
  
  return  ((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value: BCD value to be converted.
  * @retval Converted word
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
  uint8_t tmp = 0;
  tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (Value & (uint8_t)0x0F));
}


/**
  * @brief  Deinitializes the RTC registers to their default reset values.
  * @note   This function doesn't reset the RTC Clock source and RTC Backup Data
  *         registers.       
 * @param  RTCx: selects the RTC peripheral
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are deinitialized
  *          - ERROR: RTC registers are not deinitialized
  */
ErrorStatus RTC_DeInit(RTC_TypeDef *RTCx)
{
	  __IO uint32_t wutcounter = 0x00;
  uint32_t wutwfstatus = 0x00;
  ErrorStatus status = ERROR;
  
  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode(RTC) == ERROR)
  {
    status = ERROR;
  }  
  else
  {
    /* Reset TR, DR and CR registers */
    RTCx->CR  =   (uint32_t)0x00000000;
    RTCx->DATE = (uint32_t)0x00000000;

  
    /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
    do
    {
      wutwfstatus = RTCx->ISR & RTC_ISR_WAITF;
      wutcounter++;  
    } while((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));
    
    if ((RTCx->ISR & RTC_ISR_WAITF) == RESET)
    {
      status = ERROR;
    }
    else
    {
      /* Reset all RTC CR register bits */
      RTCx->CR    &= (uint32_t)0x00000000;
      RTCx->CLKCR &= (uint32_t)0x00000000;
      RTCx->TIME  &= (uint32_t)0x00000000;
      RTCx->DATE  &= (uint32_t)0x00000000;
      RTCx->ALTIME&= (uint32_t)0x00000000;        
      RTCx->ALDATE&= (uint32_t)0x00000000;
      RTCx->ALPR  &= (uint32_t)0x00000000;
      RTCx->CKTR  &= (uint32_t)0x00000000;
      RTCx->INTCLR = (uint32_t)0x00000000;
      
      if(RTC_WaitForSynchro(RTC) == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;      
      }
    }
  }
  
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF;  
  
  return status;


}

/**
  * @brief  Initializes the RTC registers according to the specified parameters 
  *         in RTC_InitStruct.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure that contains 
  *         the configuration information for the RTC peripheral.
  * @note   The RTC Prescaler register is write protected and can be written in 
  *         initialization mode only.  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are initialized
  *          - ERROR: RTC registers are not initialized  
  */
ErrorStatus RTC_Init(RTC_TypeDef *RTCx,RTC_InitTypeDef* RTC_InitStruct)
{
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
  assert_param(IS_RTC_ASYNCH_PREDIV(RTC_InitStruct->RTC_AsynchPrediv));


  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;
	
	 /* Configure the RTC PRER */
	RTCx->CLKCR &= ~RTC_AsynchPrediv_mask;
	RTCx->CLKCR |= (uint32_t)(RTC_InitStruct->RTC_AsynchPrediv);
	
		/* Configure the RTC PRER */
	RTCx->CLKCR &= ~RTC_ClkSelMask;
	RTCx->CLKCR |= (uint32_t)(RTC_InitStruct->RTC_ClkSelect);

  /* Set Initialization mode */
  if (RTC_EnterInitMode(RTC) == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Clear RTC CR FMT Bit */
    RTCx->CR &= ((uint32_t)~(RTC_HourFormat_24));
    /* Set RTC_CR register */
    RTCx->CR |=  ((uint32_t)(RTC_InitStruct->RTC_HourFormat));
  
    /* Exit Initialization mode */
    RTC_ExitInitMode(RTC);

    status = SUCCESS;    
  }
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
  
  return status;
}

/**
  * @brief  Fills each RTC_InitStruct member with its default value.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure which will be 
  *         initialized.
  * @retval None
  */
void RTC_StructInit(RTC_TypeDef *RTCx,RTC_InitTypeDef* RTC_InitStruct)
{
  /* Initialize the RTC_HourFormat member */
  RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24;
    
  /* Initialize the RTC_AsynchPrediv member */
  RTC_InitStruct->RTC_AsynchPrediv = (uint32_t)0x3FF;

  /* Initialize the RTC_SynchPrediv member */
  RTC_InitStruct->RTC_ClkSelect = (uint32_t)RTC_CLK_LXT; 
}

/**
  * @brief  Enables or disables the RTC registers write protection.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the write protection.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WriteProtectionCmd(RTC_TypeDef *RTCx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState != DISABLE)
  {
    /* Enable the write protection for RTC registers */
    RTCx->WPR = 0xFF;   
  }
  else
  {
    /* Disable the write protection for RTC registers */
    RTCx->WPR = 0xCA;
    RTCx->WPR = 0x53;    
  }
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @note   The RTC Initialization mode is write protected, use the 
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.    
  * @param  RTCx: selects the RTC peripheral
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC is in Init mode
  *          - ERROR: RTC is not in Init mode  
  */
ErrorStatus RTC_EnterInitMode(RTC_TypeDef *RTCx)
{
  __IO uint32_t initcounter = 0x00;
  ErrorStatus status = ERROR;
  uint32_t initstatus = 0x00;
 
   /* Set the Initialization mode */
  /* Check if the Initialization mode is set */
  if ((RTCx->ISR & RTC_ISR_WAITF) == (uint32_t)RESET)
	{
	  /* Set the Initialization mode */
    RTCx->ISR  &= ~(uint32_t)RTC_ISR_WAIT;
		RTCx->ISR  |=  (uint32_t)RTC_ISR_WAIT;
		
	  /* Wait till RTC is in INIT state and if Time out is reached exit */
    do
    {
      initstatus = RTCx->ISR & RTC_ISR_WAITF;
      initcounter++;  
    } while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));
		
		if ((RTCx->ISR & RTC_ISR_WAITF) != RESET)
    {
      status = SUCCESS;
    }
    else
    {
      status = ERROR;
    }        
	}
	else
  {
      status = SUCCESS;  
  } 
    
  return (status);  
}

/**
  * @brief  Exits the RTC Initialization mode.
  * @note   When the initialization sequence is complete, the calendar restarts 
  *         counting after 4 RTCCLK cycles.  
  * @note   The RTC Initialization mode is write protected, use the 
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.      
  * @param  RTCx: selects the RTC peripheral
  * @retval None
  */
void RTC_ExitInitMode(RTC_TypeDef *RTCx)
{ 
	 __IO uint32_t initcounter = 0x00;
  uint32_t initstatus = 0x00;
  /* Exit Initialization mode */
  RTCx->ISR &= (uint32_t)~RTC_ISR_WAIT;  
	/* Wait till RTC is in INIT state and if Time out is reached exit */
	do
	{
		initstatus = RTCx->ISR & RTC_ISR_WAITF;
		initcounter++;  
	} while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x01));
}

/**
  * @brief  Waits until the RTC Time and Date registers (RTC_TR and RTC_DR) are 
  *         synchronized with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the 
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function. 
  * @note   To read the calendar through the shadow registers after Calendar 
  *         initialization, calendar update or after wakeup from low power modes 
  *         the software must first clear the RSF flag. 
  *         The software must then wait until it is set again before reading 
  *         the calendar, which means that the calendar registers have been 
  *         correctly copied into the RTC_TR and RTC_DR shadow registers.   
  * @param  RTCx: selects the RTC peripheral
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are synchronised
  *          - ERROR: RTC registers are not synchronised
  */
ErrorStatus RTC_WaitForSynchro(RTC_TypeDef *RTCx)
{
  __IO uint32_t synchrocounter = 0;
  ErrorStatus status = ERROR;
  uint32_t synchrostatus = 0x00;

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;
    
  /* Clear RSF flag */
  RTCx->ISR &= (uint32_t)RTC_RSF_MASK;
    
  /* Wait the registers to be synchronised */
  do
  {
    synchrostatus = RTCx->ISR & RTC_ISR_RSF;
    synchrocounter++;  
  } while((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));
    
  if ((RTCx->ISR & RTC_ISR_RSF) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }        

  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
    
  return (status); 
}
/**
  * @brief  Enables or disables the RTC clock to be output through the relative pin.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the digital calibration Output.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_RtcClkCmd(RTC_TypeDef *RTCx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;
  
  if (NewState != DISABLE)
  {
    /* Enable the RTC clock output */
    RTCx->CLKCR |= (uint32_t)RTC_Clk_Enable;
  }
  else
  { 
    /* Disable the RTC clock output */
    RTCx->CLKCR &= (uint32_t)~RTC_Clk_Enable;
  }
  
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
}


/**
  * @brief  Enables or disables the RTC clock to be output through the relative pin.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTCClk: set the rtc clk parameter
  * @retval None
  */
void RTC_SelRtcClk(RTC_TypeDef *RTCx,uint32_t RTCClk)
{
  /* Check the parameters */
  assert_param(IS_RTC_CLK_SEL(RTCClk));
  
  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

	/* Enable the RTC clock output */
	RTCx->CLKCR  &= ~(uint32_t)RTC_ClkSelMask;
	RTCx->CLKCR  |= (uint32_t)RTCClk;
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
}
/**
  * @brief  Enables or Disables the Bypass Shadow feature.
  * @note   When the Bypass Shadow is enabled the calendar value are taken 
  *         directly from the Calendar counter.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the Bypass Shadow feature.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
*/
void RTC_BypassShadowCmd(RTC_TypeDef *RTCx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;
  
  if (NewState != DISABLE)
  {
    /* Set the BYPSHAD bit */
    RTCx->CR |= (uint32_t)RTC_CR_BYPSHAD;
  }
  else
  {
    /* Reset the BYPSHAD bit */
    RTCx->CR &= (uint32_t)~RTC_CR_BYPSHAD;
  }

  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF;
}

/**
  * @brief  Set the RTC current time.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format 
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that contains 
  *                        the time configuration information for the RTC.     
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Time register is configured
  *          - ERROR: RTC Time register is not configured
  */
ErrorStatus RTC_SetTime(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
  uint32_t tmpreg = 0;
  ErrorStatus status = ERROR;
    
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  
  if (RTC_Format == RTC_Format_BIN)
  {
    if ((RTCx->CR & RTC_HourFormat_24) == (uint32_t)RESET)
    {
      assert_param(IS_RTC_HOUR12(RTC_TimeStruct->RTC_Hours));
      assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
			
    } 
    else
    {
      assert_param(IS_RTC_HOUR24(RTC_TimeStruct->RTC_Hours));		
    }
    assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
  }
  else
  {
    if ((RTCx->CR & RTC_HourFormat_24) == (uint32_t)RESET)
    {
      assert_param(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours));
      assert_param(IS_RTC_HOUR12(tmpreg));
      assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12)); 
    } 
    else
    {
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
    }
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds)));
  }
  
  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpreg = (((uint32_t)(RTC_TimeStruct->RTC_WeekDay) << 24) |
		         ((uint32_t)(RTC_TimeStruct->RTC_Hours) << 16) | \
             ((uint32_t)(RTC_TimeStruct->RTC_Minutes) << 8) | \
             ((uint32_t)(RTC_TimeStruct->RTC_Seconds)) | \
             ((uint32_t)(RTC_TimeStruct->RTC_H12) << 21)); 
  }  
  else
  {
    tmpreg = (uint32_t)(((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_WeekDay) << 24)|
		               ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Hours) << 16) | \
                   ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Minutes) << 8) | \
                   ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Seconds)) | \
                   ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_H12) << 21));
  }  

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode(RTC) == ERROR)
  {
    status = ERROR;
  } 
  else
  {
  /* Set the RTC_TR register */
    RTCx->TIME = (uint32_t)(tmpreg & RTC_TR_RESERVED_MASK);

    /* Exit Initialization mode */
    RTC_ExitInitMode(RTC); 

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if ((RTCx->CR & RTC_CR_BYPSHAD) == RESET)
    {
    if(RTC_WaitForSynchro(RTC) == ERROR)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }
  }
    else
    {
      status = SUCCESS;
    }
  }
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
  
  return status;
}

/**
  * @brief  Fills each RTC_TimeStruct member with its default value
  *         (Time = 00h:00min:00sec).
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure which will be 
  *         initialized.
  * @retval None
  */
void RTC_TimeStructInit(RTC_TypeDef *RTCx,RTC_TimeTypeDef* RTC_TimeStruct)
{
  /* Time = 00h:00min:00sec */
  RTC_TimeStruct->RTC_H12 = RTC_H12_AM;
  RTC_TimeStruct->RTC_Hours = 0;
  RTC_TimeStruct->RTC_Minutes = 0;
  RTC_TimeStruct->RTC_Seconds = 0; 
	RTC_TimeStruct->RTC_WeekDay = 0;
}

/**
  * @brief  Get the RTC current Time.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format 
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that will 
  *                        contain the returned current time configuration.     
  * @retval None
  */
void RTC_GetTime(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(RTCx->TIME & RTC_TR_RESERVED_MASK); 

		if((RTCx->CR & RTC_HourFormat_24) == RTC_HourFormat_24)
		{
				RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & RTC_TR_HU_24) >> 16);
		} else {
			  RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & RTC_TR_HU) >> 16);
		}
		/* Fill the structure fields with the read parameters */
		RTC_TimeStruct->RTC_WeekDay = (uint8_t)((tmpreg & RTC_TR_WEEKDAY) >> 24);
	
		RTC_TimeStruct->RTC_Minutes = (uint8_t)((tmpreg & RTC_TR_MNU) >>8);
		RTC_TimeStruct->RTC_Seconds = (uint8_t)(tmpreg & RTC_TR_SU);
		RTC_TimeStruct->RTC_H12 = (uint8_t)((tmpreg & (RTC_TTME_H20PA)) >> 21); 
    
	
		if (RTC_Format == RTC_Format_BIN)
	  {
			/* Convert the structure parameters to Binary format */
			RTC_TimeStruct->RTC_WeekDay = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_WeekDay);
			RTC_TimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
			RTC_TimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes);
			RTC_TimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds);  
			RTC_TimeStruct->RTC_H12 = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_H12); 		
		}
 
}



/**
  * @brief  Set the RTC current date.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format 
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure that contains 
  *                         the date configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Date register is configured
  *          - ERROR: RTC Date register is not configured
  */
ErrorStatus RTC_SetDate(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
  uint32_t tmpreg = 0;
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  if ((RTC_Format == RTC_Format_BIN) && ((RTC_DateStruct->RTC_Month & 0x10) == 0x10))
  {
    RTC_DateStruct->RTC_Month = (RTC_DateStruct->RTC_Month & (uint32_t)~(0x10)) + 0x0A;
  }  
  if (RTC_Format == RTC_Format_BIN)
  {
    assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
    assert_param(IS_RTC_MONTH(RTC_DateStruct->RTC_Month));
    assert_param(IS_RTC_DATE(RTC_DateStruct->RTC_Date));
  }
  else
  {
    assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year)));
    tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
    assert_param(IS_RTC_MONTH(tmpreg));
    tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
    assert_param(IS_RTC_DATE(tmpreg));
  }


  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpreg = ((((uint32_t)RTC_DateStruct->RTC_Year) << 16) | \
		          ((uint32_t)RTC_DateStruct->RTC_Century << 15)|\
              (((uint32_t)RTC_DateStruct->RTC_Month) << 8) | \
              ((uint32_t)RTC_DateStruct->RTC_Date));     
  }  
  else
  {
    tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Year) << 16) | \
		          ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Century) << 15)|\
              ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Month) << 8) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Date))); 
  }

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode(RTC) == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Set the RTC_DR register */
		RTCx->DATE  = (uint32_t)(tmpreg & RTC_DATE_RESERVED_MASK);
    /* Exit Initialization mode */
    RTC_ExitInitMode(RTC); 

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if ((RTCx->CR & RTC_CR_BYPSHAD) == RESET)
    {
    if(RTC_WaitForSynchro(RTC) == ERROR)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }
  }
    else
    {
      status = SUCCESS;
    }
  }
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF;   
  
  return status;
}

/**
  * @brief  Fills each RTC_DateStruct member with its default value
  *         (Monday, January 01 xx00).
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure which will be 
  *         initialized.
  * @retval None
  */
void RTC_DateStructInit(RTC_TypeDef *RTCx,RTC_DateTypeDef* RTC_DateStruct)
{
  /* Monday, January 01 xx00 */
  RTC_DateStruct->RTC_Date = 1;
  RTC_DateStruct->RTC_Month = RTC_Month_January;
  RTC_DateStruct->RTC_Year = 0;
	RTC_DateStruct->RTC_Century = 0;
}

/**
  * @brief  Get the RTC current date. 
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format 
  *            @arg RTC_Format_BCD: BCD data format
  * @param RTC_DateStruct: pointer to a RTC_DateTypeDef structure that will 
  *                        contain the returned current date configuration.     
  * @retval None
  */
void RTC_GetDate(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  
  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(RTCx->DATE & RTC_DATE_RESERVED_MASK); 
	

  /* Fill the structure fields with the read parameters */
  RTC_DateStruct->RTC_Year = (uint8_t)((tmpreg &  RTC_DR_YU) >> 16);
	RTC_DateStruct->RTC_Century = (uint8_t)((tmpreg &  RTC_DR_CEN) >> 15);
  RTC_DateStruct->RTC_Month = (uint8_t)((tmpreg & RTC_DR_MU) >> 8);
  RTC_DateStruct->RTC_Date = (uint8_t)(tmpreg &   RTC_DR_DU);
	
  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_DateStruct->RTC_Year = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year);
    RTC_DateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
    RTC_DateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
		RTC_DateStruct->RTC_Century = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Century);
  }
}

/**
  * @brief  Set the specified RTC Alarm.
  * @param  RTCx: selects the RTC peripheral
  * @note   The Alarm register can only be written when the corresponding Alarm
  *         is disabled (Use the RTC_AlarmCmd(DISABLE)).    
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format 
  *            @arg RTC_Format_BCD: BCD data format
  * @param  RTC_AlarmEableStruct: pointer to a RTC_AlarmTypeDef structure that 
  *         contains the alarm configuration parameters. 
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that 
  *                          contains the alarm configuration parameters.     
  * @retval None
  */
void RTC_SetAlarm1(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_AlarmTypeEnableDef*RTC_AlarmEableStruct, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  uint32_t tmpreg = 0;
	uint32_t tmpreg1 = 0;
	
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
	
	/* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

	
	/*alarm hour set*/
	if(RTC_AlarmEableStruct->RTC_HourAlarmEable == ENABLE)
	{
		if ((RTCx->CR & RTC_HourFormat_24) == (uint32_t)RESET)
		{
			assert_param(IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
			assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
		} 
		else
		{
			assert_param(IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
		}
		
		tmpreg1 |= RTC_AlarmHour_ENABLE;
		if (RTC_Format == RTC_Format_BIN) //bin data
		{
			tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16;
			tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 21;
		} else {        //bcd data
			tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours << 16;
			tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 << 21;
		}
		
	} else{
	  
		tmpreg1 &= ~RTC_AlarmHour_ENABLE;
	}
	
	/*alarm minuter set*/
	if(RTC_AlarmEableStruct->RTC_MinAlarmEable == ENABLE)
	{
		assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));

		tmpreg1 |= RTC_AlarmMin_ENABLE;
		
		if (RTC_Format == RTC_Format_BIN) //bin data
			tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8;
		else  //bcd data
			tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes << 8;
		
	} else {
	 
		tmpreg1 &= ~RTC_AlarmMin_ENABLE;
	}
	
	/*alarm sec set*/
	if(RTC_AlarmEableStruct->RTC_SecAlarmEable == ENABLE)
	{
		assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));
	
		tmpreg1 |= RTC_AlarmSec_ENABLE;
		
		if (RTC_Format == RTC_Format_BIN)
			tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds);
		else
			tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds;
		
	} else {

		tmpreg1 &= ~RTC_AlarmSec_ENABLE;
	}
	
	/*alarm weekday set*/
	if(RTC_AlarmEableStruct->RTC_WeekAlarmEable == ENABLE)
	{
		assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
	
		tmpreg1 |= RTC_AlarmWeek_ENABLE;
		
		if (RTC_Format == RTC_Format_BIN)
			tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay) << 24;
		else
			tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay<<24;
		
	} else{
	
		tmpreg1 &= ~RTC_AlarmWeek_ENABLE;
	}
	
	/*alarm year set*/
	if(RTC_AlarmEableStruct->RTC_YearAlarmEable == ENABLE)
	{
		assert_param(IS_RTC_YEAR(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year));
	
		tmpreg1 |= RTC_AlarmYear_ENABLE;
		
		if (RTC_Format == RTC_Format_BIN)
		{
			tmpreg1 |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year) << 16;
			tmpreg1 |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Century) << 15;
		} else {
			tmpreg1 |= (uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Year << 16;
			tmpreg1 |= (uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Century << 15;
		}				
	} else {
	
		tmpreg1 &= ~RTC_AlarmYear_ENABLE;
	}
	
	/*alarm month set*/
	if(RTC_AlarmEableStruct->RTC_MonthAlarmEable == ENABLE)
	{
		assert_param(IS_RTC_MONTH(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month));
	
		tmpreg1 |= RTC_AlarmMon_ENABLE;

		if (RTC_Format == RTC_Format_BIN)
		{
			tmpreg1 |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month) << 8;
		}
		else
		{
			tmpreg1 |= (uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Month << 8;	
		}
		
	} else{
		
		 tmpreg1 &= ~RTC_AlarmMon_ENABLE;
	}
	
	/*alarm date set*/
	if(RTC_AlarmEableStruct->RTC_DateAlarmEable == ENABLE)
	{
		assert_param(IS_RTC_DATE(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date));

		tmpreg1 |= RTC_AlarmDay_ENABLE;
		
		if (RTC_Format == RTC_Format_BIN)
		{
			tmpreg1 |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date);
		}
		else
			tmpreg1 |= (uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Date;
		
	} else{

		 tmpreg1 &= ~RTC_AlarmDay_ENABLE;		
	}
	
 
	/*write register*/
	RTCx->ALTIME = tmpreg;
	RTCx->ALDATE = tmpreg1;
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF;   
}


/**
  * @brief  Set the specified RTC Alarm.
  * @param  RTCx: selects the RTC peripheral       
  * @param  value: set the value of ALPR
  * @retval None
  */
void RTC_SetAlarm2(RTC_TypeDef *RTCx,uint32_t value)
{
	/* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;
	/*set the value to the ALPR*/
	RTCx->ALPR = value;
	RTCx->WPR = 0xFF;
}

/**
  * @brief  Fills each RTC_AlarmStruct member with its default value
  *         (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
  *         all fields are masked).
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_AlarmStruct: pointer to a @ref RTC_AlarmTypeDef structure which
  *         will be initialized.
  * @retval None
  */
void RTC_AlarmStructInit(RTC_TypeDef *RTCx,RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  /* Alarm Time Settings : Time = 00h:00mn:00sec */
  RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;
	RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = 0;
	RTC_AlarmStruct->RTC_AlarmDate.RTC_Century = 0;
	RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = 0;
	RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = 0;
}

/**
  * @brief  Get the RTC Alarm value and masks.
  * @param  RTC_Format: specifies the format of the output parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format 
  *            @arg RTC_Format_BCD: BCD data format
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that will 
  *                          contains the output alarm configuration values.     
  * @retval None
  */
void RTC_GetAlarm1(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
   uint32_t tmpregtime = 0;
	 uint32_t tmpregdate = 0;

	
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  assert_param(IS_RTC_ALARM(RTC_Alarm)); 

  /* Get the RTC_ALRMxR register */
  
	tmpregtime = (uint32_t)(RTCx->ALTIME)&RTC_AlarmMask_time;
	tmpregdate = (uint32_t)(RTCx->ALDATE)&RTC_AlarmMask_date;

  /* Fill the structure with the read parameters */
	RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = (uint32_t)((tmpregtime & RTC_AlarmMask_PA) >> 21);
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint32_t)((tmpregtime & RTC_AlarmMask_Hours) >> 16);
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint32_t)((tmpregtime & RTC_AlarmMask_Minutes) >> 8);
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint32_t)(tmpregtime & RTC_AlarmMask_Seconds);
  RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay = (uint32_t)((tmpregtime & RTC_AlarmMask_Week) >> 24);
	RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = (uint32_t)((tmpregdate & RTC_AlarmMask_Year) >> 16);
	RTC_AlarmStruct->RTC_AlarmDate.RTC_Century = (uint32_t)((tmpregdate & RTC_AlarmMask_ALCEN) >> 15);
	RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = (uint32_t)((tmpregdate & RTC_AlarmMask_Mouth) >> 8);
	RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = (uint32_t)(tmpregdate & RTC_AlarmMask_Day);
	
	/*BIN TO BCD */
  if (RTC_Format == RTC_Format_BIN)
  {
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
		RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay);
		RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year);
		RTC_AlarmStruct->RTC_AlarmDate.RTC_Century = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Century);
		RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month);
		RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date);
  }  
}

/**
  * @brief  Enables or disables the specified RTC Alarm.
  * @param  RTCx: selects the RTC peripheral
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Alarm is enabled/disabled
  *          - ERROR: RTC Alarm is not enabled/disabled  
  */
uint8_t RTC_GetAlarm2(RTC_TypeDef *RTCx)
{
   return  (uint8_t)(RTCx->ALPR);
}
/**
  * @brief  Enables or disables the specified RTC Alarm.
  * @param  RTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  *            @arg RTC_Alarm_B: to select Alarm B  
  * @param  NewState: new state of the specified alarm.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_AlarmCmd(RTC_TypeDef *RTCx,uint32_t RTC_Alarm, FunctionalState NewState)
{
  __IO uint32_t alarmcounter = 0x00;
  /* Check the parameters */
  assert_param(IS_RTC_GET_IT(RTC_Alarm));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

  /* Configure the Alarm state */
  if (NewState != DISABLE)
  {
    RTCx->CR |= (uint32_t)RTC_Alarm;
   
  }else {
		RTCx->CR &= (uint32_t)~RTC_Alarm;
		
   
		
	}
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
  

}

/**
  * @brief  Configures the Coarse calibration parameters.
  * @param  RTC_CalibSign: specifies the sign of the coarse calibration value.
  *          This parameter can be  one of the following values:
  *            @arg RTC_CalibSign_Positive: The value sign is positive 
  *            @arg RTC_CalibSign_Negative: The value sign is negative
  * @param  Value: value of coarse calibration expressed in ppm (coded on 5 bits).
  *    
  * @note   This Calibration value should be between 0 and 63 when using negative
  *         sign with a 2-ppm step.
  *           
  * @note   This Calibration value should be between 0 and 126 when using positive
  *         sign with a 4-ppm step.
  *           
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Coarse calibration are initialized
  *          - ERROR: RTC Coarse calibration are not initialized     
  */
ErrorStatus RTC_CoarseCalibConfig(RTC_TypeDef *RTCx,uint32_t RTC_CalibSign, uint32_t Value)
{
  ErrorStatus status = ERROR;
   
  /* Check the parameters */
  assert_param(IS_RTC_CALIB_SIGN(RTC_CalibSign));
  assert_param(IS_RTC_CALIB_VALUE(Value)); 

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode(RTC) == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Set the coarse calibration value */
    RTCx->CKTR = (uint32_t)(RTC_CalibSign | Value);
    /* Exit Initialization mode */
    RTC_ExitInitMode(RTC);
    
    status = SUCCESS;
  } 

  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
  
  return status;
}



/**
  * @brief  Enables or disables the RTC clock to be output through the relative pin.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the digital calibration Output.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_CalibOutputCmd(RTC_TypeDef *RTCx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;
  
  if (NewState != DISABLE)
  {
    /* Enable the RTC clock output */
    RTCx->CR |= (uint32_t)RTC_CalibOutput_1Hz;
  }
  else
  { 
    /* Disable the RTC clock output */
    RTCx->CR &= (uint32_t)~RTC_CalibOutput_1Hz;
  }
  
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
}


/**
  * @brief  Enables or disables the RTC Count.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the digital calibration Output.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_CountCmd(RTC_TypeDef *RTCx,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;
  
  if (NewState != DISABLE)
  {
    /* Enable the RTC clock output */
    RTCx->CR |= (uint32_t)RTC_Count_Enable;
  }
  else
  { 
    /* Disable the RTC clock output */
    RTCx->CR &= (uint32_t)~RTC_Count_Enable;
  }
  
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
}




/**
  * @brief  Configures the Smooth Calibration Settings.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_SmoothCalibPeriod : Select the Smooth Calibration Period.
  *   This parameter can be can be one of the following values:
  *     @arg RTC_SmoothCalibPeriod_32sec : The smooth calibration period is 32s.
  *     @arg RTC_SmoothCalibPeriod_16sec : The smooth calibration period is 16s.
  *     @arg RTC_SmoothCalibPeriod_8sec  : The smooth calibartion period is 8s.
  * @param  RTC_SmoothCalibTrmingValue: Set the value to TRIM
  * @retval None
*/
void RTC_SmoothCalibConfig(RTC_TypeDef *RTCx,uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibTrmingValue)
{
  /* Check the parameters */
  assert_param(IS_RTC_SMOOTH_CALIB_PERIOD(RTC_SmoothCalibPeriod));
  assert_param(IS_RTC_SMOOTH_CALIB_TRMINGVALUE(RTC_SmoothCalibTrmingValue));

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;
  
	/* Configure the Smooth calibration settings */
	RTCx->CKTR = (uint32_t)((uint32_t)RTC_SmoothCalibPeriod | (uint32_t)RTC_SmoothCalibTrmingValue );

  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF;
}

/**@brief   Interrupts and flags management functions
  * @param  RTCx: selects the RTC peripheral  
  * @param  RTC_IT: specifies the rtc interrupt parameter to config. 
  * @param  NewState: new state of the digital calibration Output.
  *         This parameter can be: ENABLE or DISABLE.
 */
void RTC_AlprITConfig(RTC_TypeDef *RTCx,uint32_t RTC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_CONFIG_IT(RTC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

  if (NewState != DISABLE)
  {
    /* Configure the Interrupts in the RTC_CR register */
    RTCx->CR |= (uint32_t)RTC_IT;
 
  }
  else
  {
		 /* Configure the Interrupts in the RTC_CR register */
     RTCx->CR &= ~(uint32_t)RTC_IT;
  }
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
}

/**
  * @brief  Alm and flags management functions
  * @param  RTCx: selects the RTC peripheral  
  * @param  RTC_IT: specifies the RTC interrupt sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_TS:  Time Stamp interrupt mask
  *            @arg RTC_IT_WUT:  WakeUp Timer interrupt mask
  *            @arg RTC_IT_ALRB:  Alarm B interrupt mask
  *            @arg RTC_IT_ALRA:  Alarm A interrupt mask
  *            @arg RTC_IT_TAMP: Tamper event interrupt mask
  * @param  NewState: new state of the specified RTC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_AlmITConfig(RTC_TypeDef *RTCx,uint32_t RTC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_CONFIG_IT(RTC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

  if (NewState != DISABLE)
  {
    /* Configure the Interrupts in the RTC_CR register */
    RTCx->CR |= (uint32_t)RTC_IT;
 
  }
  else
  {
		 /* Configure the Interrupts in the RTC_CR register */
     RTCx->CR &= ~(uint32_t)RTC_IT;
  }
  /* Enable the write protection for RTC registers */
  RTCx->WPR = 0xFF; 
}


/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTCx: selects the RTC peripheral  
  * @param  RTC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg RTC_IT_ALM1: ALM1 event flag.
  *            @arg RTC_IT_ALM2: ALM2 event flag.
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
FlagStatus RTC_GetFlagStatus(RTC_TypeDef *RTCx,uint32_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG));
    
  /* Return the status of the flag */
  if ((RTCx->ISR & RTC_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the RTC's pending flags.
  * @param  RTCx: selects the RTC peripheral 
  * @param  RTC_FLAG: specifies the RTC flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_ALM1: ALM1 event flag.
  *            @arg RTC_IT_ALM2: ALM2 event flag.
  * @retval None
  */
void RTC_ClearFlag(RTC_TypeDef *RTCx,uint32_t RTC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));
	
	/* Disable the write protection for RTC registers */
  RTCx->WPR = 0xCA;
  RTCx->WPR = 0x53;

  /* Clear the Flags in the RTC_ISR register */
  RTCx->INTCLR  =  RTC_FLAG ;
	
	/* Enable the write protection for RTC registers */
	RTCx->WPR = 0xFF;
}

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTCx: selects the RTC peripheral 
  * @param  RTC_IT: specifies the RTC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg RTC_IT_ALM1: ALM1 event flag.
  *            @arg RTC_IT_ALM2: ALM2 event flag.
  * @retval The new state of RTC_IT (SET or RESET).
  */
ITStatus RTC_GetITStatus(RTC_TypeDef *RTCx,uint32_t RTC_IT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RTC_GET_IT(RTC_IT));
  
  /* Get the status of the Interrupt */
  if (RTCx->ISR & RTC_IT)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}
/************************ (C) COPYRIGHT XMC *****END OF FILE****/

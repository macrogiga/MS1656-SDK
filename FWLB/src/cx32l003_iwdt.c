

/**
  ******************************************************************************
  * @file    cx32l003_iwdg.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Independent watchdog (IWDG) peripheral:           
  *           + Prescaler and Counter configuration
  *           + IWDG activation
  *           + Flag management
  *
    @verbatim    
 ===============================================================================
                          ##### IWDG features #####
 ===============================================================================
    [..]  
      The IWDG can be started by either software or hardware (configurable
      through option byte).
              
      The IWDG is clocked by its own dedicated low-speed clock (LSI) and
      thus stays active even if the main clock fails.
      Once the IWDG is started, the LSI is forced ON and cannot be disabled
      (LSI cannot be disabled too), and the counter starts counting down from 
      the reset value of 0xFFF. When it reaches the end of count value (0x000)
      a system reset is generated.
      The IWDG counter should be reloaded at regular intervals to prevent
      an MCU reset.
                             
      The IWDG is implemented in the VDD voltage domain that is still functional
      in STOP and STANDBY mode (IWDG reset can wake-up from STANDBY).          
              
      IWDGRST flag in RCC_CSR register can be used to inform when a IWDG
      reset occurs.
              
      Min-max timeout value @32KHz (LSI): ~125us / ~32.7s
      The IWDG timeout may vary due to LSI frequency dispersion. STM32F4xx
      devices provide the capability to measure the LSI frequency (LSI clock
      connected internally to TIM5 CH4 input capture). The measured value
      can be used to have an IWDG timeout with an acceptable accuracy. 
      For more information, please refer to the STM32F4xx Reference manual
            
                     ##### How to use this driver #####
 ===============================================================================
    [..]
      (#) Enable write access to IWDG_PR and IWDG_RLR registers using
          IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable) function
                 
      (#) Configure the IWDG prescaler using IWDG_SetPrescaler() function
              
      (#) Configure the IWDG counter value using IWDG_SetReload() function.
          This value will be loaded in the IWDG counter each time the counter
          is reloaded, then the IWDG will start counting down from this value.
              
      (#) Start the IWDG using IWDG_Enable() function, when the IWDG is used
          in software mode (no need to enable the LSI, it will be enabled
          by hardware)
               
      (#) Then the application program must reload the IWDG counter at regular
          intervals during normal operation to prevent an MCU reset, using
          IWDG_ReloadCounter() function.      
            
    @endverbatim    
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_iwdt.h"
#include "cx32l003_rcc.h"

uint8_t iwdt_flg;

/** @defgroup IWDG_Group1 Prescaler and Counter configuration functions
 *  @brief   Prescaler and Counter configuration functions
 *
@verbatim   
 ===============================================================================
              ##### Prescaler and Counter configuration functions #####
 ===============================================================================  
  *
  * @brief  Enables or disables write access to IWDG_PR and IWDG_RLR registers.
  * @param  IWDG_WriteAccess: new state of write access to IWDG_PR and IWDG_RLR registers.
  *          This parameter can be one of the following values:
  *            @arg IWDG_WriteAccess_Enable: Enable write access to IWDG_PR and IWDG_RLR registers
  *            @arg IWDG_WriteAccess_Disable: Disable write access to IWDG_PR and IWDG_RLR registers
  * @retval None
  */
void IWDG_WriteAccessCmd(uint32_t IWDG_WriteAccess)
{
  /* Check the parameters */
  assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
  IWDG->LOCK = IWDG_WriteAccess;
}


/**
  * @brief  Sets IWDG Reload value.
  * @param  Reload: specifies the IWDG Reload value.
  *          This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  */
void IWDG_SetReload(uint32_t Reload)
{
  /* Check the parameters */
  assert_param(IS_IWDG_RELOAD(Reload));
	/*Set the value to the RLOAD Register*/
  IWDG->RLOAD = Reload;
}


/**
  * @brief  Sets the mode of IWDG
  * @param  Mode: specifies the IWDG Mode.
  * @retval None
  */
void IWDG_SetWdtMode(uint32_t Mode)
{
  /* Check the parameters */
	if(Mode == COMMAND_WDT_INT)
		IWDG->CFG |= COMMAND_WDT_INT;
	else
	 IWDG->CFG &= ~COMMAND_WDT_INT;
}

/**
  * @brief  Gets IWDG Reload value.
  * @param  None
  * @retval None
  */
uint32_t IWDG_GetReload(void)
{
  /* Check the parameters */
  return  (uint32_t)(IWDG->CNTVAL);
}

/**
  * @brief  Reloads IWDG counter with value defined in the reload register
  *         (write access to IWDG_PR and IWDG_RLR registers disabled).
  * @param  None
  * @retval None
  */
void IWDG_ReloadCounter(void)
{
  IWDG->COMMAND = COMMAND_IWDT_RELOAD;
}


/**
  * @brief  Enables IWDG (write access to Command registers disabled).
  * @param  None
  * @retval None
  */
void IWDG_Cmd(void)
{
	/*Set the vlaue to the command*/
  IWDG->COMMAND = COMMAND_IWDT_ENABLE;
}

/**
  * @brief  Enables IWDG (write access to Command registers disabled).
  * @param  None
  * @retval None
  */
void IWDG_RELOAD(void)
{
	/*Set the vlaue to the command*/
  IWDG->COMMAND = COMMAND_IWDT_RELOAD;
}

/**
  * @brief  Checks whether the specified IWDG flag is set or not.
  * @param  IWDG_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg IWDG_INT_FLAG: IWDG Interrupt Flags
  * @retval The new state of IWDG_FLAG (SET or RESET).
  */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  if ((IWDG->INTS & IWDG_FLAG) != (uint32_t)RESET)
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
  * @brief  Enable interrupt shield  function
  * @param  NewState: new state of the WWDG peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IWDG_WdtITShieldCmd(FunctionalState NewStatus)
{
	/*Enables the flag of iwdt interrupt*/
	if(NewStatus!= DISABLE)
	 IWDG->CFG |= COMMAND_WDTINTSHIELD_ENBLE;
  else
	/*Disables the flag of iwdt interrupt*/
	 IWDG->CFG &= ~COMMAND_WDTINTSHIELD_ENBLE;
}

/**
  * @brief  Clears the flag of IWDG
  * @param  None
  * @retval None
  */
void IWDG_WdtITClear(void)
{
	
	/*Clears the flag of IWDG*/
	IWDG->INTCLR = COMMAND_WDTINTCLR_ENBLE;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT XMC *****END OF FILE****/


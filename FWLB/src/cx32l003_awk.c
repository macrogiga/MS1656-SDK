/**
  ******************************************************************************
  * @file    cx32l003_awk.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides all the awk firmware functions.
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
#include "cx32l003_awk.h"
#include "cx32l003_rcc.h"



uint8_t awk_flg;


/**
  * @brief  Initializes the AWK peripheral according to the specified
  *         parameters in the AWK_InitStruct.
  * @param  AWKx:selects the AWK peripheral
  * @param  AWK_InitStruct:pointer to a AWK_InitTypeDef structure which will
  *         be initialized.       
  * @retval None
  */
void AWK_Init(AWK_TypeDef *AWKx, AWK_InitTypeDef* AWK_InitStruct)
{
	int tmpreg = 0;
	/*Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
	/*read the value of CR*/
	tmpreg = AWKx->CR;
	
	/*Clear the function bits to zero*/
	tmpreg &= AWK_CR_MASK;
	
	/*---------------------------- AWK CR Configuration ------------------------*/
	/*set the specified parameters */
	/*set AWK_XTLPRSC to the XTLPRSC*/
	/*set AWK_SeleteClkSource to the TCLKSEL*/
  /*set AWK_CounterClkDiv to the DIVSEL*/
	
	tmpreg |= ((AWK_InitStruct->AWK_XTLPRSC << 8)|\
	           (AWK_InitStruct->AWK_SeleteClkSource<<5)|\
	           (AWK_InitStruct->AWK_CounterClkDiv));
	
	/*set the value to CR register*/
	AWKx->CR = tmpreg;
}

/**
  * @brief  Enables or disables the specified AWK peripheral function.
  * @param  AWKx:selects the AWK peripheral
  * @param  NewState: new state of the AWK peripheral.
  * This parameter can be: ENABLE or DISABLE.     
  * @retval None
  */
void AWK_Cmd(AWK_TypeDef *AWKx,FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	/*---------------------------- AWK CMD ENABLE------------------------*/
	if(NewState != DISABLE)
		  /*Enable the awk peripheral*/
	    AWKx->CR |= AWK_ENABLE;
	else
		  /*Disalbe the awk peripheral*/
		  AWKx->CR &= ~AWK_ENABLE;
}

/**
  * @brief  Set the clk of AWK
  * @param  AWKx:selects the AWK peripheral
  * @param  AWKClk:
  *         
  * @retval None
  */
void AWK_SelClk(AWK_TypeDef *AWKx,uint8_t AWKClk)
{
	/* Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
	assert_param(IS_AWK_SELCLK(AWKClk));
	/*Select the awk clk*/
	AWKx->CR &= ~AWK_CLKMASK;
	AWKx->CR |= AWKClk;
}

/**
  * @brief  Setting up overloaded data registers
  * @param  AWKx: selects the AWK peripheral
  * @param  value: set the value to the register of RLDVAL        
  * @retval None
  */
void AWK_SetRldval(AWK_TypeDef *AWKx,uint8_t value)
{
	  /* Check the parameters */
	  assert_param(IS_AWK_ALL_PERIPH(AWKx));
	  /*Set the value to the register of RLDVAL*/
		AWKx->RLDVAL = value;
}

/**
  * @brief  Clear the IT Flag 
  * @param  AWKx: selects the AWK peripheral       
  * @retval None
  */
void AWK_ClearITFlag(AWK_TypeDef *AWKx)
{
	  /*Check the parameters */
	  assert_param(IS_AWK_ALL_PERIPH(AWKx));
	  /*Clear the TI Flag*/
		AWKx->INTCLR = AWK_TI_CLEAR;
}

/**
  * @}
  */

/**
  * @}
  */
/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/



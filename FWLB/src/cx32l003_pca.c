/**
  ******************************************************************************
  * @file    cx32l003_pca.c
  * @author  MCD Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the CRC firmware functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC </center></h2>
  *
  * Licensed under MCU Liberty SW License Agreement V2, (the "License");
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
#include  "cx32l003_pca.h"



uint8_t  pca_flg = 0;



/**
  * @brief  Initializes the PCA_CountTimerInit 
  *         the specified parameters in the PCA_CountTimerInitInitStruct.
  * @param  PCAx: Select the PCA peripheral.
  * @param  PCA_CountTimerInitInitStruct:pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the specified ADC peripheral.     
  * @retval None
  */
void PCA_CountTimerInit(PCA_TypeDef* PCAx, PCA_CountTimerInitTypeDef* PCA_CountTimerInitInitStruct)
{
	int tmpreg = 0;
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_PCA_FUNCTION(PCA_CountTimerInitInitStruct->PCA_CounterMode));
	assert_param(IS_PCA_PRESCALE_DIV(PCA_CountTimerInitInitStruct->PCA_ClockDivision));
	assert_param(IS_PCA_CNT_VALUE(PCA_CountTimerInitInitStruct->PCA_ThresholdCounter));
	
	/*Set clock */
	tmpreg = PCA_CountTimerInitInitStruct->PCA_ClockDivision;
	PCAx->CMOD  &= ~(pca_counterclk_mask);
	PCAx->CMOD |= tmpreg;
	
	/*Setting counting overflow threshold*/
	PCAx->CNT = PCA_CountTimerInitInitStruct->PCA_ThresholdCounter;
}

/**
  * @brief  enable the PCA_CountTimercmd 
  *         the specified parameters in the PCA_CountTimerInitInitStruct.
  * @param  PCAx: Select the PCA peripheral.
  * @param  NewState: new state of the ADCx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.     
  * @retval None
  */
void PCA_CountTimercmd(PCA_TypeDef* PCAx, FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
  if(NewState != DISABLE)
		/*enable the PCA_CountTimercmd */
		PCAx->CCON |= PCA_CR_ENABLE;
	else
		/*disable the PCA_CountTimercmd */
		PCAx->CCON &= ~PCA_CR_ENABLE;	
}

/**
  * @brief  enable the PCA_Count Timer interrupt
  *         the specified parameters in the PCA_CountTimerInitInitStruct.
  * @param  PCAx: Select the PCA peripheral.
  * @param  NewState: new state of the ADCx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.     
  * @retval None
  */
void PCA_CountTimerITCmd(PCA_TypeDef* PCAx, FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
  if(NewState != DISABLE)
		/*enable the PCA_Count Timer interrupt*/
		PCAx->CMOD |= PCA_TI_ENABLE;
	else
		/*disable the PCA_Count Timer interrupt*/
		PCAx->CMOD &= ~PCA_TI_ENABLE;	
}

/**
  * @brief  Initializes the PCA capture function
  *         the specified parameters in the PCA_CountTimerInitInitStruct.
  * @param  PCAx: Set the PCA peripheral.
  * @param  PCA_ICInitStruct: pointer to an PCA_ICInitStruct structure that contains
  *         the configuration information for the specified PCA peripheral.  
  * @retval None
  */
void PCA_CaptureInit(PCA_TypeDef* PCAx, PCA_ICInitTypeDef* PCA_ICInitStruct)
{
	int tmpreg = 0;
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_PCA_CAP_Edge(PCA_ICInitStruct->PCA_ICPolarity));
	assert_param(IS_PCA_CHANNEL(PCA_ICInitStruct->PCA_Channel));
	assert_param(IS_PCA_PRESCALE_DIV(PCA_ICInitStruct->PCA_ICPrescaler));

	
	/*config pca parameter*/
	tmpreg = PCA_ICInitStruct->PCA_ICPrescaler;
	PCAx->CMOD  &= ~(pca_counterclk_mask);
	PCAx->CMOD |= tmpreg;
	
	/*config pca channel*/
	if(PCA_ICInitStruct->PCA_Channel==PCA_Channel0)
	{
		PCAx->CCAPM0 &= ~PCA_CAP_ALL_Edge;
		PCAx->CCAPM0 |= PCA_ICInitStruct->PCA_ICPolarity;
	}
	else if(PCA_ICInitStruct->PCA_Channel==PCA_Channel1)
	{
		PCAx->CCAPM1 &= ~PCA_CAP_ALL_Edge;
		PCAx->CCAPM1 |= PCA_ICInitStruct->PCA_ICPolarity;
	}
	else if(PCA_ICInitStruct->PCA_Channel==PCA_Channel2)
	{
		PCAx->CCAPM2 &= ~PCA_CAP_ALL_Edge;
		PCAx->CCAPM2 |= PCA_ICInitStruct->PCA_ICPolarity;
	}
	else if(PCA_ICInitStruct->PCA_Channel==PCA_Channel3)
	{
		PCAx->CCAPM3 &= ~PCA_CAP_ALL_Edge;
		PCAx->CCAPM3 |= PCA_ICInitStruct->PCA_ICPolarity;
	} else{
		if(PCA_ICInitStruct->PCA_Channel==PCA_Channel4)
		{
			PCAx->CCAPM4 &= ~PCA_CAP_ALL_Edge;
			PCAx->CCAPM4 |= PCA_ICInitStruct->PCA_ICPolarity;
		}	
	}	
}

/**
  * @brief  enable the PCA capture interrupt function
  * @param  PCAx: Set the PCA peripheral.
  * @param  PCA_ICInitStruct: pointer to an PCA_ICInitStruct structure that contains
  *         the configuration information for the specified PCA peripheral.  
  * @param  NewState: new state of the ADCx peripheral. 
  *         This parameter can be: ENABLE or DISABLE.    
  * @retval None
  */
void PCA_CaptureITCmd(PCA_TypeDef* PCAx,PCA_ICInitTypeDef* PCA_ICInitStruct, FunctionalState NewState)
{
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_PCA_CAP_Edge(PCA_ICInitStruct->PCA_ICPolarity));
	assert_param(IS_PCA_CHANNEL(PCA_ICInitStruct->PCA_Channel));
	assert_param(IS_PCA_PRESCALE_DIV(PCA_ICInitStruct->PCA_ICPrescaler));
	
	/*Set parameters to channel*/
	if(PCA_ICInitStruct->PCA_Channel==PCA_Channel0)
	{
		if(NewState)
			PCAx->CCAPM0 |= PCA_CCIE_ENABLE;
		else
			PCAx->CCAPM0 &= ~PCA_CCIE_ENABLE;
	}
	else if(PCA_ICInitStruct->PCA_Channel==PCA_Channel1)
	{
			if(NewState)
				PCAx->CCAPM1 |= PCA_CCIE_ENABLE;
		  else
				PCAx->CCAPM1 &= ~PCA_CCIE_ENABLE;
	}
	else if(PCA_ICInitStruct->PCA_Channel==PCA_Channel2)
	{
			if(NewState)
				PCAx->CCAPM2 |= PCA_CCIE_ENABLE;
		  else
				PCAx->CCAPM2 &= ~PCA_CCIE_ENABLE;
	}
	else if(PCA_ICInitStruct->PCA_Channel==PCA_Channel3)
	{
			if(NewState)
				PCAx->CCAPM3 |= PCA_CCIE_ENABLE;
		  else
				PCAx->CCAPM3 &= ~PCA_CCIE_ENABLE;
	} else{
		if(PCA_ICInitStruct->PCA_Channel==PCA_Channel4)
		{
			if(NewState)
				PCAx->CCAPM4 |= PCA_CCIE_ENABLE;
		  else
				PCAx->CCAPM4 &= ~PCA_CCIE_ENABLE;
		}	
	}	
}

/**
  * @brief  Set Soft Compare
  * @param  PCAx: Set the PCA peripheral.
  * @param  channel: 
  * @param  value:    
  * @retval None
  */
void PCA_SetSoftCompare(PCA_TypeDef* PCAx,PCA_Channel channel,uint16_t value)
{
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_PCA_CHANNEL(channel));
	
	/*check channel*/
	if(channel == PCA_Channel0)
	{
		PCAx->CCAP0L = (uint8_t)value; 
		PCAx->CCAP0H = (uint8_t)(value>>8); 
		PCAx->CCAPM0 &= ~ PCA_MAT_ENABLE;
		PCAx->CCAPM0 |=  PCA_MAT_ENABLE;
		
	}
	else if(channel == PCA_Channel1)
	{
		PCAx->CCAP1L = (uint8_t)value; 
		PCAx->CCAP1H = (uint8_t)(value>>8); 
		PCAx->CCAPM1 &= ~ PCA_MAT_ENABLE;
		PCAx->CCAPM1 |=  PCA_MAT_ENABLE;
	}
	else if(channel == PCA_Channel2)
	{
		PCAx->CCAP2L = (uint8_t)value; 
		PCAx->CCAP2H = (uint8_t)(value>>8);
	  PCAx->CCAPM2 &= ~ PCA_MAT_ENABLE;
		PCAx->CCAPM2 |=  PCA_MAT_ENABLE;		
	}
	else if(channel == PCA_Channel3)
	{
		PCAx->CCAP3L = (uint8_t)value; 
		PCAx->CCAP3H = (uint8_t)(value>>8);
    PCAx->CCAPM3 &= ~ PCA_MAT_ENABLE;
		PCAx->CCAPM3 |=  PCA_MAT_ENABLE;		
	}
	else {
		if(channel == PCA_Channel4)
		{
			PCAx->CCAP4L = (uint8_t)value; 
			PCAx->CCAP4H = (uint8_t)(value>>8);
			PCAx->CCAPM4 &= ~ PCA_MAT_ENABLE;
		  PCAx->CCAPM4 |=  PCA_MAT_ENABLE;
		}
	}
}

/** @brief  enable the PCA capture interrupt function
  * @param  PCAx: Set the PCA peripheral.
  * @param  channel: 
  * @param  value: 
  * @retval None
  */
void PCA_ClearSoftCompare(PCA_TypeDef* PCAx,PCA_Channel channel,uint16_t value)
{
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_PCA_CHANNEL(channel));
	
	/*Set value to channel register*/
	if(channel == PCA_Channel0)
	{
		PCAx->CCAP0L = (uint8_t)value;
		PCAx->CCAPM0 &= ~ PCA_MAT_ENABLE;
	}
	else if(channel == PCA_Channel1)
	{
		PCAx->CCAP1L = (uint8_t)value;
		PCAx->CCAPM1 &= ~ PCA_MAT_ENABLE;
	}
	else if(channel == PCA_Channel2)
	{
		PCAx->CCAP2L = (uint8_t)value;
		PCAx->CCAPM2 &= ~ PCA_MAT_ENABLE;
	}
	else if(channel == PCA_Channel3)
	{
		PCAx->CCAP3L = (uint8_t)value;
		PCAx->CCAPM3 &= ~ PCA_MAT_ENABLE;
	}
	else {
		if(channel == PCA_Channel4)
		{
			PCAx->CCAP4L = (uint8_t)value;
			PCAx->CCAPM4 &= ~ PCA_MAT_ENABLE;
		}
	}
}


/** @brief  config high speed output function
  * @param  PCAx: Set the PCA peripheral.
  * @param  channel: 
  * @param  value: 
  * @param  bit: 
  * @retval None
  */
void PCA_SetHighSpeed_output(PCA_TypeDef* PCAx,PCA_Channel channel,uint16_t value,uint8_t bit)
{
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_PCA_CHANNEL(channel));
	
	if(bit != 0) bit = 0x01;
	/*check channel*/
	if(channel == PCA_Channel0)
	{
		/*Set ECOM*/
		PCAx->CCAP0L = (uint8_t)value; 
		PCAx->CCAP0H = (uint8_t)(value>>8); 
    /*Set MAT*/		
		PCAx->CCAPM0 &= ~ PCA_MAT_ENABLE;
		PCAx->CCAPM0 |=  PCA_MAT_ENABLE;
		/*Set TOG*/
		PCAx->CCAPM0 &= ~ PCA_TOG_ENABLE;
		PCAx->CCAPM0 |=  PCA_TOG_ENABLE;
		
		/*Set TOG*/
		PCAx->CCAPM0 &= ~ PCA_CCIE_ENABLE;
		PCAx->CCAPM0 |=  PCA_CCIE_ENABLE;
		
		/*Setting the initial state*/
		PCAx->CCAPO  &= ~(bit<<PCA_Channel0);
		PCAx->CCAPO  |= (bit<<PCA_Channel0);
		
		/*Setting Output Enablation*/
		PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel0);
		PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel0);
	}
	else if(channel == PCA_Channel1)
	{
		/*Set ECOM*/
		PCAx->CCAP1L = (uint8_t)value; 
		PCAx->CCAP1H = (uint8_t)(value>>8); 
		/*Set MAT*/		
		PCAx->CCAPM1 &= ~ PCA_MAT_ENABLE;
		PCAx->CCAPM1 |=  PCA_MAT_ENABLE;
		
		/*Set TOG*/
		PCAx->CCAPM1 &= ~ PCA_TOG_ENABLE;
		PCAx->CCAPM1 |=  PCA_TOG_ENABLE;
		
		/*Set CCIE*/
		PCAx->CCAPM1 &= ~ PCA_CCIE_ENABLE;
		PCAx->CCAPM1 |=  PCA_CCIE_ENABLE;
		
		/*Setting the initial state*/
		PCAx->CCAPO   &= ~(bit<<PCA_Channel1);
		PCAx->CCAPO   |= (bit<<PCA_Channel1);
		/*Setting Output Enablation*/
		PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel1);
		PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel1);
	}
	else if(channel == PCA_Channel2)
	{
		/*Set ECOM*/
		PCAx->CCAP2L = (uint8_t)value; 
		PCAx->CCAP2H = (uint8_t)(value>>8); 
		/*Set MAT*/	
		PCAx->CCAPM2 &= ~ PCA_MAT_ENABLE;
		PCAx->CCAPM2 |=  PCA_MAT_ENABLE;
		/*Set TOG*/
		PCAx->CCAPM2 &= ~ PCA_TOG_ENABLE;
		PCAx->CCAPM2 |=  PCA_TOG_ENABLE;
		/*Set CCIE*/
		PCAx->CCAPM2 &= ~ PCA_CCIE_ENABLE;
		PCAx->CCAPM2 |=  PCA_CCIE_ENABLE;
		/*Setting the initial state*/
		PCAx->CCAPO   &= ~(bit<<PCA_Channel2);
		PCAx->CCAPO  |= (bit<<PCA_Channel2);
		/*Setting Output Enablation*/
		PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel2);
		PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel2);
	}
	else if(channel == PCA_Channel3)
	{
		/*Set ECOM*/
		PCAx->CCAP3L = (uint8_t)value; 
		PCAx->CCAP3H = (uint8_t)(value>>8);
		/*Set MAT*/	
		PCAx->CCAPM3 &= ~ PCA_MAT_ENABLE;
		PCAx->CCAPM3 |=  PCA_MAT_ENABLE;
		/*Set TOG*/
		PCAx->CCAPM3 &= ~ PCA_TOG_ENABLE;
		PCAx->CCAPM3 |=  PCA_TOG_ENABLE;
		
		/*Set CCIE*/
		PCAx->CCAPM3 &= ~ PCA_CCIE_ENABLE;
		PCAx->CCAPM3 |=  PCA_CCIE_ENABLE;
		
		/*Setting the initial state*/
		PCAx->CCAPO   &= ~(bit<<PCA_Channel3);
		PCAx->CCAPO   |= (bit<<PCA_Channel3);
		/*Setting Output Enablation*/
		PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel3);
		PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel3);
	}	
	else 
	{
		if(channel == PCA_Channel4)
		{
			/*Set ECOM*/
			PCAx->CCAP4L = (uint8_t)value; 
			PCAx->CCAP4H = (uint8_t)(value>>8);
			 /*Set MAT*/	
			PCAx->CCAPM4 &= ~ PCA_MAT_ENABLE;
			PCAx->CCAPM4 |=  PCA_MAT_ENABLE;
			/*Set TOG*/
			PCAx->CCAPM4 &= ~ PCA_TOG_ENABLE;
			PCAx->CCAPM4 |=  PCA_TOG_ENABLE;
			/*Set CCIE*/
		  PCAx->CCAPM4 &= ~ PCA_CCIE_ENABLE;
		  PCAx->CCAPM4 |=  PCA_CCIE_ENABLE;
			/*Setting the initial state*/
			PCAx->CCAPO   &= ~(bit<<PCA_Channel4);
			PCAx->CCAPO   |= (bit<<PCA_Channel4);
			/*Setting Output Enablation*/
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel4);
			PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel4);
		}
 }
}

/** @brief  set  Pwm output
  * @param  PCAx: Set the PCA peripheral.
  * @param  channel: 
  * @param  valuel: 
  * @param  valueh: 
  * @param  NewState: new state of the ADCx peripheral. 
  *         This parameter can be: ENABLE or DISABLE.   
  * @retval None
  */
void PCA_SetPwm_output(PCA_TypeDef* PCAx,PCA_Channel channel,uint8_t valuel,uint8_t valueh,FunctionalState NewStatus)
{
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	assert_param(IS_PCA_CHANNEL(channel));
	
	/*check channel*/
	if(channel == PCA_Channel0)
	{
		PCAx->CCAPM0 = 0x00; 
		/*Set ECOM*/
		PCAx->CCAP0L = (uint8_t)valuel; 
		PCAx->CCAP0H = (uint8_t)valueh; 
    /*Set PWM*/		
		PCAx->CCAPM0 &= ~ PCA_PWM_ENABLE;
		PCAx->CCAPM0 |=  PCA_PWM_ENABLE;

		if(NewStatus == ENABLE)
		{
		  /*Setting Output Enablation*/
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel0);
			PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel0);
			PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel0);
			PCAx->POCON |= (PCA_PWMTOGGLE_ENABLE<<PCA_Channel0);
	
		}
		else 
		{
			PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel0);
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel0);
		}
	}
	else if(channel == PCA_Channel1)
	{
		PCAx->CCAPM1 = 0x00; 
		/*Set ECOM*/
		PCAx->CCAP1L = (uint8_t)valuel; 
		PCAx->CCAP1H = (uint8_t)valueh; 
    /*Set PWM*/	
		PCAx->CCAPM1 &= ~ PCA_PWM_ENABLE;
		PCAx->CCAPM1 |=  PCA_PWM_ENABLE;
		
	
		if(NewStatus == ENABLE)
		{
			/*Setting Output Enablation*/
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel1);
			PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel1);
			PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel1);
			PCAx->POCON |= (PCA_PWMTOGGLE_ENABLE<<PCA_Channel1);
		}
		else 
		{
			PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel1);
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel1);
		}
	}
	else if(channel == PCA_Channel2)
	{
		PCAx->CCAPM2 = 0x00; 
		/*Set ECOM*/
		PCAx->CCAP2L = (uint8_t)valuel; 
		PCAx->CCAP2H = (uint8_t)valueh; 
    /*Set PWM*/		
		PCAx->CCAPM2 &= ~ PCA_PWM_ENABLE;
		PCAx->CCAPM2 |=  PCA_PWM_ENABLE;
		
		
		if(NewStatus == ENABLE)
		{
			/*Setting Output Enablation*/
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel2);
			PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel2);
			PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel2);
			PCAx->POCON |= (PCA_PWMTOGGLE_ENABLE<<PCA_Channel2);
		}
		else 
		{
			PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel2);
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel2);
		}
	}
	else if(channel == PCA_Channel3)
	{
		PCAx->CCAPM3 = 0x00; 
		/*Set ECOM*/
		PCAx->CCAP3L = (uint8_t)valuel; 
		PCAx->CCAP3H = (uint8_t)valueh; 
    /*Set PWM*/		
		PCAx->CCAPM3 &= ~ PCA_PWM_ENABLE;
		PCAx->CCAPM3 |=  PCA_PWM_ENABLE;
		
		if(NewStatus == ENABLE)
		{
			/*Setting Output Enablation*/
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel3);
			PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel3);
			PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel3);
			PCAx->POCON |= (PCA_PWMTOGGLE_ENABLE<<PCA_Channel3);
		}
		else 
		{
			PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel3);
			PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel3);
		}
	} 
	else 
	{
		if(channel == PCA_Channel4)
		{
			PCAx->CCAPM4 = 0x00; 
			/*Set ECOM*/
			PCAx->CCAP4L = (uint8_t)valuel; 
			PCAx->CCAP4H = (uint8_t)valueh; 
			/*Set PWM*/	
			PCAx->CCAPM4 &= ~ PCA_PWM_ENABLE;
			PCAx->CCAPM4 |=  PCA_PWM_ENABLE;
			
			
			if(NewStatus == ENABLE)
			{
				/*Setting Output Enablation*/
			  PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel4);
			  PCAx->POCON |= (PCA_OUTPUT_ENABLE<<PCA_Channel4);
				PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel4);
				PCAx->POCON |= (PCA_PWMTOGGLE_ENABLE<<PCA_Channel4);
			}
			else 
			{
				 PCAx->POCON &= ~(PCA_PWMTOGGLE_ENABLE<<PCA_Channel4);
				 PCAx->POCON &= ~(PCA_OUTPUT_ENABLE<<PCA_Channel4);
			}
		}
 }
}


/** @brief  Clear the interrupt flag
  * @param  PCAx: Set the PCA peripheral.
  * @param  PCA_TI_FLAG: 
  * @param  valuel: 
  * @param  valueh: 
  * @param  NewState: new state of the ADCx peripheral. 
  *         This parameter can be: ENABLE or DISABLE.   
  * @retval None
  */
void PCA_ITClear(PCA_TypeDef* PCAx, uint32_t PCA_TI_FLAG)
{
	/*Check the parameters */
	assert_param(IS_PCA_ALL_PERIPH(PCAx));
	/*Clear the PCA interrupt flag*/
	PCAx->ICLR  |= PCA_TI_FLAG;
	
}


	
	















	
		
		
		
		
	
	



	
	
	










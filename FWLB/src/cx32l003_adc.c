/**
  ******************************************************************************
  * @file    cx32l003_adc.c
  * @author  MCD Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *           + Initialization and Configuration (in addition to ADC multi mode 
  *             selection)
  *           + Analog Watchdog configuration
  *           + Temperature Sensor & Vrefint (Voltage Reference internal) & VBAT
  *             management 
  *           + Regular Channels Configuration
  *           + Regular Channels DMA Configuration
  *           + Injected channels Configuration
  *           + Interrupts and flags management
  *         
  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]
    (#) Enable the ADC interface clock using 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADCx, ENABLE); 
       
    (#) ADC pins configuration
         (++) Enable the clock for the ADC GPIOs using the following function:
             RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);   
         (++) Configure these ADC pins in analog mode using GPIO_Init();  
  
     (#) Configure the ADC Prescaler, conversion resolution and data 
         alignment using the ADC_Init() function.
     (#) Activate the ADC peripheral using ADC_Cmd() function.
  
     *** Regular channels group configuration ***
     ============================================
     [..]    
       (+) To configure the ADC regular channels group features, use 
           ADC_Init() and ADC_RegularChannelConfig() functions.
       (+) To activate the continuous mode, use the ADC_continuousModeCmd()
           function.
       (+) To configurate and activate the Discontinuous mode, use the 
           ADC_DiscModeChannelCountConfig() and ADC_DiscModeCmd() functions.
       (+) To read the ADC converted values, use the ADC_GetConversionValue()
           function.
  
     *** Multi mode ADCs Regular channels configuration ***
     ======================================================
     [..]
       (+) Refer to "Regular channels group configuration" description to
           configure the ADC1, ADC2 and ADC3 regular channels.        
       (+) Select the Multi mode ADC regular channels features (dual or 
           triple mode) using ADC_CommonInit() function and configure 
           the DMA mode using ADC_MultiModeDMARequestAfterLastTransferCmd() 
           functions.        
       (+) Read the ADCs converted values using the 
           ADC_GetMultiModeConversionValue() function.
  
     *** DMA for Regular channels group features configuration ***
     ============================================================= 
     [..]
       (+) To enable the DMA mode for regular channels group, use the 
           ADC_DMACmd() function.
       (+) To enable the generation of DMA requests continuously at the end
           of the last DMA transfer, use the ADC_DMARequestAfterLastTransferCmd() 
           function.
  
     *** Injected channels group configuration ***
     =============================================    
     [..]
       (+) To configure the ADC Injected channels group features, use 
           ADC_InjectedChannelConfig() and  ADC_InjectedSequencerLengthConfig()
           functions.
       (+) To activate the continuous mode, use the ADC_continuousModeCmd()
           function.
       (+) To activate the Injected Discontinuous mode, use the 
           ADC_InjectedDiscModeCmd() function.  
       (+) To activate the AutoInjected mode, use the ADC_AutoInjectedConvCmd() 
           function.        
       (+) To read the ADC converted values, use the ADC_GetInjectedConversionValue() 
           function.
  
    @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_adc.h"
#include "cx32l003_rcc.h"



uint8_t adc_flg =0;
/** @defgroup ADC_Group1 Initialization and Configuration functions
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the ADC Prescaler
      (+) ADC Conversion Resolution (12bit..6bit)
      (+) Scan Conversion Mode (multichannel or one channel) for regular group
      (+) ADC Continuous Conversion Mode (Continuous or Single conversion) for 
          regular group
      (+) External trigger Edge and source of regular group, 
      (+) Converted data alignment (left or right)
      (+) The number of ADC conversions that will be done using the sequencer for 
          regular channel group
      (+) Multi ADC mode selection
      (+) Direct memory access mode selection for multi ADC mode  
      (+) Delay between 2 sampling phases (used in dual or triple interleaved modes)
      (+) Enable or disable the ADC peripheral   
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes all ADCs peripherals registers to their default reset 
  *         values.
  * @param  None
  * @retval None
  */
void ADC_DeInit(void)
{
   RCC_PeriphResetCmd(RCC,RCC_APBPeriph_ADCRST, ENABLE);
   RCC_PeriphResetCmd(RCC,RCC_APBPeriph_ADCRST, DISABLE);
}

/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters 
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC ( 
  *         Resolution and Data Alignment), however, the rest of the configuration
  *         parameters are specific to the regular channels group (scan mode 
  *         activation, continuous mode activation, External trigger source and 
  *         edge, number of conversion in the regular channels group sequencer).  
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  uint32_t tmpreg1 = 0;

	
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_PRESCALER(ADC_InitStruct->ADC_ClkSel)); 
	assert_param(IS_ADC_CHANNEL(ADC_InitStruct->ADC_ChannelSel)); 
	assert_param(IS_ADC_SAMPLE_CYCLE(ADC_InitStruct->ADC_SamSel)); 
	
//	assert_param(IS_ADC_TRIG0_EDGE(ADC_InitStruct->ADC_Trigs0Sel)); 
//	assert_param(IS_ADC_TRIG1_EDGE(ADC_InitStruct->ADC_Trigs1Sel)); 
	
  /*---------------------------- ADCx CR1 Configuration -----------------*/
  /* Get the ADCx CR1 value */
  tmpreg1 = ADCx->CR0;
  
  /* Clear RES and SCAN bits */
  tmpreg1 &=  (~ADC_CR0_MASK);
  
  /* Configure ADCx: scan conversion mode and resolution */
  /* Set SCAN bit according to ADC_ScanConvMode value */
  /* Set RES bit according to ADC_Resolution value */ 
  tmpreg1 |= (uint32_t)(((uint32_t)ADC_InitStruct->ADC_ClkSel ) | \
                        ((uint32_t)ADC_InitStruct->ADC_ChannelSel) |\
												((uint32_t)ADC_InitStruct->ADC_SamSel));
																	 
  /* Write to ADCx CR1 */
  ADCx->CR0 = tmpreg1;
  /*---------------------------- ADCx CR2 Configuration -----------------*/
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the ADC ( 
  *         Resolution and Data Alignment), however, the rest of the configuration
  *         parameters are specific to the regular channels group (scan mode 
  *         activation, continuous mode activation, External trigger source and 
  *         edge, number of conversion in the regular channels group sequencer).
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* Initialize the ADC_Mode member */
  ADC_InitStruct->ADC_ClkSel = 0x00;

  /* initialize the ADC_ScanConvMode member */
  ADC_InitStruct->ADC_SamSel = 0x00;

  /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ChannelSel = 0x00;
}

/**
  * @brief  Initializes the ADCs peripherals according to the specified parameters 
  *         in the ADC_CommonInitStruct.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_CommonInitStruct: pointer to an ADC_CommonInitTypeDef structure 
  *         that contains the configuration information for  All ADCs peripherals.
  * @retval None
  */
void ADC_CommonInit(ADC_TypeDef* ADCx,ADC_CommonInitTypeDef* ADC_CommonInitStruct)
{
  uint32_t tmpreg1 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_CT(ADC_CommonInitStruct->ADC_CtMode));
	assert_param(IS_ADC_TRIG0_EDGE(ADC_CommonInitStruct->ADC_Trigs0Sel));
	assert_param(IS_ADC_TRIG1_EDGE(ADC_CommonInitStruct->ADC_Trigs1Sel));
	assert_param(IS_ADC_MODE(ADC_CommonInitStruct->ADC_CircleMode));
	assert_param(IS_ADC_SAMPLE_TIMES(ADC_CommonInitStruct->ADC_SetAdcCnt));
	
 

  /*---------------------------- ADC CR1 Configuration -----------------*/
  /* Get the ADC CR1 value */
  tmpreg1 = ADCx->CR1;
  
  /* Clear MULTI, DELAY, DMA and ADCPRE bits */
  tmpreg1 &= (~ADC_CR1_MASK);
  
  /* Configure ADCx: Multi mode, Delay between two sampling time, ADC prescaler,
     and DMA access mode for multimode */
  /* Set MULTI bits according to ADC_Mode value */
  /* Set ADCPRE bits according to ADC_Prescaler value */
  /* Set DMA bits according to ADC_DMAAccessMode value */
  /* Set DELAY bits according to ADC_TwoSamplingDelay value */    
  tmpreg1 |= (uint32_t)(ADC_CommonInitStruct->ADC_CtMode | 
                        ADC_CommonInitStruct->ADC_Trigs0Sel | 
                        ADC_CommonInitStruct->ADC_Trigs1Sel); 
                 
                        
  /* Write to ADC CR1 */
  ADCx->CR1 = tmpreg1;
	
	/*---------------------------- ADC CR2 Configuration -----------------*/
  /* Get the ADC CR2 value */
  tmpreg1 = ADCx->CR2;
  
  /* Clear MULTI, DELAY, DMA and ADCPRE bits */
  tmpreg1 &= (~ADC_CR2_MASK);
	
	  /* Configure ADCx: Multi mode, Delay between two sampling time, ADC prescaler,
     and DMA access mode for multimode */
  /* Set MULTI bits according to ADC_Mode value */
  /* Set ADCPRE bits according to ADC_Prescaler value */
  /* Set DMA bits according to ADC_DMAAccessMode value */
  /* Set DELAY bits according to ADC_TwoSamplingDelay value */    
  tmpreg1 |= (uint32_t)((ADC_CommonInitStruct->ADC_CircleMode) | 
                        (ADC_CommonInitStruct->ADC_SetAdcCnt));
												
  /* Write to ADC CR2 */
  ADCx->CR2  =  tmpreg1;                 
}

/**
  * @brief  Fills each ADC_CommonInitStruct member with its default value.
  * @param  ADC_CommonInitStruct: pointer to an ADC_CommonInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct)
{
  /* Initialize the ADC_Mode member */
  ADC_CommonInitStruct->ADC_CtMode = ADC_Ct_Single;

  /* initialize the ADC_Prescaler member */
  ADC_CommonInitStruct->ADC_Trigs0Sel = ADC_Trigs0_DISABLE;

  /* Initialize the ADC_DMAAccessMode member */
  ADC_CommonInitStruct->ADC_Trigs1Sel = ADC_Trigs1_DISABLE;

  /* Initialize the ADC_TwoSamplingDelay member */
  ADC_CommonInitStruct->ADC_CircleMode = ADC_Mode_Independent;
	
	/* Initialize the ADC_TwoSamplingDelay member */
  ADC_CommonInitStruct->ADC_SetAdcCnt = 0x00;
	
	
}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx:  select the ADC peripheral.
  * @param  NewState: new state of the ADCx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the ADON bit to wake up the ADC from power down mode */
    ADCx->CR0 |= (uint32_t)ADC_CR0_ADON;
  }
  else
  {
    /* Disable the selected ADC peripheral */
    ADCx->CR0 &= (uint32_t)(~ADC_CR0_ADON);
  }
}

/**
  * @brief  Configures for the selected ADC regular channel its corresponding
  *         rank in the sequencer and its sample time.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *          This parameter can be one of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *                       
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel. 
  *          This parameter can be one of the following values:
  *            @arg ADC_SampleTime_3Cycles: Sample time equal to 3 cycles
  *            @arg ADC_SampleTime_15Cycles: Sample time equal to 15 cycles
  *            @arg ADC_SampleTime_28Cycles: Sample time equal to 28 cycles
  *            @arg ADC_SampleTime_56Cycles: Sample time equal to 56 cycles	
  *            @arg ADC_SampleTime_84Cycles: Sample time equal to 84 cycles	
  *            @arg ADC_SampleTime_112Cycles: Sample time equal to 112 cycles	
  *            @arg ADC_SampleTime_144Cycles: Sample time equal to 144 cycles	
  *            @arg ADC_SampleTime_480Cycles: Sample time equal to 480 cycles	
  * @retval None
  */
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, uint32_t ADC_CircleMode, uint32_t ADC_SampleTime)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel)); 
	assert_param(IS_ADC_MODE(ADC_CycleMode)); 
  assert_param(IS_ADC_SAMPLE_TIMES(ADC_SampleTime));
	
	/*Set channel mask*/
	ADCx->CR0 &=  (~ADC_ChannelEL_MASK);
	ADCx->CR0 |=  ADC_Channel;
	
	/*Set circle mask*/
	ADCx->CR2 &=  (~ADC_CIRCLEMODE_MASK);
	ADCx->CR2 |= ADC_CircleMode;
	
	/*set sample times*/
	ADCx->CR2 &=  (~ADC_ADCCNT_MASK);
	ADCx->CR2 |= ADC_SampleTime;
}

/**
  * @brief  Enables the selected ADC software start conversion of the regular channels.
  * @param  ADCx:  select the ADC peripheral.
  * @retval None
  */
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  /* Enable the selected ADC conversion for regular group */
  ADCx->CR0 |= (uint32_t)ADC_CR0_SWSTART;
}

/**
  * @brief  Gets the selected ADC Software start regular conversion Status.
  * @param  ADCx: select the ADC peripheral.
  * @retval The new state of ADC software start conversion (SET or RESET).
  */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  /* Check the status of SWSTART bit */
  if ((ADCx->CR0 & ADC_CR0_SWSTART) != (uint32_t)RESET)
  {
    /* SWSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* SWSTART bit is reset */
    bitstatus = RESET;
  }
  
  /* Return the SWSTART bit status */
  return  bitstatus;
}


/**
  * @brief  Enables or disables the ADC continuous conversion mode 
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the selected ADC continuous conversion mode
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC continuous conversion mode */
    ADCx->CR1 |= (uint32_t)ADC_Ct_Contine;
  }
  else
  {
    /* Disable the selected ADC continuous conversion mode */
    ADCx->CR1 &= (uint32_t)(~ADC_Ct_Contine);
  }
}


/**
  * @brief  Enables or disables the ADC continuous conversion mode 
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the selected ADC continuous conversion mode
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ContinuousConverChannelCmd(ADC_TypeDef* ADCx,uint32_t Channel_Enable,FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_ADC_CHANNEL_CMD(Channel_Enable));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC continuous conversion mode */
    ADCx->CR2 |= (uint32_t)Channel_Enable;
  }
  else
  {
    /* Disable the selected ADC continuous conversion mode */
    ADCx->CR1 &= (uint32_t)(~Channel_Enable);
  }
}

/**
  * @brief  Enables or disables the ADC continuous conversion mode 
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the selected ADC continuous conversion mode
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ContinuousConverRstCmd(ADC_TypeDef* ADCx,uint32_t NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
  
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC continuous conversion Rest */
    ADCx->CR0 |= (uint32_t)ADC_CR0_STATERST;
  }
  else
  {
    /* no use*/
    ADCx->CR0 &= (uint32_t)(~ADC_CR0_STATERST);
  }
}



/**
  * @brief  Enables or disables the discontinuous mode on regular group channel 
  *         for the specified ADC
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the selected ADC discontinuous mode on 
  *         regular group channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DisContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Disable the selected ADC continuous conversion mode */
    ADCx->CR1 &= (uint32_t)(~ADC_Ct_Contine);
  }
  else
  {
    /* Enable the selected ADC continuous conversion mode */
    ADCx->CR1 |= (uint32_t)ADC_Ct_Contine;
  }
}

/**
  * @brief  Returns the last ADCx conversion result data for regular channel.
  * @param  ADCx: select the ADC peripheral.
  * @retval The Data conversion value.
  */
uint32_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  /* Return the selected ADC conversion value */
  return (uint16_t) ADCx->RESULT;
}

/**
  * @brief  Returns the last ADCx conversion result data for regular channel.
  * @param  ADCx: select the ADC peripheral.
  * @param  Channel: select the ADC peripheral channel.
  * @retval The Data conversion value.
  */
uint32_t ADC_GetChannelConversionValue(ADC_TypeDef* ADCx,uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(Channel));

    if(Channel == ADC_Channel0)
        /* Return ADC channel0 conversion value */
        return (uint32_t) ADCx->RESULT0;
    else if(Channel == ADC_Channel1)
        /* Return ADC channel1 conversion value */
        return (uint32_t) ADCx->RESULT1;
    else if(Channel == ADC_Channel2)
        /* Return ADC channel2 conversion value */
        return (uint32_t) ADCx->RESULT2;
    else if(Channel == ADC_Channel3)
        /* Return ADC channel3 conversion value */
        return (uint32_t) ADCx->RESULT3;
    else if(Channel == ADC_Channel4)
        /* Return ADC channel4 conversion value */
        return (uint32_t) ADCx->RESULT4;
    else if(Channel == ADC_Channel5)
        /* Return ADC channel5 conversion value */
        return (uint32_t) ADCx->RESULT5;
    else if(Channel == ADC_Channel6)
        /* Return ADC channel6 conversion value */
        return (uint32_t) ADCx->RESULT6;
    else {
        if(Channel == ADC_Channel7)
            /* Return ADC channel7 conversion value */
            return (uint32_t) ADCx->RESULT6;
    }
    return (uint32_t)0;
}


/**
  * @brief  set compare ht value
  * @param  ADCx: select the ADC peripheral.
  * @param  HtValue: the value of ht.
  * @retval The Data conversion value.
  */
uint32_t ADC_SetCompareHtValue(ADC_TypeDef* ADCx,uint32_t HtValue)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_COMPARE_VALUES(HtValue));

    /*set ADC ht value */
    ADCx->HT = HtValue;

    return HtValue;    
}

/**
  * @brief  set compare lt value
  * @param  ADCx: select the ADC peripheral.
  * @param  LtValue: the value of lt.
  * @retval The Data conversion value.
  */
uint32_t ADC_SetCompareLtValue(ADC_TypeDef* ADCx,uint32_t LtValue)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_COMPARE_VALUES(LtValue));
  
    /*set ADC Lt value */
    ADCx->LT = LtValue;
    return LtValue;
}



/**
  * @brief  Returns the last ADCx conversion result data for regular channel.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_ControlCmd: ADC control enable
  * @param  NewState: new state of the selected ADC discontinuous mode on 
  *         regular group channel.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval The Data conversion value.
  */
uint32_t ADC_CompareControl(ADC_TypeDef* ADCx,uint32_t ADC_ControlCmd,FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_CR1_CMD(ADC_ControlCmd));

    if (NewState != DISABLE)
    {
        /* Enable the selected ADC continuous conversion mode */
        ADCx->CR1 |= (uint32_t)ADC_ControlCmd;
    }
    else
    {
        /* Disable the selected ADC continuous conversion mode */
        ADCx->CR1 &= (uint32_t)(~ADC_ControlCmd);
    }
    
    return 1;
}
 /**
  * @brief  Configures the ADCx external trigger for injected channels conversion.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_ExternalTrigInjecConv: specifies the ADC trigger to start injected conversion.
  *          This parameter can be one of the following values:                                           
  * @retval None
  */
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
 
  /* Get the old register value */
  tmpreg = ADCx->CR1;
  
  /* Clear the old external event selection for injected group */
  tmpreg &= ~ADC_TRIGS1_MASK;
	tmpreg &= ~ADC_TRIGS0_MASK;
  
  /* Set the external event selection for injected group */
  tmpreg |= ADC_ExternalTrigInjecConv;
  
  /* Store the new register value */
  ADCx->CR1 = tmpreg;
}
/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled. 
  *          This parameter can be one of the following values:
	*						@arg ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
	*						@arg ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
	*						@arg ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
	*						@arg ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
	*						@arg ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
	*						@arg ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
	*						@arg ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
	*						@arg ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
	*						@arg ADC_TILLT_FLAG         ((uint32_t)0x0100)
	*						@arg ADC_TIHHT_FLAG         ((uint32_t)0x0200)
	*						@arg ADC_TIREG_FLAG         ((uint32_t)0x0400)
	*						@arg ADC_TICONT_FLAG         ((uint32_t)0x0800)                    
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITCmd(ADC_TypeDef* ADCx, uint32_t ADC_FLAG, FunctionalState NewState)  
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_FLAG(ADC_FLAG)); 

  /* Get the ADC IT index */
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->IEN |= (uint32_t)ADC_FLAG;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->IEN &= (~(uint32_t)ADC_FLAG);
  }
}


/**
  * @brief  Enables or disables the specified ADC acc.
  * @param  ADCx:select the ADC peripheral.        
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AccCmd(ADC_TypeDef* ADCx, FunctionalState NewState)  
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));


  /* Get the ADC IT index */
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->CR1 |= (uint32_t)ADC_ACC_EN;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->CR1 &= (~(uint32_t)ADC_ACC_EN);
  }
}

/**
  * @brief  Clear the acc result
  * @param  ADCx: select the ADC peripheral.   
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AccResultClear(ADC_TypeDef* ADCx,FunctionalState NewState)  
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if(NewState != DISABLE)
	{
		ADCx->CR1 |= ADC_ACCResult_Clear;
	}
	else
	{
	  ADCx->CR1  &= ~ADC_ACCResult_Clear;
	}
}


/**
  * @brief  Gets acc result
  * @param  ADCx: select the ADC peripheral.
  * @retval the value of acc result
  */
uint32_t ADC_GetAccResult(ADC_TypeDef* ADCx)  
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
  return  (uint32_t)ADCx->RESULTACC;
}


/**
  * @brief  Gets ris flag status
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to check. 
 *          This parameter can be one of the following values:
	*						@arg ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
	*						@arg ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
	*						@arg ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
	*						@arg ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
	*						@arg ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
	*						@arg ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
	*						@arg ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
	*						@arg ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
	*						@arg ADC_TILLT_FLAG         ((uint32_t)0x0100)
	*						@arg ADC_TIHHT_FLAG         ((uint32_t)0x0200)
	*						@arg ADC_TIREG_FLAG         ((uint32_t)0x0400)
	*						@arg ADC_TICONT_FLAG        ((uint32_t)0x0800)                                                  
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetRISFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_FLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADCx->RIS & ADC_FLAG) != (uint8_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Gets MIS Flag  Status
  * @param  ADCx: select the ADC peripheral.
   *          This parameter can be one of the following values:
	*						@arg ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
	*						@arg ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
	*						@arg ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
	*						@arg ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
	*						@arg ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
	*						@arg ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
	*						@arg ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
	*						@arg ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
	*						@arg ADC_TILLT_FLAG         ((uint32_t)0x0100)
	*						@arg ADC_TIHHT_FLAG         ((uint32_t)0x0200)
	*						@arg ADC_TIREG_FLAG         ((uint32_t)0x0400)
	*						@arg ADC_TICONT_FLAG         ((uint32_t)0x0800)                                     
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetMISFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_FLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADCx->MIS & ADC_FLAG) != (uint8_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the ADCx's pending flags.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to clear. 
  *          This parameter can be one of the following values:
	*						@arg ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
	*						@arg ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
	*						@arg ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
	*						@arg ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
	*						@arg ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
	*						@arg ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
	*						@arg ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
	*						@arg ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
	*						@arg ADC_TILLT_FLAG         ((uint32_t)0x0100)
	*						@arg ADC_TIHHT_FLAG         ((uint32_t)0x0200)
	*						@arg ADC_TIREG_FLAG         ((uint32_t)0x0400)
	*						@arg ADC_TICONT_FLAG        ((uint32_t)0x0800)              
  * @retval None
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_FLAG(ADC_FLAG));

  /* Clear the selected ADC flags */
  ADCx->ICLR |= (uint32_t)ADC_FLAG;
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

/************************ (C) COPYRIGHT cx32l003 *****END OF FILE****/

/**
  ******************************************************************************
  * @file    cx32l003_crc.c
  * @author  XMC Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the CRC firmware functions.
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
#include  "cx32l003_crc.h"
#include  "cx32l003_rcc.h"


/**
  * @brief  Deinitializes the CRC peripheral registers to their default reset values.
  * @param  : None 
  * @retval : None
  */
void CRC_DeInit(void)
{
	/*Enable CRC reset state */
	RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_CRCRST, ENABLE);
	/*Release CRC from reset state */
	RCC_PeriphResetCmd(RCC,RCC_AHBPeriph_CRCRST, DISABLE);    
}

/**
  * @brief  Resets the CRC RESULT register .
  * @param  None
  * @retval None
  */
void CRC_init(void)
{
  /* Reset CRC init */
  CRC_RESULT = 0xffff;
}

/**
  * @brief  Computes the 8-bit CRC of a given data word(8-bit).
  * @param  Data: data word(8-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_CalcCRC8(uint8_t Data)
{
	uint16_t crc_result;
	
	/*Set the value to the CRC_DATA_8 resgister*/
	CRC_DATA_8 = Data;
	
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	return  (uint16_t)crc_result;  
}


/**
  * @brief  Computes the 8-bit CRC of a given data word(8-bit).
  * @param  Data: data word(8-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_CheckCRC8(uint8_t Data)
{
	uint32_t crc_result;
	
	/*Set the value to the CRC_DATA_8 resgister*/
	CRC_DATA_8 = Data;
	
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	
	/*Set the value to the CRC_DATA_16 resgister*/
	CRC_DATA_16 = CRC_RESULT&0xffff;
	
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	
	/*Check the flag of the crc_result*/
	if(crc_result&crc_flag_mask)
	  return SUCCESS;  
	
	return ERROR;
}


/**
  * @brief  Computes the 8-bit CRC of a given data word(8-bit).
  * @param  Data: data word(8-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_MultiCalcCRC8(uint8_t *buffer,uint32_t count)
{
  uint32_t i;
	uint32_t crc_result;
	/*Set the value to the CRC_DATA_8*/
	for(i=0;i<count;i++)
	 CRC_DATA_8 = buffer[i];
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT; 
	
  return  (uint16_t)crc_result;
}

/**
  * @brief  Computes the 8-bit CRC of a given data word(8-bit).
  * @param  Data: data word(8-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_MultiCheckCRC8(uint8_t *buffer,uint32_t count)
{
  uint32_t i;
	uint32_t crc_result;
	
	/*Set the value to the CRC_DATA_8*/
	for(i=0;i<count;i++)
	 CRC_DATA_8 = buffer[i];
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT; 
	
	/*Set the value to the CRC_DATA_16*/
	CRC_DATA_16 = CRC_RESULT&0xffff;
	
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	
	/*Check the flag of the crc_result*/
	if(crc_result&crc_flag_mask)
	  return SUCCESS;  
	
	return ERROR;
}


/**
  * @brief  Computes the 16-bit CRC of a given data word(16-bit).
  * @param  Data: data word(16-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_CalcCRC16(uint16_t Data)
{
	 uint16_t crc_result;

	 /*Set the value to the CRC_DATA_16*/
	 CRC_DATA_16 = Data;

	 /*Gets the value to the CRC_RESULT resgister*/
	 crc_result = CRC_RESULT;

	/*Return the value of the CRC_RESULT */
	 return  (uint16_t)crc_result;  
}

/**
  * @brief  Computes the 16-bit CRC of a given data word(16-bit).
  * @param  Data: data word(16-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_CheckCRC16(uint16_t Data)
{
	 uint32_t crc_result;
	 /*Set the value to the CRC_DATA_16*/
	 CRC_DATA_16 = Data;
	 /*Gets the value to the CRC_RESULT resgister*/
	 crc_result = CRC_RESULT;
	 /*Set the value to the CRC_DATA_16*/
	 CRC_DATA_16 = CRC_RESULT&0xffff;
	 /*Gets the value to the CRC_RESULT resgister*/
	 crc_result = CRC_RESULT;
	 /*Check the flag of the crc_result*/
	 if(crc_result&crc_flag_mask)
	   return SUCCESS;  
	 
	 return ERROR;
}


/**
  * @brief  Computes the 16-bit CRC of a given data word(16-bit).
  * @param  Data: data word(16-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_MultiCalcCRC16(uint16_t *buffer,uint32_t count)
{
	uint32_t i;
	uint16_t crc_result;
	/*Set the value to the CRC_DATA_16*/
	for(i=0;i<count;i++)
	CRC_DATA_16 = buffer[i];
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
  /*Return the value of the CRC_RESULT */
	return  (uint16_t)crc_result;    
}
/**
  * @brief  Computes the 16-bit CRC of a given data word(16-bit).
  * @param  Data: data word(16-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_MultiCheckCRC16(uint16_t *buffer,uint32_t count)
{
   uint32_t i=0,crc_result=0;
	/*Set the value to the CRC_DATA_16*/
	for(i=0;i<count;i++)
	 CRC_DATA_16 = buffer[i];
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	/*Set the value to the CRC_DATA_16*/
	CRC_DATA_16 = CRC_RESULT&0xffff;
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	
	/*Check the flag of the crc_result*/
	if(crc_result&crc_flag_mask)
	  return SUCCESS; 
	
	return ERROR;
 
}


/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_CalcCRC32(uint32_t Data)
{
	 uint16_t crc_result = 0;
	 /*Set the value to the CRC_DATA_32*/
	 CRC_DATA_32 = Data;
	
	 /*Gets the value to the CRC_RESULT resgister*/
	 crc_result = CRC_RESULT;
	 
	 /*Return the value of the CRC_RESULT */
	 return  (uint16_t)crc_result;  
}

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_CheckCRC32(uint32_t Data)
{
	 uint32_t crc_result = 0;
	 /*Set the value to the CRC_DATA_32*/
	 CRC_DATA_32 = Data;
	 /*Gets the value to the CRC_RESULT resgister*/
	 crc_result = CRC_RESULT;
	 /*Set the value to the CRC_DATA_16*/
	 CRC_DATA_16 = CRC_RESULT&0xffff;
	 /*Gets the value to the CRC_RESULT resgister*/
	 crc_result = CRC_RESULT;
	 /*Check the flag of the crc_result*/
	 if(crc_result&crc_flag_mask)
		return SUCCESS; 
   return ERROR;	 

}



/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_MultiCalcCRC32(uint32_t *buffer,uint32_t count)
{
  uint32_t i = 0 ,crc_result = 0;
  /*Set the value to the CRC_DATA_32*/
	for(i=0;i<count;i++)
	 CRC_DATA_32 = buffer[i];
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	
	/*Return the value of the CRC_RESULT */
	return  (uint16_t)crc_result;	  
}

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_MultiCheckCRC32(uint32_t *buffer,uint32_t count)
{
  uint32_t i = 0,crc_result = 0;
  /*Set the value to the CRC_DATA_32*/
	for(i=0;i<count;i++)
	 CRC_DATA_32 = buffer[i];
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	/*Set the value to the CRC_DATA_16*/
	CRC_DATA_16 = CRC_RESULT&0xffff;
	/*Gets the value to the CRC_RESULT resgister*/
	crc_result = CRC_RESULT;
	/*Check the flag of the crc_result*/
	if(crc_result&crc_flag_mask)
	  return SUCCESS; 
  return ERROR;	
}




/**
  * @}
  */

/**
  * @}
  */
/******************* (C) COPYRIGHT 2018 XMC *****END OF FILE****/



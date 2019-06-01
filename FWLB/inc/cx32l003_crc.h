/**
  ******************************************************************************
  * @file    stm32f4xx_crc.h
  * @author  XMC Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file contains all the functions prototypes for the CRC firmware 
  *          library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32l003_CRC_H
#define __CX32l003_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
	 
	 
/** @defgroup crc_flag_mask 
  * @{
  */
#define crc_flag_mask 0x10000

/* Exported functions --------------------------------------------------------*/  
void CRC_init(void);
uint16_t CRC_CalcCRC8(uint8_t Data);
ErrorStatus CRC_CheckCRC8(uint8_t Data);
uint16_t CRC_MultiCalcCRC8(uint8_t *buffer,uint32_t count);
ErrorStatus CRC_MultiCheckCRC8(uint8_t *buffer,uint32_t count);

uint16_t CRC_CalcCRC16(uint16_t Data);
ErrorStatus CRC_CheckCRC16(uint16_t Data);
uint16_t CRC_MultiCalcCRC16(uint16_t *buffer,uint32_t count);
ErrorStatus CRC_MultiCheckCRC16(uint16_t *buffer,uint32_t count);

uint16_t CRC_CalcCRC32(uint32_t Data);
ErrorStatus CRC_CheckCRC32(uint32_t Data);
uint16_t CRC_MultiCalcCRC32(uint32_t *buffer,uint32_t count);
ErrorStatus CRC_MultiCheckCRC32(uint32_t *buffer,uint32_t count);

#ifdef __cplusplus
}
#endif

#endif /* __CX32l003_CRC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT XMC *****END OF FILE****/

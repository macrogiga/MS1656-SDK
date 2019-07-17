/**
  ******************************************************************************
  * @file    cx32l003_flash.c
  * @author  MCU_BU Application Team
  * @version V0.0.0
  * @date    28-5-2019
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the FLASH peripheral:
  *            + FLASH Interface configuration
  *            + FLASH Memory Programming
  *            + Option Bytes Programming
  *            + Interrupts and flags management
  *  
 @verbatim    
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]                             
      This driver provides functions to configure and program the FLASH memory 
      of all cx32l003 devices. These functions are split in 2 groups:
      (#) FLASH Memory Programming functions: this group includes all needed
          functions to erase and program the main memory:
        (++) Erase function: Erase sector, erase all sectors
        (++) Program functions: byte, half word, word and double word
    

    
      (#) Interrupts and flags management functions: this group 
          includes all needed functions to:
        (++) Enable/Disable the FLASH interrupt sources
        (++) Get flags status
        (++) Clear flags
        (++) Get FLASH operation status
        (++) Wait for last FLASH operation   
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
#include "cx32l003_flash.h"

/**
  * @brief  Erases a specified FLASH Sector.
  *
  * @note   If an erase and a program operations are requested simustaneously,    
  *         the erase operation is performed before the program one.
  *
  * @param  FLASH_Sector: The Sector number to be erased.
  
  * @retval FLASH Status: The returned value can be: FLASH_BUSY,FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseSector(uint32_t FLASH_Addr)
{
  uint32_t SectorProBit = 0x0;
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(FLASH_Addr));
	
	SectorProBit = FLASH_Addr/FLASH_SECTOR_SIZE;
	
	/* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation();
	
	/*Disable Sector Operation Protect*/
	if(SectorProBit > FLASH_SLOCK0_SIZE)
	{
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		
		/*Open protect earse operation*/
		FLASH->SLOCK1  |= (uint32_t)(0x01<<((SectorProBit-FLASH_SLOCK0_SIZE)/2));
	}
	else
	{
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;

		/*Open protect earse operation*/
		FLASH->SLOCK0  |= (uint32_t)(0x01<<((SectorProBit)/2));
	}
		
	if(status == FLASH_COMPLETE)
	{ 
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		FLASH->CR |= FLASH_SECTOREARSE; 
		*(__IO uint32_t *)FLASH_Addr = (uint32_t)0x00000000;
		
		
		/* Wait for last operation to be completed */
		status = FLASH_WaitForLastOperation();
		
	}
  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Erases all FLASH Sectors.
  *
  * @note   If an erase and a program operations are requested simustaneously,    
  *         the erase operation is performed before the program one.
  *  
  *       
  * @retval FLASH Status: The returned value can be: FLASH_BUSY,FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseAllSectors(void)
{
  uint32_t tmp_psize = 0x0;
  FLASH_Status status = FLASH_COMPLETE;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation();
	
	/* Disable the write protection for flash registers */
	FLASH->BYPASS = 0x5A5A;
	FLASH->BYPASS = 0xA5A5;
	/*Open flash operation protect slock0*/
	FLASH->SLOCK0 = (uint32_t)0xffffffff;
	
	/* Disable the write protection for flash registers */
	FLASH->BYPASS = 0x5A5A;
	FLASH->BYPASS = 0xA5A5;
	/*Open flash operation protect slock1*/
	FLASH->SLOCK1 = (uint32_t)0xffffffff;
	
	if(status == FLASH_COMPLETE)
	{ 
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		
		FLASH->CR  = FLASH_CHIPEARSE;
	 	
		/* Wait for last operation to be completed */
		status = FLASH_WaitForLastOperation();
		
		/*if the erase operation is completed, disable the SER Bit */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		FLASH->CR  &= FLASH_OPERATION_MASK;	
	}
  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Programs a word (32-bit) at a specified address.
  *
  * @note   This function must be used when the device voltage range is from 2.7V to 3.6V. 
  *
  * @note   If an erase and a program operations are requested simustaneously,    
  *         the erase operation is performed before the program one.
  *  
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be any address in Program memory zone or in OTP zone.  
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
	uint32_t SectorProBit = 0x0;
  FLASH_Status status = FLASH_COMPLETE;
	/* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));
	
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation();
	
	/*Disable Sector Operation Protect*/
	if(SectorProBit > FLASH_SLOCK0_SIZE)
	{
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		
		/*Open protect earse operation*/
		FLASH->SLOCK1  |= (uint32_t)(0x01<<((SectorProBit-FLASH_SLOCK0_SIZE)/2));
	}
	else
	{
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;

		/*Open protect earse operation*/
		FLASH->SLOCK0  |= (uint32_t)(0x01<<((SectorProBit)/2));
	}
  
  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new data */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		FLASH->CR  &= FLASH_OPERATION_MASK;
		
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		
		FLASH->CR |= FLASH_PROGRAM; 
		
    *(__IO uint32_t*)Address = Data;
        
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    /* if the program operation is completed, disable the PG Bit */
    FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		FLASH->CR  &= FLASH_OPERATION_MASK;
  } 
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a half word (16-bit) at a specified address. 
  * @note   This function must be used when the device voltage range is from 2.1V to 3.6V. 
  *
  * @note   If an erase and a program operations are requested simustaneously,    
  *         the erase operation is performed before the program one.
  * 
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be any address in Program memory zone or in OTP zone.  
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY,FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
	uint32_t SectorProBit = 0x0;
  FLASH_Status status = FLASH_COMPLETE;
	/* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));
	
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation();
	
	/*Disable Sector Operation Protect*/
	if(SectorProBit > FLASH_SLOCK0_SIZE)
	{
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		
		/*Open protect earse operation*/
		FLASH->SLOCK1  |= (uint32_t)(0x01<<((SectorProBit-FLASH_SLOCK0_SIZE)/2));
	}
	else
	{
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;

		/*Open protect earse operation*/
		FLASH->SLOCK0  |= (uint32_t)(0x01<<((SectorProBit)/2));
	}
  
  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new data */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		FLASH->CR  &= FLASH_OPERATION_MASK;
		
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		
		FLASH->CR |= FLASH_PROGRAM; 
		
    *(__IO uint16_t*)Address = Data;
        
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    /* if the program operation is completed, disable the PG Bit */
    FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		FLASH->CR  &= FLASH_OPERATION_MASK;
  } 
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a byte (8-bit) at a specified address.
  * @note   This function can be used within all the device supply voltage ranges.  
  *
  * @note   If an erase and a program operations are requested simustaneously,    
  *         the erase operation is performed before the program one.
  * 
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be any address in Program memory zone or in OTP zone.  
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY,FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data)
{
	 uint32_t SectorProBit = 0x0;
  FLASH_Status status = FLASH_COMPLETE;
	/* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));
	
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation();
	
	/*Disable Sector Operation Protect*/
	if(SectorProBit > FLASH_SLOCK0_SIZE)
	{
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		
		/*Open protect earse operation*/
		FLASH->SLOCK1  |= (uint32_t)(0x01<<((SectorProBit-FLASH_SLOCK0_SIZE)/2));
	}
	else
	{
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;

		/*Open protect earse operation*/
		FLASH->SLOCK0  |= (uint32_t)(0x01<<((SectorProBit)/2));
	}
  
  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new data */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		FLASH->CR  &= FLASH_OPERATION_MASK;
		
		/* Disable the write protection for flash registers */
		FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		
		FLASH->CR |= FLASH_PROGRAM; 
		
    *(__IO uint8_t*)Address = Data;
        
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    /* if the program operation is completed, disable the PG Bit */
    FLASH->BYPASS = 0x5A5A;
		FLASH->BYPASS = 0xA5A5;
		FLASH->CR  &= FLASH_OPERATION_MASK;
  } 
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Enables or disables the write protection of the desired sectors, for the first
  * @param  Newstate: new state of the Write Protection.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None  
  */
void FLASH_OB_WRPConfig(uint32_t OB_Sector, uint32_t OB_WRP, FunctionalState NewState)
{ 
  FLASH_Status status = FLASH_COMPLETE;
  
  /* Check the parameters */
  assert_param(IS_OB_WRP(OB_WRP));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  status = FLASH_WaitForLastOperation();
	
	if(OB_Sector >= FLASH_SLOCK0_SIZE)
	{
		if(status == FLASH_COMPLETE)
		{ 
			if(NewState != DISABLE)
			{
				/* Disable the write protection for flash registers */
				FLASH->BYPASS = 0x5A5A;
				FLASH->BYPASS = 0xA5A5;
				/*Open protect earse operation*/
				FLASH->SLOCK1  |= OB_WRP;
			}
			else
			{
				/* Disable the write protection for flash registers */
				FLASH->BYPASS = 0x5A5A;
				FLASH->BYPASS = 0xA5A5;
				/*Open protect earse operation*/
				FLASH->SLOCK1  &= (uint32_t)(~OB_WRP);
			}
		}
		
	}
	else
	{
		if(status == FLASH_COMPLETE)
		{ 
			if(NewState != DISABLE)
			{
				/* Disable the write protection for flash registers */
				FLASH->BYPASS = 0x5A5A;
				FLASH->BYPASS = 0xA5A5;
				/*Open protect earse operation*/
				FLASH->SLOCK0  |= OB_WRP;
			}
			else
			{
				/* Disable the write protection for flash registers */
				FLASH->BYPASS = 0x5A5A;
				FLASH->BYPASS = 0xA5A5;
				/*Open protect earse operation*/
				FLASH->SLOCK0  &= (uint32_t)(~OB_WRP);
			}
		}
	} 
}

/**
  * @brief  Programs the FLASH from User mode
  * @param  Newstate: new state of the operation mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_OB_UserConfig(FunctionalState NewState)
{
	 /* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	/* Disable the write protection for flash registers */
	FLASH->BYPASS = 0x5A5A;
	FLASH->BYPASS = 0xA5A5;

	if(NewState != DISABLE)
	{
		/* Enable the interrupt sources */
		FLASH->ISPCON  = ISP_KEY|OB_APP_BOOT;
	}
	else
	{
		/* Disable the interrupt sources */
		FLASH->ISPCON  = ISP_KEY |OB_ISP_BOOT ;
	}
}

/**
  * @brief  Programs the FLASH from BOOT mode
  * @param  Newstate: new state of the operation mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_OB_ISPConfig(FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	/* Disable the write protection for flash registers */
  FLASH->BYPASS = 0x5A5A;
  FLASH->BYPASS = 0xA5A5;

  if(NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->ISPCON  = ISP_KEY|OB_ISP_BOOT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->ISPCON  = ISP_KEY |OB_APP_BOOT ;
  }
}

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  * @param  Newstate: This parameter can be: ENABLE or DISABLE.
  * @retval None 
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FLASH_IT(FLASH_IT)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	/* Disable the write protection for flash registers */
  FLASH->BYPASS = 0x5A5A;
  FLASH->BYPASS = 0xA5A5;

  if(NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->CR &= ~(uint32_t)FLASH_IT;
  }
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *          This parameter can be one of the following values:
  *            @arg FLASH_FLAG_IT_PC: IT PC FLAG 
  *            @arg FLASH_FLAG_IT_PROTECT: IT PROTECT FLAG 
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_FLASH_FLAG_IT(FLASH_FLAG));

  if((FLASH->IFR & FLASH_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus; 
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *          This parameter can be any combination of the following values:
  *            @arg FLASH_FLAG_IT_PC: IT PC FLAG 
  *            @arg FLASH_FLAG_IT_PROTECT: IT PROTECT FLAG 
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
  /* Check the parameters */
  assert_param(IS_FLASH_FLAG_IT(FLASH_FLAG));
	
  /* Disable the write protection for flash registers */
  FLASH->BYPASS = 0x5A5A;
  FLASH->BYPASS = 0xA5A5;
  
  /* Clear the flags */
  FLASH->ICLR &= (~FLASH_FLAG);
}

/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_COMPLETE.
  */
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;
  
  if((FLASH->CR & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY) 
  {
    flashstatus = FLASH_BUSY;
  }
  else 
  {  
    flashstatus = FLASH_COMPLETE;
  }
  /* Return the FLASH Status */
  return flashstatus;
}

/**
  * @brief  Waits for a FLASH operation to complete.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_COMPLETE.
  */
FLASH_Status FLASH_WaitForLastOperation(void)
{ 
  __IO FLASH_Status status = FLASH_COMPLETE;
   
  /* Check for the FLASH Status */
  status = FLASH_GetStatus();

  /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
     Even if the FLASH operation fails, the BUSY flag will be reset and an error
     flag will be set */
  while(status == FLASH_BUSY)
  {
    status = FLASH_GetStatus();
  }
  /* Return the operation status */
  return status;
} 

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


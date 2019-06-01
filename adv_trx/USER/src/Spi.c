/**
  ******************************************************************************
  * @file    :Spi.c
  * @author  :MG Team
  * @version :V1.0
  * @date    
  * @brief   
  ******************************************************************************
***/

/* Includes ------------------------------------------------------------------*/
#include "Includes.h"



uint8_t SPI_Write_Byte(unsigned char SendData)
{
    SPI_SendData(SPI,SendData);
    while(RESET == SPI_GetFlagStatus(SPI,SPI_FLAG_SPIF));
    return SPI_ReceiveData(SPI);
}

#define SPI_Read_Byte()     SPI_Write_Byte(0xff)


/*******************************************************************************
* Function   :     	SPI_Write_Reg
* Parameter  :     	uint8_t reg, uint8_t data
* Returns    :     	void
* Description:
* Note:      :
*******************************************************************************/
void SPI_Write_Reg(uint8_t reg, uint8_t data) 
{ 
    BLE_CSN_CLR();
    
    SPI_Write_Byte(reg);
    SPI_Write_Byte(data);

    BLE_CSN_SET();
} 

/*******************************************************************************
* Function   :     	SPI_Read_Reg
* Parameter  :     	uint8_t reg
* Returns    :     	uint8_t
* Description:
* Note:      : 	    REG addr:0x00--0x1F write must or0x20
*******************************************************************************/
uint8_t SPI_Read_Reg(uint8_t reg) 
{ 
    uint8_t temp0=0;
    
    BLE_CSN_CLR();
    
    SPI_Write_Byte(reg);
    temp0 = SPI_Read_Byte();

    BLE_CSN_SET();
    return temp0;
} 
/*******************************************************************************
* Function   :     	SPI_Write_Buffer
* Parameter  :     	uint8_t reg, uint8_t *dataBuf, uint8_t len
* Returns    :     	void
* Description:
* Note:      : 
*******************************************************************************/
void SPI_Write_Buffer(uint8_t reg, uint8_t *dataBuf, uint8_t len) 
{ 
    uint8_t temp0=0;
    
    BLE_CSN_CLR();

    SPI_Write_Byte(reg|0x20);

    for(temp0=0;temp0<len;temp0++)
    {
        SPI_Write_Byte(*dataBuf);
        dataBuf++;
    }

    BLE_CSN_SET();
} 

/*******************************************************************************
* Function   :     	SPI_Read_Buffer
* Parameter  :     	uint8_t reg, uint8_t *dataBuf, uint8_t len
* Returns    :
* Description:
* Note:      :
*******************************************************************************/
void SPI_Read_Buffer(uint8_t reg, uint8_t *dataBuf, uint8_t len) 
{ 
    uint8_t temp0=0;
    
    BLE_CSN_CLR();
    
    SPI_Write_Byte(reg);

    for(temp0=0;temp0<len;temp0++)
    {
        *(dataBuf+temp0)=SPI_Read_Byte();
    }

    BLE_CSN_SET();
}

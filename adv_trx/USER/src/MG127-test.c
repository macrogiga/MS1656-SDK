/**
  ******************************************************************************
  * @file    :MG127-test.c
  * @author  :MG Team
  * @version :V1.0
  * @date
  * @brief
  ******************************************************************************
***/
#include "Includes.h"

/*************************************************
Functions used for SRRC/FCC test
Called after BLE_Init()
Add while(1){} after calling
Note: need clear watchdog if watchdog enabled.
*************************************************/


//FCC/SRRC Carrier test
void SRCCCarrierTest(unsigned char freq)
{
    unsigned long Delay=0x64000;
    unsigned char temp[6];

    SPI_Write_Reg(0x50, 0x51);
    SPI_Write_Reg(0xe1,0xff);
    SPI_Write_Reg(0x20|0x05,freq);
    SPI_Write_Reg(0x50, 0x56);
    SPI_Write_Reg(0x20,0);
    SPI_Write_Reg(0x50, 0x53);
    temp[0] = 0x00;
    temp[1] = 0x00;
    SPI_Write_Buffer(0x00, temp,2);

    SPI_Write_Reg(0x20|0x13,0x01);
    SPI_Write_Reg(0x20|0x15,0x01);
    SPI_Write_Reg(0x20|0x16,0x8c);
    SPI_Write_Reg(0x20|0x11,0x24);
    SPI_Write_Reg(0x20|0x0f,0x02);
    SPI_Write_Reg(0x20|0x10,0x01);
    temp[0] = 0x80;
    temp[1] = 0x00;
    temp[2] = 0x81;
    SPI_Write_Buffer(0x12,temp,3);
    while(Delay--);//Delay>10ms

    temp[0] = 0xf3;
    temp[1] = 0x00;
    SPI_Write_Buffer(0x14,temp,2);
    temp[0] = 0x10;
    temp[1] = 0x08;
    SPI_Write_Buffer(0x1e,temp,2);
    temp[0] = 0x80;
    temp[1] = 0x00;
    temp[2] = 0x01;
    SPI_Write_Buffer(0x12,temp,3);
    temp[0] = 0x01;
    temp[1] = 0x20;
    SPI_Write_Buffer(0x13,temp,2);

    temp[0] = 0x00;
    temp[1] = 0x80;
    temp[2] = 0x01;
    SPI_Write_Buffer(0x10,temp,3);

    temp[0] = 0x01;
    temp[1] = 0x01;
    temp[2] = 0x24;
    SPI_Write_Buffer(0x0f,temp,3);

    temp[0] = 0x00;
    temp[1] = 0x0e;
    SPI_Write_Buffer(0x11,temp,2);


    SPI_Write_Reg(0x20|0x1d,0x00|0x04);
    SPI_Write_Reg(0x20|0x1d,0x02|0x04);

    SPI_Write_Reg(0x20|0x1d,0x03|0x04);

    SPI_Write_Reg(0x20|0x1d,0x01|0x04);

    temp[0] = 0x01;
    temp[1] = 0x43;
    temp[2] = 0x24;
    SPI_Write_Buffer(0x0f,temp,3);

    temp[0] = 0x01;
    temp[1] = 0x20;
    SPI_Write_Buffer(0x13,temp,2);
}

//FCC/SRRC PRBS9 data test
const uint8_t AccessAddr[4] = {0x8e,0x6e,0x82,0x94};
const uint8_t PayLoad1[32]={
0x00,0xa4,0xff,0x83,0xdf,0x17,0x32,0x09,0x4E,0xD1,0xE7,0xCD,0x8A,0x91,0xC6,0xD5,0xC4,0xC4,0x40,0x21,0x18,0x4E,0x55,0x86,0xF4,0xDC,0x8A,0x15,0xA7,0xEC,0x92,0xDF
};
const uint8_t PayLoad2[10]={
    0x93,0x53,0x30,0x18,0xCA,0x34,0xBF,0xe2,0x21,0xe8
};
void SRRC_PRBS9Test(unsigned char freq)
{
    unsigned long delay=0x14000;
    unsigned char temp[6];

    SPI_Write_Reg(0x50, 0x51);
    
    SPI_Write_Reg(0x20,0x78);
    //0x02  0x1a  0x50
    SPI_Write_Reg(0x25,freq);
    SPI_Write_Reg(0x50, 0x53);
    temp[0] = 0x00;
    temp[1] = 0x08;
    SPI_Write_Buffer(0x00, temp,2);
    temp[0] = 0x02;
    temp[1] = 0x01;
    SPI_Write_Buffer(0x0f, temp,2);
    SPI_Write_Reg(0x36, 0x8c);
    SPI_Write_Reg(0x20|0x1d, 0x1c);
    temp[0] = 0x24;
    temp[1] = 0x2e;
    temp[2] = 0x10;
    SPI_Write_Buffer(0x11, temp, 3);
    while(delay--);//Delay>10ms

    SPI_Write_Reg(0x50, 0x51);
    SPI_Write_Reg(0x20,0x7a);
    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x20|0x1d, 0x1e);

    delay=0x14000;
    while(delay--);//Delay>10ms

    SPI_Write_Reg(0x50, 0x56);
    SPI_Write_Reg(0x20,0x0);

    SPI_Write_Reg(0x50, 0x51);

    SPI_Write_Reg(0x20|0x01,0x00);

    SPI_Write_Reg(0x20|0x04,0x00);

    SPI_Write_Buffer(0x10, (uint8_t*)AccessAddr, 4);
    SPI_Write_Reg(0x20|0x03,0x02);
    SPI_Write_Reg(0x20|0x00,0x0e);
    SPI_Write_Reg(0x20|0x06,0x06); //for cont wave
    
    SPI_Write_Reg(0xe1,0xff); 
    SPI_Write_Buffer(0xa0, (uint8_t*)PayLoad1, 32);
    SPI_Write_Buffer(0xa0, (uint8_t*)PayLoad2, 10);
    SPI_Write_Reg(0xe3,0xff);

    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x20|0x16, 0x8e);

    temp[0] = 0x02;
    temp[1] = 0x43;
    SPI_Write_Buffer(0x0f, temp,2);
}





//for 16MHz xtal capacitor tuning
//call this function after BLE_Init() in main()
//16MHz clock should be output from IRQ pin
void XOClockOutput(void)
{
    uint8_t data_buf[3];

    SPI_Write_Reg(0x50, 0x51);
    SPI_Write_Reg(0x50, 0x53);

    SPI_Write_Reg(0x35,0x01);
    data_buf[0] = 0x93;
    data_buf[1] = 0x00;
    SPI_Write_Buffer(0x14, data_buf, 2);
    SPI_Write_Reg(0x3e,0x30);
    SPI_Write_Reg(0x31,0x00);
    SPI_Write_Reg(0x3b,0x48);
    data_buf[0] = 0x00;
    data_buf[1] = 0x00;
    data_buf[2] = 0x15;
    SPI_Write_Buffer(0x12, data_buf, 3);
}


//2480MHz carrier, for xtal capacitor tuning
//call this function after BLE_Init() in main()
void Carrier(unsigned char freq)
{
    unsigned long delay = 0x14000;
    uint8_t data_buf[3] = {0xc0, 0x00, 0};

    SPI_Write_Reg(0x50, 0x51);
    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x35, 0x00);

    SPI_Write_Reg(0x3d, 0x1e);
    while(delay--);

    SPI_Write_Reg(0x50, 0x56);
    SPI_Write_Reg(0x20,0x0);

    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x36, 0x8c);  //
    SPI_Write_Reg(0x27,0x0F);
    SPI_Write_Buffer(0x4, data_buf, 2);
    data_buf[0] = 0x24;
    data_buf[1] = 0x2e;
    data_buf[2] = 0x10;
    SPI_Write_Buffer(0x11, data_buf, 3);
    SPI_Write_Reg(0x50, 0x51);
    SPI_Write_Reg(0xe1,0xff);
    SPI_Write_Reg(0x21,0x00);
    SPI_Write_Reg(0x25,freq);
    SPI_Write_Reg(0x24,0x00);

    SPI_Write_Reg(0x20,0x0e);
    SPI_Write_Reg(0x26,0x96); //for cont wave
    SPI_Write_Reg(0xe3,0xff);

    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x36, 0x8e); //

    SPI_Write_Reg(0x50, 0x51);
    SPI_Write_Reg(0x26, 0x06);
    SPI_Write_Reg(0x26, 0x96);

    SPI_Write_Reg(0x50, 0x53);
}

void RXTest(unsigned char freq)
{
    unsigned long delay=0x14000;
    unsigned char temp[32];

    SPI_Write_Reg(0x50, 0x51);
    
    SPI_Write_Reg(0x20,0x78);
    SPI_Write_Reg(0x25,freq);
    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x36, 0x8c);
    SPI_Write_Reg(0x20|0x1d, 0x1c);
    while(delay--);//Delay>10ms

    SPI_Write_Reg(0x50, 0x51);
    SPI_Write_Reg(0x20,0x7a);
    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x20|0x1d, 0x1e);

    delay=0x14000;
    while(delay--);//Delay>10ms

    SPI_Write_Reg(0x50, 0x56);
    SPI_Write_Reg(0x20,0x0);

    SPI_Write_Reg(0x50, 0x51);

    SPI_Write_Reg(0x20|0x01,0x00);

    SPI_Write_Reg(0x20|0x04,0x00);

    SPI_Write_Buffer(0x0a, (uint8_t*)AccessAddr, 4);
    SPI_Write_Reg(0x20|0x03,0x02);
    
    SPI_Write_Reg(0x20|0x11,0x20);
    SPI_Write_Reg(0x20|0x00,0x03);

    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x20|0x16, 0x8e);
    
    SPI_Write_Reg(0x50, 0x51);
    
}

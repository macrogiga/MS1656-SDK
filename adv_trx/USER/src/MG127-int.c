/**
  ******************************************************************************
  * @file    :MG127-int.c
  * @author  :MG Team
  * @version :V1.0
  * @date
  * @brief
  ******************************************************************************
***/

/* Includes ------------------------------------------------------------------*/
#include "Includes.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/



/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

extern uint8_t adv_data[];

static uint8_t McuCanSleep = 0;

uint8_t ble_McuCanSleep(void)
{
    return McuCanSleep;
}

/*******************************************************************************
* Function   :     	BLE_Start
* Parameter  :     	txcnt, rxcnt
* Returns    :     	void
* Description:      Beacon data .process .
* Note:      :
*******************************************************************************/
void BLE_Start(void)
{
    uint8_t data_buf[2];
    
    if((txcnt+rxcnt) == 0) return;

    BLE_Mode_PwrUp();

    //set BLE TX default channel:37.38.39
    SPI_Write_Reg(CH_NO|0X20, 37);

    //BLT FIFO write adv_data . max len:31 byte
    SPI_Write_Buffer(W_TX_PAYLOAD, adv_data, LEN_DATA);

    //PDU TYPE: 2  non-connectable undirected advertising . tx add:random address
    //set BLT PDU length:adv_data+6 mac adress.
    data_buf[0] = 0x02;
    data_buf[1] = LEN_DATA+LEN_BLE_ADDR;
    SPI_Write_Buffer(ADV_HDR_TX, data_buf, 2);

    //clear all interrupt
    data_buf[0] = 0xFF;
    data_buf[1] = 0x80;
    SPI_Write_Buffer(INT_FLAG, data_buf, 2);

    BLE_Set_TimeOut(BLE_RX_TIMEOUT);
    
    BLE_Mode_Wakeup();
    
    McuCanSleep = 0;
}

void BLE_TRX_Int(void)
{
    static uint8_t tmp_txcnt = 0;
    static uint8_t tmp_rxcnt = 0;
    uint8_t status = 0;
    uint8_t loop = 0;
    static uint8_t len_pdu = 0;    
    static uint8_t rssi = 0;
    static uint8_t ch = 37;

    {
        //BLE IRQ LOW
        if (!BLE_IRQ_GET())
        {
            //clear interrupt flag
            status = SPI_Read_Reg(INT_FLAG);
            SPI_Write_Reg(INT_FLAG|0X20, status);

            if(INT_TYPE_WAKEUP & status)//wakeup
            {
                if((txcnt > 0) && (tmp_txcnt < txcnt)){
                    tmp_txcnt ++;
                    SPI_Write_Reg(MODE_TYPE|0X20, RADIO_MODE_ADV_TX);
                    BLE_Set_StartTime(BLE_START_TIME);
                }else if((rxcnt > 0) && (tmp_rxcnt < rxcnt)){
                    tmp_rxcnt ++;
                    SPI_Write_Reg(MODE_TYPE|0X20, RADIO_MODE_ADV_RX);
                    BLE_Set_StartTime(BLE_START_TIME);
                }
                return;
            }

            BLE_Mode_Sleep();

            if(INT_TYPE_PDU_OK & status){ //only happen in rx application, no need porting in tx only application
                rssi = BLE_Get_RSSI();
                BLE_Get_Pdu(rx_buf, &len_pdu);

                LED_RED_ON(); //debug
            }else if(INT_TYPE_TX_START & status){ //only happen in tx application
                LED_GREEN_ON(); //debug
            }

            if(INT_TYPE_SLEEP & status)//sleep
            {
                LED_GREEN_OFF(); //debug
                LED_RED_OFF();  //debug

                //BLE channel
                if (++ch > 39){
                    ch = 37;
                }
                SPI_Write_Reg(CH_NO|0X20, ch);
#ifdef BLE_RXDEBUG
            if(rssi > 0){
                Uart_Send_String("\r\nRX[");
                Uart_Send_Byte(rssi);
                rssi = 0;
                Uart_Send_String("]: ");
                for(loop=0; loop<len_pdu; loop++){
                    Uart_Send_Byte(rx_buf[loop]);
                    Uart_Send_String(" ");
                }
            }
#endif
                if((tmp_txcnt >= txcnt) && (tmp_rxcnt >= rxcnt)){
                    tmp_txcnt = 0;
                    tmp_rxcnt = 0;
                    BLE_Mode_PwrDn();
                    McuCanSleep = 1;
                    return;
                }
                else{
                    BLE_Mode_Wakeup();
                }
            }
        }
    }
}

void GPIOB_IRQHandler(void)
{
    if((GPIOB->RIS & GPIO_Pin_4) && (GPIOB->MIS & GPIO_Pin_4)) {
        GPIOB->ICLR |= GPIO_Pin_4;
        //À¶ÑÀIRQÖÐ¶Ï²úÉú
        BLE_TRX_Int();
    }
}

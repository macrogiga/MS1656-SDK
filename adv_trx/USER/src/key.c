/******************************************************************************
  * @file    :MG127.c
  * @author  :MG Team
  * @version :V1.0
  * @date
  * @brief
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Includes.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define key_delay_set 0x05
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t key_delay = 0x00; //按键去抖
static uint8_t key_flag = 0x00;  //按键状态0-release, 1-press

//unsigned char advdata[31] = {  //BLE ADV_data, maxlen=31
//    0x02, BLE_GAP_AD_TYPE_FLAGS,
//    0x06,

//    0x11, BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE,
//    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,

//    0x09, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME,
//    'M', 'S', '1', '6', '5', '6', 'D', 's'
//};

/*******************************************************************************
* Function   :      Key_Scan
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
void Key_Scan(void)
{
    if (KEY_GET()) {
        if (key_flag != 0x00)
            key_delay = 0x00;
    } else {
        if (key_flag == 0x00)
            key_delay = 0x00;
    }
    key_delay++;
    if (key_delay < key_delay_set)
        return;
    key_delay = 0x00;

    if (key_flag == 0) {
        key_flag = 1;
        //按键按下
        LED_RED_ON();
        //RTC_CountCmd(RTC,DISABLE);
        
    } else {
        key_flag = 0;
        //按键松开
        LED_RED_OFF();
        //RTC_CountCmd(RTC,ENABLE);
    }
}

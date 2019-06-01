#include "Includes.h"


uint8_t txcnt = 0;
uint8_t rxcnt = 0;


static void Enter_DeepSleep(void)
{
    SCB->SCR |= 0x04;
    __WFI();
}

static void Enter_Sleep(void)
{
    SCB->SCR &= (~0x04);
    __WFI();
}

int main( void )
{
    BSP_Init();
    
    //BLE initnal
    BLE_Init();
    
    while(1)
    {

        //////user proc
        LED_RED_ON();

        //////ble rtx api
        txcnt=3; //txcnt=0 is for rx only application
        rxcnt=0; //rxcnt=0 is for tx only application
        BLE_TRX();

        Enter_DeepSleep(); //active by RTC
    }

}

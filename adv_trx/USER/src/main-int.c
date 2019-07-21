#include "Includes.h"


uint8_t txcnt = 0;
uint8_t rxcnt = 0;

extern void Key_Scan(void);
extern uint8_t ble_McuCanSleep(void);


static void Enter_DeepSleep(void)
{
    SCB->SCR |= 0x04;
    __WFI();
}


int main( void )
{
    BSP_Init();
    
    //BLE initnal
    BLE_Init();
    
    //////ble rtx api
    txcnt=3; //txcnt=0 is for rx only application
    rxcnt=6; //rxcnt=0 is for tx only application
    BLE_Start();
    
    while(1)
    {
        if (ble_McuCanSleep()){
            Enter_DeepSleep(); //active by RTC
        }
        //////user proc
        Key_Scan();
    }
}

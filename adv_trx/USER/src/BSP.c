#include "Includes.h"


/***
PC4=NSS,PC5=SCK,PC6=MOSI,PD2=MISO
PB4=IRQ

PD4=UART_TX, PD3=UART_RX

PC3=key1  //for demo
PA1=LED_g //for demo
PA2=LED_r //for demo

SPIDEBUG:
PA3=NSS,PB5=SCK,PD6=MOSI
***/

#define trim_24M    (*((volatile uint16_t*)(0x180000C0))&0x0fff);
#define trim_22M    (*((volatile uint16_t*)(0x180000C2))&0x0fff);
#define trim_16M    (*((volatile uint16_t*)(0x180000C4))&0x0fff);
#define trim_8M     (*((volatile uint16_t*)(0x180000C6))&0x0fff);
#define trim_4M     (*((volatile uint16_t*)(0x180000C8))&0x0fff);
//#define HIRC24M_FLASHADDR					0x180000C0
//#define HIRC22M_FLASHADDR					0x180000C2
//#define HIRC16M_FLASHADDR					0x180000C4
//#define HIRC8M_FLASHADDR					0x180000C6
//#define HIRC4M_FLASHADDR					0x180000C8

void SysClock_Init(void)
{
    RCC->REGLOCK = RCC_REGLOCKKEY;
    
    //system clock, default 4MHz
    //RCC->HIRCCR = 0x5a690000+trim_24M;  //system clock:24MHz
    RCC->CLKCON =  0x5a690205; //开启低频时钟
    while(!(RCC->LIRCCR&0x1000)); //LIRC_stable
    
    RCC->REGLOCK = RCC_RESGLOCKKEY;
    
    SysTick_Config(4000); //4M
    //SysTick_Config(24000); //24M
}
/*******************************************************************************
* Function   :      SPIM_Init
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
void SPIM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;

    
    RCC->AHBCLKEN = RCC_AHBPeriph_GPIOAEN   | 
                    RCC_AHBPeriph_GPIOBEN   | 
                    RCC_AHBPeriph_GPIOCEN   | 
                    RCC_AHBPeriph_GPIODEN;
    RCC->APBCLKEN = RCC_APBPeriph_SPICKEN   |
                    RCC_APBPeriph_UART0CKEN |
                    RCC_APBPeriph_IWDTCKEN;
    
#ifdef BLE_SPIDEBUG
    //IO映射调试内部BLE通讯，IRQ固定PB4
    //SPI_NSS :PA3
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_SetBits(GPIOA, GPIO_Pin_3);

    //SPI_MOSI :PD6
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    //SPI_CLK :PB5
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI_CLK_PB5); //Spiclk
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_SPI_MOSI_PD6); //Spimosi
#endif
    //SPI_NSS :PC4 (software)
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_SetBits(GPIOC, GPIO_Pin_4);

    //SPI_CLK :PC5
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    //SPI_MOSI :PC6
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    //SPI_MISO :PD2
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_SPI_CLK_PC5); //Spiclk
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_SPI_MISO_PD2); //Spimiso
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_SPI_MOSI_PC6); //Spimosi

    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_Init(SPI,&SPI_InitStruct);
    SPI_Cmd(SPI,ENABLE);   
}

#define UARTx UART0
#define TIMx  TIM10
void UART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    UART_InitTypeDef UART_InitStructure;

    //将USART Rx的GPIO配置为推挽复用模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOD,&GPIO_InitStruct);

    //将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOD,&GPIO_InitStruct);
    
    //uart GPIO管脚配置
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF_UART0_RX_PD3); //RX
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_UART0_TX_PD4); //TX

    // 配置串口的工作参数
    // 配置波特率
    UART_InitStructure.UART_BaudRate = 115200; //24M - 115200bps, 4M - 19200bps
    // 配置 针数据字长
    UART_InitStructure.UART_BaudRateDbaud_Enable = ENABLE;
    // 配置停止位
    UART_InitStructure.UART_BaudRateTimer_Selected = DISABLE;
    // 配置校验位
    UART_InitStructure.UART_Mode = UART_MODE1;

    // 完成串口的初始化配置
    UART_Init(UART0, TIMx, &UART_InitStructure);
    
    // 串口中断优先级配置
    //NVIC_Configuration();

    // 使能串口中断*/
    UART_ITConfig(UART0, UART_RIEN_EABLE, ENABLE);
    UART_ITConfig(UART0, UART_TIEN_EABLE, ENABLE);

    // 使能串口
    UART_Cmd(UART0, UART_RXEN_EABLE, ENABLE);
}

/*******************************************************************************
* Function   :      LED_KEY_Config
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
static void LED_KEY_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin  = LED1_GPIO_PORT_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin  = LED2_GPIO_PORT_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin  = KEY1_GPIO_PORT_PIN;   //key
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
}

/*******************************************************************************
* Function   :      RTCInit
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
void RTCInit(void)
{
    RTC_InitTypeDef RTC_InitStruct;

    RCC->APBCLKEN |= RCC_APBPeriph_RTCCKEN;
    
    RTC_DeInit(RTC);
    
    RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
    RTC_InitStruct.RTC_ClkSelect = RTC_ClkSelLIRC;
    RTC_InitStruct.RTC_AsynchPrediv = 1;
    RTC_Init(RTC,&RTC_InitStruct);

    RTC_RtcClkCmd(RTC,ENABLE);

    RTC_SetAlarm2(RTC,2);  //1-800ms, 2-400ms
    RTC_AlarmCmd(RTC,RTC_IT_ALM2, ENABLE);
    RTC_AlarmCmd(RTC,RTC_IT_ALMEN, ENABLE);

    NVIC_EnableIRQ(RTC_MATCH0_IRQn);
    NVIC_SetPriority(RTC_MATCH0_IRQn,2);

    RTC_CountCmd(RTC,ENABLE);
    
    RTC_Init(RTC,&RTC_InitStruct);
}

/*******************************************************************************
* Function   :      IWDG_Config
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
static void IWDG_Config(void)
{
    /*打开写保护*/
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
    IWDG_SetWdtMode(COMMAND_WDT_RESET);
    IWDG_SetReload(38400);//1s
    IWDG_Cmd();
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
}

/*******************************************************************************
* Function   :      BSP_Init
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
void BSP_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    GPI0_IRQ_InitTypeDef GPIO_IRQ_InitStruct;
    
    SysClock_Init();
    
    SPIM_Init();
    
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4;   //irq
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

#ifdef WMODE_INT    /*EXIT中断设置*/
    GPIO_IRQ_InitStruct.GPI0_IRQ_Pin_Type = DISABLE;        //0-边沿触发，1-电平触发
    GPIO_IRQ_InitStruct.GPI0_IRQ_Pin_Polarity = DISABLE;     //0-低电平或下降沿触发，1-高电平或上升沿触发
    GPIO_IRQ_InitStruct.GPI0_IRQ_Pin_Edge =  DISABLE;       //0-由上两个寄存器决定，1-上升沿和下降沿都触发中断
    GPIO_IRQ_InitStruct.GPI0_IRQ_Pin_Clear = ENABLE;        //1-清中断标志
    GPIO_IRQ_InitStruct.GPI0_IRQ_Pin_Enable = ENABLE;
    GPIO_EXTILineConfig(GPIOB,&GPIO_IRQ_InitStruct,GPIO_Pin_4);
    
    NVIC_InitStruct.NVIC_IRQChannel = GPIOB_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
#endif

    UART_Config();
    RTCInit();
    
    LED_KEY_Config();
    
//    IWDG_Config();
}

/*******************************************************************************
* Function   :      Uart_Send_Byte
* Parameter  :      uint8_t data
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
void Uart_Send_Byte(char data)
{
    uint8_t temp;
    uint8_t temp0[2];

    //1byte hex to asdcii 2byte.
    temp = data & 0x0F;
    temp0[0] = Hex2Ascii(temp);
    
    temp = data >> 4;
    temp0[1] = Hex2Ascii(temp);

    //usart send data
    UART_SendData(UARTx,temp0[1]);

    /* Wait until end of transmit */
    while(UART_GetITStatus(UARTx, UART_ISR_TI) !=  SET);
    UART_ClearITBit(UARTx, UART_ISR_TI);

    UART_SendData(UARTx,temp0[0]);
    /* Wait until end of transmit */
    while(UART_GetITStatus(UARTx, UART_ISR_TI) !=  SET);
    UART_ClearITBit(UARTx, UART_ISR_TI);
}

/*******************************************************************************
* Function   :      Uart_Send_String
* Parameter  :      uint8_t *data
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
void Uart_Send_String(char *data)
{
    //check string end char
    while(*data != '\0')
    {
        UART_SendData(UARTx,*data);

        /* Wait until end of transmit */
        while(UART_GetITStatus(UARTx, UART_ISR_TI) !=  SET);
        UART_ClearITBit(UARTx, UART_ISR_TI);
        
        data++;	
    }
}

/*******************************************************************************
* Function   :      KEY_GET
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
char KEY_GET(void)
{
    return (!GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PORT_PIN));
}

void LED_RED_ON(void)
{
    GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PORT_PIN);
}
void LED_RED_OFF(void)
{
    GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PORT_PIN);
}
void LED_GREEN_ON(void)
{
    GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PORT_PIN);
}
void LED_GREEN_OFF(void)
{
    GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PORT_PIN);
}

/*******************************************************************************
* Function   :      SysTick_Handler
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
unsigned short tick = 0;

void SysTick_Handler(void)
{
    NVIC_ClearPendingIRQ(SysTick_IRQn);
    if(tick>0) tick--;
}

/*******************************************************************************
* Function   :      RTC_MATCH0_IRQHandler
* Parameter  :      void
* Returns    :      void
* Description:
* Note:      :
*******************************************************************************/
void RTC_MATCH0_IRQHandler(void)
{
    RTC_ClearFlag(RTC,RTC_IT_ALM2);
#ifdef WMODE_INT
    BLE_Start();
#endif
}

void Delay_ms(uint16_t delayCnt)
{
    tick = delayCnt;
    while(tick);
}

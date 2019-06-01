#include "BSP.h"


/***
PC4=NSS,PC5=SCK,PC6=MOSI,PD2=MISO
PB4=IRQ

PD5=UART_TX, PD6=UART_RX

PC3=key1  //for demo
PA1=LED_g //for demo
PA2=LED_r //for demo

***/


void SysClock_Init(void)
{
    RCC->REGLOCK = 0x55aa6699;
    
    //system clock, default 4MHz
    //RCC->HIRCCR = 0x5a690d78; //24MHz
    SysTick_Config(4000);
    
    RCC->CLKCON =  0x5a690205; //开启低频时钟
    while(!(RCC->LIRCCR&0x1000)); //LIRC_stable
    
    RCC->REGLOCK = 0x55aa6698;
}

void SPIM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;

    
    RCC->AHBCLKEN = RCC_AHBPeriph_GPIOAEN   | 
                    RCC_AHBPeriph_GPIOBEN   | 
                    RCC_AHBPeriph_GPIOCEN   | 
                    RCC_AHBPeriph_GPIODEN;
    RCC->APBCLKEN = RCC_APBPeriph_SPICKEN   |
                    RCC_APBPeriph_UART1CKEN |
                    RCC_APBPeriph_IWDTCKEN;
    
    //SPI_MISO :PD2
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOD,&GPIO_InitStruct);

    //SPI_MOSI :PC6
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC,&GPIO_InitStruct);
         
    //SPI_CLK :PC5
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC,&GPIO_InitStruct);

    //SPI_NSS :PC4 (software)
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC,&GPIO_InitStruct);
    

    GPIO_PinAFConfig(GPIOC,GPIO_PinSource5,GPIO_AF_SPI_CLK_PC5); //Spiclk
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_SPI_MISO_PD2); //Spimiso
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_SPI_MOSI_PC6); //Spimosi
    
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_Init(SPI,&SPI_InitStruct);
    SPI_Cmd(SPI,ENABLE);
    
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4;   //irq
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
}

void UART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    UART_InitTypeDef UART_InitStructure;

    //将USART Rx的GPIO配置为推挽复用模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(GPIOD,&GPIO_InitStruct);

    
    //将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(GPIOD,&GPIO_InitStruct);
    
    //uart GPIO管脚配置
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_UART1_RX_PD6); //RX
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_UART1_TX_PD5); //TX

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
    UART_Init(UART1,TIM11, &UART_InitStructure);
    
    // 串口中断优先级配置
    //NVIC_Configuration();

    // 使能串口中断*/
    UART_ITConfig(UART1,UART_RIEN_EABLE,ENABLE);
    UART_ITConfig(UART1,UART_TIEN_EABLE,ENABLE);

    // 使能串口
    UART_Cmd(UART1,UART_RXEN_EABLE,ENABLE);
}

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
    NVIC_SetPriority(RTC_MATCH0_IRQn,4);

    RTC_CountCmd(RTC,ENABLE);
}

static void IWDG_Config(void)
{
    /*打开写保护*/
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
    IWDG_SetWdtMode(COMMAND_WDT_RESET);
    IWDG_SetReload(38400);//1s
    IWDG_Cmd();
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
}

void BSP_Init(void)
{
    SysClock_Init();
    
    SPIM_Init();
    UART_Config();
    RTCInit();
    
    LED_KEY_Config();
    
    IWDG_Config();
}

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
    UART_SendData(UART1,temp0[1]);

    /* Wait until end of transmit */
    while(UART_GetITStatus(UART1, UART_ISR_TI) !=  SET);
    UART_ClearITBit(UART1, UART_ISR_TI);

    UART_SendData(UART1,temp0[0]);
    /* Wait until end of transmit */
    while(UART_GetITStatus(UART1, UART_ISR_TI) !=  SET);
    UART_ClearITBit(UART1, UART_ISR_TI);
}
void Uart_Send_String(char *data)
{
    //check string end char
    while(*data != '\0')
    {
        UART_SendData(UART1,*data);

        /* Wait until end of transmit */
        while(UART_GetITStatus(UART1, UART_ISR_TI) !=  SET);
        UART_ClearITBit(UART1, UART_ISR_TI);
        
        data++;	
    }
}


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

unsigned short tick = 0;

void SysTick_Handler(void)
{
    NVIC_ClearPendingIRQ(SysTick_IRQn);
    if(tick>0) tick--;
}

void RTC_MATCH0_IRQHandler(void)
{
    RTC_ClearFlag(RTC,RTC_IT_ALM2);
}

void Delay_ms(uint16_t delayCnt)
{
    tick = delayCnt;
    while(tick);
}

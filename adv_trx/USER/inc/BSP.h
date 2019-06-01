#ifndef _BSP_H_
#define _BSP_H_
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "cx32l003_rcc.h"
#include "cx32l003_gpio.h"
#include "cx32l003_spi.h"
#include "cx32l003_uart.h"
#include "cx32l003_rtc.h"
#include "cx32l003_iwdt.h"


#define      LED1_GPIO_PORT                      GPIOA
#define      LED1_GPIO_PORT_PIN                  GPIO_Pin_1
#define      LED1_GPIO_PORT_PIN_SOURCE           GPIO_PinSource1

#define      LED2_GPIO_PORT                      GPIOA
#define      LED2_GPIO_PORT_PIN                  GPIO_Pin_2
#define      LED2_GPIO_PORT_PIN_SOURCE           GPIO_PinSource2

#define      KEY1_GPIO_PORT                      GPIOC
#define      KEY1_GPIO_PORT_PIN                  GPIO_Pin_3
#define      KEY1_GPIO_PORT_PIN_SOURCE           GPIO_PinSource3


#define Hex2Ascii(data)  (data < 10)? ('0' + data) : ('A' + data - 10)

void BSP_Init(void);
void Delay_ms(uint16_t delayCnt);

char KEY_GET(void);
void LED_RED_ON(void);
void LED_RED_OFF(void);
void LED_GREEN_ON(void);
void LED_GREEN_OFF(void);

void Uart_Send_Byte(char data);
void Uart_Send_String(char *data);


#endif

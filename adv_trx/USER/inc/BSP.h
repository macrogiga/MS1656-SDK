#ifndef _BSP_H_
#define _BSP_H_
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "cx32l003_rcc.h"
#include "cx32l003_gpio.h"
#include "cx32l003_exti.h"
#include "cx32l003_spi.h"
#include "cx32l003_uart.h"
#include "cx32l003_rtc.h"
#include "cx32l003_iwdt.h"
#include "misc.h"

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

extern void BSP_Init(void);
extern void Delay_ms(uint16_t delayCnt);

extern char KEY_GET(void);
extern void LED_RED_ON(void);
extern void LED_RED_OFF(void);
extern void LED_GREEN_ON(void);
extern void LED_GREEN_OFF(void);

extern void Uart_Send_Byte(char data);
extern void Uart_Send_String(char *data);


#endif

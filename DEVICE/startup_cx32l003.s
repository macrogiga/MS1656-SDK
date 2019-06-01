;/**************************************************************************//**
; * @file     startup_CX32S003.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM0plus Device Series
; * @version  V1.01
; * @date     23. November 2012
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler


                ; External Interrupts         
                DCD     GPIOA_IRQHandler          ; GPIOA_IRQn          = 0,
                DCD     GPIOB_IRQHandler          ; GPIOB_IRQn          = 1,
                DCD     GPIOC_IRQHandler          ; GPIOC_IRQn          = 2,
                DCD     GPIOD_IRQHandler          ; GPIOD_IRQn          = 3,
				DCD     0                         ; Reserved---------------4,
				DCD     0                         ; Reserved---------------5,
                DCD     UART0_IRQHandler          ; UART0_IRQn          = 6,
                DCD     UART1_IRQHandler          ; UART1_IRQn          = 7,
				DCD     LPUART_IRQHandler         ; LPUART_IRQn=8,
				DCD     0                         ; Reserved---------------9,
                DCD     SPI0COMB_IRQHandler       ; SPI0COMB_IRQn       = 10,
                DCD     SPI_DUMMYCOMB_IRQHandler  ; SPI_DUMMYCOMB_IRQn  = 11,
                DCD     I2C0_IRQHandler           ; I2C0_IRQn           = 12,
                DCD     I2C_DUMMY_IRQHandler      ; I2C_DUMMY_IRQn      = 13,
                DCD     TIMER10_IRQHandler         ; TIMER0_IRQn         = 14,
                DCD     TIMER11_IRQHandler         ; TIMER1_IRQn         = 15,
				DCD     LPTIMER_IRQHandler        ; LPTIMER_IRQn        = 16,
				DCD     0                         ; Reserved---------------17,
                DCD     PWM_IRQHandler            ; PWM_IRQn            = 18,
				DCD     ADVTIM_IRQHandler        ; Reserved---------------19,
				DCD     0                         ; Reserved---------------20,
                DCD     PCA_IRQHandler            ; PCA_IRQn            = 21,
                DCD     WWDT_IRQHandler           ; WWDT_IRQn           = 22,
                DCD     IWDT_IRQHandler           ; IWDT_IRQn           = 23,
                DCD     ADC0_IRQHandler           ; ADC0_IRQn           = 24,
				DCD     LVD_IRQHandler            ; LVD_IRQn            = 25
				DCD     VC_IRQHandler             ;VC_IRQn              = 26,,
				DCD     0                         ; Reserved---------------27,
				DCD     AWK_IRQHandler            ; AWK_IRQn            = 28,
				DCD     ONEWIRE_IRQHandler        ; ONEWIRE_IRQn        = 29,
                DCD     RTC_MATCH0_IRQHandler     ; RTC_MATCH0_IRQn     = 30,
                DCD     CLKTRIM_IRQHandler        ; CLKTRIM_IRQn        = 31      
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                ;IMPORT  SystemInit
                IMPORT  __main
			    ;LDR     R0, =SystemInit
                ;BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

				EXPORT  GPIOA_IRQHandler          [WEAK]  ; GPIOA_IRQn          = 0,                                                     
				EXPORT  GPIOB_IRQHandler          [WEAK]  ; GPIOB_IRQn          = 1,                                                     
				EXPORT  GPIOC_IRQHandler          [WEAK]  ; GPIOC_IRQn          = 2,                                                     
				EXPORT  GPIOD_IRQHandler          [WEAK]  ; GPIOD_IRQn          = 3,                                                     
				;EXPORT  0                         [WEAK]  ; Reserved---------------4,                                                    
				;EXPORT  0                         [WEAK]  ; Reserved---------------5,                                                    
				EXPORT  UART0_IRQHandler          [WEAK]  ; UART0_IRQn          = 6,                                                     
				EXPORT  UART1_IRQHandler          [WEAK]  ; UART1_IRQn          = 7,                                                     
				EXPORT  LPUART_IRQHandler          [WEAK]  ;LPUART_IRQn = 8,                                                    
				;EXPORT  0                         [WEAK]  ; Reserved---------------9,                                                    
				EXPORT  SPI0COMB_IRQHandler       [WEAK]  ; SPI0COMB_IRQn       = 10,                                                    
				EXPORT  SPI_DUMMYCOMB_IRQHandler  [WEAK]  ; SPI_DUMMYCOMB_IRQn  = 11,                                                    
				EXPORT  I2C0_IRQHandler           [WEAK]  ; I2C0_IRQn           = 12,                                                    
				EXPORT  I2C_DUMMY_IRQHandler      [WEAK]  ; I2C_DUMMY_IRQn      = 13,                                                    
				EXPORT  TIMER10_IRQHandler         [WEAK]  ; TIMER0_IRQn         = 14,                                                    
				EXPORT  TIMER11_IRQHandler         [WEAK]  ; TIMER1_IRQn         = 15,                                                    
				EXPORT  LPTIMER_IRQHandler        [WEAK]  ; LPTIMER_IRQn  = 16,                                                   
				;EXPORT  0                         [WEAK]  ; Reserved---------------17,                                                   
				EXPORT  PWM_IRQHandler            [WEAK]  ; PWM_IRQn            = 18,                                                    
				EXPORT  ADVTIM_IRQHandler        [WEAK]  ; ADVTim2---------------19,                                               
				;EXPORT  0                         [WEAK]  ; Reserved---------------20,                                                   
				EXPORT  PCA_IRQHandler            [WEAK]  ; PCA_IRQn            = 21,                                                    
				EXPORT  WWDT_IRQHandler           [WEAK]  ; WWDT_IRQn           = 22,                                                    
				EXPORT  IWDT_IRQHandler           [WEAK]  ; IWDT_IRQn           = 23,                                                    
				EXPORT  ADC0_IRQHandler           [WEAK]  ; ADC0_IRQn           = 24,                                                    
				EXPORT  LVD_IRQHandler            [WEAK]  ; LVD_IRQn            = 25,                                                
				EXPORT  VC_IRQHandler             [WEAK]  ; VC_IRQn             = 26,                                                   
				;EXPORT  0                         [WEAK]  ; Reserved---------------27,                                                   
				EXPORT  AWK_IRQHandler            [WEAK] ; AWK_IRQn    			= 28,                      
				EXPORT  ONEWIRE_IRQHandler        [WEAK] ; ONEWIRE_IRQn    		= 29,                       
				EXPORT  RTC_MATCH0_IRQHandler     [WEAK]  ;  RTC_MATCH0_IRQn    = 30,
				EXPORT  CLKTRIM_IRQHandler        [WEAK]  ;  CLKTRIM_IRQn       = 31 

                
 
 
GPIOA_IRQHandler          ; GPIOA_IRQn          = 0,                                                     
GPIOB_IRQHandler          ; GPIOB_IRQn          = 1,                                                     
GPIOC_IRQHandler          ; GPIOC_IRQn          = 2,                                                     
GPIOD_IRQHandler          ; GPIOD_IRQn          = 3,                                                     
;0                         ; Reserved---------------4,                                                    
;0                         ; Reserved---------------5,                                                    
UART0_IRQHandler          ; UART0_IRQn          = 6,                                                     
UART1_IRQHandler          ; UART1_IRQn          = 7,                                                     
LPUART_IRQHandler         ; LPUART_IRQn = 8,                                                    
;0                         ; Reserved---------------9,                                                    
SPI0COMB_IRQHandler       ; SPI0COMB_IRQn       = 10,                                                    
SPI_DUMMYCOMB_IRQHandler  ; SPI_DUMMYCOMB_IRQn  = 11,                                                    
I2C0_IRQHandler           ; I2C0_IRQn           = 12,                                                    
I2C_DUMMY_IRQHandler      ; I2C_DUMMY_IRQn      = 13,                                                    
TIMER10_IRQHandler         ; TIMER0_IRQn         = 14,                                                    
TIMER11_IRQHandler         ; TIMER1_IRQn         = 15,                                                    
LPTIMER_IRQHandler        ; LPTIMER_IRQn  = 16,,                                                   
;0                         ; Reserved---------------17,                                                   
PWM_IRQHandler            ; PWM_IRQn            = 18,                                                    
ADVTIM_IRQHandler        ; ADVTim_IRQn---------------19,                                                     
;0                         ; Reserved---------------20,                                                   
PCA_IRQHandler            ; PCA_IRQn            = 21,                                                    
WWDT_IRQHandler           ; WWDT_IRQn           = 22,                                                    
IWDT_IRQHandler           ; IWDT_IRQn           = 23,                                                    
ADC0_IRQHandler           ; ADC0_IRQn           = 24,                                                    
LVD_IRQHandler            ; LVD_IRQn            = 25,                                                   
VC_IRQHandler             ; VC_IRQn             = 26,                                                     
;0                         ; Reserved---------------27,                                                   
AWK_IRQHandler             ; AWK_IRQn            =   28,                                                 
ONEWIRE_IRQHandler         ; ONEWIRE_IRQn            =   29,                        
RTC_MATCH0_IRQHandler     ; RTC_MATCH0_IRQn     = 30, C_MATCH0_IRQHandler     
CLKTRIM_IRQHandler        ; CLKTRIM_IRQn        = 31  KTRIM_IRQHandler       
      
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END

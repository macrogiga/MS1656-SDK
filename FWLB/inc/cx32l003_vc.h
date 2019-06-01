/**
  ******************************************************************************
  * @file    cx32l003_vc.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the SYSCFG firmware
  *          library. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under MCU Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/*Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32l003_VC_H
#define __CX32l003_VC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"
	 
	 
/* Exported types ------------------------------------------------------------*/
#define IS_VC_ALL_PERIPH(PERIPH) (((PERIPH) == VC) 
	 
	 
#define VC_PIN_MASK     ((uint32_t)0x00000003)
#define VC_NIN_MASK     ((uint32_t)0x00000003<<2)
#define VC_V25DIV_MASK  ((uint32_t)0x00000007<<4)
	 
#define VC_PIN_SEL(PIN) ((PIN>=0x00000000)||\
	                       (PIN <=0x00000003))
#define VC_NIN_SEL(NIN) ((PIN>=0x00000000)||\
	                       ((NIN&0xfffffff3) ==0x00000000))
	 
	 
#define V25DIV_00     ((uint32_t)0x00000000<<4)	 
#define V25DIV_01     ((uint32_t)0x00000001<<4)	 
#define V25DIV_02     ((uint32_t)0x00000002<<4)	 
#define V25DIV_03     ((uint32_t)0x00000003<<4)	 
#define V25DIV_04     ((uint32_t)0x00000004<<4)	 
#define V25DIV_05     ((uint32_t)0x00000005<<4)	 
#define V25DIV_06     ((uint32_t)0x00000006<<4)	 
#define V25DIV_07     ((uint32_t)0x00000007<<4)	 
#define VC_V25DIV_SEL(V25DIV) ((V25DIV>=0x00000000)||\
                               ((NIN&0xffffcfff) ==0x00000000))

#define V25DIV_ENABLE    ((uint32_t)0x00000040)	
#define V25DIV_DISABLE   ((uint32_t)0x00000000)	


#define VC_ENABLE    ((uint32_t)0x00000001)	
#define VC_DISABLE   ((uint32_t)0x00000000)	




#define VC_FLTCLK_MASK   ((uint32_t)0x0000000c)

#define VC_FLT_ENABLE    (uint32_t)0x00000100
#define VC_FLT_DISABLE   (uint32_t)0x00000000
#define IS_VC_FLT(NewStauts)  ((NewStauts== VC_FLT_ENABLE) ||\
	                             (NewStauts == VC_FLT_DISABLE))


#define VC_FALLINT_ENABLE   (uint32_t)0x00001000
#define VC_FALLINT_DISABLE  (uint32_t)0x00000000
#define IS_VC_FALLINT(NewStauts)  ((NewStauts== VC_FALLINT_ENABLE) ||\
                                   (NewStauts == VC_FALLINT_DISABLE))

#define VC_RISEINT_ENABLE   (uint32_t)0x00002000
#define VC_RISEINT_DISABLE  (uint32_t)0x00000000
#define IS_VC_RISEINT(NewStauts)  ((NewStauts== VC_RISEINT_ENABLE) ||\
                                   (NewStauts == VC_RISEINT_DISABLE))
																												
#define VC_HIGHINT_ENABLE   (uint32_t)0x00004000
#define VC_HIGHINT_DISABLE  (uint32_t)0x00000000
#define IS_VC_HIGHINT(NewStauts)  ((NewStauts== VC_HIGHINT_ENABLE) ||\
                                   (NewStauts == VC_HIGHINT_DISABLE))
																												
																																												
#define VC_TI_ENABLE   (uint32_t)0x00008000
#define VC_TI_DISABLE  (uint32_t)0x00000000
#define IS_VC_INT(NewStauts)  ((NewStauts== VC_INT_ENABLE) ||\
                               (NewStauts == VC_INT_DISABLE))
																												



#define VC_FLTNUM_MASK           (uint32_t)0xffff0000
#define VC_INV2TM012G_ENABLE     (uint32_t)0x00000001
#define VC2TM10G_ENABLE          (uint32_t)0x00000002
#define VC2TM11G_ENABLE          (uint32_t)0x00000004
#define VC2TMLptm_ENABLE         (uint32_t)0x00000010
#define VC2TMLptmeclk_ENABLE     (uint32_t)0x00000020
#define VC_INV2PCA_ENABLE        (uint32_t)0x00000040
#define VC2PCA_CAP0_ENABLE       (uint32_t)0x00000080
#define VC2PCA_ECI_ENABLE        (uint32_t)0x00000100
#define VC_INV2TM1_CH1G_ENABLE   (uint32_t)0x00000200
#define VC2TM1_CH1G_ENABLE       (uint32_t)0x00000400
#define VC_INV2TM1_CH2G_ENABLE   (uint32_t)0x00000800
#define VC2TM1_CH2G_ENABLE       (uint32_t)0x00001000
#define VC_INV2TM1_CH3G_ENABLE   (uint32_t)0x00002000
#define VC2TM1_CH3G_ENABLE       (uint32_t)0x00004000
#define VC_INV2TM1_CH4G_ENABLE   (uint32_t)0x00008000
#define VC2TM1_CH4G_ENABLE       (uint32_t)0x00010000
#define VC2BRAKE_ENABLE          (uint32_t)0x00020000
#define VC_INV2PORT_ENABLE       (uint32_t)0x00040000

#define  IS_VC2_Status(NewStatus) ((NewStatus>= (uint32_t)0x00000000)||\
                                    ((NewStatus & 0x00080000) == (uint32_t)0x00000000))
																		
#define  VC_IRFLAG   ((uint32_t)0x00000001)


/*define function*/
void VC_SetPin(VC_TypeDef *VCx,uint32_t PIN);
void VC_SetNin(VC_TypeDef *VCx,uint32_t NIN);
void VC_SetV25Div(VC_TypeDef *VCx,uint32_t V25DIV);
void VC_V25DivCmd(VC_TypeDef *VCx,FunctionalState NewState);
void VC_Cmd(VC_TypeDef *VCx,FunctionalState NewState);
void VC_SetFltClk(VC_TypeDef *VCx,uint32_t FLTCLK);
void VC_FLTCmd(VC_TypeDef *VCx,FunctionalState NewState);
void VC_FallITCmd(VC_TypeDef *VCx,FunctionalState NewState);
void VC_RiseITCmd(VC_TypeDef *VCx,FunctionalState NewState);
void VC_HighITCmd(VC_TypeDef *VCx,FunctionalState NewState);
void VC_SetFltNum(VC_TypeDef *VCx,uint32_t FltNum);
void VC_OutCfgCmd(VC_TypeDef *VCx,uint32_t OutCfgStatus,FunctionalState NewState);
FlagStatus VC_GetFlagStatus(VC_TypeDef *VCx,uint16_t VC_FLAG);
void VC_ClearITFlag(VC_TypeDef *VCx);
void VC_ITConfig(VC_TypeDef *VCx,FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif

/**
  * @}
  */

/**
  * @}
  */


/************************(C) COPYRIGHT cx32l003*****END OF FILE****/







	 
	 




/******************************************************************************
  * @file    cx32l003_flash.h
  * @author  MCU_BU Application Team
  * @version V0.0.0
  * @date    28-5-2019
  * @brief   This file contains all the functions prototypes for the FLASH 
  *          firmware library.
  ******************************************************************************
  * @attention
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CX32L003_FLASH_
#define _CX32L003_FLASH_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"





/* Exported types ------------------------------------------------------------*/
/** 
  * @brief FLASH Status  
  */ 
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_COMPLETE
}FLASH_Status;

/* Exported constants --------------------------------------------------------*/

#define    ISP_KEY      (uint32_t)0x5a690000

#define    FLASH_SECTOR_SIZE       512
#define    FLASH_SLOCK0_SIZE       64
#define    FLASH_SLOCK1_SIZE       128

/*FLASH OPERATION*/
#define    FLASH_READ            (uint32_t)0x00000000
#define    FLASH_PROGRAM         (uint32_t)0x00000001 
#define    FLASH_SECTOREARSE     (uint32_t)0x00000002
#define    FLASH_CHIPEARSE       (uint32_t)0x00000003
#define    FLASH_OPERATION_MASK  (uint32_t)0xFFFFFF00      



#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x00000000) && ((ADDRESS) <= 0xFFFFFFFF))
                                  
/** @defgroup Option_Bytes_Write_Protection 
  * @{
  */ 
#define OB_WRP_Sector0_1       ((uint32_t)0x00000001) /*!< Write protection of Sector0_1     */
#define OB_WRP_Sector2_3       ((uint32_t)0x00000002) /*!< Write protection of Sector2_3     */
#define OB_WRP_Sector4_5       ((uint32_t)0x00000004) /*!< Write protection of Sector4_5     */
#define OB_WRP_Sector6_7       ((uint32_t)0x00000008) /*!< Write protection of Sector6_7     */
#define OB_WRP_Sector8_9       ((uint32_t)0x00000010) /*!< Write protection of Sector8_9     */
#define OB_WRP_Sector10_11     ((uint32_t)0x00000020) /*!< Write protection of Sector10_11     */
#define OB_WRP_Sector12_13     ((uint32_t)0x00000040) /*!< Write protection of Sector12_13      */
#define OB_WRP_Sector14_15     ((uint32_t)0x00000080) /*!< Write protection of Sector14_15     */
#define OB_WRP_Sector16_17     ((uint32_t)0x00000100) /*!< Write protection of Sector16_17     */
#define OB_WRP_Sector18_19     ((uint32_t)0x00000200) /*!< Write protection of Sector18_19      */
#define OB_WRP_Sector20_21     ((uint32_t)0x00000400) /*!< Write protection of Sector20_21    */
#define OB_WRP_Sector22_23     ((uint32_t)0x00000800) /*!< Write protection of Sector22_23     */
#define OB_WRP_Sector24_25     ((uint32_t)0x00001000) /*!< Write protection of Sector24_25      */
#define OB_WRP_Sector26_27     ((uint32_t)0x00002000) /*!< Write protection of Sector26_27     */
#define OB_WRP_Sector28_29     ((uint32_t)0x00004000) /*!< Write protection of Sector28_29     */
#define OB_WRP_Sector30_31     ((uint32_t)0x00008000) /*!< Write protection of Sector30_31     */
#define OB_WRP_Sector32_33     ((uint32_t)0x00010000) /*!< Write protection of Sector32_33     */
#define OB_WRP_Sector34_35     ((uint32_t)0x00020000) /*!< Write protection of Sector34_35      */
#define OB_WRP_Sector36_37     ((uint32_t)0x00040000) /*!< Write protection of Sector36_37     */
#define OB_WRP_Sector38_39     ((uint32_t)0x00080000) /*!< Write protection of Sector38_39     */
#define OB_WRP_Sector40_41     ((uint32_t)0x00100000) /*!< Write protection of Sector40_41     */
#define OB_WRP_Sector42_43     ((uint32_t)0x00200000) /*!< Write protection of Sector42_43      */
#define OB_WRP_Sector44_45     ((uint32_t)0x00400000) /*!< Write protection of Sector44_45    */
#define OB_WRP_Sector46_47     ((uint32_t)0x00800000) /*!< Write protection of Sector46_47    */
#define OB_WRP_Sector48_49     ((uint32_t)0x01000000) /*!< Write protection of Sector48_49     */
#define OB_WRP_Sector50_51     ((uint32_t)0x02000000) /*!< Write protection of Sector50_51     */
#define OB_WRP_Sector52_53     ((uint32_t)0x04000000) /*!< Write protection of Sector52_53     */
#define OB_WRP_Sector54_55     ((uint32_t)0x08000000) /*!< Write protection of Sector54_55     */
#define OB_WRP_Sector56_57     ((uint32_t)0x10000000) /*!< Write protection of Sector56_57     */
#define OB_WRP_Sector58_59     ((uint32_t)0x20000000) /*!< Write protection of Sector58_59      */
#define OB_WRP_Sector60_61     ((uint32_t)0x40000000) /*!< Write protection of Sector60_61     */
#define OB_WRP_Sector62_63     ((uint32_t)0x80000000) /*!< Write protection of Sector62_63     */
#define OB_WRP_Sector0_63      ((uint32_t)0xffffffff) /*!< Write protection of Sector0_63     */


#define OB_WRP_Sector64_65       ((uint32_t)0x00000001) /*!< Write protection of Sector64_65     */
#define OB_WRP_Sector66_67       ((uint32_t)0x00000002) /*!< Write protection of Sector66_67     */
#define OB_WRP_Sector68_69       ((uint32_t)0x00000004) /*!< Write protection of Sector68_69      */
#define OB_WRP_Sector70_71       ((uint32_t)0x00000008) /*!< Write protection of Sector70_71     */
#define OB_WRP_Sector72_73       ((uint32_t)0x00000010) /*!< Write protection of Sector72_73     */
#define OB_WRP_Sector74_75       ((uint32_t)0x00000020) /*!< Write protection of Sector74_75     */
#define OB_WRP_Sector76_77       ((uint32_t)0x00000040) /*!< Write protection of Sector76_77      */
#define OB_WRP_Sector78_79       ((uint32_t)0x00000080) /*!< Write protection of Sector78_79     */
#define OB_WRP_Sector80_81       ((uint32_t)0x00000100) /*!< Write protection of Sector80_81    */
#define OB_WRP_Sector82_83       ((uint32_t)0x00000200) /*!< Write protection of Sector82_83     */
#define OB_WRP_Sector84_85       ((uint32_t)0x00000400) /*!< Write protection of Sector84_85    */
#define OB_WRP_Sector86_87       ((uint32_t)0x00000800) /*!< Write protection of Sector86_87       */
#define OB_WRP_Sector88_89       ((uint32_t)0x00001000) /*!< Write protection of Sector88_89        */
#define OB_WRP_Sector90_91       ((uint32_t)0x00002000) /*!< Write protection of Sector90_91    */
#define OB_WRP_Sector92_93       ((uint32_t)0x00004000) /*!< Write protection of Sector92_93      */
#define OB_WRP_Sector94_95       ((uint32_t)0x00008000) /*!< Write protection of Sector94_95      */
#define OB_WRP_Sector96_97       ((uint32_t)0x00010000) /*!< Write protection of Sector96_97      */
#define OB_WRP_Sector98_99       ((uint32_t)0x00020000) /*!< Write protection of Sector98_99     */
#define OB_WRP_Sector100_101     ((uint32_t)0x00040000) /*!< Write protection of Sector100_101     */
#define OB_WRP_Sector102_103     ((uint32_t)0x00080000) /*!< Write protection of Sector102_103      */
#define OB_WRP_Sector104_105     ((uint32_t)0x00100000) /*!< Write protection of Sector104_105     */
#define OB_WRP_Sector106_107     ((uint32_t)0x00200000) /*!< Write protection of Sector106_107      */
#define OB_WRP_Sector108_109     ((uint32_t)0x00400000) /*!< Write protection of Sector108_109    */
#define OB_WRP_Sector110_111     ((uint32_t)0x00800000) /*!< Write protection of Sector110_111    */
#define OB_WRP_Sector112_113     ((uint32_t)0x01000000) /*!< Write protection of Sector112_113    */
#define OB_WRP_Sector114_115     ((uint32_t)0x02000000) /*!< Write protection of Sector114_115    */
#define OB_WRP_Sector116_117     ((uint32_t)0x04000000) /*!< Write protection of Sector116_117  */
#define OB_WRP_Sector118_119     ((uint32_t)0x08000000) /*!< Write protection of Sector118_119    */
#define OB_WRP_Sector120_121     ((uint32_t)0x10000000) /*!< Write protection of Sector120_121     */
#define OB_WRP_Sector122_123     ((uint32_t)0x20000000) /*!< Write protection of Sector122_123     */
#define OB_WRP_Sector124_125     ((uint32_t)0x40000000) /*!< Write protection of Sector124_125     */
#define OB_WRP_Sector126_127     ((uint32_t)0x80000000) /*!< Write protection of Sector126_127    */
#define OB_WRP_Sector64_127      ((uint32_t)0xffffffff) /*!< Write protection of Sector126_127    */
#define IS_OB_WRP(SECTOR)    (((SECTOR) >= 0x00000000) && ((SECTOR) <= 0xffffffff))


/** @defgroup FLASH_Option_Bytes_Read_Protection 
  * @{
  */
#define OB_ISP_BOOT   ((uint32_t)0x00000001)
#define OB_APP_BOOT   ((uint32_t)0x00000001)

#define IS_OB_BOOT(BOOT)   ((BOOT) == OB_ISP_BOOT || (BOOT) == OB_APP_BOOT)
                       
													
													
/** @defgroup FLASH_Interrupts 
  * @{
  */ 
#define FLASH_IT_PC                   ((uint32_t)0x00000008)  /*FLASH FLAG IT PC FLAG */
#define FLASH_IT_PROTECT              ((uint32_t)0x00000010)  /*FLASH FLAG IT PROTECT FLAG */
#define IS_FLASH_IT(IT) ((IT == FLASH_IT_PC )||(IT == FLASH_FLAG_IT_PROTECT ))

/** @defgroup FLASH_Interrupts_Flags 
  * @{
  */ 
#define FLASH_FLAG_IT_PC                   ((uint32_t)0x00000001)  /*FLASH FLAG IT PC FLAG */
#define FLASH_FLAG_IT_PROTECT              ((uint32_t)0x00000002)  /*FLASH FLAG IT PROTECT FLAG */
#define FLASH_FLAG_ALL                     ((uint32_t)0x00000003)  /*FLASH FLAG IT PROTECT FLAG */

#define IS_FLASH_FLAG_IT(FLAG) ((FLAG == FLASH_FLAG_IT_PC )||(FLAG == FLASH_FLAG_IT_PROTECT )\
                                 (FLAG == FLASH_FLAG_ALL))



/** @defgroup FLASH_Flags 
  * @{
  */ 
#define FLASH_FLAG_BUSY                 ((uint32_t)0x00000004)  /*!< FLASH Busy flag                           */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
FLASH_Status FLASH_EraseSector(uint32_t FLASH_Addr);
FLASH_Status FLASH_EraseAllSectors(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data);
void FLASH_OB_WRPConfig(uint32_t OB_Sector, uint32_t OB_WRP, FunctionalState NewState);
void FLASH_OB_UserConfig(FunctionalState NewState);
void FLASH_OB_ISPConfig(FunctionalState NewState);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(void); 

#ifdef __cplusplus
}
#endif

#endif /* _CX32L003_FLASH */


/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT XMC *****END OF FILE****/







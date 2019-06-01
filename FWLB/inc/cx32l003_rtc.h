/**
  ******************************************************************************
  * @file    cx32l003_rtc.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the RTC firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 XMC</center></h2>
  *
  * Licensed under XMC Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ****************************************************************************** 
  */
	
	
/* Define to prevent recursive inclusion -----------*/
#ifndef __CX32l003_RTC_H
#define __CX32l003_RTC_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003.h"
#include "cx32l003_conf.h"



/* Exported types ------------------------------------------------------------*/
#define IS_RTC_ALL_PERIPH(PERIPH) ((PERIPH) == RTC)

/** 
  * @brief  RTC Init structures definition  
  */ 
typedef struct
{
  uint32_t RTC_HourFormat;   /*!< Specifies the RTC Hour Format.
                             This parameter can be a value of @ref RTC_Hour_Formats */
  
  uint32_t RTC_AsynchPrediv; /*!< Specifies the RTC Asynchronous Predivider value.
                             This parameter must be set to a value lower than 0x7F */
  
  uint32_t RTC_ClkSelect;  /*!< Specifies the RTC Synchronous Predivider value.
                             This parameter must be set to a value lower than 0x7FFF */
}RTC_InitTypeDef;

/** 
  * @brief  RTC Time structure definition  
  */
typedef struct
{
  uint32_t RTC_WeekDay; /*!< Specifies the RTC Date WeekDay.
                        This parameter can be a value of @ref RTC_WeekDay_Definitions */
  uint32_t RTC_Hours;    /*!< Specifies the RTC Time Hour.
                        This parameter must be set to a value in the 0-12 range
                        if the RTC_HourFormat_12 is selected or 0-23 range if
                        the RTC_HourFormat_24 is selected. */

  uint32_t RTC_Minutes;  /*!< Specifies the RTC Time Minutes.
                        This parameter must be set to a value in the 0-59 range. */
  
  uint32_t RTC_Seconds;  /*!< Specifies the RTC Time Seconds.
                        This parameter must be set to a value in the 0-59 range. */

  uint32_t RTC_H12;      /*!< Specifies the RTC AM/PM Time.
                        This parameter can be a value of @ref RTC_AM_PM_Definitions */
}RTC_TimeTypeDef; 

/** 
  * @brief  RTC Date structure definition  
  */
typedef struct
{ 
  uint32_t RTC_Month;   /*!< Specifies the RTC Date Month (in BCD format).
                        This parameter can be a value of @ref RTC_Month_Date_Definitions */

  uint32_t RTC_Date;     /*!< Specifies the RTC Date.
                        This parameter must be set to a value in the 1-31 range. */
	
  uint32_t RTC_Century;     /*!< Specifies the RTC Date Year.
                        This parameter must be set to a value in the 0/1 range. */
  
  uint32_t RTC_Year;     /*!< Specifies the RTC Date Year.
                        This parameter must be set to a value in the 0-99 range. */
}RTC_DateTypeDef;


/** 
  * @brief  RTC Date structure definition  
  */
typedef struct
{
  uint8_t RTC_YearAlarmEable;     /*!< Specifies the RTC  Year Alarm Eable.*/
                                   
  uint8_t RTC_MonthAlarmEable;    /*!< Specifies the RTC  Month Alarm Eable.*/
                                  
  uint8_t RTC_DateAlarmEable;      /*!< Specifies the RTC Date Year Alarm Eable.*/
		
  uint8_t RTC_WeekAlarmEable;     /*!< Specifies the RTC Week Year Alarm Eable.*/
	
	uint8_t RTC_HourAlarmEable;     /*!< Specifies the RTC Week Hour Alarm Eable.*/
	
	uint8_t RTC_MinAlarmEable;     /*!< Specifies the RTC Week Min Alarm Eable.*/
	
  uint8_t RTC_SecAlarmEable;     /*!< Specifies the RTC Week Sec Alarm Eable.*/
	
}RTC_AlarmTypeEnableDef;

/** 
  * @brief  RTC Alarm structure definition  
  */
typedef struct
{
  RTC_TimeTypeDef RTC_AlarmTime;     /*!< Specifies the RTC Alarm Time members. */
	
	RTC_DateTypeDef RTC_AlarmDate;     /*!< Specifies the RTC Alarm Date members. */
	
}RTC_AlarmTypeDef;


/** @defgroup RTC_Hour_Formats 
  * @{
  */ 
#define RTC_HourFormat_24              ((uint32_t)0x00000004)
#define RTC_HourFormat_12              ((uint32_t)0x00000000)
#define IS_RTC_HOUR_FORMAT(FORMAT)     (((FORMAT) == RTC_HourFormat_12)||\
                                       ((FORMAT) == RTC_HourFormat_24))

#define  RTC_AsynchPrediv_mask         ((uint32_t)0x000003ff)

/** @defgroup RTC_CLK_SEL 
  * @{
  */ 
#define  RTC_ClkSelMask               ((uint32_t)0x00030000)
#define  RTC_ClkSelLXT                ((uint32_t)0x00000000)
#define  RTC_ClkSelLIRC               ((uint32_t)0x00010000)
#define  RTC_ClkSelFhxt               ((uint32_t)0x00020000)
#define IS_RTC_CLK_SEL(CLK)     (((CLK) == RTC_ClkSelMask) ||\
																 ((CLK) == RTC_ClkSelLXT)  ||\
                                 ((CLK) == RTC_ClkSelLIRC) ||\
                                 ((CLK) == RTC_ClkSelFhxt))

/** @defgroup RTC_Asynchronous_Predivider 
  * @{
  */ 
#define IS_RTC_ASYNCH_PREDIV(PREDIV)   ((PREDIV) <= 0x3FF)
 

/** @defgroup RTC_Time_Definitions 
  * @{
  */ 
#define IS_RTC_HOUR12(HOUR)            (((HOUR) > 0) && ((HOUR) <= 12))
#define IS_RTC_HOUR24(HOUR)            ((HOUR) <= 23)
#define IS_RTC_MINUTES(MINUTES)        ((MINUTES) <= 59)
#define IS_RTC_SECONDS(SECONDS)        ((SECONDS) <= 59)

/**
  * @}
  */ 
#define RTC_CLK_RESERVED   ((uint32_t)0x00030000)
#define RTC_CLK_LXT   ((uint32_t)0x00000000)
#define RTC_CLK_LIRC   ((uint32_t)0x00010000)
#define RTC_CLK_FHXT   ((uint32_t)0x00020000)

/** @defgroup RTC_AM_PM_Definitions 
  * @{
  */ 
#define RTC_H12_AM                     ((uint8_t)0x00)
#define RTC_H12_PM                     ((uint8_t)0x00200000)
#define IS_RTC_H12(PM) (((PM) == RTC_H12_AM) || ((PM) == RTC_H12_PM))

/**
  * @}RTC_ISR
  */ 
#define RTC_ISR_ALARM2_RAW                ((uint32_t)0x00000020)
#define RTC_ISR_ALARM1_RAW                ((uint32_t)0x00000010)
#define RTC_ISR_RSF                       ((uint32_t)0x00000004)
#define RTC_ISR_WAITF                     ((uint32_t)0x00000002)
#define RTC_ISR_WAIT                      ((uint32_t)0x00000001)
#define RTC_CR_BYPSHAD                    ((uint32_t)0x00000001)


/**
  * @}Masks Definition
  */ 
#define RTC_TR_RESERVED_MASK    ((uint32_t)0x073F7F7F)
#define RTC_DATE_RESERVED_MASK  ((uint32_t)0x00FF9F3F) 
#define RTC_INIT_MASK           ((uint32_t)0xFFFFFFFF)  
#define RTC_RSF_MASK            ((uint32_t)0xFFFFFFFB)
#define RTC_FLAGS_MASK          ((uint32_t)((RTC_INIT_MASK)|\
                                            (RTC_RSF_MASK)) 
                                           
/**
  * @}Masks Definition MODE_TIMEOUT
  */ 	
#define INITMODE_TIMEOUT         ((uint32_t) 0x00010000)
#define SYNCHRO_TIMEOUT          ((uint32_t) 0x00020000)
#define RECALPF_TIMEOUT          ((uint32_t) 0x00020000)
#define SHPF_TIMEOUT             ((uint32_t) 0x00001000)



/** @defgroup RTC_Year_Date_Definitions 
  * @{
  */ 
#define IS_RTC_YEAR(YEAR)              ((YEAR) <= 99)

/**
  * @}
  */ 

/** @defgroup RTC_Month_Date_Definitions 
  * @{
  */ 
#define RTC_Month_January              ((uint8_t)0x01)
#define RTC_Month_February             ((uint8_t)0x02)
#define RTC_Month_March                ((uint8_t)0x03)
#define RTC_Month_April                ((uint8_t)0x04)
#define RTC_Month_May                  ((uint8_t)0x05)
#define RTC_Month_June                 ((uint8_t)0x06)
#define RTC_Month_July                 ((uint8_t)0x07)
#define RTC_Month_August               ((uint8_t)0x08)
#define RTC_Month_September            ((uint8_t)0x09)
#define RTC_Month_October              ((uint8_t)0x10)
#define RTC_Month_November             ((uint8_t)0x11)
#define RTC_Month_December             ((uint8_t)0x12)
#define IS_RTC_MONTH(MONTH)            (((MONTH) >= 1) &&((MONTH) <= 12))
#define IS_RTC_DATE(DATE)              (((DATE) >= 1) && ((DATE) <= 31))

 
/** @defgroup RTC_WeekDay_Definitions 
  * @{
  */ 
  
#define RTC_Weekday_Monday             ((uint8_t)0x00)
#define RTC_Weekday_Tuesday            ((uint8_t)0x01)
#define RTC_Weekday_Wednesday          ((uint8_t)0x02)
#define RTC_Weekday_Thursday           ((uint8_t)0x03)
#define RTC_Weekday_Friday             ((uint8_t)0x04)
#define RTC_Weekday_Saturday           ((uint8_t)0x05)
#define RTC_Weekday_Sunday             ((uint8_t)0x06)
#define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday)    || \
                                 ((WEEKDAY) == RTC_Weekday_Tuesday)   || \
                                 ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                 ((WEEKDAY) == RTC_Weekday_Thursday)  || \
                                 ((WEEKDAY) == RTC_Weekday_Friday)    || \
                                 ((WEEKDAY) == RTC_Weekday_Saturday)  || \
                                 ((WEEKDAY) == RTC_Weekday_Sunday))
/**
  * @}
  */ 


/** @defgroup RTC_Alarm_Definitions
  * @{
  */ 
#define IS_RTC_ALARM_DATE_WEEKDAY_DATE(DATE) (((DATE) > 0) && ((DATE) <= 31))
#define IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday)    || \
                                                    ((WEEKDAY) == RTC_Weekday_Tuesday)   || \
                                                    ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                                    ((WEEKDAY) == RTC_Weekday_Thursday)  || \
                                                    ((WEEKDAY) == RTC_Weekday_Friday)    || \
                                                    ((WEEKDAY) == RTC_Weekday_Saturday)  || \
                                                    ((WEEKDAY) == RTC_Weekday_Sunday))

/** @defgroup RTC_AlarmDateWeekDay_Definitions 
  * @{
  */ 
#define RTC_AlarmDateWeekDaySel_Date      ((uint32_t)0x07000000)
#define RTC_AlarmDateWeekDaySel_WeekDay   ((uint32_t)0x07000000)

#define IS_RTC_ALARM_DATE_WEEKDAY_SEL(SEL) (((SEL) == RTC_AlarmDateWeekDaySel_Date) || \
                                            ((SEL) == RTC_AlarmDateWeekDaySel_WeekDay))

/**
  * @}
  */ 

/** @defgroup RTC_Input_parameter_format_definitions 
  * @{
  */ 
#define RTC_Format_BIN                    ((uint32_t)0x000000000)
#define RTC_Format_BCD                    ((uint32_t)0x000000001)
#define IS_RTC_FORMAT(FORMAT)     (((FORMAT) == RTC_Format_BIN) ||\
                                   ((FORMAT) == RTC_Format_BCD))


/** @defgroup RTC_Alarms_Definitions 
  * @{
  */ 
#define RTC_Alarm_Enable                       ((uint32_t)0x00000040)
#define RTC_Alarm_Disable                      ((uint32_t)0x00000040)


/** @defgroup RTC_AlarmEnable_Definitions 
  * @{
  */ 
#define RTC_AlarmYear_ENABLE              ((uint32_t)0x40000000)
#define RTC_AlarmMon_ENABLE               ((uint32_t)0x20000000)
#define RTC_AlarmDay_ENABLE               ((uint32_t)0x10000000)
#define RTC_AlarmWeek_ENABLE              ((uint32_t)0x08000000)
#define RTC_AlarmHour_ENABLE              ((uint32_t)0x04000000)
#define RTC_AlarmMin_ENABLE               ((uint32_t)0x02000000)
#define RTC_AlarmSec_ENABLE               ((uint32_t)0x01000000)
#define RTC_AlarmAll_ENABLE               ((uint32_t)0x7f000000)


/** @defgroup RTC_AlarmMask_Definitions 
  * @{
  */ 
#define RTC_AlarmMask_Week                ((uint32_t)0x07000000)
#define RTC_AlarmMask_PA                  ((uint32_t)0x00200000)
#define RTC_AlarmMask_Hours               ((uint32_t)0x001F0000)
#define RTC_AlarmMask_Minutes             ((uint32_t)0x00007F00)
#define RTC_AlarmMask_Seconds             ((uint32_t)0x0000007F)
#define RTC_AlarmMask_time                ((uint32_t)0x073F7F7F)

#define RTC_AlarmMask_Year                ((uint32_t)0x00FF0000)
#define RTC_AlarmMask_ALCEN               ((uint32_t)0x00008000)
#define RTC_AlarmMask_Mouth               ((uint32_t)0x00001F00)
#define RTC_AlarmMask_Day                 ((uint32_t)0x0000001F)
#define RTC_AlarmMask_date                ((uint32_t)0x00FF9F1f)


/** @defgroup RTC_Wakeup_Timer_Definitions 
  * @{
  */ 
#define RTC_WakeUpClock_RTCCLK_Div16        ((uint32_t)0x00000000)
#define RTC_WakeUpClock_RTCCLK_Div8         ((uint32_t)0x00000001)
#define RTC_WakeUpClock_RTCCLK_Div4         ((uint32_t)0x00000002)
#define RTC_WakeUpClock_RTCCLK_Div2         ((uint32_t)0x00000003)
#define RTC_WakeUpClock_CK_SPRE_16bits      ((uint32_t)0x00000004)
#define RTC_WakeUpClock_CK_SPRE_17bits      ((uint32_t)0x00000006)
#define IS_RTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == RTC_WakeUpClock_RTCCLK_Div16)   || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div8)    || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div4)    || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div2)    || \
                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_16bits) || \
                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_17bits))
#define IS_RTC_WAKEUP_COUNTER(COUNTER)  ((COUNTER) <= 0xFFFF)


/** @defgroup RTC_Time_Stamp_Edges_definitions 
  * @{
  */ 
#define RTC_TimeStampEdge_Rising          ((uint32_t)0x00000000)
#define RTC_TimeStampEdge_Falling         ((uint32_t)0x00000008)
#define IS_RTC_TIMESTAMP_EDGE(EDGE) (((EDGE) == RTC_TimeStampEdge_Rising) || \
                                     ((EDGE) == RTC_TimeStampEdge_Falling))


/** @defgroup RTC_Output_selection_Definitions 
  * @{
  */ 
#define RTC_Output_Disable             ((uint32_t)0x00000000)
#define RTC_Output_AlarmA              ((uint32_t)0x00200000)
#define RTC_Output_AlarmB              ((uint32_t)0x00400000)
#define RTC_Output_WakeUp              ((uint32_t)0x00600000)
 
#define IS_RTC_OUTPUT(OUTPUT) (((OUTPUT) == RTC_Output_Disable) ||\
                               ((OUTPUT) == RTC_Output_AlarmA)  ||\
                               ((OUTPUT) == RTC_Output_AlarmB)  ||\
                               ((OUTPUT) == RTC_Output_WakeUp))



/** @defgroup RTC_Output_Polarity_Definitions 
  * @{
  */ 
#define RTC_OutputPolarity_High           ((uint32_t)0x00000000)
#define RTC_OutputPolarity_Low            ((uint32_t)0x00100000)
#define IS_RTC_OUTPUT_POL(POL) (((POL) == RTC_OutputPolarity_High)||\
                                ((POL) == RTC_OutputPolarity_Low))

/** @defgroup RTC_Digital_Calibration_Definitions 
  * @{
  */ 
#define RTC_CalibSign_Positive            ((uint32_t)0x00000000) 
#define RTC_CalibSign_Negative            ((uint32_t)0x00000080)
#define IS_RTC_CALIB_SIGN(SIGN) (((SIGN) == RTC_CalibSign_Positive) ||\
                                 ((SIGN) == RTC_CalibSign_Negative))
#define IS_RTC_CALIB_VALUE(VALUE) ((VALUE) < 0x20)


 /** @defgroup RTC_Calib_Output_selection_Definitions 
  * @{
  */ 
#define RTC_CalibOutput_1Hz            ((uint32_t)0x00000002)
#define RTC_Count_Enable               ((uint32_t)0x00000100)
#define RTC_Count_Disable              ((uint32_t)0x00000000)
#define RTC_Clk_Enable                 ((uint32_t)0x00100000)
#define RTC_Clk_Disable                ((uint32_t)0x00000000)




/** @defgroup RTC_Smooth_calib_period_Definitions 
  * @{
  */ 
#define RTC_SmoothCalibPeriod_60sec   ((uint32_t)0x00000000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation
                                                             period is 60s,  else 2exp20 RTCCLK seconds */
#define RTC_SmoothCalibPeriod_30sec   ((uint32_t)0x00000100) /*!<  if RTCCLK = 32768 Hz, Smooth calibation
                                                             period is 30s,  else 2exp20 RTCCLK seconds */
#define RTC_SmoothCalibPeriod_15sec   ((uint32_t)0x00000200) /*!<  if RTCCLK = 32768 Hz, Smooth calibation 
                                                             period is 15s, else 2exp19 RTCCLK seconds */
#define RTC_SmoothCalibPeriod_6sec    ((uint32_t)0x00000300) /*!<  if RTCCLK = 32768 Hz, Smooth calibation 
                                                             period is 6s, else 2exp18 RTCCLK seconds */
#define IS_RTC_SMOOTH_CALIB_PERIOD(PERIOD) (((PERIOD) == RTC_SmoothCalibPeriod_60sec)  ||\
                                             ((PERIOD) == RTC_SmoothCalibPeriod_30sec) ||\
                                             ((PERIOD) == RTC_SmoothCalibPeriod_15sec) ||\
																						 ((PERIOD) == RTC_SmoothCalibPeriod_6sec))
                                          


/** @defgroup RTC_Smooth_calib_Plus_pulses_Definitions 
  * @{
  */ 
#define IS_RTC_SMOOTH_CALIB_TRMINGVALUE(VALUE) (((VALUE) >= 0x00)||\
                                                ((VALUE) <= 0xff))

/** @defgroup RTC_Smooth_calib_Minus_pulses_Definitions 
  * @{
  */ 
#define  IS_RTC_SMOOTH_CALIB_MINUS(VALUE) ((VALUE) <= 0x000000FF)

/** @defgroup RTC_Substract_Fraction_Of_Second_Value
  * @{
  */ 
#define IS_RTC_SHIFT_SUBFS(FS) ((FS) <= 0x00007FFF)

/** @defgroup RTC_Input_parameter_format_definitions 
  * @{
  */ 
#define RTC_Format_BIN                    ((uint32_t)0x000000000)
#define RTC_Format_BCD                    ((uint32_t)0x000000001)
#define IS_RTC_FORMAT(FORMAT) (((FORMAT) == RTC_Format_BIN) ||\
                               ((FORMAT) == RTC_Format_BCD))


/** @defgroup RTC_Interrupts_Definitions 
  * @{
  */ 
#define RTC_IT_ALM1                        ((uint32_t)0x00000010)
#define RTC_IT_ALM2                        ((uint32_t)0x00000020)
#define RTC_IT_ALMEN                       ((uint32_t)0x00000040)
#define RTC_IT_ALM                         ((uint32_t)0x00000070)

#define IS_RTC_CLEAR_FLAG(FLAG)  (((FLAG) == RTC_IT_ALM1) ||\
                                  ((FLAG) == RTC_IT_ALM2) ||\
																	((FLAG) == RTC_IT_ALMEN))
																	
#define IS_RTC_GET_IT(FLAG)      (((FLAG) == RTC_IT_ALM1)||\
																	((FLAG) == RTC_IT_ALM2)||\
																	((FLAG) == RTC_IT_ALMEN))

/** @defgroup RTC_Legacy 
  * @{
  */ 
#define RTC_DigitalCalibConfig  RTC_CoarseCalibConfig
#define RTC_DigitalCalibCmd     RTC_CoarseCalibCmd

/**
  * @}
  */ 
	/******************************************************************************/
/*                                                                            */
/*                           Real-Time Clock (RTC)                            */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RTC_TR register  *******************/
#define RTC_TTME_H20PA                       ((uint32_t)0x00200000)
#define RTC_TR_WEEKDAY                       ((uint32_t)0x07000000)
#define RTC_TR_WEEKDAY_0                     ((uint32_t)0x01000000)
#define RTC_TR_WEEKDAY_1                     ((uint32_t)0x02000000)
#define RTC_TR_WEEKDAY_2                     ((uint32_t)0x04000000)

#define RTC_TR_HU_24                         ((uint32_t)0x001F0000)
#define RTC_TR_HU                            ((uint32_t)0x001F0000)
#define RTC_TR_HU_0                          ((uint32_t)0x00010000)
#define RTC_TR_HU_1                          ((uint32_t)0x00020000)
#define RTC_TR_HU_2                          ((uint32_t)0x00040000)
#define RTC_TR_HU_3                          ((uint32_t)0x00080000)
#define RTC_TR_HU_4                          ((uint32_t)0x00100000)

#define RTC_TR_MNU                           ((uint32_t)0x00007F00)
#define RTC_TR_MNU_0                         ((uint32_t)0x00000100)
#define RTC_TR_MNU_1                         ((uint32_t)0x00000200)
#define RTC_TR_MNU_2                         ((uint32_t)0x00000400)
#define RTC_TR_MNU_3                         ((uint32_t)0x00000800)
#define RTC_TR_MNU_4                         ((uint32_t)0x00001000)
#define RTC_TR_MNU_5                         ((uint32_t)0x00002000)
#define RTC_TR_MNU_6                         ((uint32_t)0x00004000)
#define RTC_TR_SU                            ((uint32_t)0x0000007F)
#define RTC_TR_SU_0                          ((uint32_t)0x00000001)
#define RTC_TR_SU_1                          ((uint32_t)0x00000002)
#define RTC_TR_SU_2                          ((uint32_t)0x00000004)
#define RTC_TR_SU_3                          ((uint32_t)0x00000008)
#define RTC_TR_SU_4                          ((uint32_t)0x00000010)
#define RTC_TR_SU_5                          ((uint32_t)0x00000020)
#define RTC_TR_SU_6                          ((uint32_t)0x00000040)

/********************  Bits definition for RTC_DR register  *******************/
#define RTC_DR_YU                            ((uint32_t)0x00FF0000)
#define RTC_DR_YU_0                          ((uint32_t)0x00010000)
#define RTC_DR_YU_1                          ((uint32_t)0x00020000)
#define RTC_DR_YU_2                          ((uint32_t)0x00040000)
#define RTC_DR_YU_3                          ((uint32_t)0x00080000)
#define RTC_DR_YU_4                          ((uint32_t)0x00100000)
#define RTC_DR_YU_5                          ((uint32_t)0x00200000)
#define RTC_DR_YU_6                          ((uint32_t)0x00400000)
#define RTC_DR_YU_7                          ((uint32_t)0x00800000)

#define RTC_DR_MU                            ((uint32_t)0x00001F00)
#define RTC_DR_MU_0                          ((uint32_t)0x00000100)
#define RTC_DR_MU_1                          ((uint32_t)0x00000200)
#define RTC_DR_MU_2                          ((uint32_t)0x00000400)
#define RTC_DR_MU_3                          ((uint32_t)0x00000800)
#define RTC_DR_MU_4                          ((uint32_t)0x00001000)


#define RTC_DR_DU                            ((uint32_t)0x0000003F)
#define RTC_DR_DU_0                          ((uint32_t)0x00000001)
#define RTC_DR_DU_1                          ((uint32_t)0x00000002)
#define RTC_DR_DU_2                          ((uint32_t)0x00000004)
#define RTC_DR_DU_3                          ((uint32_t)0x00000008)
#define RTC_DR_DU_4                          ((uint32_t)0x00000010)
#define RTC_DR_DU_5                          ((uint32_t)0x00000020)
#define RTC_DR_CEN                           ((uint32_t)0x00008000)

	
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the RTC configuration to the default reset state *****/

ErrorStatus RTC_DeInit(RTC_TypeDef *RTCx);
ErrorStatus RTC_Init(RTC_TypeDef *RTCx,RTC_InitTypeDef* RTC_InitStruct);
void RTC_StructInit(RTC_TypeDef *RTCx,RTC_InitTypeDef* RTC_InitStruct);
void RTC_WriteProtectionCmd(RTC_TypeDef *RTCx,FunctionalState NewState);
ErrorStatus RTC_EnterInitMode(RTC_TypeDef *RTCx);
void RTC_ExitInitMode(RTC_TypeDef *RTCx);
ErrorStatus RTC_WaitForSynchro(RTC_TypeDef *RTCx);
void RTC_RtcClkCmd(RTC_TypeDef *RTCx,FunctionalState NewState);
void RTC_BypassShadowCmd(RTC_TypeDef *RTCx,FunctionalState NewState);
ErrorStatus RTC_SetTime(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_TimeStructInit(RTC_TypeDef *RTCx,RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_GetTime(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);
ErrorStatus RTC_SetDate(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct);
void RTC_DateStructInit(RTC_TypeDef *RTCx,RTC_DateTypeDef* RTC_DateStruct);
void RTC_GetDate(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct);
void RTC_SetAlarm1(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_AlarmTypeEnableDef*RTC_AlarmEableStruct, RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_SetAlarm2(RTC_TypeDef *RTCx,uint32_t value);
void RTC_AlarmStructInit(RTC_TypeDef *RTCx,RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_GetAlarm1(RTC_TypeDef *RTCx,uint32_t RTC_Format, RTC_AlarmTypeDef* RTC_AlarmStruct);
uint8_t RTC_GetAlarm2(RTC_TypeDef *RTCx);
void RTC_AlarmCmd(RTC_TypeDef *RTCx,uint32_t RTC_Alarm, FunctionalState NewState);
ErrorStatus RTC_CoarseCalibConfig(RTC_TypeDef *RTCx,uint32_t RTC_CalibSign, uint32_t Value);
void RTC_CalibOutputCmd(RTC_TypeDef *RTCx,FunctionalState NewState);
void RTC_CountCmd(RTC_TypeDef *RTCx,FunctionalState NewState);
void RTC_SmoothCalibConfig(RTC_TypeDef *RTCx,uint32_t RTC_SmoothCalibPeriod,uint32_t RTC_SmoothCalibTrmingValue);
void RTC_AlprITConfig(RTC_TypeDef *RTCx,uint32_t RTC_IT, FunctionalState NewState);
void RTC_AlmITConfig(RTC_TypeDef *RTCx,uint32_t RTC_IT, FunctionalState NewState);
FlagStatus RTC_GetFlagStatus(RTC_TypeDef *RTCx,uint32_t RTC_FLAG);
void RTC_ClearFlag(RTC_TypeDef *RTCx,uint32_t RTC_FLAG);
ITStatus RTC_GetITStatus(RTC_TypeDef *RTCx,uint32_t RTC_IT);
void RTC_SelRtcClk(RTC_TypeDef *RTCx,uint32_t RTCClk);

#ifdef __cplusplus
}
#endif

#endif /*__CX32l003_RTC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT XMC *****END OF FILE****/

#ifndef _BLE_H_
#define _BLE_H_


/* 8bit muc .not support 64bit byte.*/
#define HFCLK_1MS 			16000UL


//0.5ms
#define	BLE_START_TIME		(HFCLK_1MS/2)

//50ms, max:0xffff=65,535 us
#define BLE_RX_TIMEOUT      50000
#define BLE_GUARD_TIME      (2UL*BLE_RX_TIMEOUT/1000)

/* set BLE TX power
0  -- -54 dBm
1  -- -37 dBm
5  -- -30 dBm
42 -- -20 dBm
48 -- -15 dBm
58 -- -8 dBm
61 -- -6 dBm
64 -- -3 dBm
67 --  0 dBm
72 --  3 dBm
74 --  4 dBm
#define
*/
#define	BLE_TX_POWER_54dbm	0
#define	BLE_TX_POWER_37dbm	1
#define	BLE_TX_POWER_30dbm	5
#define	BLE_TX_POWER_20dbm	42
#define	BLE_TX_POWER_15dbm	48
#define	BLE_TX_POWER_8dbm	58
#define	BLE_TX_POWER_6dbm	61
#define	BLE_TX_POWER_3dbm	64
#define	BLE_TX_POWER0dbm	67
#define	BLE_TX_POWER3dbm	72
#define	BLE_TX_POWER5dbm	74

#define BLE_TX_POWER		BLE_TX_POWER5dbm

/*-------------------------------BLE register---------------------------------*/
//set advertise channel number 37 38 39
#define CH_NO         0x01
/*
7:6: RESERVED
5:0: set channel
*/

//set tx mode \ rx mode .
#define MODE_TYPE     0x02

//mode
#define RADIO_MODE_NULL    		0
#define RADIO_MODE_ADV_RX		0x09
#define RADIO_MODE_ADV_TX		0x0c

//set tx pud length , pud type
#define ADV_HDR_TX    0x03
#define ADV_HDR_RX    4
/*
15:8:	Pdu length
7:0:	Pdu type
*/
#define ADV_IND            0
#define ADV_DIRECT_IND     1
#define ADV_NONCONN_IND    2
#define ADV_SCAN_REQ       3
#define ADV_SCAN_RSP       4
#define ADV_CONN_REQ       5
#define ADV_SCAN_IND       6

//start time
#define START_TIME    0x07

#define ADVA_RX       0xA
#define INITA_RX      0xB

//interrupt mask & flag
//tx_done\ enter sleep \ wakeup
#define INT_FLAG      0x0E
/*
15:8:	Interrupt mask bit
7:5	:	reserved
4	:	tx finish
3	:	reserved
2	:	reserved
1	:	Enter sleep mode
0	:	Wake up

*/

//INT
#define INT_TYPE_WAKEUP   	0x01
#define INT_TYPE_SLEEP    	0x02
#define INT_TYPE_TX_START 	0x10
#define INT_TYPE_PDU_ERR 	0x20
#define INT_TYPE_PDU_OK 	0x40
#define INT_TYPE_TX_Done  	0xFF





//set wakeup time\enable sleep\enable wakeup
#define SLEEP_WAKEUP  0x0F
/*
32:8:	Wake up time
7:2	:	reserved
1	:	Enter sleep
0	:	Enter wakeup
*/

//LF&HF clock counter
#define CLK_CNT       0x10
/*
48:24:	LF counter
23:0 :	HF counter
*/

//TX/RX timeout(us)
#define TIMEOUT       0x11
/*
16	:	Disable Timerout
15:8:	Timeout byte1
7:0	:	Timeout byte0
*/

//TX Data Payload maxLen 31 Bytes
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0

//Chip ok
#define CHIP_OK       0x1F
/*-------------------------------BLE register  End----------------------------*/


//Nordic SDK GAP  AD_TYPE
#define BLE_GAP_AD_TYPE_FLAGS                               0x01 /**< Flags for discoverability. */
#define BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE   0x02 /**< Partial list of 16 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE         0x03 /**< Complete list of 16 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_MORE_AVAILABLE   0x04 /**< Partial list of 32 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_COMPLETE         0x05 /**< Complete list of 32 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_MORE_AVAILABLE  0x06 /**< Partial list of 128 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE        0x07 /**< Complete list of 128 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME                    0x08 /**< Short local device name. */
#define BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME                 0x09 /**< Complete local device name. */
#define BLE_GAP_AD_TYPE_TX_POWER_LEVEL                      0x0A /**< Transmit power level. */
#define BLE_GAP_AD_TYPE_CLASS_OF_DEVICE                     0x0D /**< Class of device. */
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C               0x0E /**< Simple Pairing Hash C. */
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R         0x0F /**< Simple Pairing Randomizer R. */
#define BLE_GAP_AD_TYPE_SECURITY_MANAGER_TK_VALUE           0x10 /**< Security Manager TK Value. */
#define BLE_GAP_AD_TYPE_SECURITY_MANAGER_OOB_FLAGS          0x11 /**< Security Manager Out Of Band Flags. */
#define BLE_GAP_AD_TYPE_SLAVE_CONNECTION_INTERVAL_RANGE     0x12 /**< Slave Connection Interval Range. */
#define BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_16BIT       0x14 /**< List of 16-bit Service Solicitation UUIDs. */
#define BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_128BIT      0x15 /**< List of 128-bit Service Solicitation UUIDs. */
#define BLE_GAP_AD_TYPE_SERVICE_DATA                        0x16 /**< Service Data - 16-bit UUID. */
#define BLE_GAP_AD_TYPE_PUBLIC_TARGET_ADDRESS               0x17 /**< Public Target Address. */
#define BLE_GAP_AD_TYPE_RANDOM_TARGET_ADDRESS               0x18 /**< Random Target Address. */
#define BLE_GAP_AD_TYPE_APPEARANCE                          0x19 /**< Appearance. */
#define BLE_GAP_AD_TYPE_ADVERTISING_INTERVAL                0x1A /**< Advertising Interval. */
#define BLE_GAP_AD_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS         0x1B /**< LE Bluetooth Device Address. */
#define BLE_GAP_AD_TYPE_LE_ROLE                             0x1C /**< LE Role. */
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C256            0x1D /**< Simple Pairing Hash C-256. */
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R256      0x1E /**< Simple Pairing Randomizer R-256. */
#define BLE_GAP_AD_TYPE_SERVICE_DATA_32BIT_UUID             0x20 /**< Service Data - 32-bit UUID. */
#define BLE_GAP_AD_TYPE_SERVICE_DATA_128BIT_UUID            0x21 /**< Service Data - 128-bit UUID. */
#define BLE_GAP_AD_TYPE_3D_INFORMATION_DATA                 0x3D /**< 3D Information Data. */
#define BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA          0xFF /**< Manufacturer Specific Data. */


#define GAP_ADTYPE_FLAGS_LIMITED                			0x01 //!< Discovery Mode: LE Limited Discoverable Mode
#define GAP_ADTYPE_FLAGS_GENERAL                			0x02 //!< Discovery Mode: LE General Discoverable Mode
#define GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED    			0x04 //!< Discovery Mode: BR/EDR Not Supported


extern void BLE_Init(void);
extern void BLE_TRX(void);
extern void BLE_Start(void);

extern uint8_t txcnt;
extern uint8_t rxcnt;

#define LEN_BLE_ADDR 6
#define LEN_DATA 31
extern uint8_t adv_data[LEN_DATA];
extern uint8_t rx_buf[39];

extern void BLE_Mode_PwrDn(void);
extern void BLE_Mode_PwrUp(void);
extern void BLE_Mode_Sleep(void);
extern void BLE_Mode_Wakeup(void);
extern void BLE_Set_TimeOut(uint32_t data_us);
extern void BLE_Set_StartTime(uint32_t htime);
extern uint8_t BLE_Get_RSSI(void);
extern void BLE_Get_Pdu(uint8_t *ptr, uint8_t *len);

#endif


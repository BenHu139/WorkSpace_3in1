
/* !Comment: Included File             */
#include "Can_Data_Types.h"
#include "Can_Data_MsgCfg.h"



/* ************************************************************************** */
/*                                 MACROS                                     */
/* ************************************************************************** */


/* ************************************************************************** */
/*                                 TYPES                                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                              GLOABAL VARIRABLE                             */
/* ************************************************************************** */
/* !Comment: CAN_1 mailbox configuration definition           */
const Can_tstrMbType Can_astrMbCfg_B[CAN1_MSG_NUM] =
{
   { OBC_RX, 				0x1806E5F4	 , 8, CAN_RX, CAN_ID_EXTENDED, CAN_ID_DATA, (1000/CAN_BASE_TASK),   FALSE},
   { VCU_PwrCtrl, 			0x81         , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (10/CAN_BASE_TASK),  FALSE},
   { BMS_RequestVA, 		0x284        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { BMS_HeatChargeSt, 		0x295        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { VCU_VehicleSt, 		0x155        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (10/CAN_BASE_TASK),  FALSE},
   { DCDC_EnSt, 			0x4C7        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
#ifdef DEBUG_EN
   { Debug_Rx, 				0x200        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (50/CAN_BASE_TASK),  FALSE},
   { TstDataIO, 			0x380        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { TstAdc1, 				0x381        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { TstAdc2, 				0x382        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { TstAdc3, 				0x383        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { TstAdc4, 				0x384        , 8, CAN_RX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
#endif
   { OBC_TX, 				0x18FF50E5	 , 8, CAN_TX, CAN_ID_EXTENDED, CAN_ID_DATA, (1000/CAN_BASE_TASK),FALSE},
   { DCDC_Sts, 				0x0CFF0104   , 8, CAN_TX, CAN_ID_EXTENDED, CAN_ID_DATA, (50/CAN_BASE_TASK),  FALSE},
   { DCDC_BattU, 			0x261        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { OBC_Status_1, 			0x4F6        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { OBC_Status_2, 			0x486        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { OBC_Status_3, 			0x4D5        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { OBC_Status_4, 			0x5C1        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (5000/CAN_BASE_TASK),FALSE},
   { DCDC_Status_1, 		0x361        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { DCDC_Status_2, 		0x594        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (1000/CAN_BASE_TASK),FALSE},
   { OBC_WakeUp_Status, 	0x654        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (1000/CAN_BASE_TASK),FALSE},
#ifdef DEBUG_EN
   { Debug_Adc_phy1, 		0x103        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_Adc_phy2, 		0x104        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_Adc_phy3, 		0x105        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_Adc_phy4, 		0x106        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_Adc_phy5, 		0x10E        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (10/CAN_BASE_TASK),  FALSE},
   { Debug_Adc_clc1, 		0x113        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_Adc_clc2, 		0x114        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_Adc_clc3, 		0x115        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_Adc_clc4, 		0x116        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_Dio_phy, 		0x107        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { Debug_St, 				0x108        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { OBC_InternalState, 	0x109        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (0/CAN_BASE_TASK), FALSE},
   { DCDC_InternalState, 	0x10A        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK), FALSE},
   { DCDC_Fault, 			0x10B        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { OBC_Fault, 			0x10C        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (30/CAN_BASE_TASK),  FALSE},
   { OBCDCDC_ADJUST, 		0x10D        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK),  FALSE},
   { OBCDCDC_CtrlVal, 		0x127        , 8, CAN_TX, CAN_ID_STANDARD, CAN_ID_DATA, (100/CAN_BASE_TASK),  FALSE},
#endif
};
uint16 Can_u16FreqCnt_B[CAN1_MSG_NUM];

/* !Comment: Message OBC_RX structure definition      */
CanMsg_tstrOBC_RXType CanMsg_tstrOBC_RX;

/* WuLing Receive!Comment: Message BmsReqVa structure definition      */
CanMsg_tstrBmsReqVaType CanMsg_tstrBmsReqVa;

/* WuLing Receive!Comment: Message BmsHeatCharge structure definition      */
CanMsg_tstrBmsHeatChargeStType CanMsg_tstrBmsHeatChargeSt;

/* WuLing Receive!Comment: Message VcuVehicle structure definition      */
CanMsg_tstrVcuVehicleStType CanMsg_tstrVcuVehicleSt;

/* WuLing Receive!Comment: Message DcdcEn structure definition      */
CanMsg_tstrDcdcEnStType CanMsg_tstrDcdcEnSt;

/* !Comment: Message OBC_TX structure definition      */
CanMsg_tstrOBC_TXType CanMsg_tstrOBC_TX;

/* !Comment: Message VcuPwrCtrl structure definition      */
CanMsg_tstrVcuPwrCtrlType CanMsg_tstrVcuPwrCtrl;

/* !Comment: Message DcdcSt structure definition      */
CanMsg_tstrDcdcStType CanMsg_tstrDcdcSt;

/* !Comment: Message DCDC_BattU structure definition      */
CanMsg_tstrDCDC_BattUType CanMsg_tstrDCDC_BattU;

/* WuLing Transmission!Comment: Message OBC_Status_1 structure definition      */
CanMsg_tstrOBC_Status_1Type CanMsg_tstrOBC_Status_1;

/* WuLing Transmission!Comment: Message OBC_Status_2 structure definition      */
CanMsg_tstrOBC_Status_2Type CanMsg_tstrOBC_Status_2;

/* WuLing Transmission!Comment: Message OBC_Status_3 structure definition      */
CanMsg_tstrOBC_Status_3Type CanMsg_tstrOBC_Status_3;

/* WuLing Transmission!Comment: Message OBC_Status_4 structure definition      */
CanMsg_tstrOBC_Status_4Type CanMsg_tstrOBC_Status_4;

/* WuLing Transmission!Comment: Message DCDC_Status_1 structure definition      */
CanMsg_tstrDCDC_Status_1Type CanMsg_tstrDCDC_Status_1;

/* WuLing Transmission!Comment: Message DCDC_Status_2 structure definition      */
CanMsg_tstrDCDC_Status_2Type CanMsg_tstrDCDC_Status_2;

/* WuLing Transmission!Comment: Message OBC_WakeUp_Status structure definition      */
CanMsg_tstrOBC_WakeUp_StatusType CanMsg_tstrOBC_WakeUp_Status;

#ifdef DEBUG_EN
/* !Comment: Message Debug_Adc_phy1 structure definition      */
CanMsg_tstrDebug_Adc_phy1Type CanMsg_tstrDebug_Adc_phy1;

/* !Comment: Message Debug_Adc_phy2 structure definition      */
CanMsg_tstrDebug_Adc_phy2Type CanMsg_tstrDebug_Adc_phy2;

/* !Comment: Message Debug_Adc_phy3 structure definition      */
CanMsg_tstrDebug_Adc_phy3Type CanMsg_tstrDebug_Adc_phy3;

/* !Comment: Message Debug_Adc_phy4 structure definition      */
CanMsg_tstrDebug_Adc_phy4Type CanMsg_tstrDebug_Adc_phy4;

/* !Comment: Message Debug_Adc_phy5 structure definition      */
CanMsg_tstrDebug_Adc_phy5Type CanMsg_tstrDebug_Adc_phy5;

/* !Comment: Message Debug_Adc_clc1 structure definition      */
CanMsg_tstrDebug_Adc_clc1Type CanMsg_tstrDebug_Adc_clc1;

/* !Comment: Message Debug_Adc_clc2 structure definition      */
CanMsg_tstrDebug_Adc_clc2Type CanMsg_tstrDebug_Adc_clc2;

/* !Comment: Message Debug_Adc_clc3 structure definition      */
CanMsg_tstrDebug_Adc_clc3Type CanMsg_tstrDebug_Adc_clc3;

/* !Comment: Message Debug_Adc_clc4 structure definition      */
CanMsg_tstrDebug_Adc_clc4Type CanMsg_tstrDebug_Adc_clc4;

/* !Comment: Message Debug_Adc_clc3 structure definition      */
CanMsg_tstrDebug_DIO_phyType CanMsg_tstrDebug_DIO_phy;

/* !Comment: Message Debug_St structure definition      */
CanMsg_tstrDebug_StType CanMsg_tstrDebug_St;

/* !Comment: Message Debug_Rx structure definition      */
CanMsg_tstrDebug_RxType CanMsg_tstrDebug_Rx;

/* !Comment: Message TstDataIO structure definition      */
CanMsg_tstrTstDataIOType CanMsg_tstrTstDataIO;

/* !Comment: Message TstAdc1 structure definition      */
CanMsg_tstrTstAdc1Type CanMsg_tstrTstAdc1;

/* !Comment: Message TstAdc2 structure definition      */
CanMsg_tstrTstAdc2Type CanMsg_tstrTstAdc2;

/* !Comment: Message TstAdc1 structure definition      */
CanMsg_tstrTstAdc3Type CanMsg_tstrTstAdc3;

/* !Comment: Message TstAdc2 structure definition      */
CanMsg_tstrTstAdc4Type CanMsg_tstrTstAdc4;

/* !Comment: Message DCDC_InternalState structure definition      */
CanMsg_tstrOBC_InternalStateType CanMsg_tstrOBC_InternalState;

/* !Comment: Message DCDC_InternalState structure definition      */
CanMsg_tstrDCDC_InternalStateType CanMsg_tstrDCDC_InternalState;

/* !Comment: Message DCDC_Fault structure definition      */
CanMsg_tstrDCDC_FaultType CanMsg_tstrDCDC_Fault;

/* !Comment: Message DCDC_Fault structure definition      */
CanMsg_tstrOBC_FaultType CanMsg_tstrOBC_Fault;

/* !Comment: Message OBC/DCDC adjust volt current Type definition      */
CanMsg_tstrOBCDCDC_AdjustType CanMsg_tstrOBCDCDC_Adjust;

/* !Comment: Message OBC/DCDC control volt current Type definition      */
CanMsg_tstrOBCDCDC_CtrlValType CanMsg_tstrOBCDCDC_CtrlVal;

#endif
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */



/* ************** End of The File *************************************** */

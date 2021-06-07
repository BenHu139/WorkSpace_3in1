/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Driver module head File
*   Author          : HeYang
********************************************************************************
*   Description     : Main header file of the AUTOSAR CAN Transport Protocol, 
*                     according to AUTOSAR_SWS_CANTransportLayer.pdf(Release4.0)
*                     The header file contains the declaration of the Can module 
*                     API;contains 'extern' declarations of constants,global data,
*                     type definitions and services that are specified in the 
*                     CanTp module SWS.
*                                            
********************************************************************************
*   Limitations     : 
*
********************************************************************************
*
********************************************************************************
*   ComStack Publish History:
* 
*   Version     Date          Publisher       Descriptions
*   ---------   ----------    ------------    ---------------
*   1.0.0       2014-09-24    guorui          Final
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    2010/05/24    qyMa          N/A          Original
*   02.00.00    2014/03/11    rui.guo       N/A          N/A   
*   02.00.01    2014/10/30    rui.guo       N/A          D10_CANTP_141030_01
********************************************************************************
* END_FILE_HDR*/

#ifndef _CANTP_H_
#define _CANTP_H_

/**************************************************************************************************
* Include files
**************************************************************************************************/

#include "ComStack_Types.h"
#include "CanTp_Cfg.h"


#define CANTP_VENDOR_ID             (uint16)(0xFFFFu)  /*Supplier ID */
#define CANTP_MODULE_ID             (uint16)(0x0023u)  /*CanTp Moudle ID */
#define CANTP_INSTANCE_ID           ((uint8)0)

/* CanTp Component release Version  */
#define CANTP_SW_MAJOR_VERSION      (uint8)(0x01u)
#define CANTP_SW_MINOR_VERSION      (uint8)(0x00u)
#define CANTP_SW_PATCH_VERSION      (uint8)(0x00u)
/* Autosar release version */
#define CANTP_AR_MAJOR_VERSION      (uint8)(0x04u)
#define CANTP_AR_MINOR_VERSION      (uint8)(0x00u)
#define CANTP_AR_PATCH_VERSION      (uint8)(0x00u)

/**************************************************************************************************
* Global defines
**************************************************************************************************/
#define CANTP_MODE_HALF_DUPLEX      ((uint8)0x00u)
#define CANTP_MODE_FULL_DUPLEX      ((uint8)0x01u)

#define CANTP_MAX_FRAME_LENGTH            8u    /* CAN frame max length*/
#define CANTP_MAX_FRAME_LENGTH_UINT8      ((uint8)CANTP_MAX_FRAME_LENGTH)    /* CAN frame max length*/
#define CANTP_MAX_FRAME_LENGTH_UINT16     ((uint16)CANTP_MAX_FRAME_LENGTH)    /* CAN frame max length*/

#define CANTP_UNUSED                ((uint16)0xFFu)


/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/
/* AUTOSAR compliant */

typedef enum /* CanTpInternalState */
{
    CANTP_OFF = 0,
    CANTP_ON = 1u
} CanTpInternalState;

typedef enum
{
    CANTP_RX_CHANNEL = 0,
    CANTP_TX_CHANNEL = 1u
} CanTpChannelType;


typedef enum
{
    CANTP_STANDARD = 0,
    CANTP_EXTENDED = 1u,
    CANTP_MIXED = 2u
} CanTpAddressingFormat;

typedef enum
{
    CANTP_PHYSICAL = 0,
    CANTP_FUNCTIONAL = 1u
} CanTpTaType;

typedef enum
{
    CANTP_BS_PARAMETER = 0,
    CANTP_STMIN_PARAMETER = 1u
} CanTpParameterType;


/************************************************
* Types for static-configuration (ROM/Flash) 
************************************************/
/*************
* CanTp (ROM) 
*************/
typedef struct /*RxNsdu (ROM)*/ 
{ 
    PduIdType      CanTpChannelId;
    PduIdType      CanTpRxNPduId;    /* from CanIf */
    PduIdType      CanTpTxFcNPduId;  /* to   CanIf */
    uint16         CanTpRxDl;
    uint16         CanTpNar;
    uint16         CanTpNbr;
    uint16         CanTpNcr;  
    uint8          CanTpRxPaddingActive;
    CanTpTaType          CanTpRxTaType;
    CanTpAddressingFormat          CanTpRxAddrFormat;
    uint8          CanTpBs;
    uint8          CanTpSTmin;
    uint8          CanTpRxWftMax;
    uint8          CanTpRxNAe;
    uint8          CanTpRxNSa;
    uint8          CanTpRxNTa;
} CanTp_RxNsduCfgType;

typedef struct /*TxNsdu (ROM)*/
{ 
    PduIdType      CanTpChannelId;
    PduIdType      CanTpTxNPduId;    /* to   CanIf */
    PduIdType      CanTpRxFcNPduId;  /* from CanIf */
    uint16         CanTpTxDl;
    uint16         CanTpNas;
    uint16         CanTpNbs;
    uint16         CanTpNcs;
    uint8          CanTpTxPaddingActive;
    CanTpTaType          CanTpTxTaType;
    CanTpAddressingFormat          CanTpTxAddrFormat;
    uint8          CanTpTxNAe;
    uint8          CanTpTxNSa;
    uint8          CanTpTxNTa;
} CanTp_TxNsduCfgType;



typedef struct
{
    uint8  CanTpChannelMode;
}CanTp_ChannelModeType;

/* *********************************************** */
/* CanTp Overall (ROM)                             */
/* *********************************************** */
typedef struct /* Struct to hold the complete CanTp-configuration */
{ 
    CONSTP2CONST(CanTp_RxNsduCfgType,CANTP_CONFIG_CONST,TYPEDEF) CanTp_RxNsduCfg;
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_CONFIG_CONST,TYPEDEF) CanTp_TxNsduCfg;
    CONSTP2CONST(CanTp_ChannelModeType,CANTP_CONFIG_CONST,TYPEDEF) CanTp_ChannelMode;
} CanTp_ConfigType;

/*******************************************************************************
*   Internal data types and structures define
*******************************************************************************/

/* *************** */
/* Rx-status (RAM) */
/* *************** */
typedef struct 
{
    PduInfoType   RxNPduInfo;
    PduIdType     CurrentRxSduId; 
    /*PduLengthType DataIndex;*/  
    PduLengthType DataLength;
    /*PduLengthType FrameIndex;*/
    PduLengthType MinBuffSize;
    PduLengthType AvailableBufLength;
    uint16        Timer;
    uint8         CurrentRxFormatOffset;
    uint8         ChannelState;/* activation status */ 
    uint8         WFTCounter;
    uint8         BlockSizeCounter;  /* actual values */
    uint8         BlockSize;
    uint8         STMin; 
    uint8         FlowStatus;
    uint8         ExpectedSN;
    uint8         ChannelLastState;
    uint8         RxPreCancel;  
    uint8         RxErrorType; 
    uint8         RxFormatOffset;
    uint8*        RxBufPtr;
    uint8*        TxFCPtr;
    uint8         RxData[CANTP_MAX_FRAME_LENGTH];
    uint8         FCData[CANTP_MAX_FRAME_LENGTH];
    
}CanTp_RxStateType;

/* *************** */
/* Tx-status (RAM) */
/* *************** */
typedef struct 
{
    PduInfoType   TxNPduInfo;
    PduIdType     CurrentTxSduId;
    /*PduLengthType DataIndex;*/
    PduLengthType DataLength;
    /*PduLengthType FrameIndex;*/
    PduLengthType RemainTxDataCnt;
    uint16        Timer;
    /*uint8         PaddingLength;*/
    /*uint8         CurrentTxFormatOffset;*/
    uint8         ChannelState;
    uint8         BlockSizeCounter;
    uint8         STMin;
    uint8         SeqNumber;
    /*uint8         TxErrorType; TBD */
    uint8         TxFormatOffset;
    uint8         TxData[CANTP_MAX_FRAME_LENGTH];
}CanTp_TxStateType;

/* *********************************************** */
/* External administration data (RAM)              */
/* *********************************************** */
typedef struct 
{
    /*P2CONST(CanTp_ConfigType,TYPEDEF,CANTP_CONFIG_CONST) CfgPtr;*/
    P2CONST(CanTp_RxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   pRxNsduCfg;
    P2CONST(CanTp_TxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   pTxNsduCfg;
    P2CONST(CanTp_ChannelModeType,AUTOMATIC,CANTP_PRIVATE_CONST) pChnModeCfg;
    P2VAR(CanTp_RxStateType,AUTOMATIC,AUTOMATIC)                 pRxState;
    P2VAR(CanTp_TxStateType,AUTOMATIC,AUTOMATIC)                 pTxState;
    CanTpInternalState InternalState; /* keep track of the initialization status */
} CanTp_AdminDataType;


typedef struct 
{
    P2CONST(CanTp_RxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   _pRxSduCfg;
    P2CONST(CanTp_TxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   _pTxSduCfg;
    P2CONST(CanTp_ChannelModeType,AUTOMATIC,CANTP_PRIVATE_CONST) _pChnMdCfg;
    CanTp_RxStateType*     _pRxChnSt;
    CanTp_TxStateType*     _pTxChnSt;
    uint8*                 _pTmpData;
    PduIdType              _sduid;              
    PduLengthType          _candlc;
}CanTp_ContextType;
/**************************************************************************************************
* Gloable Data definitions
**************************************************************************************************/
#define CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/*extern CONST(CanTp_CfgType,CANTP_CONFIG_CONST) CanTp_Cfg;*/

#define CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
#define CANTP_START_SEC_PUBLIC_CODE
#include "MemMap.h"

extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_Init
(
    CONSTP2CONST(CanTp_ConfigType, CANTP_APPL_CONST, AUTOMATIC) pCfgPtr
);

extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_Shutdown(void);
extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_MainFunction(void);
extern FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_Transmit
(
    PduIdType CanTpTxSduId,
    P2CONST(PduInfoType,AUTOMATIC,CANTP_APPL_DATA) CanTpTxInfoPtr
);
#if (CANTP_TC == STD_ON)  
extern FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_CancelTransmitRequest
(
    PduIdType CanTpTxSduId
);
#endif      
extern FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_CancelReceiveRequest
(
    PduIdType CanTpRxSduId
);
extern FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_ChangeParameterRequest
(
    PduIdType CanTpSduId,
    CanTpParameterType parameter,
    uint16 value
);

#if (CANTP_VERSION_INFO_API == STD_ON)
extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_GetVersionInfo
(
    P2VAR(Std_VersionInfo_Type,AUTOMATIC,CANTP_APPL_DATA) VersionInfo
);
#endif                                                     
#define CANTP_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"
extern CONST(CanTp_ConfigType,CANTP_CONFIG_CONST) CanTp_Cfg;
#endif/* ifndef CANTP_H */

/*******************************************************************************
 *  END OF FILE: CanTp.h
 ******************************************************************************/ 


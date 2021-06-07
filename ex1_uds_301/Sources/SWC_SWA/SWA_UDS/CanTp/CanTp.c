/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanTp.c
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CanTp module Source File
*   Author          : qyMa
*                     rui.guo
********************************************************************************
*   Description     : Source of AUTOSAR Basic Software module CAN Transport 
*                     Layer (CanTp).
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
*   Version       Date           Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    2010/05/24         qyMa        N/A          Original
*   02.00.00    2014/03/11         rui.guo     N/A          N/A 
*   02.00.01    2014/08/08         rui.guo     N/A          Transmit CF by Stmin 
*                                                           strictly
*   02.00.02    2014/08/28         rui.guo     N/A          Updata STmin algorithm
*                                                           when received FC
*   02.00.03    2014/08/29         rui.guo     N/A          According to
*                                                           DiagOnCANTest_20140828-1720 
*   02.00.04    2014/09/18         rui.guo     N/A          Add CanTp_CanCancelTransmit,
*                                                           when N_A timeout.
*   02.00.05    2014/10/30         rui.guo     N/A          D10_CANTP_141030_01
*   02.00.06    2014/10/31         rui.guo     N/A          D10_CANTP_141031_01
*   03.00.00    2013/03/09         rui.guo     N/A    
*   03.00.01    2015/03/27         rui.guo     N/A  
*   03.01.00    2015/11/19         rui.guo     N/A          base ON WST
*   03.02.00    2015/11/26         rui.guo     N/A          
*   03.02.01    2015/12/04         rui.guo     N/A   
********************************************************************************
* END_FILE_HDR*/


/* Includes*/
/******************************************************************/
#include "CanTp_Cfg.h"
#include "CanTp.h"
#include "CanTp_Cbk.h"

#include "MemMap.h"

#define CANTP_AUTOSAREXT_SORRETBUSY       STD_OFF
#define CANTP_AUTOSAREXT_COPRXRETBUSY     STD_OFF
#define CANTP_AUTOSAREXT_WAITENOUGHBUFF   STD_OFF /*WaitEnoughBuffer*/

/*#define CANTP_AUTOSAR42          STD_ON*/
#define CANTP_RXSDUTRANSMITRETRY STD_OFF
#define CANTP_TXSDUTRANSMITRETRY STD_OFF
/*
#define CANTP_E_NOT_OK  ((Std_ReturnType)E_NOT_OK)
#define CANTP_E_OK      ((Std_ReturnType)E_OK)
*/

#define CANTP_RXPRECANCEL_TRUE                ((uint8)1)
#define CANTP_RXPRECANCEL_FALSE               ((uint8)0)
#define CANTP_PCIOFFSET_NORMAL                ((uint8)0)
#define CANTP_PCIOFFSET_EXTMIX                ((uint8)1)

#define STMINABSOLUTEMASK                     ((uint8)(0x80u))
#define STMINRELATIVEMIN                      ((uint8)(0xF1u))
#define STMINRELATIVEMAX                      ((uint8)(0xF9u))

#define CANTP_STMIN_RANGE_VALID      (1)
#define CANTP_STMIN_RANGE_INVALID    (0)

#define CANTP_STMIN_RANGE00_7F       CANTP_STMIN_RANGE_VALID
#define CANTP_STMIN_RANGE80_F0       CANTP_STMIN_RANGE_INVALID
#define CANTP_STMIN_RANGEF1_F9       CANTP_STMIN_RANGE_INVALID
#define CANTP_STMIN_RANGEFA_FF       CANTP_STMIN_RANGE_INVALID

/*******************************************************************************
*   Macros
*******************************************************************************/
/* Internal and iso 15765-2 compliant */
/* CanTp_FrameType */
#define cCanTp_SF                   ((uint8)0x00u)
#define cCanTp_FF                   ((uint8)0x10u)
#define cCanTp_CF                   ((uint8)0x20u)
#define cCanTp_FC                   ((uint8)0x30u)
#define cCanTp_FC_FS_CTS            ((uint8)0x00u)
#define cCanTp_FC_FS_Wait           ((uint8)0x01u)
#define cCanTp_FC_FS_Overrun        ((uint8)0x02u)

/* Masks for frame parsing */
#define cCanTp_DLMaskSF             ((uint8)0x0Fu)
#define cCanTp_DLMaskFF             ((uint8)0x0Fu)
#define cCanTp_FrameTypeMask        ((uint8)0xF0u)
#define cCanTp_FSMask               ((uint8)0x0Fu)
#define cCanTp_SNMask               ((uint8)0x0Fu)
/* Start value for sequence number counter*/
#define cCanTpSNStartValue          ((uint8)0x01u)

/*******************************************************************************
*   Transport protocol global status codes
*******************************************************************************/
/* CanTp_RxStateType */
/* Rx Idle state must be zero due to optimization */
#define cCanTpRxState_Idle                          ((uint8)0x00u) 
#define cCanTpRxState_WaitCF                        ((uint8)0x01u)
#define cCanTpRxState_WaitForTxFC                   ((uint8)0x02u)
#define cCanTpRxState_WaitForTxFCOverrun            ((uint8)0x03u)
#define cCanTpRxState_WaitForTxFCOverrunFFReqBuff   ((uint8)0x04u)
#define cCanTpRxState_WaitForTxFCWait               ((uint8)0x05u)
#define cCanTpRxState_WaitForTxFCWaitFFReqBuff      ((uint8)0x06u)
#define cCanTpRxState_WaitForRxBufferSF             ((uint8)0x07u)
#define cCanTpRxState_WaitForRxBufferFF             ((uint8)0x08u)
#define cCanTpRxState_WaitForRxBufferLastCF         ((uint8)0x09u)
#define cCanTpRxState_WaitForRxBufferLastCFBlock    ((uint8)0x0au)
#define cCanTpRxState_WaitForRxBufferGoingCF        ((uint8)0x0bu)
#define cCanTpRxState_WaitForSFRequestBuffer        ((uint8)0x0cu)
#define cCanTpRxState_WaitForFFRequestBuffer        ((uint8)0x0du)
#define cCanTpRxState_NoBuffer                      ((uint8)0x0eu)
#define cCanTpRxState_WFTmax_OvRn                   ((uint8)0x0fu)
#define cCanTpRxState_WFTmax_OvRnFFReqBuff          ((uint8)0x11u)

#define cCanTpRxState_WaitForFCConf                 ((uint8)0x10u)        
#define cCanTpRxState_WaitForFCWaitConf             ((uint8)0x20u)
#define cCanTpRxState_WaitForFCWaitConfFFReqBuff    ((uint8)0x30u)
#define cCanTpRxState_WaitForFCOverConf             ((uint8)0x40u)
#define cCanTpRxState_WaitForFCOverConfFFReqBuff    ((uint8)0x50u)
#define cCanTpRxState_RxProcessing                  ((uint8)0x60u)
#define cCanTpRxState_WaitEnoughBuffer              ((uint8)0x70u)

/* CanTp_TxStateType */
/* Tx Idle state must be zero due to optimization */
#define cCanTpTxState_Idle                          ((uint8)0x00u)
#define cCanTpTxState_WaitFC                        ((uint8)0x01u)
#define cCanTpTxState_WaitForTpTxCF                 ((uint8)0x02u)
#define cCanTpTxState_WaitForTxStart                ((uint8)0x03u)
#define cCanTpTxState_Error                         ((uint8)0x04u)
#define cCanTpTxState_ReCopy                        ((uint8)0x08u)
#define cCanTpTxState_WaitForSFConf                 ((uint8)0x10u)
#define cCanTpTxState_WaitForFFConf                 ((uint8)0x20u)
#define cCanTpTxState_WaitForCFConf                 ((uint8)0x30u)
#define cCanTpTxState_WaitForLastCFConf             ((uint8)0x40u)
/********************************************/
#if((CANTP_RXSDUTRANSMITRETRY == STD_ON)||(CANTP_TXSDUTRANSMITRETRY == STD_ON))
#define cCanTpState_Retransmit                      ((uint8)0x80u)
#endif
/*******************************************************************************
*   TP ISO offsets in CAN-frame
*******************************************************************************/
#define EXT_OFFSET                                  0 /*((uint8)0)*/
#define MIX_OFFSET                                  0 /*((uint8)0)*/
#define EXTMIX_OFFSET                               0

#define CANTP_TXLIMLEN                              ((uint8)0x07u)
#define CANTP_TXMAXLEN                              ((uint16)0xFFFu)/*4095*/
#define CANTP_BITS8                                 (0x08u)
#define CANTP_MAXSNNUM                              ((uint8)0x0Fu) 
#define CANTP_FC_DataLength                         (3u)

/*******************************************************************************
*   TP ISO offsets in RX CAN-frame and protocol lengths
*******************************************************************************/

#define RX_NPCI_OFFSET(pChnSt)              ((pChnSt)->RxFormatOffset)
#define RX_DL_OFFSET(pChnSt)                ((1u)+ ((pChnSt)->RxFormatOffset))
#define RX_FF_OFFSET(pChnSt)                ((((uint8)2)+(pChnSt)->RxFormatOffset))
#define RX_SF_OFFSET(pChnSt)                ((((uint8)1)+(pChnSt)->RxFormatOffset))
#define RX_CF_OFFSET(pChnSt)                ((((uint8)1)+(pChnSt)->RxFormatOffset))
#define RX_BS_OFFSET(pChnSt)                ((((uint8)1)+(pChnSt)->RxFormatOffset))
#define RX_STMIN_OFFSET(pChnSt)             ((((uint8)2)+(pChnSt)->RxFormatOffset))
#define RX_SF_DataLength(pChnSt)            ((((uint8)7)-(pChnSt)->RxFormatOffset))
#define RX_FF_DataLength(pChnSt)            ((uint16)(((uint8)6)-(pChnSt)->RxFormatOffset))
#define RX_FC_CAN_DataLength(pChnSt)        ((uint16)(((uint8)3)+(pChnSt)->TxFormatOffset))
#define RX_CF_DataLength(pChnSt)            ((((uint8)7)-(pChnSt)->RxFormatOffset))
/*******************************************************************************
*TP ISO offsets in TX CAN-frame and protocol lengths
*******************************************************************************/
#define TX_NPCI_OFFSET(pChnSt)              ((pChnSt)->TxFormatOffset)
#define TX_DL_OFFSET(pChnSt)                (((uint8)1)+(pChnSt)->TxFormatOffset)
#define TX_FF_OFFSET(pChnSt)                (((uint8)2)+(pChnSt)->TxFormatOffset)
#define TX_SF_OFFSET(pChnSt)                (((uint8)1)+(pChnSt)->TxFormatOffset)
#define TX_CF_OFFSET(pChnSt)                (((uint8)1)+(pChnSt)->TxFormatOffset)
#define TX_BS_OFFSET(pChnSt)                (((uint8)1)+(pChnSt)->TxFormatOffset)
#define TX_STMIN_OFFSET(pChnSt)             (((uint8)2)+(pChnSt)->TxFormatOffset)
#define TX_SF_DataLength(pChnSt)            ((uint16)(((uint8)7)-(pChnSt)->TxFormatOffset))
#define TX_FF_DataLength(pChnSt)            ((uint16)(((uint8)6)-(pChnSt)->TxFormatOffset))
#define TX_FC_CAN_DataLength(pChnSt)        ((uint16)(((uint8)3)+(pChnSt)->RxFormatOffset))
#define TX_CF_DataLength(pChnSt)            ((uint16)(((uint8)7)-(pChnSt)->TxFormatOffset))

/*******************************************************************************
* CanTpRxNSdu{RxNsdu}
*******************************************************************************/

/*by sdu ptr*/ 
#define CANTP_RXTPCHANNEL_ID(pSduCfg)        ((pSduCfg)->CanTpChannelId)
#define CANTP_RXNPDU_ID(pSduCfg)             ((pSduCfg)->CanTpRxNPduId)
#define CANTP_TXFC_NPDU_ID(pSduCfg)          ((pSduCfg)->CanTpTxFcNPduId)
/*dele in AUTOSAR V4.2*/
/*#define CANTP_RX_DL(CanTpSduId)            CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxDl*/
#define CANTP_NAR(pSduCfg)                   ((uint16)((pSduCfg)->CanTpNar/CANTP_MAIN_FUNCTION_PERIOD))
#define CANTP_NBR(pSduCfg)                   ((uint16)((pSduCfg)->CanTpNbr/CANTP_MAIN_FUNCTION_PERIOD))
#define CANTP_NCR(pSduCfg)                   ((uint16)((pSduCfg)->CanTpNcr/CANTP_MAIN_FUNCTION_PERIOD))
#define CANTP_RX_PADDING_ACTIVATION(pSduCfg) ((pSduCfg)->CanTpRxPaddingActive)
#define CANTP_RX_TA_TYPE(pSduCfg)            ((pSduCfg)->CanTpRxTaType)
#define CANTP_RX_ADDRESSING_FORMAT(pSduCfg)  ((pSduCfg)->CanTpRxAddrFormat)
#define CANTP_BS(pSduCfg)                    ((pSduCfg)->CanTpBs)
#define CANTP_STMIN(pSduCfg)                 ((pSduCfg)->CanTpSTmin)
#define CANTP_WFTMAX(pSduCfg)                ((pSduCfg)->CanTpRxWftMax)
#define CANTP_RX_NAE(pSduCfg)                ((pSduCfg)->CanTpRxNAe)
#define CANTP_RX_NSA(pSduCfg)                ((pSduCfg)->CanTpRxNSa)
#define CANTP_RX_NTA(pSduCfg)                ((pSduCfg)->CanTpRxNTa)
/*******************************************************************************
* CanTpTxNSdu{TxNsdu}
*******************************************************************************/
#define CANTP_TXTPCHANNEL_ID(pSduCfg)        ((pSduCfg)->CanTpChannelId)
#define CANTP_TXNPDU_ID(pSduCfg)             ((pSduCfg)->CanTpTxNPduId)
#define CANTP_RXFC_NPDU_ID(pSduCfg)          ((pSduCfg)->CanTpRxFcNPduId)
/*dele AUTOSAR V4.2*/
/*#define CANTP_TX_DL(pSduCfg)                 pSduCfg->CanTpTxDl*/
#define CANTP_NAS(pSduCfg)                   ((uint16)((pSduCfg)->CanTpNas/CANTP_MAIN_FUNCTION_PERIOD))
#define CANTP_NBS(pSduCfg)                   ((uint16)((pSduCfg)->CanTpNbs/CANTP_MAIN_FUNCTION_PERIOD))
#define CANTP_NCS(pSduCfg)                   ((uint16)((pSduCfg)->CanTpNcs/CANTP_MAIN_FUNCTION_PERIOD))
#define CANTP_TX_PADDING_ACTIVATION(pSduCfg) ((pSduCfg)->CanTpTxPaddingActive)
#define CANTP_TX_TA_TYPE(pSduCfg)            ((pSduCfg)->CanTpTxTaType)
#define CANTP_TX_ADDRESSING_FORMAT(pSduCfg)  ((pSduCfg)->CanTpTxAddrFormat)
#define CANTP_TX_NAE(pSduCfg)                ((pSduCfg)->CanTpTxNAe)
#define CANTP_TX_NSA(pSduCfg)                ((pSduCfg)->CanTpTxNSa)
#define CANTP_TX_NTA(pSduCfg)                ((pSduCfg)->CanTpTxNTa)


/*******************************************************************************
* CanTp_ChannelModeInfo
*******************************************************************************/
#define CANTP_CHANNEL_MODE(pChnModeCfg)        ((pChnModeCfg)->CanTpChannelMode)

/* -----------------------------------------------------------------------------
  Gloable Data definitions
 ----------------------------------------------------------------------------- */
/*Public function*/
#define CANTP_START_SEC_PUBLIC_CODE
#include "MemMap.h"

#define CANTP_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"


#define CANTP_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/* Administration data in RAM */
/* Channel-, connection-administration data */
STATIC VAR(CanTp_RxStateType,CANTP_INIT_DATA) CanTp_RxState[CANTP_CHANNELS];
STATIC VAR(CanTp_TxStateType,CANTP_INIT_DATA) CanTp_TxState[CANTP_CHANNELS];
STATIC VAR(CanTp_AdminDataType,CANTP_INIT_DATA) Admin;
/*STATIC VAR(RetryInfoType,CANTP_INIT_DATA) RetryInfoStruct[CANTP_NUM_TX_SDUS];*/

#define CANTP_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
*   PRIVATE Functions declare
*******************************************************************************/
#define CANTP_START_SEC_PRIVATE_CODE
#include "MemMap.h"

STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxMainFunction
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_TxMainFunction
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_RxChannelInit
(
    CONSTP2VAR(CanTp_RxStateType,CANTP_APPL_DATA,AUTOMATIC) RxStatePtr
);
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_TxChannelInit
(
    CONSTP2VAR(CanTp_TxStateType,CANTP_APPL_DATA,AUTOMATIC) TxStatePtr
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxSFPdu
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxFFPdu
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxCFPdu
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxFCPdu
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_AssembleFC
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_DataCopy
( 
    CONSTP2VAR(uint8,AUTOMATIC,CANTP_CONST) dest,
    CONSTP2CONST(uint8,CANTP_APPL_DATA, AUTOMATIC) src,
    CONST(uint16, CANTP_CONST) cnt
);

STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_PaddingData
( 
    CONSTP2VAR(uint8,AUTOMATIC,CANTP_CONST) dest, 
    CONST(uint16, CANTP_CONST) cnt, 
    CONST(uint8, CANTP_CONST) value
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_StartTransmit
(
    CONSTP2VAR(CanTp_TxStateType,AUTOMATIC,CANTP_CONST) TxStatePtr,
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) TxSduCfgPtr
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_CFTransmit
(
    CONSTP2VAR(CanTp_TxStateType,AUTOMATIC,CANTP_CONST) TxStatePtr,
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) TxSduCfgPtr
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_TxSduCreatePCI
(
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) SduCfgPtr,
    CONSTP2VAR(CanTp_TxStateType,AUTOMATIC,CANTP_CONST) tpStatePtr,
    CONSTP2VAR(uint8,AUTOMATIC,CANTP_CONST) tpbuff,
    uint8 FrameType
);
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_GetTxSduFormatOffset
(
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) SduCfgPtr,
    uint8* Offset
);
#if 0
STATIC FUNC(void,CANTP_PRIVATE_CODE) _CanTp_GetRxSduFormatOffset
(
    CONSTP2CONST(CanTp_RxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) SduCfgPtr,
    uint8* Offset
);
#endif
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxChannelCheck
(
    uint8  chnSt,
    CONSTP2CONST(CanTp_RxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) RxSduCfgPtr,
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) TxSduCfgPtr
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_TxChannelCheck
(
    uint8  chnSt,
    CONSTP2CONST(CanTp_RxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) RxSduCfgPtr,
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) TxSduCfgPtr
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_IsStateON
(
    void
);
#if(CANTP_RXSDUTRANSMITRETRY == STD_ON)
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_ReTransmitFC
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
#endif
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_IsPDULenValid
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext,
    uint8  FrameType,
    uint16 frameLen
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_GetFrameLength
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext,
    uint8   FrameType,
    uint16* frameLen
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_IsLastCF
(
    CONSTP2CONST(CanTp_RxStateType,CANTP_APPL_DATA,AUTOMATIC) pRxChnSt
);
#if((CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)||\
    (CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)||\
    (CANTP_AUTOSAREXT_WAITENOUGHBUFF == STD_ON))
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_TxWaitFCHandle
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
);
#endif
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_GoingCFProcess
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext,
    BufReq_ReturnType  BufReqResult
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_GetRxMinBufferNextBlk
(
    CanTp_RxStateType* pRxChnSt
);
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_MinBufferAccess
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext,
    boolean SetBr
);

#define CANTP_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"   

#define CANTP_START_SEC_PUBLIC_CODE
#include "MemMap.h" 

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_Init
*
* Description  : This function initializes the CanTp module. 
*
* Inputs       : CfgPtr: Pointer to the CanTp post-build configuration data.
*
* Outputs      : None.
*    
* Limitations  : None.
********************************************************************************
 END_FUNCTION_HDR*/
FUNC(void,CANTP_PUBLIC_CODE) CanTp_Init
(
    CONSTP2CONST(CanTp_ConfigType, CANTP_APPL_CONST, AUTOMATIC)pCfgPtr
)
{
    PduIdType tpChannel;
    /*uint16    i;*/    
    CanTp_RxStateType* pRxChnSt;
    CanTp_TxStateType* pTxChnSt;
    /*Std_ReturnType ret;*/
    
    CanTp_CanInterruptDisable();

    Admin.pChnModeCfg = pCfgPtr->CanTp_ChannelMode;
    Admin.pTxNsduCfg = pCfgPtr->CanTp_TxNsduCfg;
    Admin.pRxNsduCfg = pCfgPtr->CanTp_RxNsduCfg;

    Admin.pRxState = &CanTp_RxState[0];
    Admin.pTxState = &CanTp_TxState[0];  

    pRxChnSt = Admin.pRxState;
    pTxChnSt = Admin.pTxState;
    /*    
    if(Admin.InternalState != CANTP_ON)
    {
        Admin.InternalState = CANTP_ON;
    } 
    */
    
    /*for(i = 0;i < CANTP_NUM_TX_SDUS;i++)
    {
        RetryInfoStruct[i].TpDataState = TP_DATACONF;
    }*/
    /***** RX *****************************************************************/   
    for(tpChannel = 0;tpChannel < CANTP_NUM_RX_CHANNELS;tpChannel++)
    {
        /*pContext->_pRxChnSt += tpChannel;*/
        L_CanTp_RxChannelInit(pRxChnSt + tpChannel);
    }
    /***** TX *****************************************************************/  
    for(tpChannel = 0;tpChannel < CANTP_NUM_TX_CHANNELS;tpChannel++)
    {
        /*pContext->_pTxChnSt += tpChannel;*/
        L_CanTp_TxChannelInit(pTxChnSt + tpChannel);
    }
    
    Admin.InternalState = CANTP_ON;
    
    CanTp_CanInterruptRestore();
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name:CanTp_Shutdown
* Description: 
*   This function is called to shutdown the CanTp module. 
* Inputs:
*   None. 
* Outputs:
*   None. 
* Limitations:
*   None.
********************************************************************************
 END_FUNCTION_HDR*/
FUNC(void,CANTP_PUBLIC_CODE) CanTp_Shutdown(void)
{
    Admin.InternalState = CANTP_OFF;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_Transmit
*
* Description  : This service is used to request the transfer of segmented data.
*   
* Inputs       : CanTpTxSduId  : This parameter contains the unique CanTp module 
*                                identifier of the CAN N-SDU to be transmitted.
*                                Range[0,(maximum number of L-PDU IDs received)
*                                -1]
*                CanTpTxInfoPtr: An indicator of a structure with CAN N-SDU rel-
*                                ated data:indicator of a CAN N-SDU buffer and 
*                                the length of this buffer.
*   
* Outputs      : E_OK    : request is accepted.
*                E_NOT_OK: request is not accepted.
*
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_Transmit
(
    PduIdType CanTpTxSduId, 
    P2CONST(PduInfoType,AUTOMATIC,CANTP_APPL_DATA) CanTpTxInfoPtr 
)
{
    Std_ReturnType  ErrorStatus = E_OK;
    PduIdType       CanTpTxChannelId;
    uint8           TxOffsetTemp;
    P2CONST(CanTp_TxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   pTxNsdu;
    P2CONST(CanTp_RxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   pRxNsdu;
    P2CONST(CanTp_ChannelModeType,AUTOMATIC,CANTP_PRIVATE_CONST) pChnMode;

    CanTp_TxStateType* pTxChnSt;
    CanTp_RxStateType* pRxChnSt;


    if((CanTpTxInfoPtr->SduLength == 0)||\
        (CanTpTxInfoPtr->SduLength > CANTP_TXMAXLEN)||\
        (CanTpTxSduId >= CANTP_NUM_TX_SDUS))
    {
        ErrorStatus = E_NOT_OK;
    }
    else
    {
        CanTp_CanInterruptDisable();    
        if(E_OK == L_CanTp_IsStateON())
        {
            pTxNsdu = &(Admin.pTxNsduCfg[CanTpTxSduId]);
            CanTpTxChannelId = CANTP_TXTPCHANNEL_ID(pTxNsdu);
            if(CanTpTxChannelId < CANTP_NUM_TX_CHANNELS)
            {             
                pTxChnSt = &Admin.pTxState[CanTpTxChannelId];
                pRxChnSt = &Admin.pRxState[CanTpTxChannelId];
                pChnMode = Admin.pChnModeCfg + CanTpTxChannelId;
                
                if(pTxChnSt->ChannelState != cCanTpTxState_Idle)
                {
                    ErrorStatus = E_NOT_OK;
                }
                else
                {
                    /*pTxChnSt = &Admin.pTxState[CanTpTxChannelId];*/
                    /*pRxChnSt = &Admin.pRxState[CanTpTxChannelId];*/

                    L_CanTp_GetTxSduFormatOffset(pTxNsdu,&TxOffsetTemp);
                    
                    if(CANTP_TX_TA_TYPE(pTxNsdu) == CANTP_FUNCTIONAL)
                    {
                        if(CanTpTxInfoPtr->SduLength > (CANTP_TXLIMLEN-TxOffsetTemp))
                        {
                            ErrorStatus = E_NOT_OK;
                        }
                        else
                        {

                        }
                    }
                    else if(CANTP_CHANNEL_MODE(pChnMode) == CANTP_MODE_HALF_DUPLEX)
                    {
                        pRxNsdu = &(Admin.pRxNsduCfg[pRxChnSt->CurrentRxSduId]);
                        ErrorStatus = L_CanTp_RxChannelCheck(pRxChnSt->ChannelState,pRxNsdu,pTxNsdu);        
                    }
                    else
                    { 

                    }

                    if(ErrorStatus == E_OK)
                    {
                        L_CanTp_TxChannelInit(pTxChnSt);              

                        pTxChnSt->TxFormatOffset = TxOffsetTemp;
                            
                        pTxChnSt->CurrentTxSduId = CanTpTxSduId;

                        /*******************************************************************************
                        * check and modify state and timer
                        *******************************************************************************/
                        pTxChnSt->ChannelState = cCanTpTxState_WaitForTxStart;
                        pTxChnSt->Timer = 0;/*(uint16)1;*/
                        pTxChnSt->DataLength = CanTpTxInfoPtr->SduLength;
                    }
                    else
                    {

                    }
                }
            }
            else
            {
                ErrorStatus = E_NOT_OK;
            }
            
        }
        else
        {
            ErrorStatus = E_NOT_OK;  
        }
        CanTp_CanInterruptRestore(); 
    }
    return ErrorStatus;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_RxIndication
*   
* Description  : This function is called by the CAN Interface after a successful  
*                reception of a Rx CAN L-PDU.
*    
* Inputs       : CanTpRxPduId : ID of CAN L-PDU that has been received.Identifi-
*                               es the data that has been received.Range: 0..(m-
*                               aximum number of L-PDU IDs received ) - 1
*                CanTpRxPduPtr: Indicator of structure with received L-SDU (pay-
*                               load) and data length.
*  
* Outputs      : None.
*    
* Limitations  : (CANTP235)The function CanTp_RxIndication shall be callable in  
*                interrupt context (it could be called from the CAN receive 
*                interrupt). 
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,CANTP_PUBLIC_CODE) CanTp_RxIndication
(
    PduIdType CanTpRxPduId, 
    P2CONST(PduInfoType,AUTOMATIC,CANTP_APPL_DATA)pCanTpRxPduPtr
)
{
    Std_ReturnType  ErrorStatus = E_OK;
    uint16 i;
    uint16 SduId = CANTP_UNUSED;
    uint16 ChnId = CANTP_UNUSED;
    uint8  CanTpReceiveData[CANTP_MAX_FRAME_LENGTH];
    uint8  offset = 0;
    CanTp_ContextType tContext;
       
    if((E_OK == L_CanTp_IsStateON())&&(CANTP_MAX_FRAME_LENGTH >= pCanTpRxPduPtr->SduLength))
    {
        CanTp_CanInterruptDisable();
        
        tContext._pTmpData =  CanTpReceiveData;
        tContext._pRxSduCfg = &Admin.pRxNsduCfg[0];
        tContext._pTxSduCfg = &Admin.pTxNsduCfg[0];

        L_CanTp_DataCopy(tContext._pTmpData,pCanTpRxPduPtr->SduDataPtr,pCanTpRxPduPtr->SduLength);
        /***************************   check CanTp_RxNsduCfg first ******************************/
        for(i = 0;i < CANTP_NUM_RX_SDUS;i++)
        {  
            if(CanTpRxPduId == CANTP_RXNPDU_ID(tContext._pRxSduCfg))
            {
                ChnId = CANTP_RXTPCHANNEL_ID(tContext._pRxSduCfg);
                
                if(ChnId >= CANTP_NUM_RX_CHANNELS)
                {
                    
                }
                else
                {
                    if(CANTP_RX_ADDRESSING_FORMAT(tContext._pRxSduCfg) == CANTP_STANDARD)/*Addressing Format is Extended */
                    {
                        offset = CANTP_PCIOFFSET_NORMAL;
                    }  
                    /*CANTP_EXTENDED or MIXED*/
                    else if(CanTpReceiveData[EXTMIX_OFFSET] == CANTP_RX_NSA(tContext._pRxSduCfg))/*Check Extend Address */
                    {
                        offset = CANTP_PCIOFFSET_EXTMIX;
                    }
                    else
                    {
                        ErrorStatus = E_NOT_OK;
                    }                  

                    if(ErrorStatus == E_OK)
                    {
                        SduId = i;
                        break;
                    }
                    else
                    {

                    }
                }
            }
            tContext._pRxSduCfg++; 
        }

        if((ChnId < CANTP_NUM_RX_CHANNELS)&&(SduId != CANTP_UNUSED))
        {  
            ErrorStatus = E_OK;


            tContext._pRxChnSt = &Admin.pRxState[ChnId];
            /*Get the TxState Ptr*/
            tContext._pTxChnSt = &Admin.pTxState[ChnId];/*QAC Mis*/
            
            if((Admin.pTxState[ChnId].CurrentTxSduId) < CANTP_NUM_TX_SDUS)
            {
                tContext._pTxSduCfg += Admin.pTxState[ChnId].CurrentTxSduId;
            }
            tContext._pChnMdCfg = Admin.pChnModeCfg + ChnId;
            tContext._candlc    = pCanTpRxPduPtr->SduLength;

            if(tContext._pRxChnSt->ChannelState != cCanTpRxState_Idle)
            {
                if((tContext._pRxChnSt->CurrentRxSduId != SduId)&&
                    (tContext._pRxChnSt->CurrentRxSduId != CANTP_UNUSED))
                {
                    ErrorStatus = E_NOT_OK;
                }
            }
            else
            {
            
            }

            if(ErrorStatus == E_OK)
            {
                switch((uint8)(CanTpReceiveData[offset] & cCanTp_FrameTypeMask))     
                {

                    case cCanTp_SF:
                    {
                        if(tContext._pRxChnSt->CurrentRxSduId == SduId)
                        {
                            /*Terminate the current reception, report an indication, 
                            with parameter Result set to NTFRSLT_E_UNEXP_PDU, to 
                            the upper layer*/
                            /*CanTp_NUSDataIndication(RxSduId,NTFRSLT_E_UNEXP_PDU)*/
                            tContext._pRxChnSt->RxPreCancel = CANTP_RXPRECANCEL_TRUE;
                            /*save the current offset*/
                            tContext._pRxChnSt->CurrentRxFormatOffset = tContext._pRxChnSt->RxFormatOffset;
                        }
                        else
                        {
                            tContext._pRxChnSt->RxPreCancel = CANTP_RXPRECANCEL_FALSE;
                        }

                        tContext._pRxChnSt->RxFormatOffset = offset;
                        tContext._sduid = SduId;
                        
                        if(E_OK != L_CanTp_RxSFPdu(&tContext))
                        {
                            L_CanTp_RxChannelInit(tContext._pRxChnSt);
                        }
                    }
                    break;

                    case cCanTp_FF:
                    {
                        if(tContext._pRxChnSt->CurrentRxSduId == SduId)
                        {
                            /*Terminate the current reception, report an indication, with parameter Result set to NTFRSLT_E_UNEXP_PDU, to the upper layer*/
                            /*CanTp_NUSDataIndication(RxSduId,NTFRSLT_E_UNEXP_PDU);*/
                            tContext._pRxChnSt->RxPreCancel = CANTP_RXPRECANCEL_TRUE;
                            /*save the current offset*/
                            tContext._pRxChnSt->CurrentRxFormatOffset = tContext._pRxChnSt->RxFormatOffset;
                        }
                        else
                        {
                            tContext._pRxChnSt->RxPreCancel = CANTP_RXPRECANCEL_FALSE;
                        }

                        tContext._pRxChnSt->RxFormatOffset = offset;
                        tContext._sduid = SduId;
                        
                        if(E_OK != L_CanTp_RxFFPdu(&tContext))
                        {
                            L_CanTp_RxChannelInit(tContext._pRxChnSt);
                        }
                    }
                    break;

                    case cCanTp_CF:
                    {
                        if(tContext._pRxChnSt->CurrentRxSduId == SduId)
                        {
                            tContext._pRxChnSt->RxFormatOffset = offset;
                            tContext._pRxChnSt->CurrentRxSduId = SduId;
                            tContext._sduid = SduId;
                            if(E_OK != L_CanTp_RxCFPdu(&tContext))
                            {
                                L_CanTp_RxChannelInit(tContext._pRxChnSt);
                            }
                        }
                    }
                    break;

                    case cCanTp_FC:
                    {
                        ErrorStatus = E_NOT_OK;
                    }
                    break;

                    default:
                    {
                        ErrorStatus = E_OK;
                    }
                    break;
                }

            }
            else if(cCanTp_FC == ((uint8)(CanTpReceiveData[offset] & cCanTp_FrameTypeMask)))
            {
                ErrorStatus = E_NOT_OK;
            }
            else
            {
                ErrorStatus = E_OK;
            }
        }
        else
        {
            ErrorStatus = E_NOT_OK;
        }

        /***************************   check CanTp_RxNsduCfg End  ******************************/

        /***************************   check CanTp_TxNsduCfg Start ******************************/
        SduId = CANTP_UNUSED;
        ChnId = CANTP_UNUSED;

        tContext._pRxSduCfg = &Admin.pRxNsduCfg[0];
        tContext._pTxSduCfg = &Admin.pTxNsduCfg[0];

        
        if(ErrorStatus == E_NOT_OK)
        {
            for(i = 0;i < CANTP_NUM_TX_SDUS;i++)
            {  
                if(CanTpRxPduId == CANTP_RXFC_NPDU_ID(tContext._pTxSduCfg))
                {
                    ChnId = CANTP_TXTPCHANNEL_ID(tContext._pTxSduCfg);
                    if(ChnId >= CANTP_NUM_TX_CHANNELS)
                    {
                        
                    }
                    else
                    {
                        /*tContext._pTxChnSt = &Admin.pTxState[ChnId];*/

                        if(CANTP_TX_ADDRESSING_FORMAT(tContext._pTxSduCfg) == CANTP_STANDARD)/*Addressing Format is Mixed */
                        {
                            ErrorStatus = E_OK;
                            offset = CANTP_PCIOFFSET_NORMAL;
                        }
                        else if(CanTpReceiveData[EXT_OFFSET] == CANTP_TX_NSA(tContext._pTxSduCfg))/*Check Extend Address */
                        {
                            ErrorStatus = E_OK;
                            offset = CANTP_PCIOFFSET_EXTMIX;
                        }
                        else
                        {        
                            ErrorStatus = E_NOT_OK;
                        }

                        if(ErrorStatus == E_OK)
                        {
                            SduId = i;
                            break;
                        }
                        else
                        {

                        }
                    }
                }
                tContext._pTxSduCfg++;
            }

            if((ChnId < CANTP_NUM_TX_CHANNELS)&&(SduId != CANTP_UNUSED))/*if( TxSduId != CANTP_UNUSED)*/
            {
                ErrorStatus = E_OK;


                tContext._pRxChnSt = &Admin.pRxState[ChnId];
                /*Get the TxState Ptr*/
                tContext._pTxChnSt = &Admin.pTxState[ChnId];
                if((Admin.pRxState[ChnId].CurrentRxSduId) < CANTP_NUM_RX_SDUS)
                {
                    tContext._pRxSduCfg += Admin.pRxState[ChnId].CurrentRxSduId;
                }
                tContext._pChnMdCfg = Admin.pChnModeCfg + ChnId;
                tContext._candlc    = pCanTpRxPduPtr->SduLength;

                if(tContext._pTxChnSt->ChannelState != cCanTpTxState_Idle)
                {
                    if((tContext._pTxChnSt->CurrentTxSduId != CANTP_UNUSED)&&\
                        (tContext._pTxChnSt->CurrentTxSduId != SduId))
                    {     
                        ErrorStatus = E_NOT_OK;
                    }
                }
                else
                {
                    ErrorStatus = E_NOT_OK;
                }

                if(ErrorStatus == E_OK)
                {  
                    switch((uint8)(CanTpReceiveData[offset] & cCanTp_FrameTypeMask))     
                    {
                        case cCanTp_FC:
                        {
                            if(tContext._pTxChnSt->CurrentTxSduId == SduId)
                            {
                                tContext._sduid = SduId;
                                
                                if(E_OK != L_CanTp_RxFCPdu(&tContext))
                                {
                                    L_CanTp_TxChannelInit(tContext._pTxChnSt);
                                }
                            }
                        }
                        break;

                        default:

                        break;
                    }

                }
                else
                {
                }

            }
            else
            {

            }
        }
        else
        {

        }
        CanTp_CanInterruptRestore();     
    }
    else
    {

    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxConfirmation
*   
* Description  : All transmitted CAN frames(SF, FF, CF, FC) belonging to the CAN   
*                Transport will be confirmed by this function.
*    
* Inputs       : CanTpTxPduId: ID of CAN L-PDU that has been transmitted. Range: 
*                0..(maximum number of L-PDU IDs received ) - 1 
* Outputs      : None.
*    
* Limitations  : (CANTP236)The function CanTp_TxConfirmation shall be callable 
*                in interrupt context (it could be called from the CAN transmit 
*                interrupt).
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,CANTP_PUBLIC_CODE) CanTp_TxConfirmation
(
    PduIdType CanTpTxPduId
)
{
    uint16 ChnId;
    CanTp_ContextType tContext;

    if(E_OK == L_CanTp_IsStateON())
    {
        /***************************   check CanTp_TxNsduCfg first  ******************************/
        for(ChnId = 0;ChnId < CANTP_NUM_TX_CHANNELS;ChnId++)
        {
            tContext._pTxChnSt = &Admin.pTxState[ChnId];
            tContext._pTxSduCfg = &Admin.pTxNsduCfg[0];

            if((tContext._pTxChnSt->CurrentTxSduId != CANTP_UNUSED)&&(tContext._pTxChnSt->ChannelState != cCanTpTxState_Idle))
            {
                tContext._pTxSduCfg += tContext._pTxChnSt->CurrentTxSduId;
                    
                if(CANTP_TXNPDU_ID(tContext._pTxSduCfg) == CanTpTxPduId)
                {
                    if((tContext._pTxChnSt->ChannelState) != 0)    
                    {
                        switch(tContext._pTxChnSt->ChannelState)
                        {            
                            case cCanTpTxState_WaitForSFConf:
                            case cCanTpTxState_WaitForLastCFConf: 
                            {
                                CanTp_NUSDataConfirm(tContext._pTxChnSt->CurrentTxSduId,NTFRSLT_OK);
                                L_CanTp_TxChannelInit(tContext._pTxChnSt);
                            }
                            break;
                            case cCanTpTxState_WaitForFFConf:
                            {
                                tContext._pTxChnSt->ChannelState = cCanTpTxState_WaitFC;
                                tContext._pTxChnSt->Timer = CANTP_NBS(tContext._pTxSduCfg);
                            }
                            break;
                            case cCanTpTxState_WaitForCFConf:
                            {  
                                if(tContext._pTxChnSt->BlockSizeCounter != 0)
                                {
                                    tContext._pTxChnSt->BlockSizeCounter--;
                                    if(tContext._pTxChnSt->BlockSizeCounter == 0)
                                    {
                                        tContext._pTxChnSt->ChannelState = cCanTpTxState_WaitFC;
                                        tContext._pTxChnSt->Timer = CANTP_NBS(tContext._pTxSduCfg);
                                    }
                                    else   
                                    {
                                        tContext._pTxChnSt->ChannelState = cCanTpTxState_WaitForTpTxCF;
                                        tContext._pTxChnSt->Timer = tContext._pTxChnSt->STMin;
                                    }
                                }
                                else
                                {  
                                    tContext._pTxChnSt->ChannelState = cCanTpTxState_WaitForTpTxCF;
                                    tContext._pTxChnSt->Timer = tContext._pTxChnSt->STMin;
                                }
                            }
                            break;    
                            
                            default:

                            break;
                        }

                    }
                    else
                    {

                    }
                    
                    break;/*i = CANTP_CHANNELS;*/
                }
                else
                {
                
                }

            }
            else
            {

            }

        }

        /***************************   check CanTp_TxNsduCfg first  end ******************************/
        /***************************   check CanTp_RxNsduCfg second  ******************************/  
        for(ChnId = 0;ChnId < CANTP_NUM_RX_CHANNELS;ChnId++)
        {
            tContext._pRxChnSt = &Admin.pRxState[ChnId];
            tContext._pRxSduCfg = &Admin.pRxNsduCfg[0];
            
            if(tContext._pRxChnSt->CurrentRxSduId != CANTP_UNUSED) 
            {
                tContext._pRxSduCfg += tContext._pRxChnSt->CurrentRxSduId;
                
                if(CANTP_TXFC_NPDU_ID(tContext._pRxSduCfg) == CanTpTxPduId)
                {
                    if((tContext._pRxChnSt->ChannelState) != 0) 
                    {
                        switch(tContext._pRxChnSt->ChannelState)
                        {
                            case cCanTpRxState_WaitForFCConf:
                            {
                                tContext._pRxChnSt->ChannelState = cCanTpRxState_WaitCF;
                                tContext._pRxChnSt->Timer = CANTP_NCR(tContext._pRxSduCfg);
                            }
                            break;   

                            case cCanTpRxState_WaitForFCWaitConf:
                            case cCanTpRxState_WaitForFCWaitConfFFReqBuff:
                            {
                                tContext._pRxChnSt->WFTCounter++;
                                tContext._pRxChnSt->ChannelState = tContext._pRxChnSt->ChannelLastState;
                                tContext._pRxChnSt->Timer = CANTP_NBR(tContext._pRxSduCfg);    
                            }
                            break;

                            case cCanTpRxState_WaitForFCOverConf:
                            {
                                CanTp_NUSDataIndication(tContext._pRxChnSt->CurrentRxSduId,NTFRSLT_E_NO_BUFFER); 
                                L_CanTp_RxChannelInit(tContext._pRxChnSt);
                            }
                            break;

                            case cCanTpRxState_WaitForFCOverConfFFReqBuff:
                            {
                                L_CanTp_RxChannelInit(tContext._pRxChnSt);
                            }
                            break;  

                            default:

                            break;
                        }
                    }
                    else
                    {    
                    
                    }
                    
                    break;/*i = CANTP_CHANNELS;*/
                }
                else 
                {

                }

            }
            else
            {

            }

        }
        /***************************   check CanTp_RxNsduCfg second  end ******************************/
    }    
    else
    {

    }
}    

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_MainFunction
*   
* Description  : The main function for scheduling the CAN TP.
*    
* Inputs       : None.
*    
* Outputs      : None.
*    
* Limitations  : (CANTP164)The main function for scheduling the CAN TP (Entry 
*                point for scheduling)The main function will be called by the 
*                Schedule Manager or by the Free Running Timer module according 
*                of the call period needed. CanTp_MainFunction is involved in 
*                handling of CAN TP timeouts N_As, N_Bs, N_Cs, N_Ar, N_Br,N_Cr 
*                and STMmin.(CANTP300)The function CanTp_MainFunction is affect-
*                ed by configurationparameter CanTpMainFunctionPeriod. 
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,CANTP_PUBLIC_CODE) CanTp_MainFunction(void)
{
    PduIdType         CanTpChanelId;
    CanTp_ContextType tContext;
    Std_ReturnType    ret;
    
    if(E_OK == L_CanTp_IsStateON())
    {
        /*****Rx Task******************/
        for(CanTpChanelId = 0;CanTpChanelId < CANTP_CHANNELS;CanTpChanelId++)
        {
            CanTp_CanInterruptDisable();
            
            tContext._pRxChnSt = &Admin.pRxState[CanTpChanelId];
            tContext._pTxChnSt = &Admin.pTxState[CanTpChanelId];
            
            tContext._pRxSduCfg = &Admin.pRxNsduCfg[0];
            
            if(tContext._pRxChnSt->ChannelState != cCanTpRxState_Idle)
            { 
                tContext._pRxSduCfg += tContext._pRxChnSt->CurrentRxSduId;
                
                ret = L_CanTp_RxMainFunction(&tContext);
                
                if(ret != E_OK)
                {
                    L_CanTp_RxChannelInit(tContext._pRxChnSt);
                }
            }
            CanTp_CanInterruptRestore();
        } 
        /*****Tx Task******************/
        for(CanTpChanelId = 0;CanTpChanelId < CANTP_CHANNELS;CanTpChanelId++)
        {
            CanTp_CanInterruptDisable();
            
            tContext._pRxChnSt = &Admin.pRxState[CanTpChanelId];
            tContext._pTxChnSt = &Admin.pTxState[CanTpChanelId];

            tContext._pTxSduCfg = &Admin.pTxNsduCfg[0];
            
            /******************************Tx**********************************/
            if(tContext._pTxChnSt->ChannelState != cCanTpTxState_Idle) 
            {
                tContext._pTxSduCfg +=  tContext._pTxChnSt->CurrentTxSduId;
                ret = L_CanTp_TxMainFunction(&tContext);
                if(ret != E_OK)
                {
                    L_CanTp_TxChannelInit(tContext._pTxChnSt);
                }
            }
            CanTp_CanInterruptRestore();
        }

    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_GetVersionInfo
*   
* Description  : This function returns the version information of the CanTp 
*                module.
* Inputs       : pVersionInfo: Indicator as to where to store the version infor-
*                              mation of this module.
*    
* Outputs      : None.
*    
* Limitations  : The function CanTp_GetVersionInfo shall be pre compile timef 
*                configurable On or Off by the configuration parameter:CANTP_VE-
*                RSION_INFO_API.
********************************************************************************
END_FUNCTION_HDR*/

#if(CANTP_VERSION_INFO_API == STD_ON)
FUNC(void,CANTP_PUBLIC_CODE) CanTp_GetVersionInfo
(
    P2VAR(Std_VersionInfo_Type,AUTOMATIC,CANTP_APPL_DATA) VersionInfo
)
{
    VersionInfo->vendorID = CANTP_VENDOR_ID;
    VersionInfo->moduleID = CANTP_MODULE_ID;
    VersionInfo->instanceID = CANTP_INSTANCE_ID;
    VersionInfo->sw_major_version = CANTP_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = CANTP_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = CANTP_SW_PATCH_VERSION;
}
#endif

#if(CANTP_TC == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_CancelTransmitRequest
*   
* Description  : This service is used to cancel the transmission of an N-SDU 
*                that has already requested for transmission by calling CanTp_T-
*                ransmit service. 
*   
* Inputs       : CanTpTxSduId: This parameter contains the unique CanTp module 
*                              identifier of the N-SDU to be cancelled for tran-
*                              smission.Range:0..(maximum number of L-PDU IDs t-
*                              ransmmited ) - 1.
*     
* Outputs      : E_OK    : Cancellation request of the specified N-SDU is 
*                          accepted.
*                E_NOT_OK: Cancellation request is rejected; the reason can be 
*                          that request is issued for an N-SDU that is not segm-
*                          ented,request is issued after the last CF has been 
*                          requested for transmission or cancellation is not 
*                          possible for the related N-SDU due to configuration.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_CancelTransmitRequest
(
    PduIdType CanTpTxSduId
)
{
    Std_ReturnType result = E_NOT_OK;
    CanTp_TxStateType*     pTxChnSt;
    PduIdType chid;

    CanTp_CanInterruptDisable();
    if(CanTpTxSduId < CANTP_NUM_TX_SDUS)
    {
        chid = CANTP_TXTPCHANNEL_ID((&Admin.pTxNsduCfg[CanTpTxSduId]));

        if(chid < CANTP_NUM_TX_CHANNELS)
        {
            pTxChnSt = &Admin.pTxState[chid];
            if(pTxChnSt->ChannelState != cCanTpTxState_Idle)
            {
                if((pTxChnSt->CurrentTxSduId == CanTpTxSduId) && \
                    (pTxChnSt->ChannelState != cCanTpTxState_WaitForLastCFConf))
                {
                    result = CanTp_CanCancelTransmit(CANTP_TXNPDU_ID((&Admin.pTxNsduCfg[CanTpTxSduId])));
                    if(E_OK == result)/*CanTp_CanCancelTransmit(CanTpTxSduId))*/
                    {         
                        L_CanTp_TxChannelInit(pTxChnSt);
                        result = E_OK;
                    }
                }
            }
            else
            {
                result = E_OK;
            }
        }
    }
    
    CanTp_CanInterruptRestore();
    return result;
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_CancelReceiveRequest
*               
* Description  : This service is used to cancel the reception of an ongoing N-SDU.
*               
* Inputs       : CanTpRxSduId: Identifier of the received N-SDU.Range: 0..(maxi-
*                mum number of L-PDU IDs received ) - 1.
*     
* Outputs      : E_OK    : Cancellation request of the specified N-SDU is 
*                          accepted.
*                E_NOT_OK: Cancellation request is rejected; the reason can be 
*                          that request is issued for an N-SDU that is not segm-
*                          ented,request is issued after the last CF has been 
*                          requested for transmission or cancellation is not 
*                          possible for the related N-SDU due to configuration.

* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/   
FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_CancelReceiveRequest
(
    PduIdType CanTpRxSduId
)
{
    Std_ReturnType result = E_NOT_OK; 
    CanTp_RxStateType*     pRxChnSt;
    PduIdType chid;
    
    CanTp_CanInterruptDisable();
    if(CanTpRxSduId < CANTP_NUM_RX_SDUS)
    {
        chid = CANTP_RXTPCHANNEL_ID((&Admin.pRxNsduCfg[CanTpRxSduId]));
        if(chid < CANTP_NUM_RX_CHANNELS)
        {
            pRxChnSt = &Admin.pRxState[chid];
            if(pRxChnSt->ChannelState != cCanTpRxState_Idle)
            {
                if(pRxChnSt->CurrentRxSduId == CanTpRxSduId)
                {
                    L_CanTp_RxChannelInit(pRxChnSt);
                    result = E_OK;
                }
            }
        }
    }
    CanTp_CanInterruptRestore();
    return result;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_ChangeParameterRequest
*
* Description  : This service is used to request the change of reception  
*                parameters BS and STmin for a specified N-SDU.

* Inputs       : CanTpSduId: Identifier of the received N-SDU on which the
*                            reception parameter has to be changed.
*                parameter : Specify the parameter to which the value has to be 
*                            changed (BS or STmin).
*                value     : The new value of the parameter.
*     
* Outputs      : E_OK    : request is accepted.
*                E_NOT_OK: request is not accepted. 
*    
* Limitations  : (CANTP303)A parameter change is only possible if the related 
*                N-SDU is not in the process of reception , i.e. a change of
*                parameter value it is not possible after reception of FF until 
*                indication for last CF reception of the related N-SDU.   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_ChangeParameterRequest
(
    PduIdType CanTpSduId,
    CanTpParameterType parameter,
    uint16 value
)
{
    Std_ReturnType result = E_OK;
    if((Admin.pRxState[CanTpSduId].ChannelState) == cCanTpRxState_Idle)
    {
        if(parameter == CANTP_BS_PARAMETER)
        {
            Admin.pRxState[CanTpSduId].BlockSize = (uint8)value;  /*NTFRSLT_E_VALUE_NOT_OK*/     
        }
        else /*CANTP_STMIN_PARAMETER*/
        {
            Admin.pRxState[CanTpSduId].STMin = (uint8)value;
        }
    }
    else
    {
        result = E_NOT_OK;
    }
    return result;
}
#define CANTP_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_PRIVATE_CODE
#include "MemMap.h" 
#if((CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)||\
    (CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)||\
    (CANTP_AUTOSAREXT_WAITENOUGHBUFF == STD_ON))
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_TxWaitFCHandle
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{
    CanTp_RxStateType* pRxChnSt;
    uint8 curchst;
    
    pRxChnSt = pContext->_pRxChnSt;
    curchst = pRxChnSt->ChannelState;


    if(CANTP_WFTMAX(pContext->_pRxSduCfg) < pRxChnSt->WFTCounter)
    {
        /*abord*/
        if(curchst == cCanTpRxState_WaitForFFRequestBuffer)
        {
            pRxChnSt->ChannelState = cCanTpRxState_WFTmax_OvRnFFReqBuff;
        }
        else
        {
            pRxChnSt->ChannelState = cCanTpRxState_WFTmax_OvRn;
        }
    }
    else
    {   
        pRxChnSt->ChannelLastState = pRxChnSt->ChannelState;
        if(curchst == cCanTpRxState_WaitForFFRequestBuffer)
        {
            pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCWaitFFReqBuff;
        }
        else
        {
            pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCWait;
        }
    }
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_RxMainFunction

* Description  : This function is called by CanTp_MainFunction to handle N_Ar, 
*                N_Br,N_Cr and STMmin. 

* Inputs       : CanTpRxChannelId: Channel number of the received TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxMainFunction
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{
#if((CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)||(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON))
    BufReq_ReturnType  BufReqResult;
#endif
    Std_ReturnType     ret = E_OK;
    CanTp_RxStateType* pRxChnSt;

    pRxChnSt = pContext->_pRxChnSt;
    
    if(pRxChnSt->Timer != 0)
    {
        pRxChnSt->Timer--; 
    }
    
    do
    {
#if(CANTP_RXSDUTRANSMITRETRY == STD_ON)
        if(((uint8)(pRxChnSt->ChannelState & cCanTpState_Retransmit))==cCanTpState_Retransmit)
        {
            if(pRxChnSt->Timer == 0)
            {
                /*CanTp_NUSDataIndication(CanTp_RxState[CanTpRxChannelId].CurrentRxSduId,NTFRSLT_E_TIMEOUT_A);*/
                pRxChnSt->ChannelState ^= cCanTpState_Retransmit;/*Clear Retransmit Flag */        
            }
            else
            {
                /*_CanTp_AssembleFC(pContext);*/  
                L_CanTp_ReTransmitFC(pContext);
            }
            break;
        }
#endif
#if(CANTP_AUTOSAREXT_WAITENOUGHBUFF == STD_ON)
        if((pRxChnSt->ChannelState) == cCanTpRxState_WaitEnoughBuffer)/**/
        {
            pRxChnSt->RxNPduInfo.SduLength = 0;
            (void)CanTp_CopyRxData(pRxChnSt->CurrentRxSduId,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));               
            if(pRxChnSt->AvailableBufLength >= pRxChnSt->MinBuffSize)
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFC;
                pRxChnSt->Timer = 0;/*Tx FC in the current task*/
            }
            else if(pRxChnSt->Timer <= ((uint16)1))/*Before expiration of the N_Br timer,Send FC Wait*/
            {
                if(CANTP_WFTMAX(pContext->_pRxSduCfg) == 0)/*CANTP223*/
                {
                    pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                }
                else
                {
                    L_CanTp_TxWaitFCHandle(pContext);
                }
                pRxChnSt->Timer = 0;
            }
            else
            {
    
            }
            break;
        }
#endif
#if(CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)
        if((pRxChnSt->ChannelState) == cCanTpRxState_WaitForSFRequestBuffer)/*CANTP222*/
        {
            BufReqResult = CanTp_NUSDataSFIndication(pRxChnSt->CurrentRxSduId,pRxChnSt->DataLength,&(pRxChnSt->AvailableBufLength));            
            if(BufReqResult == BUFREQ_OK) 
            {
                BufReqResult = CanTp_CopyRxData(pRxChnSt->CurrentRxSduId,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));               
                if(BufReqResult == BUFREQ_OK) 
                {
                    CanTp_NUSDataIndication(pRxChnSt->CurrentRxSduId,NTFRSLT_OK);
                    ret = E_NOT_OK;/*Reset Rx Channel*/
                }
    #if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
                else if(BufReqResult == BUFREQ_E_BUSY)
                {
                    pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferSF;
                }
    #endif
                else/*BUFREQ_E_NOT_OK   BUFREQ_E_OVFL  #if(CANTP_AUTOSAR42 != STD_ON)BUFREQ_E_BUSY*/
                {
                    /*abord*/
                    pRxChnSt->ChannelState = cCanTpRxState_NoBuffer;/* inform appl with relust NTFRSLT_E_NO_BUFFER */
                    pRxChnSt->Timer = 0;/*in the task*/
                }
            }
    #if(CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)
            else if(BufReqResult == BUFREQ_E_BUSY)
            {
                
            }
    #endif        
            else/*BUFREQ_E_NOT_OK   BUFREQ_E_OVFL   #if(CANTP_AUTOSAR42 != STD_ON)BUFREQ_E_BUSY*/
            {
                /*abord*/
                pRxChnSt->Timer = 0;/*init Tp Rx Channel in the task, do not inform upper layer*/
            }
            break;
        }  
#endif
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
        if((pRxChnSt->ChannelState) == cCanTpRxState_WaitForRxBufferSF)
        {
            BufReqResult = CanTp_CopyRxData(pRxChnSt->CurrentRxSduId,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));
            if(BufReqResult == BUFREQ_OK)
            {                    
                CanTp_NUSDataIndication(pRxChnSt->CurrentRxSduId,NTFRSLT_OK);
                ret = E_NOT_OK;/*Reset Rx Channel*/
            }
    #if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
            else if(BufReqResult == BUFREQ_E_BUSY)
            {
    
            }
    #endif
            else/*BUFREQ_E_NOT_OK BUFREQ_E_OVFL #if(CANTP_AUTOSAR42 != STD_ON)BUFREQ_E_BUSY*/
            {
                /*abord*/
                pRxChnSt->ChannelState = cCanTpRxState_NoBuffer;/* inform appl with relust NTFRSLT_E_NO_BUFFER */
                pRxChnSt->Timer = 0;/*in the task*/
            }
            break;
        }
#endif
#if(CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)
        if((pRxChnSt->ChannelState) == cCanTpRxState_WaitForFFRequestBuffer)/*CANTP222*/
        {
            BufReqResult = CanTp_NUSDataFFIndication(pRxChnSt->CurrentRxSduId,pRxChnSt->DataLength,&(pRxChnSt->AvailableBufLength));           
            if(BufReqResult == BUFREQ_OK)
            { 
                if(((0 == CANTP_BS(pContext->_pRxSduCfg))&&(pRxChnSt->AvailableBufLength < pRxChnSt->DataLength))||\
                    (pRxChnSt->AvailableBufLength < RX_FF_DataLength(pRxChnSt)))
                {
                    pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                    pRxChnSt->Timer = 0; /*Transmit FC in the task immediately*/ 
                }          
                else
                {
                    pRxChnSt->BlockSizeCounter = pRxChnSt->BlockSize;
                    pRxChnSt->STMin = CANTP_STMIN(pContext->_pRxSduCfg);/**/
                    BufReqResult = CanTp_CopyRxData(pRxChnSt->CurrentRxSduId,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));               
    
                    if(BufReqResult == BUFREQ_OK)
                    {
                        pRxChnSt->DataLength -= RX_FF_DataLength(pRxChnSt);
                        (void)L_CanTp_GetRxMinBufferNextBlk(pRxChnSt);
                        (void)L_CanTp_MinBufferAccess(pContext,FALSE);
                    }
            #if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
                    else if(BufReqResult == BUFREQ_E_BUSY)/*BUFREQ_E_BUSY*/
                    { 
                        pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferFF;
                        if(pRxChnSt->Timer <= ((uint16)1))/*Before expiration of the N_Br timer,Send FC Wait*/
                        {
                            if(CANTP_WFTMAX(pContext->_pRxSduCfg) == 0)/*CANTP223*/
                            {
                                /*abord*/
                                pRxChnSt->ChannelState = cCanTpRxState_NoBuffer;
                            }
                            else
                            {
                                L_CanTp_TxWaitFCHandle(pContext);
                            }
                            pRxChnSt->Timer = 0;                    
                        }               
                    }
            #endif
                    else/*BUFREQ_E_NOT_OK BUFREQ_E_OVFL;#if(CANTP_AUTOSAR42 != STD_ON) BUFREQ_E_BUSY*/
                    {/*abord*/
                        pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                        pRxChnSt->Timer = 0;/*Tx FC in the current task*/
                    }
                }
            } 
    #if(CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)
            else if(BufReqResult == BUFREQ_E_BUSY)/*BUFREQ_E_BUSY*/
            { 
                pRxChnSt->ChannelState = cCanTpRxState_WaitForFFRequestBuffer;
                if(pRxChnSt->Timer <= ((uint16)1))/*Before expiration of the N_Br timer,Send FC Wait*/
                {
                    if(CANTP_WFTMAX(pContext->_pRxSduCfg) == 0)/*CANTP223*/ 
                    {
                        /*Tx FCOVER*/
                        pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrunFFReqBuff;
                    }
                    else
                    {
                        L_CanTp_TxWaitFCHandle(pContext);
                    }
                    pRxChnSt->Timer = 0;
                }
                else
                {
    
                }
            }
    #endif
            else/*BUFREQ_E_NOT_OK BUFREQ_E_OVFL;#if(CANTP_AUTOSAR42 != STD_ON) BUFREQ_E_BUSY*/
            {  /*abord*/
                pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrunFFReqBuff;/*cCanTpRxState_WaitForTxFCOverrun;*/
                pRxChnSt->Timer = 0;/*Tx FC in the current task*/ 
            }
            break;
        }
#endif
    
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
        if((pRxChnSt->ChannelState) == cCanTpRxState_WaitForRxBufferFF)
        {
            BufReqResult = CanTp_CopyRxData(pRxChnSt->CurrentRxSduId,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));
    
            if(BufReqResult == BUFREQ_OK)
            {
                pRxChnSt->DataLength -= RX_FF_DataLength(pRxChnSt);
                (void)L_CanTp_GetRxMinBufferNextBlk(pRxChnSt);  
                (void)L_CanTp_MinBufferAccess(pContext,FALSE);
            }
    #if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
            else if(BufReqResult == BUFREQ_E_BUSY)
            { 
                pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferFF;
                if(pRxChnSt->Timer <= ((uint16)1))/*Before expiration of the N_Br timer,Send FC Wait*/
                {
                    if(CANTP_WFTMAX(pContext->_pRxSduCfg) == 0)/*CANTP223*/ 
                    {
                        /*abord*/
                        pRxChnSt->ChannelState = cCanTpRxState_NoBuffer;
                        pRxChnSt->Timer = 0;/* inform appl with relust NTFRSLT_E_NO_BUFFER */
                    }
                    else
                    {
                        L_CanTp_TxWaitFCHandle(pContext);
                    }
                    pRxChnSt->Timer = 0;
                }
    
            } 
    #endif
            else/*BUFREQ_E_OVFL    BUFREQ_E_NOT_OK*/
            {
                /*abord*/
                pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                pRxChnSt->Timer = 0;/*Tx FC in the current task*/
            }
            break;
        }
#endif
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
        if((pRxChnSt->ChannelState) == cCanTpRxState_WaitForRxBufferGoingCF)
        {
            BufReqResult = CanTp_CopyRxData(pRxChnSt->CurrentRxSduId,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));
            pRxChnSt->ChannelState = cCanTpRxState_WaitCF;                
    
            if(BufReqResult == BUFREQ_OK)
            {
                pRxChnSt->DataLength -= RX_CF_DataLength(pRxChnSt);
                        
                pRxChnSt->ChannelState = cCanTpRxState_WaitCF;  
                /*Timer Setting here is no used because CF has been copyed to buffer*/
                pRxChnSt->Timer = (uint16)(CANTP_NCR(pContext->_pRxSduCfg) - \
                    ((CANTP_STMIN(pContext->_pRxSduCfg)/CANTP_MAIN_FUNCTION_PERIOD) - pRxChnSt->Timer));
            }
    #if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
            else if(BufReqResult == BUFREQ_E_BUSY)
            {   
                pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferGoingCF;          
                if(pRxChnSt->Timer == 0)
                {
                    pRxChnSt->ChannelState = cCanTpRxState_NoBuffer;/* inform appl with relust NTFRSLT_E_NO_BUFFER */
                }
                else
                {
    
                }
            }
    #endif
            else /*BUFREQ_E_NOT_OK  BUFREQ_E_OVFL*/
            {   /*abort */
                pRxChnSt->Timer = 0;
                pRxChnSt->ChannelState = cCanTpRxState_NoBuffer;/* inform appl with relust NTFRSLT_E_NO_BUFFER */
            }
            break;
        }
#endif
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
        if((pRxChnSt->ChannelState) == cCanTpRxState_WaitForRxBufferLastCFBlock)
        {
            BufReqResult = CanTp_CopyRxData(pRxChnSt->CurrentRxSduId,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));
            pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFC;                
      
            if(BufReqResult == BUFREQ_OK)
            {            
                pRxChnSt->DataLength -= RX_CF_DataLength(pRxChnSt);
                (void)L_CanTp_GetRxMinBufferNextBlk(pRxChnSt);
                (void)L_CanTp_MinBufferAccess(pContext,FALSE);
            } 
    #if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)                       
            else if(BufReqResult == BUFREQ_E_BUSY)/* CANTP268 */
            { 
                pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferLastCFBlock;
                if(pRxChnSt->Timer <= ((uint16)1))/*Before expiration of the N_Br timer,Send FC Wait*/
                {
                    if(CANTP_WFTMAX(pContext->_pRxSduCfg) == 0)/*CANTP223*/
                    {
                        pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                    }
                    else
                    {
                        L_CanTp_TxWaitFCHandle(pContext);
                    }
                    pRxChnSt->Timer = 0;
                }
                else
                {
                
                }
            }
    #endif
            else/*BUFREQ_E_NOT_OK      BUFREQ_E_OVFL*/
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                pRxChnSt->FlowStatus = cCanTp_FC_FS_Overrun;
                pRxChnSt->Timer = 0; /*Transmit FC in the task */
            }
            break;
        }
#endif
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON) 
        if((pRxChnSt->ChannelState) == cCanTpRxState_WaitForRxBufferLastCF)
        {            
            BufReqResult = CanTp_CopyRxData(pRxChnSt->CurrentRxSduId,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));
    
            if(BufReqResult == BUFREQ_OK)
            {                                                                                   
                CanTp_NUSDataIndication(pRxChnSt->CurrentRxSduId,NTFRSLT_OK); 
                ret = E_NOT_OK;/*Reset Rx Channel*/
            }  
    #if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON) 
            else if(BufReqResult == BUFREQ_E_BUSY)/* CANTP268 */
            { 
                pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferLastCF;
                if(pRxChnSt->Timer == 0)
                {
                    /*abord*/
                    pRxChnSt->ChannelState = cCanTpRxState_NoBuffer;/* inform appl with relust NTFRSLT_E_NO_BUFFER */
                }
                else
                {
                
                }
            }
    #endif
            else/*BUFREQ_E_NOT_OK      BUFREQ_E_OVFL*/
            {
                pRxChnSt->ChannelState = cCanTpRxState_NoBuffer;/* inform appl with relust NTFRSLT_E_NO_BUFFER */
                pRxChnSt->Timer = 0;/*Transmit FC in the task */               
            }
            break;
        }
#endif

    }while(0);

    /*ret == E_OK  Reset Channel*/
    if((ret == E_OK)&&(pRxChnSt->Timer == 0)&&(pRxChnSt->ChannelState != cCanTpRxState_Idle))
    {   /*TX FC switch*/   /*Timeout switch*/
        switch(pRxChnSt->ChannelState)
        {
            case cCanTpRxState_WaitForTxFC:
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForFCConf;
                pRxChnSt->FlowStatus = cCanTp_FC_FS_CTS;
                pRxChnSt->Timer = CANTP_NAR(pContext->_pRxSduCfg);
                L_CanTp_AssembleFC(pContext);
            }
            break;
            
            /*case cCanTpRxState_WaitEnoughBuffer:*/
            case cCanTpRxState_WaitForTxFCOverrun:
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForFCOverConf;
                pRxChnSt->FlowStatus = cCanTp_FC_FS_Overrun;
                pRxChnSt->Timer = CANTP_NAR(pContext->_pRxSduCfg);
                L_CanTp_AssembleFC(pContext);
            }
            break;  

            case cCanTpRxState_WaitForTxFCOverrunFFReqBuff:  
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForFCOverConfFFReqBuff;/*cCanTpRxState_WaitForFCOverConf;*/
                pRxChnSt->FlowStatus = cCanTp_FC_FS_Overrun;
                pRxChnSt->Timer = CANTP_NAR(pContext->_pRxSduCfg);
                L_CanTp_AssembleFC(pContext);
            }
            break;

            case cCanTpRxState_WaitForTxFCWait:
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForFCWaitConf;
                pRxChnSt->FlowStatus = cCanTp_FC_FS_Wait;
                pRxChnSt->Timer = CANTP_NAR(pContext->_pRxSduCfg);
                L_CanTp_AssembleFC(pContext); 
            }
            break;
            
            case cCanTpRxState_WaitForTxFCWaitFFReqBuff:
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForFCWaitConfFFReqBuff;
                pRxChnSt->FlowStatus = cCanTp_FC_FS_Wait;
                pRxChnSt->Timer = CANTP_NAR(pContext->_pRxSduCfg);
                L_CanTp_AssembleFC(pContext); 
            }
            break;
            
            case cCanTpRxState_WaitCF:
            {
                CanTp_NUSDataIndication(pRxChnSt->CurrentRxSduId,NTFRSLT_E_TIMEOUT_CR);
                ret = E_NOT_OK;/*Reset Rx Channel*/
            }
            break;
              
            case cCanTpRxState_WaitForFCConf:          
            case cCanTpRxState_WaitForFCWaitConf:  
            case cCanTpRxState_WaitForFCOverConf:
            {
                (void)CanTp_CanCancelTransmit(CANTP_TXFC_NPDU_ID(pContext->_pRxSduCfg));   
                CanTp_NUSDataIndication(pRxChnSt->CurrentRxSduId,NTFRSLT_E_TIMEOUT_A);
                ret = E_NOT_OK;/*Reset Rx Channel*/
            }
            break;
            
            case cCanTpRxState_WaitForRxBufferSF:
            case cCanTpRxState_NoBuffer:  
            case cCanTpRxState_WaitForRxBufferLastCF:
            /*case cCanTpRxState_WaitEnoughBuffer:*/
            {
                CanTp_NUSDataIndication(pRxChnSt->CurrentRxSduId,NTFRSLT_E_NO_BUFFER);
                ret = E_NOT_OK;/*Reset Rx Channel*/
            }
            break;
            
            case cCanTpRxState_WFTmax_OvRn:
            {
                CanTp_NUSDataIndication(pRxChnSt->CurrentRxSduId,NTFRSLT_E_WFT_OVRN);
                ret = E_NOT_OK;/*Reset Rx Channel*/
            }
            break;
            
            case cCanTpRxState_WFTmax_OvRnFFReqBuff:
            {
                ret = E_NOT_OK;/*Reset Rx Channel*/
            }
            break;

            case cCanTpRxState_WaitForSFRequestBuffer:/* wait SFRxReqBuff(CanTpStartOfReception) Timeout ,do not inform Upper*/
            case cCanTpRxState_WaitForFFRequestBuffer:/* wait FFRxReqBuff(CanTpStartOfReception) Timeout ,do not inform Upper*/
            case cCanTpRxState_WaitForFCOverConfFFReqBuff:/* Tx Fc Timeout ,do not inform Upper*/
            case cCanTpRxState_WaitForFCWaitConfFFReqBuff:/* Tx Fc Timeout ,do not inform Upper*/
            {
                /*CanTp_ChannelInit(CANTP_RX_CHANNEL,CanTpRxChannelId);*/
                ret = E_NOT_OK;/*Reset Rx Channel*/
            }
            break;
            
            default:

            break;
        }
    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxMainFunction

* Description  : This function is called by CanTp_MainFunction to handle N_As, 
*                N_Bs and N_Cs. 

* Inputs       : CanTpTxChannelId: Channel number of the Transimmit TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_TxMainFunction
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{
    /*PduInfoType CanTpTxNPduInfo;*/
#if(CANTP_TXSDUTRANSMITRETRY == STD_ON)
    Std_ReturnType CanIfTxRet;
#endif
    Std_ReturnType ret = E_OK;
    CanTp_TxStateType* TxStatePtr;
    P2CONST(CanTp_TxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST) TxSduCfgPtr;
	
    TxStatePtr = pContext->_pTxChnSt;
    TxSduCfgPtr = pContext->_pTxSduCfg;

    if(TxStatePtr->Timer != 0)
    {
        TxStatePtr->Timer--; 
    }
    
#if(CANTP_TXSDUTRANSMITRETRY == STD_ON)
    if(((uint8)(TxStatePtr->ChannelState & cCanTpState_Retransmit)) == cCanTpState_Retransmit)
    {
        if(TxStatePtr->Timer == 0)
        {
            CanTp_NUSDataConfirm(TxStatePtr->CurrentTxSduId,NTFRSLT_E_TIMEOUT_A);
            ret = E_NOT_OK;/*for reset txchannel only*/
        }
        else
        {
            CanIfTxRet = CanTp_CanTransmit(CANTP_TXNPDU_ID(TxSduCfgPtr),&(TxStatePtr->TxNPduInfo));
            if(E_OK == CanIfTxRet)/*CanTp_CanTransmit(CANTP_TXNPDU_ID(CanTp_TxState[CanTpTxChannelId].CurrentTxSduId),&CanTp_TxState[CanTpTxChannelId].TxNPduInfo))*/
            {
                TxStatePtr->ChannelState ^= cCanTpState_Retransmit;/*Clear Retransmit Flag */
                /*here Do not need to ReSrart NAs*/
            }
            else
            {

            }

        }
    }
    else
#endif
    {    
        if(TxStatePtr->Timer == 0) /* Set a prestate for checking a interrupt while decrementing */
        {
            switch(TxStatePtr->ChannelState)
            {
                case cCanTpTxState_WaitForTxStart:
                {
                    ret = L_CanTp_StartTransmit(TxStatePtr,TxSduCfgPtr);
                }
                break;      

                case cCanTpTxState_WaitFC:
                {
                    CanTp_NUSDataConfirm(TxStatePtr->CurrentTxSduId,NTFRSLT_E_TIMEOUT_BS);          
                    ret = E_NOT_OK;/*for reset txchannel only*/
                }
                break;
                
                case cCanTpTxState_WaitForTpTxCF:
                {
                    ret = L_CanTp_CFTransmit(TxStatePtr,TxSduCfgPtr);
                }
                break;
                
                case cCanTpTxState_WaitForFFConf:
                case cCanTpTxState_WaitForSFConf:  
                case cCanTpTxState_WaitForCFConf:
                case cCanTpTxState_WaitForLastCFConf:
                {
                    (void)CanTp_CanCancelTransmit(CANTP_TXNPDU_ID(TxSduCfgPtr));
                    CanTp_NUSDataConfirm(TxStatePtr->CurrentTxSduId,NTFRSLT_E_TIMEOUT_A);
                    ret = E_NOT_OK;/*for reset txchannel only*/
                }
                break;
                /* end */
                default:    
                {
                    ret = E_NOT_OK;/*for reset txchannel only*/
                }
                break;
            }    
        }
        else
        {
        
        }
    }

    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: _CanTp_TxSduCreatePCI

* Description  : This function is called by CanTp_MainFunction to handle N_As, 
*                N_Bs and N_Cs. 

* Inputs       : CanTpTxChannelId: Channel number of the Transimmit TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_TxSduCreatePCI
(
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) SduCfgPtr,
    CONSTP2VAR(CanTp_TxStateType,AUTOMATIC,CANTP_CONST) tpStatePtr,
    CONSTP2VAR(uint8,AUTOMATIC,CANTP_CONST) tpbuff,
    uint8 FrameType
)
{
    Std_ReturnType ret = E_OK;

    switch(CANTP_TX_ADDRESSING_FORMAT(SduCfgPtr))
    {

        case CANTP_EXTENDED:
            *(tpbuff + EXT_OFFSET) = CANTP_TX_NTA(SduCfgPtr);/*Extended Address*/

        break;
        case CANTP_MIXED:
            *(tpbuff + MIX_OFFSET) = CANTP_TX_NAE(SduCfgPtr);/*AE Address */
        break;

        case CANTP_STANDARD:
            /*Addressing Format is Standard */
        break;
        default:
            ret = E_NOT_OK;
        break;

    }
    
    if(ret == E_OK)
    {
        switch(FrameType)
        {
            case cCanTp_SF:
                *(tpbuff + TX_NPCI_OFFSET(tpStatePtr)) = (uint8)tpStatePtr->DataLength;
            break;
            case cCanTp_FF:
                *(tpbuff + TX_NPCI_OFFSET(tpStatePtr)) = (cCanTp_FF)|((uint8)(tpStatePtr->DataLength >> CANTP_BITS8));    
                *(tpbuff + TX_DL_OFFSET(tpStatePtr)) = ((uint8)(tpStatePtr->DataLength));	
            break;

            case cCanTp_CF:

                *(tpbuff + TX_NPCI_OFFSET(tpStatePtr)) = (cCanTp_CF) | tpStatePtr->SeqNumber;

                if(tpStatePtr->SeqNumber == CANTP_MAXSNNUM)
                {
                    tpStatePtr->SeqNumber = 0;
                }
                else
                {
                    tpStatePtr->SeqNumber++;
                }

            break;

            /*case cCanTp_FC:

            break;*/

            default:
                ret = E_NOT_OK;
            break;
        }
    }
    return ret;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxMainFunction

* Description  : This function is called by CanTp_MainFunction to handle N_As, 
*                N_Bs and N_Cs. 

* Inputs       : CanTpTxChannelId: Channel number of the Transimmit TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_GetTxSduFormatOffset
(
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) SduCfgPtr,
    uint8* Offset
)
{
    if(CANTP_TX_ADDRESSING_FORMAT(SduCfgPtr) == CANTP_STANDARD)
    {
        *Offset = CANTP_PCIOFFSET_NORMAL;/*TxFormatOffset[tpChannel]=1u;*/
    }
    else
    {
        *Offset = CANTP_PCIOFFSET_EXTMIX; /*TxFormatOffset[tpChannel]=0;*/
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxMainFunction

* Description  : This function is called by CanTp_MainFunction to handle N_As, 
*                N_Bs and N_Cs. 

* Inputs       : CanTpTxChannelId: Channel number of the Transimmit TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
#if 0
STATIC FUNC(void,CANTP_PRIVATE_CODE) _CanTp_GetRxSduFormatOffset
(
    CONSTP2CONST(CanTp_RxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) SduCfgPtr,
    uint8* Offset
)
{
    if(CANTP_RX_ADDRESSING_FORMAT(SduCfgPtr) == CANTP_STANDARD)
    {
        *Offset = CANTP_PCIOFFSET_NORMAL;/*TxFormatOffset[tpChannel]=1u;*/
    }
    else
    {
        *Offset = CANTP_PCIOFFSET_EXTMIX; /*TxFormatOffset[tpChannel]=0;*/
    }
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxMainFunction

* Description  : This function is called by CanTp_MainFunction to handle N_As, 
*                N_Bs and N_Cs. 

* Inputs       : CanTpTxChannelId: Channel number of the Transimmit TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxChannelCheck
(
    uint8  chnSt,
    CONSTP2CONST(CanTp_RxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) RxSduCfgPtr,
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) TxSduCfgPtr
)
{
    Std_ReturnType ret = E_OK;

    if(chnSt != cCanTpRxState_Idle)
    {              
        if(CANTP_RX_TA_TYPE(RxSduCfgPtr) == CANTP_FUNCTIONAL )
        {
            /*reserved*/
        }
        else if((CANTP_TXNPDU_ID(TxSduCfgPtr) == CANTP_TXFC_NPDU_ID(RxSduCfgPtr)) || \
        (CANTP_UNUSED == CANTP_TXFC_NPDU_ID(RxSduCfgPtr)))
        {
            ret = E_NOT_OK;
        }
        else
        {

        }
    } 
                   
    return ret;

}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxMainFunction

* Description  : This function is called by CanTp_MainFunction to handle N_As, 
*                N_Bs and N_Cs. 

* Inputs       : CanTpTxChannelId: Channel number of the Transimmit TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_TxChannelCheck
(
    uint8  chnSt,
    CONSTP2CONST(CanTp_RxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) RxSduCfgPtr,
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) TxSduCfgPtr
)
{
    Std_ReturnType ret = E_OK;

    if(chnSt != cCanTpTxState_Idle)
    {                                                      
        if(CANTP_TX_TA_TYPE(TxSduCfgPtr) == CANTP_FUNCTIONAL)
        {

        }
        else if((CANTP_RXNPDU_ID(RxSduCfgPtr) == CANTP_RXFC_NPDU_ID(TxSduCfgPtr)) || \
            (CANTP_UNUSED == CANTP_RXFC_NPDU_ID(TxSduCfgPtr)))
        {
            /*Ignore*/
            ret = E_NOT_OK;
        }
        else
        {

        }

    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxMainFunction

* Description  : This function is called by CanTp_MainFunction to handle N_As, 
*                N_Bs and N_Cs. 

* Inputs       : CanTpTxChannelId: Channel number of the Transimmit TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_StartTransmit
(
	CONSTP2VAR(CanTp_TxStateType,AUTOMATIC,CANTP_CONST) TxStatePtr,
	CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) TxSduCfgPtr
)
{	 
    BufReq_ReturnType ReturnState;
    Std_ReturnType ret = E_OK;
    PduInfoType CanTpTxNPduInfo;
    uint8 FrameType;
    uint8 PadSt;
    uint8 paddlen;
    uint8* TxBuffPtr;

    TxBuffPtr  = TxStatePtr->TxData;

    if(TxStatePtr->DataLength <= TX_SF_DataLength(TxStatePtr)) 
    {	/*(0)1 to 6/7 bytes will be a SingleFrame*/
        FrameType = cCanTp_SF;
        CanTpTxNPduInfo.SduDataPtr = TxBuffPtr + TX_SF_OFFSET(TxStatePtr);								 
        CanTpTxNPduInfo.SduLength = TxStatePtr->DataLength;	
    }
    else 
    {		  
        FrameType = cCanTp_FF;
        CanTpTxNPduInfo.SduDataPtr = TxBuffPtr + TX_FF_OFFSET(TxStatePtr);
        CanTpTxNPduInfo.SduLength = TX_FF_DataLength(TxStatePtr);  
    } 

    TxStatePtr->Timer = CANTP_NAS(TxSduCfgPtr) - ((uint16)1);
    ReturnState = CanTp_CopyTxData(TxStatePtr->CurrentTxSduId,&CanTpTxNPduInfo,NULL_PTR,&(TxStatePtr->RemainTxDataCnt));
    if((BUFREQ_E_NOT_OK == ReturnState) || (BUFREQ_E_OVFL == ReturnState))
    {
        CanTp_NUSDataConfirm(TxStatePtr->CurrentTxSduId,NTFRSLT_E_NO_BUFFER);
        ret = E_NOT_OK;/*for Reset TxChannel only*/
    }
    else if(BUFREQ_E_BUSY == ReturnState)
    {
        TxStatePtr->ChannelState |= cCanTpTxState_ReCopy;
    }
    else
    {
        ret = L_CanTp_TxSduCreatePCI(TxSduCfgPtr,TxStatePtr,TxBuffPtr,FrameType);
        if(E_OK == ret)
        {
            if(FrameType == cCanTp_SF) 
            {	/*(0)1 to 6/7 bytes will be a SingleFrame*/
                TxStatePtr->ChannelState = cCanTpTxState_WaitForSFConf;
                if(CANTP_TX_PADDING_ACTIVATION(TxSduCfgPtr) == CANTP_ON)
                {
                    TxStatePtr->TxNPduInfo.SduLength = CANTP_MAX_FRAME_LENGTH;
                    paddlen = (uint8)(TX_SF_DataLength(TxStatePtr) - TxStatePtr->DataLength);
                    PadSt = (uint8)(CANTP_MAX_FRAME_LENGTH - paddlen);
                    L_CanTp_PaddingData(TxBuffPtr+PadSt,paddlen,CANTP_FILLPATTERN);
                }
                else
                {
                    TxStatePtr->TxNPduInfo.SduLength = (TxStatePtr->DataLength + ((uint16)1) + (uint16)(TX_NPCI_OFFSET(TxStatePtr)));
                }		
            }
            else 
            {
                TxStatePtr->DataLength -= TX_FF_DataLength(TxStatePtr);
                TxStatePtr->ChannelState = cCanTpTxState_WaitForFFConf;
                TxStatePtr->RemainTxDataCnt = TxStatePtr->DataLength;/*TBD*/
                TxStatePtr->TxNPduInfo.SduLength = CANTP_MAX_FRAME_LENGTH; 
            }  
#if(CANTP_TXSDUTRANSMITRETRY == STD_ON)
            if(E_OK != CanTp_CanTransmit(CANTP_TXNPDU_ID(TxSduCfgPtr),&(TxStatePtr->TxNPduInfo)))
            {  
                TxStatePtr->ChannelState |= cCanTpState_Retransmit;
            }
#else
            (void)CanTp_CanTransmit(CANTP_TXNPDU_ID(TxSduCfgPtr),&(TxStatePtr->TxNPduInfo));
#endif

        }
        /*else {}Reset TxChannel */
    }

    return ret;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxMainFunction

* Description  : This function is called by CanTp_MainFunction to handle N_As, 
*                N_Bs and N_Cs. 

* Inputs       : CanTpTxChannelId: Channel number of the Transimmit TpChannel.
*    
* Outputs      : None.
*     
* Limitations  : None.    
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_CFTransmit
(
    CONSTP2VAR(CanTp_TxStateType,AUTOMATIC,CANTP_CONST) TxStatePtr,
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_APPL_CONST,AUTOMATIC) TxSduCfgPtr
)
{
    BufReq_ReturnType ReturnState;
    Std_ReturnType ret = E_OK;
    PduInfoType CanTpTxNPduInfo;
    uint8 FrameType = cCanTp_CF;
    uint8 PadSt;
    uint8* TxBuffPtr;
    PduLengthType cflen;

    TxBuffPtr  = TxStatePtr->TxData;
    cflen = TX_CF_DataLength(TxStatePtr);
    CanTpTxNPduInfo.SduDataPtr = TxBuffPtr + TX_CF_OFFSET(TxStatePtr);

    if(TxStatePtr->DataLength <= cflen)
    {/* the last CF */
        CanTpTxNPduInfo.SduLength = TxStatePtr->DataLength;
        TxStatePtr->ChannelState = cCanTpTxState_WaitForLastCFConf;   
        if(CANTP_TX_PADDING_ACTIVATION(TxSduCfgPtr) == CANTP_ON)
        {    
            TxStatePtr->TxNPduInfo.SduLength = CANTP_MAX_FRAME_LENGTH;
            if(TxStatePtr->DataLength < cflen)
            {  
                PadSt = (uint8)(CANTP_MAX_FRAME_LENGTH - (cflen - TxStatePtr->DataLength));
                L_CanTp_PaddingData(TxBuffPtr+PadSt,cflen - TxStatePtr->DataLength,CANTP_FILLPATTERN);
            }
        }
        else
        {
            TxStatePtr->TxNPduInfo.SduLength = (uint16)(CanTpTxNPduInfo.SduLength + TX_CF_OFFSET(TxStatePtr));
        }
    }
    else
    {
        CanTpTxNPduInfo.SduLength = TX_CF_DataLength(TxStatePtr);
        TxStatePtr->TxNPduInfo.SduLength = CANTP_MAX_FRAME_LENGTH;                                
        TxStatePtr->ChannelState = cCanTpTxState_WaitForCFConf;
    }

    TxStatePtr->Timer = CANTP_NAS(TxSduCfgPtr);						
    ReturnState = CanTp_CopyTxData(TxStatePtr->CurrentTxSduId,&CanTpTxNPduInfo,NULL_PTR,&(TxStatePtr->RemainTxDataCnt));


    if((BUFREQ_E_NOT_OK == ReturnState) || (BUFREQ_E_OVFL == ReturnState))
    {
        CanTp_NUSDataConfirm(TxStatePtr->CurrentTxSduId,NTFRSLT_E_NO_BUFFER);
        ret = E_NOT_OK;/*for Reset TxChannel only*/
    }
    else if(BUFREQ_E_BUSY == ReturnState)
    {
        TxStatePtr->ChannelState |= cCanTpTxState_ReCopy;
    }
    else
    {
        TxStatePtr->DataLength -= cflen;
        (void)L_CanTp_TxSduCreatePCI(TxSduCfgPtr,TxStatePtr,TxBuffPtr,FrameType); 
#if(CANTP_TXSDUTRANSMITRETRY == STD_ON)
        if(E_OK != CanTp_CanTransmit(CANTP_TXNPDU_ID(TxSduCfgPtr),&(TxStatePtr->TxNPduInfo)))
        {
            TxStatePtr->ChannelState |= cCanTpState_Retransmit;
        }
#else
        (void)CanTp_CanTransmit(CANTP_TXNPDU_ID(TxSduCfgPtr),&(TxStatePtr->TxNPduInfo));
#endif
    }

    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_RxSFPdu

* Description  : This function is called by CanTp_RxIndication after successful 
*                reception a SF-PDU.
* 
* Inputs       : RxSduId,CanTpRxChannelId,SFDataBuf,CanDlc
*
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxSFPdu
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{
    BufReq_ReturnType  BufReqResult;
    BufReq_ReturnType  CopyRxDataResult;
    Std_ReturnType TpSFCheckStatus = E_OK;
    Std_ReturnType ret = E_OK;
    uint8 tempoffset;
    uint16 sflen;

    CanTp_RxStateType* pRxChnSt;

    pRxChnSt = pContext->_pRxChnSt;

    if(E_OK != L_CanTp_GetFrameLength(pContext,cCanTp_SF,&sflen))
    {
        TpSFCheckStatus = E_NOT_OK;
    }
    else if(E_OK != L_CanTp_IsPDULenValid(pContext,cCanTp_SF,sflen))
    {
        /*CanTp_NUSDataIndication(RxSduId,NTFRSLT_E_CAN_WRONG_SFDL);*/
        TpSFCheckStatus = E_NOT_OK;
    }
    /*do not need to check Rx TA Type FUNCTIONAL*/   
    else if(CANTP_CHANNEL_MODE(pContext->_pChnMdCfg) == CANTP_MODE_HALF_DUPLEX) 
    {
        TpSFCheckStatus = L_CanTp_TxChannelCheck(pContext->_pTxChnSt->ChannelState,pContext->_pRxSduCfg,pContext->_pTxSduCfg);
    }
    else
    {

    }


    if(TpSFCheckStatus == E_NOT_OK)
    {
        if(pRxChnSt->RxPreCancel == CANTP_RXPRECANCEL_TRUE)
        {
            pRxChnSt->RxPreCancel = CANTP_RXPRECANCEL_FALSE;
            pRxChnSt->RxFormatOffset = pRxChnSt->CurrentRxFormatOffset;
        }
        else
        {

        }
    }
    else
    {
        if(pRxChnSt->RxPreCancel == CANTP_RXPRECANCEL_TRUE)
        {
            tempoffset = pRxChnSt->RxFormatOffset;/*save the RxFormatOffset[CanTpRxChannelId] before init TpChannel*/
            CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_UNEXP_PDU);
            L_CanTp_RxChannelInit(pRxChnSt);
            pRxChnSt->RxFormatOffset = tempoffset;/*restore the offset*/    
        }
        else
        {

        }
        pRxChnSt->CurrentRxSduId = pContext->_sduid;
        pRxChnSt->DataLength = (uint16)sflen;
        pRxChnSt->RxNPduInfo.SduDataPtr = pContext->_pTmpData + RX_SF_OFFSET(pRxChnSt);                              
        pRxChnSt->RxNPduInfo.SduLength = (uint16)sflen;
        pRxChnSt->ChannelState = cCanTpRxState_RxProcessing;

        BufReqResult = CanTp_NUSDataSFIndication(pContext->_sduid,(uint16)sflen,&(pRxChnSt->AvailableBufLength));
        if(BufReqResult == BUFREQ_OK) 
        {
            /*BufReq_ReturnType  CopyRxDataResult;move to up*/
            CopyRxDataResult = CanTp_CopyRxData(pContext->_sduid,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));               

            if(CopyRxDataResult == BUFREQ_OK) 
            {
                CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_OK);
                ret = E_NOT_OK;/*reset rxchannel only*/
            }
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
            else if(CopyRxDataResult == BUFREQ_E_BUSY)
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferSF;
                pRxChnSt->Timer = CANTP_NBR(pContext->_pRxSduCfg);
                L_CanTp_DataCopy(pRxChnSt->RxBufPtr,pRxChnSt->RxNPduInfo.SduDataPtr,sflen);
                pRxChnSt->RxNPduInfo.SduDataPtr = pRxChnSt->RxBufPtr;
            }
            else/*BUFREQ_E_NOT_OK   BUFREQ_E_OVFL*/
            {
                /*abord*/
                CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_NO_BUFFER );
                ret = E_NOT_OK;/*reset rxchannel only*/
            }
#else
            else/*BUFREQ_E_NOT_OK   BUFREQ_E_OVFL  BUFREQ_E_BUSY*/
            {
                /*abord*/
                CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_NO_BUFFER );
                ret = E_NOT_OK;/*reset rxchannel only*/
            }
#endif
            /*ReturnState = E_OK;*/
        }
#if(CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)
        else if(BufReqResult == BUFREQ_E_BUSY)
        {
            pRxChnSt->ChannelState = cCanTpRxState_WaitForSFRequestBuffer;
            pRxChnSt->Timer = CANTP_NBR(pContext->_pRxSduCfg);
            L_CanTp_DataCopy(pRxChnSt->RxBufPtr,pRxChnSt->RxNPduInfo.SduDataPtr,sflen);
            pRxChnSt->RxNPduInfo.SduDataPtr = pRxChnSt->RxBufPtr;
        }       
        else/*BUFREQ_E_NOT_OK   BUFREQ_E_OVFL*/
        {
            /*abord*/
            ret = E_NOT_OK;/*reset rxchannel only*/
        }
#else  
        else/*BUFREQ_E_NOT_OK   BUFREQ_E_OVFL   BUFREQ_E_BUSY*/
        {
            /*abord*/
            ret = E_NOT_OK;/*reset rxchannel only*/
        }
#endif
    }
    /*return ReturnState;*/
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: _CanTp_RxFFPdu

* Description  : This function is called by CanTp_RxIndication after successful 
*                reception a FF-PDU.
* 
* Inputs       : RxSduId,CanTpRxChannelId,FFDataBuf,CanDlc
*
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxFFPdu
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{
    BufReq_ReturnType  BufReqResult;
    Std_ReturnType TpFFCheckStatus = E_OK;
    Std_ReturnType ret = E_OK;
    uint8 tempoffset;
    PduLengthType fflen = 0;
    CanTp_RxStateType* pRxChnSt;

    pRxChnSt = pContext->_pRxChnSt;

    if(CANTP_RX_TA_TYPE(pContext->_pRxSduCfg) == CANTP_FUNCTIONAL)/*Target Addressing Format*/
    {
        TpFFCheckStatus = E_NOT_OK;
    }
    else if(E_OK != L_CanTp_GetFrameLength(pContext,cCanTp_FF,&fflen))
    {
        TpFFCheckStatus = E_NOT_OK;
    }
    else if(E_OK != L_CanTp_IsPDULenValid(pContext,cCanTp_FF,fflen))
    {
        /*CanTp_NUSDataIndication(RxSduId,NTFRSLT_E_CAN_WRONG_SFDL);*/
        TpFFCheckStatus = E_NOT_OK;
    }
    else if(CANTP_CHANNEL_MODE(pContext->_pChnMdCfg) == CANTP_MODE_HALF_DUPLEX) 
    {
        TpFFCheckStatus = L_CanTp_TxChannelCheck(pContext->_pTxChnSt->ChannelState,pContext->_pRxSduCfg,pContext->_pTxSduCfg);
    }
    else
    {
    
    }

    if(TpFFCheckStatus == E_NOT_OK)
    {
        if(pRxChnSt->RxPreCancel == CANTP_RXPRECANCEL_TRUE)
        {
            pRxChnSt->RxPreCancel = CANTP_RXPRECANCEL_FALSE;
            pRxChnSt->RxFormatOffset = pRxChnSt->CurrentRxFormatOffset;
        }
        else
        {

        }
    }
    else
    {        

        if(pRxChnSt->RxPreCancel == CANTP_RXPRECANCEL_TRUE)
        {
            tempoffset = pRxChnSt->RxFormatOffset;/*save the RxFormatOffset[CanTpRxChannelId] before init TpChannel*/
            CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_UNEXP_PDU);
            L_CanTp_RxChannelInit(pRxChnSt);
            pRxChnSt->RxFormatOffset = tempoffset;/*restore the offset*/
        }
        else
        {

        }
        pRxChnSt->CurrentRxSduId = pContext->_sduid;                         
        pRxChnSt->DataLength = fflen;
        pRxChnSt->ExpectedSN = cCanTpSNStartValue;
        pRxChnSt->RxNPduInfo.SduDataPtr = pContext->_pTmpData + RX_FF_OFFSET(pRxChnSt);/*(uint8*)(&FFDataBuf[RX_FF_OFFSET(CanTpRxChannelId)]);*/
        pRxChnSt->RxNPduInfo.SduLength = RX_FF_DataLength(pRxChnSt);
        pRxChnSt->BlockSize = CANTP_BS(pContext->_pRxSduCfg);
        pRxChnSt->STMin = CANTP_STMIN(pContext->_pRxSduCfg);
        /*_pRxChnSt->MinBuffSize = (RX_CF_DataLength(_pRxChnSt)) * (_pRxChnSt->BlockSize);*/
        pRxChnSt->ChannelState = cCanTpRxState_RxProcessing;
        BufReqResult = CanTp_NUSDataFFIndication(pContext->_sduid,fflen,&(pRxChnSt->AvailableBufLength));
        if(BufReqResult == BUFREQ_OK)
        {  
            /*BufReq_ReturnType  BufReqResultTemp;move to up equal to BufReqResult*/
            if(((0 == CANTP_BS(pContext->_pRxSduCfg))&&(pRxChnSt->AvailableBufLength < pRxChnSt->DataLength))||\
                (pRxChnSt->AvailableBufLength < RX_FF_DataLength(pRxChnSt)))
            {
                pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                pRxChnSt->Timer = 0; /*Transmit FC in the task immediately*/ 
            }
            else
            {  
                pRxChnSt->BlockSizeCounter = pRxChnSt->BlockSize;
                pRxChnSt->STMin = CANTP_STMIN(pContext->_pRxSduCfg);
                BufReqResult = CanTp_CopyRxData(pContext->_sduid,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));               

                if(BufReqResult == BUFREQ_OK)
                {
                    pRxChnSt->DataLength -= RX_FF_DataLength(pRxChnSt);
                    (void)L_CanTp_GetRxMinBufferNextBlk(pRxChnSt);
                    (void)L_CanTp_MinBufferAccess(pContext,TRUE);
                }  
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
                else if(BufReqResult == BUFREQ_E_BUSY)/*BUFREQ_E_BUSY*/
                { 
                    pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferFF;
                    pRxChnSt->Timer = CANTP_NBR(pContext->_pRxSduCfg);
                    pRxChnSt->WFTCounter = 0;
                    
                    L_CanTp_DataCopy(pRxChnSt->RxBufPtr,pRxChnSt->RxNPduInfo.SduDataPtr,pRxChnSt->RxNPduInfo.SduLength);
                    pRxChnSt->RxNPduInfo.SduDataPtr = pRxChnSt->RxBufPtr;
                } 
#endif
                else/*BUFREQ_E_OVFL BUFREQ_E_NOT_OK; #if(CANTP_AUTOSAR42 != STD_ON)BUFREQ_E_BUSY*/
                {    
                    /*abord*/
                    pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                    pRxChnSt->Timer = 0; /*Transmit FC in the task immediately*/ 
                }

            }

        }
#if(CANTP_AUTOSAREXT_SORRETBUSY == STD_ON)
        else if(BufReqResult == BUFREQ_E_BUSY)/*BUFREQ_E_BUSY*/
        { 
            pRxChnSt->ChannelState = cCanTpRxState_WaitForFFRequestBuffer;
            pRxChnSt->Timer = CANTP_NBR(pContext->_pRxSduCfg);
            pRxChnSt->WFTCounter = 0;
            L_CanTp_DataCopy(pRxChnSt->RxBufPtr,pRxChnSt->RxNPduInfo.SduDataPtr,pRxChnSt->RxNPduInfo.SduLength);
            pRxChnSt->RxNPduInfo.SduDataPtr = pRxChnSt->RxBufPtr;
        }      
#endif	
        /**************************************************************/
        else if(BufReqResult==BUFREQ_E_NOT_OK)
        {   
            /*abord*/
            ret = E_NOT_OK;
        }	
        /*************************************************************/		
        else/*BUFREQ_E_OVFL or (#if(CANTP_AUTOSAR42 != STD_ON)) BUFREQ_E_BUSY*/
        {
            pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrunFFReqBuff;
            pRxChnSt->Timer = 0; /*Transmit FC in the task immediately*/
        }
    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: _CanTp_RxFFPdu

* Description  : This function is called by CanTp_RxIndication after successful 
*                reception a FF-PDU.
* 
* Inputs       : RxSduId,CanTpRxChannelId,FFDataBuf,CanDlc
*
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_GoingCFProcess
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext,
    BufReq_ReturnType  BufReqResult
)
{
    Std_ReturnType ret = E_OK;
    CanTp_RxStateType* pRxChnSt;
    pRxChnSt = pContext->_pRxChnSt;
    if(BufReqResult == BUFREQ_OK)
    {
        pRxChnSt->DataLength -= RX_CF_DataLength(pRxChnSt);
    }
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
    else if(BufReqResult == BUFREQ_E_BUSY)
    {    
        pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferGoingCF;
        pRxChnSt->Timer = (uint16)(CANTP_STMIN(pContext->_pRxSduCfg) / CANTP_MAIN_FUNCTION_PERIOD); 
        L_CanTp_DataCopy(pRxChnSt->RxBufPtr,pRxChnSt->RxNPduInfo.SduDataPtr,pRxChnSt->RxNPduInfo.SduLength);
        pRxChnSt->RxNPduInfo.SduDataPtr = pRxChnSt->RxBufPtr;
                          
        if(pRxChnSt->Timer == 0)
        {
            CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_NO_BUFFER);
            ret = E_NOT_OK;/*reset rxchannel only*/
        }
        else
        {
    
        }
    }
#endif
    else /*BUFREQ_E_NOT_OK  BUFREQ_E_OVFL;#if(CANTP_AUTOSAR42 != STD_ON) BUFREQ_E_BUSY*/
    {   /*abort */
        CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_NO_BUFFER);
        ret = E_NOT_OK;/*reset rxchannel only*/
    }

    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: _CanTp_RxFFPdu

* Description  : This function is called by CanTp_RxIndication after successful 
*                reception a FF-PDU.
* 
* Inputs       : RxSduId,CanTpRxChannelId,FFDataBuf,CanDlc
*
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_IsLastCF
(
    CONSTP2CONST(CanTp_RxStateType,CANTP_APPL_DATA,AUTOMATIC) pRxChnSt
)
{
    Std_ReturnType ret = E_OK;
    if(pRxChnSt->DataLength > RX_CF_DataLength(pRxChnSt))/*not the last CF*/
    {
        ret = E_NOT_OK;
    }

    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: _CanTp_RxFFPdu

* Description  : This function is called by CanTp_RxIndication after successful 
*                reception a FF-PDU.
* 
* Inputs       : RxSduId,CanTpRxChannelId,FFDataBuf,CanDlc
*
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_GetFrameLength
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext,
    uint8   FrameType,
    uint16* frameLen
)
{
    Std_ReturnType ret = E_OK;
    PduLengthType  len = 0;
    CanTp_RxStateType* pRxChnSt;
    /*CanTp_TxStateType* _pTxChnSt;*/
    uint8 pci;

    pRxChnSt = pContext->_pRxChnSt;
    /*_pTxChnSt = pContext->_pTxChnSt;*/

    switch(FrameType)
    {
        case cCanTp_SF:
            pci = *(pContext->_pTmpData + RX_NPCI_OFFSET(pRxChnSt));
            /*SF Data Length*/
            len = (uint16)(pci & cCanTp_DLMaskSF);
        break;
        case cCanTp_FF:
            
            len = (PduLengthType)(*(pContext->_pTmpData + RX_DL_OFFSET(pRxChnSt)));
            len |= (PduLengthType)(((PduLengthType)((*(pContext->_pTmpData + RX_NPCI_OFFSET(pRxChnSt)))& cCanTp_DLMaskFF))<< CANTP_BITS8);

        break;

        case cCanTp_CF:

            if(E_OK == L_CanTp_IsLastCF(pRxChnSt))
            { /*the last CF*/
                len = pRxChnSt->DataLength;
            }
            else
            { /*not the last CF*/
                len = (uint16)(RX_CF_DataLength(pRxChnSt));
            }

        break;

        case cCanTp_FC:
           len = CANTP_FC_DataLength;
        break;

        default:
            ret = E_NOT_OK;
        break;
    }
    *frameLen = len;
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: _CanTp_RxFFPdu

* Description  : This function is called by CanTp_RxIndication after successful 
*                reception a FF-PDU.
* 
* Inputs       : RxSduId,CanTpRxChannelId,FFDataBuf,CanDlc
*
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_IsPDULenValid
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext,
    uint8 FrameType,
    uint16 frameLen
)
{
    Std_ReturnType ret = E_OK;
    PduLengthType  len;
    CanTp_RxStateType* pRxChnSt;
    CanTp_TxStateType* pTxChnSt;

    pRxChnSt = pContext->_pRxChnSt;
    pTxChnSt = pContext->_pTxChnSt;

    switch(FrameType)
    {
        case cCanTp_SF:

            /*check SF Length*/
            if((frameLen > RX_SF_DataLength(pRxChnSt))||(frameLen == 0))
            {
                /*CanTp_NUSDataIndication(RxSduId,NTFRSLT_E_CAN_WRONG_SFDL);*/
                ret = E_NOT_OK;
            }
            else if(CANTP_RX_PADDING_ACTIVATION(pContext->_pRxSduCfg) == STD_ON)
            {  
                /*check CAN DLC*/
                if(pContext->_candlc < CANTP_MAX_FRAME_LENGTH)
                {
                    /*CAN data link error,abort CAN frame*/
                    ret = E_NOT_OK;
                }
            }
            else/*padding off*/
            {    
                /*check CAN DLC and SF Length*/
                if((pContext->_candlc) < (frameLen + RX_SF_OFFSET(pRxChnSt)))
                {
                    /*CAN data link error,abort CAN frame*/
                    ret = E_NOT_OK;
                }
            }
        break;
        case cCanTp_FF:
            /*check CAN DLC*/
            if(pContext->_candlc < CANTP_MAX_FRAME_LENGTH)
            {
                /*Ignore*/
                ret = E_NOT_OK;
            }
            /*check FF Length*/
            else if(frameLen <= RX_SF_DataLength(pRxChnSt))
            {
                ret = E_NOT_OK;
            }
            else
            {

            }
             
        break;

        case cCanTp_CF:

            if(CANTP_RX_PADDING_ACTIVATION(pContext->_pRxSduCfg) == STD_ON)
            {  
                /*check CAN DLC*/
                if(pContext->_candlc < CANTP_MAX_FRAME_LENGTH)
                {
                    /*CAN data link error,abort CAN frame*/
                    ret = E_NOT_OK;
                }
            }
            else/*padding off*/
            {
                len = pRxChnSt->DataLength;

                if(len <= RX_CF_DataLength(pRxChnSt))/*the last CF*/
                {
                    if(pContext->_candlc < (len + RX_CF_OFFSET(pRxChnSt)))
                    {
                        ret = E_NOT_OK;
                    }
                }
                /*not the last CF ,check CAN DLC */
                else if(pContext->_candlc < CANTP_MAX_FRAME_LENGTH)
                {
                    ret = E_NOT_OK;
                }
                else if(pContext->_candlc < (len + RX_CF_OFFSET(pRxChnSt)))
                {   
                    if(pContext->_candlc < CANTP_MAX_FRAME_LENGTH)
                    {
                        /*CAN data link error,abort CAN frame*/
                        ret = E_NOT_OK;
                    }
                
                }
                else
                {
                
                }
            }
        
        break;

        case cCanTp_FC:
            if(CANTP_RX_PADDING_ACTIVATION(pContext->_pRxSduCfg) == STD_ON)
            {  
                /*check CAN DLC*/
                if(pContext->_candlc < CANTP_MAX_FRAME_LENGTH)
                {
                    /*CAN data link error,abort CAN frame*/
                    ret = E_NOT_OK;
                }
            }
            /*padding off*/
            else if(pContext->_candlc < RX_FC_CAN_DataLength(pTxChnSt))
            {
                /*CAN data link error,abort CAN frame*/
                ret = E_NOT_OK;
            }
            else
            {

            }
        break;

        default:
            ret = E_NOT_OK;
        break;
    }

    return ret;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_RxCFPdu

* Description  : This function is called by CanTp_RxIndication after successful 
*                reception a CF-PDU.
* 
* Inputs       : RxSduId,CanTpRxChannelId,CFDataBuf,CanDlc
*
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxCFPdu
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{
    BufReq_ReturnType  BufReqResult;
    /*PduLengthType LastCFLength = 0;*/
    Std_ReturnType ret = E_OK;
    uint8  cfpci;
    uint16 cflen;
    CanTp_RxStateType* pRxChnSt;

    pRxChnSt = pContext->_pRxChnSt;

    cfpci = *(pContext->_pTmpData + RX_NPCI_OFFSET(pRxChnSt));

    if(pRxChnSt->ChannelState != cCanTpRxState_WaitCF)
    {   /*may be the current state is cCanTpRxState_WaitForTxFC.. or others*/
        /*Ignore*/
        /*do not inform upper layer */
    }
    else if((cfpci & cCanTp_SNMask) != pRxChnSt->ExpectedSN)
    {
        CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_WRONG_SN);
        ret = E_NOT_OK;/*reset rxchannel only*/
    }
    else if(E_OK != L_CanTp_GetFrameLength(pContext,cCanTp_CF,&cflen))
    {
        CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_CAN_WRONG_CFDL);
        ret = E_NOT_OK;/*reset rxchannel only*/
    }
    else if(E_OK != L_CanTp_IsPDULenValid(pContext,cCanTp_CF,cflen))
    {
        CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_CAN_WRONG_CFDL);
        ret = E_NOT_OK;/*reset rxchannel only*/
    }
    /* do not need to check  HALF_DUPLEX or FULL_DUPLEX ?*/
    /*
    else if(CANTP_CHANNEL_MODE(pContext->_pChnMdCfg) == CANTP_MODE_HALF_DUPLEX) 
    {
        TpCFCheckStatus = _CanTp_TxChannelCheck(pContext->_pTxChnSt->ChannelState,pContext->_pRxSduCfg,pContext->_pTxSduCfg);
    }
    */
    else
    {
        pRxChnSt->RxNPduInfo.SduDataPtr = pContext->_pTmpData + RX_CF_OFFSET(pRxChnSt);
        pRxChnSt->RxNPduInfo.SduLength = cflen;

        BufReqResult = CanTp_CopyRxData(pContext->_sduid,&(pRxChnSt->RxNPduInfo),&(pRxChnSt->AvailableBufLength));

        if(E_OK == L_CanTp_IsLastCF(pRxChnSt))/*the last CF*/
        {
            if(BufReqResult == BUFREQ_OK)
            {  
                CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_OK); 
                ret = E_NOT_OK;/*reset rxchannel only*/
            }
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON) 
            else if(BufReqResult == BUFREQ_E_BUSY)/* CANTP268 */
            { 
                pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferLastCF;
                pRxChnSt->Timer = CANTP_NBR(pContext->_pRxSduCfg);
                L_CanTp_DataCopy(pRxChnSt->RxBufPtr,pRxChnSt->RxNPduInfo.SduDataPtr,cflen);
                pRxChnSt->RxNPduInfo.SduDataPtr = pRxChnSt->RxBufPtr;     
            } 
#endif
            else/*BUFREQ_E_NOT_OK  BUFREQ_E_OVFL;#if(CANTP_AUTOSAR42 != STD_ON) BUFREQ_E_BUSY*/
            {
                CanTp_NUSDataIndication(pContext->_sduid,NTFRSLT_E_NO_BUFFER);
                ret = E_NOT_OK;/*reset rxchannel only*/
            }
        }
        else /*is not last CF*/
        {
            pRxChnSt->ChannelState = cCanTpRxState_WaitCF;                
            pRxChnSt->Timer = CANTP_NCR(pContext->_pRxSduCfg);                
            /*process SN */
            if(pRxChnSt->ExpectedSN < cCanTp_SNMask)
            {
                pRxChnSt->ExpectedSN++;
            }
            else
            {
                pRxChnSt->ExpectedSN = 0;
            }
            /*check BS */
            if(pRxChnSt->BlockSizeCounter != 0)
            {
                pRxChnSt->BlockSizeCounter--;
                if(pRxChnSt->BlockSizeCounter == 0)/*is the last CF of block*/
                {
                    pRxChnSt->BlockSizeCounter = pRxChnSt->BlockSize;

                    if(BufReqResult == BUFREQ_OK)
                    {     
                        pRxChnSt->DataLength -= RX_CF_DataLength(pRxChnSt);
                        (void)L_CanTp_GetRxMinBufferNextBlk(pRxChnSt);
                        (void)L_CanTp_MinBufferAccess(pContext,TRUE);
                    } 
#if(CANTP_AUTOSAREXT_COPRXRETBUSY == STD_ON)
                    else if(BufReqResult==BUFREQ_E_BUSY)/* CANTP268 */
                    { 
                        pRxChnSt->ChannelState = cCanTpRxState_WaitForRxBufferLastCFBlock;
                        pRxChnSt->Timer = CANTP_NBR(pContext->_pRxSduCfg);
                        pRxChnSt->WFTCounter = 0;
                        L_CanTp_DataCopy(pRxChnSt->RxBufPtr,pRxChnSt->RxNPduInfo.SduDataPtr,pRxChnSt->RxNPduInfo.SduLength);
                        pRxChnSt->RxNPduInfo.SduDataPtr = pRxChnSt->RxBufPtr;
                    }
#endif
                    else/*BUFREQ_E_NOT_OK BUFREQ_E_OVFL;#if(CANTP_AUTOSAR42 != STD_ON) BUFREQ_E_BUSY*/
                    {
                        pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
                        pRxChnSt->Timer = (uint16)1; /*Transmit FC in the task */   
                    }
                }
                /*CANTP271: If the PduR_CanTpCopyRxData() returns BUFREQ_E_NOT_OK or
                BUFREQ_E_OVFL or BUFREQ_E_BUSY after reception of a Consecutive Frame in a
                block the CanTp shall abort the reception of N-SDU.*/

                else/*is NOT the last CF of block*/
                {
                    ret = L_CanTp_GoingCFProcess(pContext,BufReqResult);
                }
            }
            else/*BS=0*/
            {
                ret = L_CanTp_GoingCFProcess(pContext,BufReqResult);
            }        
        }
    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: _CanTp_RxFCPdu

* Description  : This function is called by CanTp_RxIndication after successful 
*                reception a FC-PDU.
* 
* Inputs       : RxSduId,CanTpRxChannelId,FCDataBuf,CanDlc
*
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_RxFCPdu
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{ 
    Std_ReturnType TpFCCheckStatus = E_OK;

    Std_ReturnType ret = E_OK;
    uint8 fcpciFS;
    uint8 fcpciBS;
    uint8 fcpciSTmin;
    CanTp_TxStateType* pTxChnSt;

    pTxChnSt = pContext->_pTxChnSt;
    fcpciFS = *(pContext->_pTmpData + TX_NPCI_OFFSET(pTxChnSt));
    fcpciFS &= cCanTp_FSMask;    

    fcpciBS    = *(pContext->_pTmpData + TX_BS_OFFSET(pTxChnSt));
    fcpciSTmin = *(pContext->_pTmpData + TX_STMIN_OFFSET(pTxChnSt));

    if(E_OK != L_CanTp_IsPDULenValid(pContext,cCanTp_FC,RX_FC_CAN_DataLength(pTxChnSt)))
    {
        /*CanTp_NUSDataIndication(RxSduId,NTFRSLT_E_CAN_WRONG_SFDL);*/
        TpFCCheckStatus = E_NOT_OK;
    }
    else if((pTxChnSt->ChannelState) != cCanTpTxState_WaitFC)
    {
        /*FC NotExpected,Ignore*/
        TpFCCheckStatus = E_NOT_OK;
    }
    else if(CANTP_TX_TA_TYPE(pContext->_pTxSduCfg) == CANTP_FUNCTIONAL)/*Target Addressing Format*/
    {
        TpFCCheckStatus = E_NOT_OK;
    }
    else if(CANTP_CHANNEL_MODE(pContext->_pChnMdCfg) == CANTP_MODE_HALF_DUPLEX) 
    {
        TpFCCheckStatus = L_CanTp_RxChannelCheck(pContext->_pRxChnSt->ChannelState,pContext->_pRxSduCfg,pContext->_pTxSduCfg);
    }
    else
    {

    }

    if(TpFCCheckStatus == E_OK)
    {
        switch(fcpciFS)
        {
            case  cCanTp_FC_FS_CTS:
            {
                pTxChnSt->ChannelState = cCanTpTxState_WaitForTpTxCF;                                     
                pTxChnSt->BlockSizeCounter = fcpciBS;
                if((fcpciSTmin & STMINABSOLUTEMASK) != 0)/*== 0x80)*/
                {   /*80 - FF*/
#if(CANTP_STMIN_RANGEF1_F9 == CANTP_STMIN_RANGE_VALID)
                    if((fcpciSTmin >= STMINRELATIVEMIN)&&(fcpciSTmin <= STMINRELATIVEMAX)) /*F1 - F9: STmin range: 100us - 900us*/
                    {/*F1 - F9 100 ¦Ìs - 900 ¦Ìs*/
                        pTxChnSt->STMin = (uint8)1;
                    }
                    else 
                    { 
#endif/*80 - F0,FA - FF Reserved*/
                        pTxChnSt->STMin = (uint8)(((uint16)STMINABSOLUTEMASK) / CANTP_MAIN_FUNCTION_PERIOD); /* Max STmin time */
                        
                        if((((uint8)STMINABSOLUTEMASK) % ((uint8)CANTP_MAIN_FUNCTION_PERIOD)) != 0u)
                        {
                            pTxChnSt->STMin++;
                        }
 
#if(CANTP_STMIN_RANGEF1_F9 == CANTP_STMIN_RANGE_VALID)  
                    }
#endif                   
                }
                else /*00 - 7F,STmin range:0 ms -127 ms*/
                {
                    pTxChnSt->STMin = (uint8)(fcpciSTmin / CANTP_MAIN_FUNCTION_PERIOD)+(uint8)1;

                    /*if((FCDataBuf[TX_STMIN_OFFSET(CanTpTxChannelId)] % CANTP_MAIN_FUNCTION_PERIOD) != 0)
                    {
                        CanTp_TxState[CanTpTxChannelId].STMin++;
                    }
                    else
                    {
                        
                    }*/
                }
                /*CanTp_TxState[CanTpTxChannelId].Timer = CanTp_TxState[CanTpTxChannelId].STMin;*/
                pTxChnSt->Timer = 0;
                /*Transmit CF in as fast as possible */

                /*ReturnState = E_OK;*/
            }
            break;
            
            case  cCanTp_FC_FS_Wait:
            {
                pTxChnSt->ChannelState = cCanTpTxState_WaitFC;
                pTxChnSt->Timer = CANTP_NBS(pContext->_pTxSduCfg);
                /*ReturnState = E_OK;*/        
            }
            break;
            
            case  cCanTp_FC_FS_Overrun:
            {
                CanTp_NUSDataConfirm(pContext->_sduid,NTFRSLT_E_NO_BUFFER);
                ret = E_NOT_OK;
            }
            break;

            default:
            {
                CanTp_NUSDataConfirm(pContext->_sduid,NTFRSLT_E_INVALID_FS );
                ret = E_NOT_OK;
            }
            break;
        }
    }
    /*return ReturnState;  */
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_AssembleFC

* Description  : After receiving FF , this function is called to assemble FC .

* Inputs       : CanTpRxChannelId,FlowStatus
*    
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
#if(CANTP_RXSDUTRANSMITRETRY == STD_ON)
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_ReTransmitFC
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{
    PduInfoType CanTpTxFCPduInfo;
    Std_ReturnType CanIfTxRet;
    uint8* FCBuff;
    CanTp_RxStateType* pRxChnSt;

    pRxChnSt = pContext->_pRxChnSt;
    FCBuff = pRxChnSt->TxFCPtr;
    CanTpTxFCPduInfo.SduDataPtr = FCBuff; 
    
    if(CANTP_RX_PADDING_ACTIVATION(pContext->_pRxSduCfg) == CANTP_ON)
    {          
        CanTpTxFCPduInfo.SduLength = CANTP_MAX_FRAME_LENGTH;
    }
    else
    {       
        CanTpTxFCPduInfo.SduLength = TX_FC_CAN_DataLength(pRxChnSt);
    }

    CanIfTxRet = CanTp_CanTransmit(CANTP_TXFC_NPDU_ID(pContext->_pRxSduCfg),&CanTpTxFCPduInfo);
    if(E_OK == CanIfTxRet)
    {
        pRxChnSt->ChannelState ^= cCanTpState_Retransmit;/*Clear Retransmit Flag */ 
    }
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_AssembleFC

* Description  : After receiving FF , this function is called to assemble FC .

* Inputs       : CanTpRxChannelId,FlowStatus
*    
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_AssembleFC
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext
)
{
    PduInfoType CanTpTxFCPduInfo;
#if(CANTP_RXSDUTRANSMITRETRY == STD_ON)
    Std_ReturnType CanIfTxRet;
#endif
    uint8* FCBuff;
    CanTp_RxStateType* pRxChnSt;

    pRxChnSt = pContext->_pRxChnSt;

    FCBuff = pRxChnSt->TxFCPtr;
    if(CANTP_RX_ADDRESSING_FORMAT(pContext->_pRxSduCfg) == CANTP_EXTENDED)
    {
        *(FCBuff + EXT_OFFSET) = CANTP_RX_NTA(pContext->_pRxSduCfg);
    }
    else if(CANTP_RX_ADDRESSING_FORMAT(pContext->_pRxSduCfg) == CANTP_MIXED)
    {
        *(FCBuff + MIX_OFFSET) = CANTP_RX_NAE(pContext->_pRxSduCfg);
    }
    else
    {     
    
    }
    
    *(FCBuff + RX_NPCI_OFFSET(pRxChnSt)) = (uint8)(cCanTp_FC|pRxChnSt->FlowStatus);
    *(FCBuff + RX_BS_OFFSET(pRxChnSt)) = pRxChnSt->BlockSize;
    *(FCBuff + RX_STMIN_OFFSET(pRxChnSt)) = pRxChnSt->STMin;
    CanTpTxFCPduInfo.SduDataPtr = FCBuff;    
    
    if(CANTP_RX_PADDING_ACTIVATION(pContext->_pRxSduCfg) == CANTP_ON)
    {   
        L_CanTp_PaddingData(FCBuff + (RX_STMIN_OFFSET(pRxChnSt) + 1u),(uint16)(CANTP_MAX_FRAME_LENGTH - RX_STMIN_OFFSET(pRxChnSt) - 1u),CANTP_FILLPATTERN);
        CanTpTxFCPduInfo.SduLength = CANTP_MAX_FRAME_LENGTH;
    }
    else
    {       
        CanTpTxFCPduInfo.SduLength = TX_FC_CAN_DataLength(pRxChnSt);
    }    
#if(CANTP_RXSDUTRANSMITRETRY == STD_ON)
    CanIfTxRet = CanTp_CanTransmit(CANTP_TXFC_NPDU_ID(pContext->_pRxSduCfg),&CanTpTxFCPduInfo);
    if(E_OK != CanIfTxRet)
    {
        pRxChnSt->ChannelState |= cCanTpState_Retransmit;
    }
#else
    (void)CanTp_CanTransmit(CANTP_TXFC_NPDU_ID(pContext->_pRxSduCfg),&CanTpTxFCPduInfo);
#endif
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_DataCopy

* Description  : This function is Called by CanTp for coping data.
*    
* Inputs       : None.
*        
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_DataCopy
( 
    CONSTP2VAR(uint8,AUTOMATIC,CANTP_CONST) dest,
    CONSTP2CONST(uint8,CANTP_APPL_DATA, AUTOMATIC) src,
    CONST(uint16,CANTP_CONST) cnt   
)
{
    uint16 i;
    for(i = 0;i < cnt;i++)
    {
        *(dest + i) = *(src + i);
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: _CanTp_PaddingData

* Description  : This function is Called by CanTp for padding data.
*    
* Inputs       : None.
*        
* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_PaddingData
( 
    CONSTP2VAR(uint8,AUTOMATIC,CANTP_CONST) dest,
    CONST(uint16, CANTP_CONST) cnt,
    CONST(uint8, CANTP_CONST) value
)
{
    uint16 i;
    for(i = 0;i < cnt;i++)
    {
    	*(dest + i) = value;
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_ChannelInit

* Description  : This function initializes the CanTp module 
*   
* Inputs       : tpChannelType: Tx or Rx Tp Channel,range:CANTP_RX_CHANNEL and
*                               CANTP_TX_CHANNEL.
*                tpChannel    : The init Tp Channel number.

* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_IsStateON
(
    void
)
{
    Std_ReturnType ret;

    ret = E_OK;
    if(Admin.InternalState != CANTP_ON)
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_TxChannelInit

* Description  : This function initializes the CanTp module 
*   
* Inputs       : tpChannelType: Tx or Rx Tp Channel,range:CANTP_RX_CHANNEL and
*                               CANTP_TX_CHANNEL.
*                tpChannel    : The init Tp Channel number.

* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_TxChannelInit
(
    CONSTP2VAR(CanTp_TxStateType,CANTP_APPL_DATA,AUTOMATIC) TxStatePtr
)
{
    CanTp_CanInterruptDisable();

    TxStatePtr->TxFormatOffset = 0;  
    TxStatePtr->CurrentTxSduId = CANTP_UNUSED;

    /* activation status */
    TxStatePtr->Timer = 0;
    TxStatePtr->ChannelState = cCanTpTxState_Idle;
    TxStatePtr->TxNPduInfo.SduDataPtr = TxStatePtr->TxData;
    TxStatePtr->TxNPduInfo.SduLength = 0;
    /* Lengths */
    TxStatePtr->DataLength = 0;
    TxStatePtr->RemainTxDataCnt = 0;
    /* actual values */
    TxStatePtr->BlockSizeCounter = 0;
    TxStatePtr->STMin = 0;
    /* Bittypes */
    TxStatePtr->SeqNumber = cCanTpSNStartValue;
    
    CanTp_CanInterruptRestore();
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanTp_RxChannelInit

* Description  : This function initializes the CanTp module 
*   
* Inputs       : tpChannelType: Tx or Rx Tp Channel,range:CANTP_RX_CHANNEL and
*                               CANTP_TX_CHANNEL.
*                tpChannel    : The init Tp Channel number.

* Outputs      : None.
*   
* Limitations  : None.
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,CANTP_PRIVATE_CODE) L_CanTp_RxChannelInit
(
    CONSTP2VAR(CanTp_RxStateType,CANTP_APPL_DATA,AUTOMATIC) RxStatePtr
)
{
    /***** RX *****************************************************************/    
    CanTp_CanInterruptDisable();
   
    
    RxStatePtr->RxFormatOffset = 0;
    
    RxStatePtr->CurrentRxSduId = CANTP_UNUSED;
    /* activation status */
    RxStatePtr->Timer = 0;
    RxStatePtr->ChannelState = cCanTpRxState_Idle;
    RxStatePtr->RxNPduInfo.SduDataPtr = RxStatePtr->RxData;
    RxStatePtr->RxNPduInfo.SduLength = 0;
    /* Lengths */
    RxStatePtr->DataLength = 0;
    /* buffer admin */
    RxStatePtr->AvailableBufLength = 0;
    RxStatePtr->WFTCounter = 0;
    /* actual values */
    RxStatePtr->BlockSizeCounter = 0;
    RxStatePtr->BlockSize = 0;
    RxStatePtr->STMin = 0;
    /* Bittypes */
    RxStatePtr->ExpectedSN = 0;
    RxStatePtr->RxPreCancel = 0;
    RxStatePtr->RxBufPtr = RxStatePtr->RxData;
    RxStatePtr->TxFCPtr  = RxStatePtr->FCData;

    CanTp_CanInterruptRestore();
}
STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_GetRxMinBufferNextBlk
(
    CanTp_RxStateType* pRxChnSt
)
{
    Std_ReturnType ret = E_OK;
    PduLengthType minlen;
    
    do
    {
        if(pRxChnSt->BlockSize == 0)
        {
            minlen = pRxChnSt->DataLength;
            break;
        }
        minlen = (uint16)((RX_CF_DataLength(pRxChnSt)) * (pRxChnSt->BlockSize));
        minlen = (minlen > pRxChnSt->DataLength)?(pRxChnSt->DataLength):(minlen);
    }while(0);

    pRxChnSt->MinBuffSize = minlen;
    
    return ret;
}

STATIC FUNC(Std_ReturnType,CANTP_PRIVATE_CODE) L_CanTp_MinBufferAccess
(
    CONSTP2CONST(CanTp_ContextType,CANTP_APPL_DATA,AUTOMATIC) pContext,
    boolean SetBr
)
{
    Std_ReturnType     ret = E_OK;
    CanTp_RxStateType* pRxChnSt;
    boolean brf;
	brf = SetBr;
#if(CANTP_AUTOSAREXT_WAITENOUGHBUFF != STD_ON)
	(void)brf;
#endif
    pRxChnSt = pContext->_pRxChnSt;
    if(pRxChnSt->AvailableBufLength >= pRxChnSt->MinBuffSize)
    {
        pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFC;
        pRxChnSt->Timer = 0; /*Transmit FC in the task immediately*/
    }
#if(CANTP_AUTOSAREXT_WAITENOUGHBUFF == STD_ON)
    else
    {
        pRxChnSt->ChannelState = cCanTpRxState_WaitEnoughBuffer;
        pRxChnSt->WFTCounter = 0;
        if(TRUE == brf)
        {
            pRxChnSt->Timer = CANTP_NBR(pContext->_pRxSduCfg);
        }
    }
#else
    else
    {
        pRxChnSt->ChannelState = cCanTpRxState_WaitForTxFCOverrun;
        pRxChnSt->Timer = 0; /*Transmit FC in the task immediately*/
    }
#endif
    return ret;
}

#define CANTP_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"  


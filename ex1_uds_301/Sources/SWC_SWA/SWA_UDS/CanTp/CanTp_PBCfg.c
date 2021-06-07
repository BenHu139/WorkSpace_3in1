/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanTp_PBCfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : CanTp module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : CanTp module configuration File
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   04.03.00    06/09/2016     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/
  
/******************************************************************************* 
*   Includes 
*******************************************************************************/ 
#include "CanTp.h"
#include "CanTp_Cfg.h"
  
#define CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"
  
/******************************************************************************* 
*   declaration 
*******************************************************************************/ 
/* struct to hold the complete CanTp-configuration */
STATIC CONST(CanTp_RxNsduCfgType,CANTP_CONFIG_CONST) CanTp_RxNsduCfgInfo[CANTP_NUM_RX_SDUS];
STATIC CONST(CanTp_TxNsduCfgType,CANTP_CONFIG_CONST) CanTp_TxNsduCfgInfo[CANTP_NUM_TX_SDUS];
STATIC CONST(CanTp_ChannelModeType,CANTP_CONFIG_CONST) CanTp_ChannelModeInfo[CANTP_CHANNELS];
  
CONST(CanTp_ConfigType,CANTP_CONFIG_CONST) CanTp_Cfg =
{   
    CanTp_RxNsduCfgInfo /* Pointer to RxNsdu-cfg-table */, 
    CanTp_TxNsduCfgInfo /* Pointer to TxNsdu-cfg-table */, 
    CanTp_ChannelModeInfo /* Extended SDU indirection table */, 
};
  
/******************************************************************************* 
*   RxNsdu 
*******************************************************************************/ 
STATIC CONST(CanTp_RxNsduCfgType,CANTP_CONFIG_CONST) CanTp_RxNsduCfgInfo[CANTP_NUM_RX_SDUS] =
{
    /* NSDU ID 0:CANTP_RXNSDU_ID to PduR DIAG_Req_Phy */
    {
        1,   /* Tp Channel Num */
        0,   /* CANTP_RXNPDU_ID; from  CanIf */ 
        0,   /* CANTP_TXFC_NPDU_ID; to CanIf */  
        1,   /* CANTP_DL */   
        70,   /* CANTP_NAR */ 
        70,   /* CANTP_NBR (N_Br+N_Ar) < 0.9*N_Bs */  
        150,   /* CANTP_NCR */  
        STD_ON,   /* CANTP_PADDING_ACTIVATION */  
        CANTP_PHYSICAL,   /* CANTP_TA_TYPE */  
        CANTP_STANDARD,   /* CANTP_ADDRESSING_FORMAT */  
        8,   /* CANTP_BS */ 
        20,   /* CANTP_STMIN */ 
        0,   /* CANTP_WFTMAX */ 
        CANTP_UNUSED,   /* CANTP_RX_NAE */ 
        CANTP_UNUSED,   /* CANTP_RX_NSA */ 
        CANTP_UNUSED,   /* CANTP_RX_NTA */ 
    },
    /* NSDU ID 1:CANTP_RXNSDU_ID to PduR DIAG_Req_Fun */
    {
        0,   /* Tp Channel Num */
        1,   /* CANTP_RXNPDU_ID; from  CanIf */ 
        CANTP_UNUSED,   /* CANTP_TXFC_NPDU_ID; to CanIf */  
        1,   /* CANTP_DL */   
        70,   /* CANTP_NAR */ 
        70,   /* CANTP_NBR (N_Br+N_Ar) < 0.9*N_Bs */  
        150,   /* CANTP_NCR */  
        STD_OFF,   /* CANTP_PADDING_ACTIVATION */  
        CANTP_FUNCTIONAL,   /* CANTP_TA_TYPE */  
        CANTP_STANDARD,   /* CANTP_ADDRESSING_FORMAT */  
        8,   /* CANTP_BS */ 
        20,   /* CANTP_STMIN */ 
        10,   /* CANTP_WFTMAX */ 
        CANTP_UNUSED,   /* CANTP_RX_NAE */ 
        CANTP_UNUSED,   /* CANTP_RX_NSA */ 
        CANTP_UNUSED,   /* CANTP_RX_NTA */ 
    }
    
    
};
  
/******************************************************************************* 
*   TxNsdu 
*******************************************************************************/ 
STATIC CONST(CanTp_TxNsduCfgType,CANTP_CONFIG_CONST) CanTp_TxNsduCfgInfo[CANTP_NUM_TX_SDUS] =
{
    /* NSDU ID 0:CANTP_TXNSDU_ID from PduR DIAG_Response*/
    {
        1,   /* Tp Channel Num */
        0,   /* CANTP_TXNPDU_ID; to CanIf */  
        0,   /* CANTP_RXFC_ID; from  CanIf */ 
        1,   /* CANTP_DL */   
        70,   /* CANTP_NAS */ 
        150,   /* CANTP_NBS */  
        70,   /* CANTP_NCS */  
        STD_ON,   /* CANTP_PADDING_ACTIVATION */  
        CANTP_PHYSICAL,   /* CANTP_TA_TYPE */  
        CANTP_STANDARD,   /* CANTP_ADDRESSING_FORMAT */  
        CANTP_UNUSED,   /* CANTP_TX_NAE */ 
        CANTP_UNUSED,   /* CANTP_TX_NSA */ 
        CANTP_UNUSED,   /* CANTP_TX_NTA */ 
    }
     
};
  
/******************************************************************************* 
*   CanTp Channel Mode  
*******************************************************************************/ 
STATIC CONST(CanTp_ChannelModeType,CANTP_CONFIG_CONST) CanTp_ChannelModeInfo[CANTP_CHANNELS] =
{
    {
        CANTP_MODE_HALF_DUPLEX
    },
    {
        CANTP_MODE_HALF_DUPLEX
    }
};

#define CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"

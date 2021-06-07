/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanIf_Lcfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : CanIf module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : CanIf module configuration File
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
#include "CanIf.h" 
#include "CanTp_Cbk.h" 

/*******************************************************************************
*   Macro
*******************************************************************************/

#define CANIF_CFG_TOTAL_TXPDUID             (1)  
#define CANIF_CFG_TOTAL_RXPDUID             (2)  

#if (STD_ON == CANIF_RX_PDU_RANGE_CANID) 
    #define CANIF_CFG_RANGE_CANID_RXPDUID   (0)
#endif
#define CANIF_CFG_TOTAL_HRH                 (5)  


/*******************************************************************************
*   Global Data Define, No need to be configed 
*******************************************************************************/
#define CANIF_START_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
    VAR(boolean, CANIF_PRIVATE_DATA) 
                              CanIfTxBufferPDUFillflag[CANIF_CFG_TOTAL_TXPDUID];

    VAR(uint8, CANIF_PRIVATE_DATA)
                        CanIfTxBufferSdu[CANIF_CFG_TOTAL_TXPDUID][CAN_DATA_DLC];

    VAR(Can_PduType, CANIF_PRIVATE_DATA) 
                                      CanIfTxBufferPdu[CANIF_CFG_TOTAL_TXPDUID];
#endif

#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
    VAR(Can_IdType, CANIF_PRIVATE_DATA) 
                             CanIfTxPduCanIdForDynamic[CANIF_CFG_TOTAL_TXPDUID]; 
#endif 

#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
    VAR(CanIf_NotifStatusType, CANIF_PRIVATE_DATA)
                                    CanIfTxNotifStatus[CANIF_CFG_TOTAL_TXPDUID];
#endif 

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API) 
    VAR(CanIf_NotifStatusType, CANIF_PRIVATE_DATA)
                                    CanIfRxNotifStatus[CANIF_CFG_TOTAL_RXPDUID];
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
    VAR(uint8, CANIF_PRIVATE_DATA) 
                    CanIfRxBufferSduData[CANIF_CFG_TOTAL_RXPDUID][CAN_DATA_DLC];
    VAR(PduLengthType, CANIF_PRIVATE_DATA) 
                                CanIfRxBufferSduLength[CANIF_CFG_TOTAL_RXPDUID];
#endif

#define CANIF_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
CONST(PduIdType, CANIF_CONFIG_CONST) CanIfInitNumberOfCanRxPduIds 
                                                      = CANIF_CFG_TOTAL_RXPDUID;
CONST(PduIdType, CANIF_CONFIG_CONST) CanIfInitNumberOfCanTxPduIds 
                                                      = CANIF_CFG_TOTAL_TXPDUID;
CONST(Can_HwHandleType, CANIF_CONFIG_CONST) CanIfInitNumberofHrh 
                                                          = CANIF_CFG_TOTAL_HRH;

/*******************************************************************************
*   Config Parameters   
*******************************************************************************/

#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
CONST(CanIf_RxPduCanIdRangeType, CANIF_CONFIG_CONST) 
	                     CanIfRxPduCanIdRangeConfig[CANIF_CFG_RANGE_CANID_RXPDUID] = 
{
}; 
#endif 

CONST(CanIf_RxPduConfigType, CANIF_CONFIG_CONST) 
	                     CanIfRxPduConfig[CANIF_CFG_TOTAL_RXPDUID] = 
{
    /* 0 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x18da17f1U, /* CanId*/ 
        EXTENDED_CAN, /* CanIdType */ 
        0, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        CanTp_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        1, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 1 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        1,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x18dbfff9U, /* CanId*/ 
        EXTENDED_CAN, /* CanIdType */ 
        0, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        CanTp_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    }

}; 

#if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
CONST(Can_HwHandleType, CANIF_CONFIG_CONST)
                                     CanIfHrhFirstRxPduID[CANIF_CFG_TOTAL_HRH] = 
{ 
    0,
    0,
    0,
    0,
    2
};

#if(STD_ON == CANIF_PUBLIC_TX_BUFFERING)
CONST(Can_HwHandleType, CANIF_CONFIG_CONST)
	                                     CanIfHthFirstTxPduID[1] =
{
    0,
};
#endif
#endif 

#if(STD_ON == CANIF_HRH_RANGE_FILTER)
CONST(CanIf_HrhRangeCfgType, CANIF_CONFIG_CONST)
                                         CanIfHrhRangeCfg[CANIF_CFG_TOTAL_HRH] =
{
    /* not supported */  
};
#endif 

CONST(CanIf_TxPduConfigType, CANIF_CONFIG_CONST)
	                     CanIfTxPduConfig[CANIF_CFG_TOTAL_TXPDUID] = 
{
    /* 0 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x18daf117U, /* CanId*/ 
        EXTENDED_CAN, /* CanIdType */ 
        (0*CAN_PER_CONTROLLER_MB_NUM) + 13u, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        CanTp_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        CANIF_LAST_HOH_PDUID   /* HthNextTxPduID */  
        #endif
    }   
}; 

#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"


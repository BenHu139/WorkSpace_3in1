/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanTp_Cfg.h
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
#ifndef _CANTP_CFG_H_                                    
#define _CANTP_CFG_H_                                    
  
/******************************************************************************* 
*   Includes 
*******************************************************************************/ 
#include  "CanIf.h"
#include  "Dcm_Cbk.h"

/******************************************************************************* 
*   Global defines
*******************************************************************************/ 
/* CanTpGeneral{CanTpConfiguration} */
#define CANTP_VERSION_INFO_API        STD_OFF
#define CANTP_DEV_ERROR_DETECT        STD_OFF
#define CANTP_PROD_ERROR_DETECT       STD_OFF
#define CANTP_TC                      STD_OFF
#define CANTP_MAIN_FUNCTION_PERIOD    (10)

/* CanTpChannel */ 
#define CANTP_FILLPATTERN    ((uint8)0x0U)

/* Maximum number of Channels supported by the CanTp on this ECU */ 
#define CANTP_CHANNELS         (2)
#if CANTP_CHANNELS > 0 
#else
#error "The CANTP_CHANNELS should not be 0" 
#endif

#define CANTP_NUM_RX_SDUS      ((PduIdType)2)
#define CANTP_NUM_TX_SDUS      ((PduIdType)1)

#define CANTP_NUM_RX_CHANNELS               ((PduIdType)CANTP_CHANNELS)
#define CANTP_NUM_TX_CHANNELS               ((PduIdType)CANTP_CHANNELS)

#define CanTp_CanInterruptDisable()  CANIF_ENTER_CRITICAL_SECTION()/* DisableInterrupts; */
#define CanTp_CanInterruptRestore()  CANIF_LEAVE_CRITICAL_SECTION()/* EnableInterrupts;  */ 

/*******************************************************************************
*   Description : The network layer use  the service function that is provided 
*   by the lower layer to transmit N-PDU 
*******************************************************************************/
#define CanTp_CanTransmit(txSduIdx,pduInfo)    CanIf_Transmit(txSduIdx,pduInfo)

/*******************************************************************************
*   Description : The network layer use  the service function that is provided 
*   by the lower layer to cancel transmit N-PDU. 
*******************************************************************************/
#define CanTp_CanCancelTransmit(txSduIdx)    E_OK

/*******************************************************************************
*   Description : This service is used by the network layer to pass status 
*   information and received data to upper communication layers or the application 
*******************************************************************************/
#define CanTp_NUSDataIndication(rxSduIdx,canTpErrorCode)     Dcm_RxIndication(rxSduIdx,canTpErrorCode)

/*******************************************************************************
*   Description : This service is used by the network layer to pass status  
*   information to higher communication layers or the application. 
*******************************************************************************/
#define CanTp_NUSDataConfirm(txSduIdx,canTpErrorCode)     Dcm_TxConfirmation(txSduIdx,canTpErrorCode)

/*******************************************************************************
*   Description : This service is used to signal the beginning of a segmented  
*   message reception to the upper layer. 
*******************************************************************************/
#define CanTp_NUSDataFFIndication(rxSduIdx,length,bufferSizePtr)     Dcm_StartOfReception(rxSduIdx,length,bufferSizePtr)

/*******************************************************************************
*   Description : This service is used to signal the beginning of a segmented  
*   message reception to the upper layer. 
*******************************************************************************/
#define CanTp_NUSDataSFIndication(rxSduIdx,length,bufferSizePtr)     Dcm_StartOfReception(rxSduIdx,length,bufferSizePtr)

/*******************************************************************************
*   Description : The network layer use  the  function that is provided by the  
*   upper layer to copy data of received N-PDU to buffer provided by the upper layer  
*******************************************************************************/
#define CanTp_CopyRxData(rxSduIdx,pduInfo,bufferSizePtr)      Dcm_CopyRxData(rxSduIdx,pduInfo,bufferSizePtr)

/*******************************************************************************
*   Description : The network layer use  the  function that is provided by   
*   the upper layer to copy data of transmitted N-PDU from buffer provided by   
*   the upper layer  to network layer. 
*******************************************************************************/
#define CanTp_CopyTxData(txSduIdx,pduInfo,NULL_PTR,bufferSizePtr)      Dcm_CopyTxData(txSduIdx,pduInfo,NULL_PTR,bufferSizePtr)

#endif /* CANTP_CFG_H */

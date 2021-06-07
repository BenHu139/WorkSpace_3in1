/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : App_CanIf.c
********************************************************************************
*   Project/Product : CanIf module
*   Title           : CanIf module Source File 
*   Author          : Hirain
********************************************************************************
*   Description     : Main source file of the AUTOSAR Diagnositc communcation 
* 
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
*   02.03.01    03/07/2015    sijia.hao    N/A          D10_CANIF_140317_01
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
* Include files
********************************************************************************/
#include "CAN.h" 
#include "CanIf.h"
#include "CanTp_Cbk.h"

/*******************************************************************************
* Global variables(Scope:local)
********************************************************************************/
uint8 CANA_APP_TX_FLAG = 1;

/******************************************************************************
* Name         :App_TxConfirmation 
* Called by    :CanIf   
* Preconditions:N/A  
* Parameters   :PduIdType CanIfTxPduId  
* Return code  :N/A  
* Description  : Confirm Tx Completed
*                
******************************************************************************/
FUNC(void,CANTP_PUBLIC_CODE) App_TxConfirmation
(
    PduIdType CanIfTxPduId
)
{
    #if 0
    if(CanIfTxPduId < 23)
    {
        CANA_APP_TX_FLAG = 1;
    }
    #endif
}

/******************************************************************************
* Name         :App_RxIndication 
* Called by    :CanIf   
* Preconditions:N/A  
* Parameters   :PduIdType CanIfRxPduId, 
                       P2CONST(PduInfoType,AUTOMATIC,CANIF_APPL_DATA)pCanIfRxPduPtr
* Return code  :N/A  
* Description  : App Rx
*                
******************************************************************************/
FUNC(void,CANTP_PUBLIC_CODE) App_RxIndication
(
    PduIdType CanIfRxPduId, 
    P2CONST(PduInfoType,AUTOMATIC,CANIF_APPL_DATA)pCanIfRxPduPtr
)
{

}




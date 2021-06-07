/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : App_Dcm.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Dcm module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Dcm module configuration File
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
*   04.03.00    19/09/2016     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
* Include files
********************************************************************************/
#include "Compiler_Cfg.h"
#include "Dcm.h"
#include "App_Boot.h"
#include "bl_typedefs.h"
#include "bl_common.h"
#include "Dcm_Types.h"
#include "TMR.h"
#include "E2PE_Cfg.h"
#include "E2PE_MGR.h"
#include "Calibration_cfg.h"
#include "debug_only.h"

//#include "SpiFlash.h"
//#include "REMOTEREVDATA.h"
//#include "UPDATEDATA.h"
#include "App_Boot.h"
#include "stdlib.h" 
#include "security.h"
#include "UDS_CAN.h"
#include "CAN_STACK.h"
#include "VERSION.h"

static FUNC(void,DCM_CODE) GetKey(uint8 Dcm_SecuirityLevel, uint8* Key);
static FUNC(void,DCM_CODE) GetSeed(uint8 Dcm_SecuirityLevel, uint8* seed);

#define  ENCRYPTION_KEY   (0x1FF1DE77)

#if(DCM_SERVICE_28_ENABLED == STD_ON)
#endif

/*******************************************************************************
* Macros and Typedef
********************************************************************************/

#if(DCM_SERVICE_85_ENABLED == STD_ON)
uint8 gDTCSwitch;
#endif

#if(DCM_SERVICE_3D_ENABLED == STD_ON)
#define W8(addr, value)              (*((uint8 *) (addr)) = (value))
#define R8(addr)                     (*((uint8 *) (addr)))
#endif

#if(ISO_15031_5 == STD_ON)
/* For 0x01*/
/* For 0x02*/
/* For 0x06*/
/* For 0x09*/
#endif

/* For 0x22*/
#define ReadHandle_0x0000    (0U)
#define ReadHandle_0xF184    (1U)
#define ReadHandle_0xF185    (2U)
#define ReadHandle_0xF187    (3U)
#define ReadHandle_0xF189    (4U)
#define ReadHandle_0xF18A    (5U)
#define ReadHandle_0xF18B    (6U)
#define ReadHandle_0xF18C    (7U)
#define ReadHandle_0xF190    (8U)
#define ReadHandle_0xF193    (9U)
#define ReadHandle_0xF1A0    (10U)
#define ReadHandle_0xF1A1    (11U)
#define ReadHandle_0xF1A2    (12U)
#define ReadHandle_0xFC01    (13U)
#define ReadHandle_0xFC02    (14U)
#define ReadHandle_0xFC03    (15U)
#define ReadHandle_0xFC04    (16U)
#define ReadHandle_0xFC11    (17U)
#define ReadHandle_0xFC12    (18U)


/* For 0x24*/

/* For 0x27 */
#define DCM_SEC_HANDLE_LV_1    (0U)
#define DCM_SEC_HANDLE_LV_2    (1U)
#define DCM_SEC_HANDLE_LV_3    (2U)
#define DCM_SEC_HANDLE_LV_4    (3U)
#define DCM_SEC_HANDLE_LV_5    (4U)
#define DCM_SEC_HANDLE_LV_6    (5U)
#define DCM_SEC_HANDLE_LV_7    (6U)

/* For 0x28 */
#define Dcm_EnRx_EnTx          (0U)
#define Dcm_DisRx_EnTx         (1U)
#define Dcm_EnRx_DisTx         (2U)
#define Dcm_DisRx_DisTx        (3U)

/* For 0x2A*/

/* For 0x2C*/

/* For 0x2E*/
#define WriteHandle_0x0000    (0U)
#define WriteHandle_0xF184    (1U)
#define WriteHandle_0xF185    (2U)
#define WriteHandle_0xF187    (3U)
#define WriteHandle_0xF189    (4U)
#define WriteHandle_0xF18A    (5U)
#define WriteHandle_0xF18B    (6U)
#define WriteHandle_0xF18C    (7U)
#define WriteHandle_0xF190    (8U)
#define WriteHandle_0xF193    (9U)
#define WriteHandle_0xF1A0    (10U)
#define WriteHandle_0xF1A1    (11U)
#define WriteHandle_0xF1A2    (12U)
#define WriteHandle_0xFC01    (13U)
#define WriteHandle_0xFC02    (14U)
#define WriteHandle_0xFC03    (15U)
#define WriteHandle_0xFC04    (16U)
#define WriteHandle_0xFC11    (17U)
#define WriteHandle_0xFC12    (18U)

/* For 0x2F*/
#define IOcontrolHandle_0xFE00    (0U)
#define IOcontrolHandle_0xFE01    (1U)
#define IOcontrolHandle_0xFE02    (2U)
#define IOcontrolHandle_0xFE03    (3U)
#define IOcontrolHandle_0xFE04    (4U)
#define IOcontrolHandle_0xFE05    (5U)
#define IOcontrolHandle_0xFE06    (6U)
#define IOcontrolHandle_0xFE07    (7U)
#define IOcontrolHandle_0xFE08    (8U)

/* For 0x31*/
#define RoutineHandle_0xFF02    (0U)
#define RoutineHandle_0xFF00    (1U)
#define RoutineHandle_0xF001    (2U)
#define RoutineHandle_0xFF01    (3U)
#define RoutineHandle_0x0800    (4U)

#define ADPT_UDS_ERASE_MEMORY_FORMAT_POS    (5)
#define ADPT_UDS_ERASE_MEMORY_ADDRESS_POS   (6)
#define ADPT_UDS_ERASE_MEMORY_SIZE_POS      (10)


/*******************************************************************************
* Global variables(Scope:local)
********************************************************************************/
#if(ISO_15031_5 == STD_ON)
/* For 0x02*/
/* For 0x03*/
/* For 0x04*/
/* For 0x07*/
/* For 0x08*/
/* For 0x0A*/
#endif

static uint8 DTCStatusAvailabilityMask = 0xffU;
uint32 SupportedDTCGroup = 0x00U;
static uint32 SupportedDTC[NUM_OF_DTC] =
{
    0x000C03U,
    0x000C83U,
    0x000C8AU,
    0x000C93U,
    0x000DCAU,
    0x000DD3U,
    0x000E83U,
    0x000E84U,
    0x000EA3U,
    0x000EA4U,
    0x000EC3U,
    0x000EC4U,
    0x0017C8U,
    0x0017CAU,
    0x0017D3U,
    0x019608U,
    0x01960AU,
    0x019613U,
    0xFC004AU,
    0xFC0053U,
    0xFC0062U,
    0xFC0083U,
    0xFC0086U,
    0xFC00A3U,
    0xFC00A6U,
    0xFC00C3U,
    0xFC00C6U,
    0xFC00E3U,
    0xFC00E6U,
    0xFC0103U,
    0xFC0106U,
    0xFC0123U,
    0xFC0126U,
    0xFC0253U,
    0xFC0273U,
    0xFC0293U,
    0xFC02ABU,
    0xFC02CBU,
    0xFC02EBU,
    0xFC030BU,
    0xFC032BU,
    0xFC034BU,
    0xFC036BU,
    0xFC038BU,
    0xFC03ABU,
    0xFC03CBU,
    0xFC03EBU,
    0xFC040BU,
    0xFC042BU,
    0xFC0443U,
    0xFC0444U
};
uint8 DTCStatus[NUM_OF_DTC] =
{
    0x08U
};

uint8 DATA_0x0000[4];

static uint8 ApplicationSoftwareIdentification[32] =
{
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b,
    0x1c, 0x1d, 0x1e, 0x1f
};

/* Below codes are demo for 0x27, all of them can be deleted */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
static uint8 MagicSeed[8] = {0x5A, 0x5A, 0xAA, 0xAA, 0x54, 0x54, 0xCC, 0xCC};
#endif

#if(DCM_SERVICE_28_ENABLED == STD_ON)
/* if Hirain Com& Nm are used, don't change below codes */
static uint8 Dcm_NmMessage_Status = Dcm_EnRx_EnTx;
static uint8 Dcm_ComMessage_Status = Dcm_EnRx_EnTx;
#endif

/* Below codes are demo for 0x2F, all of them can be deleted */
static uint8 TEST[7] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07};



/***************************************************************************
* Global Function Implementation
****************************************************************************/
#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
/****************************************************************************
* Name         :App_DiagnosticActive 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :N/A  
* Return code  :N/A  
* Description  :Check is it possible to enable Dcm module.  
*                
******************************************************************************/
FUNC(Std_ReturnType,DCM_CODE) App_DiagnosticActive(void)
{
     return E_OK;
}
#endif 

#if(ISO_15031_5 == STD_ON)
#if(DCM_SERVICE_01_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_03_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_04_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_06_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_07_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_08_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_09_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_0A_ENABLED == STD_ON)
#endif
#endif 



/* 0x10 */
#if(DCM_SERVICE_10_ENABLED == STD_ON)

/******************************************************************************
* Name         :App_Default 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Default(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2StarServerMax/10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
    
    FWS_CAN_STACK_SetGlobalComEnFlag(1u);
}


/******************************************************************************
* Name         :App_DefaultPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_DefaultPost(Std_ReturnType Result)
{
    uint8 i;
    
    if(Result == E_OK)
    {
        Set_SesCtrl(DCM_SESSION_DEFAULT); 
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* Reset the CommunicationControl Flags */
        #if(DCM_SERVICE_28_ENABLED == STD_ON)
        #endif
        
        /* add your code here*/
    }
    else
    {
    }
}

/******************************************************************************
* Name         :App_Programming 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Programming(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
#if 0
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2StarServerMax/10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
    #endif

     DslInternal_RCRResponsePending(FORCERCR_RP);
     Clr_DiagState(DIAG_UDS_PROCESSING);
    
}


/******************************************************************************
* Name         :App_ProgrammingPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_ProgrammingPost(Std_ReturnType Result)
{
#if 0
    uint8 i;
    
    if(Result == E_OK)
    {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_PROGRAMMING);  
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* add your code here*/
    }
    else
    {
    }
#endif
    Boot_ReprogramCallBack();
 
}

/******************************************************************************
* Name         :App_Extended_Diagnostic 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_Diagnostic(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2StarServerMax/10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}


/******************************************************************************
* Name         :App_Extended_DiagnosticPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_DiagnosticPost(Std_ReturnType Result)
{
    uint8 i;
    
    if(Result == E_OK)
    {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_EXTENDED_DIAGNOSTIC);  
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* add your code here*/
    }
    else
    {
    }
}
#endif

/* 0x11 */
#if(DCM_SERVICE_11_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Hard_Reset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :Hard_Reset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Hard_Reset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_Hard_Reset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_Hard_Reset_ResetPost(Std_ReturnType Result)
{
    uint8 i;

    if(Result == E_OK)
    {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);

        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */           
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
    }
    else
    {
    }
}
/******************************************************************************
* Name         :App_keyOffOnReset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :keyOffOnReset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_keyOffOnReset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_keyOffOnReset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_keyOffOnReset_ResetPost(Std_ReturnType Result)
{
    uint8 i;

    if(Result == E_OK)
    {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);

        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */           
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
    }
    else
    {
    }
}
/******************************************************************************
* Name         :App_Soft_Reset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :Soft_Reset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Soft_Reset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_Soft_Reset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_Soft_Reset_ResetPost(Std_ReturnType Result)
{
    uint8 i;

    if(Result == E_OK)
    {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);

        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */           
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
    }
    else
    {
    }
}
#endif

/* 0x14 */
#if(DCM_SERVICE_14_ENABLED == STD_ON)
/************************************************************************
* Name         :App_ClearDiagnosticInformation 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Clear single DTC or group of DTC.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ClearDiagnosticInformation(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;

    Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_1], pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3]);
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if(Dtc == SupportedDTC[i])
        {
            i = NUM_OF_DTC;                                
        }
        else
        {
            if(i == (NUM_OF_DTC - 1U))
            {
                if((Dtc != 0xffffff) && (Dtc != SupportedDTCGroup))
                {
                    error = 1U;
                    DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
                }
                else
                {
                }
            }
            else
            {
            }
        }
    }
    if(error == 0U)
    {
        for(i = 0U; i < NUM_OF_DTC; i++)
        {
           DTCStatus[i] = 0U;        
        }
        pMsgContext->resDataLen = 1U; 
        DsdInternal_ProcessingDone(pMsgContext);

        /* Add your code here to clear DTC information */
    }
    else
    {
    }
}
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Read0x0000 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0000(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0000].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0x0000[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0000].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0000].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF189 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF189(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint16 i;
    uint8 tmp[16];
    
    FWS_VER_GetAppSWV(tmp);
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF189].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = tmp[i];
    }
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF189].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF189].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF18A 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18A(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_SYS_Supply_ID_7, (u8*)&pMsgContext->resData[2U]);
	
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF18A].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF18A].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF18B 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18B(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_ECU_Date_1, (u8*)&pMsgContext->resData[2U]);
	
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF18B].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF18B].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF18C 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18C(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_ECU_SN_0, (u8*)&pMsgContext->resData[2U]);
	
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF18C].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF18C].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF190 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_VIN_Code_11, (u8*)&pMsgContext->resData[2U]);
	
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF1A2 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF1A2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_Product_Model_10, (u8*)&pMsgContext->resData[2U]);
	
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1A2].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1A2].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF1A0 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF1A0(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_CAL_SW_Ver_8, (u8*)&pMsgContext->resData[2U]);
	
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1A0].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1A0].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}


/******************************************************************************
* Name         :App_Read0xF1A1 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF1A1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_CAL_Data_Ver_9, (u8*)&pMsgContext->resData[2U]);
	
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1A1].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1A1].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}


/******************************************************************************
* Name         :App_Read0xF193 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF193(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_ECU_HW_Ver_2, (u8*)&pMsgContext->resData[2U]);
	
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF193].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF193].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF184 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF184(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_APP_SW_Finger_4, (u8*)&pMsgContext->resData[2U]);
	
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF184].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF184].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
 
}

/******************************************************************************
* Name         :App_Read0xF185 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF185(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_APP_Data_Finger_5, (u8*)&pMsgContext->resData[2U]);
	
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF185].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF185].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF187 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF187(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
	E2PE_ReadParaFromBuffer(E2PE_PARA_ID_ECU_Part_Num_6, (u8*)&pMsgContext->resData[2U]);
	
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xFC01 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xFC01(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint16 i;
    uint8 tmp[10];
    
    CALIB_vidGetCalibInputData(CALIB_HVVOLT, tmp);
    
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xFC01].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = tmp[i];
    }
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xFC01].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xFC01].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xFC02 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xFC02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint16 i;
    uint8 tmp[10];
    
    CALIB_vidGetCalibInputData(CALIB_HVCURR, tmp);
    
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xFC02].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = tmp[i];
    }
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xFC02].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xFC02].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xFC03 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xFC03(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint16 i;
    uint8 tmp[10];
    
    CALIB_vidGetCalibInputData(CALIB_LVVOLT, tmp);
    
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xFC03].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = tmp[i];
    }
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xFC03].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xFC03].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xFC04 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xFC04(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint16 i;
    uint8 tmp[10];
    
    CALIB_vidGetCalibInputData(CALIB_LVCURR, tmp);
    
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xFC04].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = tmp[i];
    }
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xFC04].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xFC04].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xFC11 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xFC11(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint16 i;
    uint8 tmp[8];
    
    CALIB_vidGetCalibOutputData(0, tmp);
    
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xFC11].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = tmp[i];
    }
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xFC11].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xFC11].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xFC12 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xFC12(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint16 i;
    uint8 tmp[8];
    
    CALIB_vidGetCalibOutputData(1, tmp);
    
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xFC12].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = tmp[i];
    }
	#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xFC12].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xFC12].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
#endif
#endif
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#endif

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
#endif

/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Write0x0000
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0x0000(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0x0000].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0x0000[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF189
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF189(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_APP_SW_Ver_3, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF18B
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF18B(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_ECU_Date_1, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF18C
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF18C(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_ECU_SN_0, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF190
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_VIN_Code_11, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF193
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF193(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_ECU_HW_Ver_2, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF184
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF184(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_APP_SW_Finger_4, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xF187
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF187(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_ECU_Part_Num_6, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xF18A
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF18A(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_SYS_Supply_ID_7, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xF1A0
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF1A0(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_CAL_SW_Ver_8, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xF1A1
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF1A1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_CAL_Data_Ver_9, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xF1A2
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF1A2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_Product_Model_10, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xF185
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF185(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	E2PE_WriteParaToBuffer(E2PE_PARA_ID_APP_Data_Finger_5, (u8*)&pMsgContext->resData[2U]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xFC01
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xFC01(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	CALIB_vidSetCalibInputData(CALIB_HVVOLT, (u8*)&pMsgContext->resData[2U]);
	E2PE_WriteCalibDataWithoutCRC();
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xFC02
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xFC02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	CALIB_vidSetCalibInputData(CALIB_HVCURR, (u8*)&pMsgContext->resData[2U]);
	E2PE_WriteCalibDataWithoutCRC();
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xFC03
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xFC03(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	CALIB_vidSetCalibInputData(CALIB_LVVOLT, (u8*)&pMsgContext->resData[2U]);
	E2PE_WriteCalibDataWithoutCRC();
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xFC04
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xFC04(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	CALIB_vidSetCalibInputData(CALIB_LVCURR, (u8*)&pMsgContext->resData[2U]);
	E2PE_WriteCalibDataWithoutCRC();
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xFC11
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xFC11(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	CALIB_vidSetCalibOutputData(0, (u8*)&pMsgContext->resData[2U]);
	E2PE_WriteCalibDataWithoutCRC();
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Write0xFC12
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xFC12(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	CALIB_vidSetCalibOutputData(1, (u8*)&pMsgContext->resData[2U]);
	E2PE_WriteCalibDataWithoutCRC();
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ReturnControlToEcuFE00 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE00 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE00 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE00 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE00 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE00 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE00 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE00 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcuFE01 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE01 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE01 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE01 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE01 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE01 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE01 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE01 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcuFE02 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE02 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE02 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE02 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE02 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE02 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE02 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE02 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcuFE03 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE03 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE03 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE03 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE03 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE03 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE03 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE03 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcuFE04 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE04 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE04 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE04 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE04 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE04 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE04 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE04 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcuFE05 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE05 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE05 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE05 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE05 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE05 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE05 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE05 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcuFE06 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE06 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE06 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE06 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE06 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE06 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE06 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE06 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcuFE07 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE07 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE07 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE07 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE07 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE07 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE07 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE07 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcuFE08 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0xFE08 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentStateFE08 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0xFE08 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefaultFE08 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0xFE08 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentFE08 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0xFE08 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x19 */
#if(DCM_SERVICE_19_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ReportNumberOfDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Report number of DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_Number(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 i;
    uint16 counter = 0U;
    uint8  DtcStatus_Temp;
    DtcStatus_Temp = pMsgContext->reqData[DCM_INDEX_2];

    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if((DtcStatus_Temp & DTCStatus[i]) != 0U)
        {
            counter++;
        }
        else
        {  
        }
    }

    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    /* Change below data if necessary */
    /* 0x00 ISO15031-6Format,0x01 ISO14229-1Format,0x02 J1939 Format */
    pMsgContext->resData[DCM_INDEX_3] = 0x00U;
    pMsgContext->resData[DCM_INDEX_4] = (uint8)(counter >> 8U);
    pMsgContext->resData[DCM_INDEX_5] = (uint8)(counter);
    /* Always equals 6, don't change it */
    pMsgContext->resDataLen = 6U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Report DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_identified_errors(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8  i;
    uint16 counter = 0U;
    uint8  DtcStatus_Temp;
    DtcStatus_Temp = pMsgContext->reqData[DCM_INDEX_2];
   
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if((DtcStatus_Temp & DTCStatus[i]) != 0U)
        {
            pMsgContext->resData[DCM_INDEX_3 + counter * 4U] = (uint8)(SupportedDTC[i] >> 16U);
            pMsgContext->resData[DCM_INDEX_4 + counter * 4U] = (uint8)(SupportedDTC[i] >> 8U);
            pMsgContext->resData[DCM_INDEX_5 + counter * 4U] = (uint8)SupportedDTC[i];
            pMsgContext->resData[DCM_INDEX_6 + counter * 4U] = DTCStatus[i]; 
            counter++;
        }
        else
        {
        }
    }

    pMsgContext->resData[DCM_INDEX_1] = pMsgContext->reqData[DCM_INDEX_1];
    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    pMsgContext->resDataLen = DCM_INDEX_3 + (counter * 4U);
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportDTCSnapshortRecordByDTCNumber 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_snapshot(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;
    uint8 DTCSnapshotRecordNumber;
    uint8 DTCSnapshotRecordLength = 0U;

    DTCSnapshotRecordNumber = pMsgContext->reqData[DCM_INDEX_5];
    
    Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3], pMsgContext->reqData[DCM_INDEX_4]);

    /* Check DTC */
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if(Dtc == SupportedDTC[i])
        {
            pMsgContext->resData[DCM_INDEX_5] = DTCStatus[i]; 
            i = NUM_OF_DTC;                                
        }
        else
        {
            if(i == (NUM_OF_DTC - 1U))
            {
                error = 1U;
                DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
            }
            else
            {
                /* Do nothing */
            }
        }
    }

    if(error == 0U)
    {
        switch(DTCSnapshotRecordNumber)
        {
            /* Add your code here. Below codes should be changed as Spec */
            case 0xFF: /*return all DTCSnapshotRecordnumber*/
            case 0x01:
                pMsgContext->resData[6] = 0x01;  /* DTCSnapshotRecordNumber #2 */
                pMsgContext->resData[7] = 0x01;  /* DTCSnapshotRecordNumberOfIdentifiers #2 */

                /*the first Identifier 0x9abc*/
                pMsgContext->resData[8] = 0x9a; /*Dataidentifier#1  byte#1(MSB)*/
                pMsgContext->resData[9] = 0xbc; /*Dataidentifier#1  byte#1(LSB)*/
                pMsgContext->resData[10] = 0x13;/*SnapshotData#1	 byte#1*/	
                pMsgContext->resData[11] = 0x13;/*SnapshotData#1	 byte#2*/	
                pMsgContext->resData[12] = 0x13;/*SnapshotData#1	 byte#3*/			
                /* change below length according to App*/
                /* if the current DTCSnapshotRecordNumber is not available the length should 0 */
                DTCSnapshotRecordLength = 13U;
                break;

            default:
                DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
                error = 1U;
                break;
        }
    }
    else
    {
        /* Do nothing */
    }
    if(error == 0U)
    {
        pMsgContext->resDataLen = 8U + DTCSnapshotRecordLength;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDone(pMsgContext);
    }
}

/******************************************************************************
* Name         :App_ReportDTCExtendedDataRecordByDTCNumber 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_DTC_Extended_Data_Records_By_DTC_Number(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;
    /* change below length according to App*/
    if(((pMsgContext->reqData[DCM_INDEX_5] >= 1U) && (pMsgContext->reqData[DCM_INDEX_5] <= 0x8fU)) || (pMsgContext->reqData[DCM_INDEX_5] == 0xffU))
    {
        Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3], pMsgContext->reqData[DCM_INDEX_4]);
        for(i = 0U; i < NUM_OF_DTC; i++)
        {
            if(Dtc == SupportedDTC[i])
            {
                i = NUM_OF_DTC;                                
            }
            else
            {
                if(i == (NUM_OF_DTC - 1U))
                {
                    if(Dtc != 0xffffff)
                    {
                        error = 1U;
                        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
                    }
                    else
                    {
                    }
                }
                else
                {
                }
            }
        }
    }
    else
    {
        error = 1U;
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }

    if(error == 0U)
    {
        pMsgContext->resDataLen = 29U;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
    }
}

/******************************************************************************
* Name         :App_ReportSupportedDTC 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_supported_errors(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 i;

    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        pMsgContext->resData[DCM_INDEX_3 + i * 4U] = (uint8)(SupportedDTC[i] >> 16U);
        pMsgContext->resData[DCM_INDEX_4 + i * 4U] = (uint8)(SupportedDTC[i] >> 8U);
        pMsgContext->resData[DCM_INDEX_5 + i * 4U] = (uint8)(SupportedDTC[i]);
        pMsgContext->resData[DCM_INDEX_6 + i * 4U] = DTCStatus[i]; 
    }
    pMsgContext->resDataLen = 3U + NUM_OF_DTC * 4U;
    DsdInternal_ProcessingDone(pMsgContext);
}

#endif

/* 0x23 */
#if(DCM_SERVICE_23_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ReadAddress 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
void App_ReadAddress(Dcm_MsgContextType* pMsgContext)
{
    /* if too many datas to be readed ,and it is impossible read all data one time,
    App should remember the address and conter of data for the next Call .*/
    uint32 startAddress = 0U;                                
    uint32 memorySize = 0U;
    uint32 i;

    /* Calculate start address */
    for(i = 0U; i < gMemoryAddressFormat; i++)
    {
        startAddress |= ((uint32)(pMsgContext->reqData[2U + i]) << ((uint8)(8U * (gMemoryAddressFormat - 1U - i))));      
    }

    /* Calculate size  */
    for(i = 0U; i < gMemorySizeFormat; i++)
    {
        memorySize |= ((uint32)(pMsgContext->reqData[2U + gMemoryAddressFormat + i]) << ((uint8)(8U * (gMemorySizeFormat - 1U - i)))); 
    }

    /* Add your code here, to read data from the memory */
    for(i = 0U; i < memorySize; i++)
    {
        pMsgContext->resData[DCM_INDEX_1 + i] = R8(startAddress + i);
    }
    
    pMsgContext->resDataLen = (DCM_INDEX_1 + memorySize);
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x27 */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
/******************************************************************************
* Name         :GetKey 
* Called by    :  
* Preconditions:
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
static FUNC(void,DCM_CODE) GetKey(uint8 Dcm_SecuirityLevel, uint8* Key)
{
    uint8 buf[8] = {0u,0u,0u,0u,0u,0u,0u,0u};
    uint8 buf1[8] = {0u,0u,0u,0u,0u,0u,0u,0u};
    uint8 buf2[8] = {0u,0u,0u,0u,0u,0u,0u,0u};
    
    switch(Dcm_SecuirityLevel)
    {
        /* Add your code here to get Key according to last seed */
        case DCM_SEC_LEV_L1:
            Key[DCM_INDEX_0] = 0xFF;
            Key[DCM_INDEX_1] = 0xFF;
            Key[DCM_INDEX_2] = 0xFF;
            Key[DCM_INDEX_3] = 0xAA;
            Key[DCM_INDEX_4] = 0x06;
            Key[DCM_INDEX_5] = 0x05;
			Key[DCM_INDEX_6] = 0xDD;
			Key[DCM_INDEX_7] = 0x88;
            break;
        case DCM_SEC_LEV_L2:
            Key[0] = (uint8)(ENCRYPTION_KEY >> 24u);
            Key[1] = (uint8)(ENCRYPTION_KEY >> 16u);
            Key[2] = (uint8)(ENCRYPTION_KEY >> 8u);
            Key[3] = (uint8)(ENCRYPTION_KEY);
            
            _4byte_to_8byte((char*)MagicSeed,(char*)buf);
            _4byte_to_8byte((char*)Key,(char*)buf1);          
            encryption((char*)buf,(char*)buf1,(char*)buf2);
            _8byte_to_4byte((char*)buf2,(char*)Key);
            
            break;
        case DCM_SEC_LEV_L3:
        case DCM_SEC_LEV_L4:
        case DCM_SEC_LEV_L5:
        case DCM_SEC_LEV_L6:
        case DCM_SEC_LEV_L7:
            Key[DCM_INDEX_0] = 0xcc;
            Key[DCM_INDEX_1] = 0xcc;
            Key[DCM_INDEX_2] = 0xcc;
            Key[DCM_INDEX_3] = 0xcc;
            break;
        default: 
            break;
    }
}

void BOOTLOADER_GetSeed(u8 *buffer)
{
    uint32 seed;
    uint32 sentseed;

    seed = TMR_SYSTEM_TIME_GetTickMs();

    srand(seed);
    sentseed = (u16)rand();
    sentseed = (sentseed << 16U) + rand();
    
    buffer[0U] = (u8)(sentseed >> 24U);
    buffer[1U] = (u8)(sentseed >> 16U);
    buffer[2U] = (u8)(sentseed >> 8U);
    buffer[3U] = (u8)(sentseed);
}

/******************************************************************************
* Name         :GetKey 
* Called by    :  
* Preconditions:
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
static FUNC(void,DCM_CODE) GetSeed(uint8 Dcm_SecuirityLevel, uint8* seed)
{
    uint8 buf[8] = {0u,0u,0u,0u,0u,0u,0u,0u};

    switch(Dcm_SecuirityLevel)
    {
        /* Add your code here to get Key according to last seed */
        case DCM_SEC_LEV_L1:
            seed[DCM_INDEX_0] = 0xcc;
            seed[DCM_INDEX_1] = 0xcc;
            seed[DCM_INDEX_2] = 0xcc;
            seed[DCM_INDEX_3] = 0xcc;
            break;
        case DCM_SEC_LEV_L2:
            BOOTLOADER_GetSeed(buf);
            seed[DCM_INDEX_0] = buf[0];
            seed[DCM_INDEX_1] = buf[1];
            seed[DCM_INDEX_2] = buf[2];
            seed[DCM_INDEX_3] = buf[3];
            break;
        case DCM_SEC_LEV_L3:
        case DCM_SEC_LEV_L4:
        case DCM_SEC_LEV_L5:
        case DCM_SEC_LEV_L6:
        case DCM_SEC_LEV_L7:
            seed[DCM_INDEX_0] = 0xcc;
            seed[DCM_INDEX_1] = 0xcc;
            seed[DCM_INDEX_2] = 0xcc;
            seed[DCM_INDEX_3] = 0xcc;
            break;
        default: 
            break;
    }
}

/******************************************************************************
* Name         :App_Request_Seed_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Request_Seed_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 i;
    
    pMsgContext->resData[DCM_INDEX_1] = pMsgContext->reqData[DCM_INDEX_1];
    for(i = 0U; i < gDcmDspSecurityRow[DCM_SEC_HANDLE_LV_1].DcmDspSecuritySeedSize; i++)
    {
        /* add your code here, generate App Seed */
        gMsgContextType.resData[2U + i] = MagicSeed[i];
    }
    pMsgContext->resDataLen = gDcmDspSecurityRow[DCM_SEC_HANDLE_LV_1].DcmDspSecuritySeedSize + 2U; 
    DsdInternal_ProcessingDone(pMsgContext); 
}

/******************************************************************************
* Name         :App_Send_Key_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Send_Key_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 i;
    uint8 temp = 0U;
    uint8 key[8];
    
    /* Add your code here, check key according last Seed */
    GetKey(DCM_SEC_LEV_L1,key);
    
    for(i = 0U; i < gDcmDspSecurityRow[DCM_SEC_HANDLE_LV_1].DcmDspSecurityKeySize; i++)
    {
        if(pMsgContext->reqData[2U + i] != key[i])
        {
            temp++;
            i = gDcmDspSecurityRow[DCM_SEC_HANDLE_LV_1].DcmDspSecurityKeySize;
        } 
        else 
        {
            /* Do nothing */
        }
    }
    
    if(temp == 0U)
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_VALID);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_NOT_VALID);
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_INVALIDKEY);
    }
}


/******************************************************************************
* Name         :App_Request_Seed_L3 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Request_Seed_L2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 i;
    uint8  seed[8] = {0u,0u,0u,0u,0u,0u,0u,0u};

    GetSeed(DCM_SEC_LEV_L2,seed);
    
    pMsgContext->resData[DCM_INDEX_1] = pMsgContext->reqData[DCM_INDEX_1];
    for(i = 0U; i < gDcmDspSecurityRow[DCM_SEC_HANDLE_LV_2].DcmDspSecuritySeedSize; i++)
    {
        /* add your code here, generate App Seed */
        gMsgContextType.resData[2U + i] = seed[i];
        MagicSeed[i] = seed[i];
    }
    pMsgContext->resDataLen = gDcmDspSecurityRow[DCM_SEC_HANDLE_LV_2].DcmDspSecuritySeedSize + 2U; 
    DsdInternal_ProcessingDone(pMsgContext); 
}

/******************************************************************************
* Name         :App_Send_Key_L3 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Send_Key_L2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 i;
    uint8 temp = 0U;
    uint8 key[4];
    
    /* Add your code here, check key according last Seed */
    GetKey(DCM_SEC_LEV_L2,key);
    
    for(i = 0U; i < gDcmDspSecurityRow[DCM_SEC_HANDLE_LV_2].DcmDspSecurityKeySize; i++)
    {
        if(pMsgContext->reqData[2U + i] != key[i])
        {
            temp++;
            i = gDcmDspSecurityRow[DCM_SEC_HANDLE_LV_2].DcmDspSecurityKeySize;
        } 
        else 
        {
            /* Do nothing */
        }
    }

    if(temp == 0U)
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L2,KEY_IS_VALID);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L2,KEY_IS_NOT_VALID);
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_INVALIDKEY);
    }
}
#endif

/* 0x28 */
#if(DCM_SERVICE_28_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_EnableRxAndEnableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_EnableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    FWS_CAN_STACK_SetGlobalComEnFlag(1);
    
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_EnableRxAndDisableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_EnableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_DisableRxAndEnableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DisableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_DisableRxAndDisableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DisableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    
    if(Can_GetActiveChn() == 0u)
    {
        FWS_CAN_STACK_SetGlobalComEnFlag(0);
    }
   
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_StartRoutine0xFF02 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 ret;
    uint8 result = 0u;
     
    DsdInternal_RoutineStarted();
    /* Add your code here */
    ret = REMOTEUPDATE_CheckProgramCond();
    
    if(1u == ret)
    {
        result = ADPT_ROUTINE_CORRECT_RESULT;
    }
    else
    {
        result = ADPT_ROUTINE_INCORRECT_RESULT;
    }
    
    if(Can_GetActiveChn() == 4u)
    {
        pMsgContext->resData[DCM_INDEX_4] = 0x02u;
    }
    else
    {
        pMsgContext->resData[DCM_INDEX_4] = result;
    }
    
    UdsClearDownInfo(&gs_UdsPrivateData);
       
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF02].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StopRoutine0xFF02 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */
    UdsClearDownInfo(&gs_UdsPrivateData);
    
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF02].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xFF02
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF02].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}

/******************************************************************************
* Name         :App_StartRoutine0xFF00 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xFF00(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    /* Add your code here */
    if(UdsIsValidStatus(uds_download_state,UDS_STATUS_ERASE_BLOCK) != BL_ERR_OK)
    {
        REMOTEUPDATE_CallbackEraseMemory();
        
        UdsSetDownStatus(&uds_download_state, UDS_STATUS_ERASE_BLOCK);
    }
    
    DsdInternal_RoutineStarted();
    pMsgContext->resData[DCM_INDEX_4] = DCM_E_POSITIVERESPONSE;
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF00].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    
    if(REMOTEUPDATE_GetEraseMemoryResult() == 1u)  /*²Á³ýÍê³É*/
    {
        DsdInternal_ProcessingDone(pMsgContext);  
    }

}
/******************************************************************************
* Name         :App_StopRoutine0xFF00 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xFF00(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF00].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xFF02
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xFF00(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF00].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}

/******************************************************************************
* Name         :App_StartRoutine0xF001 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xF001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 result = 0u;
    
    DsdInternal_RoutineStarted();
    /* Add your code here */
    
    if(UdsIsValidStatus(uds_download_state,UDS_STATUS_CHECK_SUM) != BL_ERR_OK)
    {
        REMOTEUPDATE_SetCheckSumStart();          
        UdsSetDownStatus(&uds_download_state, UDS_STATUS_CHECK_SUM);
    }
    
    if(1u == REMOTEUPDATE_CallbackCheckSumCal())
    {
        result = REMOTEUPDATE_CallbackIsCheckSumValueValid(4u,&(pMsgContext->reqData[4]));
        if(1u == result)
        {
            result = ADPT_ROUTINE_CORRECT_RESULT;
        }
        else
        {
            result = ADPT_ROUTINE_INCORRECT_RESULT;
        }
        
        
        pMsgContext->resData[DCM_INDEX_4] = result;
        pMsgContext->resDataLen = 4U + \
            DcmDspRoutineIdentifierTable_31[RoutineHandle_0xF001].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength; 
        
        DsdInternal_ProcessingDone(pMsgContext); 
    }
 
}
/******************************************************************************
* Name         :App_StopRoutine0xF001 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xF001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xF001].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xF001
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xF001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xF001].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}

/******************************************************************************
* Name         :App_StartRoutine0xFF01 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xFF01(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    uint8 ret;
    uint8 result = 0u;

    result = ADPT_ROUTINE_INCORRECT_RESULT;
    
    DsdInternal_RoutineStarted();
    /* Add your code here */
    ret = REMOTEUPDATE_CheckCompatibility();
    if(1u == ret)
    {
        result = ADPT_ROUTINE_CORRECT_RESULT;
    }
    else
    {
        result = ADPT_ROUTINE_INCORRECT_RESULT;
    }

    UdsClearDownInfo(&gs_UdsPrivateData);
    
    pMsgContext->resData[DCM_INDEX_4] = result;
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF01].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StopRoutine0xFF01 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xFF01(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF01].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xFF01
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xFF01(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF01].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}

/******************************************************************************
* Name         :App_StartRoutine0x0800 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0x0800(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    uint8 result = 0u;


    result = ADPT_ROUTINE_INCORRECT_RESULT;

    
    DsdInternal_RoutineStarted();
    /* Add your code here */
    if(0x01 == pMsgContext->reqData[4])
    {
    	UPDATEDATA_init();
        if(1u == UPDATEDATA_CheckUpdateReqValid())
        {
            result = ADPT_ROUTINE_CORRECT_RESULT;
            REMOTEUPDATE_SetUpdateResetEcuReq(); 
        }
        else
        {
            result = ADPT_ROUTINE_INCORRECT_RESULT; 
        }
    }
    else if(0x02 == pMsgContext->reqData[4])
    {
        result = ADPT_ROUTINE_CORRECT_RESULT;
    }
    else
    {
        /*nothing to do*/
    }
   
    pMsgContext->resData[DCM_INDEX_4] = pMsgContext->reqData[4];
    pMsgContext->resData[DCM_INDEX_5] = result;
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0800].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext); 
    
}
/******************************************************************************
* Name         :App_StopRoutine0x0800 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0x0800(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0800].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xFF01
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0x0800(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0800].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}

#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
/*******************************************************************************
* Name         :App_WriteAddress 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
/* if too many datas, and it is impossible write all data one time,
App should remember the address and conter of data for the next Call. */
uint8  App_WriteAddressCounter = 0U;
uint32 startAddress_3D = 0U;
uint16 memorySize_3D = 0U;
  
FUNC(void,DCM_CODE) App_WriteAddress(Dcm_MsgContextType* pMsgContext)
{
    uint32 i;
    
    (void)pMsgContext;
    
    if(App_WriteAddressCounter == 0U)
    {
        /* Calculate start address */
        for(i = 0U; i < gMemoryAddressFormat; i++)
        {
            startAddress_3D |= (((uint32)(pMsgContext->reqData[2U + i])) << ((uint8)(8U * (gMemoryAddressFormat - 1U - i))));      
        }
        /* Calculate size */
        for(i = 0U; i < gMemorySizeFormat; i++)
        {
            memorySize_3D |=(((uint32)(pMsgContext->reqData[2U + gMemoryAddressFormat + i])) << ((uint8)(8U * (gMemorySizeFormat - 1U - i)))); 
        }
    }
    else
    {
        /* Do nothing */
    }
    if(App_WriteAddressCounter < memorySize_3D)
    {
        /* Add your code here to write data to the certain address */ 
        /* If the address to be written is in Flash or EEPROM, call related Driver */
        W8((startAddress_3D + App_WriteAddressCounter), pMsgContext->resData[2U + gMemoryAddressFormat + gMemorySizeFormat + App_WriteAddressCounter]);

        App_WriteAddressCounter++;
    }
    else
    {
        App_WriteAddressCounter = 0U;
        startAddress_3D = 0U;
        memorySize_3D = 0U; 
        pMsgContext->resDataLen = 2U + gMemoryAddressFormat + gMemorySizeFormat;
        DsdInternal_ProcessingDone(pMsgContext);
    }
}
#endif

/* 0x85 */
#if(DCM_SERVICE_85_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ON_Send
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ON_Send(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    (void)pMsgContext;
    /* Add your code here */
    gDTCSwitch = STD_ON;

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_OFF_Send
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_OFF_Send(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    (void)pMsgContext;
    /* Add your code here */
    gDTCSwitch = STD_OFF;

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x86 */
#if(DCM_SERVICE_86_ENABLED == STD_ON)
#endif

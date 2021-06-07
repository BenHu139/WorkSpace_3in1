/*BEGIN_FILE_HDR
***************************************************************************************************
* NOTICE                              
* This software is the property of HiRain Technologies. Any information contained in this 
* doc should not be reproduced, or used, or disclosed without the written authorization from 
* HiRain Technologies.
***************************************************************************************************
* File Name: Dem.c
***************************************************************************************************
* Project/Product: AUTOSAR BSW
* Title:
* Author: qyMa
***************************************************************************************************
* Description:AUTOSAR Diagnostic Event Manager (DEM) API implementation.
*
***************************************************************************************************
* Limitations:
*
* (limitations) 
***************************************************************************************************

***************************************************************************************************
* Revision History:
* 
*  Version       Date         Initials     CR#         Descriptions
*  ---------   -----------  ------------  ----------  ----------------------------------------
*  1.0.0        2015/12/15    guorui       N/A         Original
*  01.00.00     23/11/2016    rui.guo      N/A         HrAsrDem161123-01 
*  01.00.01     26/11/2016    rui.guo      N/A         HrAsrDem161126-01 
***************************************************************************************************
*END_FILE_HDR*/

#include "Dcm.h"
#include "Dem.h"
#include "Dem_Lcfg.h"
#include "Dem_Cfg.h"
#include "Nvm.h"
#include "debug_only.h"


/********************** NVM Inferface define End **************************/

#define DEM_QUEUE_CYCLE_STARTED                  DEM_CYCLE_STATE_START  /*(1U)*/
#define DEM_QUEUE_CYCLE_STOPPED                  DEM_CYCLE_STATE_END    /*(2U)*/
#define DEM_QUEUE_CYCLE_RESTARTED                (3U)
#define Dem_GetEventCurrentStatus(EventId)           (DemStorageMem.EventExtendStatus[EventId].ucEvnCurStatus)
#define Dem_SetEventCurrentStatus(EventId,Status)    (DemStorageMem.EventExtendStatus[EventId].ucEvnCurStatus=Status)
#define Dem_GetEventOperationCycleId(EventId)        (DemEventClassSet[EventId].DemOperationCycleRef)


#define DEM_RESTOREFLAG0  0x6759
#define DEM_RESTOREFLAG1  0xd94c

/*Clear DTC typ define*/
#define DEM_INTER_CLRNONE      0
#define DEM_INTER_CLRALL       1
#define DEM_INTER_CLRSINGLE    2
#define DEM_DCM_CLEAR_DTC_IDLE     0
#define DEM_DCM_CLEAR_DTC_HEADER   1
#define DEM_DCM_CLEAR_DTC_FF       3
#define DEM_DCM_CLEAR_DTC_EVST     4
#define DEM_DCM_CLEAR_DTC_BUSY     5
#define DEM_DCM_CLEAR_DTC_OK       6
#define DEM_DCM_CLEAR_DTC_ERR      7
#define DEM_DCM_CLEAR_EVENT_MEM    8
#define DEM_UNINIT                             0x0000
#define DEM_INITPENDING                        0x0001
#define DEM_CLEARMEMORY                        0x0002
#define DEM_DATARESTORING                      0x0004
#define DEM_NORMAL                             0x0008
#define DEM_OPECYCPENDING                      0x0010
#define DEM_SHUTDOWN                           0x0020
#define DEM_DATASTORING                        0x0040
#define DEM_STATVALIDEMASK                     0xFFFF
#define Dem_SetDemState(x)                         DemState = x
#define Dem_GetDemState(x)                         x = DemState
#define Dem_SetDemStateBit(x)                      DemState |= x
#define Dem_CheckDemState(st,mask)               ((st & mask) != 0)
#define Dem_GetCounterBasedDebounceCounter(EventId,Counter)  (Counter = DemStorageMem.EventExtendStatus[EventId].ssFCounterCB)                           
#define Dem_SetCounterBasedDebounceCounter(EventId,Counter)  (DemStorageMem.EventExtendStatus[EventId].ssFCounterCB = Counter)                           

#define Dem_Queue_IsPendingCycle(CycleId)        ((Dem_QueueCyclePendingFlag & ((uint8)(1U << (CycleId)))) != 0)         


typedef struct Dem_DebounceInfoType_s Dem_DebounceInfoType;                                                 

typedef P2FUNC(void, DEM_CODE, DebounceVoidFunctionPtr)(                                                                        
    Dem_EventIdType evnid,
    Dem_DebounceInfoType* pDebInfo);
typedef P2FUNC(boolean, DEM_CODE, DebounceBoolFunctionPtr)(
    Dem_EventIdType evnid,
    Dem_DebounceInfoType* pDebInfo);


struct Dem_DebounceFunctionTable_s
{
    DebounceBoolFunctionPtr debCal;/*debounce Calculate*/
    /*DebounceBoolFunctionPtr Validate;*/
    /*DebounceVoidFunctionPtr Commit;*/
};

typedef struct Dem_DebounceFunctionTable_s Dem_DebounceFunctionTableType;                           

struct Dem_DebounceInfoType_s
{
    struct
    {
      DebounceBoolFunctionPtr Calculate;
      Dem_EventStatusType MonitorStatus;
      boolean DebouncingChanged;
      uint8 DebounceAlgorithm;
    } Common;
    union
    {                                                                                                                              
      struct
      {
        sint16 OldDebounceValue;
        sint16 NewDebounceValue;

      } CounterBased;
      /*struct
      {
        Dem_Cfg_EventInternalStatusType OldInternalStatus;
        Dem_Cfg_EventInternalStatusType NewInternalStatus;
      } TimeBased;
      struct
      {
        sint8  NewFdc;
      } MonitorInternal;*/
    } Specific;
};

typedef struct Dem_ClearDTCInfo_s Dem_ClearDTCInfoType;

struct Dem_ClearDTCInfo_s
{
    uint16  MemEntryId;
    uint16  NvMBlkId;/*current block ID*/
    uint8  cleartyp;
    uint8  clearct;/*cuttent state0:clear idle. 1:clear header. 2:clear FF. 3:Clear EventStatus*/
    uint8  clearnt;/*next state */ /*NOT use*/
    union
    {
        uint8  _c[4];
        uint32 dtcvalue;
    }dtc;
};

typedef struct 
{
    Dem_EventStatusInfoType *     pEventStInfo;
    const Dem_EventParameterType* pEventParCfg; 
    const Dem_EventClassType*     pEventClassCfg; 
}Dem_EventContextType;


typedef struct Dem_DTCFilterInfo_s Dem_DTCFilterInfoType;
struct Dem_DTCFilterInfo_s
{
    uint8 FilteredValidFlag;

    uint8 DTCStatusMask; 
    Dem_DTCKindType DTCKind; 
    Dem_DTCFormatType DTCFormat; 
    Dem_DTCOriginType DTCOrigin;
    Dem_FilterWithSeverityType FilterWithSeverity; 
    Dem_DTCSeverityType DTCSeverityMask; 
    Dem_FilterForFDCType FilterForFaultDetectionCounter;
    uint16 FilteredDTCIndexTable[DEM_NUMBER_OF_DTC];
    uint16 NumberOfFilteredDTC;/*Total number*/
    uint16 NextFilteredDTCIndex;
};
#if !defined (DEM_UDS_STATUS_TF)
#define DEM_UDS_STATUS_TF                       (0x01U)
#endif
#if !defined (DEM_UDS_STATUS_TFTOC)
#define DEM_UDS_STATUS_TFTOC                    (0x02U)
#endif
#if !defined (DEM_UDS_STATUS_PDTC)
#define DEM_UDS_STATUS_PDTC                     (0x04U)
#endif
#if !defined (DEM_UDS_STATUS_CDTC)
#define DEM_UDS_STATUS_CDTC                     (0x08U)
#endif
#if !defined (DEM_UDS_STATUS_TNCSLC)
#define DEM_UDS_STATUS_TNCSLC                   (0x10U)
#endif
#if !defined (DEM_UDS_STATUS_TFSLC)
#define DEM_UDS_STATUS_TFSLC                    (0x20U)
#endif
#if !defined (DEM_UDS_STATUS_TNCTOC)
#define DEM_UDS_STATUS_TNCTOC                   (0x40U)
#endif
#if !defined (DEM_UDS_STATUS_WIR)
#define DEM_UDS_STATUS_WIR                      (0x80U)
#endif

#define DEM_1BYTE                                1
#define DEM_2BYTE                                2

#define DEM_MASK_1                               0xffU
#define DEM_MASK_2                               0xffffU
#define DEM_MASK(size)                           DEM_MASK_##size                                                              

#define DEM_BIT(pos)                             (0x01U << (pos))                                                               
#define DEM_BIT_MASK(pos, size)                  (DEM_MASK(size) ^ DEM_BIT(pos))                                                

#define DEM_UDS_STATUS_TF_MASK                   DEM_BIT_MASK(0, DEM_1BYTE)
#define DEM_UDS_STATUS_TFTOC_MASK                DEM_BIT_MASK(1, DEM_1BYTE)
#define DEM_UDS_STATUS_PDTC_MASK                 DEM_BIT_MASK(2, DEM_1BYTE)
#define DEM_UDS_STATUS_CDTC_MASK                 DEM_BIT_MASK(3, DEM_1BYTE)
#define DEM_UDS_STATUS_TNCSLC_MASK               DEM_BIT_MASK(4, DEM_1BYTE)
#define DEM_UDS_STATUS_TFSLC_MASK                DEM_BIT_MASK(5, DEM_1BYTE)
#define DEM_UDS_STATUS_TNCTOC_MASK               DEM_BIT_MASK(6, DEM_1BYTE)
#define DEM_UDS_STATUS_WIR_MASK                  DEM_BIT_MASK(7, DEM_1BYTE)

/* Status bit0 testFailed  */
#define DEM_TEST_UDS_STATUS_TF(Status)       (((Status) & DEM_UDS_STATUS_TF) != 0)                                          
#define DEM_SET_UDS_STATUS_TF(Status)        ((uint8)((Status) | DEM_UDS_STATUS_TF))                                        
#define DEM_RESET_UDS_STATUS_TF(Status)      ((uint8)((Status) & DEM_UDS_STATUS_TF_MASK))                                   

/* Status bit1 testFailedThisOperationCycle */
#define DEM_TEST_UDS_STATUS_TFTOC(Status)    (((Status) & DEM_UDS_STATUS_TFTOC) != 0)                                       
#define DEM_SET_UDS_STATUS_TFTOC(Status)     ((uint8)((Status) | DEM_UDS_STATUS_TFTOC))                                     
#define DEM_RESET_UDS_STATUS_TFTOC(Status)   ((uint8)((Status) & DEM_UDS_STATUS_TFTOC_MASK))                                

/* Status bit2 pendingDTC */
#define DEM_TEST_UDS_STATUS_PDTC(Status)     (((Status) & DEM_UDS_STATUS_PDTC) != 0)                                        
#define DEM_SET_UDS_STATUS_PDTC(Status)      ((uint8)((Status) | DEM_UDS_STATUS_PDTC))                                      
#define DEM_RESET_UDS_STATUS_PDTC(Status)    ((uint8)((Status) & DEM_UDS_STATUS_PDTC_MASK))                                 

/* Status bit3 confirmedDTC */
#define DEM_TEST_UDS_STATUS_CDTC(Status)     (((Status) & DEM_UDS_STATUS_CDTC) != 0)                                        
#define DEM_SET_UDS_STATUS_CDTC(Status)      ((uint8)((Status) | DEM_UDS_STATUS_CDTC))                                      
#define DEM_RESET_UDS_STATUS_CDTC(Status)    ((uint8)((Status) & DEM_UDS_STATUS_CDTC_MASK))                                 

/* Status bit4 testNotCompletedSinceLastClear*/
#define DEM_TEST_UDS_STATUS_TNCSLC(Status)   (((Status) & DEM_UDS_STATUS_TNCSLC) != 0)                                      
#define DEM_SET_UDS_STATUS_TNCSLC(Status)    ((uint8)((Status) | DEM_UDS_STATUS_TNCSLC))                                    
#define DEM_RESET_UDS_STATUS_TNCSLC(Status)  ((uint8)((Status) & DEM_UDS_STATUS_TNCSLC_MASK))                               

/* Status bit5 testFailedSinceLastClear */
#define DEM_TEST_UDS_STATUS_TFSLC(Status)    (((Status) & DEM_UDS_STATUS_TFSLC) != 0)                                       
#define DEM_SET_UDS_STATUS_TFSLC(Status)     ((uint8)((Status) | DEM_UDS_STATUS_TFSLC))                                     
#define DEM_RESET_UDS_STATUS_TFSLC(Status)   ((uint8)((Status) & DEM_UDS_STATUS_TFSLC_MASK))                                

/* Status bit6 testNotCompletedThisOperationCycle*/
#define DEM_TEST_UDS_STATUS_TNCTOC(Status)   (((Status) & DEM_UDS_STATUS_TNCTOC) != 0)                                       
#define DEM_SET_UDS_STATUS_TNCTOC(Status)    ((uint8)((Status) | DEM_UDS_STATUS_TNCTOC))                                     
#define DEM_RESET_UDS_STATUS_TNCTOC(Status)  ((uint8)((Status) & DEM_UDS_STATUS_TNCTOC_MASK))                                

/* Status bit7 warningIndicatorRequested */
#define DEM_TEST_UDS_STATUS_WIR(Status)      (((Status) & DEM_UDS_STATUS_WIR) != 0)                                          
#define DEM_SET_UDS_STATUS_WIR(Status)       ((uint8)((Status) | DEM_UDS_STATUS_WIR))                                        
#define DEM_RESET_UDS_STATUS_WIR(Status)     ((uint8)((Status) & DEM_UDS_STATUS_WIR_MASK))                                   


#define DEM_EVENT_PRIORITY_INVALID            0xFF/*should be 0*/
#define DEM_EVENT_IDENTIFIER_INVALID          0xFFFF/*should be 0*/


/* Forward declarations of local functions. */

STATIC boolean Dem_CreatEventMemoryEntry(Dem_EventIdType EventId,Dem_EventMemoryEntryType** pMemEntry);
STATIC boolean Dem_GetEventMemoryEntry(Dem_EventIdType EventId,Dem_EventMemoryEntryType** pMemEntry);
STATIC void Dem_StoreEventData(Dem_EventIdType EventId);
STATIC void Dem_StoreFreezeFrame(Dem_EventIdType EventId,uint8 Entry);
STATIC void Dem_SetIndicatiorStatus(Dem_EventIdType EventId);
STATIC Std_ReturnType Dem_DataCopy(uint8* Dest,const uint8* Src,uint16 Cnt);
STATIC boolean  Dem_EnableDtcSetting=FALSE;
                                                     

/* Internal variable definitions.*/
/*STATIC*/ 
Dem_StorageMemType DemStorageMem;
STATIC Dem_DtcStatusInfoType Dem_DtcStatusInfo[DEM_NUMBER_OF_DTC];


STATIC CONST(Dem_EventMemoryHeadType,DEM_CONST) EventMemoryHeadInit = 
{
    /*0,0,*/DEM_RESTOREFLAG0,DEM_RESTOREFLAG1,0,0,0,0
};
STATIC CONST(Dem_EventStatusInfoType,DEM_CONST) EventStatusInfoInit = 
{
    0,0x50,0x50,0,0,0,0
};
STATIC CONST(Dem_DtcStatusInfoType,DEM_CONST) Dem_DtcStatusInfoInit =
{
    0x50,0,0,0
};

STATIC uint16 Dem_EventFFMemOffset[DEM_NUMBER_OF_EVENT][DEM_CFG_MAXNUMBEROFRECORDNUMBER];
STATIC uint16 Dem_EventFFDataLen[DEM_NUMBER_OF_EVENT][DEM_CFG_MAXNUMBEROFRECORDNUMBER];
STATIC uint16 Dem_EventFFRecdLen[DEM_NUMBER_OF_EVENT][DEM_CFG_MAXNUMBEROFRECORDNUMBER];
STATIC uint16 Dem_EventExtDataLen[DEM_NUMBER_OF_EVENT][DEM_CFG_MAXNUMBEROFEXTENDEDNUM];
STATIC uint16 Dem_EventExtRecdLen[DEM_NUMBER_OF_EVENT][DEM_CFG_MAXNUMBEROFEXTENDEDNUM];
STATIC uint16 DemState;
STATIC uint8 Dem_SaveEvStReqFlag[(uint8)(DEM_NUMBER_OF_EVENT/8)+1]={0};
STATIC uint8 Dem_EventCaptureFlag[(uint8)(DEM_NUMBER_OF_EVENT/8)+1]={0};
STATIC uint16   EventInfoId = 0;
STATIC uint16   EventCaptureId = 0;
STATIC uint16   ClrDTCCounter = 0;
STATIC uint16   CaptureFlagByte = 0;
STATIC Dem_ClearDTCInfoType Dem_ClearDTCInfo;
STATIC uint8    Dem_DTCStatusMask=DEM_STATUS_AVAILABILITY_MASK;
STATIC Dem_DTCFilterInfoType Dem_DTCFilterInfo;
STATIC VAR(uint16, DEM_NOINIT_DATA) Dem_QueueCyclePendingState;
STATIC VAR(uint16, DEM_NOINIT_DATA) Dem_QueueCyclePendingFlag;   
STATIC VAR(uint16, DEM_NOINIT_DATA) Dem_CurrentCycleState;


STATIC FUNC(boolean, DEM_CODE)  Dem_CounterBasedDebounce
(
    Dem_EventIdType  EventId,
    Dem_DebounceInfoType*  DebounceInfo
);
STATIC const Dem_DebounceFunctionTableType Dem_DebounceFunctionTable[3] =                                    
{                                                                                            
    {&Dem_CounterBasedDebounce},
    {NULL_PTR},
    {NULL_PTR}
};
STATIC boolean Dem_GetCaptureQueue(Dem_EventIdType EventId)
{
    uint16 byteidx = 0;
    uint16 bitidx = 0;
    boolean ret = FALSE;

    byteidx = EventId/8;
    bitidx = EventId%8;

    if(Dem_EventCaptureFlag[byteidx]&((uint8)(1u<<bitidx)))
    {
        ret = TRUE;
    }

    return ret;
}

STATIC boolean Dem_SetCaptureQueue(Dem_EventIdType EventId)
{
    uint16 byteidx = 0;
    uint16 bitidx = 0;

    byteidx = EventId/8;
    bitidx = EventId%8;
    Dem_EventCaptureFlag[byteidx]|=(uint8)(1u<<bitidx);

    return TRUE;
}

STATIC boolean Dem_ClrCaptureQueue(Dem_EventIdType EventId)
{
    uint16 byteidx = 0;
    uint16 bitidx = 0;

    
    byteidx = EventId/8;
    bitidx = EventId%8;
    Dem_EventCaptureFlag[byteidx]^=(uint8)(1u<<bitidx);

    return TRUE;
}

/*TBD*/
STATIC boolean Dem_CheckEventStQueueByte(Dem_EventIdType EventId)
{
    return TRUE;
}
/*TBD*/
STATIC boolean Dem_CheckEventStQueueBit(Dem_EventIdType EventId)
{
    return TRUE;
}

STATIC boolean Dem_CreatEventMemoryEntry(Dem_EventIdType EventId,Dem_EventMemoryEntryType** pMemEntry)
{
    uint16 i;
    boolean boolret = FALSE;

    for(i = 0;i<DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY;i++)
    {
        if((DEM_EVENT_IDENTIFIER_INVALID == DemStorageMem.EventMemoryEntry[i].EmEventId)||\
			(EventId == DemStorageMem.EventMemoryEntry[i].EmEventId))
        {
            *pMemEntry = &DemStorageMem.EventMemoryEntry[i];
            boolret = TRUE;
            break;
        }
    
    }

    return boolret;
}

STATIC boolean Dem_GetEventMemoryEntry(Dem_EventIdType EventId,Dem_EventMemoryEntryType** pMemEntry)
{
    /*The event memory is full,new event has occured*/
    /* Event stored with displacement: 1. Priority 2. Status (active/passive) 3. Occurrence*/  
    uint16 i;
    boolean boolret = FALSE;

    if(EventId != DEM_EVENT_IDENTIFIER_INVALID)
    {
        for(i = 0;i<DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY;i++)
        {
            if(EventId == DemStorageMem.EventMemoryEntry[i].EmEventId)
            {
                *pMemEntry = &DemStorageMem.EventMemoryEntry[i];
                boolret = TRUE;
                break;
            }
        
        }
    }

    return boolret;
}


STATIC Std_ReturnType Dem_GetFaultOccurCounterAddr(uint16 evidx,uint8** src)
{
    *src = &DemStorageMem.EventExtendStatus[evidx].ucFaultOccurCounter;
    return E_OK;
}
STATIC Std_ReturnType Dem_GetFaultPendingCounterAddr(uint16 evidx,uint8** src)
{
    *src = &DemStorageMem.EventExtendStatus[evidx].ucFaultPendingCounter;
    return E_OK;
}
STATIC Std_ReturnType Dem_GetAgedCounterAddr(uint16 evidx,uint8** src)
{
    *src = &DemStorageMem.EventExtendStatus[evidx].ucAgedCounter;
    return E_OK;
}

STATIC Std_ReturnType Dem_GetAgingCounterAddr(uint16 evidx,uint8** src)
{
    *src = &DemStorageMem.EventExtendStatus[evidx].ucAgingCounter;
    return E_OK;
}
STATIC void Dem_StorageDataProcess
(
    Dem_DataElementClassType det,
    uint16 dei,
    uint8** ppBuff,
    uint16 evnidx
)
{ 
    switch(det)
    {
        case DemInternal:
            /*TBD*/ /*FF*/
        {
            uint8* src;
            uint8  len = 0;
            Std_ReturnType ret = E_NOT_OK;

            len = DemInternalDataElementClassTab[dei].DemDataElementDataSize;
            
            if(DemInternalDataElementClassTab[dei].DemInternalDataElement == DEM_OCCCTR)
            {
                ret = Dem_GetFaultOccurCounterAddr(evnidx,&src);
            }
            else if(DemInternalDataElementClassTab[dei].DemInternalDataElement == DEM_AGINGCTR)
            {
                ret = Dem_GetAgingCounterAddr(evnidx,&src);
            }
            else if(DemInternalDataElementClassTab[dei].DemInternalDataElement == DEM_AGEDCTR)
            {
                ret = Dem_GetAgedCounterAddr(evnidx,&src);
            }
            else if(DemInternalDataElementClassTab[dei].DemInternalDataElement == DEM_PENDINFCTR)
            {
                ret = Dem_GetFaultPendingCounterAddr(evnidx,&src);
            }
            else
            {
            }
            if(E_OK == ret)
            {   
                Dem_DataCopy(*ppBuff,src,len); 
            }
            *ppBuff += len;
        break;
        }
        case DemExternalCS:
            /**/
            if(NULL_PTR != Dem_ExternalCSDataElementClassTab[dei].DemDataElementReadFnc)
            {
                if((0u == dei) || (1u == dei)) /*故障发生时间，故障结束时间需特殊处理*/
                {
                    if(DEM_TEST_UDS_STATUS_CDTC(Dem_GetEventCurrentStatus(evnidx)))  /*wen  add*/
                    {
                        /*故障发生,结束时间不更新*/
                        if(1u == dei)
                        {
                            (void)(*Dem_ExternalCSDataElementClassTab[dei].DemDataElementReadFnc)\
                                (0u,*ppBuff);
                        }
                        else
                        {
                            (void)(*Dem_ExternalCSDataElementClassTab[dei].DemDataElementReadFnc)\
                                (Dem_ExternalCSDataElementClassTab[dei].DemDataElementDataSize,*ppBuff);
                        }
                    }
                    else
                    {
                        /*故障结束,发生时间不更新*/
                        if(0u == dei)
                        {
                            (void)(*Dem_ExternalCSDataElementClassTab[dei].DemDataElementReadFnc)\
                                (0u,*ppBuff);
                        }
                        else
                        {
                            (void)(*Dem_ExternalCSDataElementClassTab[dei].DemDataElementReadFnc)\
                                (Dem_ExternalCSDataElementClassTab[dei].DemDataElementDataSize,*ppBuff);
                        }
                    }
                }
                else
                {
                    (void)(*Dem_ExternalCSDataElementClassTab[dei].DemDataElementReadFnc)\
                        (Dem_ExternalCSDataElementClassTab[dei].DemDataElementDataSize,*ppBuff);
                }


                *ppBuff = *ppBuff + Dem_ExternalCSDataElementClassTab[dei].DemDataElementDataSize;
            }
        break;   
        case DemExternalSR:
            /*TBD*/
            if(NULL_PTR != Dem_ExternalSRDataElementClassTab[dei].DemDataElementAddr)
            {
                uint16 lop;

                for(lop = 0;lop < Dem_ExternalSRDataElementClassTab[dei].DemDataElementDataSize;lop++)
                {
                    **ppBuff = *(lop + Dem_ExternalSRDataElementClassTab[dei].DemDataElementAddr);
                     ++(*ppBuff);
                }
            }
        break;
        default:

        break;
    }
}

STATIC boolean Dem_CaptureFreezeFrame(Dem_EventIdType EventId)
{
    uint16 NumRecNum;/**/
    uint16 NumOfDID;/**/
    uint16 i,j,k;
    Dem_EventMemoryEntryType* _pMemEntry;
    uint8* _pBuff;
    uint16 did;
    Dem_DataElementClassType det;/*Data element type*/
    uint16 dei;/*data element index*/
    boolean rt = TRUE;
    const Dem_DidClassType* pdidclass;
    const Dem_ExtendedDataElementType* pextdata;
    
    if(TRUE == Dem_CreatEventMemoryEntry(EventId,&_pMemEntry))
    {
        _pMemEntry->EmEventId = EventId;

        if(_pMemEntry->EventOccCnt < 0xFF)
        {
            ++_pMemEntry->EventOccCnt;
        }
            
        _pMemEntry->DTCNum = DemDTCClassSet[DemEventParameterTab[EventId].DemDTCClassRef].DemUdsDTC;
        /*Capture shapshot*/
        NumRecNum = DemFreezeFrameClassTab0[DemEventParameterTab[EventId].DemFreezeFrameClassRef].DemNumberOfRecordNum;
        /*if(_pMemEntry->EventOccCnt < DEM_MAX_OCCURRENCE_FF_STORAGE)*/
        {
            /*_pBuff = _pMemEntry->FreezeFrameData[_pMemEntry->EventOccCnt];*/ /*DEM_FF_RECNUM_CALCULATED*/
            _pBuff = _pMemEntry->FreezeFrameData;/* DEM_FF_RECNUM_CONFIGURED */
            
            for(i = 0;i<NumRecNum;i++)
            {
                NumOfDID = DemFreezeFrameClassTab0[DemEventParameterTab[EventId].DemFreezeFrameClassRef].DemFreezeFrameRecNumClassRef[i].DemSnapshotRecordNumberOfIdentifiers;
                pdidclass = DemFreezeFrameClassTab0[DemEventParameterTab[EventId].DemFreezeFrameClassRef].DemFreezeFrameRecNumClassRef[i].DemDidClassRef;

                for(j = 0;j<NumOfDID;j++)
                { 
                    det = pdidclass[j].DemDidDataElementClassRef;
                    dei = pdidclass[j].DemDataIndex;
                    Dem_StorageDataProcess(det,dei,&_pBuff,EventId);
                }
            }
        }

        /*Extended data*/
        NumRecNum = DemExtendedDataClassTab0[DemEventParameterTab[EventId].DemExtendedDataClassRef].DemNumberOfExtendRecNum;
        {
            /*_pBuff = _pMemEntry->FreezeFrameData[_pMemEntry->EventOccCnt];*/ /*DEM_FF_RECNUM_CALCULATED*/
            _pBuff = _pMemEntry->ExtendedData;
            for(i = 0;i<NumRecNum;i++)
            {
                NumOfDID = DemExtendedDataClassTab0[DemEventParameterTab[EventId].DemExtendedDataClassRef].DemExtendedDataRecordClassRef[i].DemExtendedRecordNumberOfIdentifiers;
                pextdata = DemExtendedDataClassTab0[DemEventParameterTab[EventId].DemExtendedDataClassRef].DemExtendedDataRecordClassRef[i].DemExtendedDataElement;


                for(j = 0;j<NumOfDID;j++)
                {
                    det = pextdata[j].DemDataElementClassRef;
                    dei = pextdata[j].DemDataIndex;
                    Dem_StorageDataProcess(det,dei,&_pBuff,EventId);               
                }
            }
        }
    }
    else
    {
        rt = FALSE;
    }
    return rt;
}
STATIC void Dem_EventMemHeadInit(void)
{
    DemStorageMem.EventMemoryHead = EventMemoryHeadInit;
}

STATIC void Dem_EventMemFFInit(void)
{
    uint16 i;
    
    for(i = 0;i<DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY;i++)
    {
        DemStorageMem.EventMemoryEntry[i].EmEventId =   DEM_EVENT_IDENTIFIER_INVALID;
        DemStorageMem.EventMemoryEntry[i].EventOccCnt = 0; 
		DemStorageMem.EventMemoryEntry[i].DTCNum = 0;
        /*DemStorageMem.EventMemoryEntry[i].EventPrio = DEM_EVENT_PRIORITY_INVALID;TBD*/
    }
}

STATIC void Dem_EventStatusInit(void)
{
    uint16 i;
    for(i = 0;i<DEM_NUMBER_OF_EVENT;i++)
    {
        DemStorageMem.EventExtendStatus[i] = EventStatusInfoInit;
    }
}
STATIC void Dem_DtcStatusInit(void)
{
    uint16 i;
    for(i = 0;i<DEM_NUMBER_OF_DTC;i++)
    {
        /*DemStorageMem.EventExtendStatus[i] = EventStatusInfoInit;*/
        Dem_DtcStatusInfo[i] = Dem_DtcStatusInfoInit;
    }
}

STATIC void Dem_DebounceInfoInit
(
    uint16 EventId, 
    Dem_DebounceInfoType* DebounceInfo
)
{
    uint8 DebounceAlgorithm;

    DebounceAlgorithm = DemDebounceAlgorithmClassTab[EventId].DemEventDebounceAlgorithm.DebounceAlgorithmRef;

    DebounceInfo->Common.Calculate = Dem_DebounceFunctionTable[DebounceAlgorithm].debCal;
}

STATIC Std_ReturnType L_DemGetEventRecNumIndex
(
    Dem_EventIdType EventId,
    uint8 RecordNumber, 
    uint8* Index/*out*/
) 
{
    uint8 i;
    uint16 NumRecNum;
    Std_ReturnType ret = E_NOT_OK;
    
    NumRecNum = DemFreezeFrameClassTab0[DemEventParameterTab[EventId].DemFreezeFrameClassRef].DemNumberOfRecordNum;

    for(i=0;i<NumRecNum;i++)
    {
        if(RecordNumber ==(((DemFreezeFrameClassTab0[DemEventParameterTab[EventId].DemFreezeFrameClassRef].DemFreezeFrameRecNumClassRef)+i)->DemFreezeFrameRecordNumber))
        {
            *Index = i;
            ret = E_OK;
            break;
        }
    }
    return ret;
}
STATIC FUNC(boolean, DEM_CODE) Dem_CounterBasedDebounce
(
    Dem_EventIdType          EventId,
    Dem_DebounceInfoType*  DebounceInfo
)
{
    uint8 loop;
    boolean result = TRUE;
    /*Init OldDebounceValue*/
    DebounceInfo->Specific.CounterBased.OldDebounceValue = DemStorageMem.EventExtendStatus[EventId].ssFCounterCB;
    /*Init NewDebounceValue*/
    DebounceInfo->Specific.CounterBased.NewDebounceValue = DemStorageMem.EventExtendStatus[EventId].ssFCounterCB;

    switch(DebounceInfo->Common.MonitorStatus)
    {
        case DEM_EVENT_STATUS_FAILED:

            DebounceInfo->Specific.CounterBased.NewDebounceValue = \
                DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterFailedThreshold;
            break;
        case DEM_EVENT_STATUS_PASSED:
            DebounceInfo->Specific.CounterBased.NewDebounceValue = \
                DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterPassedThreshold;
                  
            break;
        case DEM_EVENT_STATUS_PREFAILED:

            /*clear  counter*/
            if(DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterJumpUp == TRUE)
            {
                /*reach the pass level*/
                if(DebounceInfo->Specific.CounterBased.OldDebounceValue <= DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterPassedThreshold)
                {
                    DebounceInfo->Specific.CounterBased.NewDebounceValue = DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterJumpUpValue;
                }  
            }
            
            /* increase  Intermit failed counter*/
            if(DebounceInfo->Specific.CounterBased.NewDebounceValue >= DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterFailedThreshold)
            {
                DebounceInfo->Common.MonitorStatus = DEM_EVENT_STATUS_FAILED;
            }
            else
            {
                DebounceInfo->Specific.CounterBased.NewDebounceValue += DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterIncrementStepSize;
                if(DebounceInfo->Specific.CounterBased.NewDebounceValue >= DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterFailedThreshold)
                {
                    DebounceInfo->Common.MonitorStatus = DEM_EVENT_STATUS_FAILED;
                }
            }
            
            break;
        case DEM_EVENT_STATUS_PREPASSED:
            /*clear  counter*/
            if(DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterJumpDown == TRUE)
            {
                /*reach the failed level*/
                if(DebounceInfo->Specific.CounterBased.OldDebounceValue  >= DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterFailedThreshold)
                {
                    DebounceInfo->Specific.CounterBased.NewDebounceValue = DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterJumpDownValue;
                }                      
            }
            /* decrease counter passed counter*/
            if(DebounceInfo->Specific.CounterBased.NewDebounceValue <= DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterPassedThreshold)
            {
                DebounceInfo->Common.MonitorStatus = DEM_EVENT_STATUS_PASSED;
            }
            else
            {
                DebounceInfo->Specific.CounterBased.NewDebounceValue += DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterDecrementStepSize;
                if(DebounceInfo->Specific.CounterBased.NewDebounceValue <= DemDebounceAlgorithmClassTab[EventId].DemDebounceCounterBased.DemDebounceCounterPassedThreshold)
                {
                    DebounceInfo->Common.MonitorStatus = DEM_EVENT_STATUS_PASSED;
                }
            }
            break;
        default:
            result = FALSE;
            break;
    }

    return result;
}

STATIC void Dem_CycleStopProcess(Dem_OperationCycleIdType OperationCycleId)
{    
    uint16 EvnIdx;
    for(EvnIdx = 0; EvnIdx < DEM_NUMBER_OF_EVENT; EvnIdx++)
    {
        if(OperationCycleId == DemEventClassSet[EvnIdx].DemAgingCycleRef)
        {
            uint8 ucCurrentStat=0;

            if(TRUE == Dem_GetCaptureQueue(EvnIdx))
            {
#if(0)  /*wen modfidy  */                
                Dem_ClrCaptureQueue(EvnIdx);              
                (void)Dem_CaptureFreezeFrame(EvnIdx);
#endif                 
            }
        }
    }
}

STATIC void Dem_EventAgedProcess(uint16 evnidx)
{
    Dem_EventMemoryEntryType* _pMemEntry;
    if(TRUE == Dem_GetEventMemoryEntry(evnidx,&_pMemEntry))
    {
        _pMemEntry->DTCNum = 0;
        _pMemEntry->EmEventId = DEM_EVENT_IDENTIFIER_INVALID;
        /*_pMemEntry->EventPrio = DEM_EVENT_PRIORITY_INVALID; TBD*/
        _pMemEntry->EventOccCnt = 0;
    }
}
STATIC void Dem_CycleStartProcess(Dem_OperationCycleIdType OperationCycleId)
{    
    uint16 EvnIdx;
    for(EvnIdx = 0; EvnIdx < DEM_NUMBER_OF_EVENT; EvnIdx++)
    {
        if(OperationCycleId == DemEventClassSet[EvnIdx].DemAgingCycleRef)
        {
            uint8 llastEventStatus;
            uint8 lOldEventStatus; 
            uint8 lNewEventStatus;

            llastEventStatus = DemStorageMem.EventExtendStatus[EvnIdx].ucEvnLstStatus;
            /*save the current dtc status*/
            lOldEventStatus = Dem_GetEventCurrentStatus(EvnIdx);
            lNewEventStatus = lOldEventStatus;

            Dem_SetCounterBasedDebounceCounter(EvnIdx,0);

            /*BIT3_CONFIRMED_DTC*/
            if(DEM_TEST_UDS_STATUS_CDTC(lOldEventStatus))
            {
                if((!DEM_TEST_UDS_STATUS_TFTOC(lOldEventStatus))&&\
                    (!DEM_TEST_UDS_STATUS_TNCSLC(lOldEventStatus)))
                {
                    DemStorageMem.EventExtendStatus[EvnIdx].ucAgingCounter++;
                }
                else
                {   
                    DemStorageMem.EventExtendStatus[EvnIdx].ucAgingCounter = 0;
                }
                        
                if(DemStorageMem.EventExtendStatus[EvnIdx].ucAgingCounter >= DemEventClassSet[EvnIdx].DemAgingCycleCounterThreshold)
                {   
                    lNewEventStatus = DEM_RESET_UDS_STATUS_CDTC(lNewEventStatus);
                    Dem_EventAgedProcess(EvnIdx);
                    DemStorageMem.EventExtendStatus[EvnIdx].ucAgingCounter = 0;
                    if(DemStorageMem.EventExtendStatus[EvnIdx].ucAgedCounter < 0xFF)
                    {
                        DemStorageMem.EventExtendStatus[EvnIdx].ucAgedCounter++;
                    }
                }
                else
                {
                }

            }
            else
            {
            }
            /*BIT2_Pending_DTC*/
            if((DEM_TEST_UDS_STATUS_PDTC(llastEventStatus))&&\
                (DEM_TEST_UDS_STATUS_PDTC(lOldEventStatus)))
            {
                if((!DEM_TEST_UDS_STATUS_TFTOC(llastEventStatus))&&\
                (!DEM_TEST_UDS_STATUS_TNCSLC(llastEventStatus))&&\
                (!DEM_TEST_UDS_STATUS_TFTOC(lOldEventStatus))&&\
                (!DEM_TEST_UDS_STATUS_TNCSLC(lOldEventStatus)))
                {
                    lNewEventStatus = DEM_RESET_UDS_STATUS_PDTC(lNewEventStatus);
                    DemStorageMem.EventExtendStatus[EvnIdx].ucFaultPendingCounter = 0;
                }
                else
                {
                }

            }
            else
            {
            }
            /*clear bit0*/
            /*
            if(DTCStatusByteInfoCfg[usDTCIndex].ucStatusByteSwitch & DTC_STATUS_BIT0_TEST_FAILED)
            {
                DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT0_TEST_FAILED;
            }
            else
            {
            } 
            */
            /*clear bit1*/
            lNewEventStatus = DEM_RESET_UDS_STATUS_TFTOC(lNewEventStatus);
            /*if(DTCStatusByteInfoCfg[usDTCIndex].ucStatusByteSwitch & DTC_STATUS_BIT1_CYCLE_FAILED)
            {
                DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT1_CYCLE_FAILED;
            }
            else
            {
            }*/
            /*set bit6*/
            lNewEventStatus = DEM_SET_UDS_STATUS_TNCTOC(lNewEventStatus);
            /*if(DTCStatusByteInfoCfg[usDTCIndex].ucStatusByteSwitch & DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE)
            {
                DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE;
            }
            else
            {
            }*/
            /*save the current DTC as the last operation cycle status*/
            DemStorageMem.EventExtendStatus[EvnIdx].ucEvnLstStatus = lOldEventStatus;
            Dem_SetEventCurrentStatus(EvnIdx,lNewEventStatus);
    
            if(DemEventParameterTab[EvnIdx].DemDTCClassRef < DEM_NUMBER_OF_DTC)
            {
                Dem_DtcStatusInfo[DemEventParameterTab[EvnIdx].DemDTCClassRef].DtcStatus = lNewEventStatus;
            }
    
        }
    }

}

STATIC FUNC(uint8, DEM_CODE)
Dem_GetCurrentCycleStatus(uint8  CycleId)
{
  return (uint8)(((Dem_CurrentCycleState & (uint16)(1U << (CycleId))) != 0)?DEM_QUEUE_CYCLE_STARTED:DEM_QUEUE_CYCLE_STOPPED);
}
/*****************************************************************************

 *****************************************************************************/
STATIC FUNC(void, DEM_CODE)                                                                                          
Dem_SetCurrentCycleStatus(
    uint8  CycleId,
    uint8  Status
)
{
  uint16 lMask;

  lMask = (uint16)(1U << CycleId);
  if (DEM_QUEUE_CYCLE_STOPPED == Status)
  {
    lMask = (uint16)~lMask;
    Dem_CurrentCycleState = (uint16)(Dem_CurrentCycleState & lMask);
  }
  else
  {
    Dem_CurrentCycleState = (uint16)(Dem_CurrentCycleState | lMask);
  }
}

STATIC FUNC(void, DEM_CODE)
Dem_Queue_ProcessCycles(void)
{
    uint8 lCycleId;
    uint16 lQueueCycleState;
    uint16 lQueueCycleFlag;

    Dem_DisableInterrupt();

    lQueueCycleState = Dem_QueueCyclePendingState;
    Dem_QueueCyclePendingState = 0U;

    lQueueCycleFlag = Dem_QueueCyclePendingFlag;
    Dem_QueueCyclePendingFlag = 0U;

    lCycleId = 0;
    while (0 != lQueueCycleFlag)
    {
        if ((lQueueCycleFlag & 0x01U) != 0)
        {
            uint8 lNewStatus;
            uint8 lOldStatus;
            lNewStatus = (uint8)(((lQueueCycleState & 0x01U) != 0)?DEM_QUEUE_CYCLE_STARTED:DEM_QUEUE_CYCLE_STOPPED);
            lOldStatus = Dem_GetCurrentCycleStatus(lCycleId);
            if(DEM_QUEUE_CYCLE_STARTED == lNewStatus)
            {

                if (lNewStatus == lOldStatus)
                {
                    /* TBD  Dem_Esm_CycleUpdate(lCycleId, DEM_QUEUE_CYCLE_RESTARTED);*/
                }
                else
                {
                    Dem_CycleStartProcess(lCycleId);
                    Dem_SetCurrentCycleStatus(lCycleId,DEM_QUEUE_CYCLE_STARTED);
                }
            }
            else/*new : DEM_QUEUE_CYCLE_STOPPED*/
            {
                if (lNewStatus != lOldStatus)
                {
                    Dem_CycleStopProcess(lCycleId);
                    Dem_SetCurrentCycleStatus(lCycleId,DEM_QUEUE_CYCLE_STOPPED);
                }
            }
        }
        ++lCycleId;
        lQueueCycleFlag = (uint16)(lQueueCycleFlag >> 1U);
        lQueueCycleState = (uint16)(lQueueCycleState >> 1U);
    }
    Dem_SetDemState(DEM_NORMAL);/*may be deleted?*/
    Dem_EnableInterrupt();
}

STATIC FUNC(void, DEM_CODE)                                                                                            
Dem_Queue_SetPendingCycle(
  uint8  CycleId,
  uint8  Status
  )
{
  uint16 lMask = (uint16)(1U << CycleId);

  Dem_QueueCyclePendingFlag = (uint16)(Dem_QueueCyclePendingFlag | lMask);

  if (DEM_QUEUE_CYCLE_STOPPED == Status)
  {
    lMask = (uint16)~lMask;
    Dem_QueueCyclePendingState = (uint16)(Dem_QueueCyclePendingState & lMask);
  }
  else
  {
    Dem_QueueCyclePendingState = (uint16)(Dem_QueueCyclePendingState | lMask);
  }
}


STATIC FUNC(boolean, DEM_CODE)                                                                                        
Dem_Queue_GetPendingCycle(
  uint8  CycleId
  )
{
  return (boolean)(((Dem_QueueCyclePendingState & (uint16)(1U << CycleId)) != 0U)
                     ? DEM_QUEUE_CYCLE_STARTED
                     : DEM_QUEUE_CYCLE_STOPPED);
}

STATIC Std_ReturnType L_DemGetEventFFRecdIndx
(
    uint16 evnidx,
    uint8 recdnum,
    uint16* recdidx
)
{
    uint16 num;
    const Dem_FreezeFrameRecNumClassType* pffrec;
    Std_ReturnType ret = E_NOT_OK;
    uint16 i;
    
    if(recdnum != 0xFF)
    {
        pffrec = DemFreezeFrameClassTab0[DemEventParameterTab[evnidx].DemFreezeFrameClassRef].DemFreezeFrameRecNumClassRef;
        
        num = DemFreezeFrameClassTab0[DemEventParameterTab[evnidx].DemFreezeFrameClassRef].DemNumberOfRecordNum;
        
        for(i = 0;i<num;i++)
        {
            if(recdnum == pffrec->DemFreezeFrameRecordNumber)
            {
                *recdidx = i;
                ret = E_OK;
                break;
            }
            pffrec++;
        }
    }

    return ret;
}
STATIC Std_ReturnType L_DemGetEventExtRecdIndx
(
    uint16 evnidx,
    uint8 recdnum,
    uint16* recdidx
)
{
    uint16 num;
    const Dem_ExtendedDataRecordClassType* pffrec;
    Std_ReturnType ret = E_NOT_OK;
    uint16 i;
    if(recdnum != 0xFF)
    {
        pffrec = DemExtendedDataClassTab0[DemEventParameterTab[evnidx].DemExtendedDataClassRef].DemExtendedDataRecordClassRef;
        
        num = DemExtendedDataClassTab0[DemEventParameterTab[evnidx].DemExtendedDataClassRef].DemNumberOfExtendRecNum;
        
        for(i = 0;i<num;i++)
        {
            if(recdnum == pffrec->DemExtendedDataRecordNumber)
            {
                *recdidx = i;
                ret = E_OK;
                break;
            }
            pffrec++;
        }
    }

    return ret;
}

/*struct:{RecordNumber,NumOfDIDs, DID[1], data[1], ..., DID[N],data[N]}*/
STATIC uint16 Dem_GetEventFFRecdLength
(
    uint16 evnidx,
    uint8 recdnum,
    uint16 recdidx
)
{
    uint16 length;
    uint16 i;

    length = 0;

    if(0xFF != recdnum)
    {
        length = Dem_EventFFRecdLen[evnidx][recdidx]; 
    }
    else
    {
        for(i = 0;i<DEM_CFG_MAXNUMBEROFRECORDNUMBER;i++)
        {
            length += Dem_EventFFRecdLen[evnidx][i]; 
        }
    }
    return length;
}
STATIC uint16 Dem_GetEventExtRecdLength
(
    uint16 evnidx,
    uint8 recdnum,
    uint16 recdidx
)
{
    uint16 length;
    uint16 i;

    length = 0;

    if(0xFF != recdnum)
    {
        length = Dem_EventExtRecdLen[evnidx][recdidx]; 
    }
    else
    {
        for(i = 0;i<DEM_CFG_MAXNUMBEROFEXTENDEDNUM;i++)
        {
            length += Dem_EventExtRecdLen[evnidx][i]; 
        }
    }
    return length;
}


STATIC uint16 Dem_GetEventExtDataLength
(
    uint16 evnidx,
    uint8 recdnum,
    uint16 recdidx
)
{
    uint16 length;
    uint16 i;

    length = 0;

    if(0xFF != recdnum)
    {
        length = Dem_EventExtDataLen[evnidx][recdidx]; 
    }
    else
    {
        for(i = 0;i<DEM_CFG_MAXNUMBEROFEXTENDEDNUM;i++)
        {
            length += Dem_EventExtDataLen[evnidx][i]; 
        }
    }
    return length;
}

STATIC void L_Dem_GetEventFFRecdBuffOffset
(
    uint16 recdidx,
    uint16 eveidx,
    uint16*ofst
)
{
    uint16 i;
    *ofst = 0;
    for(i = 0;i<recdidx;i++)
    {
        *ofst += Dem_EventFFDataLen[eveidx][i];
    }

}
STATIC void L_Dem_GetEventExtRecdBufferOffset
(
    uint16 recdidx,
    uint16 eveidx,
    uint16*ofst
)
{
    uint16 i;
    *ofst = 0;

    for(i = 0;i<recdidx;i++)
    {
        *ofst += Dem_EventExtDataLen[eveidx][i];
    }
}

STATIC uint16 Dem_GetEventMemEntryIndexByDTC(uint32 dtc)
{
    uint16 entry;
    /*search the DTC in DemStorageMem*/
    for (entry = 0; entry < DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY; entry++)
    {
        if((DemStorageMem.EventMemoryEntry[entry].DTCNum == dtc)&&\
		   (DemStorageMem.EventMemoryEntry[entry].EmEventId != DEM_EVENT_IDENTIFIER_INVALID))
            break;
    }
    return entry;
}
STATIC Std_ReturnType Dem_CheckDtcValid(uint32 DTC,uint16* dtcidx)
{
    uint16 i;
    Std_ReturnType ret = E_NOT_OK;
    for(i = 0;i<DEM_NUMBER_OF_DTC;i++)
    {
        if(DTC == DemDTCClassSet[i].DemUdsDTC)
        {
            *dtcidx = i;
            ret = E_OK;
            break;
        }
    }
    return ret;
}
STATIC Std_ReturnType L_DemGetDataElementSize
(
    Dem_DataElementClassType eleref,
    uint8* size,
    uint16 index
)
{
    Std_ReturnType ret = E_OK;

    switch(eleref)
    {
        case DemInternal:
        /*TBD*/
        break;
        case DemExternalCS:
        /**/
        *size = Dem_ExternalCSDataElementClassTab[index].DemDataElementDataSize;

        break;   
        case DemExternalSR:
        /*TBD*/
        *size = Dem_ExternalSRDataElementClassTab[index].DemDataElementDataSize;
        break;
        default:
            ret = E_NOT_OK;

        break;
    }

    return ret;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.2 Interface ECU State Manager
************************************************************************************************
END_FUNCTION_HDR */
#if 0
void Dem_PreInit( 
    const Dem_ConfigType* ConfigPtr 
)
{

}
#endif
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.2 Interface ECU State Manager
************************************************************************************************
END_FUNCTION_HDR */
void Dem_Init(void)
{
    uint16 i,j,k,numofrcd,numofdid;
    Dem_EventIdType eventId;
    Std_ReturnType ret;
    uint8 datsize=0;

    Dem_SetDemState(DEM_UNINIT);

    /*add init */
    Dem_EnableDtcSetting = TRUE;
    Dem_DTCStatusMask=DEM_STATUS_AVAILABILITY_MASK;

    Dem_DTCFilterInfo.FilteredValidFlag = FALSE;

    for(i = 0;i<DEM_NUMBER_OF_EVENT;i++)
    {
        for(j=0;j<DEM_CFG_MAXNUMBEROFRECORDNUMBER;j++)
        {
            Dem_EventFFDataLen[i][j]=0;
            Dem_EventFFRecdLen[i][j]=0;
        }
        for(k=0;k<DEM_CFG_MAXNUMBEROFEXTENDEDNUM;k++)
        {
            Dem_EventExtDataLen[i][k]=0;
            Dem_EventExtRecdLen[i][k]=0;
        }
    }
     
    for(i = 0;i<DEM_NUMBER_OF_EVENT;i++)
    {
        const Dem_DidClassType* pdidclass;
        const Dem_FreezeFrameRecNumClassType* pffrcdclass;

        numofrcd = DemFreezeFrameClassTab0[DemEventParameterTab[i].DemFreezeFrameClassRef].DemNumberOfRecordNum;
        pffrcdclass = DemFreezeFrameClassTab0[DemEventParameterTab[i].DemFreezeFrameClassRef].DemFreezeFrameRecNumClassRef;
        
        for(j=0;j<numofrcd;j++)
        {
            numofdid  = pffrcdclass->DemSnapshotRecordNumberOfIdentifiers;
            pdidclass = pffrcdclass->DemDidClassRef;
            
            for(k=0;k<numofdid;k++)
            {
                (void)L_DemGetDataElementSize(pdidclass->DemDidDataElementClassRef,&datsize,pdidclass->DemDataIndex);
                Dem_EventFFDataLen[i][j] += datsize;
                Dem_EventFFRecdLen[i][j] += 2u;/*DID byteH byteL*/
                pdidclass++;
            }
            Dem_EventFFRecdLen[i][j] += (2u+Dem_EventFFDataLen[i][j]);
            pffrcdclass++;
        }
    }

    for(i = 0;i<DEM_NUMBER_OF_EVENT;i++)
    {
        const Dem_ExtendedDataElementType* pExtendedData;
        const Dem_ExtendedDataRecordClassType*pffrcdclass;

        numofrcd = DemExtendedDataClassTab0[DemEventParameterTab[i].DemExtendedDataClassRef].DemNumberOfExtendRecNum;
        pffrcdclass = DemExtendedDataClassTab0[DemEventParameterTab[i].DemExtendedDataClassRef].DemExtendedDataRecordClassRef;

        for(j=0;j<numofrcd;j++)
        {
            numofdid  = pffrcdclass->DemExtendedRecordNumberOfIdentifiers;
            pExtendedData = pffrcdclass->DemExtendedDataElement;
            for(k=0;k<numofdid;k++)
            {
                (void)L_DemGetDataElementSize(pExtendedData->DemDataElementClassRef,&datsize,pExtendedData->DemDataIndex);
                Dem_EventExtDataLen[i][j] += datsize;
                pExtendedData++;
            }
            Dem_EventExtRecdLen[i][j] += (1u+Dem_EventExtDataLen[i][j]);
            pffrcdclass++;
        }
    }


    Dem_QueueCyclePendingState = 0;  
    Dem_QueueCyclePendingFlag = 0;   
    Dem_CurrentCycleState = 0;


    Dem_ClearDTCInfo.cleartyp = DEM_INTER_CLRNONE;
    Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_DTC_IDLE;

    Dem_SetDemState(DEM_INITPENDING);

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.2 Interface ECU State Manager
************************************************************************************************
END_FUNCTION_HDR */
void Dem_Shutdown(void)
{
    uint16 i;
    uint16 j;


    uint16 ldemstate;
    Std_ReturnType ucRet = E_OK;
    

    Dem_DisableInterrupt();
    Dem_GetDemState(ldemstate);
    Dem_EnableInterrupt();

    if(!Dem_CheckDemState(ldemstate,DEM_STATVALIDEMASK))
    {
        return;
    }

    if(!(Dem_CheckDemState(ldemstate,DEM_SHUTDOWN)))
    {
        j = (8u*(sizeof(Dem_QueueCyclePendingState)));
        Dem_DisableInterrupt();
        for(i = 0;i<j;i++)
        {Dem_Queue_SetPendingCycle(i,DEM_QUEUE_CYCLE_STOPPED);}
        Dem_Queue_ProcessCycles();
        Dem_SetDemState(DEM_SHUTDOWN);/*must be here*/
        Dem_EnableInterrupt();
    }
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
void Dem_ReportErrorStatus( 
    Dem_EventIdType EventId, 
    Dem_EventStatusType EventStatus 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
FUNC(Std_ReturnType, DEM_CODE)Dem_SetEventStatus
(
    Dem_EventIdType     EventId,                                                                                                      
    Dem_EventStatusType EventStatus
)
{   
    boolean testFailed;
    Dem_EventStatusExtendedType oldStatus; 
    uint8 lOldEventStatus;
    uint8 lNewEventStatus;
  
    uint8 ChangeFlagIndex=0;
    uint8 DebounceAlgorithm=0;

    Dem_DebounceInfoType pDebounceInfo;
    Std_ReturnType ret = E_NOT_OK;

    uint16 ldemstate;


    Dem_DisableInterrupt();
    Dem_GetDemState(ldemstate);
    Dem_EnableInterrupt();
    
    /* Save old Status <-> compare with trigger functions */ 
    /*oldStatus = Dem_Events[EventId].DtcStatus;*/
    /* Get TestFailed (bit 0) from extended status. */
    /*testFailed = Dem_Events[EventId].DtcStatus & DEM_BIT0;*/
    /* Use counter based predebouncing algorithm from DEM? */


//    if(!Dem_CheckDemState(ldemstate,DEM_NORMAL))
//        return E_NOT_OK;
    if(Dem_EnableDtcSetting != TRUE)
        return E_NOT_OK;
    if(Dem_ClearDTCInfo.cleartyp != DEM_INTER_CLRNONE)
        return E_NOT_OK;
    /*
    lNewEventStatus = Dem_EventGetStatus(EventId);*/
    lOldEventStatus = Dem_GetEventCurrentStatus(EventId);
    lNewEventStatus = lOldEventStatus;

    if((Dem_GetCurrentCycleStatus(Dem_GetEventOperationCycleId(EventId)) == DEM_QUEUE_CYCLE_STARTED)&&(EventId < DEM_NUMBER_OF_EVENT))
    {
        Dem_DebounceInfoInit(EventId,&pDebounceInfo);
        pDebounceInfo.Common.MonitorStatus = EventStatus;
        
        if(TRUE == (*(pDebounceInfo.Common.Calculate))(EventId,&pDebounceInfo))
        {  
            if(pDebounceInfo.Common.MonitorStatus == DEM_EVENT_STATUS_FAILED)
            {
                /*snapshot and extended data*/
        
                lNewEventStatus = DEM_SET_UDS_STATUS_TF(lNewEventStatus);
                lNewEventStatus = DEM_SET_UDS_STATUS_TFTOC(lNewEventStatus);
                lNewEventStatus = DEM_SET_UDS_STATUS_PDTC(lNewEventStatus);
                /*lNewEventStatus = DEM_SET_UDS_STATUS_CDTC(lNewEventStatus);*/
                lNewEventStatus = DEM_SET_UDS_STATUS_TFSLC(lNewEventStatus);
                lNewEventStatus = DEM_RESET_UDS_STATUS_TNCSLC(lNewEventStatus);
                lNewEventStatus = DEM_RESET_UDS_STATUS_TNCTOC(lNewEventStatus);

                if((DEM_TEST_UDS_STATUS_TF(lNewEventStatus))&&(!DEM_TEST_UDS_STATUS_TF(lOldEventStatus)))
                {
                    /*(void)Dem_CaptureFreezeFrame(EventId);*/
                    (void)Dem_SetCaptureQueue(EventId);

                    if(DemStorageMem.EventExtendStatus[EventId].ucFaultOccurCounter<0xFF)
                    {
                        ++DemStorageMem.EventExtendStatus[EventId].ucFaultOccurCounter;
                    }

                    if(DemStorageMem.EventExtendStatus[EventId].ucFaultPendingCounter < DemEventClassSet[EventId].DemEventFailureCycleCounterThreshold)
                    {
                        ++DemStorageMem.EventExtendStatus[EventId].ucFaultPendingCounter;
                        if(DemStorageMem.EventExtendStatus[EventId].ucFaultPendingCounter == DemEventClassSet[EventId].DemEventFailureCycleCounterThreshold)
                        {
                            lNewEventStatus = DEM_SET_UDS_STATUS_CDTC(lNewEventStatus);
                            /*DemStorageMem.EventExtendStatus[EventId].ucAgingCounter = 0;*/
                        }
                    }
                }
            }
            else if(pDebounceInfo.Common.MonitorStatus == DEM_EVENT_STATUS_PASSED)
            {
                lNewEventStatus = DEM_RESET_UDS_STATUS_TF(lNewEventStatus);
                lNewEventStatus = DEM_RESET_UDS_STATUS_TNCSLC(lNewEventStatus);
                lNewEventStatus = DEM_RESET_UDS_STATUS_TNCTOC(lNewEventStatus);
            }
            else
            {

            }
            Dem_DisableInterrupt();

            Dem_SetEventCurrentStatus(EventId,lNewEventStatus);
            /*updata DTC status byte*/
            Dem_DtcStatusInfo[DemEventParameterTab[EventId].DemDTCClassRef].DtcStatus = lNewEventStatus;

            /* Write back counter. */
            Dem_SetCounterBasedDebounceCounter(EventId,pDebounceInfo.Specific.CounterBased.NewDebounceValue);   
            Dem_EnableInterrupt();
            ret = E_OK;
        }
    }
    
    return ret;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventStatus
(
    Dem_EventIdType  EventId                                                                                                     
)
{
    Std_ReturnType ret = E_NOT_OK;
    Std_ReturnType lReturnValue;
    uint8 lOldEventStatus;
    uint8 lNewEventStatus;

    lOldEventStatus = Dem_GetEventCurrentStatus(EventId);

    if ((Dem_EnableDtcSetting == TRUE)&&\
        (DEM_TEST_UDS_STATUS_TNCTOC(lOldEventStatus)))
    {   /* DTC setting is enabled, proceed */
        lNewEventStatus = DEM_RESET_UDS_STATUS_TF(lOldEventStatus);

        Dem_SetEventCurrentStatus(EventId, lNewEventStatus);
        /* Reset debounce counter. */
        Dem_SetCounterBasedDebounceCounter(EventId,0);
    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_PrestoreFreezeFrame( 
    Dem_EventIdType EventId 
)
{
    return E_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_ClearPrestoredFreezeFrame( 
    Dem_EventIdType EventId 
) 
{
    return E_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetOperationCycleState
(
    uint8  OperationCycleId,                                                                                                       
    Dem_OperationCycleStateType  CycleState
)
{
    Std_ReturnType lReturnValue;
    boolean lPendingCycleStatus;
    uint16 ldemstate;

    lReturnValue = E_OK;

    Dem_DisableInterrupt();

    do
    {
        Dem_GetDemState(ldemstate);
        if(!Dem_CheckDemState(ldemstate,DEM_NORMAL))
        {
            lReturnValue = E_NOT_OK;
            break;
        }
        
        if (FALSE != Dem_Queue_IsPendingCycle(OperationCycleId))
        {
        
          lPendingCycleStatus = Dem_Queue_GetPendingCycle(OperationCycleId);

          if(lPendingCycleStatus == CycleState) 
          {
            /*do not set*/
            lReturnValue = E_NOT_OK;
            break;
          }
         
        }
        Dem_Queue_SetPendingCycle(OperationCycleId,CycleState);     
        Dem_SetDemState(DEM_OPECYCPENDING);
    }
    while(0);
    Dem_EnableInterrupt();
    return lReturnValue;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_SetOperationCycleCntValue( 
    uint8 OperationCycleId, 
    uint8 CounterValue 
) 
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_SetAgingCycleState( 
    uint8 AgingCycleId 
) 
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */

Std_ReturnType Dem_SetAgingCycleCounterValue( 
    uint8 CounterValue 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetEventStatus( 
    Dem_EventIdType EventId, 
    Dem_EventStatusExtendedType* EventStatusExtended 
)
{
#if(DEM_DEV_ERROR_DETECT==STD_ON)    
    if((EventStatusExtended == NULL_PTR)||(EventId >= DEM_NUMBER_OF_EVENT))
    {
        return  E_NOT_OK;
    }
#endif
    *EventStatusExtended = Dem_GetEventCurrentStatus(EventId); 
    return E_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetEventFailed( 
    Dem_EventIdType EventId, 
    boolean* EventFailed 
) 
{

}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetEventTested( 
    Dem_EventIdType EventId, 
    boolean* EventTested 
)
{
#if(DEM_DEV_ERROR_DETECT==STD_ON)    
    if ((EventTested == NULL_PTR) || (EventId >= DEM_NUMBER_OF_EVENT))
    {
        return  E_NOT_OK;
    }
#endif
    if ((Dem_GetEventCurrentStatus(EventId) & DEM_BIT6) == 0)
    {
        *EventTested = TRUE;
    }
    else
    {
        *EventTested = FALSE;
    }
    return  E_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetDTCOfEvent( 
    Dem_EventIdType EventId, 
    Dem_DTCFormatType DTCFormat, 
    uint32* DTCOfEvent
)
{
    return  E_OK;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_SetEnableCondition( 
    uint8 EnableConditionID, 
    boolean ConditionFulfilled 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_SetStorageCondition( 
    uint8 StorageConditionID, 
    boolean ConditionFulfilled 
) 
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetFaultDetectionCounter( 
    Dem_EventIdType EventId, 
    sint8* FaultDetectionCounter 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetIndicatorStatus( 
    uint8 IndicatorId, 
    Dem_IndicatorStatusType* IndicatorStatus 
) 
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
/* raw hexadecimal values and contains no header information*/
Std_ReturnType Dem_GetEventFreezeFrameData( 
    Dem_EventIdType EventId, 
    uint8 RecordNumber, 
    boolean ReportTotalRecord, 
    uint16 DataId, 
    uint8* DestBuffer 
) 
{

    Dem_EventIdType i; 
    uint8 didIndex;
    uint8 didInfo;
    uint8 didDataSize=0;
    Std_ReturnType ret = E_NOT_OK;    
    if((DestBuffer == NULL_PTR) || (EventId==DEM_EVENT_IDENTIFIER_INVALID))
    {
        return  E_NOT_OK;
    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetEventExtendedDataRecord( 
    Dem_EventIdType EventId, 
    uint8 RecordNumber, 
    uint8* DestBuffer 
) 
{ 
    return E_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetEventMemoryOverflow( 
    Dem_DTCOriginType DTCOrigin, 
    boolean* OverflowIndication 
) 
{
    return E_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
8.3.3 Interface BSW modules / SW-Components
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_SetDTCSuppression
( 
    uint32 DTC, 
    Dem_DTCFormatType DTCFormat, 
    boolean SuppressionStatus 
)
{

    return E_OK;
}
STATIC void L_Dem_RestoreResultHandle(void)
{
    NvM_RequestResultType nvmresult;

    if(E_OK == NvM_GetErrorStatus(2,&nvmresult))
    {
       if(nvmresult == NVM_REQ_PENDING)
       {
           /*nothing*/
       }
       else if(nvmresult == NVM_REQ_OK)
       {
           if((DemStorageMem.EventMemoryHead.DemStoredDatValid0 == DEM_RESTOREFLAG0)&&\
            (DemStorageMem.EventMemoryHead.DemStoredDatValid1 == DEM_RESTOREFLAG1))
           {


           }
           else
           {
               Dem_EventMemHeadInit();
               Dem_EventMemFFInit();
               Dem_EventStatusInit();
               Dem_DtcStatusInit();
           }
           Dem_SetDemState(DEM_NORMAL);
       }
       else
       {
           Dem_EventMemHeadInit();
           Dem_EventMemFFInit();
           Dem_EventStatusInit();
           Dem_DtcStatusInit();
           Dem_SetDemState(DEM_NORMAL);
           /*CallBack App inform Data is Reinited */
       }
    }

}
STATIC void L_Dem_StoreResultHandle(void)
{
    NvM_RequestResultType nvmresult;
    if(E_OK == NvM_GetErrorStatus(2,&nvmresult))
    {
       if(nvmresult == NVM_REQ_PENDING)
       {
           /*nothing*/
       }
       else if(nvmresult == NVM_REQ_OK)
       {
           Dem_SetDemState(DEM_UNINIT);
       }
       else
       {
           /*Callback inform app Stroe failed*/
           Dem_SetDemState(DEM_UNINIT);
       }
    }

}

STATIC void L_Dem_RestoreDataReqHandle(void)
{
    if(E_OK == NvM_ReadBlock(2,(uint8*)(&DemStorageMem)))
    {
        Dem_SetDemState(DEM_DATARESTORING);
    }

}

STATIC void L_Dem_StoreDataReqHandle(void)
{
    if(E_OK == NvM_WriteBlock(DEM_NVM_BLOCKID,(uint8*)(&DemStorageMem)))
    {
        Dem_SetDemStateBit(DEM_DATASTORING);
    }

}

STATIC void L_Dem_ClearDtcReqHandle(void)
{
    /*Clear DTC process start*/         
    switch(Dem_ClearDTCInfo.clearct)
    {
        /*0:clear idle. 1:clear header. 2:clear FF. 3:Clear EventStatus*/

        case DEM_DCM_CLEAR_DTC_BUSY:
        {
            NvM_RequestResultType nvmrt;
            if(E_OK == NvM_GetErrorStatus(Dem_ClearDTCInfo.NvMBlkId,&nvmrt))
            {
                if(nvmrt == NVM_REQ_OK)
                {    
                    Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_DTC_OK;
                }
                else if(nvmrt == NVM_REQ_PENDING)
                {/*do nothing*/

                }
                else
                {
                    Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_DTC_ERR;
                }
            }
            else
            {
                Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_DTC_ERR;
            }
        }
        break;
        case DEM_DCM_CLEAR_EVENT_MEM:
        {
            if(E_OK == NvM_WriteBlock(DEM_NVM_BLOCKID,(uint8*)(&DemStorageMem)))
            {
                Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_DTC_BUSY;
                Dem_ClearDTCInfo.NvMBlkId = 2;
            }
            else
            {
                Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_DTC_ERR;
            }
        }
        break;
        case DEM_DCM_CLEAR_DTC_OK:
        case DEM_DCM_CLEAR_DTC_ERR:
        default:
        break;

    }
	/*Clear DTC process end*/

}


void L_DemEventDataCaptureHandle(void)
{
    uint16 i;
    uint16 j;
    uint16 EventId;
    uint8 flagBitMask = 0;
	
    for (i = CaptureFlagByte; i <((uint8)(DEM_NUMBER_OF_EVENT/8)+1); i++)
    {
        if(Dem_EventCaptureFlag[i] != 0) /*Check event status change flag*/
        {
            for (j=0; j<8; j++)
            {
                EventId=(uint16)(i*8+j);/*current checking DTC*/
                flagBitMask=(uint8)(DEM_BIT0<<j);
                if((uint8)(Dem_EventCaptureFlag[i] & flagBitMask)== flagBitMask)
                {
                    Dem_EventCaptureFlag[i] &=(uint8) (~flagBitMask);
                    (void)Dem_CaptureFreezeFrame(EventId);
                }
                if(EventId >= (DEM_NUMBER_OF_EVENT -1))
                {   /*the last EventId*/
                    break;
                }
            }
            CaptureFlagByte = i+1u;
            break;
        }  
    }
    if(i>=((uint8)(DEM_NUMBER_OF_EVENT/8)+1))
    {
        CaptureFlagByte = 0;
    }
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************                 
************************************************************************************************
END_FUNCTION_HDR */
void Dem_MainFunction(void)
{
    uint8 byteidx;
    uint8 bitidx;
    uint8 bytenum;
    uint16 eventId;
    uint16 ldemstate;
    Std_ReturnType ucRet = E_OK;
    
    do
    {
        Dem_DisableInterrupt();
        Dem_GetDemState(ldemstate);
        Dem_EnableInterrupt();
    
        if(!Dem_CheckDemState(ldemstate,DEM_STATVALIDEMASK))
        {
            break;
        }
        
        if(Dem_CheckDemState(ldemstate,DEM_OPECYCPENDING))
        {
            Dem_DisableInterrupt();
            if (0U != Dem_QueueCyclePendingFlag)
            {
                Dem_Queue_ProcessCycles();
            }
            Dem_EnableInterrupt();
            break;
        }

        if(Dem_CheckDemState(ldemstate,DEM_CLEARMEMORY))
        {
            if(Dem_ClearDTCInfo.cleartyp != DEM_INTER_CLRNONE)
            {
                L_Dem_ClearDtcReqHandle();
            }
            break;
        }
        
        if(Dem_CheckDemState(ldemstate,DEM_NORMAL))
        {
            L_DemEventDataCaptureHandle();
            break;
        }
        if(Dem_CheckDemState(ldemstate,DEM_DATARESTORING))
        {
            L_Dem_RestoreResultHandle();
            break ;
        }
        if(Dem_CheckDemState(ldemstate,DEM_INITPENDING))
        {
            L_Dem_RestoreDataReqHandle();
            break ;
        }

        if(Dem_CheckDemState(ldemstate,DEM_DATASTORING))
        {
            L_Dem_StoreResultHandle();
            break;
        }        
        if(Dem_CheckDemState(ldemstate,DEM_SHUTDOWN))
        {
            L_Dem_StoreDataReqHandle();
            break;
        }
    }
    while(0);
    
    Dem_SetOperationCycleState(DEM_OPCYC_IGNITION, DEM_QUEUE_CYCLE_STARTED);
}


STATIC Std_ReturnType Dem_DataCopy( uint8* Dest,const uint8* Src,uint16 Cnt)
{
    uint16 i;
    Std_ReturnType result = E_NOT_OK;
    
    if(Dest != NULL_PTR)
    {
        for(i=0;i<Cnt;i++)
        {
            Dest[i]=Src[i] ;
        }
        result = E_OK;
    }
    return result;
}

/***********************************DCM Interface**************************************/
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information 
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnSetFilterType Dem_SetDTCFilter( 
    uint8 DTCStatusMask, 
/*
DTCStatusMask:
0x00: Autosar-specific value to deactivate the 
status-byte filtering (different meaning than in ISO 
14229-1) to report all supported DTCs (used for 
service 0x19 subfunctions 0x0A/0x15) 
*/
    Dem_DTCKindType DTCKind, /*Not support OBD-relevant DTC*/
    Dem_DTCFormatType DTCFormat, 
    Dem_DTCOriginType DTCOrigin, 
    Dem_FilterWithSeverityType FilterWithSeverity, 
    Dem_DTCSeverityType DTCSeverityMask, 
    Dem_FilterForFDCType FilterForFaultDetectionCounter /*NO use*/
)
{
    Dem_ReturnSetFilterType result=DEM_WRONG_FILTER;/*Wrong filter selected*/
    uint16 i;
    
#if(DEM_DEV_ERROR_DETECT==STD_ON)    
    if((DTCKind!=DEM_DTC_KIND_ALL_DTCS)||(DTCOrigin!=DEM_DTC_ORIGIN_MEMORY)||\
        (DTCFormat!=DEM_DTC_FORMAT_UDS))
    {
        return  DEM_WRONG_FILTER;
    }
#endif
    if(((DTCStatusMask & DEM_STATUS_AVAILABILITY_MASK)!=0)||(DTCStatusMask == 0))
    {
        if(FilterWithSeverity==DEM_FILTER_WITH_SEVERITY_YES)      
        {
            if((DEM_DTC_SEVERITY_MASK & DTCSeverityMask)!=0)
            {
                Dem_DTCFilterInfo.DTCSeverityMask = DTCSeverityMask;
            }
        }
        else
        {
            Dem_DTCFilterInfo.DTCSeverityMask = DEM_DTC_SEVERITY_MASK;
            Dem_DTCFilterInfo.DTCStatusMask=DTCStatusMask;          
        }
        Dem_DTCFilterInfo.NumberOfFilteredDTC = 0;
        Dem_DTCFilterInfo.NextFilteredDTCIndex = 0;
        for(i=0;i<DEM_NUMBER_OF_DTC;i++)
        {  
            if((0==DTCStatusMask)||\
                ((Dem_DtcStatusInfo[i].DtcStatus & Dem_DTCFilterInfo.DTCStatusMask)!= 0))
            {                   
                Dem_DTCFilterInfo.FilteredDTCIndexTable[Dem_DTCFilterInfo.NextFilteredDTCIndex] = i;
                Dem_DTCFilterInfo.NumberOfFilteredDTC++;
                Dem_DTCFilterInfo.NextFilteredDTCIndex++;
            }
        }
        Dem_DTCFilterInfo.NextFilteredDTCIndex = 0;

        /*if(Dem_DTCFilterInfo.NumberOfFilteredDTC != 0)*/
        {/* find the Filtered DTC*/
            Dem_DTCFilterInfo.FilteredValidFlag = TRUE;
            result = DEM_FILTER_ACCEPTED;
        }

    }

    return result;  
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information 
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnSetFilterType Dem_SetFreezeFrameRecordFilter
( 
    Dem_DTCFormatType DTCFormat, 
    uint16* NumberOfFilteredRecords 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information 
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetStatusOfDTCType Dem_GetStatusOfDTC
( 
    uint32 DTC, 
    Dem_DTCOriginType DTCOrigin, 
    uint8* DTCStatus 
)                                              
{
    Dem_EventIdType i;
    Dem_ReturnGetStatusOfDTCType result = DEM_STATUS_FAILED;
    uint16 dtcidx;

#if(DEM_DEV_ERROR_DETECT==STD_ON)    
    if(DTCOrigin!=DEM_DTC_ORIGIN_MEMORY)
    {
        return  DEM_STATUS_WRONG_DTCORIGIN;
    }
#endif    
    if(E_OK == Dem_CheckDtcValid(DTC,&dtcidx))
    {
        *DTCStatus = Dem_DtcStatusInfo[dtcidx].DtcStatus;
        result = DEM_STATUS_OK;/*Status of DTC is OK*/
    }           
    else
    {
        result = DEM_STATUS_WRONG_DTC;/*Status of DTC is OK*/
    }
    return result;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information         
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8* DTCStatusMask)
{
  
    if(DTCStatusMask == NULL_PTR)
    {
        return  E_NOT_OK;
    }
    *DTCStatusMask=DEM_STATUS_AVAILABILITY_MASK;
    return E_OK;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information 
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetNumberOfFilteredDTCType Dem_GetNumberOfFilteredDTC
( 
    uint16* NumberOfFilteredDTC 
)
{
    Dem_EventIdType i;
    Dem_EventIdType dtcNumber=0;

    Dem_ReturnGetNumberOfFilteredDTCType ret = DEM_NUMBER_FAILED;

#if(DEM_DEV_ERROR_DETECT==STD_ON)    
    if(NumberOfFilteredDTC == NULL_PTR)
    {
        return  DEM_NUMBER_FAILED;
    }
#endif
    if(Dem_DTCFilterInfo.FilteredValidFlag == TRUE)
    {
        *NumberOfFilteredDTC = Dem_DTCFilterInfo.NumberOfFilteredDTC;
        ret = DEM_NUMBER_OK;
    }
    
    return ret;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information               
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTC
( 
    uint32* DTC, 
    uint8* DTCStatus 
)
{
    uint16 dtcidx;
    Dem_ReturnGetNextFilteredDTCType result = DEM_FILTERED_NO_MATCHING_DTC;

#if(DEM_DEV_ERROR_DETECT==STD_ON)    
    if ((DTC == NULL_PTR) || (DTCStatus == NULL_PTR))
    {
        return DEM_FILTERED_NO_MATCHING_DTC;
    }
#endif    

    if((Dem_DTCFilterInfo.FilteredValidFlag == TRUE)&&\
        (Dem_DTCFilterInfo.NextFilteredDTCIndex < Dem_DTCFilterInfo.NumberOfFilteredDTC))
    {
        dtcidx = Dem_DTCFilterInfo.FilteredDTCIndexTable[Dem_DTCFilterInfo.NextFilteredDTCIndex];  
        *DTC = DemDTCClassSet[dtcidx].DemUdsDTC;
        *DTCStatus = Dem_DtcStatusInfo[dtcidx].DtcStatus; 
        Dem_DTCFilterInfo.NextFilteredDTCIndex++;
        result = DEM_FILTERED_OK;
    }
    else
    {
        Dem_DTCFilterInfo.FilteredValidFlag = FALSE;
    }
/*    
    for(i=Dem_DTCFilterInfo.NextFilteredDTCIndex;i<DEM_NUMBER_OF_EVENTS;i++)
    {  
        if((Dem_DtcStatusInfo[i].DtcStatus & Dem_DTCFilterInfo.DTCStatusMask)!= 0)
        {
            *DTC = DemDTCClassSet[i].DemUdsDTC;
            *DTCStatus = Dem_DtcStatusInfo[i].DtcStatus;                    
            result = DEM_FILTERED_OK;
            break; 
        }
    }
    Dem_DTCFilterInfo.NextFilteredDTCIndex = i+1; 
 */   
    return result;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information               
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetDTCByOccurrenceTimeType Dem_GetDTCByOccurrenceTime
( 
    Dem_DTCRequestType DTCRequest, 
    uint32* DTC 
)
{
    return  DEM_OCCURR_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information               
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredRecord
( 
    uint32* DTC, 
    uint8* RecordNumber 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information               
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetNextFilteredDTCType 
Dem_GetNextFilteredDTCAndFDC( 
    uint32* DTC, 
    sint8* DTCFaultDetectionCounter 
)
{
    return 0;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information               
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetNextFilteredDTCType 
Dem_GetNextFilteredDTCAndSeverity( 
    uint32* DTC, 
    uint8* DTCStatus, 
    Dem_DTCSeverityType* DTCSeverity, 
    uint8* DTCFunctionalUnit 
) 
{
    return 0;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information               
************************************************************************************************
END_FUNCTION_HDR */
Dem_DTCTranslationFormatType Dem_GetTranslationType( 
    void 
)
{
    return DEM_TYPE_OF_DTC_SUPPORT;/*DEM_ISO14229_1*/
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information               
************************************************************************************************
END_FUNCTION_HDR */

Dem_ReturnGetSeverityOfDTCType Dem_GetSeverityOfDTC( 
    uint32 DTC, 
    Dem_DTCSeverityType* DTCSeverity 
)
{
    return 0;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
Access DTCs and Status Information               
************************************************************************************************
END_FUNCTION_HDR 
NO USED
*/
Dem_ReturnGetFunctionalUnitOfDTCType Dem_GetFunctionalUnitOfDTC(
    uint32 DTC, 
    uint8* DTCFunctionalUnit 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.2 Access extended data records and FreezeFrame data              
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnDisableDTCRecordUpdateType 
Dem_DisableDTCRecordUpdate( 
    uint32 DTC, 
    Dem_DTCOriginType DTCOrigin 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.2 Access extended data records and FreezeFrame data              
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_EnableDTCRecordUpdate( 
    void 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.2 Access extended data records and FreezeFrame data              
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetFreezeFrameDataByRecordType 
Dem_GetFreezeFrameDataByRecord( 
    uint8 RecordNumber,
    Dem_DTCOriginType DTCOrigin, 
    uint32* DTC, 
    uint8* DestBuffer, 
    uint16* BufSize 
)
{

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.2 Access extended data records and FreezeFrame data              
************************************************************************************************
END_FUNCTION_HDR */
#define DEM_MINFFRECORDLEN    5/*DTCSnapshotRecordNumber DTCSnapshotRecordNumberOfIdentifiers DID_H  DID_L 1ByteDATA*/
Dem_ReturnGetFreezeFrameDataByDTCType 
Dem_GetFreezeFrameDataByDTC
( 
    uint32 DTC, 
    Dem_DTCOriginType DTCOrigin, 
    uint8 RecordNumber, /*0x00:OBD freeze frame,not support;!!!extended function 0xff can be supported*/
    uint8* DestBuffer, 
    uint16* BufSize 
) 
{
    Dem_EventIdType i;  
    uint8 recOcc;
    uint8* pffdata;
    uint16 dtcidx;
    uint16 eveidx;
    uint16 len;
    
    Dem_ReturnGetFreezeFrameDataByDTCType result=DEM_GET_FFDATABYDTC_WRONG_DTC;
#if(DEM_DEV_ERROR_DETECT==STD_ON)     
        if ((DestBuffer == NULL_PTR) || (BufSize == NULL_PTR))
        {
            return DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
        }
        if(DTCOrigin!=DEM_DTC_ORIGIN_PRIMARY_MEMORY)
        {
           return DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN;
        }
        if(*BufSize < DEM_MINFFRECORDLEN)
        {
           return DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
        }
        if(RecordNumber == 0)
        {
            return DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
        }
#endif   

    eveidx = DEM_EVENT_IDENTIFIER_INVALID;
    
    if(E_OK == Dem_CheckDtcValid(DTC,&dtcidx))
    {
        uint16 entryid;
        uint16 recdidx;
        uint16 numofrec;/* number of recorde mnumber */
        result = DEM_GET_FFDATABYDTC_OK;
      
        entryid = Dem_GetEventMemEntryIndexByDTC(DTC);
        if(entryid < DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY)
        {
            eveidx = DemStorageMem.EventMemoryEntry[entryid].EmEventId;

            do
            {
                if(RecordNumber == 0xFF)
                {
                    recdidx = 0;
                    numofrec = DemFreezeFrameClassTab0[DemEventParameterTab[eveidx].DemFreezeFrameClassRef].DemNumberOfRecordNum;
                }
                else if(E_OK == L_DemGetEventFFRecdIndx(eveidx,RecordNumber,&recdidx))
                {
                    numofrec = 1u;
                }
                else
                {
                    result = DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
                    break;
                }
                
                len = Dem_GetEventFFRecdLength(eveidx,RecordNumber,recdidx);
                if(*BufSize >= len)
                {
                   uint8 j;
                   const Dem_DidClassType* pDidClass;
                   const Dem_FreezeFrameRecNumClassType* pRecNumClass;    
                   uint8 numofdid; 
                   uint16 k;
                   uint16 ofst;

                   *BufSize = len;

                   L_Dem_GetEventFFRecdBuffOffset(recdidx,eveidx,&ofst);

                   pffdata = &DemStorageMem.EventMemoryEntry[entryid].FreezeFrameData[ofst];

                   pRecNumClass = &(DemFreezeFrameClassTab0[DemEventParameterTab[eveidx].DemFreezeFrameClassRef].DemFreezeFrameRecNumClassRef[recdidx]);

                   for(k = 0;k<numofrec;k++)
                   { 
                       numofdid = pRecNumClass->DemSnapshotRecordNumberOfIdentifiers;
                       pDidClass = pRecNumClass->DemDidClassRef;
    
                       *DestBuffer = pRecNumClass->DemFreezeFrameRecordNumber;
                       DestBuffer++;
                       *DestBuffer = numofdid;
                       DestBuffer++;
                       for(j=0;j<numofdid;j++)
                       {
                           uint8 didsize = 0;
                           *DestBuffer = (uint8)((pDidClass->DemDidIdentifier)>>8u);
                           DestBuffer++;
    
                           *DestBuffer =(uint8)(pDidClass->DemDidIdentifier);
                           DestBuffer++;

                           (void)L_DemGetDataElementSize(pDidClass->DemDidDataElementClassRef,&didsize,pDidClass->DemDataIndex);
                           Dem_DataCopy(DestBuffer,pffdata,didsize);
    
                           DestBuffer += didsize;
                           pffdata += didsize;
                           
                           pDidClass++;
                       }
                       pRecNumClass++;
                   }
                }
                else
                {
                   result = DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
                }

            }while(0);

        }
        else
        {
            *BufSize = 0;
        }
    }
     
    return result;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.2 Access extended data records and FreezeFrame data              
************************************************************************************************
END_FUNCTION_HDR */
/*TBD*/
Dem_ReturnGetSizeOfFreezeFrameByDTCType 
Dem_GetSizeOfFreezeFrameByDTC( 
    uint32 DTC, 
    Dem_DTCOriginType DTCOrigin, 
    uint8 RecordNumber, 
    uint16* SizeOfFreezeFrame 
)
{
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.2 Access extended data records and FreezeFrame data              
************************************************************************************************
END_FUNCTION_HDR */
#define DEM_MINEXTRECORDLEN    2/*DTCExtendedDataRecordNumber 1ByteDATA*/

Dem_ReturnGetExtendedDataRecordByDTCType 
Dem_GetExtendedDataRecordByDTC( 
    uint32 DTC, 
    Dem_DTCOriginType DTCOrigin, 
    uint8 ExtendedDataNumber, /*values are from 0x01 to 0xEF. !!!extended function 0xff can be supported*/
    uint8* DestBuffer, 
    uint16* BufSize 
) 
{
    Dem_EventIdType i;
    Dem_EventIdType entry;    
    uint8 recOcc;
    uint8 recNum=0;
    uint8 dataIndex=0;
    uint8 ffDataSize=0;  
    uint8* pffdata;
    uint16 dtcidx;
    uint16 eveidx;
    uint16 len;
    Dem_ReturnGetFreezeFrameDataByDTCType result=DEM_RECORD_WRONG_DTC;

    
#if(DEM_DEV_ERROR_DETECT==STD_ON)     
        if ((DestBuffer == NULL_PTR) || (BufSize == NULL_PTR))
        {
            return DEM_RECORD_WRONG_BUFFERSIZE;
        }
        if(DTCOrigin!=DEM_DTC_ORIGIN_PRIMARY_MEMORY)
        {
           return DEM_RECORD_WRONG_DTCORIGIN;
        }
        if(*BufSize < DEM_MINEXTRECORDLEN)
        {
           return DEM_RECORD_WRONG_BUFFERSIZE;
        }
        if((ExtendedDataNumber == 0)||((ExtendedDataNumber > 0xEF)&&(ExtendedDataNumber<0xFF)))
        {
            return DEM_RECORD_WRONG_NUMBER;
        }
#endif   

    eveidx = DEM_EVENT_IDENTIFIER_INVALID;
    
    if(E_OK == Dem_CheckDtcValid(DTC,&dtcidx))
    {
        uint16 entryid;
        uint16 recdidx;
        uint16 numofrec;
        
        result = DEM_RECORD_OK;

        entryid = Dem_GetEventMemEntryIndexByDTC(DTC);
        if(entryid < DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY)
        {
            eveidx = DemStorageMem.EventMemoryEntry[entryid].EmEventId;

            do
            {
                if(ExtendedDataNumber == 0xFF)
                {
                    recdidx = 0;
                    numofrec = DemExtendedDataClassTab0[DemEventParameterTab[eveidx].DemExtendedDataClassRef].DemNumberOfExtendRecNum;
                }
                else if(E_OK == L_DemGetEventExtRecdIndx(eveidx,ExtendedDataNumber,&recdidx))
                {
                    numofrec = 1u;
                }
                else
                {
                    result = DEM_RECORD_WRONG_NUMBER;
                    break;
                }
                
                len = Dem_GetEventExtRecdLength(eveidx,ExtendedDataNumber,recdidx);
                if(*BufSize >= len)
				{
					const Dem_ExtendedDataRecordClassType* pRecNumClass;  
					uint16 k;
					uint16 ofst;

					*BufSize = len;

					L_Dem_GetEventExtRecdBufferOffset(recdidx,eveidx,&ofst);

					pffdata = &DemStorageMem.EventMemoryEntry[entryid].ExtendedData[ofst];

					pRecNumClass = &(DemExtendedDataClassTab0[DemEventParameterTab[eveidx].DemExtendedDataClassRef].DemExtendedDataRecordClassRef[recdidx]);

					for(k = 0;k<numofrec;k++)
					{ 
						len = Dem_GetEventExtDataLength(eveidx,pRecNumClass->DemExtendedDataRecordNumber,recdidx);

						*DestBuffer = pRecNumClass->DemExtendedDataRecordNumber;
						DestBuffer++;
						Dem_DataCopy(DestBuffer,pffdata,len);
						DestBuffer += len;
						pffdata += len;
						pRecNumClass++;
						recdidx++;
					}
				}
                else
                {
                   result = DEM_RECORD_WRONG_BUFFERSIZE;
                }

            }while(0);

        }
        else
        {
            *BufSize = 0;
        }
    }
     
    return result;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.2 Access extended data records and FreezeFrame data              
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnGetSizeOfExtendedDataRecordByDTCType 
Dem_GetSizeOfExtendedDataRecordByDTC( 
    uint32 DTC, 
    Dem_DTCOriginType DTCOrigin, 
    uint8 ExtendedDataNumber, 
    uint16* SizeOfExtendedDataRecord 
)
{
    return 0;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.3  DTC storage              
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnClearDTCType Dem_ClearDTC
( 
    uint32 DTC, 
    Dem_DTCFormatType DTCFormat, 
    Dem_DTCOriginType DTCOrigin 
)
{
    Dem_ReturnClearDTCType result;
    uint16 ldemstate;

    Dem_DisableInterrupt();
    Dem_GetDemState(ldemstate);
    Dem_EnableInterrupt();

    
    if(!(Dem_CheckDemState(ldemstate,(DEM_CLEARMEMORY|DEM_NORMAL))))
       return DEM_CLEAR_FAILED;

    if(Dem_ClearDTCInfo.clearct != DEM_DCM_CLEAR_DTC_IDLE)
    {
        if(Dem_ClearDTCInfo.clearct == DEM_DCM_CLEAR_DTC_OK)
        {
            Dem_SetDemState(DEM_NORMAL);
            Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_DTC_IDLE;
            Dem_ClearDTCInfo.cleartyp = DEM_INTER_CLRNONE;
            return DEM_CLEAR_OK;
        }

        if(Dem_ClearDTCInfo.clearct == DEM_DCM_CLEAR_DTC_ERR)
        {
            Dem_SetDemState(DEM_NORMAL);
            Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_DTC_IDLE;
            Dem_ClearDTCInfo.cleartyp = DEM_INTER_CLRNONE;
            return DEM_CLEAR_FAILED;
        }

        return DEM_CLEAR_PENDING;
    }

    if(DTC == 0xFFFFFF)
    {
        Dem_EventMemHeadInit();
        Dem_EventMemFFInit();
        Dem_EventStatusInit();
        Dem_DtcStatusInit();
        Dem_ClearDTCInfo.cleartyp = DEM_INTER_CLRALL;
        Dem_ClearDTCInfo.clearct = DEM_DCM_CLEAR_EVENT_MEM;
        /*Dem_CheckDemState(ldemstate,DEM_CLEARMEMORY);*/
        Dem_SetDemState(DEM_CLEARMEMORY);

        result = DEM_CLEAR_PENDING;
    }
    else
    {
        result = DEM_CLEAR_WRONG_DTC;
    }

    return result;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.3  DTC storage              
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnControlDTCSettingType Dem_DisableDTCSetting( 
    Dem_DTCGroupType DTCGroup, 
    Dem_DTCKindType DTCKind 
)
{     
    if((DTCGroup!=DEM_DTC_GROUP_ALL_DTCS) || (DTCKind!=DEM_DTC_KIND_ALL_DTCS))
    {
        return DEM_CONTROL_DTC_WRONG_DTCGROUP;
    }
    Dem_EnableDtcSetting = FALSE;
    return DEM_CONTROL_DTC_SETTING_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
Interface Dcm
8.3.4.3  DTC storage              
************************************************************************************************
END_FUNCTION_HDR */
Dem_ReturnControlDTCSettingType Dem_EnableDTCSetting( 
    Dem_DTCGroupType DTCGroup, 
    Dem_DTCKindType DTCKind 
)
{
    if((DTCGroup!=DEM_DTC_GROUP_ALL_DTCS) || (DTCKind!=DEM_DTC_KIND_ALL_DTCS))
    {
        return DEM_CONTROL_DTC_WRONG_DTCGROUP;
    }
    Dem_EnableDtcSetting = TRUE;
    return DEM_CONTROL_DTC_SETTING_OK;
}
/******************************************************************************
/******************************************************************************
/******************************************************************************
/******************************************************************************

/******************************************************************************             
******************************************************************************/
/******************************************************************************
* Name         :DemDcmIf_ClearDiagnosticInformation 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContextDcm_MsgContextType* pMsgContext  
* Return code  : 0 - Positive response
*                1 - Condition not correct
*                2 - Out of range 
* Description  :Clear single DTC or group of DTC.  
*                
******************************************************************************/
void DemDcmIf_ClearDiagnosticInformation(Dcm_MsgContextType* pMsgContext)
{
    Dem_ReturnClearDTCType clearResult;
    uint32 Dtc;

    Dtc=Make32Bit(pMsgContext->reqData[1],pMsgContext->reqData[2],pMsgContext->reqData[3]);
    clearResult=Dem_ClearDTC(Dtc, DEM_DTC_KIND_ALL_DTCS,DEM_DTC_ORIGIN_PRIMARY_MEMORY);

    if(clearResult==DEM_CLEAR_PENDING)
    {
    
    }
    else if(clearResult==DEM_CLEAR_OK)
    {
        pMsgContext->resDataLen=1;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else if(clearResult==DEM_CLEAR_FAILED)
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_CONDITIONSNOTCORRECT);            
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        /*DEM_CLEAR_WRONG_DTC  DEM_CLEAR_WRONG_DTCORIGIN */
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
        DsdInternal_ProcessingDone(pMsgContext);
    }

 }
void DemDcmIf_ReportNumberOfDTCByStatusMask(Dcm_MsgContextType* pMsgContext)
{
    uint8 dtcStatus;
    uint8 dtcStatusAvailabilityMask;
    uint16 dtccounter=0;
    dtcStatus=pMsgContext->reqData[2];
    if(Dem_SetDTCFilter(dtcStatus,DEM_DTC_KIND_ALL_DTCS,DEM_DTC_FORMAT_UDS,
        DEM_DTC_ORIGIN_PRIMARY_MEMORY,DEM_FILTER_WITH_SEVERITY_NO,0,0)!=DEM_FILTER_ACCEPTED)
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    else
    {
        (void)Dem_GetNumberOfFilteredDTC(&dtccounter);
        (void)Dem_GetDTCStatusAvailabilityMask(&dtcStatusAvailabilityMask);
        pMsgContext->resData[1]=pMsgContext->reqData[1];
        pMsgContext->resData[2]=dtcStatusAvailabilityMask;
        pMsgContext->resData[3]=Dem_GetTranslationType();/* J1939 DTC Format */
        pMsgContext->resData[4]=(uint8)(dtccounter>>8);
        pMsgContext->resData[5]=(uint8)(dtccounter);
        pMsgContext->resDataLen=6;/* Always equals 6 */
    }
    DsdInternal_ProcessingDone(pMsgContext);
}


/******************************************************************************
* Name         :DemDcmIf_ReportDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContextDcm_MsgContextType* pMsgContext  
* Return code  : 0 - Positive response
*                2 - Out of range  
* Description  :Report DTC by status mask.  
*                
******************************************************************************/
void DemDcmIf_ReportDTCByStatusMask(Dcm_MsgContextType* pMsgContext)
{
    uint32 dtc;
    uint8 dtcStatus;
    uint8 dtcStatusMask;
    uint8 dtcStatusAvailabilityMask;    
    uint16 dtcCounter=0;
    uint8 getNextDtcResult;
    
    dtcStatusMask=pMsgContext->reqData[2];
    if(Dem_SetDTCFilter(dtcStatusMask,DEM_DTC_KIND_ALL_DTCS,DEM_DTC_FORMAT_UDS,\
        DEM_DTC_ORIGIN_PRIMARY_MEMORY,DEM_FILTER_WITH_SEVERITY_NO,0,0)!=DEM_FILTER_ACCEPTED)
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    else
    {
        do
        {
            getNextDtcResult = Dem_GetNextFilteredDTC(&dtc, &dtcStatus);

            if(getNextDtcResult == DEM_FILTERED_OK)
            {
                pMsgContext->resData[3+dtcCounter*4]=(uint8)(dtc>>16);
                pMsgContext->resData[4+dtcCounter*4]=(uint8)(dtc>>8);
                pMsgContext->resData[5+dtcCounter*4]=(uint8)(dtc);
                pMsgContext->resData[6+dtcCounter*4]=dtcStatus;
                dtcCounter++;  
            }
        }
        while(getNextDtcResult != DEM_FILTERED_NO_MATCHING_DTC);

        (void)Dem_GetDTCStatusAvailabilityMask(&dtcStatusAvailabilityMask);
        pMsgContext->resData[1]=pMsgContext->reqData[1];
        pMsgContext->resData[2]=dtcStatusAvailabilityMask;
        pMsgContext->resDataLen=3+(dtcCounter*4);
    }
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :  DemDcmIf_ReportDTCSnapshotRecordByDTCNumber 
* Called by    :   
* Preconditions:  
* Parameters   :  
* Return code  :  
* Description  :  
*                
******************************************************************************/
void DemDcmIf_ReportDTCSnapshortRecordByDTCNumber(Dcm_MsgContextType* pMsgContext)
{
    uint32 Dtc;
    uint8 DTCSnapshotRecNum;
    uint16 SnapshotRecLen;
    Dem_ReturnGetStatusOfDTCType DTCRetSt;

    SnapshotRecLen = UDS_PHYS_BUFFER_SIZE - 6u;
    Dtc=Make32Bit(pMsgContext->reqData[2],pMsgContext->reqData[3],pMsgContext->reqData[4]);
    DTCSnapshotRecNum=pMsgContext->reqData[5];
    DTCRetSt = Dem_GetStatusOfDTC(Dtc,DEM_DTC_ORIGIN_PRIMARY_MEMORY,&(pMsgContext->resData[5]));
    if(DEM_STATUS_OK == DTCRetSt)
    {
        if(Dem_GetFreezeFrameDataByDTC(Dtc,DEM_DTC_ORIGIN_PRIMARY_MEMORY,\
           DTCSnapshotRecNum,&pMsgContext->resData[6],&SnapshotRecLen)!=DEM_GET_FFDATABYDTC_OK)
        {
            DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
        }
        else
        {
            pMsgContext->resData[1]=pMsgContext->reqData[1];
            pMsgContext->resDataLen=6u+SnapshotRecLen;
        }  
    }
    else if((DEM_STATUS_WRONG_DTC == DTCRetSt)||(DEM_STATUS_WRONG_DTCORIGIN == DTCRetSt))
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_CONDITIONSNOTCORRECT);
    }
    
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :  DemDcmIf_ReportDTCExtendedDataRecordByDTCNumber 
* Called by    :   
* Preconditions:  
* Parameters   :  
* Return code  :  
* Description  :  
*                
******************************************************************************/
void DemDcmIf_ReportDTCExtendedDataRecordByDTCNumber(Dcm_MsgContextType* pMsgContext)
{
    uint32 Dtc;
    uint8 ExtendedDataNum;
    uint16 ExtendedDataRecLen;
    Dem_ReturnGetStatusOfDTCType DTCRetSt;

    ExtendedDataRecLen = UDS_PHYS_BUFFER_SIZE - 6u;
    Dtc=Make32Bit(pMsgContext->reqData[2],pMsgContext->reqData[3],pMsgContext->reqData[4]);
    ExtendedDataNum=pMsgContext->reqData[5];
    DTCRetSt = Dem_GetStatusOfDTC(Dtc,DEM_DTC_ORIGIN_PRIMARY_MEMORY,&(pMsgContext->resData[5]));
    if(DEM_STATUS_OK == DTCRetSt)
    {
        if(Dem_GetExtendedDataRecordByDTC(Dtc,DEM_DTC_ORIGIN_PRIMARY_MEMORY,\
           ExtendedDataNum,&pMsgContext->resData[6],&ExtendedDataRecLen)!=DEM_RECORD_OK)
        {
            DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
        }
        else
        {
            /*pMsgContext->resData[1]=pMsgContext->reqData[1];*/
            pMsgContext->resDataLen = 6u + ExtendedDataRecLen;
        }  
    }
    else if((DEM_STATUS_WRONG_DTC == DTCRetSt)||(DEM_STATUS_WRONG_DTCORIGIN == DTCRetSt))
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_CONDITIONSNOTCORRECT);
    }
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :DemDcmIf_ReportSupportedDTC 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContextDcm_MsgContextType* pMsgContext  
* Return code  :0 - Positive response  
* Description  :Report supported DTC to Tester.  
*                
******************************************************************************/
void DemDcmIf_ReportSupportedDTC(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=0;
    uint8 dtcStatusAvailabilityMask;
    Dem_ReturnGetNextFilteredDTCType getNextDtcResult;
    uint32 dtc;
    uint8 dtcStatus;
    uint16 dtcCounter=0;

    (void)Dem_GetDTCStatusAvailabilityMask(&dtcStatusAvailabilityMask);
    pMsgContext->resData[1]=pMsgContext->reqData[1];
    pMsgContext->resData[2]=dtcStatusAvailabilityMask;
    if(Dem_SetDTCFilter(0,DEM_DTC_KIND_ALL_DTCS,DEM_DTC_FORMAT_UDS,\
            DEM_DTC_ORIGIN_PRIMARY_MEMORY,DEM_FILTER_WITH_SEVERITY_NO,0,0)!=DEM_FILTER_ACCEPTED)
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    else
    {
        do
        {
            getNextDtcResult = Dem_GetNextFilteredDTC(&dtc, &dtcStatus);

            if(getNextDtcResult == DEM_FILTERED_OK)
            {
                pMsgContext->resData[3+dtcCounter*4]=(uint8)(dtc>>16);
                pMsgContext->resData[4+dtcCounter*4]=(uint8)(dtc>>8);
                pMsgContext->resData[5+dtcCounter*4]=(uint8)(dtc);
                pMsgContext->resData[6+dtcCounter*4]=dtcStatus;
                dtcCounter++;  
            }
        }
        while(getNextDtcResult != DEM_FILTERED_NO_MATCHING_DTC);
        pMsgContext->resDataLen=3+dtcCounter*4;
    }
    
    DsdInternal_ProcessingDone(pMsgContext);
}

/***********************************end***********************************/

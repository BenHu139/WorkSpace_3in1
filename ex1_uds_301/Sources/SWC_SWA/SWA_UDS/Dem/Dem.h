 /*BEGIN_FILE_HDR
**************************************************************************************************
* NOTICE                              
* This software is the property of HiRain Technologies. Any information contained in this 
* doc should not be reproduced, or used, or disclosed without the written authorization from 
* HiRain Technologies.
**************************************************************************************************
* File Name: Dem.h
**************************************************************************************************
* Project/Product: AUTOSAR BSW
* Title:
* Author: qyMa
***************************************************************************************************
* Description:AUTOSAR Diagnostic Event Manager (DEM) API header file.
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
***************************************************************************************************
*END_FILE_HDR*/
#ifndef _DEM_H_
#define _DEM_H_

/*------------------------------------------------------------------------------------------------*\
  INCLUDES
\*------------------------------------------------------------------------------------------------*/
#include "Dem_Types.h"
#include "Dem_IntEvtId.h"/*Event Id symbols */
#include "Dem_Cbk.h"
#include "Dcm_Types.h"
/*------------------------------------------------------------------------------------------------*\
  DEFINES
\*------------------------------------------------------------------------------------------------*/
extern Dem_StorageMemType DemStorageMem;
extern void Dem_MainFunction(void);
extern void Dem_Init(void);
extern FUNC(Std_ReturnType, DEM_CODE)Dem_SetEventStatus
(
    Dem_EventIdType     EventId,                                                                                                      
    Dem_EventStatusType EventStatus
);
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetOperationCycleState
(
    uint8  OperationCycleId,                                                                                                       
    Dem_OperationCycleStateType  CycleState
);
extern void Dem_ReportErrorStatus(Dem_EventIdType EventId,Dem_EventStatusType EventStatus);
extern void Dem_Shutdown(void);
extern Dem_ReturnControlDTCSettingType Dem_EnableDTCSetting( 
    Dem_DTCGroupType DTCGroup, 
    Dem_DTCKindType DTCKind 
);
extern Dem_ReturnControlDTCSettingType Dem_DisableDTCSetting( 
    Dem_DTCGroupType DTCGroup, 
    Dem_DTCKindType DTCKind 
);
extern void DemDcmIf_ClearDiagnosticInformation(Dcm_MsgContextType* pMsgContext);
extern void DemDcmIf_ReportNumberOfDTCByStatusMask(Dcm_MsgContextType* pMsgContext);
extern void DemDcmIf_ReportDTCByStatusMask(Dcm_MsgContextType* pMsgContext);
extern void DemDcmIf_ReportDTCSnapshortRecordByDTCNumber(Dcm_MsgContextType* pMsgContext);
extern void DemDcmIf_ReportDTCExtendedDataRecordByDTCNumber(Dcm_MsgContextType* pMsgContext);
extern void DemDcmIf_ReportSupportedDTC(Dcm_MsgContextType* pMsgContext);
#endif /* _DEM_H_ */

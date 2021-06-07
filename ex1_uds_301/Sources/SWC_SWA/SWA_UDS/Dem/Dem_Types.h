/*BEGIN_FILE_HDR
***************************************************************************************************
* NOTICE                              
* This software is the property of HiRain Technologies. Any information contained in this 
* doc should not be reproduced, or used, or disclosed without the written authorization from 
* HiRain Technologies.
***************************************************************************************************
* File Name: Dem_Types.h
***************************************************************************************************
* Project/Product: AUTOSAR BSW
* Title:
* Author: qyMa
***************************************************************************************************
* Description: for all DEM data types
*
***************************************************************************************************
* Limitations:
*
* (limitations) 
***************************************************************************************************

***************************************************************************************************
* Revision History:
* 
*  Version   Date      Initials     CR#    Descriptions
*  ---------   -----------  ------------  ----------  ----------------------------------------
*¡¡1.0      12/01/20    qyMa         N/A     Original
***************************************************************************************************
*END_FILE_HDR*/

#ifndef _DEM_TYPES_H_
#define _DEM_TYPES_H_

/*------------------------------------------------------------------------------------------------*\
  INCLUDES
\*------------------------------------------------------------------------------------------------*/
#include "Uds_Types.h"
#include "Dem_Cfg.h"

#define DEM_NUMBEROFINDICATORS           5
#define DEM_INDICATORID_0                  0/*DEM_INDICATOR_<NAME>*/
#define DEM_INDICATORID_1                  1/*DEM_INDICATOR_<NAME>*/
#define DEM_INDICATORID_2                  2/*DEM_INDICATOR_<NAME>*/
#define DEM_INDICATORID_3                  3/*DEM_INDICATOR_<NAME>*/
#define DEM_INDICATORID_4                  4/*DEM_INDICATOR_<NAME>*/



/*DemDataElementClass define*/
/*#define DEMEXTERNALDATAELEMENTCLASS_CS          1 
#define DEMEXTERNALDATAELEMENTCLASS_SR          2 
#define DEMINTERNALDATAELEMENTCLASS             3 */

/*self def*/
typedef enum
{
    DemInternal,
    DemExternalCS,   
    DemExternalSR
}Dem_DataElementClassType;

typedef enum
{
    DEM_EVENT_KIND_BSW,
    DEM_EVENT_KIND_SWC
}Dem_EventKindType;

typedef enum
{
    DEM_EVENT_SIGNIFICANCE_FAULT,
    DEM_EVENT_SIGNIFICANCE_OCCURRENCE
}Dem_EventSignificanceType;
typedef enum
{
    DEM_AGINGCTR,
    DEM_OCCCTR,
    DEM_OVFLIND,
    DEM_SIGNIFICANCE,
    DEM_AGEDCTR,/*add*/
    DEM_PENDINFCTR,/*add*/
}Dem_InternalDataElementType;

typedef enum
{
    DEM_UPDATE_RECORD_NO,
    DEM_UPDATE_RECORD_YES
}Dem_ExtendedDataRecordUpdateType;
/**guorui DEM  DemDTCClass **/

typedef enum
{
    DEM_DTC_SEV_CHECK_AT_NEXT_HALT,
    DEM_DTC_SEV_IMMEDIATELY   ,
    DEM_DTC_SEV_MAINTENANCE_ONLY ,
    DEM_DTC_SEV_NO_SEVERITY
}Dem_DTCSeverityType;

/*------------------------------------------------------------------------------------------------*\
  TYPEDEFS
\*------------------------------------------------------------------------------------------------*/
typedef uint8 Dem_DTCFunctionalUnitTypeDef;

typedef uint8 Dem_EventDestinationType;

typedef uint32 Dem_UdsDTCType;

typedef Std_ReturnType (*InitMonitorForFunction)(void);
typedef Std_ReturnType (*Dem_CallbackGetFDCFncType)(sint8* FaultDetectionCounter);

typedef Std_ReturnType (*Dem_ReadDataElementFunType)(uint8 size,uint8* Buffer);
typedef void (*Dem_GetInterDataElementFunType)
(
    Dem_InternalDataElementType InteElemType,uint8* Buffer
);

/*Identification of an event by assigned EventId. The EventId is assigned by the DEM.*/
typedef uint16 Dem_EventIdType;
/* Possible values for Dem_EventStatusType. */
typedef uint8 Dem_EventStatusType;
#define DEM_EVENT_STATUS_PASSED                     (uint8)0x00
#define DEM_EVENT_STATUS_FAILED                     (uint8)0x01
#define DEM_EVENT_STATUS_PREPASSED                  (uint8)0x02
#define DEM_EVENT_STATUS_PREFAILED                  (uint8)0x03
/* Possible values for Dem_EventStatusExtendedType; */
typedef uint8 Dem_EventStatusExtendedType;
#define DEM_TEST_FAILED                             (uint8)0x01 
#define DEM_TEST_FAILED_THIS_OPERATION_CYCLE        (uint8)0x02 
#define DEM_PENDING_DTC                             (uint8)0x04 
#define DEM_CONFIRMED_DTC                           (uint8)0x08 
#define DEM_TEST_NOT_COMPLETED_SINCE_LAST_CLEAR     (uint8)0x10 
#define DEM_TEST_FAILED_SINCE_LAST_CLEAR            (uint8)0x20 
#define DEM_TEST_NOT_COMPLETED_THIS_OPERATION_CYCLE (uint8)0x40 
#define DEM_WARNING_INDICATOR_REQUEST               (uint8)0x80


/* Possible values for Dem_OperationCycleStateType. */
typedef uint8 Dem_OperationCycleStateType;
#define DEM_CYCLE_STATE_INIT                                ((uint8)0x00) /*differ*/
#define DEM_CYCLE_STATE_START                               ((uint8)0x01)
#define DEM_CYCLE_STATE_END                                 ((uint8)0x02)


/*DemIndicatorID : Unique identifier of an indicator.*/
typedef uint8 Dem_IndicatorIdType; /*differ*/

/* Possible values for Dem_IndicatorStatusType. */
typedef uint8 Dem_IndicatorStatusType;
#define DEM_INDICATOR_OFF                           (uint8)0x00
#define DEM_INDICATOR_CONTINUOUS                    (uint8)0x01
#define DEM_INDICATOR_BLINKING                      (uint8)0x02
#define DEM_INDICATOR_BLINK_CONT                    (uint8)0x03

/* Possible values for Dem_DTCGroupType :Selects a group of DTCs.*/
typedef uint32 Dem_DTCGroupType;
#define DEM_DTC_GROUP_EMISSION_REL_DTCS     (uint32)0x000000/*selects group of OBDrelevant DTCs*/
#define DEM_DTC_GROUP_BODY_DTCS             (uint32)0x000001 /*selects group of body DTCs */
#define DEM_DTC_GROUP_CHASSIS_DTCS          (uint32)0x000002 /*selects group of chassis DTCs */
#define DEM_DTC_GROUP_NETWORK_COM_DTCS      (uint32)0x000003 /*selects group of network communication DTCs*/
#define DEM_DTC_GROUP_POWERTRAIN_DTCS       (uint32)0x000004 /*selects group of powertrain DTCs */
#define DEM_DTC_GROUP_ALL_DTCS              (uint32)0xFFFFFF/*selects all DTCs*/
/* Possible values for Dem_DTCKindType. */
typedef uint8 Dem_DTCKindType;
#define DEM_DTC_KIND_ALL_DTCS                        0x01/*Select all DTCs*/
#define DEM_DTC_KIND_EMISSION_REL_DTCS               0x02/*Select OBD-relevant DTCs*/

/*Selects/specifies the format of the DTC value*/
typedef uint8 Dem_DTCFormatType;

#define DEM_DTC_FORMAT_OBD 0 /*selects the 2-byte OBD DTC format (refer to DemObdDTC) */
#define DEM_DTC_FORMAT_UDS 1 /*selects the 3-byte UDS DTC format (refer to DemUdsDTC*/

/* Possible values for DTCOrigin:This enum is used to define the location of the events. The definition and use of
the different memory types is OEM-specific. */
typedef uint8 Dem_DTCOriginType;
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY                       ((uint8)0x01)
#define DEM_DTC_ORIGIN_MIRROR_MEMORY                        ((uint8)0x02)
#define DEM_DTC_ORIGIN_PERMANENT_MEMORY                     ((uint8)0x03)
#define DEM_DTC_ORIGIN_SECONDARY_MEMORY                     ((uint8)0x04)
/* Possible values for DTCRequest. */
typedef uint8 Dem_DTCRequestType;
#define DEM_FIRST_FAILED_DTC                                ((uint8)0x01)/*first failed DTC requested*/
#define DEM_MOST_RECENT_FAILED_DTC                          ((uint8)0x02)/*most recent failed DTC requested*/
#define DEM_FIRST_CONFIRMED_DTC      /*differ*/             ((uint8)0x03)/*0x03first detected confirmed DTC requested*/
#define DEM_MOST_RECENT_CONFIRMED_DTC  /*differ*/           ((uint8)0x04)/*most recently detected confirmed DTC requeste*/

typedef uint8 Dem_DTCTranslationFormatType;
#define DEM_DTC_TRANSLATION_ISO15031_6  0x00 /*ISO15031-6 DTC format*/
#define DEM_DTC_TRANSLATION_ISO14229_1  0x01 /*ISO14229-1 DTC format*/ 
#define DEM_DTC_TRANSLATION_SAEJ1939_73 0x02 /*SAEJ1939-73 DTC format*/ 
#define DEM_DTC_TRANSLATION_ISO11992_4  0x03 /*ISO11992-4 DTC format*/ 

/* Possible values for DTCSeverity:Defines the type of a DTCSeverityMask according to ISO14229-1. */
typedef uint8 Dem_FilterForFDCType;
#define DEM_FILTER_FOR_FDC_YES 0x00 /*Fault Detection Counter information used*/ 
#define DEM_FILTER_FOR_FDC_NO  0x01 /*Fault Detection Counter information not used*/ 


/* Possible values for Dem_FilterWithSeverity. */
typedef uint8 Dem_FilterWithSeverityType;
#define DEM_FILTER_WITH_SEVERITY_YES                        ((uint8)0x00)/*Severity information used*/
#define DEM_FILTER_WITH_SEVERITY_NO                         ((uint8)0x01) /*Severity information not used*/

typedef uint8 Dem_InitMonitorReasonType;
#define DEM_INIT_MONITOR_CLEAR   0x01/*Event was cleared and all internal values and states are reset. */ 
#define DEM_INIT_MONITOR_RESTART 0x02/*Operation cycle of the event was (re-)started.*/

/*****************************Dem return types*********************************/
/*****************************Dem return types*********************************/
/*****************************Dem return types*********************************/
/*****************************Dem return types*********************************/


typedef uint8 Dem_ReturnSetFilterType; 
#define DEM_FILTER_ACCEPTED 0x00  /*Filter was accepted*/ 
#define DEM_WRONG_FILTER    0x01  /*Wrong filter selected */

/* Possible values for Dem_ReturnGetStatusOfDTC:Used to return the status of Dem_GetStatusOfDTC */
typedef uint8 Dem_ReturnGetStatusOfDTCType;/*differ*/
#define DEM_STATUS_OK                                       ((uint8)0x00)/*Status of DTC is OK*/
#define DEM_STATUS_WRONG_DTC                                ((uint8)0x01)/*Wrong DTC*/
#define DEM_STATUS_WRONG_DTCORIGIN                          ((uint8)0x02)/*Wrong DTC origin*/
/*#define DEM_STATUS_WRONG_DTCKIND                            ((uint8)0x03)*/ /*DTC kind wrong*/
#define DEM_STATUS_FAILED                                   ((uint8)0x03)/*DTC failed*/
#define DEM_STATUS_PENDING          ((uint8)0x04)/*The requested value is calculated 
asynchronously and currently not available. The caller can retry later.*/

/* Possible values for Dem_ReturnGetNextFilteredDTC:Used to return the status of Dem_GetNextFilteredDTC. */
typedef uint8 Dem_ReturnGetNextFilteredDTCType;
#define DEM_FILTERED_OK                                     ((uint8)0x00)/*Returned next filtered DTC*/
#define DEM_FILTERED_NO_MATCHING_DTC                        ((uint8)0x01)/*No DTC matched*/
#define DEM_FILTERED_PENDING                          ((uint8)0x02)/*The requested value is calculated 
asynchronously and currently not available. The caller can retry later. Only used by asynchronous interfaces.*/

/* Possible values for Dem_ReturnGetNumberOfFilteredDTCType */
typedef uint8 Dem_ReturnGetNumberOfFilteredDTCType;
#define DEM_NUMBER_OK                                       ((uint8)0x00)/*get of number of DTC was successful*/
#define DEM_NUMBER_FAILED                                   ((uint8)0x01)/* get of number of DTC failed*/
#define DEM_NUMBER_PENDING                                  ((uint8)0x02)/* get of number of DTC is pending*/

/* Possible values for Dem_ReturnClearDTC. */
typedef uint8 Dem_ReturnClearDTCType;
#define DEM_CLEAR_OK                                        ((uint8)0x00)/*DTC successfully cleared*/
#define DEM_CLEAR_WRONG_DTC                                 ((uint8)0x01)/*Wrong DTC*/
#define DEM_CLEAR_WRONG_DTCORIGIN                           ((uint8)0x02)/*Wrong DTC origin*/
#define DEM_CLEAR_FAILED                                    ((uint8)0x03)/*DTC not cleared*/
#define DEM_CLEAR_PENDING                                   ((uint8)0x04)/*Clearing of DTC is pending*/

/* Possible values for Dem_ReturnControlDTCSettingType(uint8):Used to return the status of Dem_DisableDTCSetting and Dem_EnableDTCSetting. */
typedef uint8 Dem_ReturnControlDTCSettingType;
#define DEM_CONTROL_DTC_SETTING_OK                          ((uint8)0x00)/*DTC setting control successful*/
#define DEM_CONTROL_DTC_SETTING_N_OK                        ((uint8)0x01)/*DTC setting control not successful*/
#define DEM_CONTROL_DTC_WRONG_DTCGROUP                      ((uint8)0x02)/*DTC setting control not successful because group of DTC was wrong*/


typedef uint8 Dem_ReturnDisableDTCRecordUpdateType; 
#define DEM_DISABLE_DTCRECUP_OK  0x00/*Event memory update of DTC successfully disabled */
#define DEM_DISABLE_DTCRECUP_WRONG_DTC  0x01/*DTC value not existing (in UDS format) */
#define DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN 0x02/*Wrong DTC origin*/ 
#define DEM_DISABLE_DTCRECUP_PENDING  0x03/*Disabling is currently not possible. The caller can retry later. */

typedef uint8 Dem_ReturnGetFreezeFrameDataByRecordType;
#define DEM_GET_FFBYRECORD_OK                   0x00  /*DTC successfully returned */
#define DEM_GET_FFBYRECORD_WRONG_RECORD         0x01  /*Wrong record */
#define DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD    0x02  /*No DTC for record available */

/* Possible values for Dem_ReturnGetExtendedDataRecordByDTC. */
typedef uint8 Dem_ReturnGetExtendedDataRecordByDTCType;
#define DEM_RECORD_OK               0x00 /*Extended data record successfully returned*/ 
#define DEM_RECORD_WRONG_DTC        0x01/*DTC value not existing (in UDS format)*/ 
#define DEM_RECORD_WRONG_DTCORIGIN  0x02/*Origin wrong*/ 
#define DEM_RECORD_WRONG_NUMBER     0x03/*Record number is not supported by configuration and therefore invalid*/ 
#define DEM_RECORD_WRONG_BUFFERSIZE 0x04/*Provided buffer to small Range: */
#define DEM_RECORD_PENDING          0x05

/* Possible values for Dem_ReturnGetDTCByOccurrenceTime. */
typedef uint8 Dem_ReturnGetDTCByOccurrenceTimeType;
#define DEM_OCCURR_OK                                       ((uint8)0x00)/*Status of DTC was OK*/
#define DEM_OCCURR_NOT_AVAILABLE  ((uint8)0x01)/*no DTC is matching the requested occurrence time*/

/* Possible values for Dem_ReturnGetFreezeFrameDataByDTC. */
typedef uint8 Dem_ReturnGetFreezeFrameDataByDTCType;
#define DEM_GET_FFDATABYDTC_OK                              ((uint8)0x00)/*Size successfully returned.*/
#define DEM_GET_FFDATABYDTC_WRONG_DTC                       ((uint8)0x01)/*Wrong DTC*/
#define DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN                 ((uint8)0x02)/*Wrong DTC origin*/
#define DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER              ((uint8)0x03)/*Wrong Record Number*/
#define DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE                ((uint8)0x04)/*provided buffer size to small*/
#define DEM_GET_FFDATABYDTC_PENDING                         ((uint8)0x05)/*The requested value is currently not available. The caller can retry later.*/

typedef uint8 Dem_ReturnGetSizeOfFreezeFrameByDTCType;
#define DEM_GET_SIZEOFFF_OK          0x00 
#define DEM_GET_SIZEOFFF_WRONG_DTC   0x01
#define DEM_GET_SIZEOFFF_WRONG_DTCOR 0x02
#define DEM_GET_SIZEOFFF_WRONG_RNUM  0x03
#define DEM_GET_SIZEOFFF_PENDING     0x04

/* Possible values for Dem_ReturnGetSizeOfExtendedDataRecordByDTC. */
typedef uint8 Dem_ReturnGetSizeOfExtendedDataRecordByDTCType;/*deffer*/
#define DEM_GET_SIZEOFEDRBYDTCTYPE_OK                       ((uint8)0x00)/*Size successfully returned.*/
#define DEM_GET_SIZEOFEDRBYDTCTYPE_WRONG_DTC                ((uint8)0x01)/*Wrong DTC*/
#define DEM_GET_SIZEOFEDRBYDTCTYPE_WRONG_DTCORIGIN          ((uint8)0x02)/*Wrong DTC origin*/
#define DEM_GET_SIZEOFEDRBYDTCTYPE_WRONG_RECORDNUMBER       ((uint8)0x04)/*Wrong Record Number*/
#define DEM_GET_SIZEOFEDRBYDTC_PENDING                      ((uint8)0x05)/*The requested value is currently not available. The caller can retry later.*/


/* Possible values for Dem_ReturnGetSeverityOfDTC. */
typedef uint8 Dem_ReturnGetSeverityOfDTCType;
#define DEM_GET_SEVERITYOFDTC_OK                            ((uint8)0x00)/*Severity successfully returned.*/
#define DEM_GET_SEVERITYOFDTC_WRONG_DTC                     ((uint8)0x01)/*Wrong DTC*/
#define DEM_GET_SEVERITYOFDTC_WRONG_DTCORIGIN               ((uint8)0x02)/*Wrong DTC origin*/
#define DEM_GET_SEVERITYOFDTC_NOSEVERITY                    ((uint8)0x03)/*Severity information is not available*/

typedef uint8 Dem_ReturnGetFunctionalUnitOfDTCType; 
#define DEM_GET_FUNCTIONALUNITOFDTC_OK  0x00  /*Functional unit successfully returned. */
#define DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC 0x01  /*DTC value not existing (in UDS format) */

/*DemTypeOfDTCSupported
 This parameter defines the format returned by Dem_GetTranslationType.*/
typedef uint8 Dem_TypeOfDTCSupportedType;/*Not find*/
#define DEM_ISO15031_6              ((uint8)0x00)/*ISO15031-6DTCFormat*/
#define DEM_ISO14229_1              ((uint8)0x01)/*ISO14229-1DTCFormat*/
#define DEM_SAEJ1939_73             ((uint8)0x02)/*SAEJ1939-73DTCFormat*/
#define DEM_ISO11992_4              ((uint8)0x03)/*ISO11992-4DTCFormat*/


/*DemOperationCycleType Different DEM operation cycle types.
 Operation cycles types for the DEM to be supported by cycle-state APIs. 
 Further cycle types can be specified as part of the DEM delivery.*/
typedef uint8 Dem_OperationCycleIdType;
#define DEM_NUMBER_OF_OPERATION_CYCLES          (uint8)6

#define DEM_OPCYC_IGNITION          (uint8)0x00   /*Ignition ON / OFF cycle */
#define DEM_OPCYC_OBD_DCY           (uint8)0x01    /*OBD Driving cycle*/
#define DEM_OPCYC_OTHER             (uint8)0x02    /*further operation cycle*/
#define DEM_OPCYC_POWER             (uint8)0x03    /*Power ON / OFF cycle */
#define DEM_OPCYC_TIME              (uint8)0x04    /*Time based operation cycle */
#define DEM_OPCYC_WARMUP            (uint8)0x05    /*OBD OBD Warm up cycle */


/* Different debouncing algorithms. */
#define DEM_DEBOUNCE_MONITOR_INTERNAL   0x00u
#define DEM_DEBOUNCE_COUNTER_BASED      0x01u
#define DEM_DEBOUNCE_MIXED              0x03u
/*DemFreezeFrameCapture &DemExtendedDataCapture 
This parameter defines the point in time, when the freeze frame data / Extended Data
collection is done for the initial event memory entry. */
#define DEM_TRIGGER_CONFIRMEDDTC        0x00u/*Triggers the collection of freeze frame data/extended data if the UDS DTC status bit 3 (confirmed DTC) changes from 0 to 1. (e.g. for specific OBD events)*/
#define DEM_TRIGGER_PENDINGDTC          0x01u/*Triggers the collection of freeze frame data/extended data if the UDS DTC status bit 2 (pending DTC) changes from 0 to 1.*/
#define DEM_TRIGGER_TESTFAILED          0x02u/*Triggers the collection of freeze frame data/extended data if the UDS DTC status bit 0 (TestedFailed) changes from 0 to 1.*/
/*DemTypeOfFreezeFrameRecordNumeration
This parameter defines the type of assigning freeze frame record
numbers for event-specific freeze frame records.*/
#define DEM_FF_RECNUM_CALCULATED        0x01u/*freeze frame records will be numbered consecutive starting by 1 in their chronological order*/
#define DEM_FF_RECNUM_CONFIGURED        0x02u/*freeze frame records will be numbered based on the given configuration in their chronological order*/
/*Event Memory Status*/
#define DEM_EVENT_MEMORY_EMPTY          ((uint8)0x00)
#define DEM_EVENT_MEMORY_NOT_OVERFLOW   ((uint8)0x01)
#define DEM_EVENT_MEMORY_OVERFLOW       ((uint8)0x02)
/*if the client has set the DTCSnapshotRecordNumber/DTCExtendedDataRecordNumber to FF hex,
  report all DTCSnapshot/ExtendedData records by DTC number*/
#define DEM_REPORT_ALL_RECORD           ((uint8)0xFF)

/* DEM Bit masks. */
#define DEM_BIT0                        ((uint8)0x01)
#define DEM_BIT1                        ((uint8)0x02)
#define DEM_BIT2                        ((uint8)0x04)
#define DEM_BIT3                        ((uint8)0x08)
#define DEM_BIT4                        ((uint8)0x10)
#define DEM_BIT5                        ((uint8)0x20)
#define DEM_BIT6                        ((uint8)0x40)
#define DEM_BIT7                        ((uint8)0x80)
#define DEM_NOT_BIT0                    ((uint8)0xfe)        
#define DEM_NOT_BIT1                    ((uint8)0xfd)
#define DEM_NOT_BIT2                    ((uint8)0xfb)
#define DEM_NOT_BIT3                    ((uint8)0xf7)
#define DEM_NOT_BIT4                    ((uint8)0xef)
#define DEM_NOT_BIT5                    ((uint8)0xdf)
#define DEM_NOT_BIT6                    ((uint8)0xbf)
#define DEM_NOT_BIT7                    ((uint8)0x7f)

/**************************************************************************************************\
  DEM Default PreCompile Configeration 
\**************************************************************************************************/

#ifndef DEM_VERSION_INFO_API                                              
#define DEM_VERSION_INFO_API                  STD_ON 
#endif

/*DCM module is in use or not */
#ifndef DEM_DCM_MODULE_SUPPORT                                              
#define DEM_DCM_MODULE_SUPPORT                STD_ON 
#endif

/*Service Interface DiagnosticInfo & General interface  provides the capability to obtain event information for SW-C */
#ifndef DEM_DIAG_INFO_INTERFACE_SUPPORT                                              
#define DEM_DIAG_INFO_INTERFACE_SUPPORT       STD_ON 
#endif
 /*The detection of development errors is configurable (ON / OFF) at precompile time. The switch 
 DemDevErrorDetect (refer to DemGeneral) shall activate or deactivate the detection of all development errors.*/
#ifndef DEM_DEV_ERROR_DETECT                                              
#define DEM_DEV_ERROR_DETECT                  STD_OFF      
#endif
/*------------------------------------------------------------------------------------------------*\
    Event  Configeration
\*------------------------------------------------------------------------------------------------*/
/*Number of Event */
#if 0
#ifndef DEM_NUMBER_OF_EVENT                                              
#define DEM_NUMBER_OF_EVENT                10u 
#endif
#endif
/*------------------------------------------------------------------------------------------------*\
    Debounce Algorithm  Configeration
\*------------------------------------------------------------------------------------------------*/
/* Type of debouncing algorithm. */

#if(DEM_DEBOUNCE_ALGORTHM_TYPE !=DEM_DEBOUNCE_MONITOR_INTERNAL)
/*Number of Counter based debounce algorithm*/
#ifndef DEM_NUMBER_OF_PDB_COUNTER_BASED                                              
#define DEM_NUMBER_OF_PDB_COUNTER_BASED     ((uint8)1)
#endif
# endif                                                       
/*------------------------------------------------------------------------------------------------*\
    Operation  Cycle Reference  Configeration
\*------------------------------------------------------------------------------------------------*/
#ifndef DEM_OPERATION_CYCLE_REF                                              
#define DEM_OPERATION_CYCLE_REF             (uint8)0x00/*DEM_OPCYC_IGNITION*/
#endif
/*------------------------------------------------------------------------------------------------*\
  Non-Volatile RAM/Event Memory Configeration 
\*------------------------------------------------------------------------------------------------*/
/*Maximum number of events which can be stored in the primary memory*/
/*The kind of additional Event Memory which DEM supports */
/*This configuration switch defines, whether support for event displacement is enabled or not.*/
#ifndef DEM_EVENT_DISPLACEMENT_SUPPORT                                             
#define DEM_EVENT_DISPLACEMENT_SUPPORT        STD_ON
#endif
/*------------------------------------------------------------------------------------------------*\
   Aging  Configeration
\*------------------------------------------------------------------------------------------------*/
/*Switch to allow aging/unlearning of the event or not.true: aging a lowed false: aging not allowed*/
#ifndef DEM_EVENT_AGING_ALLOWED                                              
#define DEM_EVENT_AGING_ALLOWED                STD_OFF 
#endif

#if(DEM_EVENT_AGING_ALLOWED == STD_ON)
/*DemAgingCycleRef */
#ifndef DEM_AGING_CYCLE_REF                                              
#define DEM_AGING_CYCLE_REF                    (uint8)0x00/*DEM_OPERATION_CYCLE_REF*/     
#endif
 /*Number ot aging cycles needed to unlearn/delete the event.*/
#ifndef DEM_EVENT_AGING_CYCLE_COUNTER_THRESHOLD                                              
#define DEM_EVENT_AGING_CYCLE_COUNTER_THRESHOLD ((uint8)40) 
#endif
#endif /*DEM_EVENT_AGING_ALLOWED == STD_ON*/
/*------------------------------------------------------------------------------------------------*\
  DTC Configeration 
\*------------------------------------------------------------------------------------------------*/
/*DTC Type that DEM support
This parameter defines the format returned by Dem_GetTranslationType. */
#ifndef DEM_TYPE_OF_DTC_SUPPORT                                              
#define DEM_TYPE_OF_DTC_SUPPORT                 ((uint8)0x01)/*DEM_ISO14229_1*/ 
#endif
/*DTC Kind that DEM support: DEM_DTC_KIND_ALL_DTCS/DEM_DTC_KIND_EMISSION_REL_DTCS*/
#ifndef DEM_KIND_OF_DTC_SUPPORT                                              
#define DEM_KIND_OF_DTC_SUPPORT                 1u/*DEM_DTC_KIND_ALL_DTCS*/
#endif
/*DTC is stored in which kind of EventMemory*/
#ifndef DEM_DTC_ORIGIN_MEMORY                                              
#define DEM_DTC_ORIGIN_MEMORY                   ((uint8)0x01)/*DEM_DTC_ORIGIN_PRIMARY_MEMORY*/
#endif
/*DTC Status Availability Mask that DEM support 
Description Mask for the supported DTC status bits by the DEM. This mask is used by UDS service 0x19.*/
#ifndef DEM_STATUS_AVAILABILITY_MASK                                              
#define DEM_STATUS_AVAILABILITY_MASK            0xFFu
#endif
/*The configuration parameter is used to determine which dtc status bit is stored in non-volatile
if the DEM module supports operation cycles over power cycles,status bit 1  needs to be stored non-volatile*/
#define DEM_STATUS_BIT_STORAGE_MASK             (uint8)(DEM_STATUS_AVAILABILITY_MASK&0x3C)
/* Dtc
testNotCompletedThisMonitoringCycle = TRUE.&testNotCompletedSinceLastClear= TRUE */
#define DEM_DTC_STATUS_INIT_VALUE               (uint8)(DEM_STATUS_AVAILABILITY_MASK&0x50)
                                                                    
/*DTC Severity Mask that DEM support*/
#ifndef DEM_DTC_SEVERITY_MASK                                              
#define DEM_DTC_SEVERITY_MASK                   ((uint8)0xE0)
#endif
/*------------------------------------------------------------------------------------------------*\
    Freeze Frame Record  Configeration
\*------------------------------------------------------------------------------------------------*/
/*Size of Freez Frame Record */
/*DemTypeOfFreezeFrameRecordNumeration 
This parameter defines the type of assigning freeze frame record
numbers for event-specific freeze frame records.*/
#ifndef DEM_TYPE_OF_FF_RECORD_NUMERATION                                              
#define DEM_TYPE_OF_FF_RECORD_NUMERATION        (0x02u) /*DEM_FF_RECNUM_CONFIGURED*/
#endif
/*This parameter defines the maximum number of occurrences,a specific event memory entry is allowed,
 to be stored in NVRAM immediately*/
#ifndef DEM_MAX_OCCURRENCE_FF_STORAGE                                             
#define DEM_MAX_OCCURRENCE_FF_STORAGE           1u 
#endif
/*Number of Freez Frame Record */
#if(DEM_TYPE_OF_FF_RECORD_NUMERATION ==DEM_FF_RECNUM_CONFIGURED)            
#ifndef DEM_MAX_NUMBER_FF_RECORDS                                              
#define DEM_MAX_NUMBER_FF_RECORDS               ((uint8)2)
#endif
#else
#ifndef DEM_MAX_NUMBER_FF_RECORDS                                              
#define DEM_MAX_NUMBER_FF_RECORDS               DEM_MAX_OCCURRENCE_FF_STORAGE
#endif
#endif
/*Max Number of Did in one Freez Frame Record */
#ifndef DEM_MAX_NUMBER_DID_IN_FF_RECORDS                                              
#define DEM_MAX_NUMBER_DID_IN_FF_RECORDS        ((uint8)1)
#endif
/*Defines the maximum number for prestored freeze frames. If set to 0, then freeze frame prestorage
 is not supported by the ECU.*/
#ifndef DEM_MAX_NUMBER_PRESTORED_FF                                              
#define DEM_MAX_NUMBER_PRESTORED_FF             0u
#endif
/*DemFreezeFrameCapture Mode:This parameter defines the point in time, when the freeze frame data
collection is done for the initial event memory entry. */
#ifndef DEM_FREEZE_FRAME_CAPTURE  
#define DEM_FREEZE_FRAME_CAPTURE                2u/*DEM_TRIGGER_TESTFAILED */
#endif

/********************** Event Status Info*************************/
typedef struct
{
    sint16 ssFCounterCB;/*CB :counter based*/
    uint8  ucEvnCurStatus;/* event current status operation cycle*/
    uint8  ucEvnLstStatus;/*last operation cycle*/
    uint8  ucFaultOccurCounter;
    uint8  ucFaultPendingCounter;
    uint8  ucAgedCounter;
    uint8  ucAgingCounter;
    /*uint8  ucFirstPowerF;*/
}Dem_EventStatusInfoType;/*DTCStatusInfoType*/

typedef struct
{
    uint8  DtcStatus;/*current operation cycle*/
    uint8  ucFaultPendingCounter;
    uint8  ucAgedCounter;
    uint8  ucAgingCounter;
    /*uint8  ucFirstPowerF;*/
}Dem_DtcStatusInfoType;/*DTCStatusInfoType*/


/*********************** EventMemory ******************************/
typedef struct
{
    uint16          DemStoredDatValid0;
    uint16          DemStoredDatValid1;
    Dem_EventIdType FirstFailedEvent;
    Dem_EventIdType FirstConfirmedEvent;
    Dem_EventIdType MostRecentFailedEvent;
    Dem_EventIdType MostRecentConfirmedEvent;
}Dem_EventMemoryHeadType;

typedef struct
{
    Dem_EventIdType             EmEventId; /*Event Mem  Event identifier*/
    uint16                       EventOccCnt;
    Dem_UdsDTCType              DTCNum;
    uint8                       FreezeFrameData/*[DEM_MAX_OCCURRENCE_FF_STORAGE] TBD*/[DEM_MAX_FF_RECORD_SIZE];
    uint8                       ExtendedData[DEM_EXTENDED_DATA_SIZE];
}Dem_EventMemoryEntryType;/*entry*/

typedef struct
{
    Dem_EventMemoryHeadType   EventMemoryHead;
    Dem_EventStatusInfoType   EventExtendStatus[DEM_NUMBER_OF_EVENT];
    Dem_EventMemoryEntryType  EventMemoryEntry[DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY];
}Dem_StorageMemType;

typedef struct
{
    uint16          NvMemStausE;
}Dem_EventMemoryEndType;

/*------------------------------------------------------------------------------------------------*\
   PostBuild configeration Data type  define
\*------------------------------------------------------------------------------------------------*/
typedef struct
{
    Dem_UdsDTCType               DemUdsDTC;
    Dem_DTCFunctionalUnitTypeDef DemDTCFunctionalUnit;
    Dem_DTCSeverityType          DemDTCSeverity;
    boolean                      DemImmediateNvStorage;
    InitMonitorForFunction       DemCallbackInitMForFFnc;/* <Module>_DemInitMonitorFor<Function>*/
}Dem_DTCClassType;

typedef struct
{
    /*Dem_EventIdType              DemEventId;*/
    Dem_EventKindType            DemEventKind;
    /* >>> This parameter is only 
required for calculated record numeration (refer to 
DemTypeOfFreezeFrameRecordNumeration). 
DemTypeOfFreezeFrameRecordNumeration is cfg DEM_FF_RECNUM_CALCULATED*/
    uint8                        DemMaxNumberFreezeFrameRecords;/*This parameter is only required for calculated record numeration*/
    uint16                       DemDTCClassRef;
    uint16                       DemExtendedDataClassRef;
    uint16                       DemFreezeFrameClassRef;
}Dem_EventParameterType;

typedef  struct
{
    boolean DemAgingAllowed;
    uint16  DemAgingCycleCounterThreshold;
    boolean DemConsiderPtoStatus;/*no use*/ /*This parameter is TRUE, when the event is affected by the Dem PTO handling.*/
    Dem_EventDestinationType DemEventDestination;
    uint16 DemEventFailureCycleCounterThreshold;/*no use*/
    uint8 DemEventPriority;
    Dem_EventSignificanceType DemEventSignificance;/*not used*/
    boolean DemFFPrestorageSupported;
    /* >> Reference to the cycle which is triggering the aging of the event. This can 
either be the same as the operation cycle of the event, or a separate aging 
cycle reported via API Dem_SetAgingCycleState. If external aging is 
configured (refer to DemAgingCycleCounterProcessing), this parameter is 
not used.*/
    uint8 DemAgingCycleRef;
    uint8 DemEnableConditionGroupRef;/*not used*/
    uint8 DemEventFailureCycleRef;
    uint8 DemOperationCycleRef;
    uint16 DemStorageConditionGroupRef;

}Dem_EventClassType;

typedef struct
{
    struct
    {
        sint16  DemDebounceCounterDecrementStepSize;/*PREPASSED*/
        sint16  DemDebounceCounterIncrementStepSize;/*PREFAILED*/
        sint16  DemDebounceCounterPassedThreshold;
        sint16  DemDebounceCounterFailedThreshold;
        boolean DemDebounceCounterJumpDown;
        boolean DemDebounceCounterJumpUp;
        sint16   DemDebounceCounterJumpDownValue;
        sint16   DemDebounceCounterJumpUpValue;

    }DemDebounceCounterBased;
    struct
    {
        uint16 DemDebounceTimeFailedThreshold;
        uint16 DemDebounceTimePassedThreshold;
    }DemDebounceTimeBase;
    struct
    {
        Dem_CallbackGetFDCFncType DemCallbackGetFDCFnc;
    }DemDebounceMonitorInternal;
    struct
    {
        uint8 DebounceAlgorithmRef;
    }DemEventDebounceAlgorithm;
}Dem_DebounceAlgorithmClassType;

typedef struct
 {
     uint8                           DemDataElementDataSize;
     Dem_InternalDataElementType     DemInternalDataElement;
 }Dem_InternalDataElementClassType;
 typedef struct
 {
     uint8                       DemDataElementDataSize;
     Dem_ReadDataElementFunType  DemDataElementReadFnc;
 }Dem_ExternalCSDataElementClassType;
 typedef struct
 {
     uint8                       DemDataElementDataSize;
     uint8*                      DemDataElementAddr;
 }Dem_ExternalSRDataElementClassType;

/****************************************************/
/*******************FF data***********************/
/****************************************************/
typedef struct
{
    uint16 DemDidIdentifier;
    Dem_DataElementClassType DemDidDataElementClassRef;
    uint16                   DemDataIndex;
}Dem_DidClassType;

typedef struct
{
    uint8             DemFreezeFrameRecordNumber;
    uint8             DemSnapshotRecordNumberOfIdentifiers;
    const Dem_DidClassType* const DemDidClassRef;
}Dem_FreezeFrameRecNumClassType;

typedef struct
{
    uint16                          DemNumberOfRecordNum;
    const Dem_FreezeFrameRecNumClassType* const DemFreezeFrameRecNumClassRef;
}Dem_FreezeFrameClassType;

/****************************************************/
/*******************extended data***********************/
/****************************************************/
typedef struct
{
    Dem_DataElementClassType DemDataElementClassRef;
    uint16                   DemDataIndex;
}Dem_ExtendedDataElementType;


typedef struct
{
    uint8                    DemExtendedDataRecordNumber;
    Dem_ExtendedDataRecordUpdateType DemExtendedDataRecordUpdate;
    uint8             DemExtendedRecordNumberOfIdentifiers;
    const Dem_ExtendedDataElementType *const DemExtendedDataElement;
}Dem_ExtendedDataRecordClassType;

typedef struct
{
    uint16                           DemNumberOfExtendRecNum;
    const Dem_ExtendedDataRecordClassType*const DemExtendedDataRecordClassRef;
}Dem_ExtendedDataClassType;

/*******************************************************************************/
/*******************************************************************************/
/***************************indicators**********************************/
/*******************************************************************************/
/*******************************************************************************/
/*
This container contains the configuration (parameters) for 
Indicators. Note that this container definition does not explicitly 
define a symbolic name parameter. Instead, the short name of 
the container will be used in the Ecu Configuration Description to 
specify the symbolic name of the INDICATOR_NAME.
*/


typedef Dem_IndicatorStatusType Dem_IndicatiorBehaviourType;

/*DemIndicatorFailureCycleSource*/
#define DEM_FAILURE_CYCLE_EVENT     0
#define DEM_FAILURE_CYCLE_INDICATOR 1
typedef struct
{
    Dem_IndicatiorBehaviourType DemIndicatorBehaviour;
    uint8  DemIndicatorFailureCycleSource;
    uint16 DemIndicatorFailureCycleCounterThreshold;
    uint16 DemIndicatorHealingCycleCounterThreshold;
    uint16 DemIndicatorFailureCycleRef;
    uint16 DemIndicatorHealingCycleRef;
    uint16 DemIndicatorRef;
}Dem_IndicatorAttributeType;

#endif /* _DEM_TYPES_H_ */

/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem_Cfg.h
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Dem module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Dem module configuration File
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
*   04.03.01    26/11/2016     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/
#ifndef _DEM_CFG_H_
#define _DEM_CFG_H_

/*******************************************************************************
*   Include files
*******************************************************************************/
#define DEM_VERSION_INFO_API                    STD_OFF
#define DEM_NUMBER_OF_EVENT                     72u
#define DEM_NUMBER_OF_DTC                       72u
#if(DEM_NUMBER_OF_EVENT != DEM_NUMBER_OF_DTC)
    #error "DEM_NUMBER_OF_EVENT shuould equal to DEM_NUMBER_OF_DTC !"
#endif
/*------------------------------------------------------------------------------------------------
*  Debounce Algorithm  Configeration
*------------------------------------------------------------------------------------------------*/
/* Type of debouncing algorithm. */
#define DEM_DEBOUNCE_ALGORTHM_TYPE              DEM_DEBOUNCE_COUNTER_BASED
/*------------------------------------------------------------------------------------------------
*  Non-Volatile RAM Configeration 
*------------------------------------------------------------------------------------------------*/
/* Maximum number of events which can be stored in the primary memory*/
#define DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY      72u
/*------------------------------------------------------------------------------------------------
*  Event information located in which kind memory 
*------------------------------------------------------------------------------------------------*/
#define DEM_DTC_ORIGIN_MEMORY                   DEM_DTC_ORIGIN_PRIMARY_MEMORY
/*------------------------------------------------------------------------------------------------
*  DTC Configeration 
*------------------------------------------------------------------------------------------------*/
/* This parameter defines the format returned by Dem_GetTranslationType. */
#define DEM_TYPE_OF_DTC_SUPPORT                 DEM_ISO15031_6
#define DEM_KIND_OF_DTC_SUPPORT                 DEM_DTC_KIND_ALL_DTCS
#define DEM_STATUS_AVAILABILITY_MASK            (uint8)0xffu
#define DEM_DTC_SEVERITY_MASK                   (uint8)0xE0u
/*------------------------------------------------------------------------------------------------
*     Extended Data Record  Configeration
*------------------------------------------------------------------------------------------------*/
#define DEM_EXTDATA_RECORD_UPDATE               DEM_UPDATE_RECORD_YES 
/*------------------------------------------------------------------------------------------------
*    DEM Task  Configeration
*------------------------------------------------------------------------------------------------*/
/*DemTaskTime Allow to configure the time for the periodic cyclic task.*/
#define DEM_TASK_TIME                           10u/*ms*/
/*DEM_DemStatusBitStorageTestFailed*/
#define DEM_MAX_FF_RECORD_SIZE                  20u
#define DEM_EXTENDED_DATA_SIZE                  4u
#define DEM_CFG_MAXNUMBEROFRECORDNUMBER         2
#define DEM_CFG_MAXNUMBEROFEXTENDEDNUM          2

#define Dem_EnableInterrupt()
#define Dem_DisableInterrupt()

#endif /* _DEM_CFG_H_ */




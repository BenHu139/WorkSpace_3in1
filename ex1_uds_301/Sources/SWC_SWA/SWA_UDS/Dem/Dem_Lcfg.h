/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem_LCfg.h
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
#ifndef _DEM_LCFG_H_
#define _DEM_LCFG_H_
#include "Dem_Cfg.h"

#define DTC_0xFE0010_INDEX          (0U)         
#define DTC_0xFE000F_INDEX          (1U)         
#define DTC_0xFE0012_INDEX          (2U)         
#define DTC_0xFE0011_INDEX          (3U)         
#define DTC_0xFE0030_INDEX          (4U)         
#define DTC_0xFE002F_INDEX          (5U)         
#define DTC_0xFE0050_INDEX          (6U)         
#define DTC_0xFE004F_INDEX          (7U)         
#define DTC_0xFE0072_INDEX          (8U)         
#define DTC_0xFE0071_INDEX          (9U)         
#define DTC_0xFE0090_INDEX          (10U)        
#define DTC_0xFE008F_INDEX          (11U)        
#define DTC_0xFE00B0_INDEX          (12U)        
#define DTC_0xFE00AF_INDEX          (13U)        
#define DTC_0xFE00D2_INDEX          (14U)        
#define DTC_0xFE00D1_INDEX          (15U)        
#define DTC_0xFE00F2_INDEX          (16U)        
#define DTC_0xFE00F1_INDEX          (17U)        
#define DTC_0xFE010B_INDEX          (18U)        
#define DTC_0xFE0122_INDEX          (19U)        
#define DTC_0xFE0140_INDEX          (20U)        
#define DTC_0xFE0162_INDEX          (21U)        
#define DTC_0xFE0182_INDEX          (22U)        
#define DTC_0xFE01AB_INDEX          (23U)        
#define DTC_0xFE01CB_INDEX          (24U)        
#define DTC_0xFE01EB_INDEX          (25U)        
#define DTC_0xFE020B_INDEX          (26U)        
#define DTC_0xFE0230_INDEX          (27U)        
#define DTC_0xFE022F_INDEX          (28U)        
#define DTC_0xFE024B_INDEX          (29U)        
#define DTC_0xFE026B_INDEX          (30U)        
#define DTC_0xFE0290_INDEX          (31U)        
#define DTC_0xFE028F_INDEX          (32U)        
#define DTC_0xFE02A3_INDEX          (33U)        
#define DTC_0xFE02A6_INDEX          (34U)        
#define DTC_0xFE02A4_INDEX          (35U)        
#define DTC_0xFE02E0_INDEX          (36U)        
#define DTC_0xFE0300_INDEX          (37U)        
#define DTC_0xFE0320_INDEX          (38U)        
#define DTC_0xFE0340_INDEX          (39U)        
#define DTC_0xFE02AA_INDEX          (40U)        
#define DTC_0xFE02AB_INDEX          (41U)        
#define DTC_0xFE02CB_INDEX          (42U)        
#define DTC_0xFE02EA_INDEX          (43U)        
#define DTC_0xFE030B_INDEX          (44U)        
#define DTC_0xFE032B_INDEX          (45U)        
#define DTC_0xFE034B_INDEX          (46U)        
#define DTC_0xFE036B_INDEX          (47U)        
#define DTC_0xFE038B_INDEX          (48U)        
#define DTC_0xFE03AA_INDEX          (49U)        
#define DTC_0xFE03CB_INDEX          (50U)        
#define DTC_0xFE03EB_INDEX          (51U)        
#define DTC_0xFE040B_INDEX          (52U)        
#define DTC_0xFE042B_INDEX          (53U)        
#define DTC_0xFE044B_INDEX          (54U)        
#define DTC_0xFE046B_INDEX          (55U)        
#define DTC_0xFE048B_INDEX          (56U)        
#define DTC_0xFE04AB_INDEX          (57U)        
#define DTC_0xFE04CA_INDEX          (58U)        
#define DTC_0xFE04EB_INDEX          (59U)        
#define DTC_0xFE050B_INDEX          (60U)        
#define DTC_0xFE052B_INDEX          (61U)        
#define DTC_0xFE054A_INDEX          (62U)        
#define DTC_0xFE056B_INDEX          (63U)        
#define DTC_0xFE058B_INDEX          (64U)        
#define DTC_0xFE05AB_INDEX          (65U)        
#define DTC_0xFE05CB_INDEX          (66U)        
#define DTC_0xFE05C0_INDEX          (67U)        
#define DTC_0xFE05EB_INDEX          (68U)        
#define DTC_0xFE0610_INDEX          (69U)        
#define DTC_0xFE060F_INDEX          (70U)        
#define DTC_0xFE064B_INDEX          (71U)        



extern const Dem_DebounceAlgorithmClassType DemDebounceAlgorithmClassTab[];
extern const Dem_EventClassType  DemEventClassSet[];
extern const Dem_FreezeFrameClassType DemFreezeFrameClassTab0[];
extern const Dem_EventParameterType DemEventParameterTab[];
extern const Dem_ExternalCSDataElementClassType Dem_ExternalCSDataElementClassTab[];
extern const Dem_ExternalSRDataElementClassType Dem_ExternalSRDataElementClassTab[];
extern const Dem_DTCClassType DemDTCClassSet[];
extern const Dem_ExtendedDataClassType DemExtendedDataClassTab0[];
extern const Dem_InternalDataElementClassType DemInternalDataElementClassTab[];

#endif


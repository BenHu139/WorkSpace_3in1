/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Std_Types.h
********************************************************************************
*   Project/Product : Common
*   Title           : Std_Types.h 
*   Author          : ning.chen
********************************************************************************
*   Description     : AUTOSAR Standard types file                    
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
*   01.00.00    13/06/2013    ning.chen     N/A          Original
*   01.00.01    17/07/2013    ning.chen     N/A          DPN_COMMON_130717_01
*   01.00.02    15/08/2013    ning.chen     N/A          D10_COMMON01_130815_01
*   01.00.03    08/01/2014    ning.chen     N/A          D10_COMMON01_140108_01
********************************************************************************
* END_FILE_HDR*/

#ifndef _UDS_TYPES_H_
#define _UDS_TYPES_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "Std_Types.h"
#include "Platform_Types.h"
#include "Compiler.h"


/*******************************************************************************
*   Macro 
*******************************************************************************/
                      
/*******************************************************************************
*   Typedef 
*******************************************************************************/                                                                   

typedef struct                                          
{
    uint16 vendorID;                           
    uint16 moduleID;
    uint8  instanceID;
    uint8  sw_major_version;                         
    uint8  sw_minor_version;
    uint8  sw_patch_version;
}Std_VersionInfoType;

#endif  /* _STD_TYPES_H_ */

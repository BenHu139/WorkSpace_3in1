/*  BEGIN_FILE_HDR
***********************************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information contained in this 
*   doc should not be reproduced, or used, or disclosed without the written authorization from 
*   HiRain Technologies.
***********************************************************************************************
*   File Name       : Det.c
***********************************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : Development Error Tracer Source File
*   Author          : HeYang
***********************************************************************************************
*   Description     : Implementation of Development Error Tracer                       
*
***********************************************************************************************
*   Limitations     : 
*
***********************************************************************************************
*
***********************************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   1.0         2012/6/6       HeYang       N/A          Original
*
***********************************************************************************************
* END_FILE_HDR*/

#include "Uds_Types.h"
#include "Det.h"
 uint8 ErrorIdTest=0;
void Det_ReportError(uint16 ModuleId,
                              uint8 InstanceId,
                              uint8 ApiId,
                              uint8 ErrorId)
{
    ErrorIdTest= ErrorId;
}
  

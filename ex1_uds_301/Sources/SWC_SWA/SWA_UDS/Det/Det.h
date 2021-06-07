/*  BEGIN_FILE_HDR
***********************************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information contained in this 
*   doc should not be reproduced, or used, or disclosed without the written authorization from 
*   HiRain Technologies.
***********************************************************************************************
*   File Name       : Det.h
***********************************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : Development Error Tracer head File
*   Author          : HeYang
***********************************************************************************************
*   Description     : Includes all user relevant information for the tracing of
*                     development errors.                      
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
#ifndef DET_H
#define DET_H
#include "Uds_Types.h"
/**********************************************************************************************************************
*  Declarations  of services
*********************************************************************************************************************/

extern void Det_ReportError(uint16 ModuleId,
                                      uint8 InstanceId,
                                      uint8 ApiId,
                                      uint8 ErrorId);
  
#endif

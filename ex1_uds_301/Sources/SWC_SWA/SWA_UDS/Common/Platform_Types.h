/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Platform_Types.h
********************************************************************************
*   Project/Product : Common
*   Title           : Platform_Types.h 
*   Author          : ning.chen
********************************************************************************
*   Description     : platform related types                         
*
********************************************************************************
*   Limitations     : only used for Freescale S12X 
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
*   01.00.02    15/08/2013    ning.chen     N/A          D10_COMMON51_130815_01
*   01.00.03    08/01/2014    ning.chen     N/A          D10_COMMON51_140108_01
********************************************************************************
* END_FILE_HDR*/

#ifndef _PLATFORM_TYPES_H_
#define _PLATFORM_TYPES_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
*   Macro 
*******************************************************************************/

/*******************************************************************************
*   Typedef 
*******************************************************************************/

typedef s8         sint8_least; 
typedef u8         uint8_least; 
typedef s16        sint16_least; 
typedef u16        uint16_least; 
typedef s32        sint32_least; 
typedef u32        uint32_least; 
 
typedef float               float32; 
typedef double              float64; 

#endif  /* _PLATFORM_TYPES_H_ */


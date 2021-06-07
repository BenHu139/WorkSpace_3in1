/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_Type.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Driver module type definitions head File
*   Author          : HeYang
********************************************************************************
*   Description     : The header file Can_Type.h contains the common type 
*                     definitions of Can Driver module
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version    Date         Initials      CR#       Descriptions
*   ---------  ----------   ------------  --------  ---------------
*   01.00.00   10/12/2012   LiXiang       N/A       Original
*   02.00.00   08/04/2013   junfei.chen   N/A       D01_ECAN_130408_01
*   02.01.00   21/04/2013   junfei.chen   N/A       D01_ECAN_130421_01
*   02.02.00   26/05/2013   junfei.chen   N/A       D01_ECAN_130526_01
*   03.00.00   02/07/2013   junfei.chen   N/A       D01_ECAN_130702_01
*   03.00.01   25/08/2013   junfei.chen   N/A       D01_ECAN_130825_01
*   03.00.02   28/08/2013   junfei.chen   N/A       D01_ECAN_130828_01
*   03.00.03   04/09/2013   junfei.chen   N/A       D01_ECAN_130904_01
*   03.00.04   06/09/2013   junfei.chen   N/A       D01_ECAN_130906_01
*   04.00.00   19/11/2014   junfei.chen   N/A       D01_ECAN_141119_01
*   04.01.00   25/05/2015   sijia.hao     N/A       D01_ECAN_150525_01
*   04.02.00   09/11/2015   sijia.hao     N/A       D01_ECAN_151109_01
********************************************************************************
* END_FILE_HDR*/


#ifndef _CAN_TYPE_H_
#define _CAN_TYPE_H_

/*******************************************************************************
*   Includes   
*******************************************************************************/
#include "Can_Cfg.h"
#include "ComStack_Types.h"

/*******************************************************************************
*   Typedef 
*******************************************************************************/
/*CAN429:
Name:  Can_HwHandleType
Type:  uint8, uint16
Range: Standard 0..0x0FF
       Extended 0..0xFFFF
Description:    
Represents the hardware object handles of a CAN hardware unit. 
For CAN hardware units with more than 255 HW objects use extended range.
*/
#if(CAN_USED_HOH_NUM > 255)
    typedef uint16 Can_HwHandleType;
#else
    typedef uint8 Can_HwHandleType;
#endif/* #if(CAN_USED_HOH_NUM > 255) */

 /*CAN416:
Name:   Can_IdType
Type:   uint16, uint32
Range:  Standard 0..0x7FF
        Extended 0..0xFFFFFFFF
Description:    
Represents the Identifier of an L-PDU. For extended IDs the most significant 
bit is set.
*/
#if (STD_ON == CAN_ENABLE_EXTENDED_ID)  
    typedef uint32 Can_IdType;
#else
    typedef uint16 Can_IdType;
#endif/* #if (STD_ON == CAN_ENABLE_EXTENDED_ID)  */

/*CAN039:
Name:       Can_ReturnType 
Type:       Enumeration 
Range: 
CAN_OK      success 
CAN_NOT_OK  error occurred or wakeup event occurred during sleep transition 
CAN_BUSY    transmit request could not be processed because no transmit object 
            was available 
Description:  
Return values of CAN driver API . 
*/
typedef enum
{
    CAN_OK = 0,                   
    CAN_NOT_OK = 1,     
    CAN_BUSY = 2        
}Can_ReturnType;

typedef enum 
{
    STANDARD_ID = 0,
    EXTENDED_ID = 1
}Can_CanIdType;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
typedef enum
{
    CAN_UNINT = 0,
    CAN_STOPPED = 1, 
    CAN_STARTED = 2,    
    CAN_SLEEP = 3    
}Can_StateType;
#endif/* #if (CAN_DEV_ERROR_DETECT == STD_ON) */

/* CAN417:  
Name:  Can_StateTransitionType 
Type:  Enumeration 
Range: 
CAN_T_START   CAN controller transition value to request state STARTED. 
CAN_T_STOP    CAN controller transition value to request state STOPPED. 
CAN_T_SLEEP   CAN controller transition value to request state SLEEP. 
CAN_T_WAKEUP  CAN controller transition value to request state STOPPED 
              from state SLEEP. 
Description:  
State transitions that are used by the function CAN_SetControllerMode 
*/
typedef enum
{
    CAN_T_NONE   = 0,
    CAN_T_START  = 1,    
    CAN_T_STOP   = 2,     
    CAN_T_SLEEP  = 3,    
    CAN_T_WAKEUP = 4   
}Can_StateTransitionType;

 /* CAN413: 
Name:  Can_ConfigType 
Type:  Structure 
Range: Implementation specific.  
Description:
This is the type of the external data structure containing the overall 
initialization data for the CAN driver and SFR settings affecting all 
controllers. Furthermore it contains pointers to controller configuration 
structures. The contents of the initialization data structure are CAN 
hardware specific. 
*/ 
typedef struct
{
    uint8 CanControllerNum;   
}Can_ConfigType;

/*CAN414:
Name:     Can_ControllerBaudrateConfigType
Type:     Structure
Range:    Implementation specific.
Description: 
This is the type of the external data structure containing 
the bit timing related initialization data for one CAN controller. 
The contents of the initialization data structure are CAN hardware specific.
*/
typedef struct
{
    uint8   CanCtrl0;
    uint8   CanCtrl1;
}Can_ControllerBaudrateConfigType;

/*CAN415:
Name: Can_PduType
Type: Structure
Description: 
This type is used to provide ID, DLC and SDU from CAN interface 
to CAN driver.
*/
typedef struct
{
    PduIdType   swPduHandle;
    uint8       length;
    Can_IdType  id;
    P2VAR(uint8, TYPEDEF, CAN_APPL_DATA)   sdu;  
}Can_PduType;

/* hoh config type */
typedef struct
{                   
    uint8       controllerRef;  /*logic controller*/
    Can_IdType  id;             /*CAN ID*/
    Can_CanIdType idType;       /*CAN ID Type*/
    uint8        hohType;        /*hohType  bit0:0-receive,1-transmit;
                                           bit1:0-basic ,1-full*/
    uint32      filterRef;      
}Can_HardwareObjectConfigType;

/* Can Internal buffer length type */
typedef uint32 Can_LenType;

typedef enum
{
    CAN_UNINITIALIZED = 0,
    CAN_INITIALIZED = 1  
}Can_InitType;

#endif/* _CAN_TYPE_H_*/


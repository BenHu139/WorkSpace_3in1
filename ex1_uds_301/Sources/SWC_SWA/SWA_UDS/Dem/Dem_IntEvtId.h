  /*BEGIN_FILE_HDR
***************************************************************************************************
* NOTICE                              
* This software is the property of HiRain Technologies. Any information contained in this 
* doc should not be reproduced, or used, or disclosed without the written authorization from 
* HiRain Technologies.
***************************************************************************************************
* File Name: Dem_IntEvtId.h
***************************************************************************************************
* Project/Product: AUTOSAR BSW
* Title:
* Author: qyMa
***************************************************************************************************
* Description:For SW-C event Id symbols.
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
*¡¡1.0     12/02/10    qyMa         N/A     Original
*
*
***************************************************************************************************
*END_FILE_HDR*/

#if !defined(DEM_INTEVTID_H)
#define DEM_INTEVTID_H

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define DEM_EVENT_INVALID                    0

/*Can Interface*/
#define CANIF_E_INVALID_DLC    (0x6001U)/*Production Error,Assigned by DEM,Failed DLC Check   */
#define CANIF_E_STOPPED        (0x6002U)/*Production Error,Assigned by DEM,CAN Interface controller mode 
                                        state machine is in mode CANIF_CS_STOPPED */

#endif /* DEM_INTEVTID_H */

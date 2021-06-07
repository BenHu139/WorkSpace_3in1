

/* ***************************************************************************/

#ifndef PORT_H_
#define PORT_H_

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "includes.h"
#include "Port_Cfg.h"
/* ***************************************************************************/
/*                                 MACROS                                    */
/* ***************************************************************************/
#define Port_vidPadModeCfg(PortId, CfgMode)          (SIUL.PCR[PortId].R = (CfgMode))
/* ***************************************************************************/
/*                                 TYPES                                     */
/* ***************************************************************************/

/* ***************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/* ***************************************************************************/


/* ***************************************************************************/
/*                                 PROTOTYPES                                */
/* ***************************************************************************/

extern void Port_vidInit(void);

extern void Port_vidPadDirConfig(uint8 PortNum,uint16 ConfigValue);

#endif

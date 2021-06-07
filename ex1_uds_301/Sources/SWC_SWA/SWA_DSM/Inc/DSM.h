
/* ***************************************************************************/
#ifndef DSM_H
#define DSM_H

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Std_Types.h"
#include "Rte_Data.h"

/* ***************************************************************************/
/*                                 MACROS                                    */
/* ***************************************************************************/
#define DSM_TASK_PERIOD_MS            ((uint8)5)

#define DSM_HVVOLT_LOWLIMIT_10V       ((uint16)100)
#define DSM_HVVOLT_HIGHTLIMIT_750V    ((uint16)7500)
#define DSM_LVVOLT_LOWLIMIT_6V        ((uint16)60)
#define DSM_LVVOLT_HIGHTLIMIT_18V     ((uint16)180)
#define DSM_LVOLTAGE_DIFF             ((uint16)10)
#define DSM_VOLTAGE_HW_FAULT          ((uint16)1)
#define DSM_VOLTAGE_SW_FAULT          ((uint16)1)
#define DSM_LVOLTAGE_DISCON           ((uint16)60)
#define DSM_HVOLTAGE_DISCON           ((uint16)1000)
#define DSM_HVOLTAGE_SW_MAX           ((uint16)7450)
#define DSM_HVOLTAGE_SW_MIN           ((uint16)4500)
#define DSM_LVOLTAGE_SW_MAX           ((uint16)180)
#define DSM_LVOLTAGE_SW_8_5V          ((uint16)85)
#define DSM_LVOLTAGE_SW_9V            ((uint16)90)


#define DSM_ERRORCODE_INPUTOCP             ((uint8)1)
#define DSM_ERRORCODE_INPUTOVP             ((uint8)2)
#define DSM_ERRORCODE_INPUTUVP             ((uint8)3)
#define DSM_ERRORCODE_OVERLOAD             ((uint8)4)
#define DSM_ERRORCODE_INPUTOUTPUTDISCON    ((uint8)5)
#define DSM_ERRORCODE_INPUTOUTPUTSHORT     ((uint8)6)
#define DSM_ERRORCODE_OUTPUTMISPHASE       ((uint8)7)
#define DSM_ERRORCODE_OVERTEMP             ((uint8)8)
 
/* ***************************************************************************/
/*                                 TYPES                                     */
/* ***************************************************************************/


/* ****************************************************************************/
/*                         VARIABLE  DEFINITION                               */
/* ****************************************************************************/
extern boolean DSM_bIntFailSt;
extern boolean DSM_bIntDeratSt;

extern boolean DSM_bDspDeratSt;
extern boolean DSM_bDspFailSt;

extern boolean DSM_bInterLockSt;

extern boolean DSM_bPwrTempDeratSt;
extern boolean DSM_bPwrTempFailSt;
extern uint8   DSM_u8PwrTempDeratCnt;
extern uint8   DSM_u8PwrTempFailCnt;

extern boolean DSM_bExtFailSt;

extern uint8   DSM_u8ProxFailSt;
extern uint16  DSM_u16ProxCnt;

extern uint8   DSM_u8PwrVolLowCnt;
extern uint8   DSM_u8PwrVolHighCnt;
extern uint8   DSM_u8PwrVolRecoveryCnt;
extern uint8   DSM_u8PwrVolFailSt;

extern uint8   DSM_u8PilotFailSt;
extern uint16  DSM_u16PilotDutyCnt;
extern uint16  DSM_u16PilotFreqCnt;
extern uint16  DSM_u16PilotVolCnt;

extern boolean DSM_bObcOutOvp;
extern boolean DSM_bObcOutUvp;

/* ***************************************************************************/
/*                                 PROTOTYPES                                */
/* ***************************************************************************/
extern void DSM_vidInit(void);
extern void DSM_vidMainFunc(void);

#endif

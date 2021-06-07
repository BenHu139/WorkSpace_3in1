

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/

#ifndef RTC_DRV_H
#define RTC_DRV_H

#include "includes.h"


/******************************************************************************/
/* DEFINE                                                                     */
/******************************************************************************/

#define RTCDRV_CLK_DIVDER_64      63
#define RTCDRV_CLK_DIVDER_60      59

/******************************************************************************/
/* DEFINE Registre Micro                                                      */
/******************************************************************************/

#define RTC_SMT_TMR_REG_0          STM.CNT0.R

/******************************************************************************/
/* MACRO FUNCTIONS                                                            */
/******************************************************************************/

#define RtcDRVEnable()                       (STM.CR.B.TEN = 1)



#define RtcDRVDisable()                      (STM.CR.B.TEN = 0)

#define RtcDRVClokDivider(value)             (STM.CR.B.CPS = value)

#define RtcDRVWriteCompValue(channel,value)  (STM.CH[##channel##].CMP.R = value)

#define RtcDRVReadCompValue(channel)         (STM.CH[##channel##].CMP.R)

#define RtcDRVCompIntEnable(channel)         (STM.CH[##channel##].CCR.B.CEN = 1)

#define RtcDRVCompIntDisable(channel)        (STM.CH[##channel##].CCR.B.CEN = 0)

#define RtcDRVRequestFlag(channel)           (STM.CH[##channel##].CIR.B.CIF)

#define RtcDRVRequestClrFlag(channel)        (STM.CH[##channel##].CIR.B.CIF = 1)

#define RtcDRVCntRead()                      (STM.CNT.R)

#define RtcDRVCntWrite(value)                (STM.CNT.R = value)




#endif /* RTC_DRV_H */

/*------------------------------ end of file ------------------------------*/

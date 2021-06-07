
/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/

#ifndef RTC_H_
#define RTC_H_

#include "Rtc_Drv.h"

/* ****************************************************************************/
/* DEFINE                                                                     */
/* ****************************************************************************/

#define MDIS_ENABLED        0 /* Clock for STM Timers is enabled*/
#define MDIS_DISABLED       1 /* Clock for STM Timers is disabled (Module Disable)*/

#define FRZ_ENABLED         1 /* Timers are stopped in debug mode*/
#define FRZ_DISABLED        0 /* Timers continue to run in debug mode*/

#define STM_RELOAD_VALUE      500

#define STM_RELOAD_TIME_1K    1000
#define STM_RELOAD_TIME_10K   100
#define STM_RELOAD_TIME_100K  10


typedef enum
{
   RTC_CMP_0 = 0,
   RTC_CMP_1,
   RTC_CMP_2,
   RTC_CMP_3,
   RTC_CMP_MAX
}Rtc_tenuCmpType;

/******************************************************************************/
/* MACRO FUNCTIONS                                                            */
/******************************************************************************/

void Rtc_init(void);
void Rtc_EnableNotification(void);
void Rtc_Start(void);
void Rtc_Stop(void);
uint32 Rtc_u32GetBaseTimerCnt(void);

#endif /* RTC_H */

/*------------------------------ end of file ------------------------------*/

/*
 * Pit_Drv.h
 *
 *  Created on: Apr 15, 2020
 *      Author: hr
 */

#ifndef PIT_DRV_H_
#define PIT_DRV_H_

#include "includes.h"

/******************************************************************************/
/* DEFINE                                                                     */
/******************************************************************************/

typedef enum
{
   PIT_CH_0 =0,
   PIT_CH_1,
   PIT_CH_2,
   PIT_CH_3,
   PIT_CH_4,
   PIT_CH_5,
   MAX_PIT_CHANNEL
}PIT_tenuChannels;

/******************************************************************************/
/* MACRO FUNCTIONS                                                            */
/******************************************************************************/

#define PitModuleEnable()                    (PIT.PITMCR.B.MDIS = 0)

#define PitModuleDisable()                   (PIT.PITMCR.B.MDIS = 1) // default

#define PitSetTimerLoaderVal(channel,value)  (PIT.CH[##channel##].LDVAL.R = value)

#define PitGetCurrentTimerVal(channel)       (PIT.CH[##channel##].LDVAL.R) // 32bits

#define PitEnableTimerInt(channel)           (PIT.CH[##channel##].TCTRL.B.TIE = 1)

#define PitDisableTimerInt(channel)          (PIT.CH[##channel##].TCTRL.B.TIE = 0) //default

#define PitTimerEnable(channel)              (PIT.CH[##channel##].TCTRL.B.TEN = 1)

#define PitTimerDisable(channel)             (PIT.CH[##channel##].TCTRL.B.TEN = 0) //default

#define PitGetTimerFlag(channel)             (PIT.CH[##channel##].TFLG.B.TIF) 	

#define PitClearTimerFlag(channel)           (PIT.CH[##channel##].TFLG.B.TIF = 1)

#endif /* PIT_DRV_H_ */

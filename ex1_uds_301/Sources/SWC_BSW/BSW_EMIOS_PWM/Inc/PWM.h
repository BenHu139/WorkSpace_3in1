
/*****************************************************************************/

#ifndef PWM_H_
#define PWM_H_

/*****************************************************************************/
/*                                 INCLUDE                                   */
/*****************************************************************************/
#include "PWM_Cfg.h"
/*****************************************************************************/
/*                                 MACROS                                    */
/*****************************************************************************/

/*****************************************************************************/
/*                                 TYPES                                     */
/*****************************************************************************/

/*****************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/*****************************************************************************/


/*****************************************************************************/
/*                                 PROTOTYPES                                */
/*****************************************************************************/
extern void PWM_vidInit(void);

extern void PWM_vidSubmoduleEnable(u8 SubmodNum);

extern void PWM_vidSubmoduleDisable(u8 SubmodNum);

extern void PWM_vidOutPutEnableChannel(u8 channel);

extern void PWM_vidOutputDisChannel(u8 channel);

extern void PWM_vidOutputEnable(void);

extern void PWM_vidOutputDisable(void);

extern void PMW_vidSetVadjDuty(uint16  duty);

extern void PMW_vidSetIadjDuty(uint16 duty);

extern void PWM_vidGetCpDuty(void);

#endif



/*****************************************************************************/

#ifndef PWM_CFG_H_
#define PWM_CFG_H_

/*****************************************************************************/
/*                                 INCLUDE                                   */
/*****************************************************************************/
//#include "Std_Type.h"
#include "Std_Types.h"
#include "EMIOS_Drv.h"

/*****************************************************************************/
/*                                 MACROS                                    */
/*****************************************************************************/
#define PWM_MODULE_USED               EMIOS_MOD_0             

typedef enum
{
   EMIOS_LOGIC_CH_0 = 0,		// PWM_VADJ
   EMIOS_LOGIC_CH_1,			// PWM_IADJ

   MAX_EMIOS_LOGIC_CHANNEL
}EMIOS_tenuChannels;

#define PWM_VADJ        EMIOS_LOGIC_CH_0
#define PWM_IADJ        EMIOS_LOGIC_CH_1           

extern u8 eMIOS_channels_cfg[MAX_EMIOS_LOGIC_CHANNEL];

#endif


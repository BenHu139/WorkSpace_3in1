
#ifndef   __CANDRV_H_
#define   __CANDRV_H_

#include "includes.h"


extern void CanTxFinishDetect(void);
extern void CanBusOffInt(void);
extern void CanHwRestart(u8 ControllerId);
extern u8 CanBusOffDetect(u8 ControllerId);

#endif



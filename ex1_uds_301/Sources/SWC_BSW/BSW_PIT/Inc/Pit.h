/*
 * Pit.h
 *
 *  Created on: Apr 15, 2020
 *      Author: hr
 */

#ifndef PIT_H_
#define PIT_H_

#include "Pit_Drv.h"

typedef void (*PIT_INT_CALLBACK)(void);

extern PIT_INT_CALLBACK Pit_pfn_Callback[MAX_PIT_CHANNEL];

void Pit_init(void);
void Pit_SetTimerLoaderVal(u8 channel, u32 val);
void Pit_EnableNotification(u8 channel);
void Pit_Start(u8 channel);
void Pit_Stop(u8 channel);
uint32 Pit_u32GetCurrentTimerCnt(u8 channel);
void Pit_SetIsrCallback(u8 channel, PIT_INT_CALLBACK pfn);

#endif /* PIT_H_ */

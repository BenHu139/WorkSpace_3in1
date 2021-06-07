/*
 * debug_only.h
 *
 *  Created on: May 21, 2020
 *      Author: hr
 */

#ifndef DEBUG_ONLY_H_
#define DEBUG_ONLY_H_

#include "includes.h"

u16 CRC16_isr(u8 *Dat, u32 len, u16 last_result);

void UPDATEDATA_init(void);
u8 UPDATEDATA_CheckUpdateReqValid(void) ;

void  REMOTEUPDATE_Init(void);
u8 REMOTEUPDATE_CheckCompatibility(void);
u8 REMOTEUPDATE_CheckProgramCond(void);
u8 REMOTEUPDATE_CallbackEraseMemory(void);
u8 REMOTEUPDATE_GetEraseMemoryResult(void);
void REMOTEUPDATE_SetCheckSumStart(void);
u8 REMOTEUPDATE_CallbackCheckSumCal(void);
u8 REMOTEUPDATE_CallbackIsCheckSumValueValid( u32 size, const u8 *buf );
u8 REMOTEUPDATE_CallbackWriteData(u8 *buf,u32 address,u32 dataSize);

u8 REMOTEUPDATE_GetUpdateResetEcuReq(void);
void REMOTEUPDATE_SetUpdateResetEcuReq(void);

#endif /* DEBUG_ONLY_H_ */

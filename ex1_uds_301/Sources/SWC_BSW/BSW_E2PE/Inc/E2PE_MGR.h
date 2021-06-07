/*
 * E2PE_MGR.h
 *
 *  Created on: May 26, 2020
 *      Author: hr
 */

#ifndef E2PE_MGR_H_
#define E2PE_MGR_H_

#include "includes.h"
#include "DFls.h"
#include "E2PE_Cfg.h"

typedef enum
{
	E2PE_BLOCK_ID_0 = 0,		// 可设定参数
	E2PE_BLOCK_ID_1,			// Calib data
	E2PE_BLOCK_ID_2,			// DEM
	E2PE_BLOCK_ID_3,			// 固定参数
	
	E2PE_BLOCK_ID_MAX
} E2PE_BLOCK_IDDEX;

#define DEM_DATA_RANGE_START     (0u)
#define DEM_DATA_RANGE_END       (3u * 1024u - 16u)


extern void E2PE_initStorageAndClearData(void);

extern void E2PE_vidInit(void);
extern u8 E2PE_gotoNextStorage(u8 block_idx);

extern u8 E2PE_RecoverBlockDataToDefault(u8 block_idx);

extern u8 E2PE_WriteCalibDataWithoutCRC(void);

extern u8 E2PE_ReadParaFromBuffer(u16 dataIdx, u8* data);
extern u8 E2PE_ReadParaFromDFlash(u16 dataIdx, u8* data); // Debug Only
extern u8 E2PE_WriteParaToBuffer(u16 dataIdx, u8* data);
extern u8 E2PE_WriteParaToBufferAndFlushToDFlash(u16 dataIdx, u8* data);
extern u8 E2PE_FlushBufferToDFlash();

extern u8 FWS_EEPROM_ReadDemDataWithoutCrc(u32 addr, u16 length, u8 *data);
extern u8 FWS_EEPROM_WriteDemDataWithoutCRC(u32 addr,u16 length,u8 *data);



#endif /* E2PE_MGR_H_ */

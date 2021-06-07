/*
 * E2PE_MGR.c
 *
 *  Created on: May 26, 2020
 *      Author: hr
 */
#include "E2PE_MGR.h"
#include "Calibration.h"
#include "DEM.h"

#define DFLS_RIGION_UNUSED		 ((u64)0xFFFFFFFFFFFFFFFF)
#define DFLS_RIGION_USING		 ((u64)0xFFFF0000FFFFFFFF)
#define DFLS_RIGION_USED		 ((u64)0x00000000FFFFFFFF)	

#define FLAG_RIGION_UNUSED		 ((u32)0xFFFFFFFF)
#define FLAG_RIGION_USING		 ((u32)0xFFFF0000)
#define FLAG_RIGION_USED		 ((u32)0x00000000)

#define BLOCK0_STORAGE_SIZE		 ((u16)0x400)				// 1K
#define BLOCK1_STORAGE_SIZE		 ((u16)0x400)				// 1K
#define BLOCK2_STORAGE_SIZE		 ((u16)0xC00)				// 3K
#define BLOCK3_STORAGE_SIZE		 ((u16)0x400)				// 1K

#define PAGE_SIZE_16B			 ((u8)16)


typedef struct {
	u8		blockID;
	u32		blockStartAddr;
	u16		blockSize;
	
	u8		storageNum;
	u16 	storageSize;
	
	u8		storageUpdateFlag;			// TRUE: need update; FALSE: data not change
	u8		curStorageNum;
	u32		storageFlagAddr;
	u32		storageStartAddr;
	
	u16     pageSize;
	u8		totalPageNum;
} E2PE_BlockST_Type;

E2PE_BlockST_Type E2PE_blockST_list[DFLS_BLOCK_NUM] = {
		{
			DFLS_BLOCK_B1F0, 
			DFLS_ADDR_START_B1F0,
			DFLS_BLOCK_SIZE, 
			DFLS_BLOCK_SIZE / BLOCK0_STORAGE_SIZE,
			BLOCK0_STORAGE_SIZE,
			0x0,
			0x0,
			0x0,
			0x0,
			PAGE_SIZE_16B,
			BLOCK0_STORAGE_SIZE / PAGE_SIZE_16B - 1
		},
		{
			DFLS_BLOCK_B1F1, 
			DFLS_ADDR_START_B1F1,
			DFLS_BLOCK_SIZE,
			DFLS_BLOCK_SIZE / BLOCK1_STORAGE_SIZE,
			BLOCK1_STORAGE_SIZE,
			0x0,
			0x0,
			0x0,
			0x0,
			BLOCK1_STORAGE_SIZE,
			1
		},
		{
			DFLS_BLOCK_B1F2, 
			DFLS_ADDR_START_B1F2,
			DFLS_BLOCK_SIZE,
			DFLS_BLOCK_SIZE / BLOCK2_STORAGE_SIZE,
			BLOCK2_STORAGE_SIZE,
			0x0,
			0x0,
			0x0,
			0x0,
			BLOCK2_STORAGE_SIZE,
			1
		},
		{
			DFLS_BLOCK_B1F3, 
			DFLS_ADDR_START_B1F3,
			DFLS_BLOCK_SIZE,
			DFLS_BLOCK_SIZE / BLOCK3_STORAGE_SIZE,
			BLOCK3_STORAGE_SIZE,
			0x0,
			0x0,
			0x0,
			0x0,
			PAGE_SIZE_16B,
			BLOCK0_STORAGE_SIZE / PAGE_SIZE_16B - 1
		}
};

s8 E2PE_findCurrentStorage(u8 block_idx)
{
	u8 j, bret, dret;
	u32 bflag;
	u32 dflag;
	
	if(block_idx < E2PE_BLOCK_ID_MAX - 1)
	{
		for(j = 0; j < E2PE_blockST_list[block_idx].storageNum; j++)
		{
			bret = DFls_u8Read(E2PE_blockST_list[block_idx].blockStartAddr + E2PE_blockST_list[block_idx].storageSize * j,
					    (u8*)&bflag, 4);
			dret = DFls_u8Read(E2PE_blockST_list[block_idx].blockStartAddr + E2PE_blockST_list[block_idx].storageSize * j + 8,
						(u8*)&dflag, 4);
			if((bret == DFLS_BLOCK_OK) && (dret == DFLS_BLOCK_OK))
			{
				if((bflag == FLAG_RIGION_USING) && (dflag == 0x0))
				{
					E2PE_blockST_list[block_idx].curStorageNum = j;
					E2PE_blockST_list[block_idx].storageFlagAddr = E2PE_blockST_list[block_idx].blockStartAddr + E2PE_blockST_list[block_idx].storageSize * E2PE_blockST_list[block_idx].curStorageNum;
					E2PE_blockST_list[block_idx].storageStartAddr = E2PE_blockST_list[block_idx].storageFlagAddr + 16;
							
					return (s8)j;
				}
			}
		}
		
		// 数据损坏: 擦除block后, 写入默认值
		DFls_u8BlockErase(E2PE_blockST_list[block_idx].blockID);
		E2PE_RecoverBlockDataToDefault(block_idx);
		return 0;
	}
	else
	{
		return -1;
	}
}

void E2PE_initStorageAndClearData(void)
{
	u8 i;
	u64 block_flag;

	for(i = 0; i < DFLS_BLOCK_NUM; i++)
	{
		DFls_u8BlockErase(E2PE_blockST_list[i].blockID);
		
		E2PE_blockST_list[i].curStorageNum = 0;
		E2PE_blockST_list[i].storageFlagAddr = E2PE_blockST_list[i].blockStartAddr + E2PE_blockST_list[i].storageSize * E2PE_blockST_list[i].curStorageNum;
		E2PE_blockST_list[i].storageStartAddr = E2PE_blockST_list[i].storageFlagAddr + 16;
		
		block_flag = DFLS_RIGION_USING;
		DFls_u8WriteDW(E2PE_blockST_list[i].storageFlagAddr, (u8*)&block_flag);
	}
}

u8 E2PE_RecoverBlockDataToDefault(u8 block_idx)
{
	u8 i;
	u64 dataFlag = 0x0;
	
	if(block_idx < E2PE_BLOCK_ID_MAX - 1)
	{
		switch(block_idx)
		{
			case E2PE_BLOCK_ID_0:
			{
				i = DFls_u8Write(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageStartAddr, (u8*)&E2PE_parameter_buffer[0], sizeof(E2PE_parameter_buffer));
				if(DFLS_BLOCK_OK == i)
				{
					DFls_u8WriteDW(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageFlagAddr + 8, (u8*)&dataFlag);
				}
			}
			break;
			
			case E2PE_BLOCK_ID_1:
			{
				i = DFls_u8Write(E2PE_blockST_list[E2PE_BLOCK_ID_1].storageStartAddr, (u8*)CALIB_SECTION_RAM_START_ADDRESS, CALIB_SECTION_LENGTH);
				if(DFLS_BLOCK_OK == i)
				{
					DFls_u8WriteDW(E2PE_blockST_list[E2PE_BLOCK_ID_1].storageFlagAddr + 8, (u8*)&dataFlag);
				}
			}
			break;
						
			case E2PE_BLOCK_ID_2:
			{
				i = DFls_u8Write(E2PE_blockST_list[E2PE_BLOCK_ID_2].storageStartAddr, (u8*)&DemStorageMem, sizeof(DemStorageMem));
				if(DFLS_BLOCK_OK == i)
				{
					DFls_u8WriteDW(E2PE_blockST_list[E2PE_BLOCK_ID_2].storageFlagAddr + 8, (u8*)&dataFlag);
				}
			}
			break;
			
			default:
			break;
		}
	}
}

void E2PE_vidInit(void)
{
	u8 i;
	u32 initFlag;
	u64 dataFlag = 0x0;
	
	// 把最后一个block作为是否初始化的标志, 初始化完成后, 该block不能擦除
	if(DFLS_BLOCK_OK == DFls_u8Read(E2PE_blockST_list[E2PE_BLOCK_ID_MAX - 1].blockStartAddr, (u8*)&initFlag, sizeof(initFlag))) 
	{
		if(FLAG_RIGION_USING == initFlag)
		{
			for(i = 0; i < E2PE_BLOCK_ID_MAX - 1; i++)
			{
				E2PE_findCurrentStorage(i);
			}
			
			// copy freedom para from data flash to buffer
			if(DFLS_BLOCK_OK == DFls_u8Read(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageFlagAddr + 8, (u8*)&initFlag, sizeof(initFlag)))
			{
				if(0x0 == initFlag)
				{
					DFls_u8Read(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageStartAddr, (u8*)&E2PE_parameter_buffer[0], sizeof(E2PE_parameter_buffer));
				}
			}
			
			
			// copy calib data from data flash to ram 
			if(DFLS_BLOCK_OK == DFls_u8Read(E2PE_blockST_list[E2PE_BLOCK_ID_1].storageFlagAddr + 8, (u8*)&initFlag, sizeof(initFlag)))
			{
				if(0x0 == initFlag)
				{
					DFls_u8Read(E2PE_blockST_list[E2PE_BLOCK_ID_1].storageStartAddr, (u8*)CALIB_SECTION_RAM_START_ADDRESS, CALIB_SECTION_LENGTH);
				}
			}
		}
		else
		{
			E2PE_initStorageAndClearData();
			
			E2PE_RecoverBlockDataToDefault(E2PE_BLOCK_ID_0);
			E2PE_RecoverBlockDataToDefault(E2PE_BLOCK_ID_1);
			E2PE_RecoverBlockDataToDefault(E2PE_BLOCK_ID_2);
		}
	}

	
}

u8 E2PE_isCurrentStorage(u8 block_idx)
{
	u32 flag;
	
	if(block_idx < E2PE_BLOCK_ID_MAX - 1)
	{
		DFls_u8Read(E2PE_blockST_list[block_idx].blockStartAddr + E2PE_blockST_list[block_idx].storageSize * E2PE_blockST_list[block_idx].curStorageNum,
				    (u8*)&flag, 4);
		
		if(FLAG_RIGION_USING == flag)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

u8 E2PE_gotoNextStorage(u8 block_idx)
{
	u8  ret, temp;
	u64 block_flag;
	
	if(block_idx < E2PE_BLOCK_ID_MAX - 1)
	{
		if(FALSE == E2PE_isCurrentStorage(block_idx))
		{
			return FALSE;
		}
		
		temp = E2PE_blockST_list[block_idx].curStorageNum + 1;
		if(temp >= E2PE_blockST_list[block_idx].storageNum)
		{
			ret = DFls_u8BlockErase(E2PE_blockST_list[block_idx].blockID);
			if(DFLS_BLOCK_OK == ret)
			{
				E2PE_blockST_list[block_idx].curStorageNum = 0;
				E2PE_blockST_list[block_idx].storageFlagAddr = E2PE_blockST_list[block_idx].blockStartAddr + E2PE_blockST_list[block_idx].storageSize * E2PE_blockST_list[block_idx].curStorageNum;
				E2PE_blockST_list[block_idx].storageStartAddr = E2PE_blockST_list[block_idx].storageFlagAddr + 16;
				
				block_flag = DFLS_RIGION_USING;
				ret = DFls_u8WriteDW(E2PE_blockST_list[block_idx].storageFlagAddr, (u8*)&block_flag);
				if(DFLS_BLOCK_OK == ret)
				{
					return TRUE;
				}
			}
		}
		else
		{
			block_flag = DFLS_RIGION_USING;
			ret = DFls_u8WriteDW(E2PE_blockST_list[block_idx].blockStartAddr + E2PE_blockST_list[block_idx].storageSize * temp, 
					             (u8*)&block_flag);
			if(DFLS_BLOCK_OK == ret)
			{
				block_flag = DFLS_RIGION_USED;
				ret = DFls_u8WriteDW(E2PE_blockST_list[block_idx].storageFlagAddr, (u8*)&block_flag);
				if(DFLS_BLOCK_OK == ret)
				{
					E2PE_blockST_list[block_idx].curStorageNum = temp;
					E2PE_blockST_list[block_idx].storageFlagAddr = E2PE_blockST_list[block_idx].blockStartAddr + E2PE_blockST_list[block_idx].storageSize * E2PE_blockST_list[block_idx].curStorageNum;
					E2PE_blockST_list[block_idx].storageStartAddr = E2PE_blockST_list[block_idx].storageFlagAddr + 16;
					
					return TRUE;
				}
			}
		}
		
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}

u8 E2PE_WriteCalibDataWithoutCRC(void)
{
	u8 ret;
	u64 dataFlag = 0x0;
	
	if(TRUE == E2PE_gotoNextStorage(E2PE_BLOCK_ID_1))
	{
		ret = DFls_u8Write(E2PE_blockST_list[E2PE_BLOCK_ID_1].storageStartAddr, (u8*)CALIB_SECTION_RAM_START_ADDRESS, CALIB_SECTION_LENGTH);
		if(DFLS_BLOCK_OK == ret)
		{
			ret = DFls_u8WriteDW(E2PE_blockST_list[E2PE_BLOCK_ID_1].storageFlagAddr + 8, (u8*)&dataFlag);
			if(DFLS_BLOCK_OK == ret)
			{
				return TRUE;
			}
		}
	}
	
	return FALSE;
}


u8 E2PE_ReadParaFromBuffer(u16 dataIdx, u8* data)
{
	u32 i, addr, len;
	
	if(dataIdx < E2PE_PARA_ID_MAX)
	{
		addr = E2PE_parameter_list[dataIdx].startAddr;
		len  = E2PE_parameter_list[dataIdx].length;
		
		if((addr + len) <= E2PE_BUF_LEN)
		{
			for(i = 0; i < len; i++, data++, addr++)
			{
				*(data) = E2PE_parameter_buffer[addr];
			}
			return TRUE;
		}
	}
	
	return FALSE;
}

u8 E2PE_ReadParaFromDFlash(u16 dataIdx, u8* data)	// For Debug only
{
	u32 i, addr, len;
		
	if(dataIdx < E2PE_PARA_ID_MAX)
	{
		addr = E2PE_parameter_list[dataIdx].startAddr;
		len  = E2PE_parameter_list[dataIdx].length;
		
		i = DFls_u8Read(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageStartAddr + addr, data, len);
		if(DFLS_BLOCK_OK == i)
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

u8 E2PE_WriteParaToBuffer(u16 dataIdx, u8* data)
{
	u32 i, addr, len;
		
	if(dataIdx < E2PE_PARA_ID_MAX)
	{
		addr = E2PE_parameter_list[dataIdx].startAddr;
		len  = E2PE_parameter_list[dataIdx].length;
		
		if((addr + len) <= E2PE_BUF_LEN)
		{
			for(i = 0; i < len; i++, data++, addr++)
			{
				E2PE_parameter_buffer[addr] = *(data);
			}
			
			E2PE_blockST_list[E2PE_BLOCK_ID_0].storageUpdateFlag = TRUE;
			
			return TRUE;
		}
	}
	
	return FALSE;
}

u8 E2PE_FlushBufferToDFlash()
{
	u8	ret;
	u32 initFlag;
	u64 dataFlag = 0x0;
	
	if(TRUE == E2PE_blockST_list[E2PE_BLOCK_ID_0].storageUpdateFlag)
	{
		if(DFLS_BLOCK_OK == DFls_u8Read(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageFlagAddr + 8, (u8*)&initFlag, sizeof(initFlag)))
		{
			if(0x0 == initFlag)
			{
				if(TRUE == E2PE_gotoNextStorage(E2PE_BLOCK_ID_0))
				{
					ret = DFls_u8Write(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageStartAddr, (u8*)&E2PE_parameter_buffer[0], sizeof(E2PE_parameter_buffer));
					if(DFLS_BLOCK_OK == ret)
					{
						ret = DFls_u8WriteDW(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageFlagAddr + 8, (u8*)&dataFlag);
						if(DFLS_BLOCK_OK == ret)
						{
							E2PE_blockST_list[E2PE_BLOCK_ID_0].storageUpdateFlag = FALSE;
							return TRUE;
						}								
					}
				}
			}
			else
			{
				ret = DFls_u8Write(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageStartAddr, (u8*)&E2PE_parameter_buffer[0], sizeof(E2PE_parameter_buffer));
				if(DFLS_BLOCK_OK == ret)
				{
					ret = DFls_u8WriteDW(E2PE_blockST_list[E2PE_BLOCK_ID_0].storageFlagAddr + 8, (u8*)&dataFlag);
					if(DFLS_BLOCK_OK == ret)
					{
						E2PE_blockST_list[E2PE_BLOCK_ID_0].storageUpdateFlag = FALSE;
						return TRUE;
					}								
				}
			}
		}
	}
	
	return FALSE;
}

u8 E2PE_WriteParaToBufferAndFlushToDFlash(u16 dataIdx, u8* data)
{
	E2PE_WriteParaToBuffer(dataIdx, data);
	E2PE_FlushBufferToDFlash();
}




/**
 * @ingroup E2PE emulation EPP with DFlash
 * @brief  读长度length的DEM数据
 * @param  add		DFLASH地址(偏移量)     
 * @param  length 	长度字节 
 * @param  data 	数据缓冲区     
 * 
 * @return  u8 0 不成功; 1 成功 
 */
u8 FWS_EEPROM_ReadDemDataWithoutCrc(u32 addr, u16 length, u8 *data)
{
	u8 ret;
	
	addr = addr + E2PE_blockST_list[E2PE_BLOCK_ID_2].storageStartAddr;
	
	if((addr >= E2PE_blockST_list[E2PE_BLOCK_ID_2].storageStartAddr) &&
	   (addr + length < E2PE_blockST_list[E2PE_BLOCK_ID_2].storageStartAddr + DEM_DATA_RANGE_END))
	{
		ret = DFls_u8Read(addr, data, length);
		if(DFLS_BLOCK_OK == ret)
		{
			return 1;
		}
	}
	
	return 0;
}

/**
 * @ingroup E2PE emulation EPP with DFlash
 * @brief  写长度length的DEM数据
 * @param  add 		DFLASH地址(偏移量)   
 * @param  length 	长度字节 
 * @param  data 	数据缓冲区   
 * 
 * @return  u8 0 不成功 ; 1 成功 
 */
u8 FWS_EEPROM_WriteDemDataWithoutCRC(u32 addr,u16 length,u8 *data)
{
	u8 ret;
	u64 dataFlag = 0x0;
	
	if(TRUE == E2PE_gotoNextStorage(E2PE_BLOCK_ID_2))
	{
		addr = E2PE_blockST_list[E2PE_BLOCK_ID_2].storageStartAddr;
		data = (u8*)&DemStorageMem;
		length = sizeof(DemStorageMem);
		
		ret = DFls_u8Write(addr, data, length);
		if(DFLS_BLOCK_OK == ret)
		{
			ret = DFls_u8WriteDW(E2PE_blockST_list[E2PE_BLOCK_ID_2].storageFlagAddr + 8, (u8*)&dataFlag);
			if(DFLS_BLOCK_OK == ret)
			{
				return 1;
			}
		}
	}
	
	return 0;
}



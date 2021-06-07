/*
 * Nvm.c
 *
 *  Created on: 2015-12-17
 *      Author: lim
 */
#include "includes.h"
#include "Nvm.h"
#include "Dem.h"
//#include "typedef.h"
#include "E2PE_MGR.h"

#if(0)
volatile uint8 dememu[1024];
#endif

#define EEPPAGESIZE 256u
STATIC NvmMemRecdInfoType NvmMemRecdInfo;
STATIC NvM_State_t  NvM_TaskState;
STATIC NvmMemBlockCfgType NvmMemBlockCfg/*[NVM_NUMOFBLOCK] */= 
{
#if(0)
    (uint32)(&dememu[0]),//0x2620,/*Dem 数据所在EEP的起始地址*/
#endif
    DEM_DATA_RANGE_START,
    sizeof(DemStorageMem), /*Dem 数据占用EEP的size*/
    EEPPAGESIZE   /*NvM 模块每个调用周期写入(读取) 数据的长度*/
};



static void EeppIfWrite(uint8* buff,uint16 length,uint32 add)
{
#if(0)
    uint16 i;
    for(i = 0;i<length;i++)
        dememu[add-(uint32)(&dememu[0]) +i] = buff[i];
#endif
    FWS_EEPROM_WriteDemDataWithoutCRC(add,length,buff);
}

static void EeppIfRead(uint8* buff,uint16 length,uint32 add)
{
#if(0)
    uint16 i;
    for(i = 0;i<length;i++)
        buff[i]= dememu[add-(uint32)(&dememu[0]) +i];
#endif
    FWS_EEPROM_ReadDemDataWithoutCrc(add,length,buff);
}

Std_ReturnType NvM_GetErrorStatus(
    NvM_BlockIdType BlockId,
    NvM_RequestResultType* RequestResultPtr
)
{

    Std_ReturnType ret = E_OK;
    
    if(NvM_TaskState == NVM_STATE_UNINIT)
    {
        ret = E_NOT_OK;
    }
    else if(NvM_TaskState == NVM_STATE_IDLE)
    {
        *RequestResultPtr = NVM_REQ_OK;
    }
    else/*NVM_STATE_READ  NVM_STATE_WRITE*/
    {
        *RequestResultPtr = NVM_REQ_PENDING;
    }

    return ret;
}

Std_ReturnType NvM_ReadBlock(
    NvM_BlockIdType BlockId,
    void* NvM_DstPtr
)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NVM_STATE_IDLE == NvM_TaskState)&&(DEM_NVM_BLOCKID == BlockId))
    {
        NvmMemRecdInfo.NvMCurrentBlockId = BlockId;
        NvmMemRecdInfo.NvMMemAddr  = NvmMemBlockCfg.addrss;
        NvmMemRecdInfo.NvMDataSize = NvmMemBlockCfg.length;
        NvmMemRecdInfo.NvMPageSzie = NvmMemBlockCfg.psize;
        NvmMemRecdInfo.NvMDataPtr  = (uint8*)NvM_DstPtr;
        NvM_TaskState = NVM_STATE_READ;
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType NvM_WriteBlock(
    NvM_BlockIdType BlockId,
    void* NvM_SrcPtr
)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NVM_STATE_IDLE == NvM_TaskState)&&(DEM_NVM_BLOCKID == BlockId))
    {
        NvmMemRecdInfo.NvMCurrentBlockId = BlockId;
        NvmMemRecdInfo.NvMMemAddr  = NvmMemBlockCfg.addrss;
        NvmMemRecdInfo.NvMDataSize = NvmMemBlockCfg.length;
        NvmMemRecdInfo.NvMPageSzie = NvmMemBlockCfg.psize;
        NvmMemRecdInfo.NvMDataPtr  = (uint8*)NvM_SrcPtr;
        NvM_TaskState = NVM_STATE_WRITE;
        ret = E_OK;
    }
    return ret;
}
void NvM_Init(void)
{
    NvM_TaskState = NVM_STATE_IDLE;
    //NvmMemRecdInfo.NvMResult = NVM_REQ_NOT_OK;
}

void NvM_MainFunction( void )
{
    uint16 len;
    /*Call EEP Write*/

    if((NvM_TaskState == NVM_STATE_WRITE)||(NvM_TaskState == NVM_STATE_READ))
    {
        if(NvmMemRecdInfo.NvMDataSize > NvmMemRecdInfo.NvMPageSzie)
        {
            len = NvmMemRecdInfo.NvMPageSzie;
        }
        else
        {
            len = NvmMemRecdInfo.NvMDataSize;
        }
        
        if(NvM_TaskState == NVM_STATE_WRITE)
        {
            EeppIfWrite(NvmMemRecdInfo.NvMDataPtr,len,NvmMemRecdInfo.NvMMemAddr);
            NvmMemRecdInfo.NvMMemAddr += len;
            NvmMemRecdInfo.NvMDataSize -= len;
            NvmMemRecdInfo.NvMDataPtr += len;
        
            NvmMemRecdInfo.NvMDataSize = 0; // 使用DFlash来模拟epprom, 数据一次写入, 而不是每次写一个page(256B)
            
            if(NvmMemRecdInfo.NvMDataSize == 0)
            {
                NvM_TaskState = NVM_STATE_IDLE;
                //NvmMemRecdInfo.NvMResult = NVM_REQ_OK;
            }
        }
        else if(NvM_TaskState == NVM_STATE_READ)
        {
            /*Call EEP Read*/
            EeppIfRead(NvmMemRecdInfo.NvMDataPtr,len,NvmMemRecdInfo.NvMMemAddr);
            
            NvmMemRecdInfo.NvMMemAddr += len;
            NvmMemRecdInfo.NvMDataSize -= len;
            NvmMemRecdInfo.NvMDataPtr += len;
            if(NvmMemRecdInfo.NvMDataSize == 0)
            {
                NvM_TaskState = NVM_STATE_IDLE;
                //NvmMemRecdInfo.NvMResult = NVM_REQ_OK;
            }
        }
        else
        {
        
        }
    }
}

/********************** NVM Inferface define End **************************/


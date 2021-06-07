/*
 * Nvm.h
 *
 *  Created on: 2015-12-17
 *      Author: lim
 */

#ifndef NVM_H_
#define NVM_H_
#include "Std_Types.h"
/*********************** NVM ************************/
typedef uint8 NvM_ReqOperationType;
#define NVM_REQ_OP_NONE     0
#define NVM_REQ_OP_WRITE    1
#define NVM_REQ_OP_READ     2

typedef uint8 NvM_RequestResultType;
#define NVM_REQ_OK                 (0)
#define NVM_REQ_NOT_OK             (1)
#define NVM_REQ_PENDING            (2)
#define NVM_REQ_INTEGRITY_FAILED   (3)
#define NVM_REQ_BLOCK_SKIPPED      (4)
#define NVM_REQ_NV_INVALIDATED     (5)
#define NVM_REQ_CANCELLED          (6)  
#define NVM_REQ_REDUNDANCY_FAILED  (7) 
#define NVM_REQ_RESTORED_FROM_ROM  (8) 
#define NVM_REQ_BUSYING            (9)

#define DEM_NVM_BLOCKID             2

#define NVM_NUMOFBLOCK              1u

typedef enum
{
    NVM_STATE_UNINIT      = 0, /* Block not init    */
    NVM_STATE_IDLE        = 1, /* Block Idle         */
    NVM_STATE_READ        = 2, /* Read Block       */    
    NVM_STATE_WRITE       = 3, /* Write Block       */
#if 0
    NVM_STATE_RESTORE     = 4,    
    NVM_STATE_ERASE       = 5, /* Erase Block              */
    NVM_STATE_INVALIDNV   = 6, /* InvalidateNvBlock     */
    NVM_STATE_SETRAMSTS   = 7, /* request Crc calculate */
    NVM_STATE_READALL     = 8, /* Read all           */    
    NVM_STATE_WRITEALL    = 9, /* Write All          */
    NVM_STATE_FSM_DEFAULT = 10 /* Other State      */
#endif
}NvM_State_t;

typedef struct
{
    uint16 NvMCurrentBlockId;
    uint16 NvMDataSize;
    //uint16 NvMDoneSize;
    uint16 NvMPageSzie;
    uint32 NvMMemAddr;
    uint8* NvMDataPtr;
    //NvM_RequestResultType  NvMResult;
}NvmMemRecdInfoType;

typedef struct
{
    uint32 addrss;
    uint16 length;
    uint16 psize;/*page size*/
}NvmMemBlockCfgType;

typedef uint16 NvM_BlockIdType;
extern Std_ReturnType NvM_GetErrorStatus(
    NvM_BlockIdType BlockId,
    NvM_RequestResultType* RequestResultPtr
);

extern Std_ReturnType NvM_ReadBlock(
    NvM_BlockIdType BlockId,
    void* NvM_DstPtr
);

extern Std_ReturnType NvM_WriteBlock(
    NvM_BlockIdType BlockId,
    void* NvM_SrcPtr
);
extern void NvM_Init(void);
extern void NvM_MainFunction( void );
#endif /* NVM_H_ */

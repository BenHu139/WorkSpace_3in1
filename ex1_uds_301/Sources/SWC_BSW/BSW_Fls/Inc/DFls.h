
/* ***************************************************************************/
#ifndef _DFLS_H_
#define _DFLS_H_

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "DFls_Def.h"

/*****************************************************************************/
/*                         MACRO DEFINE                                      */
/*****************************************************************************/
extern void  DFls_vidInit(void);
extern void  DFls_vidWdgSrv(u8 startNow);
extern uint8 DFls_u8BlockErase(uint8 EraseBlockNum);
extern uint8 DFls_u8Erase(uint32 u32DstAddr, uint32 u32Length);
extern uint8 DFLS_u8BlankCheck(uint32 u32Addr,uint32 u32Length);
extern uint8 DFls_u8WriteDW(uint32 u32DestAddr, uint8* pu8SrcData);
extern uint8 DFls_u8Write(uint32 u32DestAddr, uint8* pu8SrcData, uint32 u32Length);
extern uint8 DFls_u8Read(uint32 u32SrcAddr,uint8* pu8DestData,uint32 u32Length);
extern uint8 DFls_u8Compare(uint32 u32SrcAddr,uint8* pu8DestData,uint32 u32Length);


#endif /* DFLS_H */

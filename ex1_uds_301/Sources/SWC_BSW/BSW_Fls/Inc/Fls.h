
/*------------------------ END MANAGEMENT OF EVOLUTIONS ---------------------*/
/* ***************************************************************************/
#ifndef _FLS_H_
#define _FLS_H_

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Fls_def.h"

/*****************************************************************************/
/*                         MACRO DEFINE                                      */
/*****************************************************************************/
void  Fls_vidCaliUnlock(void );
void  Fls_vidCalilock(void );
void  Fls_vidInit(void);
void  Fls_vidWdgSrv(void);
uint8 Fls_u8BlockErase(uint8 EraseBlockNum);
uint8 Fls_u8Erase(uint32 u32DstAddr, uint32 u32Length);
uint8 Fls_u8BlankCheck(uint32 u32Addr,uint32 u32Length);
uint8 Fls_u8WriteDW(uint32 u32DestAddr, uint8* pu8SrcData);
uint8 Fls_u8Write(uint32 u32DestAddr, uint8* pu8SrcData, uint32 u32Length);
uint8 Fls_u8Read(uint32 u32SrcAddr,uint8* pu8DestData,uint32 u32Length);
uint8 Fls_u8Compare(uint32 u32SrcAddr,uint8* pu8DestData,uint32 u32Length);

#endif /* DFLS_H */

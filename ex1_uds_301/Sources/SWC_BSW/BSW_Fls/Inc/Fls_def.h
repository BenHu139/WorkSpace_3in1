
/*------------------------ END MANAGEMENT OF EVOLUTIONS ---------------------*/
/* ***************************************************************************/
#ifndef _FLS_DEF_H_
#define _FLS_DEF_H_
/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Std_Types.h"
#include "MPC5602B.h"
#include "Rtc_Drv.h"
#include "Wdg.h"
#include "Dio.h"

/* !Comment: operation in RAM definition  */
#define FLS_RAM_OP_ENA           STD_ON

/* !Comment: Data Flash Address definition */
#define FLS_ADDR_START_B0F0  ((uint32)0x00000000)
#define FLS_ADDR_START_B0F1  ((uint32)0x00008000)
#define FLS_ADDR_START_B0F2  ((uint32)0x0000C000)
#define FLS_ADDR_START_B0F3  ((uint32)0x00010000)
#define FLS_ADDR_START_B0F4  ((uint32)0x00018000)
#define FLS_ADDR_START_B0F5  ((uint32)0x00020000)

#define FLS_ADDR_END_B0F0    ((uint32)0x00007FFF)
#define FLS_ADDR_END_B0F1    ((uint32)0x0000BFFF)
#define FLS_ADDR_END_B0F2    ((uint32)0x0000FFFF)
#define FLS_ADDR_END_B0F3    ((uint32)0x00017FFF)
#define FLS_ADDR_END_B0F4    ((uint32)0x0001FFFF)
#define FLS_ADDR_END_B0F5    ((uint32)0x0003FFFF)

#define FLS_BLOCK_B0F0_SIZE  ((uint32)0x00008000)
#define FLS_BLOCK_B0F1_SIZE  ((uint32)0x00004000)
#define FLS_BLOCK_B0F2_SIZE  ((uint32)0x00004000)
#define FLS_BLOCK_B0F3_SIZE  ((uint32)0x00008000)
#define FLS_BLOCK_B0F4_SIZE  ((uint32)0x00008000)
#define FLS_BLOCK_B0F5_SIZE  ((uint32)0x00020000)

#define FLS_BASE_ADDR        FLS_ADDR_START_B0F0
#define FLS_END_ADDR         FLS_ADDR_END_B0F5

#define FLS_BLOCK_B0F0         ((uint8)0x01)
#define FLS_BLOCK_B0F1         ((uint8)0x02)
#define FLS_BLOCK_B0F2         ((uint8)0x04)
#define FLS_BLOCK_B0F3         ((uint8)0x08)
#define FLS_BLOCK_B0F4         ((uint8)0x10)
#define FLS_BLOCK_B0F5         ((uint8)0x20)

#define FLS_PAGE_SIZE          ((uint8)0x08)
#define FLS_ERASE_VALUE        ((uint8)0xFF)

/* !Comment: CFLASH operating status definition */
#define FLS_BLOCK_OK           ((uint8)0x00)
#define FLS_ERROR_PE_NOK       ((uint8)0x01)
#define FLS_ERROR_ADDR_ALIGN   ((uint8)0x02)
#define FLS_ERROR_SIZE_ALIGN   ((uint8)0x03)
#define FLS_ERROR_BUSY         ((uint8)0x04)
#define FLS_ERROR_RANGE        ((uint8)0x05)
#define FLS_ERROR_NOT_BLANK    ((uint8)0x06)

/* !Comment : Low/Mid address space lock enable password */
#define FLS_LMLR_PASSWORD      ((uint32)0xA1A11111)
/* !Comment : Secondary low and middle address space lock enable password */
#define FLS_SLMLR_PASSWORD     ((uint32)0xC3C33333)

#define FLS_BOOT_BLOCK_LOCK    0xFFC4U

#define FLS_BOOT_CALIBLOCK_LOCK    0xFFC0U

/* !Comment: watchdog refresh ticks  */
#define FLS_WDG_REFRESH_CNT    ((uint8)10)

#define FLS_vidRefreshWdg()     (SIUL.GPDO[DIO_OUT_WTD].B.PDO =  !(SIUL.GPDO[DIO_OUT_WTD].B.PDO))

/* !Comment: Interrrupt definition  */
#define Fls_vidIntDisable() (RtcDRVDisable())
#define Fls_vidIntEnable()  (RtcDRVEnable())


/* !Comment : Registers assignments in Macros */
#define FLS_vidLOW_MID_PASS()               (CFLASH.LML.R = FLS_LMLR_PASSWORD)

#define FLS_vidSEC_LOW_MID_PASS()           (CFLASH.SLL.R = FLS_SLMLR_PASSWORD)

#define FLS_vidLOW_MID_UNLOCK(SecNum)       (CFLASH.LML.B.LLK &= SecNum)

#define FLS_vidSEC_LOW_MID_UNLOCK(SecNum)   (CFLASH.SLL.B.SLK &= SecNum)

#define FLS_vidLOW_MID_LOCK(SecNum)         (CFLASH.LML.B.LLK |= SecNum)

#define FLS_vidSEC_LOW_MID_LOCK(SecNum)     (CFLASH.SLL.B.SLK |= SecNum)

#define FLS_vidSTART_PROGRAM()              (CFLASH.MCR.B.PGM = 1)

#define FLS_vidSTOP_PROGRAM()               (CFLASH.MCR.B.PGM = 0)

#define FLS_vidPROGRAM_BUSY()               (CFLASH.MCR.B.PGM == 1)

#define FLS_vidSTART_ERASE()                (CFLASH.MCR.B.ERS = 1)

#define FLS_vidSTOP_ERASE()                 (CFLASH.MCR.B.ERS = 0)

#define FLS_vidERASE_BUSY()                 (CFLASH.MCR.B.ERS == 1)

#define FLS_vidPE_DONE()                    (CFLASH.MCR.B.DONE)

#define FLS_vidPE_BUSY()                    (CFLASH.MCR.B.DONE == 0)

#define FLS_vidPE_GOOD()                    (CFLASH.MCR.B.PEG)

#define FLS_vidHIGH_VLT_ENA()               (CFLASH.MCR.B.EHV = 1)

#define FLS_vidHIGH_VLT_DIS()               (CFLASH.MCR.B.EHV = 0)

#define FLS_vidLOW_BLOCKS_ERASE_SEL(SecNum) (CFLASH.LMS.B.LSL = SecNum)

#define FLS_vidCLEAR_ECC_DATA_CORRECTION()  (CFLASH.MCR.B.EDC = 1)

#define FLS_vidCLEAR_ECC_EVENT_ERROR()      (CFLASH.MCR.B.EER = 1)

#define FLS_vidCLEAR_RW_EVENT_ERROR()       (CFLASH.MCR.B.RWE = 1)

#define FLS_vidBLOCKS_PROTECTION() \
{\
   FLS_vidLOW_MID_PASS(); \
   FLS_vidLOW_MID_UNLOCK(FLS_BOOT_BLOCK_LOCK); \
   FLS_vidSEC_LOW_MID_PASS(); \
   FLS_vidSEC_LOW_MID_UNLOCK(FLS_BOOT_BLOCK_LOCK); \
}


#define FLS_vidCaliBLOCKS_PROTECTION() \
{\
   FLS_vidLOW_MID_PASS(); \
   FLS_vidLOW_MID_UNLOCK(FLS_BOOT_CALIBLOCK_LOCK); \
   FLS_vidSEC_LOW_MID_PASS(); \
   FLS_vidSEC_LOW_MID_UNLOCK(FLS_BOOT_CALIBLOCK_LOCK); \
}

#endif /* FLS_DEF_H */

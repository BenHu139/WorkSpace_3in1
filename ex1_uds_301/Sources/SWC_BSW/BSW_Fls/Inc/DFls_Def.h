
/* ***************************************************************************/
#ifndef _DFLS_DEF_H_
#define _DFLS_DEF_H_
/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Std_Types.h"
#include "MPC5602B.h"
#include "Rtc_Drv.h"
#include "Wdg.h"

/* !Comment: Data Flash Address definition */
#define DFLS_BASE_ADDR       0x00800000U
#define DFLS_BLOCK_NUM       0x04
#define DFLS_BLOCK_SIZE      0x4000
#define DFLS_END_ADDR        (DFLS_BASE_ADDR + DFLS_BLOCK_SIZE * DFLS_BLOCK_NUM - 1)

#define DFLS_ADDR_START_B1F0 0x00800000U
#define DFLS_ADDR_START_B1F1 0x00804000U
#define DFLS_ADDR_START_B1F2 0x00808000U
#define DFLS_ADDR_START_B1F3 0x0080C000U

#define DFLS_BLOCK_B1F0      0x01
#define DFLS_BLOCK_B1F1      0x02
#define DFLS_BLOCK_B1F2      0x04
#define DFLS_BLOCK_B1F3      0x08

#define DFLS_PAGE_SIZE       0x08
#define DFLS_FLAG_VALUE		 0x00
#define DFLS_ERASE_VALUE     0xFF

/* !Comment: DFlash operating status definition */
#define DFLS_BLOCK_OK           0x00
#define DFLS_ERROR_PE_NOK       0x01
#define DFLS_ERROR_ADDR_ALIGN   0x02
#define DFLS_ERROR_SIZE_ALIGN   0x03
#define DFLS_ERROR_BUSY         0x04
#define DFLS_ERROR_RANGE        0x05
#define DFLS_ERROR_NOT_BLANK    0x06

/* !Comment : Low/Mid address space lock enable password */
#define DFLS_LMLR_PASSWORD    0xA1A11111U
/* !Comment : Secondary low and middle address space lock enable password */
#define DFLS_SLMLR_PASSWORD   0xC3C33333U

/* !Comment : FLS Block's protection Configurations */
#define DFLS_ALL_BLOCK_UNLOCK   0xFFF0U
#define DFLS_ALL_BLOCK_LOCK     0xFFFFU

#define DFLS_BLOCK_B1F0_UNLOCK  0xFFFEU
#define DFLS_BLOCK_B1F1_UNLOCK  0xFFFDU
#define DFLS_BLOCK_B1F2_UNLOCK  0xFFFBU
#define DFLS_BLOCK_B1F3_UNLOCK  0xFFF7U

#define DFLS_BLOCK_B1F0_LOCK    0xFFF1U
#define DFLS_BLOCK_B1F1_LOCK    0xFFF2U
#define DFLS_BLOCK_B1F2_LOCK    0xFFF4U
#define DFLS_BLOCK_B1F3_LOCK    0xFFF8U


/* !Comment: watchdog refresh ticks  */
#define DFLS_WDG_REFRESH_CNT    ((uint8)100)

/* !Comment: operation in RAM definition  */
#define DFLS_RAM_OP_ENA         STD_ON

#define DFLS_vidRefreshWdg()    (SIUL.GPDO[DIO_OUT_WTD].B.PDO = !(SIUL.GPDO[DIO_OUT_WTD].B.PDO))
/* !Comment: Interrrupt definition  */
#define DFls_vidIntDisable() (RtcDRVDisable())
#define DFls_vidIntEnable()  (RtcDRVEnable())

/* !Comment : Registers assignments in Macros */
#define DFLS_vidLOW_MID_PASS()               (DFLASH.LML.R = DFLS_LMLR_PASSWORD)

#define DFLS_vidSEC_LOW_MID_PASS()           (DFLASH.SLL.R = DFLS_SLMLR_PASSWORD)

#define DFLS_vidLOW_MID_UNLOCK(SecNum)       (DFLASH.LML.B.LLK &= SecNum)

#define DFLS_vidSEC_LOW_MID_UNLOCK(SecNum)   (DFLASH.SLL.B.SLK &= SecNum)

#define DFLS_vidLOW_MID_LOCK(SecNum)         (DFLASH.LML.B.LLK |= SecNum)

#define DFLS_vidSEC_LOW_MID_LOCK(SecNum)     (DFLASH.SLL.B.SLK |= SecNum)

#define DFLS_vidSTART_PROGRAM()              (DFLASH.MCR.B.PGM = 1)

#define DFLS_vidSTOP_PROGRAM()               (DFLASH.MCR.B.PGM = 0)

#define DFLS_vidPROGRAM_BUSY()               (DFLASH.MCR.B.PGM == 1)

#define DFLS_vidSTART_ERASE()                (DFLASH.MCR.B.ERS = 1)

#define DFLS_vidSTOP_ERASE()                 (DFLASH.MCR.B.ERS = 0)

#define DFLS_vidERASE_BUSY()                 (DFLASH.MCR.B.ERS == 1)

#define DFLS_vidPE_DONE()                    (DFLASH.MCR.B.DONE)

#define DFLS_vidPE_BUSY()                    (DFLASH.MCR.B.DONE == 0)

#define DFLS_vidPE_GOOD()                    (DFLASH.MCR.B.PEG)

#define DFLS_vidHIGH_VLT_ENA()               (DFLASH.MCR.B.EHV = 1)

#define DFLS_vidHIGH_VLT_DIS()               (DFLASH.MCR.B.EHV = 0)

#define DFLS_vidLOW_BLOCKS_ERASE_SEL(SecNum) (DFLASH.LMS.B.LSL = SecNum)

#define DFLS_vidCLEAR_ECC_DATA_CORRECTION()  (DFLASH.MCR.B.EDC = 1)

#define DFLS_vidCLEAR_ECC_EVENT_ERROR()      (DFLASH.MCR.B.EER = 1)

#define DFLS_vidCLEAR_RW_EVENT_ERROR()       (DFLASH.MCR.B.RWE = 1)

#endif /* DFLS_DEF_H */

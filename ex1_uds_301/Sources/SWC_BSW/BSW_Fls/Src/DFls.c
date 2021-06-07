

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/

/* !Comment : Including public headers                                       */

/* !Comment : Including internal headers                                     */
#include "includes.h"
#include "DFls.h"
#include "SWdg.h"

/* ***************************************************************************/
/*                         GLOBAL VARIABLES                                  */
/* ***************************************************************************/
uint16 DFls_u16WdgCnt;

typedef union
{
   uint8  u8Array[8];
   uint16 u16Array[4];
   uint32 u32Array[2];
} DFLS_padding_type;

DFLS_padding_type DFls_padding;

/* ***************************************************************************/
/*                         MACRO DEFINE                                      */
/* ***************************************************************************/
#if (DFLS_RAM_OP_ENA == STD_ON)
#define DFLS_u32PROG_CODE_SIZE       246UL
#define DFLS_u32ERASE_CODE_SIZE      188UL

/* ***************************************************************************/
/* !Comment:    Opcodes that carry the Erasing sequence.                                                              */
/* ***************************************************************************/
static uint32 DFls_au32EraseInRam[DFLS_u32PROG_CODE_SIZE];
static uint32 DFls_au32ProgInRam[DFLS_u32PROG_CODE_SIZE];
#endif
/* ***************************************************************************/
/*                         LOCAL PROTOTYPES                                  */
/* ***************************************************************************/


/* ***************************************************************************/
/*                         SOURCE CODE                                       */
/* ***************************************************************************/

/* ***************************************************************************/
/* Function Name     : DFls_vidWdgSrv                                        */
/* Description       : Dflash watchdog service routine                       */
/* Input Parameters  : None                                                  */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
void DFls_vidWdgSrv(u8 startNow)
{
   if(TRUE == startNow)
   {
	   Wdg_vidFastRefresh();
	   HAL_MCU_WDT_ClearInsideDog();
	   DFls_u16WdgCnt = 0;
   }
   else
   {
	  DFls_u16WdgCnt++;
	  if (DFls_u16WdgCnt >= DFLS_WDG_REFRESH_CNT)
	  {
		 Wdg_vidFastRefresh();
		 HAL_MCU_WDT_ClearInsideDog();
		 DFls_u16WdgCnt = 0;
	  }
   }
}

/* ***************************************************************************/
/* Function Name     : void Fls_vidInit(void)                                */
/* Description       : Initialize the data flash module                      */
/* Input Parameters  : None                                                  */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
void DFls_vidInit(void)
{
   DFLS_vidLOW_MID_PASS();
   DFLS_vidLOW_MID_UNLOCK(DFLS_ALL_BLOCK_UNLOCK);

   DFLS_vidSEC_LOW_MID_PASS();
   DFLS_vidSEC_LOW_MID_UNLOCK(DFLS_ALL_BLOCK_UNLOCK);

   DFLS_vidCLEAR_ECC_DATA_CORRECTION();
   DFLS_vidCLEAR_ECC_EVENT_ERROR();
   DFLS_vidCLEAR_RW_EVENT_ERROR();
}


/* ***************************************************************************/
/* Function Name     : uint8 DFls_u8BlockErase(uint8 EraseBlockNum)          */
/* Description       : Erase one data flash sector                           */
/* Input Parameters  : uint8 EraseBlockNum                                   */
/*                           Data flash sector numner 0x1 ~ 0x0f             */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
#if (DFLS_RAM_OP_ENA == STD_ON)
void DFls_vidSectorEraseInRAM(uint8 u8BlockNum, uint64* Loc_pu64Dest, uint8* pu8EraseSt)
{
   DFLS_vidSTART_ERASE();
   DFLS_vidLOW_BLOCKS_ERASE_SEL(u8BlockNum);

   /* !Comment : interlock write required by the hardware to verify the type of memory to erase */
   *Loc_pu64Dest = (uint64)DFLS_ERASE_VALUE;

   DFLS_vidHIGH_VLT_ENA();
   DFls_vidWdgSrv(TRUE);
   while (DFLS_vidPE_DONE() == 0)
   {
      /* !Comment: Refresh Watchdog */
      DFls_vidWdgSrv(FALSE);
   }

   if (DFLS_vidPE_GOOD() == 0)
   {
      *pu8EraseSt = DFLS_ERROR_PE_NOK;
   }

   DFLS_vidHIGH_VLT_DIS();
   DFLS_vidSTOP_ERASE();
}
#endif
/*****************************************************************************/
/* Function Name     : uint8 DFls_u8BlockErase(uint8 EraseBlockNum)          */
/* Description       : Erase one data flash sector                           */
/* Input Parameters  : uint8 EraseBlockNum                                   */
/*                           Data flash sector numner 0x1 ~ 0x0f             */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/*****************************************************************************/
uint8 DFls_u8BlockErase(uint8 EraseBlockNum)
{
   uint8  Loc_u8Idx;
   uint8  Loc_u8BlockEraseSt;
   uint64 *Loc_pu64Destination;
#if (DFLS_RAM_OP_ENA == STD_ON)
   void (*Loc_pfErase)(uint8, uint64*, uint8*);
   uint8  Loc_u8LoopIdx;
   uint32 *Loc_pu32Array;
#endif


   Loc_u8Idx          = EraseBlockNum;
   Loc_u8BlockEraseSt = DFLS_BLOCK_OK;

   if ((Loc_u8Idx & DFLS_BLOCK_B1F0) == DFLS_BLOCK_B1F0)
   {
      Loc_pu64Destination  = (uint64 *)DFLS_ADDR_START_B1F0;
   }
   else if ((Loc_u8Idx & DFLS_BLOCK_B1F1) == DFLS_BLOCK_B1F1)
   {
      Loc_pu64Destination  = (uint64 *)DFLS_ADDR_START_B1F1;
   }
   else if ((Loc_u8Idx & DFLS_BLOCK_B1F2) == DFLS_BLOCK_B1F2)
   {
      Loc_pu64Destination  = (uint64 *)DFLS_ADDR_START_B1F2;
   }
   else if ((Loc_u8Idx & DFLS_BLOCK_B1F3) == DFLS_BLOCK_B1F3)
   {
      Loc_pu64Destination  = (uint64 *)DFLS_ADDR_START_B1F3;
   }
   else
   {
      Loc_u8BlockEraseSt = DFLS_ERROR_RANGE;
   }
   
   if (Loc_u8BlockEraseSt == DFLS_BLOCK_OK)
   {
      if (DFLS_vidPROGRAM_BUSY() || DFLS_vidERASE_BUSY() || DFLS_vidPE_BUSY())
      {
         Loc_u8BlockEraseSt = DFLS_ERROR_BUSY;
      }
      else
      {
         /* Disable the interrupt   */
         DFls_vidIntDisable();
         __MSYNC();

#if (DFLS_RAM_OP_ENA == STD_ON)
//         for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < DFLS_u32ERASE_CODE_SIZE; Loc_u8LoopIdx++)
//         {
//            DFls_au32EraseInRam[Loc_u8LoopIdx] = 0;
//         }
//
//         Loc_pu32Array = (uint32 *)(&DFls_vidSectorEraseInRAM);
//         for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < DFLS_u32ERASE_CODE_SIZE; Loc_u8LoopIdx++)
//         {
//            DFls_au32EraseInRam[Loc_u8LoopIdx] = Loc_pu32Array[Loc_u8LoopIdx];
//         }
//         Loc_pfErase = (void (*)(uint8, uint64*, uint8*))&DFls_au32EraseInRam;
//         Loc_pfErase(Loc_u8Idx,Loc_pu64Destination,&Loc_u8BlockEraseSt);
         DFls_vidSectorEraseInRAM(Loc_u8Idx,Loc_pu64Destination,&Loc_u8BlockEraseSt);
#else
         DFLS_vidSTART_ERASE();
         DFLS_vidLOW_BLOCKS_ERASE_SEL(Loc_u8Idx);

         /* !Comment : interlock write required by the hardware to verify the type of memory to erase */
         *Loc_pu64Destination = (uint64)DFLS_ERASE_VALUE;
         DFLS_vidHIGH_VLT_ENA();
         DFls_vidWdgSrv(TRUE);
         while (DFLS_vidPE_DONE() == 0)
         {
            /* !Comment: Refresh Watchdog */
            DFls_vidWdgSrv(FALSE);
         }

         if (DFLS_vidPE_GOOD() == 0)
         {
            Loc_u8BlockEraseSt = DFLS_ERROR_PE_NOK;
         }

         DFLS_vidHIGH_VLT_DIS();
         DFLS_vidSTOP_ERASE();
#endif
         __MSYNC();
         /* Enable the interrupt   */
         DFls_vidIntEnable();
      }
   }

   return Loc_u8BlockEraseSt;
}


/* ***************************************************************************/
/* Function Name     : uint8 DFls_u8Erase(uint32 u32DstAddr, uint32 u32Length)*/
/* Description       : Erase one data flash sector                           */
/* Input Parameters  : uint8 EraseBlockNum                                   */
/*                           Data flash sector numner 0x1 ~ 0x0f             */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
uint8 DFls_u8Erase(uint32 u32DstAddr, uint32 u32Length)
{
   uint8  Loc_u8EraseSt;
   uint8  Loc_u8BlockNum;
   uint32 Loc_u32Addr;
   uint64 *Loc_pu64Destination;
#if (DFLS_RAM_OP_ENA == STD_ON)
   void (*Loc_pfErase)(uint8, uint64*, uint8*);
   uint8  Loc_u8LoopIdx;
   uint32 *Loc_pu32Array;
#endif

   Loc_u8EraseSt  = DFLS_BLOCK_OK;
   Loc_u8BlockNum = 0;
   Loc_u32Addr    = u32DstAddr;

   if (u32Length == 0U)
   {
      
   }
   else if (  (Loc_u32Addr < DFLS_BASE_ADDR)
           || (Loc_u32Addr > DFLS_END_ADDR)
           || ((Loc_u32Addr + u32Length - 1U) > DFLS_END_ADDR))
   {
      Loc_u8EraseSt = DFLS_ERROR_RANGE;
   }
   else
   {
      if (Loc_u32Addr >= DFLS_ADDR_START_B1F3)
      {
         Loc_pu64Destination = (uint64 *)DFLS_ADDR_START_B1F3;
         Loc_u8BlockNum      = DFLS_BLOCK_B1F3;
      }
      else if (Loc_u32Addr >= DFLS_ADDR_START_B1F2)
      {
         Loc_pu64Destination = (uint64 *)DFLS_ADDR_START_B1F2;
         if ((Loc_u32Addr + u32Length) < DFLS_ADDR_START_B1F3)
         {
            Loc_u8BlockNum = DFLS_BLOCK_B1F2;
         }
         else
         {
            Loc_u8BlockNum = (DFLS_BLOCK_B1F2 | DFLS_BLOCK_B1F3);
         }
      }
      else if (Loc_u32Addr >= DFLS_ADDR_START_B1F1)
      {
         Loc_pu64Destination = (uint64 *)DFLS_ADDR_START_B1F1;
         if ((Loc_u32Addr + u32Length) < DFLS_ADDR_START_B1F2)
         {
            Loc_u8BlockNum = DFLS_BLOCK_B1F1;
         }
         else if ((Loc_u32Addr + u32Length) < DFLS_ADDR_START_B1F3)
         {
            Loc_u8BlockNum = (DFLS_BLOCK_B1F1 | DFLS_BLOCK_B1F2);
         }
         else
         {
            Loc_u8BlockNum = (DFLS_BLOCK_B1F1 | DFLS_BLOCK_B1F2 | DFLS_BLOCK_B1F3);
         }
      }
      else
      {
         Loc_pu64Destination = (uint64 *)DFLS_ADDR_START_B1F0;
         if ((Loc_u32Addr + u32Length) < DFLS_ADDR_START_B1F1)
         {
            Loc_u8BlockNum = DFLS_BLOCK_B1F0;
         }
         else if ((Loc_u32Addr + u32Length) < DFLS_ADDR_START_B1F2)
         {
            Loc_u8BlockNum = (DFLS_BLOCK_B1F0 | DFLS_BLOCK_B1F1);
         }
         else if ((Loc_u32Addr + u32Length) < DFLS_ADDR_START_B1F3)
         {
            Loc_u8BlockNum = (DFLS_BLOCK_B1F0 | DFLS_BLOCK_B1F1 | DFLS_BLOCK_B1F2);
         }
         else
         {
            Loc_u8BlockNum = (DFLS_BLOCK_B1F0 | DFLS_BLOCK_B1F1 | DFLS_BLOCK_B1F2 | DFLS_BLOCK_B1F3);
         }
      }

      if (DFLS_vidPROGRAM_BUSY() || DFLS_vidERASE_BUSY() || DFLS_vidPE_BUSY())
      {
         Loc_u8EraseSt = DFLS_ERROR_BUSY;
      }
      else
      {
         /* Disable the interrupt   */
         DFls_vidIntDisable();
         __MSYNC();

#if (DFLS_RAM_OP_ENA == STD_ON)
//         for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < DFLS_u32ERASE_CODE_SIZE; Loc_u8LoopIdx++)
//         {
//            DFls_au32EraseInRam[Loc_u8LoopIdx] = 0;
//         }
//
//         Loc_pu32Array = (uint32 *)(&DFls_vidSectorEraseInRAM);
//         for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < DFLS_u32ERASE_CODE_SIZE; Loc_u8LoopIdx++)
//         {
//            DFls_au32EraseInRam[Loc_u8LoopIdx] = Loc_pu32Array[Loc_u8LoopIdx];
//         }
//
//         Loc_pfErase = (void(*)(uint8, uint64*, uint8*))&DFls_au32EraseInRam;
//         Loc_pfErase(Loc_u8BlockNum,Loc_pu64Destination,&Loc_u8EraseSt);
         DFls_vidSectorEraseInRAM(Loc_u8BlockNum,Loc_pu64Destination,&Loc_u8EraseSt);
#else
         DFLS_vidSTART_ERASE();
         DFLS_vidLOW_BLOCKS_ERASE_SEL(Loc_u8BlockNum);

         /* !Comment : interlock write required by the hardware to verify the type of memory to erase */
         *Loc_pu64Destination = (uint64)DFLS_ERASE_VALUE;
         DFLS_vidHIGH_VLT_ENA();
         DFls_vidWdgSrv(TRUE);
         while (DFLS_vidPE_DONE() == 0)
         {
            /* !Comment: Refresh Watchdog */
        	 DFls_vidWdgSrv(FALSE);
         }

         if (DFLS_vidPE_GOOD() == 0)
         {
            Loc_u8EraseSt = DFLS_ERROR_PE_NOK;
         }

         DFLS_vidHIGH_VLT_DIS();
         DFLS_vidSTOP_ERASE();
#endif
         __MSYNC();
         /* Enable the interrupt   */
         DFls_vidIntEnable();
      }
   }
   
   return Loc_u8EraseSt;
}
/*****************************************************************************/
/* Function Name   : uint8 DFLS_u8BlankCheck(uint32 u32Addr,uint32 u32Length)*/
/* Description       : Check the data flah blank                             */
/* Input Parameters  : uint32 u32Addr                                        */
/*                     uint32 u32Length                                      */
/* Output Parameters : uint8                                                 */
/* Others            :                                                       */
/*****************************************************************************/
uint8 DFLS_u8BlankCheck(uint32 u32Addr,uint32 u32Length)
{
   uint8   Loc_u8BlankSt;
   uint32  Loc_u32Idx;
   boolean Loc_bIsSame;


   Loc_u8BlankSt = DFLS_BLOCK_OK;
   if ((u32Addr >= DFLS_BASE_ADDR) && (u32Addr <= DFLS_END_ADDR))
   {
      if (u32Length == 0U)
      {
         
      }
      else if (  (u32Length <= DFLS_BLOCK_SIZE * DFLS_BLOCK_NUM)
               && ((u32Addr + u32Length - 1U) <= DFLS_END_ADDR))
      {
         /* Disable the interrupt   */
         DFls_vidIntDisable();
         __MSYNC();

         Loc_bIsSame = TRUE;
         DFls_vidWdgSrv(TRUE);
         for (Loc_u32Idx = 0; (Loc_u32Idx < u32Length) && (Loc_bIsSame != FALSE); Loc_u32Idx++)
         {
            if (*(volatile uint8 *)u32Addr == DFLS_ERASE_VALUE || *(volatile uint8 *)u32Addr == DFLS_FLAG_VALUE)
            {
               u32Addr++;
            }
            else
            {
               Loc_bIsSame   = FALSE;
               Loc_u8BlankSt = DFLS_ERROR_NOT_BLANK;
            }
            /* !Comment: Refresh Watchdog */
            DFls_vidWdgSrv(FALSE);
         }
         
         __MSYNC();
         /* Enable the interrupt   */
         DFls_vidIntEnable();
         
         if (Loc_bIsSame != FALSE)
         {
            Loc_u8BlankSt = DFLS_BLOCK_OK;
         }
      }
   }

   return Loc_u8BlankSt;
}

/* ***************************************************************************/
/* Function Name : uint8 DFls_u8WriteDW(uint32 u32DestAddr,uint8 *pu8SrcData)*/
/* Description       : Program the data to the data flash                    */
/* Input Parameters  : uint32 u32DestAddr                                    */
/*                           the address that the data will be written       */
/*                     uint8 *pu8SrcData --> the pointer of the data         */
/* Output Parameters : uint8                                                 */
/* Others            :                                                       */
/* ***************************************************************************/
uint8 DFls_u8WriteDW(uint32 u32DestAddr, uint8* pu8SrcData)
{
   uint8 Loc_u8WriteDWSt;

   Loc_u8WriteDWSt = DFLS_u8BlankCheck(u32DestAddr, DFLS_PAGE_SIZE);
   if (Loc_u8WriteDWSt == DFLS_BLOCK_OK)
   {
      if (DFLS_vidPROGRAM_BUSY() || DFLS_vidERASE_BUSY() || DFLS_vidPE_BUSY())
      {
         Loc_u8WriteDWSt = DFLS_ERROR_BUSY;
      }
      else
      {
         /* Disable the interrupt   */
         DFls_vidIntDisable();
         __MSYNC();

         DFLS_vidSTART_PROGRAM();

         *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
         u32DestAddr += 4;
         pu8SrcData  += 4;
#if (DFLS_PAGE_SIZE == 8U)
         *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
         u32DestAddr += 4;
         pu8SrcData  += 4;
#endif
         DFLS_vidHIGH_VLT_ENA();
         DFls_vidWdgSrv(TRUE);
         while (DFLS_vidPE_DONE() == 0)
         {
           /* !Comment: Refresh Watchdog */
           DFls_vidWdgSrv(FALSE);
         }
         if (DFLS_vidPE_GOOD() == 0)
         {
           Loc_u8WriteDWSt = DFLS_ERROR_PE_NOK;
         }

         DFLS_vidHIGH_VLT_DIS();
         DFLS_vidSTOP_PROGRAM();
         __MSYNC();
         /* Enable the interrupt   */
         DFls_vidIntEnable();
      }
   }

   return Loc_u8WriteDWSt;
}


/*****************************************************************************/
/* Function Name     : uint8 Fls_u8Write(uint32 u32DestAddr,                 */
/*                                    uint8 *pu8SrcData,uint32 u32Length)    */
/* Description       : Program the data to the data flash                    */
/* Input Parameters  : uint32 u32DestAddr                                    */
/*                           the address that the data will be written       */
/*                     uint8 *pu8SrcData --> the pointer of the data         */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/*****************************************************************************/

#if (DFLS_RAM_OP_ENA == STD_ON)
void  DFls_vidSectorWriteInRam(uint32 u32DestAddr, uint8* pu8SrcData, uint32 u32Length,uint8 *pu8WriteSt)
{
	  u8 i, remainNum;  
	  u32 pageNum;
	  
      DFLS_vidSTART_PROGRAM();
      
      pageNum = u32Length / DFLS_PAGE_SIZE;
      remainNum = (u8)(u32Length % DFLS_PAGE_SIZE);
      if(remainNum != 0)
      {
    	  DFls_padding.u32Array[0] = 0xFFFFFFFF;
    	  DFls_padding.u32Array[1] = 0xFFFFFFFF;
    	  
    	  for(i = 0;i < remainNum; i++)
    	  {
    		  DFls_padding.u8Array[i] = *(pu8SrcData + pageNum * DFLS_PAGE_SIZE + i);
    	  }
      }

      *pu8WriteSt = DFLS_BLOCK_OK;
      while ((*pu8WriteSt == DFLS_BLOCK_OK) && (u32Length > 0))
      {
         if (DFLS_vidERASE_BUSY() || DFLS_vidPE_BUSY())
         {
            *pu8WriteSt = DFLS_ERROR_BUSY;
         }
         else
         {
            *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
            u32DestAddr += 4;
            pu8SrcData  += 4;
   
#if (DFLS_PAGE_SIZE == 8U)
            *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
            u32DestAddr += 4;
            pu8SrcData  += 4;
#endif
   
            DFLS_vidHIGH_VLT_ENA();
            DFls_vidWdgSrv(TRUE);
            while (DFLS_vidPE_DONE() == 0)
            {
              /* !Comment: Refresh Watchdog */
              DFls_vidWdgSrv(FALSE);
            }
            if (DFLS_vidPE_GOOD() == 0)
            {
              *pu8WriteSt = DFLS_ERROR_PE_NOK;
            }
   
            DFLS_vidHIGH_VLT_DIS();
         }
         
         if (u32Length >= DFLS_PAGE_SIZE * 2)
         {
            u32Length = u32Length - DFLS_PAGE_SIZE;
         }
         else if(u32Length > DFLS_PAGE_SIZE)
         {
        	pu8SrcData = &(DFls_padding.u8Array[0]);
            u32Length = DFLS_PAGE_SIZE;
         }
         else
         {
        	 u32Length = 0;
         }
      }
      DFLS_vidSTOP_PROGRAM();

}
#endif
/*****************************************************************************/
/* Function Name     : uint8 Fls_u8Write(uint32 u32DestAddr,                 */
/*                                    uint8 *pu8SrcData,uint32 u32Length)    */
/* Description       : Program the data to the data flash                    */
/* Input Parameters  : uint32 u32DestAddr                                    */
/*                           the address that the data will be written       */
/*                     uint8 *pu8SrcData --> the pointer of the data         */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/*****************************************************************************/
uint8 DFls_u8Write(uint32 u32DestAddr, uint8* pu8SrcData, uint32 u32Length)
{
   uint8  Loc_u8WriteSt;
#if (DFLS_RAM_OP_ENA == STD_ON)
   void (*Loc_pfProg)(uint32, uint8*, uint32, uint8*);
   uint8 Loc_u8LoopIdx;
   uint32* Loc_pu32Array;
#endif

   /* Disable the interrupt   */
   DFls_vidIntDisable();
   __MSYNC();
#if (DFLS_RAM_OP_ENA == STD_ON)
   /* Copy flash driver to RAM */
   for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < DFLS_u32PROG_CODE_SIZE; Loc_u8LoopIdx++)
   {
	   DFls_au32ProgInRam[Loc_u8LoopIdx] = 0;
   }
   Loc_pu32Array = (uint32 *)(&DFls_vidSectorWriteInRam);
   for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < DFLS_u32PROG_CODE_SIZE; Loc_u8LoopIdx++)
   {
	   DFls_au32ProgInRam[Loc_u8LoopIdx] = Loc_pu32Array[Loc_u8LoopIdx];
   }
   Loc_pfProg = (void (*)(uint32, uint8*, uint32, uint8*))&DFls_au32ProgInRam;
   /* Call flash driver in RAM */
   //Loc_pfProg(u32DestAddr,pu8SrcData,u32Length,&Loc_u8WriteSt);
   DFls_vidSectorWriteInRam(u32DestAddr,pu8SrcData,u32Length,&Loc_u8WriteSt);
#else
   DFLS_vidSTART_PROGRAM();
   
   Loc_u8WriteSt = DFLS_BLOCK_OK;
   while ((Loc_u8WriteSt == DFLS_BLOCK_OK) && (u32Length > 0))
   {
      if (DFLS_vidERASE_BUSY() || DFLS_vidPE_BUSY())
      {
         Loc_u8WriteSt = DFLS_ERROR_BUSY;
      }
      else
      {
         *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
         u32DestAddr += 4;
         pu8SrcData  += 4;

#if (DFLS_PAGE_SIZE == 8U)
         *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
         u32DestAddr += 4;
         pu8SrcData  += 4;
#endif

         DFLS_vidHIGH_VLT_ENA();
         DFls_vidWdgSrv(TRUE);
         while (DFLS_vidPE_DONE() == 0)
         {
           /* !Comment: Refresh Watchdog */
           DFls_vidWdgSrv(FALSE);
         }
         if (DFLS_vidPE_GOOD() == 0)
         {
           Loc_u8WriteSt = DFLS_ERROR_PE_NOK;
         }

         DFLS_vidHIGH_VLT_DIS();
      }
      
      if (u32Length >= DFLS_PAGE_SIZE)
      {
         u32Length = u32Length - DFLS_PAGE_SIZE;
      }
      else
      {
         u32Length = 0;
      }
   }
   DFLS_vidSTOP_PROGRAM();
#endif
   __MSYNC();
   /* Enable the interrupt   */
   DFls_vidIntEnable();

   return Loc_u8WriteSt;
}

/* ***************************************************************************/
/* Function Name     : uint8 DFls_u8Read(uint32 u32SrcAddr,                  */
/*                                       uint8 *pu8DestData,uint32 u32Length)*/
/* Description       : Read the data from the data flash                     */
/* Input Parameters  : uint32 u32SrcAddr                                     */
/*                           the address that the data will be read          */
/*                     uint8 *pu8DestData --> the pointer of the data buffer */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
uint8 DFls_u8Read(uint32 u32SrcAddr,uint8* pu8DestData,uint32 u32Length)
{
   uint32 Loc_u32Idx;
   uint32 Loc_u32EndAddr;
   uint8  Loc_u8ReadSt;


   Loc_u32EndAddr = u32SrcAddr + u32Length - 1;
   if (Loc_u32EndAddr <= DFLS_END_ADDR)
   {
      /* Disable the interrupt   */
      DFls_vidIntDisable();
      __MSYNC();
      DFls_vidWdgSrv(TRUE);
      for (Loc_u32Idx = 0; Loc_u32Idx < u32Length; Loc_u32Idx++)
      {
         *pu8DestData = (*(volatile uint8*)(u32SrcAddr));
         pu8DestData++;
         u32SrcAddr++;

         /* !Comment: refresh the watchdog  */
         DFls_vidWdgSrv(FALSE);
      }
      Loc_u8ReadSt = DFLS_BLOCK_OK;
      
      __MSYNC();
      /* Enable the interrupt   */
      DFls_vidIntEnable();
   }
   else
   {
      Loc_u8ReadSt = DFLS_ERROR_RANGE;
   }

   return Loc_u8ReadSt;
}


/* ***************************************************************************/
/* Function Name     : uint8 DFls_u8Compare(uint32 u32SrcAddr,               */
/*                                       uint8 *pu8DestData,uint32 u32Length)*/
/* Description       : compare the data in data flash with the buffer        */
/* Input Parameters  : uint32 u32SrcAddr                                     */
/*                           the address that the data will be read          */
/*                     uint8 *pu8DestData --> the pointer of the data buffer */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
uint8 DFls_u8Compare(uint32 u32SrcAddr,uint8* pu8DestData,uint32 u32Length)
{
   uint32 Loc_u32Idx;
   uint32 Loc_u32EndAddr;
   uint8  Loc_u8CmpSt;


   Loc_u32Idx  = 0;
   Loc_u8CmpSt = DFLS_BLOCK_OK;
   Loc_u32EndAddr = u32SrcAddr + u32Length - 1;
   if (Loc_u32EndAddr <= DFLS_END_ADDR)
   {
      /* Disable the interrupt   */
      DFls_vidIntDisable();
      __MSYNC();
      DFls_vidWdgSrv(TRUE);
      while ((Loc_u32Idx < u32Length) && (Loc_u8CmpSt == DFLS_BLOCK_OK))
      {
         if (*pu8DestData != (*(volatile uint8*)(u32SrcAddr)))
         {
            Loc_u8CmpSt = DFLS_ERROR_PE_NOK;
         }
         pu8DestData++;
         u32SrcAddr++;
         Loc_u32Idx++;

         /* !Comment: refresh the watchdog  */
         DFls_vidWdgSrv(FALSE);
      }
      __MSYNC();
      /* Enable the interrupt   */
      DFls_vidIntEnable();
   }
   else
   {
      Loc_u8CmpSt = DFLS_ERROR_RANGE;
   }

   return Loc_u8CmpSt;
}


/*--------------------------------- end of the file ---------------------------------------*/

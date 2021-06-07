

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/

/* !Comment : Including public headers                                       */

/* !Comment : Including internal headers                                     */

#include "includes.h"
#include "Fls.h"
#include "SWdg.h"

/* ***************************************************************************/
/*                         GLOBAL VARIABLES                                  */
/* ***************************************************************************/
uint16 Fls_u16WdgCnt;

/* ***************************************************************************/
/*                         MACRO DEFINE                                      */
/* ***************************************************************************/
#if (FLS_RAM_OP_ENA == STD_ON)
#define FLS_u32PROG_CODE_SIZE      64UL
#define FLS_u32ERASE_CODE_SIZE     64UL

/* ***************************************************************************/
/* !Comment:    Opcodes that carry the Erasing sequence.                                                              */
/* ***************************************************************************/
//static uint32 Fls_au32EraseInRam[FLS_u32PROG_CODE_SIZE];
static uint32 Fls_au32EraseInRam[FLS_u32ERASE_CODE_SIZE];
static uint32 Fls_au32ProgInRam[FLS_u32PROG_CODE_SIZE];
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
void Fls_vidWdgSrv(void)
{
   Fls_u16WdgCnt++;
   if (Fls_u16WdgCnt >= FLS_WDG_REFRESH_CNT)
   {
      Wdg_vidFastRefresh();
      Fls_u16WdgCnt = 0;
   }
   HAL_MCU_WDT_ClearInsideDog();
}
/* ***************************************************************************/
/* Function Name     : void Fls_vidCaliUnlock(void)                          */
/* Description       : Initialize the data flash module                      */
/* Input Parameters  : None                                                  */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
void Fls_vidCaliUnlock(void )
{

     FLS_vidCaliBLOCKS_PROTECTION();

   FLS_vidCLEAR_ECC_DATA_CORRECTION();
   FLS_vidCLEAR_ECC_EVENT_ERROR();
   FLS_vidCLEAR_RW_EVENT_ERROR();
}

/* ***************************************************************************/
/* Function Name     : void Fls_vidCalilock(void)                          */
/* Description       : Initialize the data flash module                      */
/* Input Parameters  : None                                                  */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
void Fls_vidCalilock(void )
{

   FLS_vidBLOCKS_PROTECTION();

   FLS_vidCLEAR_ECC_DATA_CORRECTION();
   FLS_vidCLEAR_ECC_EVENT_ERROR();
   FLS_vidCLEAR_RW_EVENT_ERROR();
}


/* ***************************************************************************/
/* Function Name     : void Fls_vidInit(void)                                */
/* Description       : Initialize the data flash module                      */
/* Input Parameters  : None                                                  */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
void Fls_vidInit(void)
{
   //FLS_vidLOW_MID_PASS();
   //FLS_vidSEC_LOW_MID_PASS();

   FLS_vidBLOCKS_PROTECTION();

   FLS_vidCLEAR_ECC_DATA_CORRECTION();
   FLS_vidCLEAR_ECC_EVENT_ERROR();
   FLS_vidCLEAR_RW_EVENT_ERROR();
}


/* ***************************************************************************/
/* Function Name     : uint8 DFls_u8BlockErase(uint8 EraseBlockNum)          */
/* Description       : Erase one data flash sector                                            */
/* Input Parameters  : uint8 EraseBlockNum                                                    */
/*                           Data flash sector numner 0x1 ~ 0x0f                              */
/* Output Parameters : None                                                                   */
/* Others            :                                                                        */
/* ***************************************************************************/
#if (FLS_RAM_OP_ENA == STD_ON)
void Fls_vidSectorEraseInRAM(uint8 u8BlockNum,uint64* Loc_pu64Dest,uint8* pu8EraseSt)
{
   FLS_vidSTART_ERASE();
   FLS_vidLOW_BLOCKS_ERASE_SEL(u8BlockNum);

   /* !Comment : interlock write required by the hardware to verify the type of memory to erase */
   *Loc_pu64Dest = (uint64)FLS_ERASE_VALUE;

   FLS_vidHIGH_VLT_ENA();
   while (FLS_vidPE_DONE() == 0)
   {
      /* !Comment: Refresh Watchdog */
	  // Fls_vidWdgSrv();
	   Dio_vidToggleOutputCh(E_DOUT_WTD);
   }

   if (FLS_vidPE_GOOD() == 0)
   {
      *pu8EraseSt = FLS_ERROR_PE_NOK;
   }

   FLS_vidHIGH_VLT_DIS();
   FLS_vidSTOP_ERASE();
}
#endif
/*****************************************************************************/
/* Function Name     : uint8 Fls_u8BlockErase(uint8 EraseBlockNum)           */
/* Description       : Erase one data flash sector                           */
/* Input Parameters  : uint8 EraseBlockNum                                   */
/*                           Data flash sector numner 0x1 ~ 0x0f             */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/*****************************************************************************/
uint8 Fls_u8BlockErase(uint8 EraseBlockNum)
{
   uint8  Loc_u8Idx;
   uint8  Loc_u8BlockEraseSt;
   uint64 *Loc_pu64Destination;
#if (DFLS_RAM_OP_ENA == STD_ON)
   void  (*Loc_pfErase)(uint8 ,uint64* ,uint8*);
   uint8  Loc_u8LoopIdx;
   uint32 *Loc_pu32Array;
#endif
   Loc_u8Idx          = EraseBlockNum;
   Loc_u8BlockEraseSt = FLS_BLOCK_OK;

   if ((Loc_u8Idx & FLS_BLOCK_B0F0) == FLS_BLOCK_B0F0)
   {
      Loc_pu64Destination  = (uint64 *)FLS_ADDR_START_B0F0;
   }
   else if ((Loc_u8Idx & FLS_BLOCK_B0F1) == FLS_BLOCK_B0F1)
   {
      Loc_pu64Destination  = (uint64 *)FLS_ADDR_START_B0F1;
   }
   else if ((Loc_u8Idx & FLS_BLOCK_B0F2) == FLS_BLOCK_B0F2)
   {
      Loc_pu64Destination  = (uint64 *)FLS_ADDR_START_B0F2;
   }
   else if ((Loc_u8Idx & FLS_BLOCK_B0F3) == FLS_BLOCK_B0F3)
   {
      Loc_pu64Destination  = (uint64 *)FLS_ADDR_START_B0F3;
   }
   else if ((Loc_u8Idx & FLS_BLOCK_B0F4) == FLS_BLOCK_B0F4)
   {
      Loc_pu64Destination  = (uint64 *)FLS_ADDR_START_B0F4;
   }
   else if ((Loc_u8Idx & FLS_BLOCK_B0F5) == FLS_BLOCK_B0F5)
   {
      Loc_pu64Destination  = (uint64 *)FLS_ADDR_START_B0F5;
   }
   else
   {
      Loc_u8BlockEraseSt = FLS_ERROR_RANGE;
   }
   
   if (Loc_u8BlockEraseSt == FLS_BLOCK_OK)
   {
      if (FLS_vidPROGRAM_BUSY() || FLS_vidERASE_BUSY() || FLS_vidPE_BUSY())
      {
         Loc_u8BlockEraseSt = FLS_ERROR_BUSY;
      }
      else
      {
         /* Disable the interrupt   */
         Fls_vidIntDisable();
         __MSYNC();
#if (DFLS_RAM_OP_ENA == STD_ON)
         for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < FLS_u32ERASE_CODE_SIZE; Loc_u8LoopIdx++)
         {
            Fls_au32EraseInRam[Loc_u8LoopIdx] = 0;
         }
         Loc_pu32Array = (uint32 *)(&Fls_vidSectorEraseInRAM);
         for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < FLS_u32ERASE_CODE_SIZE; Loc_u8LoopIdx++)
         {
            Fls_au32EraseInRam[Loc_u8LoopIdx] = Loc_pu32Array[Loc_u8LoopIdx];
         }
         Loc_pfErase = Fls_au32EraseInRam;

         /* Call flash driver in RAM */
         Loc_pfErase(Loc_u8Idx,Loc_pu64Destination,&Loc_u8BlockEraseSt);
  #else
         FLS_vidSTART_ERASE();
         FLS_vidLOW_BLOCKS_ERASE_SEL(Loc_u8Idx);

         /* !Comment : interlock write required by the hardware to verify the type of memory to erase */
         *Loc_pu64Destination = (uint64)FLS_ERASE_VALUE;

         FLS_vidHIGH_VLT_ENA();
         while (FLS_vidPE_DONE() == 0)
         {
            /* !Comment: Refresh Watchdog */
        	//Fls_vidWdgSrv();
        	 Dio_vidToggleOutputCh(E_DOUT_WTD);
         }

         if (FLS_vidPE_GOOD() == 0)
         {
            Loc_u8BlockEraseSt = FLS_ERROR_PE_NOK;
         }

         FLS_vidHIGH_VLT_DIS();
         FLS_vidSTOP_ERASE();
  #endif

         /* Enable the interrupt   */
         Fls_vidIntEnable();
      }
   }

   return Loc_u8BlockEraseSt;
}


/* ***************************************************************************/
/* Function Name     : uint8 Fls_u8Erase(uint32 u32DstAddr, uint32 u32Length)*/
/* Description       : Erase one data flash sector                           */
/* Input Parameters  : uint8 EraseBlockNum                                   */
/*                           Data flash sector numner 0x1 ~ 0x0f             */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
uint8 Fls_u8Erase(uint32 u32DstAddr, uint32 u32Length)
{
   uint8  Loc_u8EraseSt;
   uint8  Loc_u8BlockNum;
   uint32 Loc_u32Addr;
   uint64 *Loc_pu64Destination;
#if (FLS_RAM_OP_ENA == STD_ON)
   void  (*Loc_pfErase)(uint8, uint64*, uint8*);
   uint8  Loc_u8LoopIdx;
   uint32 *Loc_pu32Array;
#endif

   Loc_u8EraseSt  = FLS_BLOCK_OK;
   Loc_u8BlockNum = 0;
   Loc_u32Addr    = u32DstAddr;

if ((Loc_u32Addr > FLS_END_ADDR) || ((Loc_u32Addr + u32Length - 1) > FLS_END_ADDR))
   {
      Loc_u8EraseSt = FLS_ERROR_RANGE;
   }
   else
   {
      if (Loc_u32Addr >= FLS_ADDR_START_B0F5)
      {
    	  Loc_pu64Destination = (uint64 *)FLS_ADDR_START_B0F5;
         Loc_u8BlockNum      = FLS_BLOCK_B0F5;
      }
      else if (Loc_u32Addr >= FLS_ADDR_START_B0F4)
      {
    	  Loc_pu64Destination = (uint64 *)FLS_ADDR_START_B0F4;
         if (u32Length <= FLS_BLOCK_B0F4_SIZE)
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F4;
         }
         else
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F4 | FLS_BLOCK_B0F5;
         }
      }
      else if (Loc_u32Addr >= FLS_ADDR_START_B0F3)
      {
    	  Loc_pu64Destination = (uint64 *)FLS_ADDR_START_B0F3;
         if (u32Length <= FLS_BLOCK_B0F3_SIZE)
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F3;
         }
         else if (u32Length <= (FLS_BLOCK_B0F3_SIZE + FLS_BLOCK_B0F4_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F3 | FLS_BLOCK_B0F4;
         }
         else
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F3 | FLS_BLOCK_B0F4 | FLS_BLOCK_B0F5;
         }
      }
      else if (Loc_u32Addr >= FLS_ADDR_START_B0F2)
      {
    	  Loc_pu64Destination = (uint64 *)FLS_ADDR_START_B0F2;
         if (u32Length <= FLS_BLOCK_B0F2_SIZE)
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F2;
         }
         else if (u32Length <= (FLS_BLOCK_B0F2_SIZE + FLS_BLOCK_B0F3_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3;
         }
         else if (u32Length <= (FLS_BLOCK_B0F2_SIZE + FLS_BLOCK_B0F3_SIZE + FLS_BLOCK_B0F4_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3 | FLS_BLOCK_B0F4;
         }
         else
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3 | FLS_BLOCK_B0F4 | FLS_BLOCK_B0F5;
         }
      }
      else if (Loc_u32Addr >= FLS_ADDR_START_B0F1)
      {
    	  Loc_pu64Destination = (uint64 *)FLS_ADDR_START_B0F1;
         if (u32Length <= FLS_BLOCK_B0F1_SIZE)
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F1;
         }
         else if (u32Length <= (FLS_BLOCK_B0F1_SIZE + FLS_BLOCK_B0F2_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F1 | FLS_BLOCK_B0F2;
         }
         else if (u32Length <= (FLS_BLOCK_B0F1_SIZE + FLS_BLOCK_B0F2_SIZE + FLS_BLOCK_B0F3_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F1 | FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3;
         }
         else if (u32Length <= (FLS_BLOCK_B0F1_SIZE + FLS_BLOCK_B0F2_SIZE + FLS_BLOCK_B0F3_SIZE + FLS_BLOCK_B0F4_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F1 | FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3 | FLS_BLOCK_B0F4;
         }
         else
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F1 | FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3 | FLS_BLOCK_B0F4 | FLS_BLOCK_B0F5;
         }
      }
      else
      {
    	  Loc_pu64Destination = (uint64 *)FLS_ADDR_START_B0F0;
         if (u32Length <= FLS_BLOCK_B0F0_SIZE)
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F0;
         }
         else if (u32Length <= (FLS_BLOCK_B0F0_SIZE + FLS_BLOCK_B0F1_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F0 | FLS_BLOCK_B0F1;
         }
         else if (u32Length <= (FLS_BLOCK_B0F0_SIZE + FLS_BLOCK_B0F1_SIZE + FLS_BLOCK_B0F2_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F0 | FLS_BLOCK_B0F1 | FLS_BLOCK_B0F2;
         }
         else if (u32Length <= (FLS_BLOCK_B0F0_SIZE + FLS_BLOCK_B0F1_SIZE + FLS_BLOCK_B0F2_SIZE + FLS_BLOCK_B0F3_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F0 | FLS_BLOCK_B0F1 | FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3;
         }
         else if (u32Length <= (FLS_BLOCK_B0F0_SIZE + FLS_BLOCK_B0F1_SIZE + FLS_BLOCK_B0F2_SIZE + FLS_BLOCK_B0F3_SIZE + FLS_BLOCK_B0F4_SIZE))
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F0 | FLS_BLOCK_B0F1 | FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3 | FLS_BLOCK_B0F4;
         }
         else
         {
            Loc_u8BlockNum   = FLS_BLOCK_B0F0 | FLS_BLOCK_B0F1 | FLS_BLOCK_B0F2 | FLS_BLOCK_B0F3 | FLS_BLOCK_B0F4 | FLS_BLOCK_B0F5;
         }
      }

      if (FLS_vidPROGRAM_BUSY() || FLS_vidERASE_BUSY() || FLS_vidPE_BUSY())
      {
         Loc_u8EraseSt = FLS_ERROR_BUSY;
      }
      else
      {
         /* Disable the interrupt   */
         Fls_vidIntDisable();
         __MSYNC();

#if (FLS_RAM_OP_ENA == STD_ON)
         for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < FLS_u32ERASE_CODE_SIZE; Loc_u8LoopIdx++)
         {
            Fls_au32EraseInRam[Loc_u8LoopIdx] = 0;
         }

         Loc_pu32Array = (uint32 *)(&Fls_vidSectorEraseInRAM);
         for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < FLS_u32ERASE_CODE_SIZE; Loc_u8LoopIdx++)
         {
            Fls_au32EraseInRam[Loc_u8LoopIdx] = Loc_pu32Array[Loc_u8LoopIdx];
         }

         Loc_pfErase =( void (*)(uint8, uint64*, uint8*))&Fls_au32EraseInRam;
         Loc_pfErase(Loc_u8BlockNum,Loc_pu64Destination,&Loc_u8EraseSt);
#else
         FLS_vidSTART_ERASE();
         FLS_vidLOW_BLOCKS_ERASE_SEL(Loc_u8BlockNum);

         /* !Comment : interlock write required by the hardware to verify the type of memory to erase */
         *Loc_pu64Destination = (uint64)FLS_ERASE_VALUE;
         FLS_vidHIGH_VLT_ENA();
         while (FLS_vidPE_DONE() == 0)
         {
            /* !Comment: Refresh Watchdog */
           // Fls_vidWdgSrv();
            FLS_vidRefreshWdg();
         }

         if (FLS_vidPE_GOOD() == 0)
         {
            Loc_u8EraseSt = FLS_ERROR_PE_NOK;
         }

         FLS_vidHIGH_VLT_DIS();
         FLS_vidSTOP_ERASE();
#endif
         __MSYNC();
         /* Enable the interrupt   */
         Fls_vidIntEnable();
      }
   }
   
   return Loc_u8EraseSt;
}

/*****************************************************************************/
/* Function Name   : uint8 Fls_u8BlankCheck(uint32 u32Addr,uint32 u32Length) */
/* Description       : Check the data flah blank                             */
/* Input Parameters  : uint32 u32Addr                                        */
/*                     uint32 u32Length                                      */
/* Output Parameters : uint8                                                 */
/* Others            :                                                       */
/*****************************************************************************/
uint8 Fls_u8BlankCheck(uint32 u32Addr,uint32 u32Length)
{
   uint8   Loc_u8BlankSt;
   uint32  Loc_u32Idx;
   boolean Loc_bIsSame;

   Loc_u8BlankSt = FLS_BLOCK_OK;
   if ((u32Addr <= FLS_END_ADDR) && (u32Length > 0))
   {
      /* Disable the interrupt   */
      Fls_vidIntDisable();
      __MSYNC();

      Loc_bIsSame = TRUE;
      for (Loc_u32Idx = 0; (Loc_u32Idx < u32Length) && (Loc_bIsSame != FALSE); Loc_u32Idx++)
      {
         if (*(volatile uint8 *)u32Addr == FLS_ERASE_VALUE)
         {
            u32Addr++;
         }
         else
         {
            Loc_bIsSame   = FALSE;
            Loc_u8BlankSt = FLS_ERROR_NOT_BLANK;
         }
         /* !Comment: Refresh Watchdog */
         //Fls_vidWdgSrv();
         Dio_vidToggleOutputCh(E_DOUT_WTD);
      }

      __MSYNC();
      /* Enable the interrupt   */
      Fls_vidIntEnable();

      if (Loc_bIsSame != FALSE)
      {
         Loc_u8BlankSt = FLS_BLOCK_OK;
      }
   }

   return Loc_u8BlankSt;
}

/* ***************************************************************************/
/* Function Name : uint8 Fls_u8WriteDW(uint32 u32DestAddr,uint8 *pu8SrcData)*/
/* Description       : Program the data to the data flash                    */
/* Input Parameters  : uint32 u32DestAddr                                    */
/*                           the address that the data will be written       */
/*                     uint8 *pu8SrcData --> the pointer of the data         */
/* Output Parameters : uint8                                                 */
/* Others            :                                                       */
/* ***************************************************************************/
uint8 Fls_u8WriteDW(uint32 u32DestAddr, uint8* pu8SrcData)
{
   uint8 Loc_u8WriteDWSt;


   Loc_u8WriteDWSt = Fls_u8BlankCheck(u32DestAddr,FLS_PAGE_SIZE);
   if (Loc_u8WriteDWSt == FLS_BLOCK_OK)
   {
      if (FLS_vidPROGRAM_BUSY() || FLS_vidERASE_BUSY() || FLS_vidPE_BUSY())
      {
         Loc_u8WriteDWSt = FLS_ERROR_BUSY;
      }
      else
      {
         /* Disable the interrupt   */
         Fls_vidIntDisable();
         __MSYNC();

         FLS_vidSTART_PROGRAM();

         *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
         u32DestAddr += 4;
         pu8SrcData  += 4;

         FLS_vidHIGH_VLT_ENA();
         while (FLS_vidPE_DONE() == 0)
         {
           /* !Comment: Refresh Watchdog */
           //Fls_vidWdgSrv();
        	 Dio_vidToggleOutputCh(E_DOUT_WTD);
         }
         if (FLS_vidPE_GOOD() == 0)
         {
           Loc_u8WriteDWSt = FLS_ERROR_PE_NOK;
         }

         FLS_vidHIGH_VLT_DIS();
         FLS_vidSTOP_PROGRAM();
         __MSYNC();
         /* Enable the interrupt   */
         Fls_vidIntEnable();
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

#if (FLS_RAM_OP_ENA == STD_ON)
void  Fls_vidSectorWriteInRam(uint32 u32DestAddr, uint8* pu8SrcData, uint32 u32Length,uint8 *pu8WriteSt)
{
      FLS_vidSTART_PROGRAM();

      *pu8WriteSt = FLS_BLOCK_OK;
      while ((*pu8WriteSt == FLS_BLOCK_OK) && (u32Length > 0))
      {
         if (FLS_vidERASE_BUSY() || FLS_vidPE_BUSY())
         {
            *pu8WriteSt = FLS_ERROR_BUSY;
         }
         else
         {
            *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
            u32DestAddr += 4;
            pu8SrcData  += 4;

            *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
               u32DestAddr += 4;
               pu8SrcData  += 4;
   
            FLS_vidHIGH_VLT_ENA();
            while (FLS_vidPE_DONE() == 0)
            {
               /* !Comment: Refresh Watchdog */
              // Fls_vidWdgSrv();
            	Dio_vidToggleOutputCh(E_DOUT_WTD);
            }
            if (FLS_vidPE_GOOD() == 0)
            {
               *pu8WriteSt = FLS_ERROR_PE_NOK;
            }
   
            FLS_vidHIGH_VLT_DIS();
         }
         
         if (u32Length >= FLS_PAGE_SIZE)
         {
            u32Length = u32Length - FLS_PAGE_SIZE;
         }
         else
         {
            u32Length = 0;
         }
      }
      FLS_vidSTOP_PROGRAM();
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
uint8 Fls_u8Write(uint32 u32DestAddr, uint8* pu8SrcData, uint32 u32Length)
{
   uint8  Loc_u8WriteSt;
#if (FLS_RAM_OP_ENA == STD_ON)
   uint8 Loc_u8LoopIdx;
   void (*Loc_pfProg)(uint32 ,uint8* ,uint32,uint8*);
   uint32* Loc_pu32Array;
#endif

   /* Disable the interrupt   */
   Fls_vidIntDisable();
   __MSYNC();
#if (FLS_RAM_OP_ENA == STD_ON)
   /* Copy flash driver to RAM */
   for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < FLS_u32PROG_CODE_SIZE; Loc_u8LoopIdx++)
   {
	   Fls_au32ProgInRam[Loc_u8LoopIdx] = 0;
   }
   Loc_pu32Array = (uint32 *)(&Fls_vidSectorWriteInRam);
   for (Loc_u8LoopIdx = 0; Loc_u8LoopIdx < FLS_u32PROG_CODE_SIZE; Loc_u8LoopIdx++)
   {
	   Fls_au32ProgInRam[Loc_u8LoopIdx] = Loc_pu32Array[Loc_u8LoopIdx];
   }
   Loc_pfProg = (void(*)(uint32 ,uint8* ,uint32,uint8*))&Fls_au32ProgInRam;

   /* Call flash driver in RAM */
   Loc_pfProg(u32DestAddr,pu8SrcData,u32Length,&Loc_u8WriteSt);
#else
   FLS_vidSTART_PROGRAM();
   
   Loc_u8WriteSt = FLS_BLOCK_OK;
   while ((Loc_u8WriteSt == FLS_BLOCK_OK) && (u32Length > 0))
   {
      if (FLS_vidERASE_BUSY() || FLS_vidPE_BUSY())
      {
         Loc_u8WriteSt = FLS_ERROR_BUSY;
      }
      else
      {
         *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
         u32DestAddr += 4;
         pu8SrcData  += 4;

         *(volatile uint32 *)u32DestAddr = *(uint32 *)pu8SrcData;
         u32DestAddr += 4;
         pu8SrcData  += 4;

         FLS_vidHIGH_VLT_ENA();
         while (FLS_vidPE_DONE() == 0)
         {
           /* !Comment: Refresh Watchdog */
           //Fls_vidWdgSrv();
           FLS_vidRefreshWdg();
         }
         if (FLS_vidPE_GOOD() == 0)
         {
           Loc_u8WriteSt = FLS_ERROR_PE_NOK;
         }

         FLS_vidHIGH_VLT_DIS();
      }
      
      if (u32Length >= FLS_PAGE_SIZE)
      {
         u32Length = u32Length - FLS_PAGE_SIZE;
      }
      else
      {
         u32Length = 0;
      }
   }
   FLS_vidSTOP_PROGRAM();
#endif
   __MSYNC();
   /* Enable the interrupt   */
   Fls_vidIntEnable();

   return Loc_u8WriteSt;
}

/* ***************************************************************************/
/* Function Name     : uint8 Fls_u8Read(uint32 u32SrcAddr,                   */
/*                                       uint8 *pu8DestData,uint32 u32Length)*/
/* Description       : Read the data from the data flash                     */
/* Input Parameters  : uint32 u32SrcAddr                                     */
/*                           the address that the data will be read          */
/*                     uint8 *pu8DestData --> the pointer of the data buffer */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
uint8 Fls_u8Read(uint32 u32SrcAddr,uint8* pu8DestData,uint32 u32Length)
{
   uint32 Loc_u32Idx;
   uint32 Loc_u32EndAddr;
   uint8  Loc_u8ReadSt;


   Loc_u32EndAddr = u32SrcAddr + u32Length - 1;
   if (Loc_u32EndAddr <= FLS_END_ADDR)
   {
      /* Disable the interrupt   */
      Fls_vidIntDisable();
      __MSYNC();
      
      for (Loc_u32Idx = 0; Loc_u32Idx < u32Length; Loc_u32Idx++)
      {
         *pu8DestData = (*(volatile uint8*)(u32SrcAddr));
         pu8DestData++;
         u32SrcAddr++;

         /* !Comment: refresh the watchdog  */
         //Fls_vidWdgSrv();
         Dio_vidToggleOutputCh(E_DOUT_WTD);
      }
      Loc_u8ReadSt = FLS_BLOCK_OK;
      
      __MSYNC();
      /* Enable the interrupt   */
      Fls_vidIntEnable();
   }
   else
   {
      Loc_u8ReadSt = FLS_ERROR_RANGE;
   }

   return Loc_u8ReadSt;
}


/* ***************************************************************************/
/* Function Name     : uint8 Fls_u8Compare(uint32 u32SrcAddr,                */
/*                                       uint8 *pu8DestData,uint32 u32Length)*/
/* Description       : compare the data in data flash with the buffer        */
/* Input Parameters  : uint32 u32SrcAddr                                     */
/*                           the address that the data will be read          */
/*                     uint8 *pu8DestData --> the pointer of the data buffer */
/* Output Parameters : None                                                  */
/* Others            :                                                       */
/* ***************************************************************************/
uint8 Fls_u8Compare(uint32 u32SrcAddr,uint8* pu8DestData,uint32 u32Length)
{
   uint32 Loc_u32Idx;
   uint32 Loc_u32EndAddr;
   uint8  Loc_u8CmpSt;


   Loc_u32Idx  = 0;
   Loc_u8CmpSt = FLS_BLOCK_OK;
   Loc_u32EndAddr = u32SrcAddr + u32Length - 1;
   if (Loc_u32EndAddr <= FLS_END_ADDR)
   {
      /* Disable the interrupt   */
      Fls_vidIntDisable();
      __MSYNC();
      
      while ((Loc_u32Idx < u32Length) && (Loc_u8CmpSt == FLS_BLOCK_OK))
      {
         if (*pu8DestData != (*(volatile uint8*)(u32SrcAddr)))
         {
            Loc_u8CmpSt = FLS_ERROR_PE_NOK;
         }
         pu8DestData++;
         u32SrcAddr++;
         Loc_u32Idx++;

         /* !Comment: refresh the watchdog  */
        // Fls_vidWdgSrv();
         Dio_vidToggleOutputCh(E_DOUT_WTD);
      }
      __MSYNC();
      /* Enable the interrupt   */
      Fls_vidIntEnable();
   }
   else
   {
      Loc_u8CmpSt = FLS_ERROR_RANGE;
   }

   return Loc_u8CmpSt;
}


/*--------------------------------- end of the file ---------------------------------------*/

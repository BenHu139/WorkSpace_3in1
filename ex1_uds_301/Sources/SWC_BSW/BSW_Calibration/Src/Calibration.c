/*
 * @Author: your name
 * @Date: 2020-03-20 10:31:03
 * @LastEditTime: 2020-04-01 10:18:51
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \DCDC_FCTDemo_3kwEx\SWC_BSW\BSW_Calibration\Src\Calibration.c
 */

/**********************************************************************************************************************/

#include "Std_Types.h"
#include "Fls_def.h"
#include "Fls.h"
#include "Calibration.h"



/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* FUNCTIONS DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define START_SEC_CODE
//#include "MemMap.h"

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : CALIB_vidCopyFromRamToFlash                                                                         */
/*                                                                                                                    */
/* !Description :                                                                                                     */
/* !Number      : 0x01                                                                                                */
/* !Reference   :                                                                                                     */
/*                                                                                                                    */
/* !Trace_To    :                                                                                                     */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                 */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
uint8 CALIB_vidCopyFromRamToFlash(void)
{
   uint32 Loc_u32Cnt1;
   uint32 Loc_u32FlsAdr;
   uint32 *Loc_pu32Val;
   uint32 Loc_au32Data[2];
   uint8 Loc_u8RetSt;

   Loc_u8RetSt = Fls_u8Erase(CALIB_SECTION_FLS_START_ADDRESS, CALIB_SECTION_LENGTH);
   
   if (FLS_BLOCK_OK == Loc_u8RetSt)
   {
      Loc_pu32Val = (uint32 *)CALIB_SECTION_RAM_START_ADDRESS;
      Loc_u32FlsAdr = CALIB_SECTION_FLS_START_ADDRESS;
      for (Loc_u32Cnt1 = 0; Loc_u32Cnt1 < (CALIB_SECTION_LENGTH >> 3); Loc_u32Cnt1++)
      {
         Loc_au32Data[0] = *(Loc_pu32Val);
         Loc_au32Data[1] = *(Loc_pu32Val + 1);
         Loc_pu32Val += 2;
         Loc_u8RetSt = Fls_u8Write(Loc_u32FlsAdr, (uint8 *)Loc_au32Data, 8);
         if (Loc_u8RetSt != FLS_BLOCK_OK)
         {
            return Loc_u8RetSt;
         }
         Loc_u32FlsAdr += 8;
      }

      //Mcu_PerformReset();
   }
   else
   {
   }

   return Loc_u8RetSt;
}

uint8 CALIB_u8ClearCalibFlash(void)
{
   return Fls_u8Erase(CALIB_SECTION_FLS_START_ADDRESS, CALIB_SECTION_LENGTH);
}
#define STOP_SEC_CODE
//#include "MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/

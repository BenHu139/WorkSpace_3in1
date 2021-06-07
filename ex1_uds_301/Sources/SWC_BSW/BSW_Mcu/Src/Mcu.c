

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "includes.h"
#include "Mcu_Cfg.h"
#include "Mcu_Def.h"

/* ***************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/* ***************************************************************************/

/* ***************************************************************************/
/*                              SOURCE CODE                                  */
/* ***************************************************************************/

typedef void (*mem_write_code_ptr_t)(uint32_t, uint32_t);
void Mcu_vidPFlashConfig(void)
{
#define FLASH_CONFIG_DATA 0x18877F7F
#define FLASH_CONFIG_REG CFLASH.PFCR0.R
#define FLASH_ACCESS_PROT_DATA 0x30FFFF
#define FLASH_ACCESS_PROT_REG 0x203E00

   volatile uint32_t mem_write_code_vle[] =
       {
           0x54640000, /* e_stw r3,(0)r4 machine code: writes r3 contents to addr in r4 */
           0x7C0006AC, /* mbar machine code: ensure prior store completed */
           0x00040004  /* 2 se_blr's machine code: branches to return address in link reg.*/
       };

   (*((mem_write_code_ptr_t)mem_write_code_vle))(FLASH_CONFIG_DATA,            /* which passes integer (in r3) */
                                                 (uint32_t)&FLASH_CONFIG_REG); /* and address to write integer (in r4) */

   (*((mem_write_code_ptr_t)mem_write_code_vle)) /* cast mem_write_code as func ptr*/
                                                 /* * de-references pfunc ptr, i.e. converts to func*/
       (FLASH_ACCESS_PROT_DATA,                  /* which passes integer (in r3) */
        (uint32_t)FLASH_ACCESS_PROT_REG);       /* and address to write integer (in r4) */
}

/* *************************************************************************/
/* Function Name     : void Mcu_vidRunModeConfig(void)                     */
/* Brief Description : MCU run mode Configuration                          */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
static void Mcu_vidRunModeConfig(void)
{
   /* !Comment :  RUN0 Mode Configuration                                   */
   ME.RUN[MCU_ME_RUN0].B.CFLAON = MCU_ME_FLASH_ON;
   ME.RUN[MCU_ME_RUN0].B.DFLAON = MCU_ME_FLASH_ON;

   ME.RUN[MCU_ME_RUN0].B.FXOSCON = MCU_ME_XOSCON_ON;

   ME.RUN[MCU_ME_RUN0].B.FMPLLON = MCU_ME_SYSTEM_FMPLL_ON;
   ME.RUN[MCU_ME_RUN0].B.SYSCLK = MCU_ME_SYSCLK_SYSPLL;
   
   /* !Comment :  RUN0 Mode Configuration                                   */
   ME.STANDBY0.B.FIRCON = STD_OFF;

   /* !Comment : RunPC 0 active in DRUN, RUN0 mode */
   ME.RUNPC[MCU_ME_RUNPC0].B.RUN3 = STD_OFF;
   ME.RUNPC[MCU_ME_RUNPC0].B.RUN2 = STD_OFF;
   ME.RUNPC[MCU_ME_RUNPC0].B.RUN1 = STD_OFF;
   ME.RUNPC[MCU_ME_RUNPC0].B.RUN0 = STD_ON;
   ME.RUNPC[MCU_ME_RUNPC0].B.DRUN = STD_ON;
   ME.RUNPC[MCU_ME_RUNPC0].B.SAFE = STD_OFF;
   ME.RUNPC[MCU_ME_RUNPC0].B.TEST = STD_OFF;
   /* !Comment : LowPower PC 0 default gated in all lowpower mode */
   ME.LPPC[MCU_ME_LPPC0].B.STANDBY0 = STD_OFF;
   ME.LPPC[MCU_ME_LPPC0].B.STOP0 = STD_OFF;
   ME.LPPC[MCU_ME_LPPC0].B.HALT0 = STD_OFF;
   /* !Comment : LowPower PC 1 active in standby mode */
   ME.LPPC[MCU_ME_LPPC1].B.STANDBY0 = STD_ON;
   ME.LPPC[MCU_ME_LPPC1].B.STOP0 = STD_OFF;
   ME.LPPC[MCU_ME_LPPC1].B.HALT0 = STD_OFF;
}

/* *************************************************************************/
/* Function Name     : void Mcu_vidRunModeConfig(void)                     */
/* Brief Description : MCU run mode Configuration                          */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
static void Mcu_vidPctlConfig(void)
{
   u8 Loc_u8Index;

   for (Loc_u8Index = 0; Loc_u8Index < MCU_PCTL_MAX; Loc_u8Index++)
   {
      ME.PCTL[MCU_Peripherals_Config[Loc_u8Index].u8PCTL_ID].B.DBG_F = MCU_Peripherals_Config[Loc_u8Index].u8DBG_F;

      ME.PCTL[MCU_Peripherals_Config[Loc_u8Index].u8PCTL_ID].B.LP_CFG = MCU_Peripherals_Config[Loc_u8Index].u8LP_CFG;

      ME.PCTL[MCU_Peripherals_Config[Loc_u8Index].u8PCTL_ID].B.RUN_CFG = MCU_Peripherals_Config[Loc_u8Index].u8RUNPC_CFG;
   }
}

/* *************************************************************************/
/* Function Name     : void Mcu_vidRunModeConfig(void)                     */
/* Brief Description : MCU run mode Configuration                          */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
static void Mcu_vidRunModeEntry(void)
{
   /* !Comment : Clock Out Selector -> secondary Mhz PLL, Div by 4 */
   CGM.OCDS_SC.B.SELDIV = MCU_CGM_OUTCLK_DIV_4;
   CGM.OCDS_SC.B.SELCTL = MCU_CGM_OUTCLK_SRC_FMPLL0;  
   /* !Comment : Set Configure Motor Control clock at 64 Mhz (auxilliary clock 0) */
   CGM.SC_SS.B.SELSTAT = MCU_CGM_AC0_SRC_FMPLL0;
   /* !Comment : Divider to lowest value Div = 1 and Divider enable for auxilliary clocks */
   CGM.SC_DC[0].B.DIV = MCU_CGM_AC0_NO_DIV;
   CGM.SC_DC[0].B.DE = MCU_CGM_AC0_DIV_ENABLE;
   
   CGM.SC_DC[1].B.DIV = MCU_CGM_AC0_NO_DIV;
   CGM.SC_DC[1].B.DE = MCU_CGM_AC0_DIV_ENABLE;
      
   CGM.SC_DC[2].B.DIV = MCU_CGM_AC0_NO_DIV;
   CGM.SC_DC[2].B.DE = MCU_CGM_AC0_DIV_ENABLE;
   /* !Comment: FMPLL0 REF divider     */
   CGM.FMPLL_CR.B.IDF = MCU_CGM_PLL_DIV_IPF1;
   /* !Comment: FMPLL0 VCO divider     */
   CGM.FMPLL_CR.B.ODF = MCU_CGM_PLL_DIV_ODF4; 
   /* !Comment: FMPLL0 LOOP divider     */
   CGM.FMPLL_CR.B.NDIV = MCU_CGM_PLL_DIV_NDIF64;
   /* !Comment: ENABLE THE pll output    */
   CGM.FMPLL_CR.B.EN_PLL_SW = MCU_CGM_PLL_SW_EN;
   /* !Comment: Output Clock Disabled*/
   CGM.OC_EN.B.EN = MCU_CLK_OUT_DISABLE;                  
   
   /* To Go in Run Mode */
   ME.MCTL.R = 0x40005AF0;
   ME.MCTL.R = 0x4000A50F;
   /* !Comment: Wait for mode entry to complete */
   while (ME.GS.B.S_MTRANS != FALSE)
      ;
   /* !comment: Check RUN0 MODE mode has been entered */
   while (ME.GS.B.S_CURRENTMODE != RUN0_MODE)
      ;
   /* !Comment: Wait for OSC stabilization */
   while (ME.GS.B.S_FXOSC == FALSE)
      ;
   /* !Comment: Wait for PLL locked */
   while (ME.GS.B.S_FMPLL == FALSE)
      ;
}

/* *************************************************************************/
/* Function Name     : void Mcu_vidRunModeConfig(void)                     */
/* Brief Description : MCU run mode Configuration                          */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Mcu_vidInit(void)
{
   /* !Comment :  Enable RUN1, RUN2, RUN3, STOP, HALT, STANDBY                 */
   /* RESET, SAFE, DRUN, and RUN0 modes are always enabled                     */
   ME.MER.R = MCU_ME_MER_CONFIGURATION;
   CGM.CMU_CSR.R = MCU_CGM_RC_DIV_8;

   /* !comment: MCU RUN mode configuration */
   Mcu_vidRunModeConfig();
   /* !comment: MCU PCTL register configuration */
   Mcu_vidPctlConfig();
   /* !comment: enter into the RUN MODE */
   Mcu_vidRunModeEntry();
   /* !COMMENT: Configure the Pflash */
   // Mcu_vidPFlashConfig();
}

/* *************************************************************************/
/* Function Name     : void Mcu_vidRunModeConfig(void)                     */
/* Brief Description : MCU run mode Configuration                          */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Mcu_vidReset(void)
{
   /* !Comment : Switch into Reset Mode                                        */
   ME.MCTL.R = 0x00005AF0;
   ME.MCTL.R = 0x0000A50F;
   /* !comment: Wait mode transition complete*/
   while (ME.GS.B.S_MTRANS != FALSE)
   {
   }
   while (ME.GS.B.S_CURRENTMODE != 0x00)
   {
   };
}

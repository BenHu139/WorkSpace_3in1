
/* ***************************************************************************/

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/

#include "includes.h"
#include "Port.h"
/* ***************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/* ***************************************************************************/

/* ***************************************************************************/
/*                              SOURCE CODE                                  */
/* ***************************************************************************/

/* *************************************************************************/
/* Function Name     : void Port_vidInit(void)                             */
/* Brief Description : PORT Configuration                                  */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others        :                                                         */
/* *************************************************************************/
void Port_vidInit(void)
{
   uint8 Loc_u8Index;

   /* !Comment : Initialize pad configuration registers */
   for (Loc_u8Index = 0; Loc_u8Index < PCR_MAX; Loc_u8Index++)
   {
	   if(Loc_u8Index < PCR_MAX -2) SIU.PCR[Loc_u8Index].R = Port_u16PadConfigValue[Loc_u8Index];
	   else if(Loc_u8Index == 77) SIU.PCR[121].R = Port_u16PadConfigValue[Loc_u8Index];
	   else if(Loc_u8Index == 78) SIU.PCR[122].R = Port_u16PadConfigValue[Loc_u8Index];
   }
   
   /* !Comment : Initialize Pad Selection for Multiplexed Inputs */
   for(Loc_u8Index = 0;Loc_u8Index < PSMI_MAX;Loc_u8Index++)
   {
      SIU.PSMI[Loc_u8Index].R = Port_u8PadSelMulInputValue[Loc_u8Index];
   }
   
   /* !Comment : Initialize GPIO Pad Data Output Registers */
   for (Loc_u8Index = 0;Loc_u8Index < GPDO_MAX;Loc_u8Index++)
   {
      SIU.GPDO[Loc_u8Index].R = Port_u8PadOutputValue [Loc_u8Index];
   }

   /* !Comment : Initialize Interrupt Filter Maximum Counter Registers */
   for (Loc_u8Index = 0;Loc_u8Index < IFMC_MAX;Loc_u8Index++)
   {
      SIU.IFMC[Loc_u8Index].R = Port_u32PadIntrruptCLK[Loc_u8Index];
   }
   
   SIU.ISR.R   = PORT_IF_ALL_CLEAR;
   SIU.IRER.R  = PORT_INT_ALL_DISABLE;
   SIU.IREER.R = PORT_EDGE_EVENT_DISABLE;
   SIU.IFEER.R = PORT_EDGE_EVENT_DISABLE;
   SIU.IFER.R  = PORT_FILTER_DISABLE;
   SIU.IFCPR.R = PROT_INT_FILTER_CLK_0;
}

/* *************************************************************************/
/* Function Name     : void Port_vidPadDirConfig(uint8 PortNum,uint16 ConfigValue) */
/* Brief Description : set the output channel value                                */
/* Input Parameters  : u8 ChannelID --- channel number to be write                 */
/*                     boolean Value -- the value to be write to the channel       */
/* Output Parameters :                                                         */
/* Others        :                                                             */
/* ****************************************************************************/
void Port_vidPadDirConfig(uint8 PortNum,uint16 ConfigValue)
{
   SIU.PCR[PortNum].R = ConfigValue;
}



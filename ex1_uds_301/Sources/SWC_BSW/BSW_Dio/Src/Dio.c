/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Dio.h"
#include "Adc.h"

#define Dio_vidSetOutputCh(ChannelID, Value)   (SIU.GPDO[ChannelID].B.PDO = (Value))

/* ***************************************************************************/
/*                              SOURCE CODE                                  */
/* ***************************************************************************/

/* *************************************************************************/
/* Function Name     : void Dio_vidWriteOutputCh(uint8 ch,boolean Value)*/
/* Brief Description : set the output channel value                            */
/* Input Parameters  : u8 ch --- channel number to be write             */
/*                     boolean Value -- the value to be write to the channel   */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Dio_vidWriteOutputCh(uint8 ch, boolean Value)
{
	u8 idx;
	
	if(ch < E_DOUT_CH_MAX_NUM)
	{
		idx = BSW_astrDigOutputDef[ch].u8Ch;
		SIU.GPDO[idx].B.PDO = Value;
	}
}

/* **************************************************************************/
/* Function Name     : boolean Dio_bReadInputCh(uint8 ch)            */
/* Brief Description : read the input channel value                         */
/* Input Parameters  : u8 ch -- channel number to be read            */
/* Output Parameters :                                                      */
/* Others            :                                                      */
/* **************************************************************************/
boolean Dio_bReadInputCh(uint8 ch)
{
	u8   idx;
	u16  adcVal;
		
	if(ch < E_DIN_CH_MAX_NUM)
	{
		if(BSW_astrDigInputDef[ch].u8DiSource == 0)				// 0 : GPIO
		{
			idx = BSW_astrDigInputDef[ch].u8Ch;
			return (SIU.GPDI[idx].B.PDI);
		}
		else if(BSW_astrDigInputDef[ch].u8DiSource == 1)		// 1 : ADC
		{
			adcVal = Adc_u16GetResult(BSW_astrDigInputDef[ch].u8Ch);
			if(adcVal > BSW_astrDigInputDef[ch].u16HiAdcVal) return TRUE;
			else if(adcVal < BSW_astrDigInputDef[ch].u16LoAdcVal) return FALSE;
		}
	}
}

boolean Dio_bReadFliterInputVal(uint8 ch)
{		
	if(ch < E_DIN_CH_MAX_NUM)
	{
		return BSW_astrDigInputDef[ch].bVal;
	}
}

/* **************************************************************************/
/* Function Name     : boolean Dio_bReadOutputCh(uint8 ch)           */
/* Brief Description : read the output channel value                        */
/* Input Parameters  : u8 ch -- channel number to be read            */
/* Output Parameters :                                                      */
/* Others            :                                                      */
/* **************************************************************************/
boolean Dio_bReadOutputCh(uint8 ch)
{
	u8 idx;
		
	if(ch < E_DOUT_CH_MAX_NUM)
	{
		idx = BSW_astrDigOutputDef[ch].u8Ch;
		return (SIU.GPDO[idx].B.PDO);
	}
}

/* **************************************************************************/
/* Function Name     : boolean Dio_vidToggleOutputCh(uint8 ch)       */
/* Brief Description : toggle the output channel value                      */
/* Input Parameters  : u8 ch -- channel number to be toggled         */
/* Output Parameters :                                                      */
/* Others            :                                                      */
/* **************************************************************************/
void Dio_vidToggleOutputCh(uint8 ch)
{
	u8 idx;
			
	if(ch < E_DOUT_CH_MAX_NUM)
	{
		idx = BSW_astrDigOutputDef[ch].u8Ch;
		SIU.GPDO[idx].B.PDO = !(SIU.GPDO[idx].B.PDO);
	}
}

void Dio_ReadAndChkOneDI(uint8 ch, uint8 mode)
{
	boolean Loc_bDioInputValue;
		
	if(ch < E_DIN_CH_MAX_NUM)
	{
		Loc_bDioInputValue = Dio_bReadInputCh(ch);
		
		if((boolean)(mode == Loc_bDioInputValue))
		{
			BSW_astrDigInputDef[ch].u8CurStep += BSW_astrDigInputDef[ch].u8IncStep;
			
			if (BSW_astrDigInputDef[ch].u8CurStep >= BSW_astrDigInputDef[ch].u8Threshold)
			{
				BSW_astrDigInputDef[ch].u8CurStep = BSW_astrDigInputDef[ch].u8Threshold;
				BSW_astrDigInputDef[ch].bVal      = TRUE;
			}
		}
		else
		{
			if (BSW_astrDigInputDef[ch].u8CurStep <= BSW_astrDigInputDef[ch].u8DecStep)
			{
				BSW_astrDigInputDef[ch].u8CurStep = 0;
				BSW_astrDigInputDef[ch].bVal      = FALSE;
			}
			else
			{
				BSW_astrDigInputDef[ch].u8CurStep -= BSW_astrDigInputDef[ch].u8DecStep;
			}
		}
	}
}

void Dio_ReadAndChkAllDI()
{
	uint8   Loc_u8Idx;
		
	for (Loc_u8Idx = 0; Loc_u8Idx < E_DIN_CH_MAX_NUM; Loc_u8Idx++)
	{
		Dio_ReadAndChkOneDI(Loc_u8Idx, BSW_astrDigInputDef[Loc_u8Idx].u8ChMode);
	}
}

/* *************************************************************************/
/* Function Name     : void Dio_vidInit(void)                              */
/* Brief Description : DIO initialization                                  */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Dio_vidInit(void)
{
	u8 i;
	
	for(i = 0; i < E_DOUT_CH_MAX_NUM; i++)
	{
	   Dio_vidSetOutputCh(BSW_astrDigOutputDef[i].u8Ch, BSW_astrDigOutputDef[i].u8DefaultVal);
	}
	
	//Dio_vidWriteOutputCh(E_DOUT_CAN_EN, STD_ON);
	//Dio_vidWriteOutputCh(E_DOUT_CAN_STB, STD_ON);
}

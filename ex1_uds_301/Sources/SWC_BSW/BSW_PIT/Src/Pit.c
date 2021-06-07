/*
 * Pit.c
 *
 *  Created on: Apr 15, 2020
 *      Author: hr
 */
#include "Pit.h"

PIT_INT_CALLBACK Pit_pfn_Callback[MAX_PIT_CHANNEL] = {(PIT_INT_CALLBACK)0};

void Pit_init(void)
{
	PitModuleEnable();
}

void Pit_SetTimerLoaderVal(u8 channel, u32 val)
{
	if(channel < MAX_PIT_CHANNEL)
	{
		PitSetTimerLoaderVal(PIT_CH_0, (u32)val);
	}
}

void Pit_EnableNotification(u8 channel)
{
	if(channel < MAX_PIT_CHANNEL)
	{
		PitClearTimerFlag(channel);
		PitEnableTimerInt(channel);
	}
}

void Pit_Start(u8 channel)
{
	if(channel < MAX_PIT_CHANNEL)
	{
		PitTimerEnable(channel);
	}
}

void Pit_Stop(u8 channel)
{
	if(channel < MAX_PIT_CHANNEL)
	{
		PitTimerDisable(channel);
	}
}

uint32 Pit_u32GetCurrentTimerCnt(u8 channel)
{
	if(channel < MAX_PIT_CHANNEL)
	{
		return PitGetCurrentTimerVal(channel);
	}
}

void Pit_SetIsrCallback(u8 channel, PIT_INT_CALLBACK pfn)
{
	if(channel < MAX_PIT_CHANNEL)
	{
		Pit_pfn_Callback[channel] = pfn;
	}
}

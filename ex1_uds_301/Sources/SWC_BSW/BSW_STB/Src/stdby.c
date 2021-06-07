/*
 * stdby.c
 *
 *  Created on: Jun 30, 2020
 *      Author: hr
 */

#include "includes.h"
#include "stdby.h"
#include "Port_Def.h"

#define WKUP02 					(0x2u)			
#define CAN0_STB_PIN			PC10	
#define MCU_PWR_LOCK_PIN		PE12
#define FLY_BACK_EN_PIN			PE2
#define FLY_BACK_DIS_PIN		PE3

void STB_wakeupPinConfig()
{
	// Pin5  ->  PA2  ->  WKUP2
	WKUP.WISR.R   =                 (1 << WKUP02);
	WKUP.WRER.R   = WKUP.WRER.R   | (1 << WKUP02);
	WKUP.IRER.R   = WKUP.IRER.R   | (1 << WKUP02);
	WKUP.WIREER.R = WKUP.WIREER.R | (1 << WKUP02);	// �����ش���: 0 Disable; 1 Enable;
	//WKUP.WIFEER.R = WKUP.WIFEER.R | (1 << WKUP02);	// �½��ش���: 0 Disable; 1 Enable;
	WKUP.WIFER.R  = WKUP.WIFER.R  | (1 << WKUP02);
	
	//SIU.PCR[26].R = 0x0103; /* Input, weak pull-up, �½��� */
	SIU.PCR[26].R = 0x0100; /* Input, ������ */
	
	WKUP.WIPUER.R = 0x000FFFFF ^ (1 << WKUP02);
}

void STB_clockConfigInSTB()
{
	/* standbyģʽ��, �ر�SXOSC, SIRC */
	CGM.SXOSC_CTL.B.OSCON = 0x0;
	CGM.SIRC_CTL.B.SIRCON_STDBY = 0x0;
}

void STB_enterStandByMode()
{
	/* �رշ�����Դ  */
	while(SIU.GPDO[FLY_BACK_EN_PIN].B.PDO == 1)
	{
		SIU.GPDO[FLY_BACK_EN_PIN].B.PDO = 0;
	}
	
	while(SIU.GPDO[FLY_BACK_DIS_PIN].B.PDO == 0)
	{
		SIU.GPDO[FLY_BACK_DIS_PIN].B.PDO = 1;
	}
	
	/* �رյ�Դ �� */
	while(SIU.GPDO[MCU_PWR_LOCK_PIN].B.PDO == 1)
	{
		SIU.GPDO[MCU_PWR_LOCK_PIN].B.PDO = 0;
	}
	
	/* CAN�շ�оƬ�������ģʽ  */
	while(SIU.GPDO[CAN0_STB_PIN].B.PDO == 0)
	{
		SIU.GPDO[CAN0_STB_PIN].B.PDO = 1;
	}
	
	/* To Go in standby Mode */
	ME.MCTL.R = 0xD0005AF0;
	ME.MCTL.R = 0xD000A50F;
	/* !Comment: Wait for mode entry to complete */
	// while (ME.GS.B.S_MTRANS != FALSE)
	//   ;
	while(TRUE)
		;
}

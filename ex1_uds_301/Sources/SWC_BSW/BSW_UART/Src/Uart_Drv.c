/*
 * Uart_Drv.c
 *
 *  Created on: Jul 7, 2020
 *      Author: hr
 */
#include "includes.h"
#include "Uart_Drv.h"

bool UART_getDataTxCompletedFlag(u8 mod)
{
	if(mod < MAX_LINFlex_MOD)
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				return LINFLEX_0.UARTSR.B.DTF;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				return LINFLEX_1.UARTSR.B.DTF;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				return LINFLEX_2.UARTSR.B.DTF;
			}
			break;
			
			default:
			break;
		}
	}
}

void UART_clearDataTxCompletedFlag(u8 mod)
{
	if(mod < MAX_LINFlex_MOD)
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				LINFLEX_0.UARTSR.B.DTF = 0x1;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				LINFLEX_1.UARTSR.B.DTF = 0x1;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				LINFLEX_2.UARTSR.B.DTF = 0x1;
			}
			break;
			
			default:
			break;
		}
	}
}

void UART_sendDataToTxBuf0(u8 mod, u8 data)
{
	if(mod < MAX_LINFlex_MOD)
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				LINFLEX_0.BDRL.B.DATA0 = data;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				LINFLEX_1.BDRL.B.DATA0 = data;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				LINFLEX_2.BDRL.B.DATA0 = data;
			}
			break;
			
			default:
			break;
		}
	}
}

void UART_sendDataToTxBuf1(u8 mod, u8 data)
{
	if(mod < MAX_LINFlex_MOD)
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				LINFLEX_0.BDRL.B.DATA1 = data;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				LINFLEX_1.BDRL.B.DATA1= data;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				LINFLEX_2.BDRL.B.DATA1 = data;
			}
			break;
			
			default:
			break;
		}
	}
}

void UART_sendDataToTxBuf2(u8 mod, u8 data)
{
	if(mod < MAX_LINFlex_MOD)
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				LINFLEX_0.BDRL.B.DATA2 = data;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				LINFLEX_1.BDRL.B.DATA2 = data;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				LINFLEX_2.BDRL.B.DATA2 = data;
			}
			break;
			
			default:
			break;
		}
	}
}

void UART_sendDataToTxBuf3(u8 mod, u8 data)
{
	if(mod < MAX_LINFlex_MOD)
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				LINFLEX_0.BDRL.B.DATA3 = data;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				LINFLEX_1.BDRL.B.DATA3 = data;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				LINFLEX_2.BDRL.B.DATA3 = data;
			}
			break;
			
			default:
			break;
		}
	}
}

void UART_setTxDataLength(u8 mod, u8 len)
{
	if((mod < MAX_LINFlex_MOD) &&
	   (len < UART_MAX_DATA_LEN))
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				LINFLEX_0.UARTCR.B.TDFL = len;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				LINFLEX_1.UARTCR.B.TDFL = len;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				LINFLEX_2.UARTCR.B.TDFL = len;
			}
			break;
			
			default:
			break;
		}
	}
}

u8 UART_getTxDataLength(u8 mod)
{
	if(mod < MAX_LINFlex_MOD)
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				return (u8)LINFLEX_0.UARTCR.B.TDFL;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				return (u8)LINFLEX_1.UARTCR.B.TDFL;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				return (u8)LINFLEX_2.UARTCR.B.TDFL;
			}
			break;
			
			default:
			{
				// 发送缓存大小为 0-3, 所以返回值不可能为4
				return UART_MAX_DATA_LEN;
			}
			break;
		}
	}
}

void UART_setRxDataLength(u8 mod, u8 len)
{
	if((mod < MAX_LINFlex_MOD) &&
	   (len < UART_MAX_DATA_LEN))
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				LINFLEX_0.UARTCR.B.RDFL = len;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				LINFLEX_1.UARTCR.B.RDFL = len;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				LINFLEX_2.UARTCR.B.RDFL = len;
			}
			break;
			
			default:
			break;
		}
	}
}

u8 UART_getRxDataLength(u8 mod)
{
	if(mod < MAX_LINFlex_MOD)
	{
		switch(mod)
		{
			case LINFlex_MOD_0:
			{
				return (u8)LINFLEX_0.UARTCR.B.RDFL;
			}
			break;
			
			case LINFlex_MOD_1:
			{
				return (u8)LINFLEX_1.UARTCR.B.RDFL;
			}
			break;
			
			case LINFlex_MOD_2:
			{
				return (u8)LINFLEX_2.UARTCR.B.RDFL;
			}
			break;
			
			default:
			{
				// 接收缓存大小为 0-3, 所以返回值不可能为4
				return UART_MAX_DATA_LEN;
			}
			break;
		}
	}
}


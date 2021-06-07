/*
 * Uart_Trans.c
 *
 *  Created on: Dec 23, 2020
 *      Author: zzc
 */
#include "Uart_Trans.h"
#include "CRC16.h"

STRU_UART_TRANS_FRAME tx0Buf;
STRU_UART_TRANS_FRAME tx2Buf;
STRU_UART_TRANS_FRAME rx0Buf;
STRU_UART_TRANS_FRAME rx2Buf;

boolean Uart_Trans_SetData(u8 mod, STRU_UART_DATA_FRAME* p)
{
	boolean ret = FALSE;
	STRU_UART_TRANS_FRAME* d;
	
	if(0 == mod)
	{
		d = &tx0Buf;
	}
	else if(2 == mod)
	{
		d = &tx2Buf;
	}
	
	d->UDF.Byte[0] = UART_TRANS_FRAME_START;
	d->UDF.Byte[3] = UART_TRANS_FRAME_END1;
	d->UDF.Byte[4] = UART_TRANS_FRAME_END2;
	
	if(p != NULL)
	{
		d->UDF.Byte[1] = p->UDF.Byte[1];
		d->UDF.Byte[2] = p->UDF.Byte[2];
		
		//d->UDF.Byte[0] |= (u8)(((p->UDF.Byte[0] + p->UDF.Byte[1]) & 0x70) << 0);
		//d->UDF.Byte[3] |= (u8)(((p->UDF.Byte[0] + p->UDF.Byte[1]) & 0x07) << 4);
		
		ret = TRUE;
	}

	return ret;
}

void Uart_Trans_ClearRxBuf(u8 mod)
{
	u8 i;
	STRU_UART_TRANS_FRAME* d;
	
	if(0 == mod)
	{
		d = &rx0Buf;
	}
	else if(2 == mod)
	{
		d = &rx2Buf;
	}
	
	for(i = 0; i < UART_TRANS_BUF_LEN; i++)
	{
		d->UDF.Byte[i] = 0x00u;
	}
}

boolean Uart_Trans_GetData(u8 mod, STRU_UART_DATA_FRAME* p)
{
	boolean ret = FALSE;
	STRU_UART_TRANS_FRAME* d;
	
	if(0 == mod)
	{
		d = &rx0Buf;
	}
	else if(2 == mod)
	{
		d = &rx2Buf;
	}
	
	if(((d->UDF.Byte[0] & 0x8F) == UART_TRANS_FRAME_START) )//&&
	   //((d->UDF.Byte[3] & 0X8F) == UART_TRANS_FRAME_END))
	{
		if(((d->UDF.Byte[0] & 0x70) == (u8)(((d->UDF.Byte[1] + d->UDF.Byte[2]) & 0x70) << 0)) &&
		   ((d->UDF.Byte[3] & 0x70) == (u8)(((d->UDF.Byte[1] + d->UDF.Byte[2]) & 0x07) << 4)))
		{
			p->UDF.Byte[0] = d->UDF.Byte[1];
			p->UDF.Byte[1] = d->UDF.Byte[2];
			
			ret = TRUE;
		}
	}
	
	return ret;
}



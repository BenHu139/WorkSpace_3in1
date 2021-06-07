/*
 * Uart_Trans.h
 *
 *  Created on: Dec 23, 2020
 *      Author: zzc
 */

#ifndef UART_TRANS_H_
#define UART_TRANS_H_

#include "includes.h"
#include "Uart_Data.h"

#define UART_TRANS_FRAME_START		(0xEEu )
#define UART_TRANS_FRAME_END1		(0xAAu)
#define UART_TRANS_FRAME_END2		(0x55u)

#define UART_TRANS_BUF_LEN  		(5u)

typedef struct
{
	union 
	{
		vuint8_t Byte[5];
		struct {
			vuint32_t FrameStart:8;
			vuint32_t DataHigh:8;
			vuint32_t DataLow:8;
			vuint32_t FrameEnd1:8;
			vuint32_t FrameEnd2:8;
		} Bit;
	} UDF;
} STRU_UART_TRANS_FRAME;

extern STRU_UART_TRANS_FRAME tx0Buf;
extern STRU_UART_TRANS_FRAME tx2Buf;
extern STRU_UART_TRANS_FRAME rx0Buf;
extern STRU_UART_TRANS_FRAME rx2Buf;

extern boolean Uart_Trans_SetData(u8 mod, STRU_UART_DATA_FRAME* p);
extern void Uart_Trans_ClearRxBuf(u8 mod);
extern boolean Uart_Trans_GetData(u8 mod, STRU_UART_DATA_FRAME* p);

#endif /* UART_TRANS_H_ */

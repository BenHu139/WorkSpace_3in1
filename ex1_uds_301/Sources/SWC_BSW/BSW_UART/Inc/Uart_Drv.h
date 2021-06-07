/*
 * Uart_Drv.h
 *
 *  Created on: Jul 6, 2020
 *      Author: hr
 */

#ifndef UART_DRV_H_
#define UART_DRV_H_

#include "includes.h"

typedef enum
{
	LINFlex_MOD_0 =0,
	LINFlex_MOD_1,
	LINFlex_MOD_2,
	
	MAX_LINFlex_MOD
}LINFlex_tenuModules;

typedef enum
{
	UART_DATA_LEN_1 = 0,
	UART_DATA_LEN_2,
	UART_DATA_LEN_3,
	UART_DATA_LEN_4,
	
	UART_MAX_DATA_LEN
}UART_tenuDataLength;


#define LINFlexReqInit(mod)					(LINFLEX_##mod##.LINCR1.B.INIT = 1)
#define LINFlexExitInit(mod)				(LINFLEX_##mod##.LINCR1.B.INIT = 0)

#define LINFlexReqSleep(mod)				(LINFLEX_##mod##.LINCR1.B.SLEEP = 1)
#define LINFlexExitSleep(mod)				(LINFLEX_##mod##.LINCR1.B.SLEEP = 0)

#define LINFlexOverRunRBLM(mod)				(LINFLEX_##mod##.LINCR1.B.RBLM = 0)
#define LINFlexDiscardRBLM(mod)				(LINFLEX_##mod##.LINCR1.B.RBLM = 1)

#define LINFlexUartEnaTX(mod)				(LINFLEX_##mod##.UARTCR.B.TXEN = 1)
#define LINFlexUartDisTX(mod)				(LINFLEX_##mod##.UARTCR.B.TXEN = 0)

#define LINFlexUartEnaRX(mod)				(LINFLEX_##mod##.UARTCR.B.RXEN = 1)
#define LINFlexUartDisRX(mod)				(LINFLEX_##mod##.UARTCR.B.RXEN = 0)

#define LINFlexUartSetParityOdd(mod)		(LINFLEX_##mod##.UARTCR.B.OP = 1)
#define LINFlexUartSetParityEven(mod)		(LINFLEX_##mod##.UARTCR.B.OP = 0)

#define LINFlexUartEnaPCE(mod)				(LINFLEX_##mod##.UARTCR.B.PCE = 1)
#define LINFlexUartDisPCE(mod)				(LINFLEX_##mod##.UARTCR.B.PCE = 0)

#define LINFlexUartSetWordLen7(mod)			(LINFLEX_##mod##.UARTCR.B.WL = 0)
#define LINFlexUartSetWordLen8(mod)			(LINFLEX_##mod##.UARTCR.B.WL = 1)

#define LINFlexUARTMode(mod)         		(LINFLEX_##mod##.UARTCR.B.UART = 1)
#define LINFlexLINMode(mod)         		(LINFLEX_##mod##.UARTCR.B.UART = 0)

/* Idle on bit error */
#define LINFlexResetOnIOBE(mod)     		(LINFLEX_##mod##.LINCR2.B.IOBE = 1)
#define LINFlexNotResetOnIOBE(mod)  		(LINFLEX_##mod##.LINCR2.B.IOBE = 0)

/* Idle on identifier parity error */
#define LINFlexResetOnIOPE(mod)     		(LINFLEX_##mod##.LINCR2.B.IOPE = 1)
#define LINFlexNotResetOnIOPE(mod)  		(LINFLEX_##mod##.LINCR2.B.IOPE = 0)

/* Idle on timeout event */
#define LINFlexResetOnIOT(mod)     			(LINFLEX_##mod##.LINTCSR.B.IOT = 1)
#define LINFlexNotResetOnIOT(mod)  			(LINFLEX_##mod##.LINTCSR.B.IOT = 0)

/* 波特率设置 */
#define LINFlexSetBaudRateIBR(mod, value)	(LINFLEX_##mod##.LINIBRR.R = value)
#define LINFlexSetBaudRateFBR(mod, value)	(LINFLEX_##mod##.LINFBRR.R = value)

/* 中断使能 */
#define LINFlexEnaDataTxInterrupt(mod)		(LINFLEX_##mod##.LINIER.B.DTIE = 1)
#define LINFlexDisDataTxInterrupt(mod)		(LINFLEX_##mod##.LINIER.B.DTIE = 0)	//default

#define LINFlexEnaDataRxInterrupt(mod)		(LINFLEX_##mod##.LINIER.B.DRIE = 1)
#define LINFlexDisDataRxInterrupt(mod)		(LINFLEX_##mod##.LINIER.B.DRIE = 0) //default


/* LINFlex identifier setting */
/* IFCR */

/* IFMR */

/* IFER */
bool UART_getDataTxCompletedFlag(u8 mod);
void UART_clearDataTxCompletedFlag(u8 mod);
void UART_sendDataToTxBuf0(u8 mod, u8 data);
void UART_sendDataToTxBuf1(u8 mod, u8 data);
void UART_sendDataToTxBuf2(u8 mod, u8 data);
void UART_sendDataToTxBuf3(u8 mod, u8 data);

void UART_setTxDataLength(u8 mod, u8 len);
u8 UART_getTxDataLength(u8 mod);
void UART_setRxDataLength(u8 mod, u8 len);
u8 UART_getRxDataLength(u8 mod);

#endif /* UART_DRV_H_ */

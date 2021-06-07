/*
 * Uart_Data.h
 *
 *  Created on: Jul 13, 2020
 *      Author: hr
 */

#ifndef UART_DATA_H_
#define UART_DATA_H_

#define UART_FIFO_BUF_MAX_SIZE 16U

typedef struct
{
	union 
	{
		vuint8_t Byte[5];
		struct {
			vuint32_t :8;
			
			vuint32_t HDB3:3; //bit13-15 
			vuint32_t DID:4;  //bit9-12
			vuint32_t HID:1;  //bit8
			
			vuint32_t LDB7:7;
			vuint32_t LID:1;
			
			vuint32_t :16;
		} Bit;
	} UDF;
} STRU_UART_DATA_FRAME,*P_STRU_UART_DATA_FRAME;

typedef struct
{
	int32_t head;
	int32_t tail;
	STRU_UART_DATA_FRAME buf[UART_FIFO_BUF_MAX_SIZE];
} STRU_UART_FIFO;

void BSW_UART_FIFO_init(void);
void BSW_UART_FIFO_ClearMsg(u8 mod);
bool BSW_UART_FIFO_GetRxMsg(u8 mod, STRU_UART_DATA_FRAME *msg);
bool BSW_UART_FIFO_PutRxMsg(u8 mod, STRU_UART_DATA_FRAME *msg);

#endif /* UART_DATA_H_ */

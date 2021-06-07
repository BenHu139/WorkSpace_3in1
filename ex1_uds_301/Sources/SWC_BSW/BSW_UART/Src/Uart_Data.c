/*
 * Uart_Data.c
 *
 *  Created on: Jul 13, 2020
 *      Author: hr
 */
#include "includes.h"
#include "Uart_Drv.h"
#include "Uart_Data.h"

static STRU_UART_FIFO s_uart_rx_fifo[MAX_LINFlex_MOD];

void BSW_UART_FIFO_init()
{
	u8 m;
	
	for(m = 0;m < MAX_LINFlex_MOD; m++)
	{
		s_uart_rx_fifo[m].head = 0x0;
		s_uart_rx_fifo[m].tail = 0x0;
		BSW_UART_FIFO_ClearMsg(m);
	}
}

void BSW_UART_FIFO_ClearMsg(u8 mod)
{
	u8 i;
	
	if(mod < MAX_LINFlex_MOD)
	{
		for(i = 0;i < UART_FIFO_BUF_MAX_SIZE; i++)
		{
			s_uart_rx_fifo[mod].buf[i].UDF.Byte[0] = 0x0;
			s_uart_rx_fifo[mod].buf[i].UDF.Byte[1] = 0x0;
		}
	}
}

bool BSW_UART_FIFO_GetRxMsg(u8 mod, STRU_UART_DATA_FRAME *msg)
{
	STRU_UART_DATA_FRAME *fifo_buf = DEF_NULL;
    STRU_UART_FIFO *fifo_handle = DEF_NULL;
    int32_t temp_r = 0;
    bool ret = FALSE;

    if (mod < MAX_LINFlex_MOD)
    {
        fifo_handle = &s_uart_rx_fifo[mod];

        temp_r = fifo_handle->head; /*先进先出，先读得是头*/

        if (temp_r != fifo_handle->tail) /*先进先出，头尾相等，就是无报文需处理*/
        {
            fifo_buf = &(fifo_handle->buf[temp_r]);
            if (fifo_buf != DEF_NULL)
            {
            	msg->UDF.Byte[0] = fifo_buf->UDF.Byte[0];
            	msg->UDF.Byte[1] = fifo_buf->UDF.Byte[1];

                temp_r++;
                if (temp_r >= UART_FIFO_BUF_MAX_SIZE)
                {
                    temp_r = 0;
                }

                fifo_handle->head = temp_r;

                ret = TRUE;
            }
            else
            {
                ret = FALSE;
            }
        }
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

bool BSW_UART_FIFO_PutRxMsg(u8 mod, STRU_UART_DATA_FRAME *msg)
{
	STRU_UART_DATA_FRAME *fifo_buf = DEF_NULL;
	STRU_UART_FIFO *fifo_handle = DEF_NULL;
    int32_t temp_w = 0;
    bool ret = FALSE;

    if (mod < MAX_LINFlex_MOD)
    {
        fifo_handle = &s_uart_rx_fifo[mod];

        temp_w = fifo_handle->tail; /*先进先出，后进来的是尾*/
        temp_w++;
        if (temp_w >= UART_FIFO_BUF_MAX_SIZE)
        {
            temp_w = 0;
        }

        if (temp_w != fifo_handle->head) /*写指针和读指针相等，舍弃报文不写*/
        {
            fifo_buf = &(fifo_handle->buf[fifo_handle->tail]);
            if (DEF_NULL != fifo_buf)
            {
            	fifo_buf->UDF.Byte[0] = msg->UDF.Byte[0];
            	fifo_buf->UDF.Byte[1] = msg->UDF.Byte[1];
            	
                fifo_handle->tail = temp_w;

                ret = TRUE;
            }
            else
            {
                ret = FALSE;
            }
        }
        else
        {
            ret = FALSE;
        }
    }
    else
    {
        ret = FALSE;
    }
    
    return ret;
}

/*
 * @Author: your name
 * @Date: 2020-04-03 10:31:41
 * @LastEditTime: 2020-04-03 14:32:40
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \PLF5604\Sources\FWS\CAN_STACK\CAN_STACK.h
 */
/**
 * @file CAN_STACK.h CAN栈模块头文件
 * @ingroup FWS_FWS_CAN_STACK
 */

#ifndef CAN_STACK_H_
#define CAN_STACK_H_


#include "includes.h"

#define CAN_FIFO_BUF_MAX_SIZE 50U


#define INTERNAL_CAN (CAN_CHANNEL_CAN0)
#define EXTERNAL_CAN (CAN_CHANNEL_CAN1)

typedef struct
{
    uint32_t id;
    u8 ide;				// 0 标准帧; 1 扩展帧
    u8 rtr;				// 0 数据帧; 1 远程帧
    u8 len;
    uint8_t buf[8];
} STRU_CAN_MESSAGE;

typedef struct
{
    int32_t head;
    int32_t tail;
    STRU_CAN_MESSAGE buffer[CAN_FIFO_BUF_MAX_SIZE];
} S_CAN_FIFO;

typedef enum
{
    CAN_BUSY_SELF = 0u,
    CAN_IDLE
} CAN_TX_STATE;

bool FWS_CAN_STACK_GetRxMsg(u8 chn, STRU_CAN_MESSAGE *msg);
bool FWS_CAN_STACK_PutRxMsg(u8 chn, STRU_CAN_MESSAGE *msg);
void FWS_CAN_STACK_SendMessage(u8 chn, STRU_CAN_MESSAGE *msg);
void FWS_CAN_STACK_SetGlobalComEnFlag(u8 flag);
void FWS_CAN_STACK_ClearMsg(u8 chn);
void FWS_CAN_STACK_Init(void);
void FWS_CAN_STACK_CallBackTx(u8 chn);
bool FWS_CAN_STACK_InitSel(u8 stack_start, u8 stack_end);
#endif /* CAN_STACK_H_ */

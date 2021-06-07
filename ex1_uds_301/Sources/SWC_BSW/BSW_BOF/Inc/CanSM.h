#ifndef __CANSM_H_
#define __CANSM_H_

#include "includes.h"

#include "CanDriver.h"
#include "CanSM.h"
#include "CanSM_Cfg.h"

/* type boolean  */

#define BOF_FALSE 0
#define BOF_TRUE 1

/* CAN id 定义 */
#define CAN0ID 0
#define CAN1ID 1
#define CAN2ID 2

#define CANSM_BOR_TXOFF_L 0
#define CANSM_BOR_TXOFF_F 1

/* ERORR CODE */
#define IDERORR 3

#define CanSM_E_OK 1

/* 传输确认状态 */
#define CAN_TX_OK 0
#define CAN_TX_ERR 1

/* CAN 通信状态 */
typedef enum
{
	/* 通信非正常 */
	CANSM_BSM_S_UFULLCOM,
	/* 通信正常 */
	CANSM_BSM_S_FULLCOM
} CanSM_ComStatuType;

/* CAN bus off 状态机状态 */
typedef enum
{
	CANSM_BR_CHECK,
	CANSM_BR_NO_BUS_OFF,
	CANSM_BR_RESTART_CC,
	CANSM_BR_RESTART_WAIT,
	CANSM_BR_TXOFF
} CanSM_BusOffStatusType;

/* CanSM 初始化状态 */
typedef enum
{
	/* CAN状态管理未被初始化 */
	CANSM_STATUS_UNINIT,
	/* CAN状态管理已被初始化 */
	CANSM_STATUS_INIT
} CanSM_InitStatusType;

/* 网络工作状态  */
typedef struct
{
	/* 时间计数器  */
	u16 timer;
	/* 记录busoff发生次数 */
	u8 count;
	/* 标示当前是否发生了busoff事件 */
	u8 busoffevent;
	/* busoff当前状态 */
	CanSM_BusOffStatusType BusOffCurStatus;
} CanSM_NetWorkType;

/* 网络配置结构体 */
typedef struct
{
	/* 快速恢复时间 */
	u16 CanSMBorTimeL1;
	/* 慢速恢复时间 */
	u16 CanSMBorTimeL2;
	/* 从快速恢复进入到慢速busoff计数界限值 */
	u8 CanSMBorCounterL1ToL2;
	/* 进行产品报错的busoff计数界限值 */
	u8 CanSMBorCounterErr;
	/* Can硬件复位超时 */
	u16 RestartTimeOut;
	/* pdu tx ensured time */
	u16 CanSMBorTimeTxEnsured;
} CanSM_NetConfigType;

/* 报警与通信状态结构体 */
typedef struct
{
	/* Can 通信状态 */
	CanSM_ComStatuType CanComStatus;
	/* CanSM 报警请求 */
	u8 BusOffWarningReq;
} CanSM_WarAndComstType;

/* CanSM配置结构体 */
typedef struct
{
	/* CanSM 初始化状态 */
	CanSM_InitStatusType CanSM_InitStatus;
	/* CanSM busoff相关参数配置 */
	CanSM_NetConfigType *pCanSM_NetConfig;
} CanSM_ConfigType;

/* 运行时结构体 */
typedef struct
{
	CanSM_NetWorkType CanSM_NetWork;
	CanSM_ConfigType CanSM_Config;
} CanSM_RunTimeType;

extern CanSM_NetWorkType g_CanNetWorks[CANSM_CTRL_NUM];
extern CanSM_ComStatuType g_CanComStatus;
extern CanSM_ConfigType CanSM_Config;

extern void CanSM_Scheduler(void);
extern void CanSM_Init(void);

extern u8 CanSM_GetComState(u8 ControllerId, CanSM_ComStatuType *pComState);
extern u8 CanSM_GetWarnState(u8 ControllerId, u8 *pWarnState);

#endif

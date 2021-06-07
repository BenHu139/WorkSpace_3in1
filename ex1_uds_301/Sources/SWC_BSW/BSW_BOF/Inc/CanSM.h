#ifndef __CANSM_H_
#define __CANSM_H_

#include "includes.h"

#include "CanDriver.h"
#include "CanSM.h"
#include "CanSM_Cfg.h"

/* type boolean  */

#define BOF_FALSE 0
#define BOF_TRUE 1

/* CAN id ���� */
#define CAN0ID 0
#define CAN1ID 1
#define CAN2ID 2

#define CANSM_BOR_TXOFF_L 0
#define CANSM_BOR_TXOFF_F 1

/* ERORR CODE */
#define IDERORR 3

#define CanSM_E_OK 1

/* ����ȷ��״̬ */
#define CAN_TX_OK 0
#define CAN_TX_ERR 1

/* CAN ͨ��״̬ */
typedef enum
{
	/* ͨ�ŷ����� */
	CANSM_BSM_S_UFULLCOM,
	/* ͨ������ */
	CANSM_BSM_S_FULLCOM
} CanSM_ComStatuType;

/* CAN bus off ״̬��״̬ */
typedef enum
{
	CANSM_BR_CHECK,
	CANSM_BR_NO_BUS_OFF,
	CANSM_BR_RESTART_CC,
	CANSM_BR_RESTART_WAIT,
	CANSM_BR_TXOFF
} CanSM_BusOffStatusType;

/* CanSM ��ʼ��״̬ */
typedef enum
{
	/* CAN״̬����δ����ʼ�� */
	CANSM_STATUS_UNINIT,
	/* CAN״̬�����ѱ���ʼ�� */
	CANSM_STATUS_INIT
} CanSM_InitStatusType;

/* ���繤��״̬  */
typedef struct
{
	/* ʱ�������  */
	u16 timer;
	/* ��¼busoff�������� */
	u8 count;
	/* ��ʾ��ǰ�Ƿ�����busoff�¼� */
	u8 busoffevent;
	/* busoff��ǰ״̬ */
	CanSM_BusOffStatusType BusOffCurStatus;
} CanSM_NetWorkType;

/* �������ýṹ�� */
typedef struct
{
	/* ���ٻָ�ʱ�� */
	u16 CanSMBorTimeL1;
	/* ���ٻָ�ʱ�� */
	u16 CanSMBorTimeL2;
	/* �ӿ��ٻָ����뵽����busoff��������ֵ */
	u8 CanSMBorCounterL1ToL2;
	/* ���в�Ʒ�����busoff��������ֵ */
	u8 CanSMBorCounterErr;
	/* CanӲ����λ��ʱ */
	u16 RestartTimeOut;
	/* pdu tx ensured time */
	u16 CanSMBorTimeTxEnsured;
} CanSM_NetConfigType;

/* ������ͨ��״̬�ṹ�� */
typedef struct
{
	/* Can ͨ��״̬ */
	CanSM_ComStatuType CanComStatus;
	/* CanSM �������� */
	u8 BusOffWarningReq;
} CanSM_WarAndComstType;

/* CanSM���ýṹ�� */
typedef struct
{
	/* CanSM ��ʼ��״̬ */
	CanSM_InitStatusType CanSM_InitStatus;
	/* CanSM busoff��ز������� */
	CanSM_NetConfigType *pCanSM_NetConfig;
} CanSM_ConfigType;

/* ����ʱ�ṹ�� */
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

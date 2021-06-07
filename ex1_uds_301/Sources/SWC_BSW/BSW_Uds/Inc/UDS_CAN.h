/**
 * @file CAN.h FLEXCAN模块头文件
 * @ingroup HAL_MCU_CAN
 */
#if 1

#ifndef __UDS_CAN_H__
#define __UDS_CAN_H__

#include "typedefs.h"
#include "Can_Type.h"
#include "Dcm_Cfg.h"
//#include "ComStack_Types.h"
//typedef u16 PduIdType;
//typedef u32 Can_IdType;
//typedef u32 Can_HwHandleType;
#define UDS_SEND_BUF 16u
#define UDS_REV_BUF  32u
#define UDSCAN_TIMEOUT  (10000UL /DCM_TASK_TIME )

#if 0
typedef struct      
{
	PduIdType swPduHandle;/*ID句柄*/
	u8 length;
	Can_IdType id;/*报文ID*/
    u8 *sdu;/*发送数据组*/
}Can_PduType;


typedef enum
{
	CAN_OK = 0U,
	CAN_NOT_OK,
	CAN_BUSY
}Can_ReturnType;

#endif


extern Can_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo);
extern void Can_InitActiveChn(void);
extern u8 Can_GetActiveChn(void);
extern void Can_SetActiveChn(u8 chn);
extern void Can_RealseActiveChn(void);
extern void Can_RefreshActiveTimeOut(u32 Time);
extern void DecreaseActiveTimeOut(void);

#endif /* __CAN__ */
#endif

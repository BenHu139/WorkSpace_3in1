

#ifndef CAN_DATA_TYPES_H
#define CAN_DATA_TYPES_H
/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Std_Types.h"

/* ***************************************************************************/
/*                                 MACROS                                    */
/* ***************************************************************************/
#define CAN_TX ((uint8)0x01)
#define CAN_RX ((uint8)0x00)

#define CAN_REMOTE_FRAME ((uint8)0x01)
#define CAN_DATA_FRAME ((uint8)0x00)

#define CAN_ID_STANDARD ((uint8)0x00)
#define CAN_ID_EXTENDED ((uint8)0x01)

#define CAN_ID_DATA ((uint8)0x00)
#define CAN_ID_REMOTE ((uint8)0x01)

#define CAN_MB_TYPE_TX ((uint8)0x08)
#define CAN_MB_TYPE_RX ((uint8)0x04)

#define CAN_MB_RX_MASK ((uint32)0x1FFFFFFF)

#define CAN_MB_FLAG_CLEAR ((uint32)0xFFFFFFFF)
#define CAN_MB_IRQ_DISABLE ((uint32)0x00000000)

#define CAN_MB_RX_FULL ((uint32)0x00000001)
#define CAN_MB_RX_EMPTY ((uint8)0x04)

#define CAN_MB_TX_REQ ((uint8)0x0C)
#define CAN_MB_TX_FINISH ((uint8)0x08)

#define CAN_BASE_TASK ((uint8)10)

/* ***************************************************************************/
/*                                 TYPES                                     */
/* ***************************************************************************/

/* !Comment: CAN mailbox configuration type               */
typedef struct
{
   uint8   u8BufID;				// Message Buffer ID
   uint32   FrameID;			// Can Frame ID
   uint8   u8FrameDlc;			// 要发送的数据长度
   uint8   u8FrameTxRx;			// Tx or Rx
   uint8   u8FrameType;			// 标准帧 or 扩展帧
   uint8   u8DataType;			// 数据帧 or 远程帧
   uint16   u8FramePeriod;		// 发送周期计数
   uint8   u8BufIntEna;			// Message Buffer Interrupt Enable Flag
}Can_tstrMbType;

typedef struct
{
	u8  u8RxCode;                /* Received message buffer code */
	u32 u32RxID;                 /* Received message ID */
	u8  u8RxLength;              /* Received message number of data bytes */
	u8  *pRxData;                /* Received message data pointer */
	u16 u16RxTimestamp;          /* Received message time */
}Can_tstrRxMsgType;

/******************************************************************************/
/*                         VARIABLE  DEFINITION                               */
/******************************************************************************/

/*****************************************************************************/
/*                                 PROTOTYPES                                */
/*****************************************************************************/



#endif

/*
 * @Author: your name
 * @Date: 2020-04-03 10:31:42
 * @LastEditTime: 2020-04-03 14:35:52
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \PLF5604\Sources\HAL\MCU\CAN\CAN.h
 */
/**
 * @file CAN.h FLEXCAN模块头文件
 * @ingroup HAL_MCU_CAN
 */

#ifndef __CAN_H__
#define __CAN_H__

#include "includes.h"

/* CAN_0 INTERNAL_CAN */
#define LCM1_CAN_ID			0x18ffc822u
#define LCM2_CAN_ID			0x18ffc622u
#define BMS_CAN_ID		    0x1806E5F4u
#define PWRCTRL_CAN_ID		0x81u		
#define DEBUG_CAN_ID		0x200u
#define TEST_DIO_CAN_ID		0x380u
#define TEST_ADC1_CAN_ID	0x381u
#define TEST_ADC2_CAN_ID	0x382u
#define TEST_ADC3_CAN_ID	0x383u
#define TEST_ADC4_CAN_ID	0x384u
#define BMS_VA_CAN_ID		0x284u
#define	BMS_HEATST_CAN_ID	0x295u
#define	VCU_VEHST_CAN_ID	0x155u
#define	DCDC_ENST_CAN_ID	0x4C7u


#define LCM1_MB_NUM			0u
#define LCM2_MB_NUM			1u
#define BMS_MB_NUM		    2u
#define PWRCTRL_MB_NUM		3u		
#define DEBUG_MB_NUM		4u
#define TEST_DIO_MB_NUM		5u
#define TEST_ADC1_MB_NUM	6u
#define TEST_ADC2_MB_NUM	7u
#define TEST_ADC3_MB_NUM	8u
#define TEST_ADC4_MB_NUM	9u
#define BMS_VA_MB_NUM		11u
#define	BMS_HEATST_MB_NUM	16u
#define	VCU_VEHST_MB_NUM	17u
#define	DCDC_ENST_MB_NUM	18u

/* CAN_1 EXTERNAL_CAN */

typedef enum CAN_Channel
{
	CAN_CHANNEL_CAN0 = 0U,
	CAN_CHANNEL_CAN1,

	CAN_FIFO_MAX_CHN
}CAN_CHANNEL;

enum CAN_Baud_Type /*波特率号，常用250kb*/
{
   CAN_BOUD_RATE_250KB = 0U,
   CAN_BOUD_RATE_500KB,
   CAN_BOUD_RATE_1M
};

typedef struct /*CAN初始化配置结构体*/
{
   enum CAN_Channel CAN_CHANNEL_ID;
   enum CAN_Baud_Type CAN_Baund_ID;
   uint8_t Synch_Jump_Width;
   /******************
    *1个Tq时钟周期：0*
    *2个Tq时钟周期：1*
    *3个Tq时钟周期：2*
    *4个Tq时钟周期：3* 
	常用默认：0
  *******************/
   uint8_t CAN_Clock_Select; /*CAN时钟源选择 0：晶振时钟/1：总线时钟*/
   uint32_t Global_MASK;     /*全局掩码*/
   uint32_t Buf14_MASK;      /*14邮箱掩码*/
   uint32_t Buf15_MASK;      /*15邮箱掩码*/
   uint8_t ID_Accept_Mode;
   /***********************
    *A类型 1个全ID：             0*
    *B类型 2个标准ID     1*
    *C类型 4个局部8位ID  2*
    *D类型 拒绝所有格式： 3* 
  ***********************/
   uint8_t USE_NUM_MB;           /*最大可用的邮箱个数=MAX_NUM_MB+1；最大可用的个数为64*/
   uint8_t SELF_Receive_Disable; /*是否使能自接收：0：自接收   1：不自接收*/
} CAN_ConfigType;

typedef struct /*CAN邮箱配置结构体*/
{
   bool RX_FLAG;   /*是否设置为接收邮箱 0： 发送  1：接收*/
   uint32_t CANID; /*接收的报文ID*/
   uint8_t IDE;    /*扩展帧标志位 1：扩展帧/0：标准帧*/
   uint8_t MB_NUM; /*使用报文缓存区的编号*/
   uint32_t MASK;  /*私有掩码*/
   uint8_t IRQ;    /*是否中断*/
} MB_ConfigType;

typedef struct
{
   uint32_t CANID;  /*报文ID*/
   uint8_t RTR;     /*远程帧标志位 1：远程帧/0：数据帧*/
   uint8_t IDE;     /*扩展帧标志位 1：扩展帧/0：标准帧*/
   uint8_t DATA[8]; /*发送数据组*/
   uint32_t LENGTH; /*数据长度*/
   uint8_t MB_NUM;  /*使用报文缓存区的编号*/
} Can_PduType_SELF;

extern void Can_vidInit(void);
extern uint8_t Can_SetBaudrate(enum CAN_Channel controller, enum CAN_Baud_Type BaudRateConfigID);
extern void Can_Init(CAN_ConfigType *Config);
extern uint8_t Can_Write_Self(enum CAN_Channel controller, Can_PduType_SELF *PduInfo);
extern void Can_SetBuffer(enum CAN_Channel controller, MB_ConfigType *Config);
extern uint8_t Can_Read(enum CAN_Channel controller, Can_PduType_SELF *PduInfo);
extern void Can_Stop(void);

#endif /* __CAN__ */

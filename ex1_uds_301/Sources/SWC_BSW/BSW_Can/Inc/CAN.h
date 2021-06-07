/*
 * @Author: your name
 * @Date: 2020-04-03 10:31:42
 * @LastEditTime: 2020-04-03 14:35:52
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \PLF5604\Sources\HAL\MCU\CAN\CAN.h
 */
/**
 * @file CAN.h FLEXCANģ��ͷ�ļ�
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

enum CAN_Baud_Type /*�����ʺţ�����250kb*/
{
   CAN_BOUD_RATE_250KB = 0U,
   CAN_BOUD_RATE_500KB,
   CAN_BOUD_RATE_1M
};

typedef struct /*CAN��ʼ�����ýṹ��*/
{
   enum CAN_Channel CAN_CHANNEL_ID;
   enum CAN_Baud_Type CAN_Baund_ID;
   uint8_t Synch_Jump_Width;
   /******************
    *1��Tqʱ�����ڣ�0*
    *2��Tqʱ�����ڣ�1*
    *3��Tqʱ�����ڣ�2*
    *4��Tqʱ�����ڣ�3* 
	����Ĭ�ϣ�0
  *******************/
   uint8_t CAN_Clock_Select; /*CANʱ��Դѡ�� 0������ʱ��/1������ʱ��*/
   uint32_t Global_MASK;     /*ȫ������*/
   uint32_t Buf14_MASK;      /*14��������*/
   uint32_t Buf15_MASK;      /*15��������*/
   uint8_t ID_Accept_Mode;
   /***********************
    *A���� 1��ȫID��             0*
    *B���� 2����׼ID     1*
    *C���� 4���ֲ�8λID  2*
    *D���� �ܾ����и�ʽ�� 3* 
  ***********************/
   uint8_t USE_NUM_MB;           /*�����õ��������=MAX_NUM_MB+1�������õĸ���Ϊ64*/
   uint8_t SELF_Receive_Disable; /*�Ƿ�ʹ���Խ��գ�0���Խ���   1�����Խ���*/
} CAN_ConfigType;

typedef struct /*CAN�������ýṹ��*/
{
   bool RX_FLAG;   /*�Ƿ�����Ϊ�������� 0�� ����  1������*/
   uint32_t CANID; /*���յı���ID*/
   uint8_t IDE;    /*��չ֡��־λ 1����չ֡/0����׼֡*/
   uint8_t MB_NUM; /*ʹ�ñ��Ļ������ı��*/
   uint32_t MASK;  /*˽������*/
   uint8_t IRQ;    /*�Ƿ��ж�*/
} MB_ConfigType;

typedef struct
{
   uint32_t CANID;  /*����ID*/
   uint8_t RTR;     /*Զ��֡��־λ 1��Զ��֡/0������֡*/
   uint8_t IDE;     /*��չ֡��־λ 1����չ֡/0����׼֡*/
   uint8_t DATA[8]; /*����������*/
   uint32_t LENGTH; /*���ݳ���*/
   uint8_t MB_NUM;  /*ʹ�ñ��Ļ������ı��*/
} Can_PduType_SELF;

extern void Can_vidInit(void);
extern uint8_t Can_SetBaudrate(enum CAN_Channel controller, enum CAN_Baud_Type BaudRateConfigID);
extern void Can_Init(CAN_ConfigType *Config);
extern uint8_t Can_Write_Self(enum CAN_Channel controller, Can_PduType_SELF *PduInfo);
extern void Can_SetBuffer(enum CAN_Channel controller, MB_ConfigType *Config);
extern uint8_t Can_Read(enum CAN_Channel controller, Can_PduType_SELF *PduInfo);
extern void Can_Stop(void);

#endif /* __CAN__ */

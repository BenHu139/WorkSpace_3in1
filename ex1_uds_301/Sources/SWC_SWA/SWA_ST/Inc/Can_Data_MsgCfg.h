

#ifndef CAN_DATA_MSG_CFG_H
#define CAN_DATA_MSG_CFG_H

/* !Comment: Included File             */
#include "includes.h"
#include "Can_Data_Types.h"


/* ************************************************************************** */
/*                                 MACROS                                     */
/* ************************************************************************** */
#define BYTE_SWAP_16(x) \
    (uint16)((((uint16)(x) & 0x00ff) << 8) | \
             (((uint16)(x) & 0xff00) >> 8) \
             )

#define BYTE_SWAP_32(x) \
    (uint32)((((uint32)(x) & 0xff000000) >> 24) | \
             (((uint32)(x) & 0x00ff0000) >> 8)  | \
             (((uint32)(x) & 0x0000ff00) << 8)  | \
             (((uint32)(x) & 0x000000ff) << 24) \
             )

/* ************************************************************************** */
/*                                 TYPES                                      */
/* ************************************************************************** */


/* !Comment : CAN 1 Receive messages                                 */
enum
{
   OBC_RX,						/*   CCP boot calication   */
   VCU_PwrCtrl,					/*      */
   BMS_RequestVA,				/*WuLing BMS请求电流 电压*/
   BMS_HeatChargeSt,			/*WuLing BMS加热、充电状态以及继电器状态*/
   VCU_VehicleSt,				/*WuLing 整车运行模式*/
   DCDC_EnSt,					/*WuLing DCDC使能信号*/
#ifdef DEBUG_EN
   Debug_Rx,					/*      */
   TstDataIO,					/*      */
   TstAdc1,						/*      */
   TstAdc2,						/*      */
   TstAdc3,						/*      */
   TstAdc4,						/*      */
#endif
   CAN1_RX_NBMSG
};

/* !Comment : CAN 1 Transmit messages                                 */
enum
{
   OBC_TX = CAN1_RX_NBMSG,		/*   CCP boot calication   */
   DCDC_Sts,					/*   DCDC Status Information   */
   DCDC_BattU,					/*      */
   OBC_Status_1,				/*WuLing IPS状态/输出电压电流/输入电压*/
   OBC_Status_2,				/*WuLing OBC输入电流/CC/CP*/
   OBC_Status_3,				/*WuLing OBC输入过压欠压/输出过压欠压*/
   OBC_Status_4,				/*WuLing IPS型号/供应商代码*/
   DCDC_Status_1,				/*WuLing DCDC输入电压电流/输出电压电流*/
   DCDC_Status_2,				/*WuLing DCDC高温预警信号/状态预警*/
   OBC_WakeUp_Status,			/*WuLing DCDC唤醒/保持指示*/
#ifdef DEBUG_EN
   Debug_Adc_phy1,				/*      */
   Debug_Adc_phy2,				/*      */
   Debug_Adc_phy3,				/*      */
   Debug_Adc_phy4,				/*      */
   Debug_Adc_phy5,				/*      */
   Debug_Adc_clc1,				/*      */
   Debug_Adc_clc2,				/*      */
   Debug_Adc_clc3,				/*      */
   Debug_Adc_clc4,				/*      */
   Debug_Dio_phy,				/*      */
   Debug_St,					/*      */
   OBC_InternalState,           /*      */
   DCDC_InternalState,			/*      */
   DCDC_Fault,					/*      */
   OBC_Fault,
   OBCDCDC_ADJUST,
   OBCDCDC_CtrlVal,
#endif
   CAN1_MSG_NUM
};

/**************************RX Message Start*****************************/
/* !Comment: Message CCP_RX Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 MaxAvaChgVolt:16;		// 1 - 2,   最高允许充电电压
      uint32 MaxAvaChgCurr:16;		// 3 - 4,   最高允许充电电流
      uint32 ChgCtrlEna:8;			// 5,       OBC控制, 0x00: 开始充电; 0x01: 关闭输出(暂不用); 0x02: 充电结束
      
      uint32 :4;
      uint32 BmsSelfChkSt:2;		// 6.3 - 4, BMS自检状态, 0: 正在自检; 1: 自检完成; 2: 自检失败
      uint32 ChgWorkMode:2;			// 6.1 - 2, OBC工作模式, 见系统需求
      
      uint32 :8;
      uint32 :8;
   }Data;
}CanMsg_tstrOBC_RXType;

/* !Comment: Message VcuPwrCtrl Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 Reserved:13;
      uint32 EnableReq:1;
      uint32 UrgtShut:1;
      uint32 Reserved_1:1;
      uint32 VoltReq:16;
      uint32 Reserved_2:20;
      uint32 LivingCnt:4;
      uint32 CheckSum:8;
   }Data;
}CanMsg_tstrVcuPwrCtrlType;

/* WuLing Motorola!Comment: Message BmsReqVa Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 :2;						//bit 7-6
	  uint32 BMSChrgCurRgstV:1;			//bit 5充电电流请求有效性
	  uint32 BMSChrgCurRgst_H5:13;		//bit 4-0充电电流（高5位）
      //uint32 BMSChrgCurRgst_L8:8;		//bit 15-8 充电电流（低8位）
      uint32 :2;						//bit 23-22
      uint32 BMSChrgVolRqstV:1;			//bit 21充电电压请求有效性
      uint32 BMSChrgVolRqst_H5:13;		//bit 20-16充电电压（高5位）
      //uint32 BMSChrgVolRqst_L8:8;		//bit 31-24充电电压（低8位）     
      uint32 :32;						//bit 32-63
   }Data;
}CanMsg_tstrBmsReqVaType;

/* WuLing Motorola!Comment: Message BmsHeatChargeSt Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 :4;					//bit 7-4
	  uint32 BatMaPosRlySts:2;		//bit 3-2电池包主正继电器状态,0x0:断开;0x1:闭合;0x2:粘连;0x3:开路
	  uint32 BatMaNegRlySts:2;		//bit 1-0电池包主负继电器状态,0x0:断开;0x1:闭合;0x2:粘连;0x3:开路
	  uint32 :4;					//bit 15-12
      uint32 BatChrgSts:3;			//bit 11-9电池包充电状态信号,0x0:不可充电;0x1:慢充充电;0x2:充电完成
      uint32 :1;					//bit 8
      uint32 :2;					//bit 23-22
      uint32 BatHeRlySts:2;			//bit 21-20电池包加热继电器状态,0x0:断开;0x1:闭合;0x2:粘连;0x3:开路
      uint32 BatHeSts:3;			//bit 19-17电池包加热状态,0x0:不加热;0x1:加热;0x2:加热完成;0x3:加热故障
      uint32 :1;					//bit 16
      uint32 :8;					//bit 31-24
      uint32 :32;					//bit 63-32
   }Data;
}CanMsg_tstrBmsHeatChargeStType;

/* WuLing Motorola!Comment: Message VcuVehicleSt Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 :2;					//bit 7-6
	  uint32 VecOptMod:4;			//bit 5-2 整车运行模式0x0:休眠;0x1:初始化;0x2:上电;0x3:行驶;0x4:充电;\
	  	  	  	  	  	  	  	  	  	  	  	   //0x5:下电;0x6:故障;0x7:limp home;0x8:馈电补电
	  uint32 VcuVehComSts1RollCnt:2;//bit 1-0循环计数
	  uint32 VecchrgRqst:2;			//bit 15-14 整车充电请求,0x0:禁止充电;0x1:允许充电;0x2:充电完成
	  uint32 :6;					//bit 13-8
	  uint32 :16;					//bit 31-16
      uint32 :24;					//bit 55-32
      uint32 VcuvehComStsCksm:8;	//bit 63-56校验和
   }Data;
}CanMsg_tstrVcuVehicleStType;

/* WuLing Motorola!Comment: Message DcdcEnSt Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 :1;					//bit 7
	  uint32 DCDCEnable:1;			//bit 6 DCDC使能信号,0x0:不使能;0x1使能
	  uint32 :6;					//bit 5-0
      uint32 :24;					//bit 31-8
      uint32 :32;					//bit 63-32
   }Data;
}CanMsg_tstrDcdcEnStType;
/**************************RX Message End*******************************/

/**************************TX Message Start*****************************/
/* !Comment: Message OBC_TX Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 ChgGeneVolt:16;		// 1 - 2, 充电机输出电压
      uint32 ChgGeneCurr:16;		// 3 - 4, 充电机输出电流
      
      uint32 BlockOverTemp:1;		// 5.8, 充电座过温故障 , 0: 正常  1: 故障
      uint32 CpFault:1;				// 5.7, CP故障 , 0: 正常  1: 故障
      uint32 CcFault:1;				// 5.6, CC故障 , 0: 正常  1: 故障
      uint32 ComuSt:1;				// 5.5, CAN通信状态 , 0: 通信正常  1: 通信超时
      uint32 BatStatus:1;			// 5.4, 高压电池状态 , 0: 电池电压正常  1: 电池电压异常
      uint32 InputVoltage:1;		// 5.3, 输入电压故障, 0: 正常  1: 故障
      uint32 ChgTemp:1;				// 5.2, 充电机温度故障, 0: 正常  1: 故障
      uint32 HardFault:1;			// 5.1, 硬件故障, 0: 正常  1: 故障
      
      uint32 FanSt:1;				// 6.8, 风扇状态位, 0: 不工作    1: 工作
      uint32 ElockSt:2;				// 6.6-7, 电子锁状态, 0: 未锁  1:已锁  2:解锁中   3:故障
      uint32 S2St:1;				// 6.5, S2开关控制位状态, 0: 断开  1: 闭合
      uint32 InterOverTemp:1;		// 6.4, 内部过热警告, 0: 正常  1: 过热警告
      uint32 CcSt:3;				// 6.1-3, CC信号状态, 见系统需求


      uint32 CurMaxPower:8;			// 7, 当前最大输出功率
      uint32 ObcTemp:8;				// 8, OBC温度
   }Data;
}CanMsg_tstrOBC_TXType;

/* !Comment: Message DcdcSt Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 DcdcTemp:8;
      
      uint32 :4;
      uint32 DcdcTempSt:2;      
      uint32 DcdcSt:2;

   }Data;
}CanMsg_tstrDcdcStType;

/* !Comment: Message DCDC_BattU Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	   uint32 CcRcOhmVal:16;
	   uint32 :16;
	   uint32 :32;
   }Data;
}CanMsg_tstrDCDC_BattUType;

/* WuLing Motorola!Comment: Message OBC_Status_1 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	   uint32 :2;					//bit7-6
	   uint32 IPSState:4;			//bit5-2IPS当前状态
	   uint32 :2;					//bit1-0
	   uint32 OBCOtpCurV:1;			//bit15 OBC输出电流有效性
	   uint32 :2;					//bit14-13
	   uint32 OBCOtpCur_H5:13;		//bit12-8 OBC输出电流高5位
	   //uint32 OBCOtpCur_L8:8;		//bit23-16 OBC输出电流低8位
	   uint32 OBCOtpVltV:1;			//bit31 OBC输出电压有效性
	   uint32 :2;					//bit30-29
	   uint32 OBCOpVIt_H5:13;		//bit28-24 OBC输出电压高5位
	   //uint32 OBCOpVIt_L8:8;		//bit39-32 OBC输出电压低8位
	   uint32 :5;					//bit47-43
	   uint32 OBCInpVItV:1;			//bit42 OBC输入电压有效性
	   uint32 :1;					//bit41
	   uint32 OBCInpVIt_H1:9;		//bit40 OBC输入电压高1位
	   //uint32 OBCInpVIt_L8:8;		//bit55-47 OBC输入电压低8位
	   uint32 OBCORDCACIntnlTemp:8; //bit63-56 OBC&DC/AC内部温度
   }Data;
}CanMsg_tstrOBC_Status_1Type;

/* WuLing Motorola!Comment: Message OBC_Status_2 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	   uint32 OBCInpCurV:1;			//bit7 OBC输入电流有效性
	   uint32 OBCInpMxCurV:1;		//bit6 OBC输入最大电流有效性
	   uint32 :6;					//bit5-0
	   uint32 OBCInpCur:8;			//bit15-8 OBC输入电流
	   uint32 OBCInpMxCur:8;		//bit23-16 OBC输入最大电流
	   uint32 BMSChrgVolCurRqstAnorm:1;	//bit31BMS请求电压/电流异常
	   uint32 OBCInpCurOv:1;		//bit30 OBC输入电流过流
	   uint32 OBCLVSts:1;			//bit29 OBC低压自检状态,0:自检正常,1自检异常,
	   uint32 Swit2Status:1;		//bit28 S2开关状态,0:断开,1:闭合
	   uint32 CCSts:2;				//bit27-26 CC检测状态,0:未连接,1:半连接,2:充电连接,3:放电连接
	   uint32 CPSts:2;				//bit25-24 CP检测状态
	   uint32 EleLockSts:2;			//bit39-38 电子锁状态
	   uint32 :6;					//bit37-32
	   uint32 OF1AlterCurWire:8;	//bit47-40 交流线束温度传感器1
	   uint32 :8;					//bit55-48
	   uint32 OF2AlterCurWire:8;	//bit63-56  交流线束温度传感器2
   }Data;
}CanMsg_tstrOBC_Status_2Type;

/* WuLing Motorola!Comment: Message OBC_Status_3 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	   uint32 OBCHdErr:1;			//bit7 OBC硬件故障,0:无错误,1:故障
	   uint32 :7;					//bit6-0
	   uint32 WaterwaysTemp:8;		//bit15-8 水道水温
	   uint32 OBCInpVolOv:1;		//bit23 OBC输入电压过压
	   uint32 OBCInpVolUn:1;		//bit22 OBC输入电压欠压
	   uint32 :6;					//bit21-16
	   uint32 OBCOtpVolOv:1;		//bit31 OBC输出电压过压
	   uint32 OBCOtpVolUn:1;		//bit30 OBC输出电压欠压
	   uint32 :6;					//bit29-24
	   uint32 OBCOtpCurOv:1;		//bit39 OBC输出电流过流
	   uint32 :7;					//bit38-32
	   uint32 OBCOvTemp:1;			//bit47 OBC过温保护
	   uint32 ConcetFailOfChrg:1;	//bit46 充电设施连接故障
	   uint32 ChrgCrlSnglFail:2;	//bit45-44 充电控制信号故障
	   uint32 AclnpFIt:1;			//bit43 交流输入故障
	   uint32 HVDCOtpOpCiret:1;		//bit42 高压直流输出开路
	   uint32 HVDCOtpFIt:1;			//bit41 高压交流输出开路
	   uint32 :1;					//bit40
	   uint32 DCDCInternalTemp:8;	//bit55-48 DCDC内部温度
	   uint32 :8; 					//bit63-56
   }Data;
}CanMsg_tstrOBC_Status_3Type;

/* WuLing Motorola!Comment: Message OBC_Status_4 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	   uint32 IPSType:4;			//bit7-4 IPS型号
	   uint32 SupCode:4;			//bit3-0 供应商代码
	   uint32 SoftwareMaVsnNum:8;   //bit15-8 软件版本号
	   uint32 :16;					//bit31-16
	   uint32 :32;					//bit63-32
   }Data;
}CanMsg_tstrOBC_Status_4Type;

/* WuLing Motorola!Comment: Message DCDC_Status_1 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	   uint32 DcDcotpVol:8;			//bit7-0 DCDC输出电压
	   uint32 DCDCOtpCur_H8:11;		//bit15-8 DCDC输出电流（高8位）
	   //uint32 DCDCOtpCur_L3:3;		//bit23-21 DCDC输出电流（低3位）
	   //uint32 DCDCInpVol_H5:5;		//bit20-16 DCDC输入电压（高5位）
	   uint32 DCDCInpVol_L8:13;   	//bit31-24 DCDC输入电压（低8位）
	   uint32 DCDCInpCur:8;			//bit39-32 DCDC输入电流
	   uint32 DCDCItpVolSts:2;		//bit47-46 DCDC输入电压状态
	   uint32 DCDCOtpVolSts:2;		//bit45-44 DCDC输出电压状态
	   uint32 DCDCOtpShtCicut:1;	//bit43 DCDC输出短路
	   uint32 DCDCIntnlFlt:1;   	//bit42 DCDC内部故障
	   uint32 DCDCWkSts:2;			//bit41-40 DCDC工作状态
	   uint32 :4;					//bit55-52
	   uint32 DCDCGenStsRollCnt:4;	//bit51-48 循环计数值
	   uint32 DCDCGenStsStuCksm:8;  //bit63-56 校验和
   }Data;
}CanMsg_tstrDCDC_Status_1Type;

/* WuLing Motorola!Comment: Message DCDC_Status_2 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	   uint32 DCDCTempWmg:4;		//bit7-4 DC/DC高温预警信号
	   uint32 DCDCStsWrng:4;		//bit3-0 DC/DC状态预警信号
	   uint32 :24;					//bit31-16
	   uint32 :32;					//bit63-32
   }Data;
}CanMsg_tstrDCDC_Status_2Type;

/* WuLing Motorola!Comment: Message OBC_WakeUp_Status Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	   uint32 :7;					//bit7-1
	   uint32 InitaContindOn_OBC:1;	//bit0 唤醒/保持指示
	   uint32 :24;					//bit31-8
	   uint32 :32;					//bit63-32
   }Data;
}CanMsg_tstrOBC_WakeUp_StatusType;
/**************************TX Message End*******************************/

#ifdef DEBUG_EN
/* !Comment: Message Debug_Adc_phy1 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 CcOhmHiVolAdc:16;
      uint32 CcOhmLoVolAdc:16;
      uint32 Ac220vVolAdc:16;
      uint32 PfcOutputVolAdc:16;
   }Data;
}CanMsg_tstrDebug_Adc_phy1Type;

/* !Comment: Message Debug_Adc_phy2 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 AdcHVolt:16;
	  uint32 AdcHCurrent:16;
      uint32 AdcLVolt:16;
      uint32 AdcLCurrent:16;
   }Data;
}CanMsg_tstrDebug_Adc_phy2Type;

/* !Comment: Message Debug_Adc_phy3 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 LlcOutputVolAdc:16;
	  uint32 LlcOutputCurAdc:16;
      uint32 HiBatVolAdc:16;
      uint32 AdcLVcc27v:16;
   }Data;
}CanMsg_tstrDebug_Adc_phy3Type;

/* !Comment: Message Debug_Adc_phy4 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 PfcTempAdc:16;
	  uint32 LlcFbTempAdc:16;
      uint32 AdcTempS:16;
      uint32 AdcTempP:16;
   }Data;
}CanMsg_tstrDebug_Adc_phy4Type;

typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 VinTest:16;
	  uint32 CcSense1:16;
      uint32 :16;
      uint32 :16;
   }Data;
}CanMsg_tstrDebug_Adc_phy5Type;

/* !Comment: Message Debug_Adc_clc1 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 CcOhmHiVolAdc:16;
	  uint32 CcOhmLoVolAdc:16;
	  uint32 Ac220vVolAdc:16;
	  uint32 PfcOutputVolAdc:16;
   }Data;
}CanMsg_tstrDebug_Adc_clc1Type;

/* !Comment: Message Debug_Adc_clc2 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 AdcHVolt:16;
	  uint32 AdcHCurrent:16;
	  uint32 AdcLVolt:16;
	  uint32 AdcLCurrent:16;
   }Data;
}CanMsg_tstrDebug_Adc_clc2Type;

/* !Comment: Message Debug_Adc_clc3 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 LlcOutputVolAdc:16;
	  uint32 LlcOutputCurAdc:16;
	  uint32 HiBatVolAdc:16;
	  uint32 AdcLVcc27v:16;
   }Data;
}CanMsg_tstrDebug_Adc_clc3Type;

/* !Comment: Message Debug_Adc_clc4 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 PfcTempAdc:16;
	  uint32 LlcFbTempAdc:16;
	  uint32 AdcTempS:16;
	  uint32 AdcTempP:16;
   }Data;
}CanMsg_tstrDebug_Adc_clc4Type;

/* !Comment: Message Debug_DIO_phy Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 :8;

	  uint32 CcPluginDI:1;
	  uint32 ObcEnaDI:1;
	  uint32 DcdcEnaDI:1;
	  uint32 PfcStopUI:1;
	  uint32 LlcHardPrtUI:1;
	  uint32 LvShortM:1;
	  uint32 VoutInterLockDiag:1;
	  uint32 KL15:1;
	  
	  uint32 :8;
	  uint32 :8;

	  uint32 CcOut680DO:1;
	  uint32 CcOut1000DO:1;
	  uint32 VcuEnaDO:1;
	  uint32 CpS2CtrlDO:1;
	  uint32 FanCtrl:1;
	  uint32 FlyBackEna:1;
	  uint32 FlyBackOffDO:1;
	  uint32 PowerEna:1;
	  
	  uint32 DcdcPwrPrtDO:1;
	  uint32 DcdcHartPrtRstDO:1;
	  uint32 McuPwrLockDO:1;
	  uint32 PfcJdqEnaUO:1;
	  uint32 LlcJdqEnaUO:1;
	  uint32 PfcLedCtrlUO:1;
	  uint32 LlcLedCtrlUO:1;      
	  uint32 PfcOnUO:1;
	  
	  uint32 LlcPrtUO:1;
	  uint32 PccSt:1;
	  uint32 OutSwEnSt:1;
	  uint32 :5;
	  
	  uint32 :8;
   }Data;
}CanMsg_tstrDebug_DIO_phyType;

/* !Comment: Message Debug_St Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 Sts:16;
      uint32 Error:16;
   }Data;
}CanMsg_tstrDebug_StType;

/* !Comment: Message Debug_Rx Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  // Byte 1 
      uint32 EmuTestEnable:1;			// 使能位
      uint32 McuPwrCtrl:1;				// 主控MCU电源锁
      uint32 FlyBackEna:1;				// 反激电源使能(MCU1/2)
      uint32 FlyBackOff:1;				// 反激电源禁用(MCU1/2)
      
      uint32 CcEmuTstEna:1;				// 充电桩模拟测试使能位
      uint32 PfcEmuTstEna:1;			// PFC模拟测试使能位
      uint32 LlcEmuTstEna:1;			// LLC模拟测试使能位
      uint32 DCDCEmuTstEna:1;			// DCDC模拟测试使能位
      
      // Byte 2
      uint32 CpS2Ctrl:1;				// CP 开关S2控制 
      uint32 CpDuty:7;					// CP 占空比

      // Byte 3 -4
      uint32 DcdcPwrPrt:1;				// 28950保护控制位
      uint32 DcdcPwrEna:1;				// 28950使能控制位
      uint32 :4;
      uint32 LLC_Vadj:10;				// LLC给定电压占空比
      
      // Byte 5 - 6
      uint32 PfcJdqEn:1;				// PFC继电器控制
      uint32 PfcLedCtrl:1;				// PFC LED控制
      uint32 PfcOnCtrl:1;				// PFC 使能控制
      uint32 LlcJdqEn:1;				// LLC继电器控制
      uint32 LlcLedCtrl:1;				// LLC LED控制
      uint32 LlcPrtCtrl:1;				// LLC 保护控制
      uint32 LLC_Iadj:10;				// LLC给定电流占空比
      
      // Byte 7
      uint32 DCDC_Vadj:8;				// DCDC给定电压占空比
      // Byte 8
      uint32 DCDC_Iadj:8;				// DCDC给定电流占空比
   }Data;
}CanMsg_tstrDebug_RxType;

/* !Comment: Message TstDataIO Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 :7;
      uint32 IOTestEnable:1;
      
      uint32 :1;
      uint32 TstObcEnaDI:1;
      uint32 TstDcdcEnaDI:1;
      uint32 TstPfcStopUI:1;
      uint32 TstLlcHardPrtUI:1;
      uint32 TstLvShortM:1;
      uint32 TstVoutInterLockDiag:1;
      uint32 TstKL15:1;
      
      uint32 :8;
      uint32 :8;

      uint32 TstCcOut680DO:1;
      uint32 TstCcOut1000DO:1;
      uint32 TstVcuEnaDO:1;
      uint32 TstCpS2CtrlDO:1;
      uint32 TstFanCtrl:1;
      uint32 TstFlyBackEna:1;
	  uint32 TstFlyBackOffDO:1;
      uint32 TstPowerEna:1;
      
      uint32 TstDcdcPwrPrtDO:1;
      uint32 TstDcdcHartPrtRstDO:1;
      uint32 TstMcuPwrLockDO:1;
      uint32 TstPfcJdqEnaUO:1;
      uint32 TstLlcJdqEnaUO:1;
      uint32 TstPfcLedCtrlUO:1;
	  uint32 TstLlcLedCtrlUO:1;      
	  uint32 TstPfcOnUO:1;
	  
	  uint32 TstLlcPrtUO:1;
      uint32 :7;
      
      uint32 :8;
   }Data;
}CanMsg_tstrTstDataIOType;

/* !Comment: Message TstAdc1 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 TstCcOhmHiVolAdc:16;
      uint32 TstCcOhmLoVolAdc:16;
      uint32 TstCpVolAdc:16;
      uint32 TstPfcOutputVolAdc:16;
   }Data;
}CanMsg_tstrTstAdc1Type;

/* !Comment: Message TstAdc2 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 TstAdcHVolt:16;
      uint32 TstAdcHCurrent:16;
      uint32 TstAdcLVolt:16;
      uint32 TstAdcLCurrent:16;
   }Data;
}CanMsg_tstrTstAdc2Type;

/* !Comment: Message TstAdc3 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 TstLlcOutputVolAdc:16;
      uint32 TstLlcOutputCurAdc:16;
      uint32 TstHiBatVolAdc:16;
      uint32 TstAdcLVcc27v:16;
   }Data;
}CanMsg_tstrTstAdc3Type;

/* !Comment: Message TstAdc4 Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 TstPfcTempAdc:16;
      uint32 TstLlcFbTempAdc:16;
      uint32 TstAdcTempS:16;
      uint32 TstAdcTempP:16;
   }Data;
}CanMsg_tstrTstAdc4Type;

/* !Comment: Message DCDC_InternalState Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 VoltLim:8;
      uint32 CurrentLim:8;
      uint32 PoweLim:8;
      uint32 bRelayCt_Sts:1;
      uint32 bEn28950_Sts:1;
      uint32 bGG_Sts:1;
      uint32 bPcc_Sts:1;
      uint32 bResetProm_Sts:1;
      uint32 bEn28950Delay_Sts:1;
      uint32 VoltOut:16;
      uint32 CurOut:16;
   }Data;
}CanMsg_tstrDCDC_InternalStateType;

/* !Comment: Message OBC_InternalState Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 CcOhm:16;
      uint32 CpVol:16;
      uint32 CpDuty:16;
      uint32 :8;
      uint32 :7;
      uint32 ConnSt:1;
   }Data;
}CanMsg_tstrOBC_InternalStateType;

/* !Comment: Message DCDC_Fault Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 Fault:1;
      uint32 InputOvp:1;
      uint32 InputUvp:1;
      uint32 OutOvp:1;
      uint32 OutUvp:1;
      uint32 Otp:1;
      uint32 InputOCP:1;
      uint32 Derating:1;     
      uint32 FSM_WorkingSt:8;
      uint32 DSM_SWFailSt:8;
      uint32 FSM_CurrentFaultSt:8;
      uint32 FSM_FaultProcessCtrlSt:8;
   }Data;
}CanMsg_tstrDCDC_FaultType;

/* !Comment: Message OBC_Fault Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
      uint32 OSM_HwFaultFlag:1;
      uint32 OSM_SwFaultFlag:1;
      uint32 :6;
      uint32 :8;
      uint32 :8;
      uint32 :8;
     
      uint32 OSM_WorkingSt:8;
      uint32 OSM_SWFailSt:8;
      uint32 OSM_CurrentFaultSt:8;
      uint32 OSM_FaultProcessCtrlSt:8;
   }Data;
}CanMsg_tstrOBC_FaultType;

/* !Comment: Message OBC/DCDC adjust volt current Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 LLC_VADJ:8;
	  uint32 LLC_IADJ:8;
	  uint32 DCDC_VADJ:8;
	  uint32 DCDC_IADJ:8;
	  
      uint32 :8;
      uint32 :8;
      uint32 :8;
      uint32 :8;
   }Data;
}CanMsg_tstrOBCDCDC_AdjustType;

/* !Comment: Message OBC/DCDC adjust volt current Type definition      */
typedef union
{
   uint8  u8Frame[8];
   uint16 u16Frame[4];
   uint32 u32Frame[2];
   struct
   {
	  uint32 LlcCtrlVol:16;
	  uint32 LlcCtrlCur:16;
	  uint32 DcdcCtrlVol:16;
	  uint32 DcdcCtrlCur:16;
   }Data;
}CanMsg_tstrOBCDCDC_CtrlValType;

#endif
/* ************************************************************************** */
/*                              GLOABAL VARIRABLE                             */
/* ************************************************************************** */

/* !Comment: Message CCP_RX structure definition      */
extern CanMsg_tstrOBC_RXType CanMsg_tstrOBC_RX;

/* !Comment: Message VcuPwrCtrl structure definition      */
extern CanMsg_tstrVcuPwrCtrlType CanMsg_tstrVcuPwrCtrl;

/* WuLing Receive!Comment: Message BmsReqVa structure definition      */
extern CanMsg_tstrBmsReqVaType CanMsg_tstrBmsReqVa;

/* WuLing Receive!Comment: Message BmsHeatCharge structure definition      */
extern CanMsg_tstrBmsHeatChargeStType CanMsg_tstrBmsHeatChargeSt;

/* WuLing Receive!Comment: Message VcuVehicle structure definition      */
extern CanMsg_tstrVcuVehicleStType CanMsg_tstrVcuVehicleSt;

/* WuLing Receive!Comment: Message DcdcEn structure definition      */
extern CanMsg_tstrDcdcEnStType CanMsg_tstrDcdcEnSt;


/* !Comment: Message CCP_TX structure definition      */
extern CanMsg_tstrOBC_TXType CanMsg_tstrOBC_TX;

/* !Comment: Message DcdcSt structure definition      */
extern CanMsg_tstrDcdcStType CanMsg_tstrDcdcSt;

/* !Comment: Message DCDC_BattU structure definition      */
extern CanMsg_tstrDCDC_BattUType CanMsg_tstrDCDC_BattU;

/* WuLing Transmission!Comment: Message OBC_Status_1 structure definition      */
extern CanMsg_tstrOBC_Status_1Type CanMsg_tstrOBC_Status_1;

/* WuLing Transmission!Comment: Message OBC_Status_2 structure definition      */
extern CanMsg_tstrOBC_Status_2Type CanMsg_tstrOBC_Status_2;

/* WuLing Transmission!Comment: Message OBC_Status_3 structure definition      */
extern CanMsg_tstrOBC_Status_3Type CanMsg_tstrOBC_Status_3;

/* WuLing Transmission!Comment: Message OBC_Status_4 structure definition      */
extern CanMsg_tstrOBC_Status_4Type CanMsg_tstrOBC_Status_4;

/* WuLing Transmission!Comment: Message DCDC_Status_1 structure definition      */
extern CanMsg_tstrDCDC_Status_1Type CanMsg_tstrDCDC_Status_1;

/* WuLing Transmission!Comment: Message DCDC_Status_2 structure definition      */
extern CanMsg_tstrDCDC_Status_2Type CanMsg_tstrDCDC_Status_2;

/* WuLing Transmission!Comment: Message OBC_WakeUp_Status structure definition      */
extern CanMsg_tstrOBC_WakeUp_StatusType CanMsg_tstrOBC_WakeUp_Status;

#ifdef DEBUG_EN
/* !Comment: Message Debug_Adc_phy1 structure definition      */
extern CanMsg_tstrDebug_Adc_phy1Type CanMsg_tstrDebug_Adc_phy1;

/* !Comment: Message Debug_Adc_phy2 structure definition      */
extern CanMsg_tstrDebug_Adc_phy2Type CanMsg_tstrDebug_Adc_phy2;

/* !Comment: Message Debug_Adc_phy3 structure definition      */
extern CanMsg_tstrDebug_Adc_phy3Type CanMsg_tstrDebug_Adc_phy3;

/* !Comment: Message Debug_Adc_phy4 structure definition      */
extern CanMsg_tstrDebug_Adc_phy4Type CanMsg_tstrDebug_Adc_phy4;

/* !Comment: Message Debug_Adc_phy5 structure definition      */
extern CanMsg_tstrDebug_Adc_phy5Type CanMsg_tstrDebug_Adc_phy5;

/* !Comment: Message Debug_Adc_clc1 structure definition      */
extern CanMsg_tstrDebug_Adc_clc1Type CanMsg_tstrDebug_Adc_clc1;

/* !Comment: Message Debug_Adc_clc2 structure definition      */
extern CanMsg_tstrDebug_Adc_clc2Type CanMsg_tstrDebug_Adc_clc2;

/* !Comment: Message Debug_Adc_clc3 structure definition      */
extern CanMsg_tstrDebug_Adc_clc3Type CanMsg_tstrDebug_Adc_clc3;

/* !Comment: Message Debug_Adc_clc4 structure definition      */
extern CanMsg_tstrDebug_Adc_clc4Type CanMsg_tstrDebug_Adc_clc4;

/* !Comment: Message Debug_Adc_clc3 structure definition      */
extern CanMsg_tstrDebug_DIO_phyType CanMsg_tstrDebug_DIO_phy;

/* !Comment: Message Debug_St structure definition      */
extern CanMsg_tstrDebug_StType CanMsg_tstrDebug_St;

/* !Comment: Message Debug_Rx structure definition      */
extern CanMsg_tstrDebug_RxType CanMsg_tstrDebug_Rx;

/* !Comment: Message TstDataIO structure definition      */
extern CanMsg_tstrTstDataIOType CanMsg_tstrTstDataIO;

/* !Comment: Message TstAdc1 structure definition      */
extern CanMsg_tstrTstAdc1Type CanMsg_tstrTstAdc1;

/* !Comment: Message TstAdc2 structure definition      */
extern CanMsg_tstrTstAdc2Type CanMsg_tstrTstAdc2;

/* !Comment: Message TstAdc3 structure definition      */
extern CanMsg_tstrTstAdc3Type CanMsg_tstrTstAdc3;

/* !Comment: Message TstAdc4 structure definition      */
extern CanMsg_tstrTstAdc4Type CanMsg_tstrTstAdc4;

/* !Comment: Message DCDC_InternalState structure definition      */
extern CanMsg_tstrOBC_InternalStateType CanMsg_tstrOBC_InternalState;

/* !Comment: Message DCDC_InternalState structure definition      */
extern CanMsg_tstrDCDC_InternalStateType CanMsg_tstrDCDC_InternalState;

/* !Comment: Message DCDC_Fault structure definition      */
extern CanMsg_tstrDCDC_FaultType CanMsg_tstrDCDC_Fault;

/* !Comment: Message DCDC_Fault structure definition      */
extern CanMsg_tstrOBC_FaultType CanMsg_tstrOBC_Fault;

/* !Comment: Message OBC/DCDC adjust volt current Type definition      */
extern CanMsg_tstrOBCDCDC_AdjustType CanMsg_tstrOBCDCDC_Adjust;

/* !Comment: Message OBC/DCDC control volt current Type definition      */
extern CanMsg_tstrOBCDCDC_CtrlValType CanMsg_tstrOBCDCDC_CtrlVal;

#endif

/* !Comment:  CAN A message buffer     */
extern const Can_tstrMbType Can_astrMbCfg_B[CAN1_MSG_NUM];
extern uint16 Can_u16FreqCnt_B[CAN1_MSG_NUM];

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */


#endif

/* ************** End of The File *************************************** */

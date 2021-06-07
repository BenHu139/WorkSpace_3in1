/**
 * @file CAN.c FLEXCAN模块源文件
 * @ingroup HAL_MCU_CAN
 */

#include "includes.h"

#include "CAN.h"
#include "TMR.h"
#include "CAN_STACK.h"
#include "CAN_CFG_SELF.h"
#include "CanSM.h"

#define JYD_E_NOT_OK 0U
//#define TRUE 1U

#define FAULT 0U
#define CAN_OK 1U

#define STANDARD_ID 0U
#define EXTEND_ID 1U

#define REMOTE_FORMAT 1U
#define DATA_FORMAT 0U

#define CAN_MAX_MB 64U /*报文缓冲区最大个数*/

#define CAN_TX_MSG (0x0CU)           /*传输报文*/
#define CAN_RX_EMPTY (0x04U)         /*设置RX接收为空*/
#define TX_CODE_INACTIVE (0x8U)      /*TX缓存区未被激活*/
#define RX_CODE_INACTIVE (0x0U)      /*RX缓存区未被激活*/


#define TX_CODE_SUCCESS_RTR1 (0x04U) /*RTR为1时发送成功后CODE的返回值*/
#define TX_CODE_SUCCESS_RTR0 (0x08U) /*RTR为0时发送成功后CODE的返回值*/

#define CAN_OVERTIME (2U)

void Can_vidInit(void)
{
	CAN_CFG_Sel(CAN_CHANNEL_CAN0, CAN_CHANNEL_CAN0);
	FWS_CAN_STACK_Init();
	FWS_CAN_STACK_InitSel(CAN_CHANNEL_CAN0, CAN_CHANNEL_CAN0);
	CanSM_Init();/*BUSOFF初始化*/ 
}

/**
 * @brief CAN设置波特率
 * @ingroup HAL_MCU_CAN
 * @param CAN_Channel_NUM controller 设置的CAN端口： \n    
 * 1.CAN_CHANNEL_CAN0 \n
 * 2.CAN_CHANNEL_CAN1 \n
 * 3.CAN_CHANNEL_CAN2 \n
 * 4.CAN_CHANNEL_CAN3 \n
 * 5.CAN_CHANNEL_CAN4 \n 
 * 6.CAN_CHANNEL_CAN5  
 * @param CAN_Baud_Type BaudRateConfigID  设置的波特率ID：\n
 * 1.CAN_BOUD_RATE_250KB \n
 * 2.CAN_BOUD_RATE_500KB \n
 * 3.CAN_BOUD_RATE_1M 
 * @return 0:设置失败 \n 1:设置成功
 * 限制条件：1.以锁相环频率64MHZ作为CAN时钟； 
          2.必须在冻结模式下才能设置； 
 */
uint8_t Can_SetBaudrate(enum CAN_Channel controller, enum CAN_Baud_Type BaudRateConfigID)
{
   uint8_t Error_Code = TRUE;
   switch (controller)
   {
   case CAN_CHANNEL_CAN0:
   {
      if (BaudRateConfigID == CAN_BOUD_RATE_250KB)
      {
         CAN_0.CR.B.PRESDIV = 15U; /*波特率= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_0.CR.B.PSEG1 = 4U;
         CAN_0.CR.B.PSEG2 = 4U;
         CAN_0.CR.B.PROPSEG = 4U;
      }
      else if (BaudRateConfigID == CAN_BOUD_RATE_500KB)
      {
         CAN_0.CR.B.PRESDIV = 7U; /*波特率= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_0.CR.B.PSEG1 = 4U;
         CAN_0.CR.B.PSEG2 = 4U;
         CAN_0.CR.B.PROPSEG = 4U;
      }
      else if (BaudRateConfigID == CAN_BOUD_RATE_1M)
      {
         CAN_0.CR.B.PRESDIV = 3U; /*波特率= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_0.CR.B.PSEG1 = 4U;
         CAN_0.CR.B.PSEG2 = 4U;
         CAN_0.CR.B.PROPSEG = 4U;
      }
      else
      {
         Error_Code = JYD_E_NOT_OK;
      }
      break;
   }
   case CAN_CHANNEL_CAN1:
   {
      if (BaudRateConfigID == CAN_BOUD_RATE_250KB)
      {
         CAN_1.CR.B.PRESDIV = 15U; /*波特率= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_1.CR.B.PSEG1 = 4U;
         CAN_1.CR.B.PSEG2 = 4U;
         CAN_1.CR.B.PROPSEG = 4U;
      }
      else if (BaudRateConfigID == CAN_BOUD_RATE_500KB)
      {
         CAN_1.CR.B.PRESDIV = 7U; /*波特率= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_1.CR.B.PSEG1 = 4U;
         CAN_1.CR.B.PSEG2 = 4U;
         CAN_1.CR.B.PROPSEG = 4U;
      }
      else if (BaudRateConfigID == CAN_BOUD_RATE_1M)
      {
         CAN_1.CR.B.PRESDIV = 3U; /*波特率= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_1.CR.B.PSEG1 = 4U;
         CAN_1.CR.B.PSEG2 = 4U;
         CAN_1.CR.B.PROPSEG = 4U;
      }
      else
      {
         Error_Code = JYD_E_NOT_OK;
      }
      break;
   }
   default:
   {
      Error_Code = JYD_E_NOT_OK;
      break;
   }
   }
   return Error_Code;
}

/**
 * @brief CAN初始化设置
 * @ingroup HAL_MCU_CAN
 * @param CAN_ConfigType Config  初始化配置参数：\n
 * 1.Config.CAN_CHANNEL_ID 需要操作的CAN端口  \n
 * 2.Config.CAN_Baund_ID  设置的波特率 \n
 * 3.Config.Synch_Jump_Width 设置的同步跳转宽度 \n
 * 4.Config.CAN_Clock_Select 选择CAN时钟 \n
 * 5.Config.CAN_ACCEPT_AR 设置接收码 \n
 * 6.Config.Global_MASK;    全局掩码 \n
 * 7.Config.Buf14_MASK;      14邮箱掩码 \n
 * 8.Config.Buf15_MASK;      15邮箱掩码 \n
 * 9.Config.CAN_Filter_Type 设置滤波器类型 \n
 * 10.Config.SELF_Receive_Disable  设置是否自接受 0：自接收   1：不自接收
 * @return void
 */
void Can_Init(CAN_ConfigType *Config)
{
   uint8_t can_set_result = 1U;
   uint32_t reset_flag = 1U;
   uint16_t i = 0U;
   uint16_t x = 0U;

   uint32_t CAN_CurrentTime = 0U;
   uint32_t CAN_StartTime = 0U;

   switch (Config->CAN_CHANNEL_ID)
   {
   case CAN_CHANNEL_CAN0:
   {
      SIU.PCR[16].R = 0x0603U; /*选择CAN0TX功能*/
      SIU.PCR[17].R = 0X0100U; /*将CAN0RX所在引脚设置为输入*/
      CAN_0.MCR.B.MDIS = 0U;
      CAN_0.MCR.B.SOFTRST = 1U; /*软件复位*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((reset_flag == 1U) && (CAN_CurrentTime - CAN_StartTime <= CAN_OVERTIME)) /*等待复位完成*/
      {
         reset_flag = CAN_0.MCR.B.SOFTRST;
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      CAN_0.MCR.B.MDIS = 1U;                        /*禁止FLEXCAN模块以便选择时钟*/
      CAN_0.CR.B.CLKSRC = Config->CAN_Clock_Select; /*选择总线时钟作为CAN时钟：0、晶振时钟   1、总线时钟*/
      CAN_0.CR.B.BOFFREC = 1U;                      /*关闭BUSOFF自恢复功能*/
      CAN_0.MCR.B.MDIS = 0U;                        /*使能FLEXCAN模块*/
      CAN_0.MCR.B.HALT = 1U;                        /*暂停CAN模块*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((CAN_0.MCR.B.FRZACK == 0U) && (CAN_CurrentTime - CAN_StartTime <= CAN_OVERTIME))
      {
         CAN_0.MCR.B.FRZ = 1U; /*进入冻结模式*/
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      CAN_0.MCR.B.BCC = 1U; /*打开单个MB屏蔽码*/
      CAN_0.MCR.B.SRXDIS = Config->SELF_Receive_Disable;
      CAN_0.MCR.B.WRNEN = 1U;                                                   /*使能警告中断*/
      CAN_0.MCR.B.IDAM = Config->ID_Accept_Mode;                                /*选择FIFO格式为FORMAT A*/
      CAN_0.MCR.B.FEN = 0U;                                                     /*关闭FIFO*/
      CAN_0.CR.B.RJW = Config->Synch_Jump_Width;                                /*设置同步跳转宽度*/
      can_set_result = Can_SetBaudrate(CAN_CHANNEL_CAN0, Config->CAN_Baund_ID); /*设置波特率*/
      if (Config->USE_NUM_MB >= CAN_MAX_MB)                                     /*报文缓冲区最多只能设置64个*/
      {
         Config->USE_NUM_MB = CAN_MAX_MB;
      }
      CAN_0.MCR.B.MAXMB = Config->USE_NUM_MB - 1U; /*设置使用的报文缓冲区个数*/
      for (x = 0U; x < Config->USE_NUM_MB; x++)
      {
         CAN_0.BUF[x].CS.R = 0U;   /*清空BUF寄存器第一行*/
         CAN_0.BUF[x].ID.R = 0U;   /*清空BUF寄存器第二行*/
         for (i = 0U; i < 2U; i++) /*清空BUF寄存器第三四行*/
         {
            CAN_0.BUF[x].DATA.W[i] = 0U;
         }
      }
      if (can_set_result == TRUE) /*波特率设置成功*/
      {
         CAN_0.RXGMASK.R = Config->Global_MASK; /*全局掩码*/
         CAN_0.RX14MASK.R = Config->Buf14_MASK; /*14邮箱掩码*/
         CAN_0.RX15MASK.R = Config->Buf15_MASK; /*15邮箱掩码*/
      }
      CAN_0.IMRH.R = 0x00000000U; /*禁止每一个缓冲区中断*/
      CAN_0.IMRL.R = 0x00000000U;
      CAN_0.MCR.B.HALT = 0U;
      CAN_0.MCR.B.FRZ = 0U; /*退出冻结模式*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((CAN_0.MCR.B.NOTRDY == 1U) && ((CAN_CurrentTime - CAN_StartTime) <= CAN_OVERTIME)) /*等待进入正常模式,2ms超时*/
      {
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      break;
   }
   case CAN_CHANNEL_CAN1:
   {
      SIU.PCR[42].R = 0x0603U; /*将GPIO42选择CAN1TX功能*/
      SIU.PCR[43].R = 0X0100U; /*将CAN1RX所在引脚设置为输入*/
      SIU.PSMI[0].R = 0x01U;   /*将GPIO43设置为CAN1RX*/
      CAN_1.MCR.B.MDIS = 0U;
      CAN_1.MCR.B.SOFTRST = 1U; /*软件复位*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((reset_flag == 1U) && (CAN_CurrentTime - CAN_StartTime <= CAN_OVERTIME)) /*等待复位完成*/
      {
         reset_flag = CAN_1.MCR.B.SOFTRST;
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      CAN_1.MCR.B.MDIS = 1U;                        /*禁止FLEXCAN模块以便选择时钟*/
      CAN_1.CR.B.CLKSRC = Config->CAN_Clock_Select; /*选择总线时钟作为CAN时钟：0、晶振时钟   1、总线时钟*/
      CAN_1.MCR.B.MDIS = 0U;                        /*使能FLEXCAN模块*/
      CAN_1.MCR.B.HALT = 1U;                        /*暂停CAN模块*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((CAN_1.MCR.B.FRZACK == 0U) && (CAN_CurrentTime - CAN_StartTime <= CAN_OVERTIME))
      {
         CAN_1.MCR.B.FRZ = 1U; /*进入冻结模式*/
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      CAN_1.MCR.B.BCC = 1U; /*打开单个MB屏蔽码*/
      CAN_1.MCR.B.SRXDIS = Config->SELF_Receive_Disable;
      CAN_1.MCR.B.WRNEN = 1U;                                                   /*使能警告中断*/
      CAN_1.MCR.B.IDAM = Config->ID_Accept_Mode;                                /*选择FIFO格式为FORMAT A*/
      CAN_1.MCR.B.FEN = 0U;                                                     /*关闭FIFO*/
      CAN_1.CR.B.RJW = Config->Synch_Jump_Width;                                /*设置同步跳转宽度*/
      can_set_result = Can_SetBaudrate(CAN_CHANNEL_CAN1, Config->CAN_Baund_ID); /*设置波特率*/
      CAN_1.CR.B.BOFFREC = 1U;                                                  /*关闭BUSOFF自恢复功能*/
      if (Config->USE_NUM_MB >= CAN_MAX_MB)                                     /*报文缓冲区最多只能设置64个*/
      {
         Config->USE_NUM_MB = CAN_MAX_MB;
      }
      CAN_1.MCR.B.MAXMB = Config->USE_NUM_MB - 1U; /*设置使用的报文缓冲区个数*/
      for (x = 0U; x < Config->USE_NUM_MB; x++)
      {
         CAN_1.BUF[x].CS.R = 0U;   /*清空BUF寄存器第一行*/
         CAN_1.BUF[x].ID.R = 0U;   /*清空BUF寄存器第二行*/
         for (i = 0U; i < 2U; i++) /*清空BUF寄存器第三四行*/
         {
            CAN_1.BUF[x].DATA.W[i] = 0U;
         }
      }
      if (can_set_result == TRUE) /*波特率设置成功*/
      {
         CAN_1.RXGMASK.R = Config->Global_MASK; /*全局掩码*/
         CAN_1.RX14MASK.R = Config->Buf14_MASK; /*14邮箱掩码*/
         CAN_1.RX15MASK.R = Config->Buf15_MASK; /*15邮箱掩码*/
      }
      CAN_1.IMRH.R = 0x00000000U; /*禁止每一个缓冲区中断*/
      CAN_1.IMRL.R = 0x00000000U;
      CAN_1.MCR.B.HALT = 0U;
      CAN_1.MCR.B.FRZ = 0U; /*退出冻结模式*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((CAN_1.MCR.B.NOTRDY == 1U) && ((CAN_CurrentTime - CAN_StartTime) <= CAN_OVERTIME)) /*等待进入正常模式,2ms超时*/
      {
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      break;
   }
   default:
   {
      break;
   }
   }
}

/*******************************************************************************
名称： Can_Write(enum CAN_Channel_NUM controller, Can_PduType PduInfo)

功能： CAN报文发送

输入：a. controller选择用来发送的CAN通道；
      b. Can_PduType类型结构体PduInfo元素：  1.canid 需要发送报文的识别码 
    									     2.RTR  设置发送报文是否为远程帧
    									     3.IDE 设置发送报文是否为扩展帧
    									     4.data[8] 要发送报文的内容
    									     5.length 所发送报文内容字节的长度
    									     6.MB_NUM 使用的报文缓冲区

输出：无

返回值：1.CAN_OK   CAN发送成功
    	2.FAULT  CAN发送失败

限制条件：以晶振频率16MHZ作为CAN时钟；
*******************************************************************************/
/**
 * @brief CAN发送函数
 * @ingroup HAL_MCU_CAN
 * @param CAN_Channel_NUM controller 发送的CAN端口: \n
 * 1.CAN_CHANNEL_CAN0 \n
 * 2.CAN_CHANNEL_CAN1 \n
 * 3.CAN_CHANNEL_CAN2 \n
 * 4.CAN_CHANNEL_CAN3 \n
 * 5.CAN_CHANNEL_CAN4 \n 
 * 6.CAN_CHANNEL_CAN5  
 * @param Can_PduType *PduInfo  需要发送的CAN信息: \n
 * 1.PduInfo.canid; 报文ID \n
 * 2.PduInfo.RTR; 远程帧标志位 1：远程帧/0：数据帧 \n
 * 3.PduInfo.IDE; 扩展帧标志位 1：扩展帧/0：标准帧 \n
 * 4.PduInfo.data[8]; 发送数据组 \n
 * 5.PduInfo.length; 数据长度 \n
 * 6.PduInfo.MB_NUM; 使用报文缓存区的编号
 * @return void
 */
uint8_t Can_Write_Self(enum CAN_Channel controller, Can_PduType_SELF *PduInfo)
{
   uint8_t CAN_Result = FAULT;
   uint32_t CAN_StartTime = 0U;
   uint32_t CAN_EndTime = 0U;
   uint32_t i = 0U;
   CAN_StartTime = TMR_SYSTEM_TIME_GetTickMs();
   CAN_EndTime = CAN_StartTime;

   if (PduInfo->LENGTH > 8U) /*检验数据长度*/
   {
      CAN_Result = FAULT;
   }

   switch (controller)
   {
   case CAN_CHANNEL_CAN0:
   {
      /* 等待上次发送结束 ,5MS超时*/
      if (1U != CAN_0.ESR.B.ACKERR)
      {
         while ((CAN_0.BUF[PduInfo->MB_NUM].CS.B.CODE == 0x0cU) && ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME))
         {
            CAN_EndTime = TMR_SYSTEM_TIME_GetTickMs();
         }
      }
      if ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME)
      {
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE = PduInfo->IDE;       /* 拓展帧还是标准帧：0、标准帧  1、扩展帧 */
         if(EXTEND_ID == CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE)
         {
        	 CAN_0.BUF[PduInfo->MB_NUM].ID.R = PduInfo->CANID;         		/* 发送的报文ID */
         }
         else if(STANDARD_ID == CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE)
         {
        	 CAN_0.BUF[PduInfo->MB_NUM].ID.B.STD_ID = PduInfo->CANID;   	/* 发送的报文ID */
         }
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.RTR = PduInfo->RTR;       /* 数据帧还是远程帧：0、数据帧   1、远程帧*/
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.LENGTH = PduInfo->LENGTH; /* 发送字节的个数*/
         for (i = 0U; i < PduInfo->LENGTH; i++)
         {
            CAN_0.BUF[PduInfo->MB_NUM].DATA.B[i] = PduInfo->DATA[i]; /*发送数据*/
         }
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.SRR = 1U;          /* Tx frame (not req'd for standard frame)*/
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.CODE = CAN_TX_MSG; /* 开始传输数据 */
         CAN_StartTime = CAN_EndTime;
         CAN_Result = CAN_OK;
      }
      else
      {
         CAN_StartTime = CAN_EndTime;
         CAN_Result = FAULT;
      }
      break;
   }

   case CAN_CHANNEL_CAN1:
   {
      /* 等待上次发送结束 */
      if (1U != CAN_1.ESR.B.ACKERR)
      {
         while ((CAN_1.BUF[PduInfo->MB_NUM].CS.B.CODE == 0x0cU) && ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME))
         {
            CAN_EndTime = TMR_SYSTEM_TIME_GetTickMs();
         }
      }
      if ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME)
      {
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE = PduInfo->IDE;       /* 拓展帧还是标准帧：0、标准帧  1、扩展帧 */
         if(EXTEND_ID == CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE)
         {
        	 CAN_1.BUF[PduInfo->MB_NUM].ID.R = PduInfo->CANID;         		/* 发送的报文ID */
         }
         else if(STANDARD_ID == CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE)
         {
        	 CAN_1.BUF[PduInfo->MB_NUM].ID.B.STD_ID = PduInfo->CANID;   	/* 发送的报文ID */
         }
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.RTR = PduInfo->RTR;       /* 数据帧还是远程帧：0、数据帧   1、远程帧*/
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.LENGTH = PduInfo->LENGTH; /* 发送字节的个数*/
         for (i = 0U; i < PduInfo->LENGTH; i++)
         {
            CAN_1.BUF[PduInfo->MB_NUM].DATA.B[i] = PduInfo->DATA[i]; /*发送数据*/
         }
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.SRR = 1U;          /* Tx frame (not req'd for standard frame)*/
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.CODE = CAN_TX_MSG; /* 开始传输数据 */
         CAN_StartTime = CAN_EndTime;
         CAN_Result = CAN_OK;
      }
      else
      {
         CAN_StartTime = CAN_EndTime;
         CAN_Result = FAULT;
      }
      break;
   }
   default:
   {
      CAN_Result = FAULT;
      break;
   }
   }
   return CAN_Result;
}

/*******************************************************************************
名称： Can_SetRxBuffer(enum CAN_Channel_NUM controller, RXMB_ConfigType *Config)

功能： 设置接收缓存

输入： RXMB_ConfigType类型结构体Config元素：1.canid 接收的报文ID
                                            2.IDE   扩展帧标志位 1：扩展帧/0：标准帧
                                            3.MB_NUM 使用报文缓存区的编号
                                            4.MASK    私有掩码    
                                            5.IRQ     是否接收中断 
输出：无

返回值：无

限制条件：以晶振频率16MHZ作为CAN时钟；
*******************************************************************************/
/**
 * @brief CAN接收缓存设置
 * @ingroup HAL_MCU_CAN
 * @param CAN_Channel_NUM controller 设置的CAN端口: \n
 * 1.CAN_CHANNEL_CAN0 \n
 * 2.CAN_CHANNEL_CAN1 \n
 * 3.CAN_CHANNEL_CAN2 \n
 * 4.CAN_CHANNEL_CAN3 \n
 * 5.CAN_CHANNEL_CAN4 \n 
 * 6.CAN_CHANNEL_CAN5  
 * @param RXMB_ConfigType *Config 接收缓存设置参数: \n
 * 1.Config.canid; 接收的报文ID \n
 * 2.Config.IDE; 扩展帧标志位 1：扩展帧/0：标准帧 \n
 * 3.Config.MB_NUM; 使用报文缓存区的编号 \n
 * 4.Config.MASK; 私有掩码 \n
 * 5.Config.IRQ; 是否中断 
 * @return void
 */
void Can_SetBuffer(enum CAN_Channel controller, MB_ConfigType *Config)
{
   uint32_t CAN_StartTime = 0U;
   uint32_t CAN_EndTime = 0U;
   CAN_StartTime = TMR_SYSTEM_TIME_GetTickMs();
   CAN_EndTime = CAN_StartTime;
   switch (controller)
   {
   case CAN_CHANNEL_CAN0:
   {
      CAN_0.MCR.B.HALT = 1U;                                                                /*暂停CAN模块*/
      while ((CAN_0.MCR.B.FRZACK == 0U) && ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME)) /*等待进入冻结模式，非常重要，不能删除*/
      {
         CAN_0.MCR.B.FRZ = 1U; /*进入冻结模式*/
         CAN_EndTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      if (TRUE == Config->RX_FLAG)
      {
         CAN_0.RXIMR[Config->MB_NUM].R = Config->MASK;     /*设置接收邮箱掩码*/
         CAN_0.BUF[Config->MB_NUM].CS.B.IDE = Config->IDE; /*设置为扩展帧格式还是标准帧*/
         if(EXTEND_ID == CAN_0.BUF[Config->MB_NUM].CS.B.IDE)
         {
        	 CAN_0.BUF[Config->MB_NUM].ID.R = Config->CANID;   /*设置对应邮箱ID*/
         }
         else if(STANDARD_ID == CAN_0.BUF[Config->MB_NUM].CS.B.IDE)
         {
        	 CAN_0.BUF[Config->MB_NUM].ID.B.STD_ID = Config->CANID;   /*设置对应邮箱ID*/
         }
      }
      if (Config->IRQ == 1U) /*设置对应中断*/
      {
         if (Config->MB_NUM < 32U)
         {
            CAN_0.IMRL.R |= (1U << Config->MB_NUM);
         }
         else
         {
            CAN_0.IMRH.R |= (1U << (Config->MB_NUM - 32U)); /*当大于31时设置高标志位*/
         }
      }
      else
      {
         if (Config->MB_NUM < 32U)
         {
            CAN_0.IMRL.R &= ~(1U << Config->MB_NUM);
         }
         else
         {
            CAN_0.IMRH.R &= ~(1U << (Config->MB_NUM - 32U)); /*当大于31时设置高标志位*/
         }
      }
      CAN_0.BUF[Config->MB_NUM].CS.B.CODE = CAN_RX_EMPTY; /* 设置缓存为空 */
      CAN_0.MCR.B.FRZ = 0U;                               /*退出冻结模式*/
      CAN_0.MCR.B.HALT = 0U;                              /*取消暂停CAN模块*/
      break;
   }

   case CAN_CHANNEL_CAN1:
   {
      CAN_1.MCR.B.HALT = 1U;                                                                /*暂停CAN模块*/
      while ((CAN_1.MCR.B.FRZACK == 0U) && ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME)) /*等待进入冻结模式，非常重要，不能删除*/
      {
         CAN_1.MCR.B.FRZ = 1U; /*进入冻结模式*/
         CAN_EndTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      if (TRUE == Config->RX_FLAG)
      {
         CAN_1.RXIMR[Config->MB_NUM].R = Config->MASK;     /*设置接收邮箱掩码*/
         CAN_1.BUF[Config->MB_NUM].CS.B.IDE = Config->IDE; /*设置为扩展帧格式还是标准帧*/
         if(EXTEND_ID == CAN_1.BUF[Config->MB_NUM].CS.B.IDE)
         {
        	 CAN_1.BUF[Config->MB_NUM].ID.R = Config->CANID;   /*设置对应邮箱ID*/
         }
         else if(STANDARD_ID == CAN_1.BUF[Config->MB_NUM].CS.B.IDE)
         {
        	 CAN_1.BUF[Config->MB_NUM].ID.B.STD_ID = Config->CANID;   /*设置对应邮箱ID*/
         }
      }
      if (Config->IRQ == 1U) /*设置对应中断*/
      {
         if (Config->MB_NUM < 32U)
         {
            CAN_1.IMRL.R |= (1U << Config->MB_NUM);
         }
         else
         {
            CAN_1.IMRH.R |= (1U << (Config->MB_NUM - 32U)); /*当大于31时设置高标志位*/
         }
      }
      else
      {
         if (Config->MB_NUM < 32U)
         {
            CAN_1.IMRL.R &= ~(1U << Config->MB_NUM);
         }
         else
         {
            CAN_1.IMRH.R &= ~(1U << (Config->MB_NUM - 32U)); /*当大于31时设置高标志位*/
         }
      }
      CAN_1.BUF[Config->MB_NUM].CS.B.CODE = CAN_RX_EMPTY; /* 设置缓存为空 */
      CAN_1.MCR.B.FRZ = 0U;                               /*退出冻结模式*/
      CAN_1.MCR.B.HALT = 0U;                              /*取消暂停CAN模块*/
      break;
   }
   default:
   {
      break;
   }
   }
}

/**
 * @brief CAN接收函数
 * @ingroup HAL_MCU_CAN
 * @param CAN_Channel_NUM controller 接收的CAN端口: \n
 * 1.CAN_CHANNEL_CAN0 \n
 * 2.CAN_CHANNEL_CAN1 \n
 * 3.CAN_CHANNEL_CAN2 \n
 * 4.CAN_CHANNEL_CAN3 \n
 * 5.CAN_CHANNEL_CAN4 \n 
 * 6.CAN_CHANNEL_CAN5  
 * @param Can_PduType *PduInfo ：接收的数据
 * 1.PduInfo.canid; 报文ID \n
 * 2.PduInfo.RTR; 远程帧标志位 1：远程帧/0：数据帧 \n
 * 3.PduInfo.IDE; 扩展帧标志位 1：扩展帧/0：标准帧 \n
 * 4.PduInfo.data[8]; 发送数据组 \n
 * 5.PduInfo.length; 数据长度 \n
 * 6.PduInfo.MB_NUM; 使用报文缓存区的编号
 * @return 1.TRUE   CAN读成功 
           2.FALSE  CAN读失败
 */
uint8_t Can_Read(enum CAN_Channel controller, Can_PduType_SELF *PduInfo)
{
   uint32_t byte_num = 0U;
   u32 RxCODE = 0U;
   bool CAN_READ_Result = FALSE;
   u32 dumy = 0U;
   switch (controller)
   {
   case CAN_CHANNEL_CAN0:
   {
      RxCODE = CAN_0.BUF[PduInfo->MB_NUM].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP */

      if (CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE == STANDARD_ID) /*判断接收的报文是否标准帧*/
      {
         PduInfo->IDE = STANDARD_ID;
         PduInfo->CANID = CAN_0.BUF[PduInfo->MB_NUM].ID.B.STD_ID; /*读取报文ID*/
         if (CAN_0.BUF[PduInfo->MB_NUM].CS.B.RTR == 1U)    /*判断是否远程帧*/
         {
            PduInfo->RTR = REMOTE_FORMAT;
         }
         else
         {
            PduInfo->RTR = DATA_FORMAT;
         }
         PduInfo->LENGTH = CAN_0.BUF[PduInfo->MB_NUM].CS.B.LENGTH; /*读取报文长度*/
         for (byte_num = 0U; byte_num < PduInfo->LENGTH; byte_num++)
         {
            PduInfo->DATA[byte_num] = CAN_0.BUF[PduInfo->MB_NUM].DATA.B[byte_num]; /* 获取接收的数据*/
         }
      }
      if (CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE == EXTEND_ID) /*判断接收的报文是否扩展帧*/
      {
         PduInfo->IDE = EXTEND_ID;
         PduInfo->CANID = CAN_0.BUF[PduInfo->MB_NUM].ID.R; /*读取报文ID*/
         if (CAN_0.BUF[PduInfo->MB_NUM].CS.B.RTR == 1U)    /*判断是否远程帧*/
         {
            PduInfo->RTR = REMOTE_FORMAT;
         }
         else
         {
            PduInfo->RTR = DATA_FORMAT;
         }
         PduInfo->LENGTH = CAN_0.BUF[PduInfo->MB_NUM].CS.B.LENGTH; /*读取报文长度*/
         for (byte_num = 0U; byte_num < PduInfo->LENGTH; byte_num++)
         {
            PduInfo->DATA[byte_num] = CAN_0.BUF[PduInfo->MB_NUM].DATA.B[byte_num]; /* 获取接收的数据*/
         }
      }
      dumy = CAN_0.TIMER.R; /*解锁邮箱*/
      CAN_READ_Result = TRUE;
      break;
   }
   case CAN_CHANNEL_CAN1:
   {
      RxCODE = CAN_1.BUF[PduInfo->MB_NUM].CS.B.CODE;          /* Read CODE, ID, LENGTH, DATA, TIMESTAMP */
      if (CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE == STANDARD_ID) /*判断接收的报文是否标准帧*/
      {
         PduInfo->IDE = STANDARD_ID;
         PduInfo->CANID = CAN_1.BUF[PduInfo->MB_NUM].ID.B.STD_ID; /*读取报文ID*/
         if (CAN_1.BUF[PduInfo->MB_NUM].CS.B.RTR == 1U)    /*判断是否远程帧*/
         {
            PduInfo->RTR = REMOTE_FORMAT;
         }
         else
         {
            PduInfo->RTR = DATA_FORMAT;
         }
         PduInfo->LENGTH = CAN_1.BUF[PduInfo->MB_NUM].CS.B.LENGTH; /*读取报文长度*/
         for (byte_num = 0U; byte_num < PduInfo->LENGTH; byte_num++)
         {
            PduInfo->DATA[byte_num] = CAN_1.BUF[PduInfo->MB_NUM].DATA.B[byte_num]; /* 获取接收的数据*/
         }
      }
      if (CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE == EXTEND_ID) /*判断接收的报文是否扩展帧*/
      {
         PduInfo->IDE = EXTEND_ID;
         PduInfo->CANID = CAN_1.BUF[PduInfo->MB_NUM].ID.R; /*读取报文ID*/
         if (CAN_1.BUF[PduInfo->MB_NUM].CS.B.RTR == 1U)    /*判断是否远程帧*/
         {
            PduInfo->RTR = REMOTE_FORMAT;
         }
         else
         {
            PduInfo->RTR = DATA_FORMAT;
         }
         PduInfo->LENGTH = CAN_1.BUF[PduInfo->MB_NUM].CS.B.LENGTH; /*读取报文长度*/
         for (byte_num = 0U; byte_num < PduInfo->LENGTH; byte_num++)
         {
            PduInfo->DATA[byte_num] = CAN_1.BUF[PduInfo->MB_NUM].DATA.B[byte_num]; /* 获取接收的数据*/
         }
      }
      dumy = CAN_1.TIMER.R; /*解锁邮箱*/
      CAN_READ_Result = TRUE;
      break;
   }
   default:
   {
      CAN_READ_Result = FALSE;
      break;
   }
   }
   return CAN_READ_Result;
}

/******************************************************************************************
名称：void Can_Stop(void)

功能：停止CAN模块

输入： 无

输出：无

返回值：无

限制条件：

********************************************************************************************/
void Can_Stop(void)
{
   CAN_0.MCR.B.FEN = 0U;  /*关闭FIFO*/
   CAN_0.MCR.B.HALT = 1U; /*暂停CAN模块*/
   CAN_0.MCR.B.MDIS = 1U; /*关闭FLEXCAN模块*/
}

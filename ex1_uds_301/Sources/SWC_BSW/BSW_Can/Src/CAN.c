/**
 * @file CAN.c FLEXCANģ��Դ�ļ�
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

#define CAN_MAX_MB 64U /*���Ļ�����������*/

#define CAN_TX_MSG (0x0CU)           /*���䱨��*/
#define CAN_RX_EMPTY (0x04U)         /*����RX����Ϊ��*/
#define TX_CODE_INACTIVE (0x8U)      /*TX������δ������*/
#define RX_CODE_INACTIVE (0x0U)      /*RX������δ������*/


#define TX_CODE_SUCCESS_RTR1 (0x04U) /*RTRΪ1ʱ���ͳɹ���CODE�ķ���ֵ*/
#define TX_CODE_SUCCESS_RTR0 (0x08U) /*RTRΪ0ʱ���ͳɹ���CODE�ķ���ֵ*/

#define CAN_OVERTIME (2U)

void Can_vidInit(void)
{
	CAN_CFG_Sel(CAN_CHANNEL_CAN0, CAN_CHANNEL_CAN0);
	FWS_CAN_STACK_Init();
	FWS_CAN_STACK_InitSel(CAN_CHANNEL_CAN0, CAN_CHANNEL_CAN0);
	CanSM_Init();/*BUSOFF��ʼ��*/ 
}

/**
 * @brief CAN���ò�����
 * @ingroup HAL_MCU_CAN
 * @param CAN_Channel_NUM controller ���õ�CAN�˿ڣ� \n    
 * 1.CAN_CHANNEL_CAN0 \n
 * 2.CAN_CHANNEL_CAN1 \n
 * 3.CAN_CHANNEL_CAN2 \n
 * 4.CAN_CHANNEL_CAN3 \n
 * 5.CAN_CHANNEL_CAN4 \n 
 * 6.CAN_CHANNEL_CAN5  
 * @param CAN_Baud_Type BaudRateConfigID  ���õĲ�����ID��\n
 * 1.CAN_BOUD_RATE_250KB \n
 * 2.CAN_BOUD_RATE_500KB \n
 * 3.CAN_BOUD_RATE_1M 
 * @return 0:����ʧ�� \n 1:���óɹ�
 * ����������1.�����໷Ƶ��64MHZ��ΪCANʱ�ӣ� 
          2.�����ڶ���ģʽ�²������ã� 
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
         CAN_0.CR.B.PRESDIV = 15U; /*������= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_0.CR.B.PSEG1 = 4U;
         CAN_0.CR.B.PSEG2 = 4U;
         CAN_0.CR.B.PROPSEG = 4U;
      }
      else if (BaudRateConfigID == CAN_BOUD_RATE_500KB)
      {
         CAN_0.CR.B.PRESDIV = 7U; /*������= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_0.CR.B.PSEG1 = 4U;
         CAN_0.CR.B.PSEG2 = 4U;
         CAN_0.CR.B.PROPSEG = 4U;
      }
      else if (BaudRateConfigID == CAN_BOUD_RATE_1M)
      {
         CAN_0.CR.B.PRESDIV = 3U; /*������= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
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
         CAN_1.CR.B.PRESDIV = 15U; /*������= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_1.CR.B.PSEG1 = 4U;
         CAN_1.CR.B.PSEG2 = 4U;
         CAN_1.CR.B.PROPSEG = 4U;
      }
      else if (BaudRateConfigID == CAN_BOUD_RATE_500KB)
      {
         CAN_1.CR.B.PRESDIV = 7U; /*������= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
         CAN_1.CR.B.PSEG1 = 4U;
         CAN_1.CR.B.PSEG2 = 4U;
         CAN_1.CR.B.PROPSEG = 4U;
      }
      else if (BaudRateConfigID == CAN_BOUD_RATE_1M)
      {
         CAN_1.CR.B.PRESDIV = 3U; /*������= CANCLK/(PRESDIV+1)/(1+PSEG1+1+PSEG2+1+PROPSEG+1)*/
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
 * @brief CAN��ʼ������
 * @ingroup HAL_MCU_CAN
 * @param CAN_ConfigType Config  ��ʼ�����ò�����\n
 * 1.Config.CAN_CHANNEL_ID ��Ҫ������CAN�˿�  \n
 * 2.Config.CAN_Baund_ID  ���õĲ����� \n
 * 3.Config.Synch_Jump_Width ���õ�ͬ����ת��� \n
 * 4.Config.CAN_Clock_Select ѡ��CANʱ�� \n
 * 5.Config.CAN_ACCEPT_AR ���ý����� \n
 * 6.Config.Global_MASK;    ȫ������ \n
 * 7.Config.Buf14_MASK;      14�������� \n
 * 8.Config.Buf15_MASK;      15�������� \n
 * 9.Config.CAN_Filter_Type �����˲������� \n
 * 10.Config.SELF_Receive_Disable  �����Ƿ��Խ��� 0���Խ���   1�����Խ���
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
      SIU.PCR[16].R = 0x0603U; /*ѡ��CAN0TX����*/
      SIU.PCR[17].R = 0X0100U; /*��CAN0RX������������Ϊ����*/
      CAN_0.MCR.B.MDIS = 0U;
      CAN_0.MCR.B.SOFTRST = 1U; /*�����λ*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((reset_flag == 1U) && (CAN_CurrentTime - CAN_StartTime <= CAN_OVERTIME)) /*�ȴ���λ���*/
      {
         reset_flag = CAN_0.MCR.B.SOFTRST;
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      CAN_0.MCR.B.MDIS = 1U;                        /*��ֹFLEXCANģ���Ա�ѡ��ʱ��*/
      CAN_0.CR.B.CLKSRC = Config->CAN_Clock_Select; /*ѡ������ʱ����ΪCANʱ�ӣ�0������ʱ��   1������ʱ��*/
      CAN_0.CR.B.BOFFREC = 1U;                      /*�ر�BUSOFF�Իָ�����*/
      CAN_0.MCR.B.MDIS = 0U;                        /*ʹ��FLEXCANģ��*/
      CAN_0.MCR.B.HALT = 1U;                        /*��ͣCANģ��*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((CAN_0.MCR.B.FRZACK == 0U) && (CAN_CurrentTime - CAN_StartTime <= CAN_OVERTIME))
      {
         CAN_0.MCR.B.FRZ = 1U; /*���붳��ģʽ*/
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      CAN_0.MCR.B.BCC = 1U; /*�򿪵���MB������*/
      CAN_0.MCR.B.SRXDIS = Config->SELF_Receive_Disable;
      CAN_0.MCR.B.WRNEN = 1U;                                                   /*ʹ�ܾ����ж�*/
      CAN_0.MCR.B.IDAM = Config->ID_Accept_Mode;                                /*ѡ��FIFO��ʽΪFORMAT A*/
      CAN_0.MCR.B.FEN = 0U;                                                     /*�ر�FIFO*/
      CAN_0.CR.B.RJW = Config->Synch_Jump_Width;                                /*����ͬ����ת���*/
      can_set_result = Can_SetBaudrate(CAN_CHANNEL_CAN0, Config->CAN_Baund_ID); /*���ò�����*/
      if (Config->USE_NUM_MB >= CAN_MAX_MB)                                     /*���Ļ��������ֻ������64��*/
      {
         Config->USE_NUM_MB = CAN_MAX_MB;
      }
      CAN_0.MCR.B.MAXMB = Config->USE_NUM_MB - 1U; /*����ʹ�õı��Ļ���������*/
      for (x = 0U; x < Config->USE_NUM_MB; x++)
      {
         CAN_0.BUF[x].CS.R = 0U;   /*���BUF�Ĵ�����һ��*/
         CAN_0.BUF[x].ID.R = 0U;   /*���BUF�Ĵ����ڶ���*/
         for (i = 0U; i < 2U; i++) /*���BUF�Ĵ�����������*/
         {
            CAN_0.BUF[x].DATA.W[i] = 0U;
         }
      }
      if (can_set_result == TRUE) /*���������óɹ�*/
      {
         CAN_0.RXGMASK.R = Config->Global_MASK; /*ȫ������*/
         CAN_0.RX14MASK.R = Config->Buf14_MASK; /*14��������*/
         CAN_0.RX15MASK.R = Config->Buf15_MASK; /*15��������*/
      }
      CAN_0.IMRH.R = 0x00000000U; /*��ֹÿһ���������ж�*/
      CAN_0.IMRL.R = 0x00000000U;
      CAN_0.MCR.B.HALT = 0U;
      CAN_0.MCR.B.FRZ = 0U; /*�˳�����ģʽ*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((CAN_0.MCR.B.NOTRDY == 1U) && ((CAN_CurrentTime - CAN_StartTime) <= CAN_OVERTIME)) /*�ȴ���������ģʽ,2ms��ʱ*/
      {
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      break;
   }
   case CAN_CHANNEL_CAN1:
   {
      SIU.PCR[42].R = 0x0603U; /*��GPIO42ѡ��CAN1TX����*/
      SIU.PCR[43].R = 0X0100U; /*��CAN1RX������������Ϊ����*/
      SIU.PSMI[0].R = 0x01U;   /*��GPIO43����ΪCAN1RX*/
      CAN_1.MCR.B.MDIS = 0U;
      CAN_1.MCR.B.SOFTRST = 1U; /*�����λ*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((reset_flag == 1U) && (CAN_CurrentTime - CAN_StartTime <= CAN_OVERTIME)) /*�ȴ���λ���*/
      {
         reset_flag = CAN_1.MCR.B.SOFTRST;
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      CAN_1.MCR.B.MDIS = 1U;                        /*��ֹFLEXCANģ���Ա�ѡ��ʱ��*/
      CAN_1.CR.B.CLKSRC = Config->CAN_Clock_Select; /*ѡ������ʱ����ΪCANʱ�ӣ�0������ʱ��   1������ʱ��*/
      CAN_1.MCR.B.MDIS = 0U;                        /*ʹ��FLEXCANģ��*/
      CAN_1.MCR.B.HALT = 1U;                        /*��ͣCANģ��*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((CAN_1.MCR.B.FRZACK == 0U) && (CAN_CurrentTime - CAN_StartTime <= CAN_OVERTIME))
      {
         CAN_1.MCR.B.FRZ = 1U; /*���붳��ģʽ*/
         CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      CAN_1.MCR.B.BCC = 1U; /*�򿪵���MB������*/
      CAN_1.MCR.B.SRXDIS = Config->SELF_Receive_Disable;
      CAN_1.MCR.B.WRNEN = 1U;                                                   /*ʹ�ܾ����ж�*/
      CAN_1.MCR.B.IDAM = Config->ID_Accept_Mode;                                /*ѡ��FIFO��ʽΪFORMAT A*/
      CAN_1.MCR.B.FEN = 0U;                                                     /*�ر�FIFO*/
      CAN_1.CR.B.RJW = Config->Synch_Jump_Width;                                /*����ͬ����ת���*/
      can_set_result = Can_SetBaudrate(CAN_CHANNEL_CAN1, Config->CAN_Baund_ID); /*���ò�����*/
      CAN_1.CR.B.BOFFREC = 1U;                                                  /*�ر�BUSOFF�Իָ�����*/
      if (Config->USE_NUM_MB >= CAN_MAX_MB)                                     /*���Ļ��������ֻ������64��*/
      {
         Config->USE_NUM_MB = CAN_MAX_MB;
      }
      CAN_1.MCR.B.MAXMB = Config->USE_NUM_MB - 1U; /*����ʹ�õı��Ļ���������*/
      for (x = 0U; x < Config->USE_NUM_MB; x++)
      {
         CAN_1.BUF[x].CS.R = 0U;   /*���BUF�Ĵ�����һ��*/
         CAN_1.BUF[x].ID.R = 0U;   /*���BUF�Ĵ����ڶ���*/
         for (i = 0U; i < 2U; i++) /*���BUF�Ĵ�����������*/
         {
            CAN_1.BUF[x].DATA.W[i] = 0U;
         }
      }
      if (can_set_result == TRUE) /*���������óɹ�*/
      {
         CAN_1.RXGMASK.R = Config->Global_MASK; /*ȫ������*/
         CAN_1.RX14MASK.R = Config->Buf14_MASK; /*14��������*/
         CAN_1.RX15MASK.R = Config->Buf15_MASK; /*15��������*/
      }
      CAN_1.IMRH.R = 0x00000000U; /*��ֹÿһ���������ж�*/
      CAN_1.IMRL.R = 0x00000000U;
      CAN_1.MCR.B.HALT = 0U;
      CAN_1.MCR.B.FRZ = 0U; /*�˳�����ģʽ*/
      CAN_CurrentTime = TMR_SYSTEM_TIME_GetTickMs();
      CAN_StartTime = CAN_CurrentTime;
      while ((CAN_1.MCR.B.NOTRDY == 1U) && ((CAN_CurrentTime - CAN_StartTime) <= CAN_OVERTIME)) /*�ȴ���������ģʽ,2ms��ʱ*/
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
���ƣ� Can_Write(enum CAN_Channel_NUM controller, Can_PduType PduInfo)

���ܣ� CAN���ķ���

���룺a. controllerѡ���������͵�CANͨ����
      b. Can_PduType���ͽṹ��PduInfoԪ�أ�  1.canid ��Ҫ���ͱ��ĵ�ʶ���� 
    									     2.RTR  ���÷��ͱ����Ƿ�ΪԶ��֡
    									     3.IDE ���÷��ͱ����Ƿ�Ϊ��չ֡
    									     4.data[8] Ҫ���ͱ��ĵ�����
    									     5.length �����ͱ��������ֽڵĳ���
    									     6.MB_NUM ʹ�õı��Ļ�����

�������

����ֵ��1.CAN_OK   CAN���ͳɹ�
    	2.FAULT  CAN����ʧ��

�����������Ծ���Ƶ��16MHZ��ΪCANʱ�ӣ�
*******************************************************************************/
/**
 * @brief CAN���ͺ���
 * @ingroup HAL_MCU_CAN
 * @param CAN_Channel_NUM controller ���͵�CAN�˿�: \n
 * 1.CAN_CHANNEL_CAN0 \n
 * 2.CAN_CHANNEL_CAN1 \n
 * 3.CAN_CHANNEL_CAN2 \n
 * 4.CAN_CHANNEL_CAN3 \n
 * 5.CAN_CHANNEL_CAN4 \n 
 * 6.CAN_CHANNEL_CAN5  
 * @param Can_PduType *PduInfo  ��Ҫ���͵�CAN��Ϣ: \n
 * 1.PduInfo.canid; ����ID \n
 * 2.PduInfo.RTR; Զ��֡��־λ 1��Զ��֡/0������֡ \n
 * 3.PduInfo.IDE; ��չ֡��־λ 1����չ֡/0����׼֡ \n
 * 4.PduInfo.data[8]; ���������� \n
 * 5.PduInfo.length; ���ݳ��� \n
 * 6.PduInfo.MB_NUM; ʹ�ñ��Ļ������ı��
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

   if (PduInfo->LENGTH > 8U) /*�������ݳ���*/
   {
      CAN_Result = FAULT;
   }

   switch (controller)
   {
   case CAN_CHANNEL_CAN0:
   {
      /* �ȴ��ϴη��ͽ��� ,5MS��ʱ*/
      if (1U != CAN_0.ESR.B.ACKERR)
      {
         while ((CAN_0.BUF[PduInfo->MB_NUM].CS.B.CODE == 0x0cU) && ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME))
         {
            CAN_EndTime = TMR_SYSTEM_TIME_GetTickMs();
         }
      }
      if ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME)
      {
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE = PduInfo->IDE;       /* ��չ֡���Ǳ�׼֡��0����׼֡  1����չ֡ */
         if(EXTEND_ID == CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE)
         {
        	 CAN_0.BUF[PduInfo->MB_NUM].ID.R = PduInfo->CANID;         		/* ���͵ı���ID */
         }
         else if(STANDARD_ID == CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE)
         {
        	 CAN_0.BUF[PduInfo->MB_NUM].ID.B.STD_ID = PduInfo->CANID;   	/* ���͵ı���ID */
         }
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.RTR = PduInfo->RTR;       /* ����֡����Զ��֡��0������֡   1��Զ��֡*/
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.LENGTH = PduInfo->LENGTH; /* �����ֽڵĸ���*/
         for (i = 0U; i < PduInfo->LENGTH; i++)
         {
            CAN_0.BUF[PduInfo->MB_NUM].DATA.B[i] = PduInfo->DATA[i]; /*��������*/
         }
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.SRR = 1U;          /* Tx frame (not req'd for standard frame)*/
         CAN_0.BUF[PduInfo->MB_NUM].CS.B.CODE = CAN_TX_MSG; /* ��ʼ�������� */
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
      /* �ȴ��ϴη��ͽ��� */
      if (1U != CAN_1.ESR.B.ACKERR)
      {
         while ((CAN_1.BUF[PduInfo->MB_NUM].CS.B.CODE == 0x0cU) && ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME))
         {
            CAN_EndTime = TMR_SYSTEM_TIME_GetTickMs();
         }
      }
      if ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME)
      {
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE = PduInfo->IDE;       /* ��չ֡���Ǳ�׼֡��0����׼֡  1����չ֡ */
         if(EXTEND_ID == CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE)
         {
        	 CAN_1.BUF[PduInfo->MB_NUM].ID.R = PduInfo->CANID;         		/* ���͵ı���ID */
         }
         else if(STANDARD_ID == CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE)
         {
        	 CAN_1.BUF[PduInfo->MB_NUM].ID.B.STD_ID = PduInfo->CANID;   	/* ���͵ı���ID */
         }
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.RTR = PduInfo->RTR;       /* ����֡����Զ��֡��0������֡   1��Զ��֡*/
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.LENGTH = PduInfo->LENGTH; /* �����ֽڵĸ���*/
         for (i = 0U; i < PduInfo->LENGTH; i++)
         {
            CAN_1.BUF[PduInfo->MB_NUM].DATA.B[i] = PduInfo->DATA[i]; /*��������*/
         }
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.SRR = 1U;          /* Tx frame (not req'd for standard frame)*/
         CAN_1.BUF[PduInfo->MB_NUM].CS.B.CODE = CAN_TX_MSG; /* ��ʼ�������� */
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
���ƣ� Can_SetRxBuffer(enum CAN_Channel_NUM controller, RXMB_ConfigType *Config)

���ܣ� ���ý��ջ���

���룺 RXMB_ConfigType���ͽṹ��ConfigԪ�أ�1.canid ���յı���ID
                                            2.IDE   ��չ֡��־λ 1����չ֡/0����׼֡
                                            3.MB_NUM ʹ�ñ��Ļ������ı��
                                            4.MASK    ˽������    
                                            5.IRQ     �Ƿ�����ж� 
�������

����ֵ����

�����������Ծ���Ƶ��16MHZ��ΪCANʱ�ӣ�
*******************************************************************************/
/**
 * @brief CAN���ջ�������
 * @ingroup HAL_MCU_CAN
 * @param CAN_Channel_NUM controller ���õ�CAN�˿�: \n
 * 1.CAN_CHANNEL_CAN0 \n
 * 2.CAN_CHANNEL_CAN1 \n
 * 3.CAN_CHANNEL_CAN2 \n
 * 4.CAN_CHANNEL_CAN3 \n
 * 5.CAN_CHANNEL_CAN4 \n 
 * 6.CAN_CHANNEL_CAN5  
 * @param RXMB_ConfigType *Config ���ջ������ò���: \n
 * 1.Config.canid; ���յı���ID \n
 * 2.Config.IDE; ��չ֡��־λ 1����չ֡/0����׼֡ \n
 * 3.Config.MB_NUM; ʹ�ñ��Ļ������ı�� \n
 * 4.Config.MASK; ˽������ \n
 * 5.Config.IRQ; �Ƿ��ж� 
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
      CAN_0.MCR.B.HALT = 1U;                                                                /*��ͣCANģ��*/
      while ((CAN_0.MCR.B.FRZACK == 0U) && ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME)) /*�ȴ����붳��ģʽ���ǳ���Ҫ������ɾ��*/
      {
         CAN_0.MCR.B.FRZ = 1U; /*���붳��ģʽ*/
         CAN_EndTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      if (TRUE == Config->RX_FLAG)
      {
         CAN_0.RXIMR[Config->MB_NUM].R = Config->MASK;     /*���ý�����������*/
         CAN_0.BUF[Config->MB_NUM].CS.B.IDE = Config->IDE; /*����Ϊ��չ֡��ʽ���Ǳ�׼֡*/
         if(EXTEND_ID == CAN_0.BUF[Config->MB_NUM].CS.B.IDE)
         {
        	 CAN_0.BUF[Config->MB_NUM].ID.R = Config->CANID;   /*���ö�Ӧ����ID*/
         }
         else if(STANDARD_ID == CAN_0.BUF[Config->MB_NUM].CS.B.IDE)
         {
        	 CAN_0.BUF[Config->MB_NUM].ID.B.STD_ID = Config->CANID;   /*���ö�Ӧ����ID*/
         }
      }
      if (Config->IRQ == 1U) /*���ö�Ӧ�ж�*/
      {
         if (Config->MB_NUM < 32U)
         {
            CAN_0.IMRL.R |= (1U << Config->MB_NUM);
         }
         else
         {
            CAN_0.IMRH.R |= (1U << (Config->MB_NUM - 32U)); /*������31ʱ���ø߱�־λ*/
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
            CAN_0.IMRH.R &= ~(1U << (Config->MB_NUM - 32U)); /*������31ʱ���ø߱�־λ*/
         }
      }
      CAN_0.BUF[Config->MB_NUM].CS.B.CODE = CAN_RX_EMPTY; /* ���û���Ϊ�� */
      CAN_0.MCR.B.FRZ = 0U;                               /*�˳�����ģʽ*/
      CAN_0.MCR.B.HALT = 0U;                              /*ȡ����ͣCANģ��*/
      break;
   }

   case CAN_CHANNEL_CAN1:
   {
      CAN_1.MCR.B.HALT = 1U;                                                                /*��ͣCANģ��*/
      while ((CAN_1.MCR.B.FRZACK == 0U) && ((CAN_EndTime - CAN_StartTime) <= CAN_OVERTIME)) /*�ȴ����붳��ģʽ���ǳ���Ҫ������ɾ��*/
      {
         CAN_1.MCR.B.FRZ = 1U; /*���붳��ģʽ*/
         CAN_EndTime = TMR_SYSTEM_TIME_GetTickMs();
      }
      if (TRUE == Config->RX_FLAG)
      {
         CAN_1.RXIMR[Config->MB_NUM].R = Config->MASK;     /*���ý�����������*/
         CAN_1.BUF[Config->MB_NUM].CS.B.IDE = Config->IDE; /*����Ϊ��չ֡��ʽ���Ǳ�׼֡*/
         if(EXTEND_ID == CAN_1.BUF[Config->MB_NUM].CS.B.IDE)
         {
        	 CAN_1.BUF[Config->MB_NUM].ID.R = Config->CANID;   /*���ö�Ӧ����ID*/
         }
         else if(STANDARD_ID == CAN_1.BUF[Config->MB_NUM].CS.B.IDE)
         {
        	 CAN_1.BUF[Config->MB_NUM].ID.B.STD_ID = Config->CANID;   /*���ö�Ӧ����ID*/
         }
      }
      if (Config->IRQ == 1U) /*���ö�Ӧ�ж�*/
      {
         if (Config->MB_NUM < 32U)
         {
            CAN_1.IMRL.R |= (1U << Config->MB_NUM);
         }
         else
         {
            CAN_1.IMRH.R |= (1U << (Config->MB_NUM - 32U)); /*������31ʱ���ø߱�־λ*/
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
            CAN_1.IMRH.R &= ~(1U << (Config->MB_NUM - 32U)); /*������31ʱ���ø߱�־λ*/
         }
      }
      CAN_1.BUF[Config->MB_NUM].CS.B.CODE = CAN_RX_EMPTY; /* ���û���Ϊ�� */
      CAN_1.MCR.B.FRZ = 0U;                               /*�˳�����ģʽ*/
      CAN_1.MCR.B.HALT = 0U;                              /*ȡ����ͣCANģ��*/
      break;
   }
   default:
   {
      break;
   }
   }
}

/**
 * @brief CAN���պ���
 * @ingroup HAL_MCU_CAN
 * @param CAN_Channel_NUM controller ���յ�CAN�˿�: \n
 * 1.CAN_CHANNEL_CAN0 \n
 * 2.CAN_CHANNEL_CAN1 \n
 * 3.CAN_CHANNEL_CAN2 \n
 * 4.CAN_CHANNEL_CAN3 \n
 * 5.CAN_CHANNEL_CAN4 \n 
 * 6.CAN_CHANNEL_CAN5  
 * @param Can_PduType *PduInfo �����յ�����
 * 1.PduInfo.canid; ����ID \n
 * 2.PduInfo.RTR; Զ��֡��־λ 1��Զ��֡/0������֡ \n
 * 3.PduInfo.IDE; ��չ֡��־λ 1����չ֡/0����׼֡ \n
 * 4.PduInfo.data[8]; ���������� \n
 * 5.PduInfo.length; ���ݳ��� \n
 * 6.PduInfo.MB_NUM; ʹ�ñ��Ļ������ı��
 * @return 1.TRUE   CAN���ɹ� 
           2.FALSE  CAN��ʧ��
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

      if (CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE == STANDARD_ID) /*�жϽ��յı����Ƿ��׼֡*/
      {
         PduInfo->IDE = STANDARD_ID;
         PduInfo->CANID = CAN_0.BUF[PduInfo->MB_NUM].ID.B.STD_ID; /*��ȡ����ID*/
         if (CAN_0.BUF[PduInfo->MB_NUM].CS.B.RTR == 1U)    /*�ж��Ƿ�Զ��֡*/
         {
            PduInfo->RTR = REMOTE_FORMAT;
         }
         else
         {
            PduInfo->RTR = DATA_FORMAT;
         }
         PduInfo->LENGTH = CAN_0.BUF[PduInfo->MB_NUM].CS.B.LENGTH; /*��ȡ���ĳ���*/
         for (byte_num = 0U; byte_num < PduInfo->LENGTH; byte_num++)
         {
            PduInfo->DATA[byte_num] = CAN_0.BUF[PduInfo->MB_NUM].DATA.B[byte_num]; /* ��ȡ���յ�����*/
         }
      }
      if (CAN_0.BUF[PduInfo->MB_NUM].CS.B.IDE == EXTEND_ID) /*�жϽ��յı����Ƿ���չ֡*/
      {
         PduInfo->IDE = EXTEND_ID;
         PduInfo->CANID = CAN_0.BUF[PduInfo->MB_NUM].ID.R; /*��ȡ����ID*/
         if (CAN_0.BUF[PduInfo->MB_NUM].CS.B.RTR == 1U)    /*�ж��Ƿ�Զ��֡*/
         {
            PduInfo->RTR = REMOTE_FORMAT;
         }
         else
         {
            PduInfo->RTR = DATA_FORMAT;
         }
         PduInfo->LENGTH = CAN_0.BUF[PduInfo->MB_NUM].CS.B.LENGTH; /*��ȡ���ĳ���*/
         for (byte_num = 0U; byte_num < PduInfo->LENGTH; byte_num++)
         {
            PduInfo->DATA[byte_num] = CAN_0.BUF[PduInfo->MB_NUM].DATA.B[byte_num]; /* ��ȡ���յ�����*/
         }
      }
      dumy = CAN_0.TIMER.R; /*��������*/
      CAN_READ_Result = TRUE;
      break;
   }
   case CAN_CHANNEL_CAN1:
   {
      RxCODE = CAN_1.BUF[PduInfo->MB_NUM].CS.B.CODE;          /* Read CODE, ID, LENGTH, DATA, TIMESTAMP */
      if (CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE == STANDARD_ID) /*�жϽ��յı����Ƿ��׼֡*/
      {
         PduInfo->IDE = STANDARD_ID;
         PduInfo->CANID = CAN_1.BUF[PduInfo->MB_NUM].ID.B.STD_ID; /*��ȡ����ID*/
         if (CAN_1.BUF[PduInfo->MB_NUM].CS.B.RTR == 1U)    /*�ж��Ƿ�Զ��֡*/
         {
            PduInfo->RTR = REMOTE_FORMAT;
         }
         else
         {
            PduInfo->RTR = DATA_FORMAT;
         }
         PduInfo->LENGTH = CAN_1.BUF[PduInfo->MB_NUM].CS.B.LENGTH; /*��ȡ���ĳ���*/
         for (byte_num = 0U; byte_num < PduInfo->LENGTH; byte_num++)
         {
            PduInfo->DATA[byte_num] = CAN_1.BUF[PduInfo->MB_NUM].DATA.B[byte_num]; /* ��ȡ���յ�����*/
         }
      }
      if (CAN_1.BUF[PduInfo->MB_NUM].CS.B.IDE == EXTEND_ID) /*�жϽ��յı����Ƿ���չ֡*/
      {
         PduInfo->IDE = EXTEND_ID;
         PduInfo->CANID = CAN_1.BUF[PduInfo->MB_NUM].ID.R; /*��ȡ����ID*/
         if (CAN_1.BUF[PduInfo->MB_NUM].CS.B.RTR == 1U)    /*�ж��Ƿ�Զ��֡*/
         {
            PduInfo->RTR = REMOTE_FORMAT;
         }
         else
         {
            PduInfo->RTR = DATA_FORMAT;
         }
         PduInfo->LENGTH = CAN_1.BUF[PduInfo->MB_NUM].CS.B.LENGTH; /*��ȡ���ĳ���*/
         for (byte_num = 0U; byte_num < PduInfo->LENGTH; byte_num++)
         {
            PduInfo->DATA[byte_num] = CAN_1.BUF[PduInfo->MB_NUM].DATA.B[byte_num]; /* ��ȡ���յ�����*/
         }
      }
      dumy = CAN_1.TIMER.R; /*��������*/
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
���ƣ�void Can_Stop(void)

���ܣ�ֹͣCANģ��

���룺 ��

�������

����ֵ����

����������

********************************************************************************************/
void Can_Stop(void)
{
   CAN_0.MCR.B.FEN = 0U;  /*�ر�FIFO*/
   CAN_0.MCR.B.HALT = 1U; /*��ͣCANģ��*/
   CAN_0.MCR.B.MDIS = 1U; /*�ر�FLEXCANģ��*/
}

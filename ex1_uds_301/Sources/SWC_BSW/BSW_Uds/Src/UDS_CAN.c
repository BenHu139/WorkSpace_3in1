/*
 * can.c
 *
 *  Created on: Sep 20, 2014
 *      Author: wenxc
 */

/**
 * @file CAN.c FLEXCANģ��Դ�ļ�
 * @ingroup HAL_MCU_CAN
 */
#if 1
#include "includes.h"

#include "TMR.h"
#include "CAN.h"
#include "Can_Type.h"
#include "UDS_CAN.h"


#define JYD_E_NOT_OK 0U
#define JYD_E_OK     1U

#define STANDARD_ID 0U
#define EXTEND_ID 1U

#define REMOTE_FORMAT  1U
#define DATA_FORMAT    0U


#define CAN_MAX_MB	64U	/*���Ļ�����������*/

#define CAN_TX_MSG (0x0CU)/*���䱨��*/
#define CAN_RX_EMPTY (0x04U) /*����RX����Ϊ��*/
#define TX_CODE_INACTIVE (0x8U)/*TX������δ������*/
#define RX_CODE_INACTIVE (0x0U)/*RX������δ������*/
#define TX_CODE_SUCCESS_RTR1 (0x04U)/*RTRΪ1ʱ���ͳɹ���CODE�ķ���ֵ*/
#define TX_CODE_SUCCESS_RTR0 (0x08U)/*RTRΪ0ʱ���ͳɹ���CODE�ķ���ֵ*/

#define CAN_OVERTIME       (2U) 
#define CAN_INITDELAYTIME  (2U)

/**
 * @brief CAN���ͺ���
 * @ingroup HAL_MCU_CAN
 * @param Can_HwHandleType Hth �������䣨0-383��: \n
 * 1.CAN_CHANNEL_CAN0��0-63�� \n
 * 2.CAN_CHANNEL_CAN1��64-127�� \n
 * 3.CAN_CHANNEL_CAN2��128-171��\n
 * 4.CAN_CHANNEL_CAN3��172-255�� \n
 * 5.CAN_CHANNEL_CAN4��256-319��\n 
 * 6.CAN_CHANNEL_CAN5 ��319-383�� 
 * @param Can_PduType *PduInfo  ��Ҫ���͵�CAN��Ϣ: \n
 * 1.PduInfo.swPduHandle ���ľ��
 * 2.PduInfo.id; ����ID \n
 * 3.PduInfo.sdu; �������� \n
 * 4.PduInfo.length; ���ݳ��� \n
 * @return Can_ReturnType
 */
static u8 UdsHwCanActiveChn = 0xff;
static u32 UdsCanActiveTimeOut = 0;

void Can_InitActiveChn(void)
{
    UdsHwCanActiveChn = 0xff;
}

u8 Can_GetActiveChn(void)
{
    return UdsHwCanActiveChn;
}

void Can_SetActiveChn(u8 chn)
{
    UdsHwCanActiveChn = chn;
}

void Can_RealseActiveChn(void)
{
    UdsHwCanActiveChn = 0xff;
}

void Can_RefreshActiveTimeOut(u32 Time)
{
    UdsCanActiveTimeOut = Time;
}

void DecreaseActiveTimeOut(void)
{
    if (UdsCanActiveTimeOut != 0)
    {
        UdsCanActiveTimeOut--;
    }
    else
    {
        /* �ͷż���CAN */
        UdsHwCanActiveChn = 0xff;
    }
}


Can_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{

   Can_ReturnType CAN_Result = CAN_NOT_OK;
   uint32_t CAN_StartTime = 0U;
   uint32_t CAN_EndTime = 0U;
   uint32_t i = 0U; 
   u32 controller = 0u;
   u32 buf_num = 0u;
   CAN_StartTime = TMR_SYSTEM_TIME_GetTickMs();
   CAN_EndTime = CAN_StartTime;

   if(PduInfo->length > 8U)/*�������ݳ���*/
   {
      CAN_Result = CAN_NOT_OK;
   }

   controller = Hth;
   buf_num = PduInfo->swPduHandle;
    
   switch(controller) 
   {  
      case CAN_CHANNEL_CAN0:
      {  
         if(1U != CAN_0.ESR.B.ACKERR)/*��Ӧ�����*/
         {
            if(CAN_0.BUF[buf_num].CS.B.CODE == 0x0cU)/*���治Ϊ��*/
            {
               CAN_Result = CAN_BUSY;
            }  
            else
            {
                CAN_0.BUF[buf_num].CS.B.IDE = 1u;     /* ��չ֡���Ǳ�׼֡��0����׼֡  1����չ֡ */ 
                CAN_0.BUF[buf_num].ID.R = PduInfo->id;      /* ���͵ı���ID */
                CAN_0.BUF[buf_num].CS.B.RTR = 0;    /* ����֡����Զ��֡��0������֡   1��Զ��֡*/
                CAN_0.BUF[buf_num].CS.B.LENGTH = PduInfo->length; /* �����ֽڵĸ���*/
                for (i = 0U; i < PduInfo->length; i++) 
                {
                   CAN_0.BUF[buf_num].DATA.B[i] = *(PduInfo->sdu + i);      /*��������*/
                }
                CAN_0.BUF[buf_num].CS.B.SRR = 1U;           /* Tx frame (not req'd for standard frame)*/
                CAN_0.BUF[buf_num].CS.B.CODE = CAN_TX_MSG;         /* ��ʼ�������� */ 
                CAN_Result = CAN_OK;
            }
         }  
         else
         {
            CAN_Result = CAN_NOT_OK;
         }
          break;
      }
 
      case CAN_CHANNEL_CAN1:
      {  
          if(1U != CAN_1.ESR.B.ACKERR)/*��Ӧ�����*/
          {
             if(CAN_1.BUF[buf_num].CS.B.CODE == 0x0cU)/*���治Ϊ��*/
             {
                CAN_Result = CAN_BUSY;
             }  
             else
             {
                 CAN_1.BUF[buf_num].CS.B.IDE = 1u;     /* ��չ֡���Ǳ�׼֡��0����׼֡  1����չ֡ */ 
                 CAN_1.BUF[buf_num].ID.R = PduInfo->id;      /* ���͵ı���ID */
                 CAN_1.BUF[buf_num].CS.B.RTR = 0;    /* ����֡����Զ��֡��0������֡   1��Զ��֡*/
                 CAN_1.BUF[buf_num].CS.B.LENGTH = PduInfo->length; /* �����ֽڵĸ���*/
                 for (i = 0U; i < PduInfo->length; i++) 
                 {
                    CAN_1.BUF[buf_num].DATA.B[i] = *(PduInfo->sdu + i);      /*��������*/
                 }
                 CAN_1.BUF[buf_num].CS.B.SRR = 1U;           /* Tx frame (not req'd for standard frame)*/
                 CAN_1.BUF[buf_num].CS.B.CODE = CAN_TX_MSG;         /* ��ʼ�������� */ 
                 CAN_Result = CAN_OK;
             }
          } 
          else
          {
             CAN_Result = CAN_NOT_OK;
          }
           break;
       }
      default:
      {
         CAN_Result = CAN_NOT_OK;
         break;
      }
   }
   return CAN_Result;
}
#endif

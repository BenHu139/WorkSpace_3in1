/*
 * CAN_INTC.c
 *
 *  Created on: Oct 23, 2014
 */

/**
 * @file CAN_INTC.c FLEXCAN模块中断源文件
 * @ingroup HAL_MCU_CAN
 */

#include "includes.h"         /* MCU platform development header       */
#include "CAN_INTC.h"

#include "CAN_STACK.h"
#include "CAN.h"
#include "App_Boot.h"
#include "UDS_CAN.h"
#include "CanIf_Cbk.h"
#include "UDS_CAN.h"

/************************************************************************************
名称： can_buf_00_03_interrupt_handler0(void)

功能： CAN—BUFFER 00-03的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf00_03_interrupt_handler0 (void)
{
    u8 i = 0U;
   
    Can_PduType_SELF  canmsg = {0U};
    STRU_CAN_MESSAGE stackmsg;
    
    if(CAN_0.IFRL.B.BUF00I == 1U)/*CAN0_00中断*/
    {
        canmsg.MB_NUM = 0U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
    }
    if(CAN_0.IFRL.B.BUF01I == 1U)/*CAN0_01中断*/
    {
        canmsg.MB_NUM = 1U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
    }
    if(CAN_0.IFRL.B.BUF02I == 1U)/*CAN0_02中断*/
    {
        canmsg.MB_NUM = 2U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
    }
    if(CAN_0.IFRL.B.BUF03I == 1U)/*CAN0_03中断*/
    {
        canmsg.MB_NUM = 3U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
    }   
    CAN_0.IFRL.R = 0x0000000Fu;
}
/************************************************************************************
名称： can_buf_04_07_interrupt_handler0(void)

功能： CAN—BUFFER 04-07的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf04_07_interrupt_handler0 (void)
{
    u8 i = 0U;
   
    Can_PduType_SELF  canmsg = {0U};
    STRU_CAN_MESSAGE stackmsg;
    
    if(CAN_0.IFRL.B.BUF04I == 1U)/*CAN0_04中断*/
    {
        canmsg.MB_NUM = 4U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
    }
    if(CAN_0.IFRL.B.BUF05I == 1U)/*CAN0_05中断*/
    {
        canmsg.MB_NUM = 5U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
    }
    if(CAN_0.IFRL.B.BUF06I == 1U)/*CAN0_06中断*/
    {
        canmsg.MB_NUM = 6U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
    }
    if(CAN_0.IFRL.B.BUF07I == 1U)/*CAN0_07中断*/
    {
        canmsg.MB_NUM = 7U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }       
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);      
    }   
    CAN_0.IFRL.R = 0x000000F0u;
}
/************************************************************************************
名称： can_buf_08_11_interrupt_handler0(void)

功能： CAN—BUFFER 08-11的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf08_11_interrupt_handler0 (void)
{
    u8 i = 0U;
   
    Can_PduType_SELF  canmsg = {0U};
    STRU_CAN_MESSAGE stackmsg;
    
    if(CAN_0.IFRL.B.BUF08I == 1U)/*CAN0_08中断*/
    {
        canmsg.MB_NUM = 8U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
        
    }
    if(CAN_0.IFRL.B.BUF09I == 1U)/*CAN0_09中断*/
    {
        canmsg.MB_NUM = 9U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
        
    }
    if(CAN_0.IFRL.B.BUF10I == 1U)/*CAN0_10中断*/
    {
        canmsg.MB_NUM = 10U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        if((canmsg.CANID == UDS_FUNC_ADDR_RX_ID) \
            || (canmsg.CANID == UDS_PHY_ADDR_RX_ID))
        {
			Can_SetActiveChn(CAN_CHANNEL_CAN0);
			
			Can_RefreshActiveTimeOut(UDSCAN_TIMEOUT); 
			
			CanIf_RxIndication((u16)CAN_CHANNEL_CAN0,canmsg.CANID,(u8)(canmsg.LENGTH),canmsg.DATA);
        }       
    }
    if(CAN_0.IFRL.B.BUF11I == 1U)/*CAN0_11中断*/
    {
        canmsg.MB_NUM = 11U;
        (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
    }   
    CAN_0.IFRL.R = 0x00000F00u;
}
/************************************************************************************
名称： can_buf_12_15_interrupt_handler0(void)

功能： CAN—BUFFER 12-15的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf12_15_interrupt_handler0 (void)
{
   u32 flag_reg = 0u;
   flag_reg = CAN_0.IFRL.R;
   CAN_0.IFRL.R = 0x0000F000u;
   if((flag_reg & 0x00001000U) == 0x00001000U)/*CAN0_12中断*/
   {
      FWS_CAN_STACK_CallBackTx(INTERNAL_CAN);
   }
   if((flag_reg & 0x00002000U) == 0x00002000U)/*CAN0_13中断*/
   {
        if(UDS_MCU_RSP_ID == CAN_0.BUF[13].ID.R)   
        {
            CanIf_TxConfirmation(0u);
        }
   }
   if((flag_reg & 0x00004000U) == 0x00004000U)/*CAN0_14中断*/
   {

   }
   if((flag_reg & 0x00008000U) == 0x00008000U)/*CAN0_15中断*/
   {
   }   
}
/************************************************************************************
名称： can_buf_16_31_interrupt_handler0(void)

功能： CAN—BUFFER 16-31的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf16_31_interrupt_handler0 (void)
{
	u8 i = 0U;
	   
	Can_PduType_SELF  canmsg = {0U};
	STRU_CAN_MESSAGE stackmsg;
	
   if(CAN_0.IFRL.B.BUF16I == 1U)/*CAN0_16中断*/
   {
	   canmsg.MB_NUM = 16U;
	   (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
	   
	   stackmsg.id = canmsg.CANID;
	   stackmsg.len = (u8)canmsg.LENGTH;
	   stackmsg.ide = canmsg.IDE;
	   stackmsg.rtr = canmsg.RTR;
	   
	   for(i = 0U;i < canmsg.LENGTH;i++)
	   {
		   stackmsg.buf[i] = canmsg.DATA[i];
	   }
	   
	   (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
   }
   if(CAN_0.IFRL.B.BUF17I == 1U)/*CAN0_17中断*/
   {
	   canmsg.MB_NUM = 17U;
	   (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
	   
	   stackmsg.id = canmsg.CANID;
	   stackmsg.len = (u8)canmsg.LENGTH;
	   stackmsg.ide = canmsg.IDE;
	   stackmsg.rtr = canmsg.RTR;
	   
	   for(i = 0U;i < canmsg.LENGTH;i++)
	   {
		   stackmsg.buf[i] = canmsg.DATA[i];
	   }
	   
	   (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);

   }
   if(CAN_0.IFRL.B.BUF18I == 1U)/*CAN0_18中断*/
   {
	   canmsg.MB_NUM = 18U;
	   (void)Can_Read(CAN_CHANNEL_CAN0, &canmsg);
	   
	   stackmsg.id = canmsg.CANID;
	   stackmsg.len = (u8)canmsg.LENGTH;
	   stackmsg.ide = canmsg.IDE;
	   stackmsg.rtr = canmsg.RTR;
	   
	   for(i = 0U;i < canmsg.LENGTH;i++)
	   {
		   stackmsg.buf[i] = canmsg.DATA[i];
	   }
	   
	   (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN0, &stackmsg);
   }
   if(CAN_0.IFRL.B.BUF19I == 1U)/*CAN0_19中断*/
   {

   }   
   CAN_0.IFRL.R = 0xFFFF0000u;
}

/************************************************************************************
名称： can_buf_32_63_interrupt_handler0(void)

功能： CAN—BUFFER 32-63的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf32_63_interrupt_handler0 (void)
{
    CAN_0.IFRH.R = 0xFFFFFFFFU;

}





/************************************************************************************
名称： can_buf_00_03_interrupt_handler1(void)

功能： CAN—BUFFER 00-03的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf00_03_interrupt_handler1 (void)
{
    uint32_t i = 0U;

    
    Can_PduType_SELF  canmsg = {0U};
    STRU_CAN_MESSAGE stackmsg;
    
    if(CAN_1.IFRL.B.BUF00I == 1U)/*CAN1_00中断*/
    {
        canmsg.MB_NUM = 0U;
        (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);

    }
    if(CAN_1.IFRL.B.BUF01I == 1U)/*CAN1_01中断*/
    {
        canmsg.MB_NUM = 1U;
        (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);

    }
    if(CAN_1.IFRL.B.BUF02I == 1U)/*CAN1_02中断*/
    {
        canmsg.MB_NUM = 2U;
        (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
    }
    if(CAN_1.IFRL.B.BUF03I == 1U)/*CAN1_03中断*/
    {
        canmsg.MB_NUM = 3U;
        (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
        
        stackmsg.id = canmsg.CANID;
        stackmsg.len = (u8)canmsg.LENGTH;
        stackmsg.ide = canmsg.IDE;
        stackmsg.rtr = canmsg.RTR;
        
        for(i = 0U;i < canmsg.LENGTH;i++)
        {
            stackmsg.buf[i] = canmsg.DATA[i];
        }
        
        (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);

    }   
    CAN_1.IFRL.R = 0x0000000Fu;

}
/************************************************************************************
名称： can_buf_04_07_interrupt_handler1(void)

功能： CAN—BUFFER 04-07的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf04_07_interrupt_handler1 (void)
{
    Can_PduType_SELF  canmsg = {0U};
    STRU_CAN_MESSAGE stackmsg;
    u8 i = 0U;
    
    
   if(CAN_1.IFRL.B.BUF04I == 1U)/*CAN1_04中断*/
   {
       canmsg.MB_NUM = 4U;
       (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
       
       stackmsg.id = canmsg.CANID;
       stackmsg.len = (u8)canmsg.LENGTH;
       stackmsg.ide = canmsg.IDE;
       stackmsg.rtr = canmsg.RTR;
       
       for(i = 0U;i < canmsg.LENGTH;i++)
       {
           stackmsg.buf[i] = canmsg.DATA[i];
       }
       
       (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
       
   }
   if(CAN_1.IFRL.B.BUF05I == 1U)/*CAN1_05中断*/
   {

       canmsg.MB_NUM = 5U;
       (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
       
       stackmsg.id = canmsg.CANID;
       stackmsg.len = (u8)canmsg.LENGTH;
       stackmsg.ide = canmsg.IDE;
       stackmsg.rtr = canmsg.RTR;
       
       for(i = 0U;i < canmsg.LENGTH;i++)
       {
           stackmsg.buf[i] = canmsg.DATA[i];
       }
       
       (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
   }
   if(CAN_1.IFRL.B.BUF06I == 1U)/*CAN1_06中断*/
   {
       canmsg.MB_NUM = 6U;
       (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
       
       stackmsg.id = canmsg.CANID;
       stackmsg.len = (u8)canmsg.LENGTH;
       stackmsg.ide = canmsg.IDE;
       stackmsg.rtr = canmsg.RTR;
       
       for(i = 0U;i < canmsg.LENGTH;i++)
       {
           stackmsg.buf[i] = canmsg.DATA[i];
       }
       
       (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
   }
   if(CAN_1.IFRL.B.BUF07I == 1U)/*CAN1_07中断*/
   {
       canmsg.MB_NUM = 7U;
       (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
       
       stackmsg.id = canmsg.CANID;
       stackmsg.len = (u8)canmsg.LENGTH;
       stackmsg.ide = canmsg.IDE;
       stackmsg.rtr = canmsg.RTR;
       
       for(i = 0U;i < canmsg.LENGTH;i++)
       {
           stackmsg.buf[i] = canmsg.DATA[i];
       }
       
       (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
   }   
   CAN_1.IFRL.R = 0x000000F0u;
}
/************************************************************************************
名称： can_buf_08_11_interrupt_handler1(void)

功能： CAN—BUFFER 08-11的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf08_11_interrupt_handler1 (void)
{   
   Can_PduType_SELF  canmsg = {0U};
   STRU_CAN_MESSAGE stackmsg;
   u8 i = 0U;
   
   
  if(CAN_1.IFRL.B.BUF08I == 1U)/*CAN1_04中断*/
  {
      canmsg.MB_NUM = 8U;
      (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
      
      stackmsg.id = canmsg.CANID;
      stackmsg.len = (u8)canmsg.LENGTH;
      stackmsg.ide = canmsg.IDE;
      stackmsg.rtr = canmsg.RTR;
      
      for(i = 0U;i < canmsg.LENGTH;i++)
      {
          stackmsg.buf[i] = canmsg.DATA[i];
      }
      
      (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
      
  }
  if(CAN_1.IFRL.B.BUF09I == 1U)/*CAN1_05中断*/
  {

      canmsg.MB_NUM = 9U;
      (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
      
      stackmsg.id = canmsg.CANID;
      stackmsg.len = (u8)canmsg.LENGTH;
      stackmsg.ide = canmsg.IDE;
      stackmsg.rtr = canmsg.RTR;
      
      for(i = 0U;i < canmsg.LENGTH;i++)
      {
          stackmsg.buf[i] = canmsg.DATA[i];
      }
      
      (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
  }
  if(CAN_1.IFRL.B.BUF10I == 1U)/*CAN1_06中断*/
  {
      canmsg.MB_NUM = 10U;
      (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
      
      stackmsg.id = canmsg.CANID;
      stackmsg.len = (u8)canmsg.LENGTH;
      stackmsg.ide = canmsg.IDE;
      stackmsg.rtr = canmsg.RTR;
      
      for(i = 0U;i < canmsg.LENGTH;i++)
      {
          stackmsg.buf[i] = canmsg.DATA[i];
      }
      
      (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
  }
  if(CAN_1.IFRL.B.BUF11I == 1U)/*CAN1_07中断*/
  {
      canmsg.MB_NUM = 11U;
      (void)Can_Read(CAN_CHANNEL_CAN1, &canmsg);
      
      stackmsg.id = canmsg.CANID;
      stackmsg.len = (u8)canmsg.LENGTH;
      stackmsg.ide = canmsg.IDE;
      stackmsg.rtr = canmsg.RTR;
      
      for(i = 0U;i < canmsg.LENGTH;i++)
      {
          stackmsg.buf[i] = canmsg.DATA[i];
      }
      
      (void)FWS_CAN_STACK_PutRxMsg(CAN_CHANNEL_CAN1, &stackmsg);
  }   
  CAN_1.IFRL.R = 0x00000F00u;
}
/************************************************************************************
名称： can_buf_12_15_interrupt_handler1(void)

功能： CAN—BUFFER 12-15的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf12_15_interrupt_handler1(void)
{
    u32 flag_reg = 0u;
    flag_reg = CAN_1.IFRL.R;
    CAN_1.IFRL.R = 0x0000F000u;
    if((flag_reg & 0x00001000U) == 0x00001000U)/*CAN1_12中断*/
    {
        FWS_CAN_STACK_CallBackTx(EXTERNAL_CAN);

    }
    if((flag_reg & 0x00002000U) == 0x00002000U)/*CAN1_13中断*/
    {

    }
    if((flag_reg & 0x00004000U) == 0x00004000U)/*CAN1_14中断*/
    {

    }
    if((flag_reg & 0x00008000U) == 0x00008000U)/*CAN1_15中断*/
    {

    }
}


/************************************************************************************
名称： can_buf_32_63_interrupt_handler0(void)

功能： CAN—BUFFER 32-63的中断

输入： 无

输出：无

返回值：无

限制条件：无；

修改记录：
2014-08-05
创建
***************************************************************************************/
void can_buf32_63_interrupt_handler1 (void)
{
    CAN_1.IFRH.R = 0xFFFFFFFFU;

}

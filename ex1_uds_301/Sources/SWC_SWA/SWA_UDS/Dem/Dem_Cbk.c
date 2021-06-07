/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem_Cbk.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Dem module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Dem module configuration File
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   04.03.01    26/11/2016     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/
#include "Dem_Cbk.h"
//#include "AIO.h"


/*
extern VMSCtrlPara VmsCmdPara;
extern McuFeedbackPara1 McuSendPara300h;
extern McuFeedbackPara2 McuSendPara301h;
extern McuFeedbackPara3 McuSendPara302h;
extern McuFeedbackPara4 McuSendPara310h;
extern int16 G_i16_KeyOn;*/
/*------------------------------------------------------------------------------------------------*
 * FUNCTION DEFINITIONS
 *------------------------------------------------------------------------------------------------*/
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Dem_TriggerOnEventStatusChangeCallback
* Description   : Triggers on changes of the UDS DTC status byte.
*
* Inputs        :
*     Type                 Name         Description
*     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Dem_EventIdType     EventId   Identification of an Event by assigned EventId.
*      uint8    EventStatusOld   UDS DTC status byte of event before change
*      uint8    EventStatusNew   UDS DTC status byte of event after change(
*
* Outputs       : none
*
* Limitations   : none
*
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_CallbackTriggerOnEventStatusChange(Dem_EventIdType EventId,
                                                      uint8 EventStatusOld,
                                                      uint8 EventStatusNew)
{
    (void)EventId;
    (void)EventStatusOld;
    (void)EventStatusNew;
    return E_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Dem_CallbackTriggerOnClearEventAllowed
* Description   : Triggers on DTC-deletion, which is not allowed if the out-parameter returns False..
*
* Inputs        : none
*
* Outputs       : none
*
* Limitations   : E_OK :clearance of event is allowed
                  E_NOT_OK :clearance of event is not allowed 
*
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_CallbackTriggerOnClearEventAllowed(void)
{
    return E_OK;
}

Std_ReturnType Dem_ReadDataElementFun_0xfd74(uint8 size,uint8* Buffer)  /*总电流*/
{
    uint8 ret = E_NOT_OK;
    sint32 current = 0;
    if(size > 0u)
    {
        /*总点流*/
       //current = AIO_Get_CurrentValue(CURRENT_CHAN1);
       current = current/100;
       current = current + 500; /*偏移500A*/
       if(current > 1000)
       {
          current = 1000;
       }
       else if(current < 0)
       {
          current = 0;
       }
       else
       {
          ; /*不处理*/
       }
       
       Buffer[0] = (u8)((u32)current >> 8U);
       Buffer[1] = (u8)current;
       
       ret = E_OK;
   }
   return ret;
}
Std_ReturnType Dem_ReadDataElementFun_0xfd75(uint8 size,uint8* Buffer) /*总电压*/
{
    uint8 ret = E_NOT_OK;
    uint16 voltage = 0U;
    if(size > 0u)
    {
        //AIO_GetVoltage(HV2_PN_4851_Votage,&voltage);
        voltage = voltage/10U;  
        
        Buffer[0] = (u8)((u32)voltage >> 8U);
        Buffer[1] = (u8)voltage;
        
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType Dem_ReadDataElementFun_0xfd76(uint8 size,uint8* Buffer) /*单体最高压*/
{
    uint8 ret = E_NOT_OK;
    uint16 voltage = 0U;
    
    if(size > 0u)
    {

       Buffer[0] = (u8)((u32)voltage >> 8U);
       Buffer[1] = (u8)voltage;
       
       ret = E_OK;
   }
   return ret;
}
Std_ReturnType Dem_ReadDataElementFun_0xfd77(uint8 size,uint8* Buffer) /*单体最低电压*/
{
    uint8 ret = E_NOT_OK;
    uint16 voltage = 0U;
    
    if(size > 0u)
    {
       Buffer[0] = (u8)((u32)voltage >> 8U);
       Buffer[1] = (u8)voltage;
       
       ret = E_OK;
   }
   return ret;
}

Std_ReturnType Dem_ReadDataElementFun_0xfd78(uint8 size,uint8* Buffer) /*最高温度*/
{
    uint8 ret = E_NOT_OK;
    uint8 temp = 0U;
    
    if(size > 0u)
    {                
       Buffer[0] = temp; 
       
       ret = E_OK;
   }
   return ret;
}

Std_ReturnType Dem_ReadDataElementFun_0xfd8b(uint8 size,uint8* Buffer) /*故障发生时间*/
{
    uint8 ret = E_NOT_OK;
    uint8 tmp = 0U;
    if((size > 0u) && (4U == size))
    {
 
        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Dem_ReadDataElementFun_0xfd8c(uint8 size,uint8* Buffer)/*故障停止时间*/
{
    uint8 ret = E_NOT_OK;

    uint8 tmp = 0U;
    if((size > 0u) && (4U == size))
    {
      
        ret = E_OK;
    }
    return ret;
}






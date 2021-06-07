#include "includes.h"
#include "CAN.h"
#include "CAN_CFG_SELF.h"
#include "CAN_STACK.h"
#include "CanDriver.h"
#include "CanSM.h"

/*************************************************
    Function:      CanTxFinishDetect
    Description:  
    Calls:      CanIf_TxConfirmation
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
void CanTxFinishDetect(void)
{
#if 0
    if (CAN0_TXOK)
    {
        STATR0_TXOK = 0;
        CanIf_TxConfirmation_self(0);
    }
    else if (CAN1_TXOK)
    {
        STATR1_TXOK = 0;
        CanIf_TxConfirmation_self(1);
    }
    else
    {
        ;
    }
#endif

    return;
}

/*************************************************
    Function:      CanBusOffInt
    Description:  
    Calls:      CanSM_BusOff_CallBack
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
#if (BUSOFFINT == BOF_TRUE)
void CanBusOffInt(void)
{
    if (CAN_0.ESR.B.BOFFINT == 0x01)
    {
        CAN_0.ESR.B.BOFFINT = 1;
        /* 调用busoff 回调函数 */
        CanSM_BusOff_CallBack(0);
    }
    else if (CAN_1.ESR.B.BOFFINT == 0x01)
    {
        /* 调用BUS OFF 回调函数*/
        CAN_1.ESR.B.BOFFINT = 0;
        CanSM_BusOff_CallBack(1);
    }
    else if (CAN_2.ESR.B.BOFFINT == 0x01)
    {
        CAN_2.ESR.B.BOFFINT = 0;
        CanSM_BusOff_CallBack(2);
    }
    else if (CAN_3.ESR.B.BOFFINT == 0x01)
    {
        CAN_3.ESR.B.BOFFINT = 0;
        CanSM_BusOff_CallBack(3);
    }
    else if (CAN_4.ESR.B.BOFFINT == 0x01)
    {
        CAN_4.ESR.B.BOFFINT = 0;
        CanSM_BusOff_CallBack(4);
    }
    else if (CAN_5.ESR.B.BOFFINT == 0x01)
    {
        CAN_5.ESR.B.BOFFINT = 0;
        CanSM_BusOff_CallBack(5);
    }
    else
    {
        ;
    }

    return;
}
#endif

/*************************************************
    Function:      CanHwRestart
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
void CanHwRestart(u8 ControllerId)
{
    /* 硬件自动完成重启 */
    CAN_CFG_Sel(ControllerId, ControllerId);
    FWS_CAN_STACK_InitSel(ControllerId, ControllerId);
    return;
}

/*************************************************
    Function:      CanBusOffDetect
    Description:  detect the busoff by reg.
    Calls:      
    Called By:     Can_MainFunction_BusOff 
    Input:          ControllerId
    Output:       
    Return:         
    Others:       
*************************************************/
u8 CanBusOffDetect(u8 ControllerId)
{
    u8 BusOffFlag = 0;

    switch (ControllerId)
    {
    case 0:
        if (((CAN_0.ESR.B.FLTCONF) & 0x02U) == 0x02U)
        {
            BusOffFlag = 1;
        }
        break;

    case 1:
        if (((CAN_1.ESR.B.FLTCONF) & 0x02U) == 0x02U)
        {
            BusOffFlag = 1;
        }
        break;

    case 2:
        if (((CAN_2.ESR.B.FLTCONF) & 0x02U) == 0x02U)
        {
            BusOffFlag = 1;
        }
        break;

    case 3:
        if (((CAN_3.ESR.B.FLTCONF) & 0x02U) == 0x02U)
        {
            BusOffFlag = 1;
        }
        break;

    case 4:
        if (((CAN_4.ESR.B.FLTCONF) & 0x02U) == 0x02U)
        {
            BusOffFlag = 1;
        }
        break;

    case 5:
        if (((CAN_5.ESR.B.FLTCONF) & 0x02U) == 0x02U)
        {
            BusOffFlag = 1;
        }
        break;

    default:
        break;
    }

    return BusOffFlag;
}

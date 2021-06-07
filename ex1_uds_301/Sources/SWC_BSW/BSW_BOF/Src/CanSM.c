#include "includes.h"

#include "TMR.h"
#include "CAN.h"
#include "CanSM.h"

/*************************************************/
/* Global variable definitions				     */
/*************************************************/
CanSM_NetWorkType g_CanNetWorks[CANSM_CTRL_NUM];
CanSM_WarAndComstType CanSM_WarAndComst[CANSM_CTRL_NUM];

u8 g_BusOffWarningReq[CANSM_CTRL_NUM];

u8 test_flag = 0;

/*************************************************/
/* Private variable definitions                  */
/*************************************************/
static u8 g_TxConfirState[CANSM_CTRL_NUM];
static CanSM_InitStatusType CanSM_InitState = CANSM_STATUS_UNINIT;
static u32 busoff_start_time = 0U;
static u32 busoff_current_time = 0U;

/*************************************************/
/* Function definitions 		                 */
/*************************************************/
u8 CanIf_GetTxConfirmationState(CAN_CHANNEL ControllerId);
void CanIf_TxConfirmation_Self(CAN_CHANNEL ControllerId);

void CanSM_MainFunction(void);
void Can_MainFunction_BusOff(void);
void CanSM_BusOff_CallBack(CAN_CHANNEL ControllerId);

#define BUSOFF_TIMER_5MS (5U)
/*************************************************
    Function:      CanSM_GetComState
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/

u8 CanSM_GetComState(u8 ControllerId, CanSM_ComStatuType *pComState)
{
    u8 RetResult = CanSM_E_OK;

    if (ControllerId >= CANSM_CTRL_NUM)
    {
        RetResult = IDERORR;
    }
    else
    {
        *pComState = CanSM_WarAndComst[ControllerId].CanComStatus;
        RetResult = CanSM_E_OK;
    }

    return RetResult;
}

/*************************************************
    Function:      CanSM_Bor_Check_Off
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/

u8 CanSM_GetWarnState(u8 ControllerId, u8 *pWarnState)
{
    u8 RetResult = CanSM_E_OK;

    if (ControllerId >= CANSM_CTRL_NUM)
    {
        RetResult = IDERORR;
    }
    else
    {
        *pWarnState = CanSM_WarAndComst[ControllerId].BusOffWarningReq;
    }

    return RetResult;
}

/*************************************************
    Function:      CanSM_Bor_Check_Off
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
static void CanSM_Bor_Check_Off(CAN_CHANNEL ControllerId)
{
    CanSM_NetWorkType *Network = &g_CanNetWorks[ControllerId];
    CanSM_NetConfigType *NetConfig = &CanSM_Config.pCanSM_NetConfig[ControllerId];
    if (Network->timer < 65535)
    {
        Network->timer++;
    }

    if (Network->busoffevent)
    {
        Network->busoffevent = 0;
        Network->timer = 0;
        /* test_flag = 0; */
        if (Network->count >= NetConfig->CanSMBorCounterErr)
        {
            /* SAVE DCODE */
            CanSM_WarAndComst[ControllerId].BusOffWarningReq = 1;
        }
        else
        {
            ;
        }
        /* test_flag = 1; */
        CanHwRestart(ControllerId);
        Network->BusOffCurStatus = CANSM_BR_RESTART_CC;
        CanSM_WarAndComst[ControllerId].CanComStatus = CANSM_BSM_S_UFULLCOM;
    }
#if (BOF_FALSE == CANSM_BOR_TX_CONFIRMATION_POLLING)
    else if (Network->timer >= NetConfig->CanSMBorTimeTxEnsured)
    {
        Network->count = 0;
        CanSM_WarAndComst[ControllerId].BusOffWarningReq = 0;
        Network->BusOffCurStatus = CANSM_BR_NO_BUS_OFF;
        /* test_flag = 1; */
    }
#else
    else if (CAN_TX_OK == CanIf_GetTxConfirmationState(ControllerId))
    {
        Network->count = 0;
        CanSM_WarAndComst[ControllerId].BusOffWarningReq = 0;
        Network->BusOffCurStatus = CANSM_BR_NO_BUS_OFF;
        /* test_flag = 1; */
    }
#endif
    else
    {
        ;
    }
}

/*************************************************
    Function:      CanSM_Bor_Restart_CC
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
static void CanSM_Bor_Restart_CC(CAN_CHANNEL ControllerId)
{
    CanSM_NetWorkType *Network = &g_CanNetWorks[ControllerId];

    Network->timer = 0;

    /* Restart can */
    CanHwRestart(ControllerId);
    /* test_flag = 1;*/
    Network->BusOffCurStatus = CANSM_BR_RESTART_WAIT;
}

/*************************************************
    Function:      CanSM_Bor_Restart_Wait
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
static void CanSM_Bor_Restart_Wait(CAN_CHANNEL ControllerId)
{
    CanSM_NetWorkType *Network = &g_CanNetWorks[ControllerId];
    CanSM_NetConfigType *NetConfig = &CanSM_Config.pCanSM_NetConfig[ControllerId];

    if (Network->timer < 65535)
    {
        Network->timer++;
    }

    /* test_flag = 1;*/
    if (!(CanBusOffDetect(ControllerId)))
    {
        /* test_flag = 1; */
        Network->busoffevent = 0;
        Network->BusOffCurStatus = CANSM_BR_TXOFF;
    }
    else if (Network->timer >= NetConfig->RestartTimeOut)
    {
        /* test_flag = 1; */
        Network->timer = 0;
        Network->BusOffCurStatus = CANSM_BR_RESTART_CC;
    }
    else
    {
        ;
    }
}

/*************************************************
    Function:      CanSM_TxOff_Sub
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
static void CanSM_TxOff_Sub(CAN_CHANNEL ControllerId, u16 CanSMBorTime)
{
    CanSM_NetWorkType *Network = &g_CanNetWorks[ControllerId];

    if (Network->timer >= CanSMBorTime)
    {
        Network->timer = 0;
        Network->BusOffCurStatus = CANSM_BR_CHECK;
        /* busoff counter inc */
        if (Network->count < 255)
        {
            Network->count++;
        }

        CanSM_WarAndComst[ControllerId].CanComStatus = CANSM_BSM_S_FULLCOM;
        /* test_flag = 1; */
    }
    else
    {
        ;
    }
}

/*************************************************
    Function:      CanSM_Bor_TxOff
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
static void CanSM_Bor_TxOff(CAN_CHANNEL ControllerId)
{
    CanSM_NetWorkType *NetWork = &g_CanNetWorks[ControllerId];
    CanSM_NetConfigType *NetConfig = &CanSM_Config.pCanSM_NetConfig[ControllerId];

    if (NetWork->timer < 65535U)
    {
        NetWork->timer++;
    }

    if (NetWork->count >= NetConfig->CanSMBorCounterL1ToL2)
    {
        /*  test_flag = 1; */
        CanSM_TxOff_Sub(ControllerId, NetConfig->CanSMBorTimeL2);
    }
    else
    {
        /* test_flag = 1; */
        CanSM_TxOff_Sub(ControllerId, NetConfig->CanSMBorTimeL1);
    }
}

/*************************************************
    Function:      CanSM_Bor_No_BusOff
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
static void CanSM_Bor_No_BusOff(CAN_CHANNEL ControllerId)
{
    CanSM_NetWorkType *Network = &g_CanNetWorks[ControllerId];

    if (Network->busoffevent)
    {
        Network->busoffevent = 0;
        Network->timer = 0;
        Network->BusOffCurStatus = CANSM_BR_RESTART_CC;
        CanSM_WarAndComst[ControllerId].CanComStatus = CANSM_BSM_S_UFULLCOM;
    }
}

/*************************************************
    Function:      CanSM_Init
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
************************************************/
void CanSM_Init(void)
{
    u8 cnt = 0;

    for (cnt = 0; cnt < CANSM_CTRL_NUM; cnt++)
    {
        g_CanNetWorks[cnt].BusOffCurStatus = CANSM_BR_CHECK;
        g_CanNetWorks[cnt].busoffevent = 0;
        g_CanNetWorks[cnt].count = 0;
        g_CanNetWorks[cnt].timer = 0;
        CanSM_WarAndComst[cnt].CanComStatus = CANSM_BSM_S_FULLCOM;
    }

    CanSM_InitState = CanSM_Config.CanSM_InitStatus;
    return;
}

/*************************************************
    Function:      CanSM_MainFunction
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
void CanSM_MainFunction(void)
{
    CAN_CHANNEL cnt;

    CanSM_NetWorkType *Network;

    for (cnt = CAN_CHANNEL_CAN0; cnt < CANSM_CTRL_NUM; cnt++)
    {
        Network = &g_CanNetWorks[cnt];

        switch (Network->BusOffCurStatus)
        {
        case CANSM_BR_CHECK:
            CanSM_Bor_Check_Off(cnt);
            break;

        case CANSM_BR_RESTART_CC:
            CanSM_Bor_Restart_CC(cnt);
            break;

        case CANSM_BR_RESTART_WAIT:
            CanSM_Bor_Restart_Wait(cnt);
            break;

        case CANSM_BR_TXOFF:
            CanSM_Bor_TxOff(cnt);
            break;

        case CANSM_BR_NO_BUS_OFF:
            CanSM_Bor_No_BusOff(cnt);
            break;

        default:
            break;
        }
    }
}

/*************************************************
    Function:      Can_MainFunction_BusOff
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
void Can_MainFunction_BusOff(void)
{
    CAN_CHANNEL Num = CAN_CHANNEL_CAN0;

    /* 调用底层函数检测busoff事件并 置相关标识*/
    for (Num = CAN_CHANNEL_CAN0; Num < CANSM_CTRL_NUM; Num++)
    {
        if (CanBusOffDetect(Num))
        {
            g_CanNetWorks[Num].busoffevent = 1;
        }
    }
    return;
}

/*************************************************
    Function:      CanSM_Scheduler
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
void CanSM_Scheduler(void)
{
    busoff_current_time = TMR_SYSTEM_TIME_GetTickMs();
    if ((busoff_current_time - busoff_start_time) >= BUSOFF_TIMER_5MS)
    {
#if (BUSOFFINT == BOF_FALSE)
        Can_MainFunction_BusOff();
#endif
        /* CanTxFinishDetect(); */
        CanSM_MainFunction();
        busoff_start_time = busoff_current_time;
    }
}

/*************************************************
    Function:      CanSM_BusOff_CallBack
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
void CanSM_BusOff_CallBack(CAN_CHANNEL ControllerId)
{
    /* 填充busoff 相关标识*/
    CanSM_NetWorkType *Network = &g_CanNetWorks[ControllerId];
    /* bus off事件发生 */
    Network->busoffevent = 1;
    return;
}

/*************************************************
    Function:      CanIf_GetTxConfirmationState
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
u8 CanIf_GetTxConfirmationState(CAN_CHANNEL ControllerId)
{
    return g_TxConfirState[ControllerId];
}

/*************************************************
    Function:      CanIf_TxConfirmation
    Description:  
    Calls:      
    Called By:      
    Input:          
    Output:       
    Return:         
    Others:       
*************************************************/
void CanIf_TxConfirmation_Self(CAN_CHANNEL ControllerId)
{
    g_TxConfirState[ControllerId] = CAN_TX_OK;

    return;
}

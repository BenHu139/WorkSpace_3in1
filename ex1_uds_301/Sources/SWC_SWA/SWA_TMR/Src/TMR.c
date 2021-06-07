/**
 * @file TIME.c 系统时间模块源文件
 * @ingroup TMR_SYSTEM_TIME
 */
#include "includes.h"
#include "typedefs.h"
#include "Pit.h"
#include "TMR.h"
#include <string.h>
//#include "RLT.h"
//#include "RLT_INTC.h"
//#include "uds_main_schudle.h"
//#include "rappid_utils.h"

#define TIMER_MAX_NUM (10)                  /* 最大支持10个定时器 */
#define TIMER0_LOAD_VALUE  64000U           /* 1ms */
#define TIMER0   (0u)                       /* 使用PIT0 */

TMR TmrTbl[TMR_MAX_TMR];                    /* Table of timers managed by this module             */

static u8 TmrTickCtr;

volatile static uint32_t s_u32_timer_tick_1ms = 0u;
static u8 timer_10ms_flag = 0;

static void timer_tick(void);


/**
 * 定时器初始化，完成对定时器结构的初始化
 * @ingroup TMR_SYSTEM_TIME
 * @return 无
 */
void TMR_vidInit(void)
{
    s_u32_timer_tick_1ms = 0u;
    timer_10ms_flag = 0u;
    
    Pit_SetIsrCallback(PIT_CH_0, timer_tick);              /*设置定时器中断函数指针*/
    Pit_SetTimerLoaderVal(PIT_CH_0, TIMER0_LOAD_VALUE);    /*开启定时器通道1，中断时间1ms*/
    Pit_EnableNotification(PIT_CH_0);                      /*使能定时器中断*/  
    Pit_Start(PIT_CH_0);                                   /*定时器启动*/  

    
    //软件定时器初始化
    TMR_timer_init();
}

/**
 * 获取当前定时器的tick数,基数1ms
 * @ingroup TMR_SYSTEM_TIME
 * @return  系统节拍数
 */
u32 TMR_SYSTEM_TIME_GetTickMs(void)
{
    return s_u32_timer_tick_1ms;
}

/**
 * 定时器延时函数,基数1us
 * @ingroup TMR_SYSTEM_TIME
 * @param time 延迟时间  应尽量小于20us        
 * @return  
 */
void TMR_SYSTEM_TIME_UsDelay(u32 time)
{
    u32 time1 = 0u;
    u32 time2 = 0u;
    
    //time1 = Gpt_GetCurrentCountValue(TIMER0);
    
    if(time1 != 0xffffffffu)
    {
        while(1)
        {
            //time2 = Gpt_GetCurrentCountValue(TIMER0);
            
            if(time2 >= time1)
            {
                time2 = (time1 + TIMER0_LOAD_VALUE - time2);
                time2 = time2 / 64U;
            }
            else
            {
                time2 = time1 - time2;
                time2 = time2 / 64U;
            }
            
            if(time2 > time)
            {
                break;
            }
        }
    }

       
}

/**
 * 定时器节拍，每次增加1ms
 * @ingroup SYSTIME
 * @param  无
 * @return  无
 */
static void timer_tick(void)
{
    s_u32_timer_tick_1ms++;     /* 每次递增MILLS_PER_TICKS ms */
    
    //软定时器tick signal
    TMR_timer_signal_timer();
}



/*
*********************************************************************************************************
*                                   CONFIGURE TIMER TIMEOUT FUNCTION
*
* Description : Set the user defined function when the timer expires.
* Arguments   : n         is the timer number 0..TMR_MAX_TMR-1
*               fnct      is a pointer to a function that will be executed when the timer expires
*               arg       is a pointer to an argument that is passed to 'fnct'
* Returns     : None.
*********************************************************************************************************
*/

void TMR_timer_config_function(u8 n, void (*fnct)(void), void *arg)
{
    TMR *ptmr;

    if (n < TMR_MAX_TMR)
    {
        ptmr = &TmrTbl[n];

        __DI();

        ptmr->TmrFnct = fnct; /* Store pointer to user function into timer          */

        ptmr->TmrFnctArg = arg; /* Store user's function arguments pointer            */

        __EI();
    }
}

/*
*********************************************************************************************************
*                                             CHECK TIMER
*
* Description : This function checks to see if a timer has expired
* Arguments   : n      is the timer to check
* Returns     : 0      if the timer has expired
*               TmrCtr the remaining time before the timer expires in 1/10 second
*********************************************************************************************************
*/

u32 TMR_timer_check(u8 n)
{
    u32 val;

    val = 0;
    if (n < TMR_MAX_TMR)
    {
        __DI();
        val = TmrTbl[n].TmrCtr;
        __EI();
    }
    return (val);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                     TIMER MANAGER INITIALIZATION
*
* Description : This function initializes the timer manager module.
* Arguments   : None
* Returns     : None.
*********************************************************************************************************
*/

void TMR_timer_init(void)
{
    u8 i;
    TMR *ptmr;

    ptmr = &TmrTbl[0];
    for (i = 0; i < TMR_MAX_TMR; i++)
    { /* Clear and disable all timers                       */
        ptmr->TmrEn = FALSE;
        ptmr->TmrCtr = 0;
        ptmr->Tmr_type = 0;
        ptmr->TmrInit = 0;
        ptmr->TmrFnct = NULL;
        ptmr++;
    }

    TmrTickCtr = 0;
}

/*
*********************************************************************************************************
*                                             RESET TIMER
*
* Description : This function reloads a timer with its initial value
* Arguments   : n         is the timer to reset
* Returns     : None.
*********************************************************************************************************
*/

void TMR_timer_reset(u8 n)
{
    TMR *ptmr;

    if (n < TMR_MAX_TMR)
    {
        ptmr = &TmrTbl[n];

        __DI();

        ptmr->TmrCtr = ptmr->TmrInit; /* Reload the counter                                      */

        __EI();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                        SET TIMER (SPECIFYING MINUTES, SECONDS and TENTHS)
*
* Description : Set the timer with the specified number of minutes, seconds and 1/10 seconds.  The
*               function converts the minutes, seconds and tenths into tenths.
* Arguments   : n         is the timer number 0..TMR_MAX_TMR-1
*               tmr_type, is type of timer ,0:one shot timer,1:period timer
*               min       is the number of minutes
*               sec       is the number of seconds
*               tenmss    is the number of tenmss of a second  10ms
* Returns     : None.
*********************************************************************************************************
*/

void TMR_timer_set_MST(u16 n, boolean tmr_type, u8 min, u16 sec, u32 tenmss)
{
    TMR *ptmr;
    u32 val;

    if (n < TMR_MAX_TMR)
    {
        ptmr = &TmrTbl[n];

        val = (u32)min * 6000 + (u32)sec * 100 + (u32)tenmss;

        __DI();

        ptmr->TmrInit = val;

        ptmr->TmrCtr = val;
        
        ptmr->Tmr_type = tmr_type;

        __EI();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                               SET TIMER (SPECIFYING TENTHS OF SECOND)
*
* Description : Set the timer with the specified number of 1/10 seconds.
* Arguments   : n         is the timer number 0..TMR_MAX_TMR-1
*               tmr_type, is type of timer ,0:one shot timer,1:period timer
*               mss       is the number of 1/100 second to load into the timer
* Returns     : None.
*********************************************************************************************************
*/

void TMR_timer_set_time(u8 n, boolean tmr_type,u32 tenmss)
{
    TMR *ptmr;

    if (n < TMR_MAX_TMR)
    {
        ptmr = &TmrTbl[n];

        __DI();

        ptmr->TmrInit = tenmss;

        ptmr->TmrCtr = tenmss;
        
        ptmr->Tmr_type = tmr_type;

        __EI();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                     SIGNAL TIMER MANAGER MODULE THAT A 'CLOCK TICK' HAS OCCURRED
*
* Description : This function is called by the 'clock tick' ISR on every tick.  This function is thus
*               responsible for counting the number of clock ticks per 1/100 second.  When 1/100 second
*               elapses, this function will signal the timer manager task.
* Arguments   : None.
* Returns     : None.
* Notes       : TMR_DLY_TICKS must be set to produce 1/10 second delays.  
*               This can be set to OS_TICKS_PER_SEC / 10 if you use uC/OS-II.
*********************************************************************************************************
*/

void TMR_timer_signal_timer(void)
{

    TmrTickCtr++;

    if (TmrTickCtr >= TMR_DLY_TICKS)
    {
        TmrTickCtr = 0;
        
        //10ms到，标志位置1
        timer_10ms_flag = 1;
    }
}


void TMR_SYSTEM_TIME_event(void)
{
	if( timer_10ms_flag )
	{
		timer_10ms_flag = 0;
		TMR_timer_task();
	}
}

/*
*********************************************************************************************************
*                                             START TIMER
*
* Description : This function start a timer
* Arguments   : n         is the timer to start
* Returns     : None.
*********************************************************************************************************
*/

void TMR_timer_start(u8 n)
{
    if (n < TMR_MAX_TMR)
    {
        __DI();

        TmrTbl[n].TmrEn = TRUE;

        __EI();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                             STOP TIMER
*
* Description : This function stops a timer
* Arguments   : n         is the timer to stop
* Returns     : None.
*********************************************************************************************************
*/

void TMR_timer_stop(u8 n)
{
    if (n < TMR_MAX_TMR)
    {
        __DI();

        TmrTbl[n].TmrEn = FALSE;

        __EI();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                          TIMER MANAGER TASK
*
* Description : This task is created by TmrInit() and is responsible for updating the timers.
*               TmrTask() executes every 1/10 of a second.
* Arguments   : None.
* Returns     : None.
* Note(s)     : 1) The function to execute when a timer times out is executed outside the critical
*                  section.
*********************************************************************************************************
*/

void TMR_timer_task(void)
{
    TMR *ptmr;
    u8 i;
    void (*pfnct)(void); /* Function to execute when timer times out      */
    void *parg;            /* Arguments to pass to above function           */

                                  /* Avoid compiler warning (uC/OS-II req.)        */
    pfnct = (void (*)(void ))0; /* Start off with no function to execute         */
    parg = (void *)0;

    ptmr = &TmrTbl[0]; /* Point at beginning of timer table             */

    for (i = 0; i < TMR_MAX_TMR; i++)
    {
        __DI();

        if (ptmr->TmrEn == TRUE)
        { /* Decrement timer only if it is enabled         */
            if (ptmr->TmrCtr > 0)
            {
                ptmr->TmrCtr--;

                if (ptmr->TmrCtr == 0)
                {                    /* See if timer expired                     */
                	if( ptmr->Tmr_type == 0)
                	{
                       ptmr->TmrEn = FALSE; /* Yes, stop timer                          */

                       pfnct = ptmr->TmrFnct; /* Get pointer to function to execute ...   */

                       parg = ptmr->TmrFnctArg; /* ... and its argument                     */
                	}
                	else
                	{
                		pfnct = ptmr->TmrFnct; /* Get pointer to function to execute ...   */

                	    parg = ptmr->TmrFnctArg; /* ... and its argument                     */

                	    ptmr->TmrCtr = ptmr->TmrInit; /* Reload the counter                  */

                	}
                }
            }
        }

        __EI();

        if (pfnct != (void (*)(void ))0)
        {                   /* See if we need to execute function for ...    */
            (*pfnct)(); /* ... timed out timer.                          */

            pfnct = (void (*)(void ))0;
        }

        ptmr++;
    }
}






/*
 * @Author: your name
 * @Date: 2020-04-03 10:31:41
 * @LastEditTime: 2020-04-03 17:53:14
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \PLF5604\Sources\APP\BT\App_Boot.c
 */

#include "App_Boot.h"
#include "MPC5602B.h"
#include "Std_Types.h"

static void Boot_SetFlag(uint8 flagId);
static void Boot_MemSet(uint32 *des, uint32 src);

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Boot_ReprogramCallBack
*
* Description   : Set the reprogramming flag and reset the ECU.
*
* Inputs        : none
*
* Outputs       : none
* 
* Limitations   : Only for Bootloader
*                 
************************************************************************************************
END_FUNCTION_HDR */
void Boot_ReprogramCallBack(void)
{
    /*set reprogram flag*/
    Boot_SetFlag(FLAG_REPROGRAM_ID);
    /*reset ECU*/
    Boot_Reset();
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Boot_SetFlag
*
* Description   : Set the reprogramming flag.
*
* Inputs        : none
*
* Outputs       : none
* 
* Limitations   : Only for Bootloader
*                 
************************************************************************************************
END_FUNCTION_HDR */
static void Boot_SetFlag(uint8 flagId)
{
    uint32 addr = 0xFFFFFFFFUL;
    uint32 data = 0xFFFFFFFFUL;

    if (flagId == FLAG_REPROGRAM_ID)
    {
        addr = FLAG_REPROGRAM_ADDR;
        data = FLAG_REPROGRAM_DATA;
    }

    if (addr != 0xFFFFFFFFUL)
    {
        Boot_MemSet((uint32 *)addr, data);
    }
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Boot_MemSet
* Description   : This function is used for copying data.
*                  
* Inputs        : none
* 
* Outputs       : none
* 
* Limitations   :  
*                                  
************************************************************************************************
END_FUNCTION_HDR */
static void Boot_MemSet(uint32 *des, uint32 src)
{
    if (des != BOOT_NULL_PTR)
    {
        *des = src;
    }

    return;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Boot_Reset
*
* Description   : Reset the ECU.
*
* Inputs        : none
*
* Outputs       : none
* 
* Limitations   : Only for Bootloader
*                 
************************************************************************************************
END_FUNCTION_HDR */
void Boot_Reset(void)
{

    SWT.TO.R = 0x100U;
    RGM.FEAR.B.AR_SOFT = 1U;

#if (0)
    SWT.SR.B.WSC = 0xA601U;
    SWT.SR.B.WSC = 0xB422U;
#endif

    for (;;)
    {
    }
}

/*
 * CAN_CFG.c
 *
 *  Created on: Sep 28, 2014
 */

/**
 * @file CAN_CFG.c FLEXCAN模块配置源文件
 * @ingroup HAL_MCU_CAN
 */
#include "includes.h"

#include "CAN.h"
#include "CAN_CFG_SELF.h"
#include "UDS_CAN.h"
#include "time.h"

static CAN_ConfigType Current_CanConfig[CAN_FIFO_MAX_CHN] =
    {
        /*CAN0*/
        {
            CAN_CHANNEL_CAN0,
            CAN_BOUD_RATE_500KB,
            0U,
            1U,
            0x00U,
            0x00U,
            0x00U,
            0U,
            63U,
            1U
        },
        /*CAN1*/
        {
            CAN_CHANNEL_CAN1,
            CAN_BOUD_RATE_250KB,
            0U,
            1U,
            0xFFFFFFFFU,
            0xFFFFFFFFU,
            0xFFFFFFFFU,
            0U,
            63U,
            1U
        }
    };

/**
 * @brief 对CAN进行具体配置
 * @ingroup HAL_MCU_CAN
 * @return void
 */
bool CAN_CFG_Sel(u8 start_channel, u8 end_channel)
{
    u8 i = 0u;
    bool result = TRUE;
    if (end_channel < start_channel)
    {
        result = FALSE;
    }
    else
    {
        for (i = start_channel; i <= end_channel; i++)
        {
            Can_Init(&Current_CanConfig[i]);
        }
        result = TRUE;
    }
    return result;
}

/**
 * @brief CAN配置初始化，选择要使用的通道，CAN0--CAN1
 * @ingroup HAL_MCU_CAN
 * @return void
 */
void CAN_CFG_Init(void)
{
    Can_InitActiveChn();
    CAN_CFG_Sel(CAN_CHANNEL_CAN0, CAN_CHANNEL_CAN1);
}

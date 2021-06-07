/*
 * @Author: your name
 * @Date: 2020-04-03 10:31:41
 * @LastEditTime: 2020-04-03 17:53:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \PLF5604\Sources\APP\BT\App_Boot.h
 */

#ifndef __APP_BOOT_H__
#define __APP_BOOT_H__

/*****************************************************************************
 * Macro Configuration
 *****************************************************************************/
#define FLAG_REPROGRAM_ID (0x01u)
#define FLAG_REPROGRAM_ADDR (0x40000000ul)
#define FLAG_REPROGRAM_DATA (0xA5A5A5A5UL)
#define FLAG_REPROGRAM_SIZE (0x04u)
/*****************************************************************************
 * Macro Definitions
 *****************************************************************************/

#define BOOT_NULL_PTR ((void *)0)

#define HANDLE_MAX 2u
#define HANDLE_SEND_MAX 1u

#define UDS_PHY_ADDR_RX_ID (0x18DA17F1u)
#define UDS_FUNC_ADDR_RX_ID (0x18DBFFF9u)

#define UDS_MCU_RSP_ID (0x18DAF117u)

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void Boot_ReprogramCallBack(void);
extern void Boot_Reset(void);

#endif /* __APP_BOOT_H__ */

/*
 * @Author: your name
 * @Date: 2020-04-03 10:31:41
 * @LastEditTime: 2020-04-03 17:52:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \PLF5604\Sources\APP\BT\App_Boot_cfg.h
 */

#ifndef __APP_BOOT_CFG_H__
#define __APP_BOOT_CFG_H__

//#include "bl_ram.h"
#include "bl_watchdog.h"
/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/
//typedef unsigned char  bl_u8_t;      /**< This is a unsigned type for 8 bits.*/
//typedef unsigned short bl_u16_t;    /**< This is a unsigned type for 16 bits.*/
//typedef unsigned long  bl_u32_t;     /**< This is a unsigned type for 32 bits.*/

#define CAN_TX_ID 0x18DAF13DU

#define FLAG_REPROGRAM_ID 0x01U
#define FLAG_RESET_ID 0x02U
#define FLAG_FINGERPRINT_ID 0x03U

#define FLAG_BASE_SIZE 0x04U

#define FLAG_REPROGRAM_ADDR (0x40000000)
#define FLAG_RESET_ADDR (0x40000010)
#define FLAG_FINGERPRINT_ADDR (0xFFFFFFFF)

#define FLAG_REPROGRAM_DATA 0xA5A5A5A5UL
#define FLAG_RESET_DATA 0x55555555UL

#define APP_EXIST_FLAG_FALSE (0xffffffff)
#define APP_EXIST_FLAG_TRUE (0x55aa55aa)
#define APP_EXIST_ADDRESS (0x10000)
#define APP_VERSION_ADDRESS (APP_EXIST_ADDRESS + 4) /*应用程序版本号存放地址*/
#define APP_START_ADDRESS (APP_EXIST_ADDRESS + 16)
#define BOOTLOADER_PARAM (*(volatile struct BOOTLOADER_PARAM_tag *)0x4000BFE0UL)

#define ResetMCUHandle() Wdg_FastReset()


#if 0
#define FlagReadHandle(addr, size, buf) Ram_Read(addr, size, buf)
#define FlagWriteHandle(addr, size, buf) Ram_Write(addr, size, buf)
#define Boot_ComControlHandle() ComControl()
#define Boot_CheckProgramming() CheckProgramming()
#endif

extern void Boot_SendSFCanMsg(bl_u8_t *data, bl_u8_t size, bl_u16_t canId);

#endif /*__APP_BOOT_CFG_H__*/

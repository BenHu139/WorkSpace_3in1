/*
 * @Author: your name
 * @Date: 2020-04-03 10:31:42
 * @LastEditTime: 2020-04-03 14:25:33
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \PLF5604\Sources\HAL\MCU\CAN\CAN_CFG_SELF.h
 */

#ifndef CAN_CFG_SELFH_
#define CAN_CFG_SELFH_
#include "CAN.h"

extern void CAN_CFG_Init(void);
extern bool CAN_CFG_Sel(u8 start_channel, u8 end_channel);

#endif /* CAN_CFG_H_ */

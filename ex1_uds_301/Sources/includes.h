/*
 * includes.h
 *
 *  Created on: Apr 5, 2020
 *      Author: haozw
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

//platform
#include "MPC5602B.h"
#include "Std_Types.h"
#include "typedefs.h"

#define DEBUG_EN

#define SIUL  SIU

#define __EI()    asm("wrteei 1")
#define __DI()    asm("wrteei 0")
#define __MSYNC() asm("msync")

#define UMAX(a, b)			 ( ((a) < (b)) ? (b) : (a) )	// 取两者的最大值, 只能用于unsigned 数据
#define UMIN(a, b)			 ( ((a) > (b)) ? (b) : (a) )	// 取两者的最小值, 只能用于unsigned 数据

#define BYTE_SWAP_16(x) \
    (uint16)((((uint16)(x) & 0x00ff) << 8) | \
             (((uint16)(x) & 0xff00) >> 8) \
             )
#define BYTE_SWAP_32(x) \
    (uint32)((((uint32)(x) & 0xff000000) >> 24) | \
             (((uint32)(x) & 0x00ff0000) >> 8)  | \
             (((uint32)(x) & 0x0000ff00) << 8)  | \
             (((uint32)(x) & 0x000000ff) << 24) \
             )

#endif /* INCLUDES_H_ */

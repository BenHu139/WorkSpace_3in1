/*
 * WDT.h
 *
 *  Created on: 2014-5-22
 *      Author: sunms
 */

/**
 * @file WDT.h
 * @ingroup HAL_MCU_WDT
 */

#ifndef WDT_H__
#define WDT_H__


void HAL_MCU_WDT_Init(void);
void HAL_MCU_WDT_ClearInsideDog(void);
void HAL_MCU_WDT_SoftWareReset(void);

#endif /* __WDT_H__ */

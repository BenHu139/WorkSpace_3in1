/*
 * FSM_Cfg.h
 *
 *  Created on: Jun 15, 2020
 *      Author: hr
 */

#ifndef FSM_CFG_H_
#define FSM_CFG_H_

#include "Std_Types.h"

typedef enum {
	FSM_SW_FAULT_NO_FAULT = 0,
	FSM_SW_FAULT_OUT_OVER_CURRENT,
	FSM_SW_FAULT_IN_OVER_CURRENT,
	FSM_SW_FAULT_TEMP_OVER_RANGE,
	FSM_SW_FAULT_IN_OVER_VOLT,
	FSM_SW_FAULT_IN_UNDER_VOLT,
	FSM_SW_FAULT_OUT_OVER_VOLT,
	FSM_SW_FAULT_OUT_2B1_VOLT,
	FSM_SW_FAULT_OUT_1BMIN_VOLT,
	FSM_SW_FAULT_OUT_UNDER_VOLT,
	
	FSM_SW_FAULT_IDX_MAX
} FSM_SW_Faultl_Index_Type;

typedef struct {
	uint8	u8Priority;
} FSM_SW_Fault_Config_Type;

extern FSM_SW_Fault_Config_Type swFaultCfgList[FSM_SW_FAULT_IDX_MAX];

#endif /* FSM_CFG_H_ */

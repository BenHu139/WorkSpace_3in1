/*
 * FSM_Cfg.c
 *
 *  Created on: Jun 15, 2020
 *      Author: hr
 */
#include "FSM_Cfg.h"

FSM_SW_Fault_Config_Type swFaultCfgList[FSM_SW_FAULT_IDX_MAX] = {
		{0},				// FSM_SW_FAULT_NO_FAULT
		{1},				// FSM_SW_FAULT_OUT_OVER_CURRENT
		{2},				// FSM_SW_FAULT_IN_OVER_CURRENT
		{3},				// FSM_SW_FAULT_TEMP_OVER_RANGE
		{4},				// FSM_SW_FAULT_IN_OVER_VOLT
		{4},				// FSM_SW_FAULT_IN_UNDER_VOLT
		{5},				// FSM_SW_FAULT_OUT_OVER_VOLT
		{5},				// FSM_SW_FAULT_OUT_2B1_VOLT
		{5},				// FSM_SW_FAULT_OUT_1BMIN_VOLT
		{5},				// FSM_SW_FAULT_OUT_UNDER_VOLT
};


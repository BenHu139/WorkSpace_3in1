/*
 * E2PE_Cfg.h
 *
 *  Created on: May 28, 2020
 *      Author: hr
 */

#ifndef E2PE_CFG_H_
#define E2PE_CFG_H_

#include "includes.h"

typedef struct {
	u32 startAddr;
	u32 length;
}E2PE_Parameter_Type;

typedef enum
{
	E2PE_PARA_ID_ECU_SN_0 = 0,					// 0xF18C
	E2PE_PARA_ID_ECU_Date_1,					// 0xF18B
	E2PE_PARA_ID_ECU_HW_Ver_2,					// 0xF193
	E2PE_PARA_ID_APP_SW_Ver_3,					// 0xF189
	
	E2PE_PARA_ID_APP_SW_Finger_4,				// 0xF184
	E2PE_PARA_ID_APP_Data_Finger_5,				// 0xF185
	E2PE_PARA_ID_ECU_Part_Num_6,				// 0xF187
	E2PE_PARA_ID_SYS_Supply_ID_7,				// 0xF18A
	
	E2PE_PARA_ID_CAL_SW_Ver_8,					// 0xF1A0
	E2PE_PARA_ID_CAL_Data_Ver_9,				// 0xF1A1
	E2PE_PARA_ID_Product_Model_10,				// 0xF1A2
	E2PE_PARA_ID_VIN_Code_11,					// 0xF190
	
	E2PE_PARA_ID_MAX
}E2PE_PARAMETER_INDEX;


#define PARA_ECU_SN_0_ADDR 				(0u)
#define PARA_ECU_SN_0_LEN				(16u)
#define PARA_ECU_Date_1_ADDR 			((PARA_ECU_SN_0_ADDR) + (PARA_ECU_SN_0_LEN))
#define PARA_ECU_Date_1_LEN				(6u)
#define PARA_ECU_HW_Ver_2_ADDR 			((PARA_ECU_Date_1_ADDR) + (PARA_ECU_Date_1_LEN))
#define PARA_ECU_HW_Ver_2_LEN			(8u)
#define PARA_APP_SW_Ver_3_ADDR 			((PARA_ECU_HW_Ver_2_ADDR) + (PARA_ECU_HW_Ver_2_LEN))
#define PARA_APP_SW_Ver_3_LEN			(16u)

#define PARA_APP_SW_Finger_4_ADDR 		((PARA_APP_SW_Ver_3_ADDR) + (PARA_APP_SW_Ver_3_LEN))
#define PARA_APP_SW_Finger_4_LEN		(13u)
#define PARA_APP_Data_Finger_5_ADDR 	((PARA_APP_SW_Finger_4_ADDR) + (PARA_APP_SW_Finger_4_LEN))
#define PARA_APP_Data_Finger_5_LEN		(13u)
#define PARA_ECU_Part_Num_6_ADDR 		((PARA_APP_Data_Finger_5_ADDR) + (PARA_APP_Data_Finger_5_LEN))
#define PARA_ECU_Part_Num_6_LEN			(5u)
#define PARA_SYS_Supply_ID_7_ADDR 		((PARA_ECU_Part_Num_6_ADDR) + (PARA_ECU_Part_Num_6_LEN))
#define PARA_SYS_Supply_ID_7_LEN		(5u)

#define PARA_CAL_SW_Ver_8_ADDR 			((PARA_SYS_Supply_ID_7_ADDR) + (PARA_SYS_Supply_ID_7_LEN))
#define PARA_CAL_SW_Ver_8_LEN			(16u)
#define PARA_CAL_Data_Ver_9_ADDR 		((PARA_CAL_SW_Ver_8_ADDR) + (PARA_CAL_SW_Ver_8_LEN))
#define PARA_CAL_Data_Ver_9_LEN			(8u)
#define PARA_Product_Model_10_ADDR 		((PARA_CAL_Data_Ver_9_ADDR) + (PARA_CAL_Data_Ver_9_LEN))
#define PARA_Product_Model_10_LEN		(16u)
#define PARA_VIN_Code_11_ADDR 			((PARA_Product_Model_10_ADDR) + (PARA_Product_Model_10_LEN))
#define PARA_VIN_Code_11_LEN			(17u)




// 最后一个参数的起始位置加长度
#define E2PE_BUF_LEN 		((PARA_VIN_Code_11_ADDR) + (PARA_VIN_Code_11_LEN))



extern E2PE_Parameter_Type E2PE_parameter_list[E2PE_PARA_ID_MAX];

extern u8 E2PE_parameter_buffer[E2PE_BUF_LEN];

#endif /* E2PE_CFG_H_ */

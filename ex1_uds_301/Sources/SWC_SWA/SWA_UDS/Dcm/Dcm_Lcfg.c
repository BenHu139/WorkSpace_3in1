/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Lcfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Dcm module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Dcm module configuration File
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   04.03.00    06/09/2016     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Include files
*******************************************************************************/
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"
#include "E2PE_Cfg.h"
#define DCM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/* Config S3 time */
CONST(Dcm_DspNonDefaultSessionS3ServerType, DCM_CONFIG_CONST) gDcmDspNonDefaultSessionS3Server = 5000UL;/*Unit:ms*/

/* Config Session */
CONST(DcmDspSessionRow, DCM_CONFIG_CONST) gDcmDspSessionRow[KIND_OF_SESSION] = 
{
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_DEFAULT,
        /* P2Server */ 
        50UL,
        /* P2*Server */ 
        5000UL,
    },
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_PROGRAMMING,
        /* P2Server */ 
        50UL,
        /* P2*Server */ 
        5000UL,
    },
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_EXTENDED_DIAGNOSTIC,
        /* P2Server */ 
        50UL,
        /* P2*Server */ 
        5000UL,
    }
};

#if(DCM_SERVICE_27_ENABLED == STD_ON)
CONST(DcmDspSecurityRow, DCM_CONFIG_CONST)  gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL] = 
{
    {
        5000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        8UL,  /* Key Size */
        DCM_SEC_LEV_L1, /* Level */
        2UL,  /* Attempt Number */
        8UL  /* Seed Size */
    },
    {
        5000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        4UL,  /* Key Size */
        DCM_SEC_LEV_L2, /* Level */
        2UL,  /* Attempt Number */
        4UL  /* Seed Size */
    },
    {
        5000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L3, /* Level */
        2UL,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        5000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L4, /* Level */
        2UL,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        5000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L5, /* Level */
        2UL,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L6, /* Level */
        2UL,  /* Attempt Number */
        2UL  /* Seed Size */
    },
    {
        10000UL,  /* Delay Time */
        10000UL,  /* Delay Time On Boot */
        2UL,  /* Key Size */
        DCM_SEC_LEV_L7, /* Level */
        2UL,  /* Attempt Number */
        2UL  /* Seed Size */
    }
};
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)
CONST(Dcm_22_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_22[NUMBER_OF_READ_DID] =  
{
    /* Index 0 */
    {
        /* DID */
        (uint32)0x0000U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Read0x0000,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 1 */
	{
		/* DID */
		(uint32)0xF184U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_APP_SW_Finger_4_LEN,
		/* App Callback Funtion */
		&App_Read0xF184,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 2 */
	{
		/* DID */
		(uint32)0xF185U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_APP_Data_Finger_5_LEN,
		/* App Callback Funtion */
		&App_Read0xF185,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 3 */
	{
		/* DID */
		(uint32)0xF187U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_ECU_Part_Num_6_LEN,
		/* App Callback Funtion */
		&App_Read0xF187,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 4 */
	{
		/* DID */
		(uint32)0xF189U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_APP_SW_Ver_3_LEN,
		/* App Callback Funtion */
		&App_Read0xF189,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 5 */
	{
		/* DID */
		(uint32)0xF18AU,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_SYS_Supply_ID_7_LEN,
		/* App Callback Funtion */
		&App_Read0xF18A,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 6 */
	{
		/* DID */
		(uint32)0xF18BU,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_ECU_Date_1_LEN,
		/* App Callback Funtion */
		&App_Read0xF18B,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 7 */
	{
		/* DID */
		(uint32)0xF18CU,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_ECU_SN_0_LEN,
		/* App Callback Funtion */
		&App_Read0xF18C,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 8 */
	{
		/* DID */
		(uint32)0xF190U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_VIN_Code_11_LEN,
		/* App Callback Funtion */
		&App_Read0xF190,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 9 */
	{
		/* DID */
		(uint32)0xF193U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_ECU_HW_Ver_2_LEN,
		/* App Callback Funtion */
		&App_Read0xF193,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 10 */
	{
		/* DID */
		(uint32)0xF1A0,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_CAL_SW_Ver_8_LEN,
		/* App Callback Funtion */
		&App_Read0xF1A0,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 11 */
	{
		/* DID */
		(uint32)0xF1A1,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_CAL_Data_Ver_9_LEN,
		/* App Callback Funtion */
		&App_Read0xF1A1,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 12 */
	{
		/* DID */
		(uint32)0xF1A2,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_Product_Model_10_LEN,
		/* App Callback Funtion */
		&App_Read0xF1A2,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 13 */
	{
		/* DID */
		(uint32)0xFC01,
		/* Switch */
		STD_ON,  
		/* Data Size */
		10U,
		/* App Callback Funtion */
		&App_Read0xFC01,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 14 */
	{
		/* DID */
		(uint32)0xFC02,
		/* Switch */
		STD_ON,  
		/* Data Size */
		10U,
		/* App Callback Funtion */
		&App_Read0xFC02,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 15 */
	{
		/* DID */
		(uint32)0xFC03,
		/* Switch */
		STD_ON,  
		/* Data Size */
		10U,
		/* App Callback Funtion */
		&App_Read0xFC03,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 16 */
	{
		/* DID */
		(uint32)0xFC04,
		/* Switch */
		STD_ON,  
		/* Data Size */
		10U,
		/* App Callback Funtion */
		&App_Read0xFC04,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 17 */
	{
		/* DID */
		(uint32)0xFC11,
		/* Switch */
		STD_ON,  
		/* Data Size */
		4U,
		/* App Callback Funtion */
		&App_Read0xFC11,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 18 */
	{
		/* DID */
		(uint32)0xFC12,
		/* Switch */
		STD_ON,  
		/* Data Size */
		4U,
		/* App Callback Funtion */
		&App_Read0xFC12,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
};
#endif

/* 0x23 0x3D */
#if((DCM_SERVICE_23_ENABLED == STD_ON)||(DCM_SERVICE_3D_ENABLED == STD_ON))
/* Config AddressFormat Bytes and SizeFormat Bytes */
CONST(Dcm_MemoryAddressFormatType, DCM_CONFIG_CONST)  gMemoryAddressFormat = 4U;
CONST(Dcm_MemorySizeFormatType, DCM_CONFIG_CONST) gMemorySizeFormat = 2U;
#endif

/* 0x23 */
#if(DCM_SERVICE_23_ENABLED == STD_ON)
CONST(DcmDspReadMemoryRangeInfo, DCM_CONFIG_CONST)   gDcmDspReadMemoryRangeInfo_23[NUMBER_OF_READ_ADDRESS_SEG] =
{
    {
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
};
#endif

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
CONST(Dcm_24_ServiceInfoType, DCM_CONFIG_CONST)  gDcmDsdSubService_24[NUMBER_OF_READ_DID_24] =
{
};
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
CONST(Dcm_2A_ServiceInfoType, DCM_CONFIG_CONST)   gDcmDsdSubService_2A[NUMBER_OF_PERIODIC_DID] =
{
};
#endif

/* 0x2C */
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
CONST(Dcm_2C_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2C[NUMBER_OF_DYN_DID] =
{
};
#endif

/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
CONST(Dcm_2E_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2E[NUMBER_OF_WRITE_DID] =  
{
    /* Index 0 */
    {
        /* DID */
        (uint32)0x0000U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Write0x0000,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    /* Index 1 */
	{
		/* DID */
		(uint32)0xF184U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_APP_SW_Finger_4_LEN,
		/* App Callback Funtion */
		&App_Write0xF184,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1|DCM_SEC_LEV_L2),
		/* Supported Session */
		(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 2 */
	{
		/* DID */
		(uint32)0xF185U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_APP_Data_Finger_5_LEN,
		/* App Callback Funtion */
		&App_Write0xF185,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1|DCM_SEC_LEV_L2),
		/* Supported Session */
		(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 3 */
	{
		/* DID */
		(uint32)0xF187U,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_ECU_Part_Num_6_LEN,
		/* App Callback Funtion */
		&App_Write0xF187,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1|DCM_SEC_LEV_L2),
		/* Supported Session */
		(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
    /* Index 4 */
    {
        /* DID */
        (uint32)0xF189U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        PARA_APP_SW_Ver_3_LEN,
        /* App Callback Funtion */
        &App_Write0xF189,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    /* Index 5 */
	{
		/* DID */
		(uint32)0xF18AU,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_SYS_Supply_ID_7_LEN,
		/* App Callback Funtion */
		&App_Write0xF18A,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
    /* Index 6 */
    {
        /* DID */
        (uint32)0xF18BU,
        /* Switch */
        STD_ON,  
        /* Data Size */
        PARA_ECU_Date_1_LEN,
        /* App Callback Funtion */
        &App_Write0xF18B,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    /* Index 7 */
    {
        /* DID */
        (uint32)0xF18CU,
        /* Switch */
        STD_ON,  
        /* Data Size */
        PARA_ECU_SN_0_LEN,
        /* App Callback Funtion */
        &App_Write0xF18C,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    /* Index 8 */
    {
        /* DID */
        (uint32)0xF190U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        PARA_VIN_Code_11_LEN,
        /* App Callback Funtion */
        &App_Write0xF190,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    /* Index 9 */
    {
        /* DID */
        (uint32)0xF193U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        PARA_ECU_HW_Ver_2_LEN,
        /* App Callback Funtion */
        &App_Write0xF193,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    /* Index 10 */
	{
		/* DID */
		(uint32)0xF1A0,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_CAL_SW_Ver_8_LEN,
		/* App Callback Funtion */
		&App_Write0xF1A0,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 11 */
	{
		/* DID */
		(uint32)0xF1A1,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_CAL_Data_Ver_9_LEN,
		/* App Callback Funtion */
		&App_Write0xF1A1,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 12 */
	{
		/* DID */
		(uint32)0xF1A2,
		/* Switch */
		STD_ON,  
		/* Data Size */
		PARA_Product_Model_10_LEN,
		/* App Callback Funtion */
		&App_Write0xF1A2,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 13 */
	{
		/* DID */
		(uint32)0xFC01,
		/* Switch */
		STD_ON,  
		/* Data Size */
		10U,
		/* App Callback Funtion */
		&App_Write0xFC01,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 14 */
	{
		/* DID */
		(uint32)0xFC02,
		/* Switch */
		STD_ON,  
		/* Data Size */
		10U,
		/* App Callback Funtion */
		&App_Write0xFC02,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 15 */
	{
		/* DID */
		(uint32)0xFC03,
		/* Switch */
		STD_ON,  
		/* Data Size */
		10U,
		/* App Callback Funtion */
		&App_Write0xFC03,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 16 */
	{
		/* DID */
		(uint32)0xFC04,
		/* Switch */
		STD_ON,  
		/* Data Size */
		10U,
		/* App Callback Funtion */
		&App_Write0xFC04,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 17 */
	{
		/* DID */
		(uint32)0xFC11,
		/* Switch */
		STD_ON,  
		/* Data Size */
		4U,
		/* App Callback Funtion */
		&App_Write0xFC11,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 18 */
	{
		/* DID */
		(uint32)0xFC12,
		/* Switch */
		STD_ON,  
		/* Data Size */
		4U,
		/* App Callback Funtion */
		&App_Write0xFC12,
		/* Supported Security Level */
		(DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
};
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
CONST(Dcm_2F_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID] =
{
    /* Index 0 */
    {
        /* DID */
        (uint32)0xFE00U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            4UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE00,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE00,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE00,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE00,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
    /* Index 1 */
    {
        /* DID */
        (uint32)0xFE01U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            1UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE01,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE01,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE01,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE01,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
    /* Index 2 */
    {
        /* DID */
        (uint32)0xFE02U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            1UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE02,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE02,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE02,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE02,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
    /* Index 3 */
    {
        /* DID */
        (uint32)0xFE03U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            1UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE03,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE03,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE03,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE03,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
    /* Index 4 */
    {
        /* DID */
        (uint32)0xFE04U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            3UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE04,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE04,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE04,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE04,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
    /* Index 5 */
    {
        /* DID */
        (uint32)0xFE05U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            1UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE05,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE05,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE05,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE05,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
    /* Index 6 */
    {
        /* DID */
        (uint32)0xFE06U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            2UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE06,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE06,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE06,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE06,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
    /* Index 7 */
    {
        /* DID */
        (uint32)0xFE07U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            1UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE07,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE07,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE07,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE07,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
    /* Index 8 */
    {
        /* DID */
        (uint32)0xFE08U,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED,
        {
            0UL,
            1UL,
            0UL 
        },
        /* ReturnControlToEcuFnc */
        &App_ReturnControlToEcu0xFE08,
        /* ResetToDefaultFnc */
        &App_ResetToDefault0xFE08,
        /* FreezeCurrentStateFnc */
        &App_FreezeCurrentState0xFE08,
        /* ShortTermAdjustmentFnc */
        &App_ShortTermAdjustment0xFE08,
        /* Self Defined App Callback Funtion*/
        DCM_NULL 
    },
};
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
CONST(DcmDspRoutine, DCM_CONFIG_CONST)  DcmDspRoutineIdentifierTable_31[NUMBER_OF_RID] = 
{
    /* Index 0 */
    {
        /* SID */
    	(uint32)0xFF02U,	
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0xFF02,
        /* StopRoutineFnc */
        &App_StopRoutine0xFF02,
        /* RequestResultsRoutineFnc */
        &App_RequestRoutineResults0xFF02,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
                /* Supported Session */
                (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    
    /* Index 1 */
    {
        /* SID */
        (uint32)0xFF00U,    
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0xFF00,
        /* StopRoutineFnc */
        &App_StopRoutine0xFF00,
        /* RequestResultsRoutineFnc */
        &App_RequestRoutineResults0xFF00,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L2),
                /* Supported Session */
                (DCM_SESSION_PROGRAMMING|DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                9UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    
    /* Index 2 */
    {
        /* SID */
        (uint32)0xF001U,    
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0xF001,
        /* StopRoutineFnc */
        &App_StopRoutine0xF001,
        /* RequestResultsRoutineFnc */
        &App_RequestRoutineResults0xF001,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L2),
                /* Supported Session */
                (DCM_SESSION_PROGRAMMING|DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                4UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    
    /* Index 3 */
    {
        /* SID */
        (uint32)0xFF01U,    
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0xFF01,
        /* StopRoutineFnc */
        &App_StopRoutine0xFF01,
        /* RequestResultsRoutineFnc */
        &App_RequestRoutineResults0xFF01,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L2),
                /* Supported Session */
                (DCM_SESSION_PROGRAMMING|DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    
    /* Index 4 */
    {
        /* SID */
        (uint32)0x0800U,    
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0x0800,
        /* StopRoutineFnc */
        &App_StopRoutine0x0800,
        /* RequestResultsRoutineFnc */
        &App_RequestRoutineResults0x0800,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L2),
                /* Supported Session */
                (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
};
#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
CONST(DcmDspWriteMemoryRangeInfo, DCM_CONFIG_CONST)  gDcmDspWriteMemoryRangeInfo_3D[NUMBER_OF_WRITE_ADDRESS_SEG] =
{
    {
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
};
#endif

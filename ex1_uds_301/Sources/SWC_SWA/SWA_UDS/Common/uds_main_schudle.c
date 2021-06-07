/*
 * uds_main_schudle.c
 *
 *  Created on: Apr 26, 2017
 *      Author: wenxc
 */
#include "uds_main_schudle.h"
#include "CanIf.h"
#include "CanTp_Cfg.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Nvm.h"
#include "UDS_CAN.h"
#include "Dem.h"

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the uds module. This function mainly initialize
 *           CanTp, dcm and security access delay info.
 *
 *
 *  \note This function is called by the process driver module.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_UdsInit(void)
{
    CanIf_Init();
    CanTp_Init(&CanTp_Cfg);
    Dcm_Init(((void *) 0));
}

/**************************************************************************//**
 *
 *  \details Periodic callback of function Rte_PeriodicSchedule. This function
 *           needs to be called periodically, and mainly handles timer of dcm,
 *           and CanTp module.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_UdsPeriodicCallback(void)
{
    CanTp_MainFunction();
    Dcm_MainFunction();  
    DecreaseActiveTimeOut();
    Dem_MainFunction();
    NvM_MainFunction();
}



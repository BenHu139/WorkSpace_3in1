/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to configurate the data of the security
 *              manager module.
 *
 *  \file       bl_security_cfg.h
 *  \ingroup    security_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *              mingqing.tang <minqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      05.00.00 | 19/06/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_SECURITY_CFG_H_
#define _BL_SECURITY_CFG_H_
#include "bl_security.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3205,3210,3447,3448 EOF*/
/*
 * 3205:The identifier is not used and could be removed.
 * The bl_Adapter_t is used by the specifically adapter such as UDS platform in
 * the bl_adpt_uds_platform.c
 *
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_security_cfg.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The function Declarations are in the header file.
 *
 * MISRA-C:2004 5.3(3448):Declaration of typedef is not in a header file.
 * The bl_SecurityDelay_t is declared in the header file.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/*the security configurations*/

#define SECM_ACCESS_INIT            (&Acc_UdsDemoInit)
#define SECM_ACCESS_MAKE_NEWSEED    (&Acc_UdsDemoMakeNewSeed)
#define SECM_ACCESS_GET_SEED        (&Acc_UdsDemoGetSeed)
#define SECM_ACCESS_VERIFY_KEY      (&Acc_UdsDemoVerifyKey)

#define SECM_VERIFICATION_INIT      (&Bzip2_Init)
#define SECM_VERIFICATION_START     (&Bzip2_Start)
#define SECM_VERIFICATION_UPDATE    (&Bzip2_Update)
#define SECM_VERIFICATION_VERIFY    (&Bzip2_Verify)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
/** \brief  The access interfaces list.*/
extern const bl_SecurityAccessOps_t g_SecurityAccessOps;

/** \brief  The integrality interfaces list.*/
extern const bl_VerificationOps_t g_VerificationOps;

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


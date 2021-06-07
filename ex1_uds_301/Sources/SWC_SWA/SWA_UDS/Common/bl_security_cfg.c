/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to configurate the security manager module.
 *
 *  \file       bl_security_cfg.c
 *  \ingroup    security_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *              mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 25/03/2010 | hewei.zhang      | N/A | Boot010001
 *      01.01.00 | 19/05/2010 | hewei.zhang      | N/A | Boot010002
 *      02.00.00 | 18/05/2011 | mingqing.tang    | N/A | Boot020001
 *      02.01.00 | 15/06/2011 | mingqing.tang    | N/A | Boot020002
 *      02.05.00 | 22/06/2011 | mingqing.tang    | N/A | Boot020006
 *      05.00.00 | 19/06/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_security_cfg.h"
#include "bl_crc32_bzip2.h"
#include "bl_access_udsdemo.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1531,3211 EOF*/
/*
 * 1531:The object is referenced in only one translation unit.
 *
 * 3211:The global identifier is defined but not used.
 * The g_SecurityAccessOps is used in the bl_security.c file.
 * The g_VerificationOps is used in the bl_security.c file.
 *
 */

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
/**************************************************************************//**
 *  \details    A operation list of security access, this list is only used by
 *              the security manager module.
 *
 *  \warning    All other modules MUST not use this variable.
 *****************************************************************************/
const bl_SecurityAccessOps_t g_SecurityAccessOps =
{
    SECM_ACCESS_INIT,
    SECM_ACCESS_MAKE_NEWSEED,
    SECM_ACCESS_GET_SEED,
    SECM_ACCESS_VERIFY_KEY
};


/******************************************************************************
 *  \details    The verification Operations list.
 *****************************************************************************/
const bl_VerificationOps_t g_VerificationOps =
{
    SECM_VERIFICATION_INIT,
    SECM_VERIFICATION_START,
    SECM_VERIFICATION_UPDATE,
    SECM_VERIFICATION_VERIFY
};

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/


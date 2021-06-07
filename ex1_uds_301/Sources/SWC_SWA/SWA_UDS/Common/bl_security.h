/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file of the security manager module.
 *
 *  \file       bl_security.h
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
#ifndef _BL_SECURITY_H_
#define _BL_SECURITY_H_
#include "bl_typedefs.h"
#include "bl_security_funcfg.h"

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

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/
/** \brief A alias of the struct _tag_SecurityAccessOps.*/
typedef struct _tag_SecurityAccessOps bl_SecurityAccessOps_t;
/** \brief A alias of the struct _tag_VerificationOps.*/
typedef struct _tag_VerificationOps bl_VerificationOps_t;

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/** \brief The list of the security access interfaces.*/
struct _tag_SecurityAccessOps
{
    void (*Init)(void); /**< initialize the security access function.*/
    void (*MakeNewSeed)(void);
    void (*GetSeed)(bl_Buffer_t *seed);
    bl_Return_t (*VerifyKey)(const bl_Buffer_t *key);
};

/**
 *  \brief The list of the integrality interfaces.
 */
struct _tag_VerificationOps
{
    void (*Init)(void);/**< init interface.*/
    void (*Start)(void); /**< start interface.*/
    bl_Return_t (*Update)(bl_Size_t size, const bl_Buffer_t *data);
    bl_Return_t (*Verify)(bl_Size_t size, const bl_Buffer_t *hash);
};

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
/** \brief The initialization interface of the security management module.*/
extern void Secm_Init(void);

/** \brief Make a new seed.*/
extern void Secm_MakeNewSeed(void);
/** \brief Save the current contents of the seed to a buffer.*/
extern void Secm_GetSeed(bl_Buffer_t *seed);
/** \brief Verify the key whether is valid.*/
extern bl_Return_t Secm_VerifyKey(bl_Size_t size, const bl_Buffer_t *key);

/** \brief The start interface for verifting data.*/
extern void Secm_StartHash(void);
/** \brief The update interface for verifting the HASH.*/
extern bl_Return_t Secm_UpdateHash(bl_Size_t size, const bl_Buffer_t *data);
/** \brief The compare interface for verifting data.*/
extern bl_Return_t Secm_VerifyHash(bl_Size_t size, const bl_Buffer_t *hash);

#if ((SECM_SECURITY_CLASS == BL_SECURITY_CLASS_C) \
    || (SECM_SECURITY_CLASS == BL_SECURITY_CLASS_CCC))
/** \brief Update the hash value by the address and size of a segment.*/
extern bl_Return_t Secm_UpdateHashByAddr(bl_Address_t addr, bl_Size_t size);
#endif

#endif


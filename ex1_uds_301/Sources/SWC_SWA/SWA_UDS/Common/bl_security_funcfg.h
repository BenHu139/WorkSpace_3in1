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
 *  \file       bl_security_funcfg.h
 *  \ingroup    security_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
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
#ifndef _BL_SECURITY_FUNCFG_H_
#define _BL_SECURITY_FUNCFG_H_
#include "bl_typedefs.h"

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/** \brief The security class.*/
#define SECM_SECURITY_CLASS         BL_SECURITY_CLASS_DDD
/** \brief The seed size used for the security access.*/
#define SECM_ACCESS_SEED_SIZE       (0x04u)
/** \brief The key size used for the security access.*/
#define SECM_ACCESS_KEY_SIZE        (0x04u)
/** \brief The CRC algorithm used for class DDD.*/
#define SECM_FUN_CRC_HASH_ENABLE    BL_FUN_ON
/** \brief The HMAC algorithm used for class C or CCC.*/
#define SECM_FUN_HMAC_HASH_ENABLE   BL_FUN_OFF
/** \brief The RSA algorithm used for class CCC.*/
#define SECM_FUN_RSA_HASH_ENABLE    BL_FUN_OFF

#if (SECM_FUN_CRC_HASH_ENABLE == BL_FUN_ON)
/** \brief The name of the crc algorithm.*/
#define SECM_CRC_NAME               "crc32_bzip2"
/** \brief The bit width of a crc algorithm, 32, 16 or 8.*/
#define SECM_CRC_WIDTH              (32u)
/** \brief The result size(bytes) of a crc algorithm, 4, 2 or 1.*/
#define SECM_CRC_VALUE_SIZE         (SECM_CRC_WIDTH >> 3u)
/** \brief The crc algorithm opimite*/
#define SECM_CRC_OPIMITE_BY_SIZE    BL_FUN_OFF

#endif

#if (SECM_FUN_HMAC_HASH_ENABLE == BL_FUN_ON)
#define SECM_HMAC_HASH_ALGORITHM    SECM_HASH_SHA1
#define SECM_HMAC_IN_BLOCK_SIZE     (20)
#define SECM_HMAC_KEY_SIZE          (16)
#define SECM_HMAC_HASH_SIZE         (20)
#endif

#if (SECM_FUN_RSA_HASH_ENABLE == BL_FUN_ON)
#define SECM_RSA_PUBLIC_KEY_SIZE    (1024)
#define SECM_RSA_SIGNATURE_SIZE     (20)
#endif

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


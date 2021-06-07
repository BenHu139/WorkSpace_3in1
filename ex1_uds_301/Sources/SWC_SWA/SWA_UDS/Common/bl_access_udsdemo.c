/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to make seed and verify a key.
 *
 *  \file       bl_access_udsdemo.c
 *  \ingroup    security_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 25/03/2010 | hewei.zhang      | N/A | Boot010001
 *      01.01.00 | 19/05/2010 | hewei.zhang      | N/A | Boot010002
 *      05.00.00 | 19/06/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_common.h"
#include "bl_security_funcfg.h"
#include "bl_access_udsdemo.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 602,1532,3212,3227,3453 EOF*/
/*
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 3212:This explicit cast is redundant and could be removed.
 * ACC_UDSDEMO_KEY_FROM_BUF and ACC_UDSDEMO_SEED_TO_BUF are not explicit cast.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 * Acc_UdsDemoGetSeed, the seed will be modify.
 * Acc_UdsDemoVerifyKey, the key is declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 * ACC_UDSDEMO_KEY_FROM_BUF macro do not have side-effect.
 * ACC_UDSDEMO_SEED_TO_BUF macro do not have side-effect.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/
#if ((SECM_ACCESS_KEY_SIZE != 4u) && (SECM_ACCESS_KEY_SIZE != 2u))
#error "The size of a key is only four or two, other values are invalid."
#endif

#if ((SECM_ACCESS_SEED_SIZE != 4u) && (SECM_ACCESS_SEED_SIZE != 2u))
#error "The size of a seed is only four or two, other values are invalid."
#endif
/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#if (SECM_ACCESS_KEY_SIZE == 4u)
#define ACC_UDSDEMO_KEY_MASK                (0xA5CEFDB6UL)
#define ACC_UDSDEMO_KEY_FROM_BUF(buf)       BL_BE32_TO_MCU(buf)
#elif (SECM_ACCESS_KEY_SIZE == 2u)
#define ACC_UDSDEMO_KEY_MASK                (0xDFB6u)
#define ACC_UDSDEMO_KEY_FROM_BUF(buf)       BL_BE16_TO_MCU(buf)
#endif

#if (SECM_ACCESS_SEED_SIZE == 4u)
/** \brief It is used to calculate the random seed*/
#define ACC_UDSDEMO_RANDOM_SEED             (16807UL)
#define ACC_UDSDEMO_SEED_INITVALUE          (0x12350012UL)
#define ACC_UDSDEMO_SEED_TO_BUF(seed,buf)   BL_MCU_TO_BE32(buf,seed)
#elif (SECM_ACCESS_SEED_SIZE == 2u)
/** \brief It is used to calculate the random seed*/
#define ACC_UDSDEMO_RANDOM_SEED             (16807u)
#define ACC_UDSDEMO_SEED_INITVALUE          (0x1235u)
#define ACC_UDSDEMO_SEED_TO_BUF(seed,buf)   BL_MCU_TO_BE16(buf,seed)
#endif

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/
#if (SECM_ACCESS_SEED_SIZE == 4u)
typedef bl_u32_t bl_UdsDemoSeed_t;
#elif (SECM_ACCESS_SEED_SIZE == 2u)
typedef bl_u16_t bl_UdsDemoSeed_t;
#endif

#if (SECM_ACCESS_KEY_SIZE == 4u)
typedef bl_u32_t bl_UdsDemoKey_t;
#elif (SECM_ACCESS_KEY_SIZE == 2u)
typedef bl_u16_t bl_UdsDemoKey_t;
#endif

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief Calculate the key from the gs_UdsDemoSeed.*/
static bl_UdsDemoKey_t _Acc_UdsDemoCalculateKey(void);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
static bl_UdsDemoSeed_t gs_UdsDemoSeed;

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the DEMO security access used for UDS.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Acc_UdsDemoInit(void)
{
    gs_UdsDemoSeed = ACC_UDSDEMO_SEED_INITVALUE;

    return ;
}

/**************************************************************************//**
 *
 *  \details Make a new seed.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
void Acc_UdsDemoMakeNewSeed(void)
{
    gs_UdsDemoSeed *= ACC_UDSDEMO_RANDOM_SEED;

    return ;
}

/**************************************************************************//**
 *
 *  \details Get current seed value.
 *
 *  \param[out]  seed - the value of current seed.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Acc_UdsDemoGetSeed(bl_Buffer_t *seed)
{
    ACC_UDSDEMO_SEED_TO_BUF(gs_UdsDemoSeed,seed);

    return ;
}

/**************************************************************************//**
 *
 *  \details Verify the value of transmitted key whether is right.
 *
 *  \param[in]  key - the value of transmitted key.
 *
 *  \return If the transmitted key value is right return BL_ERR_OK, otherwise
 *          return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the transmitted key value is right.
 *  \retval BL_ERR_NOT_OK - the transmitted key value is NOT right.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t Acc_UdsDemoVerifyKey(const bl_Buffer_t *key)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_UdsDemoKey_t calKey;
    bl_UdsDemoKey_t tranKey;

    calKey = _Acc_UdsDemoCalculateKey();
    tranKey = ACC_UDSDEMO_KEY_FROM_BUF(key);

    if (calKey == tranKey)
    {
        ret = BL_ERR_OK;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details An algorithm is used to calculate the key by a seed.
 *
 *  \return the key value
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
static bl_UdsDemoKey_t _Acc_UdsDemoCalculateKey(void)
{
    bl_UdsDemoKey_t key;

    /*When the size of seed is 2, there will be a necessary explicit cast.*/
    key = (((bl_UdsDemoKey_t)gs_UdsDemoSeed ^ ACC_UDSDEMO_KEY_MASK)
                                + ACC_UDSDEMO_KEY_MASK);

    return key;
}



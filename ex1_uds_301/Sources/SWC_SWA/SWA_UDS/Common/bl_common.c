/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the common module.
 *
 *  \file       bl_common.c
 *  \ingroup    common_module
 *  \author     mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 15/03/2010 | hewei.zhang      | N/A | Boot010001
 *      03.00.00 | 15/09/2011 | mingqing.tang    | N/A | Boot030001
 *      05.00.00 | 19/06/2013 | mingqing.tang    | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_common.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 310,506,602,1503,1532,2103,3212,3227,3435,3453,3456 EOF*/
/*
 * MISRA-C:2004 11.4(310):Casting to different object pointer type.
 *
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameter delay is not a null pointer.
 *
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * MISRA-C:2004 14.1(1503):The function is defined but is not used within this
 * project.
 * these functions will be used When correlative macro is enable.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * 3212:This explicit cast is redundant and could be removed.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * MISRA-C:2004 19.4(3435):Parameter is used more than once in this macro.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 * These macros do not have side-effect.
 *
 * 3456:Parameter will be evaluated more than once when this macro is used.
 * When these macros is used, there is no side-effect.
 *
 */

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#define BL_BE32TOMCU(buf) (bl_u32_t)( (((bl_u32_t)(buf)[0] & 0xFFUL) << 24u)\
                                    | (((bl_u32_t)(buf)[1] & 0xFFUL) << 16u)\
                                    | (((bl_u32_t)(buf)[2] & 0xFFUL) << 8u)\
                                    | (((bl_u32_t)(buf)[3] & 0xFFUL) << 0u))

#define BL_LE32TOMCU(buf) (bl_u32_t)( (((bl_u32_t)(buf)[3] & 0xFFUL) << 24u)\
                                    | (((bl_u32_t)(buf)[2] & 0xFFUL) << 16u)\
                                    | (((bl_u32_t)(buf)[1] & 0xFFUL) << 8u)\
                                    | (((bl_u32_t)(buf)[0] & 0xFFUL) << 0u))

#define BL_BE16TOMCU(buf) (bl_u16_t)( (((bl_u16_t)(buf)[0] & 0x00FFu) << 8u)\
                                    | (((bl_u16_t)(buf)[1] & 0x00FFu) << 0u))

#define BL_LE16TOMCU(buf) (bl_u16_t)( (((bl_u16_t)(buf)[1] & 0x00FFu) << 8u)\
                                    | (((bl_u16_t)(buf)[0] & 0x00FFu) << 0u))

#define BL_LEFT_SHIFT_8BITS     (8)
#define BL_LEFT_SHIFT_16BITS    (16)
#define BL_LEFT_SHIFT_24BITS    (24)
#define BL_BYTE_FILL_VALUE      (0xFFu)

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief Copy the data from src to des.*/
static void _Bl_CopyData(bl_Buffer_t *des,
                            const bl_Buffer_t *src,
                            bl_Size_t size);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Copy the data from src to des.
 *
 *  \param[out] des  - the destination address.
 *  \param[in]  src  - the source address.
 *  \param[in]  size - the size of the data.
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
void Bl_MemCpy(bl_Buffer_t *des,const bl_Buffer_t *src, bl_Size_t size)
{
    if ((des != src) && (des != BL_NULL_PTR))
    {
        _Bl_CopyData(des,src,size);
    }

    return ;
}
/**************************************************************************//**
 *
 *  \details Set the data to src.
 *
 *  \param[out] des  - the destination address.
 *  \param[in]  src  - the source content.
 *  \param[in]  size - the size of the data.
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
void Bl_MemSet(bl_Buffer_t *des, bl_Buffer_t src, bl_Size_t size)
{
    bl_u32_t i;

    if (des != BL_NULL_PTR)
    {
        for (i = 0; i < size; i++)
        {
            des[i] = src;
        }
    }

    return;
}

/**************************************************************************//**
 *
 *  \details exchange the contents in a buffer to data.
 *
 *  \param[in] buf  - the contents of data
 *
 *  \since V3.0.0
 *
 *****************************************************************************/
bl_u16_t Bl_Be16ToMcu(const bl_Buffer_t *buf)
{
    bl_u16_t tmp;

#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)
    tmp = BL_BE16TOMCU(buf);
#elif (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON)
    _Bl_CopyData((bl_Buffer_t *)&tmp, buf, (bl_Size_t)sizeof(tmp));
#endif

    return _BL_BE16_TO_MCU(tmp);
}
/**************************************************************************//**
 *
 *  \details exchange the contents in a buffer to data.
 *
 *  \param[in] buf  - the contents of data
 *
 *  \since V3.0.0
 *
 *****************************************************************************/
bl_u16_t Bl_Le16ToMcu(const bl_Buffer_t *buf)
{
    bl_u16_t tmp;

#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)
    tmp = BL_LE16TOMCU(buf);
#elif (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON)
    _Bl_CopyData((bl_Buffer_t *)&tmp, buf, (bl_Size_t)sizeof(tmp));
#endif

    return _BL_LE16_TO_MCU(tmp);
}
/**************************************************************************//**
 *
 *  \details exchange the contents in a buffer to data.
 *
 *  \param[in] buf  - the contents of data
 *
 *  \since V3.0.0
 *
 *****************************************************************************/
bl_u32_t Bl_Be32ToMcu(const bl_Buffer_t *buf)
{
    bl_u32_t tmp;

#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)
    tmp = BL_BE32TOMCU(buf);
#elif (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON)
    _Bl_CopyData((bl_Buffer_t *)&tmp, buf, (bl_Size_t)sizeof(tmp));
#endif

    return _BL_BE32_TO_MCU(tmp);
}
/**************************************************************************//**
 *
 *  \details exchange the contents in a buffer to data.
 *
 *  \param[in] buf  - the contents of data
 *
 *  \since V3.0.0
 *
 *****************************************************************************/
bl_u32_t Bl_Le32ToMcu(const bl_Buffer_t *buf)
{
    bl_u32_t tmp;

#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)
    tmp = BL_LE32TOMCU(buf);
#elif (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON)
    _Bl_CopyData((bl_Buffer_t *)&tmp, buf, (bl_Size_t)sizeof(tmp));
#endif

    return _BL_LE32_TO_MCU(tmp);
}

/**************************************************************************//**
 *
 *  \details exchange the data to buffer.
 *
 *  \param[out] buf     - the buffer
 *  \param[in]  data    - the data
 *
 *  \since V5.0.0
 *
 *****************************************************************************/
void Bl_McuToBe16(bl_Buffer_t *buf, bl_u16_t data)
{
    bl_u16_t tmp;

    tmp = _BL_MCU_TO_BE16(data);

#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)

    buf[0] = (bl_Buffer_t)((tmp >> BL_LEFT_SHIFT_8BITS) & BL_BYTE_FILL_VALUE);
    buf[1] = (bl_Buffer_t)((tmp >> 0u) & BL_BYTE_FILL_VALUE);

#elif (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON)

    _Bl_CopyData(buf, (const bl_Buffer_t *)&tmp, (bl_Size_t)sizeof(tmp));

#endif
}

/**************************************************************************//**
 *
 *  \details exchange the data to buffer.
 *
 *  \param[out] buf     - the buffer
 *  \param[in]  data    - the data
 *
 *  \since V5.0.0
 *
 *****************************************************************************/
void Bl_McuToLe16(bl_Buffer_t *buf, bl_u16_t data)
{
    bl_u16_t tmp;

    tmp = _BL_MCU_TO_LE16(data);

#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)

    buf[0] = (bl_Buffer_t)((tmp >> 0u) & BL_BYTE_FILL_VALUE);
    buf[1] = (bl_Buffer_t)((tmp >> BL_LEFT_SHIFT_8BITS) & BL_BYTE_FILL_VALUE);

#elif (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON)

    _Bl_CopyData(buf, (const bl_Buffer_t *)&tmp, (bl_Size_t)sizeof(tmp));

#endif
}

/**************************************************************************//**
 *
 *  \details exchange the data to buffer.
 *
 *  \param[out] buf     - the buffer
 *  \param[in]  data    - the data
 *
 *  \since V5.0.0
 *
 *****************************************************************************/
void Bl_McuToBe32(bl_Buffer_t *buf, bl_u32_t data)
{
    bl_u32_t tmp;

    tmp = _BL_MCU_TO_BE32(data);

#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)

    buf[0] = (bl_Buffer_t)((tmp >> 0u) & BL_BYTE_FILL_VALUE);
    buf[1] = (bl_Buffer_t)((tmp >> BL_LEFT_SHIFT_8BITS) & BL_BYTE_FILL_VALUE);
    buf[2] = (bl_Buffer_t)((tmp >> BL_LEFT_SHIFT_16BITS) & BL_BYTE_FILL_VALUE);
    buf[3] = (bl_Buffer_t)((tmp >> BL_LEFT_SHIFT_24BITS) & BL_BYTE_FILL_VALUE);

#elif (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON)

    _Bl_CopyData(buf, (const bl_Buffer_t *)&tmp, (bl_Size_t)sizeof(tmp));

#endif
}

/**************************************************************************//**
 *
 *  \details exchange the data to buffer.
 *
 *  \param[out] buf     - the buffer
 *  \param[in]  data    - the data
 *
 *  \since V5.0.0
 *
 *****************************************************************************/
void Bl_McuToLe32(bl_Buffer_t *buf, bl_u32_t data)
{
    bl_u32_t tmp;

    tmp = _BL_MCU_TO_LE32(data);

#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)

    buf[0] = (bl_Buffer_t)((tmp >> BL_LEFT_SHIFT_24BITS) & BL_BYTE_FILL_VALUE);
    buf[1] = (bl_Buffer_t)((tmp >> BL_LEFT_SHIFT_16BITS) & BL_BYTE_FILL_VALUE);
    buf[2] = (bl_Buffer_t)((tmp >> BL_LEFT_SHIFT_8BITS) & BL_BYTE_FILL_VALUE);
    buf[3] = (bl_Buffer_t)((tmp >> 0u) & BL_BYTE_FILL_VALUE);

#elif (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON)

    _Bl_CopyData(buf, (const bl_Buffer_t *)&tmp, (bl_Size_t)sizeof(tmp));

#endif
}

/**************************************************************************//**
 *
 *  \details Copy the data from src to des.
 *
 *  \param[out] des  - the destination address.
 *  \param[in]  src  - the source address.
 *  \param[in]  size - the size of the data.
 *
 *  \since V3.0.0
 *
 *****************************************************************************/
static void _Bl_CopyData(bl_Buffer_t *des,
                            const bl_Buffer_t *src,
                            bl_Size_t size)
{
    bl_u32_t i;

    for (i = 0; i < size; i++)
    {
        des[i] = src[i];
    }
}


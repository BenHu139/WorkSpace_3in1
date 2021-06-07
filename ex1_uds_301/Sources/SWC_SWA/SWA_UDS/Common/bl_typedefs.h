/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to define base type used for bootloader.
 *
 *  \file       bl_typedefs.h
 *  \author     mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 15/03/2010 | hewei.zhang      | N/A | Boot010001
 *      01.01.00 | 16/06/2010 | hewei.zhang      | N/A | Boot010002
 *      02.00.00 | 16/05/2011 | mingqing.tang    | N/A | Boot020001
 *      02.01.00 | 25/05/2011 | mingqing.tang    | N/A | Boot020002
 *      03.00.00 | 15/09/2011 | mingqing.tang    | N/A | Boot030001
 *      04.00.00 | 20/10/2011 | mingqing.tang    | N/A | Boot040001
 *      05.00.00 | 19/06/2013 | mingqing.tang    | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_TYPEDEFS_H_
#define _BL_TYPEDEFS_H_

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3205,3412,3435,3453,3456 EOF*/
/*
 * 3205:The identifier is not used and could be removed.
 * The identifiers was used in other files or will be used for future.
 *
 * MISRA-C:2004 19.4(3412):Macro defines an unrecognized code-fragment.
 * BL_WAITFOR_TIMEOUT is only used to polling check a status.
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
 *  Macro Definitions
 *****************************************************************************/
#define BL_BYTE_WIDTH_8     (1)     /**< one byte width is 8bits(one byte)*/
#define BL_BYTE_WIDTH_16    (2)     /**< one byte width is 16bits(two bytes).*/

#define BL_MCU_TYPE_8       (8)     /**< the 8bits mcu.*/
#define BL_MCU_TYPE_16      (16)    /**< the 16bits mcu.*/
#define BL_MCU_TYPE_32      (32)    /**< the 32bits mcu.*/

#define BL_BYTE_BIG_ENDIAN      (0) /**< big endian for byte order.*/
#define BL_BYTE_LITTLE_ENDIAN   (1) /**< little endian for byte order.*/

#define BL_STATUS_NOT_INIT      (0) /**< the uninitialized status.*/
#define BL_STATUS_INITED        (1) /**< the initialized status.*/

#define BL_ERROR_ID_16BIT   (0xFFFFu) /**< Indicate a invalid ID.*/

#define BL_SECURITY_CLASS_DDD         (0x01u) /** security level DDD.*/
#define BL_SECURITY_CLASS_C           (0x02u) /** security level C.*/
#define BL_SECURITY_CLASS_CCC         (0x03u) /** security level CCC.*/
#define BL_SECURITY_CLASS_BBB         (0x04u) /** security level BBB.*/
#define BL_SECURITY_CLASS_AAA         (0x05u) /** security level AAA.*/

/** the macro is used to indicate that a function is disable.*/
#define BL_FUN_OFF      (0)
/** the macro is used to indicate that a function is enable.*/
#define BL_FUN_ON       (1)
/** the macro is used to indicate that a pointer is invalid.*/
#define BL_NULL_PTR     ((void *)0)
/** Only used to pass muster. It's not a valid pointer.*/
#define BL_VIRTUAL_PTR  ((void *)1)


/* the informations of this MCU.*/
/** Indicate the width of a byte in this MCU.*/
#define BL_BYTE_WIDTH   BL_BYTE_WIDTH_8
/** Indicate the byte order of this MCU.*/
#define BL_BYTE_ENDIAN  BL_BYTE_BIG_ENDIAN
/** Indicate the type of this mcu.*/
#define BL_MCU_TYPE     BL_MCU_TYPE_16

#define BL_FORCE_MEMACC_ALIGN   BL_FUN_ON
/** The debug function.*/
#define BL_DEBUG        BL_FUN_OFF
/** position a memory, near or far.*/
#define BL_MEMORY_POS
/** position a memory, near or far.*/
#define BL_VARIABLE_POS

#define BL_GET_LOW_HALF(byte)    ((byte) & 0x0Fu)
#define BL_GET_HIGH_HALF(byte)   ((byte) & 0xF0u)

/** swap bytes of the 16bits number.*/
#define __BL_SWAP16(n)  ((bl_u16_t)( \
                            (((bl_u16_t)(n) & (bl_u16_t)0x00FFu) << 8u) | \
                            (((bl_u16_t)(n) & (bl_u16_t)0xFF00u) >> 8u)))
/** swap bytes of the 32bits number.*/
#define __BL_SWAP32(n)  ((bl_u32_t)( \
                            (((bl_u32_t)(n) & (bl_u32_t)0x000000FFUL) << 24u)|\
                            (((bl_u32_t)(n) & (bl_u32_t)0x0000FF00UL) << 8u) |\
                            (((bl_u32_t)(n) & (bl_u32_t)0x00FF0000UL) >> 8u) |\
                            (((bl_u32_t)(n) & (bl_u32_t)0xFF000000UL) >> 24u)))


#if (BL_BYTE_ENDIAN == BL_BYTE_BIG_ENDIAN)

#define _BL_BE16_TO_MCU(n)  ((bl_u16_t)(n))

#define _BL_LE16_TO_MCU(n)  __BL_SWAP16(n)

#define _BL_BE32_TO_MCU(n)  ((bl_u32_t)(n))

#define _BL_LE32_TO_MCU(n)  __BL_SWAP32(n)

#define _BL_MCU_TO_BE16(n)  ((bl_u16_t)(n))

#define _BL_MCU_TO_LE16(n)  __BL_SWAP16(n)

#define _BL_MCU_TO_BE32(n)  ((bl_u32_t)(n))

#define _BL_MCU_TO_LE32(n)  __BL_SWAP32(n)

#else

#define _BL_BE16_TO_MCU(n)  __BL_SWAP16(n)

#define _BL_LE16_TO_MCU(n)  ((bl_u16_t)(n))

#define _BL_BE32_TO_MCU(n)  __BL_SWAP32(n)

#define _BL_LE32_TO_MCU(n)  ((bl_u32_t)(n))

#define _BL_MCU_TO_BE16(n)  __BL_SWAP16(n)

#define _BL_MCU_TO_LE16(n)  ((bl_u16_t)(n))

#define _BL_MCU_TO_BE32(n)  __BL_SWAP32(n)

#define _BL_MCU_TO_LE32(n)  ((bl_u32_t)(n))

#endif

#if ((BL_BYTE_WIDTH != BL_BYTE_WIDTH_8) || (BL_FORCE_MEMACC_ALIGN == BL_FUN_ON))

#define BL_BE16_TO_MCU(p)   Bl_Be16ToMcu((const bl_Buffer_t *)(p))

#define BL_LE16_TO_MCU(p)   Bl_Le16ToMcu((const bl_Buffer_t *)(p))

#define BL_BE32_TO_MCU(p)   Bl_Be32ToMcu((const bl_Buffer_t *)(p))

#define BL_LE32_TO_MCU(p)   Bl_Le32ToMcu((const bl_Buffer_t *)(p))

#define BL_MCU_TO_BE16(p,n) Bl_McuToBe16((bl_Buffer_t *)(p),(bl_u16_t)(n))

#define BL_MCU_TO_LE16(p,n) Bl_McuToLe16((bl_Buffer_t *)(p),(bl_u16_t)(n))

#define BL_MCU_TO_BE32(p,n) Bl_McuToBe32((bl_Buffer_t *)(p),(bl_u32_t)(n))

#define BL_MCU_TO_LE32(p,n) Bl_McuToLe32((bl_Buffer_t *)(p),(bl_u32_t)(n))

#else

#define BL_BE16_TO_MCU(p)   _BL_BE16_TO_MCU(*(const bl_u16_t *)(p))

#define BL_LE16_TO_MCU(p)   _BL_LE16_TO_MCU(*(const bl_u16_t *)(p))

#define BL_BE32_TO_MCU(p)   _BL_BE32_TO_MCU(*(const bl_u32_t *)(p))

#define BL_LE32_TO_MCU(p)   _BL_LE32_TO_MCU(*(const bl_u32_t *)(p))

#define BL_MCU_TO_BE16(p,n) *((bl_u16_t *)(p)) = _BL_MCU_TO_BE16(n)

#define BL_MCU_TO_LE16(p,n) *((bl_u16_t *)(p)) = _BL_MCU_TO_LE16(n)

#define BL_MCU_TO_BE32(p,n) *((bl_u32_t *)(p)) = _BL_MCU_TO_BE32(n)

#define BL_MCU_TO_LE32(p,n) *((bl_u32_t *)(p)) = _BL_MCU_TO_LE32(n)

#endif

#if (BL_BYTE_ENDIAN == BL_BYTE_BIG_ENDIAN)
#define BL_MAKE_LOCAL_U16(p)        BL_BE16_TO_MCU(p)
#define BL_LOCAL_U16_TO_BUF(p,n)    BL_MCU_TO_BE16(p,n)
#define BL_MAKE_LOCAL_U32(p)        BL_BE32_TO_MCU(p)
#define BL_LOCAL_U32_TO_BUF(p,n)    BL_MCU_TO_BE32(p,n)
#elif(BL_BYTE_ENDIAN == BL_BYTE_LITTLE_ENDIAN)
#define BL_MAKE_LOCAL_U16(p)        BL_LE16_TO_MCU(p)
#define BL_LOCAL_U16_TO_BUF(p,n)    BL_MCU_TO_LE16(p,n)
#define BL_MAKE_LOCAL_U32(p)        BL_LE32_TO_MCU(p)
#define BL_LOCAL_U32_TO_BUF(p,n)    BL_MCU_TO_LE32(p,n)
#else
#error "the byte endian is error!"
#endif

#if (BL_DEBUG == BL_FUN_ON)
/** \brief A valid debug assert macro.*/
#define BL_DO_DEBUG_ASSERT(cond,ret,retval) do{\
                                                if (!(cond))\
                                                {\
                                                    if ((ret) != 0)\
                                                        return (retval);\
                                                    else\
                                                        while(1);\
                                                }\
                                              }\
                                            while(0) /*lint !e717*/
/** \brief A valid debug assert macro.*/
#define BL_DO_DEBUG_ASSERT_NO_RET(cond)     do{\
                                                if (!(cond))\
                                                {\
                                                    while(1);\
                                                }\
                                              }\
                                            while(0) /*lint !e717*/
#else
/** \brief A null macro.*/
#define BL_DO_DEBUG_ASSERT(cond,ret,retval) ((void)0)
/** \brief A null macro.*/
#define BL_DO_DEBUG_ASSERT_NO_RET(cond)     ((void)0)
#endif

/** \brief a debug assert without return value.*/
#define BL_DEBUG_ASSERT_NO_RET(cond)    BL_DO_DEBUG_ASSERT_NO_RET(cond)
/** \brief a debug assert with return value.*/
#define BL_DEBUG_ASSERT_RET(cond,ret)   BL_DO_DEBUG_ASSERT(cond,1,ret)
/** \brief a debug assert.*/
#define BL_DEBUG_ASSERT(cond) BL_DEBUG_ASSERT_RET(cond,BL_ERR_ASSERT_FAILURE)
/** \brief a debug assert.*/
#define BL_DEBUG_ASSERT_PARAM(cond) BL_DEBUG_ASSERT_RET(cond,\
                                                    BL_ERR_ASSERT_PARAMETERS)
/** \brief a debug assert.*/
#define BL_DEBUG_ASSERT_CONFIG(cond) BL_DEBUG_ASSERT_RET(cond,\
                                                 BL_ERR_ASSERT_CONFIGURATION)
/** \brief Wait until the condition is true or the timer is timeout*/
#define BL_WAITFOR_TIMEOUT(timer,cond)  while((!(cond)) && ((timer) > 0)) \
                                                { (timer) -= 1;}


/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/
typedef unsigned char bl_u8_t;      /**< This is a unsigned type for 8 bits.*/
typedef unsigned short bl_u16_t;    /**< This is a unsigned type for 16 bits.*/
typedef unsigned long bl_u32_t;     /**< This is a unsigned type for 32 bits.*/
typedef unsigned long long bl_u64_t;

typedef signed char bl_s8_t;        /**< This is a signed type for 8 bits.*/
typedef signed short bl_s16_t;      /**< This is a signed type for 16 bits.*/
typedef signed long bl_s32_t;       /**< This is a signed type for 32 bits.*/

typedef bl_u32_t bl_Address_t;      /**< The address of the memory.*/
typedef bl_u32_t bl_Size_t;         /**< The size of the memory.*/
typedef bl_u16_t bl_BootingFlag_t;   /**< The flag of booting.*/

typedef bl_u16_t bl_BufferSize_t;   /**< The size of a buffer.*/
#if (BL_BYTE_WIDTH == BL_BYTE_WIDTH_8)
typedef bl_u8_t bl_Buffer_t;        /**< The type for buffer.*/
#elif (BL_BYTE_WIDTH == BL_BYTE_WIDTH_16)
typedef bl_u16_t bl_Buffer_t;       /**< The type for buffer.*/
#else
#error "the configuration of the width byte is invalid."
#endif

typedef bl_u8_t bl_ResponseCode_t;  /**< The response code for DCM.*/

typedef bl_u32_t bl_DownStatus_t;   /**< The download status.*/

typedef bl_u16_t bl_ComIfHandle_t;  /**< THe handle of communication module.*/


typedef enum _tag_Return
{
    /** Indicate that a function was successfully processed.*/
    BL_ERR_OK = 0,
    /** Indicate that a function was NOT successfully processed.*/
    BL_ERR_NOT_OK = 1,
    /** A debug assert failure is caused by the parameters of a function.*/
    BL_ERR_ASSERT_CONFIGURATION = 2,
    /** A debug assert failure is caused by the parameters of a function.*/
    BL_ERR_ASSERT_PARAMETERS = 3,
    /** A debug assert is failure.*/
    BL_ERR_ASSERT_FAILURE = 4,
    /** The buffer is busy*/
    BL_ERR_BUFFER_BUSY = 5,
    /** The size greater than the size of buffer*/
    BL_ERR_BUFFER_OVERFLOW = 6,
    BL_ERR_INVALID_FS = 7,
    BL_ERR_WRONG_SN = 8,
    BL_ERR_UNEXPECTED_FRAME = 9,
    /** The timerA used to cantp module is timeout*/
    BL_ERR_TIMEROUT_A = 10,
    /** The timerBs used to cantp module is timeout*/
    BL_ERR_TIMEROUT_BS = 11,
    /** The timerCr used to cantp module is timeout*/
    BL_ERR_TIMEROUT_CR = 12,
    /** The error codes defined by user is not smaller than this macro.*/
    BL_ERR_SYSTEM_LIMIT = 99,
    /**
     *  A error code, named '01', is used by user. It is only used for the
     *  internal interface of a module.
     */
    BL_ERR_USER_CODE_01 = 100,
    /** A error code, named '02', is used by user.*/
    BL_ERR_USER_CODE_02 = 101,
    /** A error code, named '03', is used by user.*/
    BL_ERR_USER_CODE_03 = 102,
    /** A error code, named '04', is used by user.*/
    BL_ERR_USER_CODE_04 = 103,
    /** A error code, named '05', is used by user.*/
    BL_ERR_USER_CODE_05 = 104,
    /** A error code, named '06', is used by user.*/
    BL_ERR_USER_CODE_06 = 105,
    /** A error code, named '07', is used by user.*/
    BL_ERR_USER_CODE_07 = 106
} bl_Return_t;  /**< Some values from a called function.*/

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


/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file of a crc algorithm, this algorithm is used
 *              by BZIP2.
 *
 *  \file       bl_crc32_bzip2.h
 *  \ingroup    security_manager_module
 *  \author     mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 25/03/2010 | hewei.zhang      | N/A | Boot010001
 *      02.00.00 | 18/05/2011 | mingqing.tang    | N/A | Boot020001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_CRC32_BZIP2_H_
#define _BL_CRC32_BZIP2_H_
#include "bl_typedefs.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3210,3447 EOF*/
/*
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_security_cfg.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The function Declarations are in the header file.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/** \brief The name of this crc32 algorithm.*/
#define CRC_ALGORITHM_NAME                  "crc32_bzip2"
/** \brief The polynomial of this crc32 algorithm.*/
#define CRC32_BZIP2_POLYNOMIAL              (0x04C11DB7UL)
/** \brief The final xor value of this crc32 algorithm.*/
#define CRC32_BZIP2_FINAL_XOR_VALUE         (0xFFFFFFFFUL)
/** \brief The initialization value of this crc32 algorithm.*/
#define CRC32_BZIP2_INIT_VALUE              (0xFFFFFFFFUL)
/** \brief The check value of this crc32 algorithm.*/
#define CRC32_BZIP2_CHECK_VALUE             (0xFC891918UL)

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
/** \brief Initialize the crc32 algorithm.*/
extern void Bzip2_Init(void);
/** \brief Start the crc32 algorithm.*/
extern void Bzip2_Start(void);
/** \brief Update the crc value.*/
extern bl_Return_t Bzip2_Update(bl_Size_t size, const bl_Buffer_t *data);
/** \brief Verify the crc value whether is right.*/
extern bl_Return_t Bzip2_Verify(bl_Size_t size, const bl_Buffer_t *hash);

#endif


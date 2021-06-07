/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file of the common module.
 *
 *  \file       bl_common.h
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
#ifndef _BL_COMMON_H_
#define _BL_COMMON_H_
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
/** \brief Copy the data from src to des.*/
extern void Bl_MemCpy(bl_Buffer_t *des,const bl_Buffer_t *src, bl_Size_t size);
/** \brief Set the stuff of the buffer.*/
extern void Bl_MemSet(bl_Buffer_t *des, bl_Buffer_t src, bl_Size_t size);

/** \brief Trans the big endian to cpu endain.*/
extern bl_u16_t Bl_Be16ToMcu(const bl_Buffer_t * buf);
/** \brief This function is used to get memory id.*/
extern bl_u16_t Bl_Le16ToMcu(const bl_Buffer_t * buf);
/** \brief This function is used to get memory id.*/
extern bl_u32_t Bl_Be32ToMcu(const bl_Buffer_t * buf);
/** \brief This function is used to get memory id.*/
extern bl_u32_t Bl_Le32ToMcu(const bl_Buffer_t * buf);

/** \brief This function is used to get memory id.*/
extern void Bl_McuToBe16(bl_Buffer_t * buf, bl_u16_t data);
/** \brief This function is used to get memory id.*/
extern void Bl_McuToLe16(bl_Buffer_t * buf, bl_u16_t data);
/** \brief This function is used to get memory id.*/
extern void Bl_McuToBe32(bl_Buffer_t * buf, bl_u32_t data);
/** \brief This function is used to get memory id.*/
extern void Bl_McuToLe32(bl_Buffer_t * buf, bl_u32_t data);
#endif


/*******************************************************************************
 
 !File            : Std_Types.h
 !Description     : Item loaded by Deliver in Web Client
 !Revision        : 3

 !Module          : Standard Types
 !Description     : Standard Types Definitions
 
 !Target          : MPC56xp / GHS

 !Coding language : C

 all rights reserved
 
*******************************************************************************/
#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

//#include "Compiler.h"
//#include "Platform_Types.h"


typedef unsigned char bool; 
typedef bool boolean;

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned long long u64;
typedef signed long long s64;

typedef signed char        sint8;
typedef unsigned char      uint8;

typedef signed short       sint16;
typedef unsigned short     uint16;

typedef signed long        sint32;
typedef unsigned long      uint32;

typedef unsigned long long uint64;

typedef uint8 Std_ReturnType;

/*
typedef float f32;
*/

/* Standard typedefs used by header files, based on ISO C standard */
//typedef signed char int8_t;
//typedef unsigned char uint8_t;
//typedef volatile signed char vint8_t;
//typedef volatile unsigned char vuint8_t;
//
//typedef signed short int16_t;
//typedef unsigned short uint16_t;
//typedef volatile signed short vint16_t;
//typedef volatile unsigned short vuint16_t;
//
//typedef signed long int32_t;
//typedef unsigned long uint32_t;
//typedef volatile signed long vint32_t;
//typedef volatile unsigned long vuint32_t;

#define ENABLE     1
#define DISABLE    0

#define NULL    (0)

#define STD_u32FULL         ((u32)0xFFFFFFFFU)
#define STD_u8FULL          ((u8) 0xFFU)

#define STD_bFALSE          ((boolean)0U)
#define STD_bTRUE           ((boolean)1U)

typedef enum {
   STD_E_OK = 0, /* !Comment : No error */
   STD_E_FAILED
} Std_tenuReturn;

typedef struct {
   u16 vendorID;
   u8  moduleID;
   u8  sw_major_version;
   u8  sw_minor_version;
   u8  sw_patch_version;
} Std_VersionType;


#ifndef STATUSTYPEDEFINED 
#define STATUSTYPEDEFINED 
#define E_OK 0x00u 
typedef unsigned char StatusType; /* !Comment : OSEK compliance */ 
#endif 
#define E_NOT_OK 0x01u 

#define STD_HIGH     0x01u       /* !Comment : Physical state 5V or 3.3V      */
#define STD_LOW      0x00u       /* !Comment : Physical state 0V              */


#define STD_ACTIVE   0x01u       /* !Comment: Logical state active            */
#define STD_IDLE     0x00u       /* !Comment: Logical state idle              */


#define STD_ON       0x01u
#define STD_OFF      0x00u

#define RELAY_ON     0x01u
#define RELAY_OFF    0x00u

#define B28950_ENA    0x00u
#define B28950_DIS    0x01u

/******************************************************************************/
/* !Description : CPU types defintion                                         */
/* !Trace-to : SWS_Platform_00064                                             */
/* !Trace-to : SWS_Platform_00057                                             */
/******************************************************************************/
#define CPU_TYPE_8       8
#define CPU_TYPE_16     16
#define CPU_TYPE_32     32


/******************************************************************************/
/* !Description : CPU  bits Order                                             */
/* !Trace-to : SWS_Platform_00038                                             */
/******************************************************************************/
#define MSB_FIRST        0
#define LSB_FIRST        1


/******************************************************************************/
/* !Description : CPU  Byte Order                                             */
/* !Trace-to : SWS_Platform_00039                                             */
/******************************************************************************/
#define HIGH_BYTE_FIRST  0
#define LOW_BYTE_FIRST   1


/******************************************************************************/
/* !Description : boolean value                                               */
/* !Trace-to : PLATFORM054, PLATFORM055, PLATFORM056                          */
/******************************************************************************/
#ifndef TRUE
   #define TRUE 1
#endif
#ifndef FALSE
   #define FALSE 0
#endif

#define DEF_NULL (0)

#define CPU_TYPE        CPU_TYPE_32
#define CPU_BIT_ORDER   MSB_FIRST
#define CPU_BYTE_ORDER  HIGH_BYTE_FIRST


#endif


/*-------------------------------- end of file -------------------------------*/

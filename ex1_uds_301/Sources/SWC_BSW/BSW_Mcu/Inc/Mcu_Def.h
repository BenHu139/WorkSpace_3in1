
/*------------------------ END MANAGEMENT OF EVOLUTIONS ---------------------*/
/* ***************************************************************************/

#ifndef MCU_DEF_H_
#define MCU_DEF_H_

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Std_Types.h"

/* ***************************************************************************/
/*                                 MACROS                                    */
/* ***************************************************************************/
/* !Comment: define the PCTL register number */
#define MCU_PCTL_MAX  ((u8) 19)

/* !Comment : MCU Mode Definition */
#define RESET_MODE          0
#define TEST_MODE           1
#define SAFE_MODE           2
#define DRUN_MODE           3
#define RUN0_MODE           4
#define RUN1_MODE           5
#define RUN2_MODE           6
#define RUN3_MODE           7
#define HALT0_MODE          8

/* ***************************************************************************/
/*                                 TYPES                                     */
/* ***************************************************************************/
typedef enum
{
  MCU_ME_RUN0 = 0, 
  MCU_ME_RUN1, 
  MCU_ME_RUN2, 
  MCU_ME_RUN3
} MCU_tenuRunModes;
typedef enum
{
  MCU_ME_RUNPC0 = 0,
  MCU_ME_RUNPC1,
  MCU_ME_RUNPC2,
  MCU_ME_RUNPC3,
  MCU_ME_RUNPC4,
  MCU_ME_RUNPC5,
  MCU_ME_RUNPC6,
  MCU_ME_RUNPC7
} MCU_tenuRunPcModes;

typedef enum
{
  MCU_ME_LPPC0 = 0,
  MCU_ME_LPPC1,
  MCU_ME_LPPC2,
  MCU_ME_LPPC3,
  MCU_ME_LPPC4,
  MCU_ME_LPPC5,
  MCU_ME_LPPC6,
  MCU_ME_LPPC7
} MCU_tenuLpPcModes;
/* ***************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/* ***************************************************************************/

/* ***************************************************************************/
/*                                 PROTOTYPES                                */
/* ***************************************************************************/

#endif


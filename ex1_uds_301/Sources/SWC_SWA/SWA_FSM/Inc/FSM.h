
/* ***************************************************************************/
#ifndef FSM_H
#define FSM_H
/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Std_Types.h"
#include "Rte_Data.h"
/* ***************************************************************************/
/*                                 MACROS                                    */
/* ***************************************************************************/
#define FSM_WORKING_INIT              0
#define FSM_WORKING_STANDBY           1
#define FSM_WORKING_PRECHARGE         2
#define FSM_WORKING_BUCK              3
#define FSM_WORKING_SW_FAULT          4
#define FSM_WORKING_HW_FAULT          5
#define FSM_WORKING_PREPARESLEEP      6
#define FSM_WORKING_SHUTDOWN          7

#define CUSTOMER_WORKING_INIT			 0
#define CUSTOMER_WORKING_READY			 1
#define CUSTOMER_WORKING_RUN             2
#define CUSTOMER_WORKING_STOP            3
#define CUSTOMER_WORKING_SHUTDOWN        4
#define CUSTOMER_WORKING_ERROR           5

#define FSM_KL15_INVALID          FALSE
#define FSM_KL15_VALID            TRUE 

#define FSM_WAKEUPSLEEP_SLEEP     TRUE

/* ***************************************************************************/
/*                                 TYPES                                     */
/* ***************************************************************************/


/* ****************************************************************************/
/*                         VARIABLE  DEFINITION                               */
/* ****************************************************************************/


/* ***************************************************************************/
/*                                 PROTOTYPES                                */
/* ***************************************************************************/
extern void FSM_vidInit(void);
extern void FSM_vidMainFunc(void);

#endif

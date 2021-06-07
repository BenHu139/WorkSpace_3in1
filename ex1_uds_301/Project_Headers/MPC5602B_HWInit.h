/*
 * FILE : MPC5602B_HWInit.h
 *
 * DESCRIPTION:
 *  This file contains the functions prototypes for initializing
 *  the MPC5602B derivative.
 *
 *  VERSION: 1.0
 */

#ifndef _MPC5602B_HWINIT_H_
#define _MPC5602B_HWINIT_H_

/*----------------------------------------------------------------------------*/
/* Includes                                                                   */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************/
/* User hardware initialization for MPC5602B derivative           */
/*******************************************************/ 

/* Derivative specific hardware initialization. */
__asm void INIT_Derivative(void); 

/*----------------------------------------------------------------------------*/
/* Function declarations                                                      */
/*----------------------------------------------------------------------------*/

/* call this function to setup the external bus or external memory.
*/
__asm void INIT_ExternalBusAndMemory(void);

#ifdef __cplusplus
}
#endif

#endif

/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : mpc5604cbootloader
 *
 * Project File           : mpc5604cbootloader.rsp
 *
 * Revision Number        : 1.0
 *
 * Tool Version           : 1.3.1.6
 *
 * file                   : intc_software.h
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5604C
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 18-Jul-2013 18:21:27
 *
 * Created on Date        : 18-Jul-2013 18:21:29
 *
 * Brief Description      : This  file contains  the interrupt service routine  for the Software
 *
 *
 *######################################################################
*/

#ifndef  _INTC_SOFTWARE_H
#define  _INTC_SOFTWARE_H
/********************  Dependent Include files here **********************/

#include "MPC5602B.h"

/**********************  Function Prototype here *************************/

void software_interrupt_handler0(void);
void software_interrupt_handler1(void);


#endif  /*_INTC_SOFTWARE_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/


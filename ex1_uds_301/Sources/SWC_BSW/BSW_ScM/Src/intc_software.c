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
 * file                   : intc_software.c
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
 ******************************************************************************** 
 *
 * Detail Description     : This file is generated when Software function is
 *                         defined in INTC peripheral.This file contains the
 *                         Interrupt handlers routines for Software . In
 *                         Interrupt handlers routine respective flags are cleared.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "intc_software.h"


/************************* INTERRUPT HANDLERS ************************/

void software_interrupt_handler0 (void)
{
    INTC.SSCIR[0].B.CLR=1;

}


void software_interrupt_handler1 (void)
{
    INTC.SSCIR[1].B.CLR=1;

}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/


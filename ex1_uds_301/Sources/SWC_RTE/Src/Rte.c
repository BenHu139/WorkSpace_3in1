
/* ****************************************************************************/

/* !Comment: Included File             */
#include "Rte.h"
#include "SAM.h"
#include "DSM.h"
#include "MSM.h"
#include "TCM.h"
#include "TMR.h"
#include "Dem_Types.h"
#include "Dem_Lcfg.h"
#include "Dem.h"
#include "Nvm.h"
#include "uds_main_schudle.h"



/* ************************************************************************** */
/*                                 MACROS                                     */
/* ************************************************************************** */


/* ************************************************************************** */
/*                                 TYPES                                      */
/* ************************************************************************** */


/* ************************************************************************** */
/*                              GLOABAL VARIRABLE                             */
/* ************************************************************************** */

/* ************************************************************************** */
/*                           SOURCE CODE                                      */
/* ************************************************************************** */

/* *************************************************************************/
/* Function Name     : void Rte_vidTaskInit(void)                           */
/* Brief Description :                                                     */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Rte_vidTaskInit(void)
{
   SAM_vidInit();
   DSM_vidInit();
   MSM_vidInit();
   TCM_vidInit();
   TMR_vidInit();
   Adpt_UdsInit();
   NvM_Init();
   Dem_Init();
}
/* *************************************************************************/
/* Function Name     : void Rte_vidTask2Ms(void)                           */
/* Brief Description :                                                     */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Rte_vidTask2Ms(void)
{
   SAM_vidSenMainFunc();
   SAM_vidActMainFunc();
   TMR_SYSTEM_TIME_event();
}
/* *************************************************************************/
/* Function Name     : void Rte_vidTask5Ms(void)                           */
/* Brief Description :                                                     */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Rte_vidTask5Ms(void)
{
   DSM_vidMainFunc();
}
/* *************************************************************************/
/* Function Name     : void Rte_vidTask10Ms(void)                           */
/* Brief Description :                                                     */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Rte_vidTask10Ms(void)
{
   MSM_vidMainFunc();
   TCM_vidMainFunc();
   Dem_SetEventStatus(DTC_0xFE00B0_INDEX, DEM_EVENT_STATUS_PREFAILED);
   Adpt_UdsPeriodicCallback();
}

/* ************** End of The File *************************************** */

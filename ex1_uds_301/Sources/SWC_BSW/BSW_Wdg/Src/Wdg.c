
/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Wdg.h"
#include "Dio.h"

/*****************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/*****************************************************************************/
/* !comment: counter for watch dog */
u8 Wdg_u8TimeCounter = WDG_COUNTER_RESET;
/* !comment: flag to indicate port set or not */
boolean Wdg_bPortSetState;

/* ***************************************************************************/
/*                              SOURCE CODE                                  */
/* ***************************************************************************/

/* *************************************************************************/
/* Function Name     : void Wdg_vidRefresh(void)                           */
/* Brief Description : feed the watch dog                                  */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            : the watch dog period is 60.7ms                      */
/* *************************************************************************/
void Wdg_vidRefresh(void)
{

   Wdg_u8TimeCounter++;

   if (Wdg_u8TimeCounter >= WDG_COUNTER_TIMEOUT)
    {
      Wdg_u8TimeCounter =0;

      Dio_vidToggleOutputCh(E_DOUT_WTD);
    }
}

/* *************************************************************************/
/* Function Name     : void Wdg_vidRefresh(void)                           */
/* Brief Description : feed the watch dog                                  */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            : the watch dog period is 60.7ms                      */
/* *************************************************************************/
void Wdg_vidFastRefresh(void)
{
   Dio_vidToggleOutputCh(E_DOUT_WTD);
}


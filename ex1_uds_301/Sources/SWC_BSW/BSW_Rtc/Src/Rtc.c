

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/

#include "includes.h"
#include "Rtc.h"

/******************************************************************************/
/* DATAS DEFINITION                                                           */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS DEFINITION                                                       */
/******************************************************************************/

/* *************************************************************************/
/* Function Name     : void Rtc_init(void)                                 */
/* Brief Description : RTC Configuration                                   */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Rtc_init(void)
{
   RtcDRVClokDivider(RTCDRV_CLK_DIVDER_64);
   STM.CR.B.FRZ = 1;
   STM.CNT.R = 0;
   RtcDRVDisable();
   RtcDRVCompIntDisable(0);
   RtcDRVRequestClrFlag(0);
   RtcDRVWriteCompValue(0, STM_RELOAD_VALUE);
}

/* *************************************************************************/
/* Function Name     : void Rtc_init(void)                                 */
/* Brief Description : RTC Configuration                                   */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Rtc_EnableNotification(void)
{
   RtcDRVRequestClrFlag(0);
   RtcDRVCompIntEnable(0);
}

/* *************************************************************************/
/* Function Name     : void Rtc_init(void)                                 */
/* Brief Description : RTC Configuration                                   */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Rtc_Start(void)
{
    RtcDRVEnable();
}


/* *************************************************************************/
/* Function Name     : void Rtc_init(void)                                 */
/* Brief Description : RTC Configuration                                   */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
void Rtc_Stop(void)
{
   RtcDRVRequestClrFlag(0);
   RtcDRVCompIntDisable(0);
   RtcDRVDisable();
}

/* *************************************************************************/
/* Function Name     : void Rtc_init(void)                                 */
/* Brief Description : RTC Configuration                                   */
/* Input Parameters  :                                                     */
/* Output Parameters :                                                     */
/* Others            :                                                     */
/* *************************************************************************/
uint32 Rtc_u32GetBaseTimerCnt(void)
{
   return RtcDRVCntRead();
}


/*-------------------------------- end of file -------------------------------*/




/* ****************************************************************************/
/*                                 INCLUDE                                    */
/* ****************************************************************************/
#include "Adc.h"
#include "Dio.h"
#include "PWM.h"


/* *************************************************************************************/
/*                                                                                     */
/* !Description: Write the digital output channel                                      */
/*                                                                                     */
/* *************************************************************************************/

void IoHwAb_vidWrOcpRst(boolean udtValue)
{
   Dio_vidWriteOutputCh(E_DOUT_OCP_RST, udtValue);
}

void IoHwAb_vidWrCcOut680(boolean udtValue)
{
   Dio_vidWriteOutputCh(E_DOUT_CC_OUT_680, udtValue);
}

void IoHwAb_vidWrCpCtrlS2(boolean udtValue)
{
   Dio_vidWriteOutputCh(E_DOUT_CP_CTL_S2, udtValue);
}

void IoHwAb_vidWrVcuEna(boolean udtValue)
{
   Dio_vidWriteOutputCh(E_DOUT_VCU_ENA, udtValue);
}

void IoHwAb_vidWrUcc28950Ssen(boolean udtValue)
{
   Dio_vidWriteOutputCh(E_DOUT_UCC28950_SSEN, udtValue);
}

void IoHwAb_vidWrFlyBackEna(boolean udtValue)
{
   Dio_vidWriteOutputCh(E_DOUT_FLY_BACK_ENA, udtValue);
}

void IoHwAb_vidWrFlyBackOff(boolean udtValue)
{
   Dio_vidWriteOutputCh(E_DOUT_FLY_BACK_OFF, udtValue);
}

void IoHwAb_vidWrDcdcPrt(boolean udtValue)
{
	Dio_vidWriteOutputCh(E_DOUT_DCDC_PRT, udtValue);
}

void IoHwAb_vidWrMcuPwrCtrl(boolean udtValue)
{
	Dio_vidWriteOutputCh(E_DOUT_MCU_PWR_CTL, udtValue);
}

void IoHwAb_vidWrPCC(boolean udtValue)
{
	Dio_vidWriteOutputCh(E_DOUT_PCC, udtValue);
}

void IoHwAb_vidWrOutSwEn(boolean udtValue)
{
	Dio_vidWriteOutputCh(E_DOUT_OUT_SW_EN, udtValue);
}

 boolean IoHwAb_vidRdOcpRst()
 {
	 return Dio_bReadOutputCh(E_DOUT_OCP_RST);
 }
 
 boolean IoHwAb_vidRdCcOut680()
 {
	 return Dio_bReadOutputCh(E_DOUT_CC_OUT_680);
 }
 
 boolean IoHwAb_vidRdCpCtrlS2()
 {
	 return Dio_bReadOutputCh(E_DOUT_CP_CTL_S2);
 }
 
 boolean IoHwAb_vidRdVcuEna()
 {
	 return Dio_bReadOutputCh(E_DOUT_VCU_ENA);
 }
 
 boolean IoHwAb_vidRdUcc28950Ssen()
 {
	 return Dio_bReadOutputCh(E_DOUT_UCC28950_SSEN);
 }
 
 boolean IoHwAb_vidRdFlyBackEna()
 {
	 return Dio_bReadOutputCh(E_DOUT_FLY_BACK_ENA);
 }
 
 boolean IoHwAb_vidRdFlyBackOff()
 {
	 return Dio_bReadOutputCh(E_DOUT_FLY_BACK_OFF);
 }
 
 boolean IoHwAb_vidRdDcdcPrt()
 {
	 return Dio_bReadOutputCh(E_DOUT_DCDC_PRT);
 }
 
 boolean IoHwAb_vidRdMcuPwrCtrl()
 {
	 return Dio_bReadOutputCh(E_DOUT_MCU_PWR_CTL);
 }
 
/* *************************************************************************************/
/*                                                                                     */
/* !Description: Write the PWM output channel                                          */
/*                                                                                     */
/* *************************************************************************************/

void IoHwAb_vidWrPWMVadj(uint16 udtValue)
{
   PMW_vidSetVadjDuty(udtValue);
}

void IoHwAb_vidWrPWMIadj(uint16 udtValue)
{
   PMW_vidSetIadjDuty(udtValue);
}

/* *************************************************************************************/
/*                                                                                     */
/* !Description: Enable the PWM output channel                                         */
/*                                                                                     */
/* *************************************************************************************/

void IoHwAb_vidWrPWMVadjEnable(boolean udtValue)
{
   if(udtValue)
   {
      PWM_vidOutPutEnableChannel(PWM_VADJ);
   }
   else
   {
      PWM_vidOutputDisChannel(PWM_VADJ);
   }
}

void IoHwAb_vidWrPWMIadjEnable(boolean udtValue)
{
   if(udtValue)
   {
      PWM_vidOutPutEnableChannel(PWM_IADJ);
   }
   else
   {
      PWM_vidOutputDisChannel(PWM_IADJ);
   }
}

/*------------------------------ end of file -------------------------------------------------------------------------*/


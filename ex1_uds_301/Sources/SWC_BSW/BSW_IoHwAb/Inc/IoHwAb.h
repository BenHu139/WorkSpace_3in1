
/*------------------------ END MANAGEMENT OF EVOLUTIONS ---------------------*/
/* ***************************************************************************/

#ifndef IOHWAB_H_
#define IOHWAB_H_

/* ****************************************************************************/
/*                                 INCLUDE                                    */
/* ****************************************************************************/

extern void IoHwAb_vidWrOcpRst(boolean udtValue);
extern void IoHwAb_vidWrCcOut680(boolean udtValue);
extern void IoHwAb_vidWrCpCtrlS2(boolean udtValue);
extern void IoHwAb_vidWrVcuEna(boolean udtValue);
extern void IoHwAb_vidWrUcc28950Ssen(boolean udtValue);
extern void IoHwAb_vidWrFlyBackEna(boolean udtValue);
extern void IoHwAb_vidWrFlyBackOff(boolean udtValue);
extern void IoHwAb_vidWrDcdcPrt(boolean udtValue);
extern void IoHwAb_vidWrMcuPwrCtrl(boolean udtValue);
extern void IoHwAb_vidWrPCC(boolean udtValue);
extern void IoHwAb_vidWrOutSwEn(boolean udtValue);

extern boolean IoHwAb_vidRdOcpRst();
extern boolean IoHwAb_vidRdCcOut680();
extern boolean IoHwAb_vidRdCpCtrlS2();
extern boolean IoHwAb_vidRdVcuEna();
extern boolean IoHwAb_vidRdUcc28950Ssen();
extern boolean IoHwAb_vidRdFlyBackEna();
extern boolean IoHwAb_vidRdFlyBackOff();
extern boolean IoHwAb_vidRdDcdcPrt();
extern boolean IoHwAb_vidRdMcuPwrCtrl();

extern void IoHwAb_vidWrPWMVadj(uint16 udtValue);
extern void IoHwAb_vidWrPWMIadj(uint16 udtValue);

extern void IoHwAb_vidWrPWMVadjEnable(boolean udtValue);
extern void IoHwAb_vidWrPWMIadjEnable(boolean udtValue);

/* ****************************************************************************/
/* DATA DEFINITION                                                            */
/* ****************************************************************************/


/* !Comment: function declaration                                          */
extern void IoHwAb_vidInit(void);
extern void IoHwAb_vidRefreshDI(void);
extern void IoHwAb_vidRefreshDO(void);
extern void IoHwAb_vidGetAdcResult(void);
#endif /* IoHwAb_API_H */

/*-------------------------------- end of file -------------------------------------------*/

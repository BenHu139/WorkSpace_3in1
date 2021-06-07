
/* all rights reserved                                                        */
/* ****************************************************************************/

#ifndef RTE_DATA_H
#define RTE_DATA_H

/* !Comment: Included File             */
#include "Std_Types.h"


/* ************************************************************************** */
/*                                 MACROS                                     */
/* ************************************************************************** */

#define Rte_bGet(udtId)                (Rte_bGet_##udtId())
#define Rte_u8Get(udtId)               (Rte_u8Get_##udtId())
#define Rte_s8Get(udtId)               (Rte_s8Get_##udtId())
#define Rte_u16Get(udtId)              (Rte_u16Get_##udtId())
#define Rte_s16Get(udtId)              (Rte_s16Get_##udtId())
#define Rte_u32Get(udtId)              (Rte_u32Get_##udtId())
#define Rte_s32Get(udtId)              (Rte_s32Get_##udtId())
#define Rte_f32Get(udtId)              (Rte_f32Get_##udtId())

#define Rte_bSet(udtId, udtValue)      (Rte_vidSet_##udtId(udtValue))
#define Rte_u8Set(udtId, udtValue)     (Rte_vidSet_##udtId(udtValue))
#define Rte_s8Set(udtId, udtValue)     (Rte_vidSet_##udtId(udtValue))
#define Rte_u16Set(udtId, udtValue)    (Rte_vidSet_##udtId(udtValue))
#define Rte_s16Set(udtId, udtValue)    (Rte_vidSet_##udtId(udtValue))
#define Rte_u32Set(udtId, udtValue)    (Rte_vidSet_##udtId(udtValue))
#define Rte_s32Set(udtId, udtValue)    (Rte_vidSet_##udtId(udtValue))
#define Rte_f32Set(udtId, udtValue)    (Rte_vidSet_##udtId(udtValue))

/* ************************************************************************** */
/*                                 TYPES                                      */
/* ************************************************************************** */


/* ************************************************************************** */
/*                              GLOABAL VARIRABLE                             */
/* ************************************************************************** */
/* !Comment: CANͨ��״̬ */
extern uint8	Rte_u8CAN_ComState;
#define Rte_u8Get_CAN_ComState()				(Rte_u8CAN_ComState)
#define Rte_vidSet_CAN_ComState(udtValue)		(Rte_u8CAN_ComState = udtValue)

/* !Comment: CAN busoff״̬λ */
extern uint8	Rte_u8CAN_BusoffSt;
#define Rte_u8Get_CAN_BusoffSt()				(Rte_u8CAN_BusoffSt)
#define Rte_vidSet_CAN_BusoffSt(udtValue)		(Rte_u8CAN_BusoffSt = udtValue)

/* !Comment: CAN ���ձ���״̬λ */
extern uint8	Rte_u8CAN_MsgRxSt;
#define Rte_u8Get_CAN_MsgRxSt()				(Rte_u8CAN_MsgRxSt)
#define Rte_vidSet_CAN_MsgRxSt(udtValue)		(Rte_u8CAN_MsgRxSt = udtValue)

/* !Comment: UARTͨ��״̬ */
extern uint8	Rte_u8UART_ComState;
#define Rte_u8Get_UART_ComState()				(Rte_u8UART_ComState)
#define Rte_vidSet_UART_ComState(udtValue)		(Rte_u8UART_ComState = udtValue)

/* !Comment: CAN���������ѹ */
extern uint16	Rte_u16CAN_UBuckReq;
#define Rte_u16Get_CAN_UBuckReq()				(Rte_u16CAN_UBuckReq)
#define Rte_vidSet_CAN_UBuckReq(udtValue)		(Rte_u16CAN_UBuckReq = udtValue)

/* !Comment: CANԤ��ָ�� */
extern boolean	Rte_bCAN_ModeReq;
#define Rte_bGet_CAN_ModeReq()				(Rte_bCAN_ModeReq)
#define Rte_vidSet_CAN_ModeReq(udtValue)		(Rte_bCAN_ModeReq = udtValue)




/* !Comment: BMS����������ѹ */
extern uint16	Rte_u16BMS_MaxChgVol;
#define Rte_u16Get_BMS_MaxChgVol()				(Rte_u16BMS_MaxChgVol)
#define Rte_vidSet_BMS_MaxChgVol(udtValue)		(Rte_u16BMS_MaxChgVol = udtValue)

/* !Comment: BMS������������ */
extern uint16	Rte_u16BMS_MaxChgCur;
#define Rte_u16Get_BMS_MaxChgCur()				(Rte_u16BMS_MaxChgCur)
#define Rte_vidSet_BMS_MaxChgCur(udtValue)		(Rte_u16BMS_MaxChgCur = udtValue)

/* !Comment: BMS�Լ�״̬ */
extern uint8	Rte_u8BMS_SelfChkSt;
#define Rte_u8Get_BMS_SelfChkSt()				(Rte_u8BMS_SelfChkSt)
#define Rte_vidSet_BMS_SelfChkSt(udtValue)		(Rte_u8BMS_SelfChkSt = udtValue)

/* !Comment: BMS����OBC����ָ�� */
extern uint8	Rte_u8BMS_ObcCtrlCmd;
#define Rte_u8Get_BMS_ObcCtrlCmd()				(Rte_u8BMS_ObcCtrlCmd)
#define Rte_vidSet_BMS_ObcCtrlCmd(udtValue)		(Rte_u8BMS_ObcCtrlCmd = udtValue)

/* !Comment: BMS����OBC����ģʽ */
extern uint8	Rte_u8BMS_ObcWorkMode;
#define Rte_u8Get_BMS_ObcWorkMode()				(Rte_u8BMS_ObcWorkMode)
#define Rte_vidSet_BMS_ObcWorkMode(udtValue)		(Rte_u8BMS_ObcWorkMode = udtValue)

/* WuLing!Comment: ��ذ������̵���״̬ */
extern uint8	Rte_u8Bat_MaPosRlySts;
#define Rte_u8Get_Bat_MaPosRlySts()				(Rte_u8Bat_MaPosRlySts)
#define Rte_vidSet_Bat_MaPosRlySts(udtValue)	(Rte_u8Bat_MaPosRlySts = udtValue)

/* WuLing!Comment: ��ذ������̵���״̬ */
extern uint8	Rte_u8Bat_MaNegRlySts;
#define Rte_u8Get_Bat_MaNegRlySts()				(Rte_u8Bat_MaNegRlySts)
#define Rte_vidSet_Bat_MaNegRlySts(udtValue)	(Rte_u8Bat_MaNegRlySts = udtValue)

/* WuLing!Comment: ��ذ����״̬�ź� */
extern uint8	Rte_u8Bat_ChrgSts;
#define Rte_u8Get_Bat_ChrgSts()					(Rte_u8Bat_ChrgSts)
#define Rte_vidSet_Bat_ChrgSts(udtValue)		(Rte_u8Bat_ChrgSts = udtValue)

/* WuLing!Comment: ��ذ����ȼ̵���״̬  */
extern uint8	Rte_u8Bat_HeRlySts;
#define Rte_u8Get_Bat_HeRlySts()				(Rte_u8Bat_HeRlySts)
#define Rte_vidSet_Bat_HeRlySts(udtValue)		(Rte_u8Bat_HeRlySts = udtValue)

/* WuLing!Comment: ��ذ�����״̬  */
extern uint8	Rte_u8Bat_HeSts;
#define Rte_u8Get_Bat_HeSts()					(Rte_u8Bat_HeSts)
#define Rte_vidSet_Bat_HeSts(udtValue)			(Rte_u8Bat_HeSts = udtValue)

/* WuLing!Comment: ��������ģʽ  */
extern uint8	Rte_u8Vec_OptMod;
#define Rte_u8Get_Vec_OptMod()					(Rte_u8Vec_OptMod)
#define Rte_vidSet_Vec_OptMod(udtValue)			(Rte_u8Vec_OptMod = udtValue)

/* WuLing!Comment: �����������  */
extern uint8	Rte_u8Vec_ChrgRqst;
#define Rte_u8Get_Vec_ChrgRqst()				(Rte_u8Vec_ChrgRqst)
#define Rte_vidSet_Vec_ChrgRqst(udtValue)		(Rte_u8Vec_ChrgRqst = udtValue)

/* WuLing!Comment: DCDCʹ���źţ����� */
extern boolean Rte_bDCDC_Enable;
#define Rte_bGet_DCDC_Enable()              	(Rte_bDCDC_Enable)
#define Rte_vidSet_DCDC_Enable(udtValue)      	(Rte_bDCDC_Enable = udtValue)

/* WuLing!Comment: IPS��ǰ״̬  */
extern uint8	Rte_u8IPS_State;
#define Rte_u8Get_IPS_State()				(Rte_u8IPS_State)
#define Rte_vidSet_IPS_State(udtValue)		(Rte_u8IPS_State = udtValue)

/* WuLing!Comment: OBC���� ָʾ������ */
extern boolean Rte_bOBC_WakeUpEn;
#define Rte_bGet_OBC_WakeUpEn()              	(Rte_bOBC_WakeUpEn)
#define Rte_vidSet_OBC_WakeUpEn(udtValue)      	(Rte_bOBC_WakeUpEn = udtValue)

/* !Comment: Ԥ������ź�, ���� */
extern boolean Rte_bBSW_PCC;
#define Rte_bGet_BSW_PCC()              (Rte_bBSW_PCC)
#define Rte_vidSet_BSW_PCC(udtValue)      (Rte_bBSW_PCC = udtValue)

/* !Comment: ��ѹ����������ź�, ���� */
extern boolean Rte_bBSW_OutSwEn;
#define Rte_bGet_BSW_OutSwEn()              (Rte_bBSW_OutSwEn)
#define Rte_vidSet_BSW_OutSwEn(udtValue)      (Rte_bBSW_OutSwEn = udtValue)

/* !Comment: ģ����Ա��λ */
extern boolean	Rte_bBSW_EmuTestEnable;
#define Rte_bGet_BSW_EmuTestEnable()				(Rte_bBSW_EmuTestEnable)
#define Rte_vidSet_BSW_EmuTestEnable(udtValue)		(Rte_bBSW_EmuTestEnable = udtValue)

/* !Comment: IO���Ա��λ */
extern boolean	Rte_bBSW_IOTestEnable;
#define Rte_bGet_BSW_IOTestEnable()				(Rte_bBSW_IOTestEnable)
#define Rte_vidSet_BSW_IOTestEnable(udtValue)		(Rte_bBSW_IOTestEnable = udtValue)

/* !Comment: ���׮ģ�����ʹ��λ */
extern boolean	Rte_bBSW_CcEmuTstEna;
#define Rte_bGet_BSW_CcEmuTstEna()				(Rte_bBSW_CcEmuTstEna)
#define Rte_vidSet_BSW_CcEmuTstEna(udtValue)		(Rte_bBSW_CcEmuTstEna = udtValue)

/* !Comment: PFCģ�����ʹ��λ */
extern boolean	Rte_bBSW_PfcEmuTstEna;
#define Rte_bGet_BSW_PfcEmuTstEna()				(Rte_bBSW_PfcEmuTstEna)
#define Rte_vidSet_BSW_PfcEmuTstEna(udtValue)		(Rte_bBSW_PfcEmuTstEna = udtValue)

/* !Comment: LLCģ�����ʹ��λ */
extern boolean	Rte_bBSW_LlcEmuTstEna;
#define Rte_bGet_BSW_LlcEmuTstEna()				(Rte_bBSW_LlcEmuTstEna)
#define Rte_vidSet_BSW_LlcEmuTstEna(udtValue)		(Rte_bBSW_LlcEmuTstEna = udtValue)

/* !Comment: DCDCģ�����ʹ��λ */
extern boolean	Rte_bBSW_DcdcEmuTstEna;
#define Rte_bGet_BSW_DcdcEmuTstEna()				(Rte_bBSW_DcdcEmuTstEna)
#define Rte_vidSet_BSW_DcdcEmuTstEna(udtValue)		(Rte_bBSW_DcdcEmuTstEna = udtValue)




/* !Comment: CP��ѹֵ/PWM��ֵ */
extern uint8	Rte_u8BSW_CpVolAMP;
#define Rte_u8Get_BSW_CpVolAMP()				(Rte_u8BSW_CpVolAMP)
#define Rte_vidSet_BSW_CpVolAMP(udtValue)		(Rte_u8BSW_CpVolAMP = udtValue)

/* !Comment: CP��ѹ�����˲����ֵ */
extern uint16	Rte_u16BSW_CpFliterVoltADC;
#define Rte_u16Get_BSW_CpFliterVoltADC()				(Rte_u16BSW_CpFliterVoltADC)
#define Rte_vidSet_BSW_CpFliterVoltADC(udtValue)		(Rte_u16BSW_CpFliterVoltADC = udtValue)

/* !Comment: CP�źŵ�ռ�ձ� */
extern uint16	Rte_u16BSW_CpDutyCal;
#define Rte_u16Get_BSW_CpDutyCal()				(Rte_u16BSW_CpDutyCal)
#define Rte_vidSet_BSW_CpDutyCal(udtValue)		(Rte_u16BSW_CpDutyCal = udtValue)

/* !Comment: �����ź�: CP�źŵ�ռ�ձ� */
extern uint16	Rte_u16BSW_TstCpDutyCal;
#define Rte_u16Get_BSW_TstCpDutyCal()				(Rte_u16BSW_TstCpDutyCal)
#define Rte_vidSet_BSW_TstCpDutyCal(udtValue)		(Rte_u16BSW_TstCpDutyCal = udtValue)

/* !Comment: RC/RC+R4��ֵ */
extern uint16	Rte_u16BSW_CcRcOhmVal;
#define Rte_u16Get_BSW_CcRcOhmVal()				(Rte_u16BSW_CcRcOhmVal)
#define Rte_vidSet_BSW_CcRcOhmVal(udtValue)		(Rte_u16BSW_CcRcOhmVal = udtValue)



/* !Comment: TCAN 1043 ��������ź� , ����Ч, ���� */
extern boolean Rte_bBSW_CanFaultDI;    
#define Rte_bGet_BSW_CanFaultDI()				(Rte_bBSW_CanFaultDI)
#define Rte_vidSet_BSW_CanFaultDI(udtValue)		(Rte_bBSW_CanFaultDI = udtValue)

/* !Comment: ����������״̬, ����Ч, ����*/
extern boolean Rte_bBSW_LockStatusDI;		
#define Rte_bGet_BSW_LockStatusDI()				(Rte_bBSW_LockStatusDI)
#define Rte_vidSet_BSW_LockStatusDI(udtValue)		(Rte_bBSW_LockStatusDI = udtValue)

/* !Comment: CC��ǹ��绽��MCU�����ź� */
extern boolean	Rte_bBSW_CcPluginDI;
#define Rte_bGet_BSW_CcPluginDI()				(Rte_bBSW_CcPluginDI)
#define Rte_vidSet_BSW_CcPluginDI(udtValue)		(Rte_bBSW_CcPluginDI = udtValue)

/* !Comment: OBCʹ�������ź� */
extern boolean	Rte_bBSW_ObcEnaDI;
#define Rte_bGet_BSW_ObcEnaDI()				(Rte_bBSW_ObcEnaDI)
#define Rte_vidSet_BSW_ObcEnaDI(udtValue)		(Rte_bBSW_ObcEnaDI = udtValue)

/* !Comment: DCDCʹ�������ź� */
extern boolean	Rte_bBSW_DcdcEnaDI;
#define Rte_bGet_BSW_DcdcEnaDI()				(Rte_bBSW_DcdcEnaDI)
#define Rte_vidSet_BSW_DcdcEnaDI(udtValue)		(Rte_bBSW_DcdcEnaDI = udtValue)

/* !Comment: PFC����ر������ź� */
extern boolean	Rte_bUART_PfcStopUI;
#define Rte_bGet_UART_PfcStopUI()				(Rte_bUART_PfcStopUI)
#define Rte_vidSet_UART_PfcStopUI(udtValue)		(Rte_bUART_PfcStopUI = udtValue)

/* !Comment: LLCӲ�����������ź� */
extern boolean	Rte_bUART_LlcHardPrtUI;
#define Rte_bGet_UART_LlcHardPrtUI()				(Rte_bUART_LlcHardPrtUI)
#define Rte_vidSet_UART_LlcHardPrtUI(udtValue)		(Rte_bUART_LlcHardPrtUI = udtValue)

/* !Comment: ��ѹ���·�����ź� */
extern boolean	Rte_bBSW_LvShortM;
#define Rte_bGet_BSW_LvShortM()				(Rte_bBSW_LvShortM)
#define Rte_vidSet_BSW_LvShortM(udtValue)		(Rte_bBSW_LvShortM = udtValue)

/* !Comment: ��ѹ���������ź� */
extern boolean	Rte_bBSW_VoutInterLockDiag;
#define Rte_bGet_BSW_VoutInterLockDiag()				(Rte_bBSW_VoutInterLockDiag)
#define Rte_vidSet_BSW_VoutInterLockDiag(udtValue)		(Rte_bBSW_VoutInterLockDiag = udtValue)

/* !Comment: KL15 */
extern boolean	Rte_bBSW_KL15;
#define Rte_bGet_BSW_KL15()				(Rte_bBSW_KL15)
#define Rte_vidSet_BSW_KL15(udtValue)		(Rte_bBSW_KL15 = udtValue)




/* !Comment: �����ź�: OBCʹ������ */
extern boolean	Rte_bBSW_TstObcEnaDI;
#define Rte_bGet_BSW_TstObcEnaDI()				(Rte_bBSW_TstObcEnaDI)
#define Rte_vidSet_BSW_TstObcEnaDI(udtValue)		(Rte_bBSW_TstObcEnaDI = udtValue)

/* !Comment: �����ź�: DCDCʹ������ */
extern boolean	Rte_bBSW_TstDcdcEnaDI;
#define Rte_bGet_BSW_TstDcdcEnaDI()				(Rte_bBSW_TstDcdcEnaDI)
#define Rte_vidSet_BSW_TstDcdcEnaDI(udtValue)		(Rte_bBSW_TstDcdcEnaDI = udtValue)

/* !Comment: �����ź�: PFC����ر����� */
extern boolean	Rte_bUART_TstPfcStopUI;
#define Rte_bGet_UART_TstPfcStopUI()				(Rte_bUART_TstPfcStopUI)
#define Rte_vidSet_UART_TstPfcStopUI(udtValue)		(Rte_bUART_TstPfcStopUI = udtValue)

/* !Comment: �����ź�: LLCӲ���������� */
extern boolean	Rte_bUART_TstLlcHardPrtUI;
#define Rte_bGet_UART_TstLlcHardPrtUI()				(Rte_bUART_TstLlcHardPrtUI)
#define Rte_vidSet_UART_TstLlcHardPrtUI(udtValue)		(Rte_bUART_TstLlcHardPrtUI = udtValue)

/* !Comment: �����ź�: ��ѹ���·���� */
extern boolean	Rte_bBSW_TstLvShortM;
#define Rte_bGet_BSW_TstLvShortM()				(Rte_bBSW_TstLvShortM)
#define Rte_vidSet_BSW_TstLvShortM(udtValue)		(Rte_bBSW_TstLvShortM = udtValue)

/* !Comment: �����ź�: ��ѹ�������� */
extern boolean	Rte_bBSW_TstVoutInterLockDiag;
#define Rte_bGet_BSW_TstVoutInterLockDiag()				(Rte_bBSW_TstVoutInterLockDiag)
#define Rte_vidSet_BSW_TstVoutInterLockDiag(udtValue)		(Rte_bBSW_TstVoutInterLockDiag = udtValue)

/* !Comment: �����ź�: KL15 */
extern boolean	Rte_bBSW_TstKL15;
#define Rte_bGet_BSW_TstKL15()				(Rte_bBSW_TstKL15)
#define Rte_vidSet_BSW_TstKL15(udtValue)		(Rte_bBSW_TstKL15 = udtValue)




/* !Comment: 680ŷCC����ģ������ź� */
extern boolean	Rte_bBSW_CcOut680DO;
#define Rte_bGet_BSW_CcOut680DO()				(Rte_bBSW_CcOut680DO)
#define Rte_vidSet_BSW_CcOut680DO(udtValue)		(Rte_bBSW_CcOut680DO = udtValue)

/* !Comment: 1000ŷCC����ģ������ź� */
extern boolean	Rte_bBSW_CcOut1000DO;
#define Rte_bGet_BSW_CcOut1000DO()				(Rte_bBSW_CcOut1000DO)
#define Rte_vidSet_BSW_CcOut1000DO(udtValue)		(Rte_bBSW_CcOut1000DO = udtValue)

/* !Comment: ����VCU������ź� */
extern boolean	Rte_bBSW_VcuEnaDO;
#define Rte_bGet_BSW_VcuEnaDO()				(Rte_bBSW_VcuEnaDO)
#define Rte_vidSet_BSW_VcuEnaDO(udtValue)		(Rte_bBSW_VcuEnaDO = udtValue)

/* !Comment: OBC����S2��������ź� */
extern boolean	Rte_bBSW_CpS2CtrlDO;
#define Rte_bGet_BSW_CpS2CtrlDO()				(Rte_bBSW_CpS2CtrlDO)
#define Rte_vidSet_BSW_CpS2CtrlDO(udtValue)		(Rte_bBSW_CpS2CtrlDO = udtValue)

/* !Comment: ���ȿ����ź�����ź� */
extern boolean	Rte_bBSW_FanCtrl;
#define Rte_bGet_BSW_FanCtrl()				(Rte_bBSW_FanCtrl)
#define Rte_vidSet_BSW_FanCtrl(udtValue)		(Rte_bBSW_FanCtrl = udtValue)

/* !Comment: ������Դʹ������ź� */
extern boolean	Rte_bBSW_FlyBackEna;
#define Rte_bGet_BSW_FlyBackEna()				(Rte_bBSW_FlyBackEna)
#define Rte_vidSet_BSW_FlyBackEna(udtValue)		(Rte_bBSW_FlyBackEna = udtValue)

/* !Comment: ������Դ�ر�����ź� */
extern boolean	Rte_bBSW_FlyBackOffDO;
#define Rte_bGet_BSW_FlyBackOffDO()				(Rte_bBSW_FlyBackOffDO)
#define Rte_vidSet_BSW_FlyBackOffDO(udtValue)		(Rte_bBSW_FlyBackOffDO = udtValue)

/* !Comment: DCDC28095ʹ������ź� */
extern boolean	Rte_bBSW_PowerEna;
#define Rte_bGet_BSW_PowerEna()				(Rte_bBSW_PowerEna)
#define Rte_vidSet_BSW_PowerEna(udtValue)		(Rte_bBSW_PowerEna = udtValue)

/* !Comment: DCDC28950��������ź� */
extern boolean	Rte_bBSW_DcdcPwrPrtDO;
#define Rte_bGet_BSW_DcdcPwrPrtDO()				(Rte_bBSW_DcdcPwrPrtDO)
#define Rte_vidSet_BSW_DcdcPwrPrtDO(udtValue)		(Rte_bBSW_DcdcPwrPrtDO = udtValue)

/* !Comment: DCDCӲ��������λ����ź� */
extern boolean	Rte_bBSW_DcdcHartPrtRstDO;
#define Rte_bGet_BSW_DcdcHartPrtRstDO()				(Rte_bBSW_DcdcHartPrtRstDO)
#define Rte_vidSet_BSW_DcdcHartPrtRstDO(udtValue)		(Rte_bBSW_DcdcHartPrtRstDO = udtValue)

/* !Comment: ����������Դ������ź� */
extern boolean	Rte_bBSW_McuPwrLockDO;
#define Rte_bGet_BSW_McuPwrLockDO()				(Rte_bBSW_McuPwrLockDO)
#define Rte_vidSet_BSW_McuPwrLockDO(udtValue)		(Rte_bBSW_McuPwrLockDO = udtValue)

/* !Comment: PFC�̵�����������ź� */
extern boolean	Rte_bUART_PfcJdqEnaUO;
#define Rte_bGet_UART_PfcJdqEnaUO()				(Rte_bUART_PfcJdqEnaUO)
#define Rte_vidSet_UART_PfcJdqEnaUO(udtValue)		(Rte_bUART_PfcJdqEnaUO = udtValue)

/* !Comment: LLC�̵�����������ź� */
extern boolean	Rte_bUART_LlcJdqEnaUO;
#define Rte_bGet_UART_LlcJdqEnaUO()				(Rte_bUART_LlcJdqEnaUO)
#define Rte_vidSet_UART_LlcJdqEnaUO(udtValue)		(Rte_bUART_LlcJdqEnaUO = udtValue)

/* !Comment: PFC LED��������ź� */
extern boolean	Rte_bUART_PfcLedCtrlUO;
#define Rte_bGet_UART_PfcLedCtrlUO()				(Rte_bUART_PfcLedCtrlUO)
#define Rte_vidSet_UART_PfcLedCtrlUO(udtValue)		(Rte_bUART_PfcLedCtrlUO = udtValue)

/* !Comment: LLC LED��������ź� */
extern boolean	Rte_bUART_LlcLedCtrlUO;
#define Rte_bGet_UART_LlcLedCtrlUO()				(Rte_bUART_LlcLedCtrlUO)
#define Rte_vidSet_UART_LlcLedCtrlUO(udtValue)		(Rte_bUART_LlcLedCtrlUO = udtValue)

/* !Comment: PFCʹ������ź� */
extern boolean	Rte_bUART_PfcOnUO;
#define Rte_bGet_UART_PfcOnUO()				(Rte_bUART_PfcOnUO)
#define Rte_vidSet_UART_PfcOnUO(udtValue)		(Rte_bUART_PfcOnUO = udtValue)

/* !Comment: LLC��������ź� */
extern boolean	Rte_bUART_LlcPrtUO;
#define Rte_bGet_UART_LlcPrtUO()				(Rte_bUART_LlcPrtUO)
#define Rte_vidSet_UART_LlcPrtUO(udtValue)		(Rte_bUART_LlcPrtUO = udtValue)




/* !Comment: �����ź�: 680ŷCC����ģ����� */
extern boolean	Rte_bBSW_TstCcOut680DO;
#define Rte_bGet_BSW_TstCcOut680DO()				(Rte_bBSW_TstCcOut680DO)
#define Rte_vidSet_BSW_TstCcOut680DO(udtValue)		(Rte_bBSW_TstCcOut680DO = udtValue)

/* !Comment: �����ź�: 1000ŷCC����ģ����� */
extern boolean	Rte_bBSW_TstCcOut1000DO;
#define Rte_bGet_BSW_TstCcOut1000DO()				(Rte_bBSW_TstCcOut1000DO)
#define Rte_vidSet_BSW_TstCcOut1000DO(udtValue)		(Rte_bBSW_TstCcOut1000DO = udtValue)

/* !Comment: �����ź�: ����VCU����� */
extern boolean	Rte_bBSW_TstVcuEnaDO;
#define Rte_bGet_BSW_TstVcuEnaDO()				(Rte_bBSW_TstVcuEnaDO)
#define Rte_vidSet_BSW_TstVcuEnaDO(udtValue)		(Rte_bBSW_TstVcuEnaDO = udtValue)

/* !Comment: �����ź�: OBC����S2������� */
extern boolean	Rte_bBSW_TstCpS2CtrlDO;
#define Rte_bGet_BSW_TstCpS2CtrlDO()				(Rte_bBSW_TstCpS2CtrlDO)
#define Rte_vidSet_BSW_TstCpS2CtrlDO(udtValue)		(Rte_bBSW_TstCpS2CtrlDO = udtValue)

/* !Comment: �����ź�: ���ȿ����ź���� */
extern boolean	Rte_bBSW_TstFanCtrl;
#define Rte_bGet_BSW_TstFanCtrl()				(Rte_bBSW_TstFanCtrl)
#define Rte_vidSet_BSW_TstFanCtrl(udtValue)		(Rte_bBSW_TstFanCtrl = udtValue)

/* !Comment: �����ź�: ������Դʹ����� */
extern boolean	Rte_bBSW_TstFlyBackEna;
#define Rte_bGet_BSW_TstFlyBackEna()				(Rte_bBSW_TstFlyBackEna)
#define Rte_vidSet_BSW_TstFlyBackEna(udtValue)		(Rte_bBSW_TstFlyBackEna = udtValue)

/* !Comment: �����ź�: ������Դ�ر���� */
extern boolean	Rte_bBSW_TstFlyBackOffDO;
#define Rte_bGet_BSW_TstFlyBackOffDO()				(Rte_bBSW_TstFlyBackOffDO)
#define Rte_vidSet_BSW_TstFlyBackOffDO(udtValue)		(Rte_bBSW_TstFlyBackOffDO = udtValue)

/* !Comment: �����ź�: DCDC28095ʹ����� */
extern boolean	Rte_bBSW_TstPowerEna;
#define Rte_bGet_BSW_TstPowerEna()				(Rte_bBSW_TstPowerEna)
#define Rte_vidSet_BSW_TstPowerEna(udtValue)		(Rte_bBSW_TstPowerEna = udtValue)

/* !Comment: �����ź�: DCDC28950������� */
extern boolean	Rte_bBSW_TstDcdcPwrPrtDO;
#define Rte_bGet_BSW_TstDcdcPwrPrtDO()				(Rte_bBSW_TstDcdcPwrPrtDO)
#define Rte_vidSet_BSW_TstDcdcPwrPrtDO(udtValue)		(Rte_bBSW_TstDcdcPwrPrtDO = udtValue)

/* !Comment: �����ź�: DCDCӲ��������λ��� */
extern boolean	Rte_bBSW_TstDcdcHartPrtRstDO;
#define Rte_bGet_BSW_TstDcdcHartPrtRstDO()				(Rte_bBSW_TstDcdcHartPrtRstDO)
#define Rte_vidSet_BSW_TstDcdcHartPrtRstDO(udtValue)		(Rte_bBSW_TstDcdcHartPrtRstDO = udtValue)

/* !Comment: �����ź�: ����������Դ����� */
extern boolean	Rte_bBSW_TstMcuPwrLockDO;
#define Rte_bGet_BSW_TstMcuPwrLockDO()				(Rte_bBSW_TstMcuPwrLockDO)
#define Rte_vidSet_BSW_TstMcuPwrLockDO(udtValue)		(Rte_bBSW_TstMcuPwrLockDO = udtValue)

/* !Comment: �����ź�: PFC�̵���������� */
extern boolean	Rte_bUART_TstPfcJdqEnaUO;
#define Rte_bGet_UART_TstPfcJdqEnaUO()				(Rte_bUART_TstPfcJdqEnaUO)
#define Rte_vidSet_UART_TstPfcJdqEnaUO(udtValue)		(Rte_bUART_TstPfcJdqEnaUO = udtValue)

/* !Comment: �����ź�: LLC�̵���������� */
extern boolean	Rte_bUART_TstLlcJdqEnaUO;
#define Rte_bGet_UART_TstLlcJdqEnaUO()				(Rte_bUART_TstLlcJdqEnaUO)
#define Rte_vidSet_UART_TstLlcJdqEnaUO(udtValue)		(Rte_bUART_TstLlcJdqEnaUO = udtValue)

/* !Comment: �����ź�: PFC LED������� */
extern boolean	Rte_bUART_TstPfcLedCtrlUO;
#define Rte_bGet_UART_TstPfcLedCtrlUO()				(Rte_bUART_TstPfcLedCtrlUO)
#define Rte_vidSet_UART_TstPfcLedCtrlUO(udtValue)		(Rte_bUART_TstPfcLedCtrlUO = udtValue)

/* !Comment: �����ź�: LLC LED������� */
extern boolean	Rte_bUART_TstLlcLedCtrlUO;
#define Rte_bGet_UART_TstLlcLedCtrlUO()				(Rte_bUART_TstLlcLedCtrlUO)
#define Rte_vidSet_UART_TstLlcLedCtrlUO(udtValue)		(Rte_bUART_TstLlcLedCtrlUO = udtValue)

/* !Comment: �����ź�: PFCʹ����� */
extern boolean	Rte_bUART_TstPfcOnUO;
#define Rte_bGet_UART_TstPfcOnUO()				(Rte_bUART_TstPfcOnUO)
#define Rte_vidSet_UART_TstPfcOnUO(udtValue)		(Rte_bUART_TstPfcOnUO = udtValue)

/* !Comment: �����ź�: LLC������� */
extern boolean	Rte_bUART_TstLlcPrtUO;
#define Rte_bGet_UART_TstLlcPrtUO()				(Rte_bUART_TstLlcPrtUO)
#define Rte_vidSet_UART_TstLlcPrtUO(udtValue)		(Rte_bUART_TstLlcPrtUO = udtValue)




/* !Comment: DCDC��ѹ���� */
extern uint16	Rte_u16BSW_PWMVadj;
#define Rte_u16Get_BSW_PWMVadj()				(Rte_u16BSW_PWMVadj)
#define Rte_vidSet_BSW_PWMVadj(udtValue)		(Rte_u16BSW_PWMVadj = udtValue)

/* !Comment: DCDC�������� */
extern uint16	Rte_u16BSW_PWMIadj;
#define Rte_u16Get_BSW_PWMIadj()				(Rte_u16BSW_PWMIadj)
#define Rte_vidSet_BSW_PWMIadj(udtValue)		(Rte_u16BSW_PWMIadj = udtValue)

/* !Comment: LLC��ѹ���� */
extern uint16	Rte_u16UART_LlcPWMVadjUO;
#define Rte_u16Get_UART_LlcPWMVadjUO()				(Rte_u16UART_LlcPWMVadjUO)
#define Rte_vidSet_UART_LlcPWMVadjUO(udtValue)		(Rte_u16UART_LlcPWMVadjUO = udtValue)

/* !Comment: LLC�������� */
extern uint16	Rte_u16UART_LlcPWMIadjUO;
#define Rte_u16Get_UART_LlcPWMIadjUO()				(Rte_u16UART_LlcPWMIadjUO)
#define Rte_vidSet_UART_LlcPWMIadjUO(udtValue)		(Rte_u16UART_LlcPWMIadjUO = udtValue)




/* !Comment: ����: DCDC��ѹ���� */
extern uint16	Rte_u16BSW_TstPWMVadj;
#define Rte_u16Get_BSW_TstPWMVadj()				(Rte_u16BSW_TstPWMVadj)
#define Rte_vidSet_BSW_TstPWMVadj(udtValue)		(Rte_u16BSW_TstPWMVadj = udtValue)

/* !Comment: ����: DCDC�������� */
extern uint16	Rte_u16BSW_TstPWMIadj;
#define Rte_u16Get_BSW_TstPWMIadj()				(Rte_u16BSW_TstPWMIadj)
#define Rte_vidSet_BSW_TstPWMIadj(udtValue)		(Rte_u16BSW_TstPWMIadj = udtValue)

/* !Comment: ����: LLC��ѹ���� */
extern uint16	Rte_u16UART_TstLlcPWMVadjUO;
#define Rte_u16Get_UART_TstLlcPWMVadjUO()				(Rte_u16UART_TstLlcPWMVadjUO)
#define Rte_vidSet_UART_TstLlcPWMVadjUO(udtValue)		(Rte_u16UART_TstLlcPWMVadjUO = udtValue)

/* !Comment: ����: LLC�������� */
extern uint16	Rte_u16UART_TstLlcPWMIadjUO;
#define Rte_u16Get_UART_TstLlcPWMIadjUO()				(Rte_u16UART_TstLlcPWMIadjUO)
#define Rte_vidSet_UART_TstLlcPWMIadjUO(udtValue)		(Rte_u16UART_TstLlcPWMIadjUO = udtValue)




/* !Comment: CC��������ߵ�λ���� */
extern uint16	Rte_u16BSW_CcOhmHiVolAdc;
#define Rte_u16Get_BSW_CcOhmHiVolAdc()				(Rte_u16BSW_CcOhmHiVolAdc)
#define Rte_vidSet_BSW_CcOhmHiVolAdc(udtValue)		(Rte_u16BSW_CcOhmHiVolAdc = udtValue)

/* !Comment: CC��������͵�λ���� */
extern uint16	Rte_u16BSW_CcOhmLoVolAdc;
#define Rte_u16Get_BSW_CcOhmLoVolAdc()				(Rte_u16BSW_CcOhmLoVolAdc)
#define Rte_vidSet_BSW_CcOhmLoVolAdc(udtValue)		(Rte_u16BSW_CcOhmLoVolAdc = udtValue)

/* !Comment: CP��ѹֵ/PWM��ֵ���� */
extern uint16	Rte_u16BSW_CpVolAdc;
#define Rte_u16Get_BSW_CpVolAdc()				(Rte_u16BSW_CpVolAdc)
#define Rte_vidSet_BSW_CpVolAdc(udtValue)		(Rte_u16BSW_CpVolAdc = udtValue)

/* !Comment: DCDC��ѹ���ѹ���� */
extern uint16	Rte_u16BSW_HvVoltAdc;
#define Rte_u16Get_BSW_HvVoltAdc()				(Rte_u16BSW_HvVoltAdc)
#define Rte_vidSet_BSW_HvVoltAdc(udtValue)		(Rte_u16BSW_HvVoltAdc = udtValue)

/* !Comment: DCDC��ѹ��������� */
extern uint16	Rte_u16BSW_HvCurAdc;
#define Rte_u16Get_BSW_HvCurAdc()				(Rte_u16BSW_HvCurAdc)
#define Rte_vidSet_BSW_HvCurAdc(udtValue)		(Rte_u16BSW_HvCurAdc = udtValue)

/* !Comment: DCDC��ѹ���ѹ���� */
extern uint16	Rte_u16BSW_LvVoltAdc;
#define Rte_u16Get_BSW_LvVoltAdc()				(Rte_u16BSW_LvVoltAdc)
#define Rte_vidSet_BSW_LvVoltAdc(udtValue)		(Rte_u16BSW_LvVoltAdc = udtValue)

/* !Comment: DCDC��ѹ��������� */
extern uint16	Rte_u16BSW_LvCurAdc;
#define Rte_u16Get_BSW_LvCurAdc()				(Rte_u16BSW_LvCurAdc)
#define Rte_vidSet_BSW_LvCurAdc(udtValue)		(Rte_u16BSW_LvCurAdc = udtValue)

/* !Comment: С���ص�ѹ���� */
extern uint16	Rte_u16BSW_LvVcc27vAdc;
#define Rte_u16Get_BSW_LvVcc27vAdc()				(Rte_u16BSW_LvVcc27vAdc)
#define Rte_vidSet_BSW_LvVcc27vAdc(udtValue)		(Rte_u16BSW_LvVcc27vAdc = udtValue)

/* !Comment: DCDCԭ���¶Ȳ��� */
extern uint16	Rte_u16BSW_TempSAdc;
#define Rte_u16Get_BSW_TempSAdc()				(Rte_u16BSW_TempSAdc)
#define Rte_vidSet_BSW_TempSAdc(udtValue)		(Rte_u16BSW_TempSAdc = udtValue)

/* !Comment: DCDC�����¶Ȳ��� */
extern uint16	Rte_u16BSW_TempPAdc;
#define Rte_u16Get_BSW_TempPAdc()				(Rte_u16BSW_TempPAdc)
#define Rte_vidSet_BSW_TempPAdc(udtValue)		(Rte_u16BSW_TempPAdc = udtValue)

/* !Comment: MOS��ɢ�Ȱ��¶� */
extern uint16  Rte_u16BSW_TempMosAdc;	
#define Rte_u16Get_BSW_TempMosAdc()				(Rte_u16BSW_TempMosAdc)
#define Rte_vidSet_BSW_TempMosAdc(udtValue)		(Rte_u16BSW_TempMosAdc = udtValue)

/* !Comment: �ⲿ������¶� */
extern uint16  Rte_u16BSW_TempExtAdc;	
#define Rte_u16Get_BSW_TempExtAdc()				(Rte_u16BSW_TempExtAdc)
#define Rte_vidSet_BSW_TempExtAdc(udtValue)		(Rte_u16BSW_TempExtAdc = udtValue)

/* !Comment: CC������,��VIN_TEST */
extern uint16  Rte_u16BSW_CcSense1;	
#define Rte_u16Get_BSW_CcSense1()				(Rte_u16BSW_CcSense1)
#define Rte_vidSet_BSW_CcSense1(udtValue)		(Rte_u16BSW_CcSense1 = udtValue)

/* !Comment: CC������,��CC_SENSE1 */
extern uint16  Rte_u16BSW_VinTest;	
#define Rte_u16Get_BSW_VinTest()				(Rte_u16BSW_VinTest)
#define Rte_vidSet_BSW_VinTest(udtValue)		(Rte_u16BSW_VinTest = udtValue)

/* !Comment: PFC�����ѹ���� */
extern uint16	Rte_u16UART_PfcOutputVolAdc;
#define Rte_u16Get_UART_PfcOutputVolAdc()				(Rte_u16UART_PfcOutputVolAdc)
#define Rte_vidSet_UART_PfcOutputVolAdc(udtValue)		(Rte_u16UART_PfcOutputVolAdc = udtValue)

/* !Comment: LLC�����ѹ���� */
extern uint16	Rte_u16UART_LlcOutputVolAdc;
#define Rte_u16Get_UART_LlcOutputVolAdc()				(Rte_u16UART_LlcOutputVolAdc)
#define Rte_vidSet_UART_LlcOutputVolAdc(udtValue)		(Rte_u16UART_LlcOutputVolAdc = udtValue)

/* !Comment: LLC����������� */
extern uint16	Rte_u16UART_LlcOutputCurAdc;
#define Rte_u16Get_UART_LlcOutputCurAdc()				(Rte_u16UART_LlcOutputCurAdc)
#define Rte_vidSet_UART_LlcOutputCurAdc(udtValue)		(Rte_u16UART_LlcOutputCurAdc = udtValue)

/* !Comment: ������ص�ѹ���� */
extern uint16	Rte_u16UART_HiBatVolAdc;
#define Rte_u16Get_UART_HiBatVolAdc()				(Rte_u16UART_HiBatVolAdc)
#define Rte_vidSet_UART_HiBatVolAdc(udtValue)		(Rte_u16UART_HiBatVolAdc = udtValue)

/* !Comment: PFC�¶Ȳ��� */
extern uint16	Rte_u16UART_PfcTempAdc;
#define Rte_u16Get_UART_PfcTempAdc()				(Rte_u16UART_PfcTempAdc)
#define Rte_vidSet_UART_PfcTempAdc(udtValue)		(Rte_u16UART_PfcTempAdc = udtValue)

/* !Comment: LLC�����¶Ȳ��� */
extern uint16	Rte_u16UART_LlcFbTempAdc;
#define Rte_u16Get_UART_LlcFbTempAdc()				(Rte_u16UART_LlcFbTempAdc)
#define Rte_vidSet_UART_LlcFbTempAdc(udtValue)		(Rte_u16UART_LlcFbTempAdc = udtValue)

/* !Comment: AC220V��ѹ���� */
extern uint16	Rte_u16UART_AC220VolAdc;
#define Rte_u16Get_UART_AC220VolAdc()				(Rte_u16UART_AC220VolAdc)
#define Rte_vidSet_UART_AC220VolAdc(udtValue)		(Rte_u16UART_AC220VolAdc = udtValue)




/* !Comment: ����: CC��������ߵ�λ���� */
extern uint16	Rte_u16BSW_TstCcOhmHiVolAdc;
#define Rte_u16Get_BSW_TstCcOhmHiVolAdc()				(Rte_u16BSW_TstCcOhmHiVolAdc)
#define Rte_vidSet_BSW_TstCcOhmHiVolAdc(udtValue)		(Rte_u16BSW_TstCcOhmHiVolAdc = udtValue)

/* !Comment: ����: CC��������͵�λ���� */
extern uint16	Rte_u16BSW_TstCcOhmLoVolAdc;
#define Rte_u16Get_BSW_TstCcOhmLoVolAdc()				(Rte_u16BSW_TstCcOhmLoVolAdc)
#define Rte_vidSet_BSW_TstCcOhmLoVolAdc(udtValue)		(Rte_u16BSW_TstCcOhmLoVolAdc = udtValue)

/* !Comment: ����: CP��ѹֵ/PWM��ֵ���� */
extern uint16	Rte_u16BSW_TstCpVolAdc;
#define Rte_u16Get_BSW_TstCpVolAdc()				(Rte_u16BSW_TstCpVolAdc)
#define Rte_vidSet_BSW_TstCpVolAdc(udtValue)		(Rte_u16BSW_TstCpVolAdc = udtValue)

/* !Comment: ����: DCDC��ѹ���ѹ���� */
extern uint16	Rte_u16BSW_TstAdcHVolt;
#define Rte_u16Get_BSW_TstAdcHVolt()				(Rte_u16BSW_TstAdcHVolt)
#define Rte_vidSet_BSW_TstAdcHVolt(udtValue)		(Rte_u16BSW_TstAdcHVolt = udtValue)

/* !Comment: ����: DCDC��ѹ��������� */
extern uint16	Rte_u16BSW_TstAdcHCurrent;
#define Rte_u16Get_BSW_TstAdcHCurrent()				(Rte_u16BSW_TstAdcHCurrent)
#define Rte_vidSet_BSW_TstAdcHCurrent(udtValue)		(Rte_u16BSW_TstAdcHCurrent = udtValue)

/* !Comment: ����: DCDC��ѹ���ѹ���� */
extern uint16	Rte_u16BSW_TstAdcLVolt;
#define Rte_u16Get_BSW_TstAdcLVolt()				(Rte_u16BSW_TstAdcLVolt)
#define Rte_vidSet_BSW_TstAdcLVolt(udtValue)		(Rte_u16BSW_TstAdcLVolt = udtValue)

/* !Comment: ����: DCDC��ѹ��������� */
extern uint16	Rte_u16BSW_TstAdcLCurrent;
#define Rte_u16Get_BSW_TstAdcLCurrent()				(Rte_u16BSW_TstAdcLCurrent)
#define Rte_vidSet_BSW_TstAdcLCurrent(udtValue)		(Rte_u16BSW_TstAdcLCurrent = udtValue)

/* !Comment: ����: С���ص�ѹ���� */
extern uint16	Rte_u16BSW_TstAdcLVcc27v;
#define Rte_u16Get_BSW_TstAdcLVcc27v()				(Rte_u16BSW_TstAdcLVcc27v)
#define Rte_vidSet_BSW_TstAdcLVcc27v(udtValue)		(Rte_u16BSW_TstAdcLVcc27v = udtValue)

/* !Comment: ����: DCDCԭ���¶Ȳ��� */
extern uint16	Rte_u16BSW_TstAdcTempS;
#define Rte_u16Get_BSW_TstAdcTempS()				(Rte_u16BSW_TstAdcTempS)
#define Rte_vidSet_BSW_TstAdcTempS(udtValue)		(Rte_u16BSW_TstAdcTempS = udtValue)

/* !Comment: ����: DCDC�����¶Ȳ��� */
extern uint16	Rte_u16BSW_TstAdcTempP;
#define Rte_u16Get_BSW_TstAdcTempP()				(Rte_u16BSW_TstAdcTempP)
#define Rte_vidSet_BSW_TstAdcTempP(udtValue)		(Rte_u16BSW_TstAdcTempP = udtValue)

/* !Comment: ����: PFC�����ѹ���� */
extern uint16	Rte_u16UART_TstPfcOutputVolAdc;
#define Rte_u16Get_UART_TstPfcOutputVolAdc()				(Rte_u16UART_TstPfcOutputVolAdc)
#define Rte_vidSet_UART_TstPfcOutputVolAdc(udtValue)		(Rte_u16UART_TstPfcOutputVolAdc = udtValue)

/* !Comment: ����: LLC�����ѹ���� */
extern uint16	Rte_u16UART_TstLlcOutputVolAdc;
#define Rte_u16Get_UART_TstLlcOutputVolAdc()				(Rte_u16UART_TstLlcOutputVolAdc)
#define Rte_vidSet_UART_TstLlcOutputVolAdc(udtValue)		(Rte_u16UART_TstLlcOutputVolAdc = udtValue)

/* !Comment: ����: LLC����������� */
extern uint16	Rte_u16UART_TstLlcOutputCurAdc;
#define Rte_u16Get_UART_TstLlcOutputCurAdc()				(Rte_u16UART_TstLlcOutputCurAdc)
#define Rte_vidSet_UART_TstLlcOutputCurAdc(udtValue)		(Rte_u16UART_TstLlcOutputCurAdc = udtValue)

/* !Comment: ����: ������ص�ѹ���� */
extern uint16	Rte_u16UART_TstHiBatVolAdc;
#define Rte_u16Get_UART_TstHiBatVolAdc()				(Rte_u16UART_TstHiBatVolAdc)
#define Rte_vidSet_UART_TstHiBatVolAdc(udtValue)		(Rte_u16UART_TstHiBatVolAdc = udtValue)

/* !Comment: ����: PFC�¶Ȳ��� */
extern uint16	Rte_u16UART_TstPfcTempAdc;
#define Rte_u16Get_UART_TstPfcTempAdc()				(Rte_u16UART_TstPfcTempAdc)
#define Rte_vidSet_UART_TstPfcTempAdc(udtValue)		(Rte_u16UART_TstPfcTempAdc = udtValue)

/* !Comment: ����: LLC�����¶Ȳ��� */
extern uint16	Rte_u16UART_TstLlcFbTempAdc;
#define Rte_u16Get_UART_TstLlcFbTempAdc()				(Rte_u16UART_TstLlcFbTempAdc)
#define Rte_vidSet_UART_TstLlcFbTempAdc(udtValue)		(Rte_u16UART_TstLlcFbTempAdc = udtValue)

/* !Comment: ����: AC220V��ѹ���� */
extern uint16	Rte_u16UART_TstAC220VolAdc;
#define Rte_u16Get_UART_TstAC220VolAdc()				(Rte_u16UART_TstAC220VolAdc)
#define Rte_vidSet_UART_TstAC220VolAdc(udtValue)		(Rte_u16UART_TstAC220VolAdc = udtValue)




/* !Comment: CC��������ߵ�λ */
extern uint16	Rte_u16ASM_CcOhmHiVolAdc;
#define Rte_u16Get_ASM_CcOhmHiVolAdc()				(Rte_u16ASM_CcOhmHiVolAdc)
#define Rte_vidSet_ASM_CcOhmHiVolAdc(udtValue)		(Rte_u16ASM_CcOhmHiVolAdc = udtValue)

/* !Comment: CC��������͵�λ */
extern uint16	Rte_u16ASM_CcOhmLoVolAdc;
#define Rte_u16Get_ASM_CcOhmLoVolAdc()				(Rte_u16ASM_CcOhmLoVolAdc)
#define Rte_vidSet_ASM_CcOhmLoVolAdc(udtValue)		(Rte_u16ASM_CcOhmLoVolAdc = udtValue)

/* !Comment: CP��ѹֵ/PWM��ֵ */
extern uint16	Rte_u16ASM_CpVolAdc;
#define Rte_u16Get_ASM_CpVolAdc()				(Rte_u16ASM_CpVolAdc)
#define Rte_vidSet_ASM_CpVolAdc(udtValue)		(Rte_u16ASM_CpVolAdc = udtValue)

/* !Comment: DCDC��ѹ���ѹֵ */
extern uint16	Rte_u16ASM_HvVolt;
#define Rte_u16Get_ASM_HvVolt()				(Rte_u16ASM_HvVolt)
#define Rte_vidSet_ASM_HvVolt(udtValue)		(Rte_u16ASM_HvVolt = udtValue)

/* !Comment: DCDC��ѹ�����ֵ */
extern uint16	Rte_u16ASM_HvCur;
#define Rte_u16Get_ASM_HvCur()				(Rte_u16ASM_HvCur)
#define Rte_vidSet_ASM_HvCur(udtValue)		(Rte_u16ASM_HvCur = udtValue)

/* !Comment: DCDC��ѹ���ѹֵ */
extern uint16	Rte_u16ASM_LvVolt;
#define Rte_u16Get_ASM_LvVolt()				(Rte_u16ASM_LvVolt)
#define Rte_vidSet_ASM_LvVolt(udtValue)		(Rte_u16ASM_LvVolt = udtValue)

/* !Comment: DCDC��ѹ�����ֵ */
extern uint16	Rte_u16ASM_LvCur;
#define Rte_u16Get_ASM_LvCur()				(Rte_u16ASM_LvCur)
#define Rte_vidSet_ASM_LvCur(udtValue)		(Rte_u16ASM_LvCur = udtValue)

/* !Comment: С���ص�ѹֵ */
extern uint16	Rte_u16ASM_LvVcc27v;
#define Rte_u16Get_ASM_LvVcc27v()				(Rte_u16ASM_LvVcc27v)
#define Rte_vidSet_ASM_LvVcc27v(udtValue)		(Rte_u16ASM_LvVcc27v = udtValue)

/* !Comment: DCDCԭ���¶�ֵ */
extern sint16	Rte_s16ASM_TempS;
#define Rte_s16Get_ASM_TempS()				(Rte_s16ASM_TempS)
#define Rte_vidSet_ASM_TempS(udtValue)		(Rte_s16ASM_TempS = udtValue)

/* !Comment: DCDC�����¶�ֵ */
extern sint16	Rte_s16ASM_TempP;
#define Rte_s16Get_ASM_TempP()				(Rte_s16ASM_TempP)
#define Rte_vidSet_ASM_TempP(udtValue)		(Rte_s16ASM_TempP = udtValue)

/* !Comment: MOS��ɢ�Ȱ��¶� */
extern sint16  Rte_u16ASM_TempMosAdc;	
#define Rte_u16Get_ASM_TempMosAdc()				(Rte_u16ASM_TempMosAdc)
#define Rte_vidSet_ASM_TempMosAdc(udtValue)		(Rte_u16ASM_TempMosAdc = udtValue)

/* !Comment: �ⲿ������¶� */
extern sint16  Rte_u16ASM_TempExtAdc;	
#define Rte_u16Get_ASM_TempExtAdc()				(Rte_u16ASM_TempExtAdc)
#define Rte_vidSet_ASM_TempExtAdc(udtValue)		(Rte_u16ASM_TempExtAdc = udtValue)

/* !Comment: CC������,��VIN_TEST */
extern uint16  Rte_u16ASM_CcSense1;	
#define Rte_u16Get_ASM_CcSense1()				(Rte_u16ASM_CcSense1)
#define Rte_vidSet_ASM_CcSense1(udtValue)		(Rte_u16ASM_CcSense1 = udtValue)

/* !Comment: CC������,��CC_SENSE1 */
extern uint16  Rte_u16ASM_VinTest;	
#define Rte_u16Get_ASM_VinTest()				(Rte_u16ASM_VinTest)
#define Rte_vidSet_ASM_VinTest(udtValue)		(Rte_u16ASM_VinTest = udtValue)

/* !Comment: PFC�����ѹ */
extern uint16	Rte_u16ASM_PfcOutputVolAdc;
#define Rte_u16Get_ASM_PfcOutputVolAdc()				(Rte_u16ASM_PfcOutputVolAdc)
#define Rte_vidSet_ASM_PfcOutputVolAdc(udtValue)		(Rte_u16ASM_PfcOutputVolAdc = udtValue)

/* !Comment: LLC�����ѹ */
extern uint16	Rte_u16ASM_LlcOutputVolAdc;
#define Rte_u16Get_ASM_LlcOutputVolAdc()				(Rte_u16ASM_LlcOutputVolAdc)
#define Rte_vidSet_ASM_LlcOutputVolAdc(udtValue)		(Rte_u16ASM_LlcOutputVolAdc = udtValue)

/* !Comment: LLC������� */
extern uint16	Rte_u16ASM_LlcOutputCurAdc;
#define Rte_u16Get_ASM_LlcOutputCurAdc()				(Rte_u16ASM_LlcOutputCurAdc)
#define Rte_vidSet_ASM_LlcOutputCurAdc(udtValue)		(Rte_u16ASM_LlcOutputCurAdc = udtValue)

/* !Comment: ������ص�ѹ */
extern uint16	Rte_u16ASM_HiBatVolAdc;
#define Rte_u16Get_ASM_HiBatVolAdc()				(Rte_u16ASM_HiBatVolAdc)
#define Rte_vidSet_ASM_HiBatVolAdc(udtValue)		(Rte_u16ASM_HiBatVolAdc = udtValue)

/* !Comment: PFC�¶� */
extern sint16	Rte_s16ASM_PfcTempAdc;
#define Rte_s16Get_ASM_PfcTempAdc()				(Rte_s16ASM_PfcTempAdc)
#define Rte_vidSet_ASM_PfcTempAdc(udtValue)		(Rte_s16ASM_PfcTempAdc = udtValue)

/* !Comment: LLC�����¶� */
extern sint16	Rte_s16ASM_LlcFbTempAdc;
#define Rte_s16Get_ASM_LlcFbTempAdc()				(Rte_s16ASM_LlcFbTempAdc)
#define Rte_vidSet_ASM_LlcFbTempAdc(udtValue)		(Rte_s16ASM_LlcFbTempAdc = udtValue)

/* !Comment: AC220V��ѹ���� */
extern uint16	Rte_u16ASM_AC220VolAdc;
#define Rte_u16Get_ASM_AC220VolAdc()				(Rte_u16ASM_AC220VolAdc)
#define Rte_vidSet_ASM_AC220VolAdc(udtValue)		(Rte_u16ASM_AC220VolAdc = udtValue)




/* !Comment: OBC�������б�� */
extern boolean	Rte_bDSM_OBC_Derating;
#define Rte_bGet_DSM_OBC_Derating()				(Rte_bDSM_OBC_Derating)
#define Rte_vidSet_DSM_OBC_Derating(udtValue)		(Rte_bDSM_OBC_Derating = udtValue)

/* !Comment: OBCӲ�������� */
extern boolean	Rte_bDSM_OBC_HwError;
#define Rte_bGet_DSM_OBC_HwError()				(Rte_bDSM_OBC_HwError)
#define Rte_vidSet_DSM_OBC_HwError(udtValue)		(Rte_bDSM_OBC_HwError = udtValue)

/* !Comment: OBC��������� */
extern boolean	Rte_bDSM_OBC_SwError;
#define Rte_bGet_DSM_OBC_SwError()				(Rte_bDSM_OBC_SwError)
#define Rte_vidSet_DSM_OBC_SwError(udtValue)		(Rte_bDSM_OBC_SwError = udtValue)

/* !Comment: OBC���������ѹ��ѹ��� */
extern boolean	Rte_bDSM_OBC_InOVP;
#define Rte_bGet_DSM_OBC_InOVP()				(Rte_bDSM_OBC_InOVP)
#define Rte_vidSet_DSM_OBC_InOVP(udtValue)		(Rte_bDSM_OBC_InOVP = udtValue)

/* !Comment: OBC���������ѹǷѹ��� */
extern boolean	Rte_bDSM_OBC_InUVP;
#define Rte_bGet_DSM_OBC_InUVP()				(Rte_bDSM_OBC_InUVP)
#define Rte_vidSet_DSM_OBC_InUVP(udtValue)		(Rte_bDSM_OBC_InUVP = udtValue)

/* !Comment: PFC�����ѹ��ѹ��� */
extern boolean	Rte_bDSM_PFC_OutOVP;
#define Rte_bGet_DSM_PFC_OutOVP()				(Rte_bDSM_PFC_OutOVP)
#define Rte_vidSet_DSM_PFC_OutOVP(udtValue)		(Rte_bDSM_PFC_OutOVP = udtValue)

/* !Comment: PFC�����ѹǷѹ��� */
extern boolean	Rte_bDSM_PFC_OutUVP;	
#define Rte_bGet_DSM_PFC_OutUVP()				(Rte_bDSM_PFC_OutUVP)
#define Rte_vidSet_DSM_PFC_OutUVP(udtValue)		(Rte_bDSM_PFC_OutUVP = udtValue)

/* !Comment: OBC�����ѹ��ѹ��� */
extern boolean	Rte_bDSM_OBC_OutOVP;
#define Rte_bGet_DSM_OBC_OutOVP()				(Rte_bDSM_OBC_OutOVP)
#define Rte_vidSet_DSM_OBC_OutOVP(udtValue)		(Rte_bDSM_OBC_OutOVP = udtValue)

/* !Comment: OBC�����ѹǷѹ��� */
extern boolean	Rte_bDSM_OBC_OutUVP;
#define Rte_bGet_DSM_OBC_OutUVP()				(Rte_bDSM_OBC_OutUVP)
#define Rte_vidSet_DSM_OBC_OutUVP(udtValue)		(Rte_bDSM_OBC_OutUVP = udtValue)

/* !Comment: OBC������� */
extern boolean	Rte_bDSM_ObcOCP;
#define Rte_bGet_DSM_ObcOCP()				(Rte_bDSM_ObcOCP)
#define Rte_vidSet_DSM_ObcOCP(udtValue)		(Rte_bDSM_ObcOCP = udtValue)

/* !Comment: OBC�����·��� */
extern boolean	Rte_bDSM_OBC_OutOSP;
#define Rte_bGet_DSM_OBC_OutOSP()				(Rte_bDSM_OBC_OutOSP)
#define Rte_vidSet_DSM_OBC_OutOSP(udtValue)		(Rte_bDSM_OBC_OutOSP = udtValue)




/* !Comment: ���ص�ع�ѹ��� */
extern boolean	Rte_bDSM_CarBatOVP;
#define Rte_bGet_DSM_CarBatOVP()				(Rte_bDSM_CarBatOVP)
#define Rte_vidSet_DSM_CarBatOVP(udtValue)		(Rte_bDSM_CarBatOVP = udtValue)

/* !Comment: ���ص��Ƿѹ��� */
extern boolean	Rte_bDSM_CarBatUVP;
#define Rte_bGet_DSM_CarBatUVP()				(Rte_bDSM_CarBatUVP)
#define Rte_vidSet_DSM_CarBatUVP(udtValue)		(Rte_bDSM_CarBatUVP = udtValue)

/* !Comment: ��ѹ��ع�ѹ��� */
extern boolean	Rte_bDSM_HiBatOVP;
#define Rte_bGet_DSM_HiBatOVP()				(Rte_bDSM_HiBatOVP)
#define Rte_vidSet_DSM_HiBatOVP(udtValue)		(Rte_bDSM_HiBatOVP = udtValue)

/* !Comment: ��ѹ���Ƿѹ��� */
extern boolean	Rte_bDSM_HiBatUVP;
#define Rte_bGet_DSM_HiBatUVP()				(Rte_bDSM_HiBatUVP)
#define Rte_vidSet_DSM_HiBatUVP(udtValue)		(Rte_bDSM_HiBatUVP = udtValue)

extern boolean	Rte_bOSM_CC_Fault;
#define Rte_bGet_OSM_CC_Fault()				(Rte_bOSM_CC_Fault)
#define Rte_vidSet_OSM_CC_Fault(udtValue)		(Rte_bOSM_CC_Fault = udtValue)

extern boolean	Rte_bOSM_CP_Fault;
#define Rte_bGet_OSM_CP_Fault()				(Rte_bOSM_CP_Fault)
#define Rte_vidSet_OSM_CP_Fault(udtValue)		(Rte_bOSM_CP_Fault = udtValue)


/* !Comment: DCDC�������б�� */
extern boolean	Rte_bDSM_Derating;
#define Rte_bGet_DSM_Derating()				(Rte_bDSM_Derating)
#define Rte_vidSet_DSM_Derating(udtValue)		(Rte_bDSM_Derating = udtValue)

/* !Comment: DCDC��������� */
extern boolean	Rte_bDSM_SwError;
#define Rte_bGet_DSM_SwError()				(Rte_bDSM_SwError)
#define Rte_vidSet_DSM_SwError(udtValue)		(Rte_bDSM_SwError = udtValue)

/* !Comment: DCDCӲ�������� */
extern boolean	Rte_bDSM_HwError;
#define Rte_bGet_DSM_HwError()				(Rte_bDSM_HwError)
#define Rte_vidSet_DSM_HwError(udtValue)		(Rte_bDSM_HwError = udtValue)

/* !Comment: DCDC�����ѹ��� */
extern boolean	Rte_bDSM_OutOVP;
#define Rte_bGet_DSM_OutOVP()				(Rte_bDSM_OutOVP)
#define Rte_vidSet_DSM_OutOVP(udtValue)		(Rte_bDSM_OutOVP = udtValue)

/* !Comment: DCDC���Ƿѹһ����� */
extern boolean	Rte_bDSM_OutUV2B1;
#define Rte_bGet_DSM_OutUV2B1()				(Rte_bDSM_OutUV2B1)
#define Rte_vidSet_DSM_OutUV2B1(udtValue)		(Rte_bDSM_OutUV2B1 = udtValue)

/* !Comment: DCDC���Ƿѹ������� */
extern boolean	Rte_bDSM_OutUV1BMin;
#define Rte_bGet_DSM_OutUV1BMin()				(Rte_bDSM_OutUV1BMin)
#define Rte_vidSet_DSM_OutUV1BMin(udtValue)		(Rte_bDSM_OutUV1BMin = udtValue)

/* !Comment: DCDC���Ƿѹ��� */
extern boolean	Rte_bDSM_OutUVP;
#define Rte_bGet_DSM_OutUVP()				(Rte_bDSM_OutUVP)
#define Rte_vidSet_DSM_OutUVP(udtValue)		(Rte_bDSM_OutUVP = udtValue)

/* !Comment: DCDC�����ѹ��� */
extern boolean	Rte_bDSM_InOVP;
#define Rte_bGet_DSM_InOVP()				(Rte_bDSM_InOVP)
#define Rte_vidSet_DSM_InOVP(udtValue)		(Rte_bDSM_InOVP = udtValue)

/* !Comment: DCDC����Ƿѹ��� */
extern boolean	Rte_bDSM_InUVP;
#define Rte_bGet_DSM_InUVP()				(Rte_bDSM_InUVP)
#define Rte_vidSet_DSM_InUVP(udtValue)		(Rte_bDSM_InUVP = udtValue)

/* !Comment: DCDC�¶ȹ��߱�� */
extern boolean	Rte_bDSM_TempHigh;
#define Rte_bGet_DSM_TempHigh()				(Rte_bDSM_TempHigh)
#define Rte_vidSet_DSM_TempHigh(udtValue)		(Rte_bDSM_TempHigh = udtValue)

/* !Comment: DCDC�¶ȳ���������Χ��� */
extern boolean	Rte_bDSM_TempOTP;
#define Rte_bGet_DSM_TempOTP()				(Rte_bDSM_TempOTP)
#define Rte_vidSet_DSM_TempOTP(udtValue)		(Rte_bDSM_TempOTP = udtValue)

/* !Comment: DCDC������� */
extern boolean	Rte_bDSM_DcdcOCP;
#define Rte_bGet_DSM_DcdcOCP()				(Rte_bDSM_DcdcOCP)
#define Rte_vidSet_DSM_DcdcOCP(udtValue)		(Rte_bDSM_DcdcOCP = udtValue)

/* !Comment: DCDC��ǰ�¶ȴ�������⵽�ĵ��� */
extern sint8	Rte_s8DSM_TempMin;
#define Rte_s8Get_DSM_TempMin()				(Rte_s8DSM_TempMin)
#define Rte_vidSet_DSM_TempMin(udtValue)		(Rte_s8DSM_TempMin = udtValue)

/* !Comment: DCDC��ǰ�¶ȴ�������⵽�ĸ��� */
extern sint8	Rte_s8DSM_TempMax;
#define Rte_s8Get_DSM_TempMax()				(Rte_s8DSM_TempMax)
#define Rte_vidSet_DSM_TempMax(udtValue)		(Rte_s8DSM_TempMax = udtValue)

/* !Comment: DCDC��⵽����������� */
extern uint8	Rte_u8DSM_SWFailSt;
#define Rte_u8Get_DSM_SWFailSt()				(Rte_u8DSM_SWFailSt)
#define Rte_vidSet_DSM_SWFailSt(udtValue)		(Rte_u8DSM_SWFailSt = udtValue)


/* !Comment: OBC���������� */
extern uint32	Rte_u32TCM_ObcPowerLimt;
#define Rte_u32Get_TCM_ObcPowerLimt()				(Rte_u32TCM_ObcPowerLimt)
#define Rte_vidSet_TCM_ObcPowerLimt(udtValue)		(Rte_u32TCM_ObcPowerLimt = udtValue)

/* !Comment: OBC����ģʽ */
extern uint8	Rte_u8OSM_WorkingSt;
#define Rte_u8Get_OSM_WorkingSt()				(Rte_u8OSM_WorkingSt)
#define Rte_vidSet_OSM_WorkingSt(udtValue)		(Rte_u8OSM_WorkingSt = udtValue)

/* !Comment: CC����״̬ */
extern uint8	Rte_u8OSM_CC_ConnectSt;
#define Rte_u8Get_OSM_CC_ConnectSt()				(Rte_u8OSM_CC_ConnectSt)
#define Rte_vidSet_OSM_CC_ConnectSt(udtValue)		(Rte_u8OSM_CC_ConnectSt = udtValue)

/* !Comment: CP����״̬ */
extern uint8	Rte_u8OSM_CP_ConnectSt;
#define Rte_u8Get_OSM_CP_ConnectSt()				(Rte_u8OSM_CP_ConnectSt)
#define Rte_vidSet_OSM_CP_ConnectSt(udtValue)		(Rte_u8OSM_CP_ConnectSt = udtValue)

/* !Comment: DCDC����ģʽ */
extern uint8	Rte_u8FSM_WorkingSt;
#define Rte_u8Get_FSM_WorkingSt()				(Rte_u8FSM_WorkingSt)
#define Rte_vidSet_FSM_WorkingSt(udtValue)		(Rte_u8FSM_WorkingSt = udtValue)

/* !Comment: DCDC����״̬�� */
extern uint8	Rte_u8FSM_DCDCSt;
#define Rte_u8Get_FSM_DCDCSt()				(Rte_u8FSM_DCDCSt)
#define Rte_vidSet_FSM_DCDCSt(udtValue)		(Rte_u8FSM_DCDCSt = udtValue)

extern uint8	Rte_u8FSM_DCDCWorkSt;
#define Rte_u8Get_FSM_DCDCWorkSt()				(Rte_u8FSM_DCDCWorkSt)
#define Rte_vidSet_FSM_DCDCWorkSt(udtValue)		(Rte_u8FSM_DCDCWorkSt = udtValue)

/* !Comment: DCDC���������� */
extern uint32	Rte_u32TCM_PowerLimt;
#define Rte_u32Get_TCM_PowerLimt()				(Rte_u32TCM_PowerLimt)
#define Rte_vidSet_TCM_PowerLimt(udtValue)		(Rte_u32TCM_PowerLimt = udtValue)

/* !Comment: DCDC���������ѹ */
extern uint16	Rte_u16TCM_VoltLim;
#define Rte_u16Get_TCM_VoltLim()				(Rte_u16TCM_VoltLim)
#define Rte_vidSet_TCM_VoltLim(udtValue)		(Rte_u16TCM_VoltLim = udtValue)

/* !Comment: DCDC����������� */
extern uint16	Rte_u16TCM_CurLim;
#define Rte_u16Get_TCM_CurLim()				(Rte_u16TCM_CurLim)
#define Rte_vidSet_TCM_CurLim(udtValue)		(Rte_u16TCM_CurLim = udtValue)

/* !Comment: DCDC�����¶� */
extern sint8	Rte_s8TCM_DcdcTemp;
#define Rte_s8Get_TCM_DcdcTemp()				(Rte_s8TCM_DcdcTemp)
#define Rte_vidSet_TCM_DcdcTemp(udtValue)		(Rte_s8TCM_DcdcTemp = udtValue)

/* !Comment: DCDC���ڴ�������������� */
extern uint8	Rte_u8FSM_SWCurrentFaultSt;
#define Rte_u8Get_FSM_SWCurrentFaultSt()				(Rte_u8FSM_SWCurrentFaultSt)
#define Rte_vidSet_FSM_SWCurrentFaultSt(udtValue)		(Rte_u8FSM_SWCurrentFaultSt = udtValue)

/* !Comment: DCDC��ǰ�������Ĵ���״̬�� */
extern uint8	Rte_u8FSM_SWFaultProcessCtrlSt;
#define Rte_u8Get_FSM_SWFaultProcessCtrlSt()				(Rte_u8FSM_SWFaultProcessCtrlSt)
#define Rte_vidSet_FSM_SWFaultProcessCtrlSt(udtValue)		(Rte_u8FSM_SWFaultProcessCtrlSt = udtValue)




extern uint16 u16Debug0;
extern uint16 u16Debug1;
extern uint16 u16Debug2;
extern uint16 u16Debug3;
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */



#endif
/* ************** End of The File *************************************** */

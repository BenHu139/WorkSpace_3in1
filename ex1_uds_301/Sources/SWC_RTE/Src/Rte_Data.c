

/* !Comment: Included File             */
#include "includes.h"
#include "Rte_Data.h"


/* ************************************************************************** */
/*                                 MACROS                                     */
/* ************************************************************************** */


/* ************************************************************************** */
/*                                 TYPES                                      */
/* ************************************************************************** */


/* ************************************************************************** */
/*                              GLOABAL VARIRABLE                             */
/* ************************************************************************** */
uint8	Rte_u8CAN_ComState		= 0;			/* !Comment: CANͨ��״̬ */
uint8	Rte_u8CAN_BusoffSt		= 0;			/* !Comment: CAN busoff״̬λ */
uint8	Rte_u8CAN_MsgRxSt		= 0;			/* !Comment: CAN ���ձ���״̬λ */
uint8	Rte_u8UART_ComState		= 1;			/* !Comment: UARTͨ��״̬ */
uint16	Rte_u16CAN_UBuckReq		= 0;			/* !Comment: CAN���������ѹ */
boolean	Rte_bCAN_ModeReq		= 0;			/* !Comment: CANԤ��ָ�� */


uint16	Rte_u16BMS_MaxChgVol		= 0;			/* !Comment: BMS����������ѹ */
uint16	Rte_u16BMS_MaxChgCur		= 0;			/* !Comment: BMS������������ */
uint8	Rte_u8BMS_SelfChkSt		    = 0xFF;			/* !Comment: BMS�Լ�״̬ */
uint8	Rte_u8BMS_ObcCtrlCmd		= 0xFF;			/* !Comment: BMS����OBC����ָ�� */
uint8	Rte_u8BMS_ObcWorkMode		= 0xFF;			/* !Comment: BMS����OBC����ģʽ */
//_hb wuling
uint8	Rte_u8Bat_MaPosRlySts		= 3;			/* !Comment: ��ذ������̵���״̬ */
uint8	Rte_u8Bat_MaNegRlySts		= 3;			/* !Comment: ��ذ������̵���״̬ */
uint8	Rte_u8Bat_ChrgSts		    = 7;			/* !Comment: ��ذ����״̬�ź� */
uint8	Rte_u8Bat_HeRlySts			= 3;			/* !Comment: ��ذ����ȼ̵���״̬ */
uint8	Rte_u8Bat_HeSts				= 3;			/* !Comment: ��ذ�����״̬*/
uint8	Rte_u8Vec_OptMod			= 6;			/* !Comment: ��������ģʽ */
uint8	Rte_u8Vec_ChrgRqst			= 3;			/* !Comment: �����������*/
boolean	Rte_bDCDC_Enable			= 0;			/* !Comment: DCDCʹ���ź� */
uint8	Rte_u8IPS_State			    = 0x0F;			/* !Comment: IPS��ǰ״̬*/
boolean	Rte_bOBC_WakeUpEn			= 0;			/* !Comment: OBC����,����ָʾ */

boolean Rte_bBSW_PCC                = 0;			/* !Comment: Ԥ������ź�, ���� */
boolean Rte_bBSW_OutSwEn            = 0;			/* !Comment: ��ѹ����������ź�, ���� */
boolean	Rte_bBSW_EmuTestEnable		= 0;			/* !Comment: ģ����Ա��λ */
boolean	Rte_bBSW_IOTestEnable		= 0;			/* !Comment: IO���Ա��λ */
boolean	Rte_bBSW_CcEmuTstEna		= 0;			/* !Comment: ���׮ģ�����ʹ��λ */
boolean	Rte_bBSW_PfcEmuTstEna		= 0;			/* !Comment: PFCģ�����ʹ��λ */
boolean	Rte_bBSW_LlcEmuTstEna		= 0;			/* !Comment: LLCģ�����ʹ��λ */
boolean	Rte_bBSW_DcdcEmuTstEna		= 0;			/* !Comment: DCDCģ�����ʹ��λ */


uint8	Rte_u8BSW_CpVolAMP		= 0;			/* !Comment: CP��ѹֵ/PWM��ֵ */
uint16	Rte_u16BSW_CpFliterVoltADC		= 0;			/* !Comment: CP��ѹ�����˲����ֵ */
uint16	Rte_u16BSW_CpDutyCal		= 0;			/* !Comment: CP�źŵ�ռ�ձ� */
uint16	Rte_u16BSW_TstCpDutyCal		= 0;			/* !Comment: �����ź�: CP�źŵ�ռ�ձ� */
uint16	Rte_u16BSW_CcRcOhmVal		= 0;			/* !Comment: RC/RC+R4��ֵ */

boolean Rte_bBSW_CanFaultDI     = 1;            /* !Comment: TCAN 1043 ��������ź� , ����Ч, ���� */
boolean Rte_bBSW_LockStatusDI   = 1;			/* !Comment: ����������״̬, ����Ч, ����*/
boolean	Rte_bBSW_CcPluginDI		= 0;			/* !Comment: CC��ǹ��绽��MCU�����ź� */
boolean	Rte_bBSW_ObcEnaDI		= 0;			/* !Comment: OBCʹ�������ź� */
boolean	Rte_bBSW_DcdcEnaDI		= 0;			/* !Comment: DCDCʹ�������ź� */
boolean	Rte_bUART_PfcStopUI		= 1;			/* !Comment: PFC����ر������ź� */
boolean	Rte_bUART_LlcHardPrtUI		= 0;			/* !Comment: LLCӲ�����������ź� */
boolean	Rte_bBSW_LvShortM		= 0;			/* !Comment: ��ѹ���·�����ź� */
boolean	Rte_bBSW_VoutInterLockDiag		= 0;			/* !Comment: ��ѹ���������ź� */
boolean	Rte_bBSW_KL15		= 0;			/* !Comment: KL15 */


boolean	Rte_bBSW_TstObcEnaDI		= 0;			/* !Comment: �����ź�: OBCʹ������ */
boolean	Rte_bBSW_TstDcdcEnaDI		= 0;			/* !Comment: �����ź�: DCDCʹ������ */
boolean	Rte_bUART_TstPfcStopUI		= 0;			/* !Comment: �����ź�: PFC����ر����� */
boolean	Rte_bUART_TstLlcHardPrtUI		= 0;			/* !Comment: �����ź�: LLCӲ���������� */
boolean	Rte_bBSW_TstLvShortM		= 0;			/* !Comment: �����ź�: ��ѹ���·���� */
boolean	Rte_bBSW_TstVoutInterLockDiag		= 0;			/* !Comment: �����ź�: ��ѹ�������� */
boolean	Rte_bBSW_TstKL15		= 0;			/* !Comment: �����ź�: KL15 */


boolean	Rte_bBSW_CcOut680DO		= 0;			/* !Comment: 680ŷCC����ģ������ź� */
boolean	Rte_bBSW_CcOut1000DO		= 0;			/* !Comment: 1000ŷCC����ģ������ź� */
boolean	Rte_bBSW_VcuEnaDO		= 0;			/* !Comment: ����VCU������ź� */
boolean	Rte_bBSW_CpS2CtrlDO		= 0;			/* !Comment: OBC����S2��������ź� */
boolean	Rte_bBSW_FanCtrl		= 0;			/* !Comment: ���ȿ����ź�����ź� */
boolean	Rte_bBSW_FlyBackEna		= 1;			/* !Comment: ������Դʹ������ź� */
boolean	Rte_bBSW_FlyBackOffDO		= 1;			/* !Comment: ������Դ�ر�����ź� */
boolean	Rte_bBSW_PowerEna		= 1;			/* !Comment: DCDC28095ʹ������ź� */
boolean	Rte_bBSW_DcdcPwrPrtDO		= 0;			/* !Comment: DCDC28950��������ź� */
boolean	Rte_bBSW_DcdcHartPrtRstDO		= 0;			/* !Comment: DCDCӲ��������λ����ź� */
boolean	Rte_bBSW_McuPwrLockDO		= 1;			/* !Comment: ����������Դ������ź� */
boolean	Rte_bUART_PfcJdqEnaUO		= 0;			/* !Comment: PFC�̵�����������ź� */
boolean	Rte_bUART_LlcJdqEnaUO		= 0;			/* !Comment: LLC�̵�����������ź� */
boolean	Rte_bUART_PfcLedCtrlUO		= 0;			/* !Comment: PFC LED��������ź� */
boolean	Rte_bUART_LlcLedCtrlUO		= 0;			/* !Comment: LLC LED��������ź� */
boolean	Rte_bUART_PfcOnUO		= 0;			/* !Comment: PFCʹ������ź� */
boolean	Rte_bUART_LlcPrtUO		= 1;			/* !Comment: LLC��������ź� */


boolean	Rte_bBSW_TstCcOut680DO		= 0;			/* !Comment: �����ź�: 680ŷCC����ģ����� */
boolean	Rte_bBSW_TstCcOut1000DO		= 0;			/* !Comment: �����ź�: 1000ŷCC����ģ����� */
boolean	Rte_bBSW_TstVcuEnaDO		= 0;			/* !Comment: �����ź�: ����VCU����� */
boolean	Rte_bBSW_TstCpS2CtrlDO		= 0;			/* !Comment: �����ź�: OBC����S2������� */
boolean	Rte_bBSW_TstFanCtrl		= 0;			/* !Comment: �����ź�: ���ȿ����ź���� */
boolean	Rte_bBSW_TstFlyBackEna		= 0;			/* !Comment: �����ź�: ������Դʹ����� */
boolean	Rte_bBSW_TstFlyBackOffDO		= 0;			/* !Comment: �����ź�: ������Դ�ر���� */
boolean	Rte_bBSW_TstPowerEna		= 0;			/* !Comment: �����ź�: DCDC28095ʹ����� */
boolean	Rte_bBSW_TstDcdcPwrPrtDO		= 0;			/* !Comment: �����ź�: DCDC28950������� */
boolean	Rte_bBSW_TstDcdcHartPrtRstDO		= 0;			/* !Comment: �����ź�: DCDCӲ��������λ��� */
boolean	Rte_bBSW_TstMcuPwrLockDO		= 0;			/* !Comment: �����ź�: ����������Դ����� */
boolean	Rte_bUART_TstPfcJdqEnaUO		= 0;			/* !Comment: �����ź�: PFC�̵���������� */
boolean	Rte_bUART_TstLlcJdqEnaUO		= 0;			/* !Comment: �����ź�: LLC�̵���������� */
boolean	Rte_bUART_TstPfcLedCtrlUO		= 0;			/* !Comment: �����ź�: PFC LED������� */
boolean	Rte_bUART_TstLlcLedCtrlUO		= 0;			/* !Comment: �����ź�: LLC LED������� */
boolean	Rte_bUART_TstPfcOnUO		= 0;			/* !Comment: �����ź�: PFCʹ����� */
boolean	Rte_bUART_TstLlcPrtUO		= 0;			/* !Comment: �����ź�: LLC������� */


uint16	Rte_u16BSW_PWMVadj		= 0;			/* !Comment: DCDC��ѹ���� */
uint16	Rte_u16BSW_PWMIadj		= 0;			/* !Comment: DCDC�������� */
uint16	Rte_u16UART_LlcPWMVadjUO		= 0;			/* !Comment: LLC��ѹ���� */
uint16	Rte_u16UART_LlcPWMIadjUO		= 0;			/* !Comment: LLC�������� */


uint16	Rte_u16BSW_TstPWMVadj		= 0;			/* !Comment: ����: DCDC��ѹ���� */
uint16	Rte_u16BSW_TstPWMIadj		= 0;			/* !Comment: ����: DCDC�������� */
uint16	Rte_u16UART_TstLlcPWMVadjUO		= 0;			/* !Comment: ����: LLC��ѹ���� */
uint16	Rte_u16UART_TstLlcPWMIadjUO		= 0;			/* !Comment: ����: LLC�������� */


uint16	Rte_u16BSW_CcOhmHiVolAdc		= 0;			/* !Comment: CC��������ߵ�λ���� */
uint16	Rte_u16BSW_CcOhmLoVolAdc		= 0;			/* !Comment: CC��������͵�λ���� */
uint16	Rte_u16BSW_CpVolAdc		= 0;			/* !Comment: CP��ѹֵ/PWM��ֵ���� */
uint16	Rte_u16BSW_HvVoltAdc		= 0;			/* !Comment: DCDC��ѹ���ѹ���� */
uint16	Rte_u16BSW_HvCurAdc		= 0;			/* !Comment: DCDC��ѹ��������� */
uint16	Rte_u16BSW_LvVoltAdc		= 0;			/* !Comment: DCDC��ѹ���ѹ���� */
uint16	Rte_u16BSW_LvCurAdc		= 0;			/* !Comment: DCDC��ѹ��������� */
uint16	Rte_u16BSW_LvVcc27vAdc		= 0;			/* !Comment: С���ص�ѹ���� */
uint16	Rte_u16BSW_TempSAdc		= 0;			/* !Comment: DCDCԭ���¶Ȳ��� */
uint16	Rte_u16BSW_TempPAdc		= 0;			/* !Comment: DCDC�����¶Ȳ��� */
uint16  Rte_u16BSW_TempMosAdc   = 0;			/* !Comment: MOS��ɢ�Ȱ��¶� */
uint16  Rte_u16BSW_TempExtAdc   = 0;			/* !Comment: �ⲿ������¶� */
uint16  Rte_u16BSW_CcSense1   = 0;			/* !Comment: CC������,��VIN_TEST */
uint16  Rte_u16BSW_VinTest   = 0;			/* !Comment: CC������,��CC_SENSE1 */
uint16	Rte_u16UART_PfcOutputVolAdc		= 0;			/* !Comment: PFC�����ѹ���� */
uint16	Rte_u16UART_LlcOutputVolAdc		= 0;			/* !Comment: LLC�����ѹ���� */
uint16	Rte_u16UART_LlcOutputCurAdc		= 0;			/* !Comment: LLC����������� */
uint16	Rte_u16UART_HiBatVolAdc		= 0;			/* !Comment: ������ص�ѹ���� */
uint16	Rte_u16UART_PfcTempAdc		= 0;			/* !Comment: PFC�¶Ȳ��� */
uint16	Rte_u16UART_LlcFbTempAdc		= 0;			/* !Comment: LLC�����¶Ȳ��� */
uint16	Rte_u16UART_AC220VolAdc		= 0;			/* !Comment: AC220V��ѹ���� */



uint16	Rte_u16BSW_TstCcOhmHiVolAdc		= 0;			/* !Comment: ����: CC��������ߵ�λ���� */
uint16	Rte_u16BSW_TstCcOhmLoVolAdc		= 0;			/* !Comment: ����: CC��������͵�λ���� */
uint16	Rte_u16BSW_TstCpVolAdc		= 0;			/* !Comment: ����: CP��ѹֵ/PWM��ֵ���� */
uint16	Rte_u16BSW_TstAdcHVolt		= 0;			/* !Comment: ����: DCDC��ѹ���ѹ���� */
uint16	Rte_u16BSW_TstAdcHCurrent		= 0;			/* !Comment: ����: DCDC��ѹ��������� */
uint16	Rte_u16BSW_TstAdcLVolt		= 0;			/* !Comment: ����: DCDC��ѹ���ѹ���� */
uint16	Rte_u16BSW_TstAdcLCurrent		= 0;			/* !Comment: ����: DCDC��ѹ��������� */
uint16	Rte_u16BSW_TstAdcLVcc27v		= 0;			/* !Comment: ����: С���ص�ѹ���� */
uint16	Rte_u16BSW_TstAdcTempS		= 0;			/* !Comment: ����: DCDCԭ���¶Ȳ��� */
uint16	Rte_u16BSW_TstAdcTempP		= 0;			/* !Comment: ����: DCDC�����¶Ȳ��� */
uint16	Rte_u16UART_TstPfcOutputVolAdc		= 0;			/* !Comment: ����: PFC�����ѹ���� */
uint16	Rte_u16UART_TstLlcOutputVolAdc		= 0;			/* !Comment: ����: LLC�����ѹ���� */
uint16	Rte_u16UART_TstLlcOutputCurAdc		= 0;			/* !Comment: ����: LLC����������� */
uint16	Rte_u16UART_TstHiBatVolAdc		= 0;			/* !Comment: ����: ������ص�ѹ���� */
uint16	Rte_u16UART_TstPfcTempAdc		= 0;			/* !Comment: ����: PFC�¶Ȳ��� */
uint16	Rte_u16UART_TstLlcFbTempAdc		= 0;			/* !Comment: ����: LLC�����¶Ȳ��� */
uint16	Rte_u16UART_TstAC220VolAdc		= 0;			/* !Comment: ����: AC220V��ѹ���� */


uint16	Rte_u16ASM_CcOhmHiVolAdc		= 0;			/* !Comment: CC��������ߵ�λ */
uint16	Rte_u16ASM_CcOhmLoVolAdc		= 0;			/* !Comment: CC��������͵�λ */
uint16	Rte_u16ASM_CpVolAdc		= 0;			/* !Comment: CP��ѹֵ/PWM��ֵ */
uint16	Rte_u16ASM_HvVolt		= 0;			/* !Comment: DCDC��ѹ���ѹֵ */
uint16	Rte_u16ASM_HvCur		= 0;			/* !Comment: DCDC��ѹ�����ֵ */
uint16	Rte_u16ASM_LvVolt		= 0;			/* !Comment: DCDC��ѹ���ѹֵ */
uint16	Rte_u16ASM_LvCur		= 0;			/* !Comment: DCDC��ѹ�����ֵ */
uint16	Rte_u16ASM_LvVcc27v		= 0;			/* !Comment: С���ص�ѹֵ */
sint16	Rte_s16ASM_TempS		= 0;			/* !Comment: DCDCԭ���¶�ֵ */
sint16	Rte_s16ASM_TempP		= 0;			/* !Comment: DCDC�����¶�ֵ */
sint16  Rte_u16ASM_TempMosAdc   = 0;			/* !Comment: MOS��ɢ�Ȱ��¶� */
sint16  Rte_u16ASM_TempExtAdc   = 0;			/* !Comment: �ⲿ������¶� */
uint16  Rte_u16ASM_CcSense1   = 0;			    /* !Comment: CC������,��VIN_TEST */
uint16  Rte_u16ASM_VinTest   = 0;			    /* !Comment: CC������,��CC_SENSE1 */
uint16	Rte_u16ASM_PfcOutputVolAdc		= 0;			/* !Comment: PFC�����ѹ */
uint16	Rte_u16ASM_LlcOutputVolAdc		= 0;			/* !Comment: LLC�����ѹ */
uint16	Rte_u16ASM_LlcOutputCurAdc		= 0;			/* !Comment: LLC������� */
uint16	Rte_u16ASM_HiBatVolAdc		= 0;			/* !Comment: ������ص�ѹ */
sint16	Rte_s16ASM_PfcTempAdc		= 0;			/* !Comment: PFC�¶� */
sint16	Rte_s16ASM_LlcFbTempAdc		= 0;			/* !Comment: LLC�����¶� */
uint16	Rte_u16ASM_AC220VolAdc		= 0;			/* !Comment: AC220V��ѹ���� */


boolean	Rte_bDSM_OBC_Derating		= 0;			/* !Comment: OBC�������б�� */
boolean	Rte_bDSM_OBC_HwError		= 0;			/* !Comment: DCDCӲ�������� */
boolean	Rte_bDSM_OBC_SwError		= 0;			/* !Comment: DCDC��������� */
boolean	Rte_bDSM_OBC_InOVP		= 0;			/* !Comment: OBC���������ѹ��ѹ��� */
boolean	Rte_bDSM_OBC_InUVP		= 0;			/* !Comment: OBC���������ѹǷѹ��� */
boolean	Rte_bDSM_PFC_OutOVP		= 0;			/* !Comment: PFC�����ѹ��ѹ��� */
boolean	Rte_bDSM_PFC_OutUVP		= 0;			/* !Comment: PFC�����ѹǷѹ��� */
boolean	Rte_bDSM_OBC_OutOVP		= 0;			/* !Comment: OBC�����ѹ��ѹ��� */
boolean	Rte_bDSM_OBC_OutUVP		= 0;			/* !Comment: OBC�����ѹǷѹ��� */
boolean	Rte_bDSM_OBC_OutOSP		= 0;			/* !Comment: OBC�����·��� */
boolean	Rte_bDSM_ObcOCP		= 0;			/* !Comment: OBC������� */

boolean	Rte_bDSM_CarBatOVP		= 0;			/* !Comment: ���ص�ع�ѹ��� */
boolean	Rte_bDSM_CarBatUVP		= 0;			/* !Comment: ���ص��Ƿѹ��� */
boolean	Rte_bDSM_HiBatOVP		= 0;			/* !Comment: ��ѹ��ع�ѹ��� */
boolean	Rte_bDSM_HiBatUVP		= 0;			/* !Comment: ��ѹ���Ƿѹ��� */

boolean	Rte_bOSM_CC_Fault		= 0;			/* !Comment: CC���ϱ�� */
boolean	Rte_bOSM_CP_Fault		= 0;			/* !Comment: CP���ϱ�� */

boolean	Rte_bDSM_Derating		= 0;			/* !Comment: DCDC�������б�� */
boolean	Rte_bDSM_SwError		= 0;			/* !Comment: DCDC��������� */
boolean	Rte_bDSM_HwError		= 0;			/* !Comment: DCDCӲ�������� */
boolean	Rte_bDSM_OutOVP		= 0;			/* !Comment: DCDC�����ѹ��� */
boolean	Rte_bDSM_OutUV2B1		= 0;			/* !Comment: DCDC���Ƿѹһ����� */
boolean	Rte_bDSM_OutUV1BMin		= 0;			/* !Comment: DCDC���Ƿѹ������� */
boolean	Rte_bDSM_OutUVP		= 0;			/* !Comment: DCDC���Ƿѹ��� */
boolean	Rte_bDSM_InOVP		= 0;			/* !Comment: DCDC�����ѹ��� */
boolean	Rte_bDSM_InUVP		= 0;			/* !Comment: DCDC����Ƿѹ��� */
boolean	Rte_bDSM_TempHigh		= 0;			/* !Comment: DCDC�¶ȹ��߱�� */
boolean	Rte_bDSM_TempOTP		= 0;			/* !Comment: DCDC�¶ȳ���������Χ��� */
boolean	Rte_bDSM_DcdcOCP		= 0;			/* !Comment: DCDC������� */
sint8	Rte_s8DSM_TempMin		= 0;			/* !Comment: DCDC��ǰ�¶ȴ�������⵽�ĵ��� */
sint8	Rte_s8DSM_TempMax		= 0;			/* !Comment: DCDC��ǰ�¶ȴ�������⵽�ĸ��� */
uint8	Rte_u8DSM_SWFailSt		= 0;			/* !Comment: DCDC��⵽����������� */

uint8	Rte_u8OSM_CC_ConnectSt  = 0;			/* !Comment: cc����״̬ */
uint8	Rte_u8OSM_CP_ConnectSt  = 0;			/* !Comment: CP����״̬ */

uint8	Rte_u8OSM_WorkingSt		= 0;			/* !Comment: OBC����ģʽ */
uint8	Rte_u8FSM_WorkingSt		= 0;			/* !Comment: DCDC����ģʽ */
uint8	Rte_u8FSM_DCDCSt		= 0;			/* !Comment: DCDC����״̬�� */
uint8	Rte_u8FSM_DCDCWorkSt    = 1;			/* !Comment: DCDC����״̬ */


uint32	Rte_u32TCM_ObcPowerLimt		= 0;			/* !Comment: OBC���������� */
uint32	Rte_u32TCM_PowerLimt		= 0;			/* !Comment: DCDC���������� */
uint16	Rte_u16TCM_VoltLim		= 0;			/* !Comment: DCDC���������ѹ */
uint16	Rte_u16TCM_CurLim		= 0;			/* !Comment: DCDC����������� */
sint8	Rte_s8TCM_DcdcTemp		= 0;			/* !Comment: DCDC�����¶� */
uint8	Rte_u8FSM_SWCurrentFaultSt		= 0;			/* !Comment: DCDC���ڴ�������������� */
uint8	Rte_u8FSM_SWFaultProcessCtrlSt		= 0;			/* !Comment: DCDC��ǰ�������Ĵ���״̬�� */




uint16 u16Debug0;
uint16 u16Debug1;
uint16 u16Debug2;
uint16 u16Debug3;

/* ************************************************************************** */
/*                           SOURCE CODE                                      */
/* ************************************************************************** */



/* ************** End of The File *************************************** */



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
uint8	Rte_u8CAN_ComState		= 0;			/* !Comment: CAN通信状态 */
uint8	Rte_u8CAN_BusoffSt		= 0;			/* !Comment: CAN busoff状态位 */
uint8	Rte_u8CAN_MsgRxSt		= 0;			/* !Comment: CAN 接收报文状态位 */
uint8	Rte_u8UART_ComState		= 1;			/* !Comment: UART通信状态 */
uint16	Rte_u16CAN_UBuckReq		= 0;			/* !Comment: CAN给定输出电压 */
boolean	Rte_bCAN_ModeReq		= 0;			/* !Comment: CAN预冲指令 */


uint16	Rte_u16BMS_MaxChgVol		= 0;			/* !Comment: BMS发送最大充电电压 */
uint16	Rte_u16BMS_MaxChgCur		= 0;			/* !Comment: BMS发送最大充电电流 */
uint8	Rte_u8BMS_SelfChkSt		    = 0xFF;			/* !Comment: BMS自检状态 */
uint8	Rte_u8BMS_ObcCtrlCmd		= 0xFF;			/* !Comment: BMS发送OBC控制指令 */
uint8	Rte_u8BMS_ObcWorkMode		= 0xFF;			/* !Comment: BMS发送OBC工作模式 */
//_hb wuling
uint8	Rte_u8Bat_MaPosRlySts		= 3;			/* !Comment: 电池包主正继电器状态 */
uint8	Rte_u8Bat_MaNegRlySts		= 3;			/* !Comment: 电池包主负继电器状态 */
uint8	Rte_u8Bat_ChrgSts		    = 7;			/* !Comment: 电池包充电状态信号 */
uint8	Rte_u8Bat_HeRlySts			= 3;			/* !Comment: 电池包加热继电器状态 */
uint8	Rte_u8Bat_HeSts				= 3;			/* !Comment: 电池包加热状态*/
uint8	Rte_u8Vec_OptMod			= 6;			/* !Comment: 整车运行模式 */
uint8	Rte_u8Vec_ChrgRqst			= 3;			/* !Comment: 整车充电请求*/
boolean	Rte_bDCDC_Enable			= 0;			/* !Comment: DCDC使能信号 */
uint8	Rte_u8IPS_State			    = 0x0F;			/* !Comment: IPS当前状态*/
boolean	Rte_bOBC_WakeUpEn			= 0;			/* !Comment: OBC唤醒,保持指示 */

boolean Rte_bBSW_PCC                = 0;			/* !Comment: 预冲控制信号, 正控 */
boolean Rte_bBSW_OutSwEn            = 0;			/* !Comment: 低压防反接输出信号, 正控 */
boolean	Rte_bBSW_EmuTestEnable		= 0;			/* !Comment: 模拟测试标记位 */
boolean	Rte_bBSW_IOTestEnable		= 0;			/* !Comment: IO测试标记位 */
boolean	Rte_bBSW_CcEmuTstEna		= 0;			/* !Comment: 充电桩模拟测试使能位 */
boolean	Rte_bBSW_PfcEmuTstEna		= 0;			/* !Comment: PFC模拟测试使能位 */
boolean	Rte_bBSW_LlcEmuTstEna		= 0;			/* !Comment: LLC模拟测试使能位 */
boolean	Rte_bBSW_DcdcEmuTstEna		= 0;			/* !Comment: DCDC模拟测试使能位 */


uint8	Rte_u8BSW_CpVolAMP		= 0;			/* !Comment: CP电压值/PWM幅值 */
uint16	Rte_u16BSW_CpFliterVoltADC		= 0;			/* !Comment: CP电压二次滤波后的值 */
uint16	Rte_u16BSW_CpDutyCal		= 0;			/* !Comment: CP信号的占空比 */
uint16	Rte_u16BSW_TstCpDutyCal		= 0;			/* !Comment: 测试信号: CP信号的占空比 */
uint16	Rte_u16BSW_CcRcOhmVal		= 0;			/* !Comment: RC/RC+R4阻值 */

boolean Rte_bBSW_CanFaultDI     = 1;            /* !Comment: TCAN 1043 诊断输入信号 , 低有效, 出错 */
boolean Rte_bBSW_LockStatusDI   = 1;			/* !Comment: 电子锁锁定状态, 低有效, 锁定*/
boolean	Rte_bBSW_CcPluginDI		= 0;			/* !Comment: CC插枪充电唤醒MCU输入信号 */
boolean	Rte_bBSW_ObcEnaDI		= 0;			/* !Comment: OBC使能输入信号 */
boolean	Rte_bBSW_DcdcEnaDI		= 0;			/* !Comment: DCDC使能输入信号 */
boolean	Rte_bUART_PfcStopUI		= 1;			/* !Comment: PFC请求关闭输入信号 */
boolean	Rte_bUART_LlcHardPrtUI		= 0;			/* !Comment: LLC硬件保护输入信号 */
boolean	Rte_bBSW_LvShortM		= 0;			/* !Comment: 低压侧短路输入信号 */
boolean	Rte_bBSW_VoutInterLockDiag		= 0;			/* !Comment: 高压互锁输入信号 */
boolean	Rte_bBSW_KL15		= 0;			/* !Comment: KL15 */


boolean	Rte_bBSW_TstObcEnaDI		= 0;			/* !Comment: 测试信号: OBC使能输入 */
boolean	Rte_bBSW_TstDcdcEnaDI		= 0;			/* !Comment: 测试信号: DCDC使能输入 */
boolean	Rte_bUART_TstPfcStopUI		= 0;			/* !Comment: 测试信号: PFC请求关闭输入 */
boolean	Rte_bUART_TstLlcHardPrtUI		= 0;			/* !Comment: 测试信号: LLC硬件保护输入 */
boolean	Rte_bBSW_TstLvShortM		= 0;			/* !Comment: 测试信号: 低压侧短路输入 */
boolean	Rte_bBSW_TstVoutInterLockDiag		= 0;			/* !Comment: 测试信号: 高压互锁输入 */
boolean	Rte_bBSW_TstKL15		= 0;			/* !Comment: 测试信号: KL15 */


boolean	Rte_bBSW_CcOut680DO		= 0;			/* !Comment: 680欧CC电阻模拟输出信号 */
boolean	Rte_bBSW_CcOut1000DO		= 0;			/* !Comment: 1000欧CC电阻模拟输出信号 */
boolean	Rte_bBSW_VcuEnaDO		= 0;			/* !Comment: 唤醒VCU的输出信号 */
boolean	Rte_bBSW_CpS2CtrlDO		= 0;			/* !Comment: OBC就绪S2控制输出信号 */
boolean	Rte_bBSW_FanCtrl		= 0;			/* !Comment: 风扇控制信号输出信号 */
boolean	Rte_bBSW_FlyBackEna		= 1;			/* !Comment: 反激电源使能输出信号 */
boolean	Rte_bBSW_FlyBackOffDO		= 1;			/* !Comment: 反激电源关闭输出信号 */
boolean	Rte_bBSW_PowerEna		= 1;			/* !Comment: DCDC28095使能输出信号 */
boolean	Rte_bBSW_DcdcPwrPrtDO		= 0;			/* !Comment: DCDC28950保护输出信号 */
boolean	Rte_bBSW_DcdcHartPrtRstDO		= 0;			/* !Comment: DCDC硬件保护复位输出信号 */
boolean	Rte_bBSW_McuPwrLockDO		= 1;			/* !Comment: 主控制器电源锁输出信号 */
boolean	Rte_bUART_PfcJdqEnaUO		= 0;			/* !Comment: PFC继电器控制输出信号 */
boolean	Rte_bUART_LlcJdqEnaUO		= 0;			/* !Comment: LLC继电器控制输出信号 */
boolean	Rte_bUART_PfcLedCtrlUO		= 0;			/* !Comment: PFC LED控制输出信号 */
boolean	Rte_bUART_LlcLedCtrlUO		= 0;			/* !Comment: LLC LED控制输出信号 */
boolean	Rte_bUART_PfcOnUO		= 0;			/* !Comment: PFC使能输出信号 */
boolean	Rte_bUART_LlcPrtUO		= 1;			/* !Comment: LLC保护输出信号 */


boolean	Rte_bBSW_TstCcOut680DO		= 0;			/* !Comment: 测试信号: 680欧CC电阻模拟输出 */
boolean	Rte_bBSW_TstCcOut1000DO		= 0;			/* !Comment: 测试信号: 1000欧CC电阻模拟输出 */
boolean	Rte_bBSW_TstVcuEnaDO		= 0;			/* !Comment: 测试信号: 唤醒VCU的输出 */
boolean	Rte_bBSW_TstCpS2CtrlDO		= 0;			/* !Comment: 测试信号: OBC就绪S2控制输出 */
boolean	Rte_bBSW_TstFanCtrl		= 0;			/* !Comment: 测试信号: 风扇控制信号输出 */
boolean	Rte_bBSW_TstFlyBackEna		= 0;			/* !Comment: 测试信号: 反激电源使能输出 */
boolean	Rte_bBSW_TstFlyBackOffDO		= 0;			/* !Comment: 测试信号: 反激电源关闭输出 */
boolean	Rte_bBSW_TstPowerEna		= 0;			/* !Comment: 测试信号: DCDC28095使能输出 */
boolean	Rte_bBSW_TstDcdcPwrPrtDO		= 0;			/* !Comment: 测试信号: DCDC28950保护输出 */
boolean	Rte_bBSW_TstDcdcHartPrtRstDO		= 0;			/* !Comment: 测试信号: DCDC硬件保护复位输出 */
boolean	Rte_bBSW_TstMcuPwrLockDO		= 0;			/* !Comment: 测试信号: 主控制器电源锁输出 */
boolean	Rte_bUART_TstPfcJdqEnaUO		= 0;			/* !Comment: 测试信号: PFC继电器控制输出 */
boolean	Rte_bUART_TstLlcJdqEnaUO		= 0;			/* !Comment: 测试信号: LLC继电器控制输出 */
boolean	Rte_bUART_TstPfcLedCtrlUO		= 0;			/* !Comment: 测试信号: PFC LED控制输出 */
boolean	Rte_bUART_TstLlcLedCtrlUO		= 0;			/* !Comment: 测试信号: LLC LED控制输出 */
boolean	Rte_bUART_TstPfcOnUO		= 0;			/* !Comment: 测试信号: PFC使能输出 */
boolean	Rte_bUART_TstLlcPrtUO		= 0;			/* !Comment: 测试信号: LLC保护输出 */


uint16	Rte_u16BSW_PWMVadj		= 0;			/* !Comment: DCDC电压给定 */
uint16	Rte_u16BSW_PWMIadj		= 0;			/* !Comment: DCDC电流给定 */
uint16	Rte_u16UART_LlcPWMVadjUO		= 0;			/* !Comment: LLC电压给定 */
uint16	Rte_u16UART_LlcPWMIadjUO		= 0;			/* !Comment: LLC电流给定 */


uint16	Rte_u16BSW_TstPWMVadj		= 0;			/* !Comment: 测试: DCDC电压给定 */
uint16	Rte_u16BSW_TstPWMIadj		= 0;			/* !Comment: 测试: DCDC电流给定 */
uint16	Rte_u16UART_TstLlcPWMVadjUO		= 0;			/* !Comment: 测试: LLC电压给定 */
uint16	Rte_u16UART_TstLlcPWMIadjUO		= 0;			/* !Comment: 测试: LLC电流给定 */


uint16	Rte_u16BSW_CcOhmHiVolAdc		= 0;			/* !Comment: CC电阻测量高电位采样 */
uint16	Rte_u16BSW_CcOhmLoVolAdc		= 0;			/* !Comment: CC电阻测量低电位采样 */
uint16	Rte_u16BSW_CpVolAdc		= 0;			/* !Comment: CP电压值/PWM幅值采样 */
uint16	Rte_u16BSW_HvVoltAdc		= 0;			/* !Comment: DCDC高压侧电压采样 */
uint16	Rte_u16BSW_HvCurAdc		= 0;			/* !Comment: DCDC高压侧电流采样 */
uint16	Rte_u16BSW_LvVoltAdc		= 0;			/* !Comment: DCDC低压侧电压采样 */
uint16	Rte_u16BSW_LvCurAdc		= 0;			/* !Comment: DCDC低压侧电流采样 */
uint16	Rte_u16BSW_LvVcc27vAdc		= 0;			/* !Comment: 小蓄电池电压采样 */
uint16	Rte_u16BSW_TempSAdc		= 0;			/* !Comment: DCDC原边温度采样 */
uint16	Rte_u16BSW_TempPAdc		= 0;			/* !Comment: DCDC副边温度采样 */
uint16  Rte_u16BSW_TempMosAdc   = 0;			/* !Comment: MOS旁散热板温度 */
uint16  Rte_u16BSW_TempExtAdc   = 0;			/* !Comment: 外部充电座温度 */
uint16  Rte_u16BSW_CcSense1   = 0;			/* !Comment: CC电阻检测,需VIN_TEST */
uint16  Rte_u16BSW_VinTest   = 0;			/* !Comment: CC电阻检测,需CC_SENSE1 */
uint16	Rte_u16UART_PfcOutputVolAdc		= 0;			/* !Comment: PFC输出电压采样 */
uint16	Rte_u16UART_LlcOutputVolAdc		= 0;			/* !Comment: LLC输出电压采样 */
uint16	Rte_u16UART_LlcOutputCurAdc		= 0;			/* !Comment: LLC输出电流采样 */
uint16	Rte_u16UART_HiBatVolAdc		= 0;			/* !Comment: 动力电池电压采样 */
uint16	Rte_u16UART_PfcTempAdc		= 0;			/* !Comment: PFC温度采样 */
uint16	Rte_u16UART_LlcFbTempAdc		= 0;			/* !Comment: LLC副边温度采样 */
uint16	Rte_u16UART_AC220VolAdc		= 0;			/* !Comment: AC220V电压采样 */



uint16	Rte_u16BSW_TstCcOhmHiVolAdc		= 0;			/* !Comment: 测试: CC电阻测量高电位采样 */
uint16	Rte_u16BSW_TstCcOhmLoVolAdc		= 0;			/* !Comment: 测试: CC电阻测量低电位采样 */
uint16	Rte_u16BSW_TstCpVolAdc		= 0;			/* !Comment: 测试: CP电压值/PWM幅值采样 */
uint16	Rte_u16BSW_TstAdcHVolt		= 0;			/* !Comment: 测试: DCDC高压侧电压采样 */
uint16	Rte_u16BSW_TstAdcHCurrent		= 0;			/* !Comment: 测试: DCDC高压侧电流采样 */
uint16	Rte_u16BSW_TstAdcLVolt		= 0;			/* !Comment: 测试: DCDC低压侧电压采样 */
uint16	Rte_u16BSW_TstAdcLCurrent		= 0;			/* !Comment: 测试: DCDC低压侧电流采样 */
uint16	Rte_u16BSW_TstAdcLVcc27v		= 0;			/* !Comment: 测试: 小蓄电池电压采样 */
uint16	Rte_u16BSW_TstAdcTempS		= 0;			/* !Comment: 测试: DCDC原边温度采样 */
uint16	Rte_u16BSW_TstAdcTempP		= 0;			/* !Comment: 测试: DCDC副边温度采样 */
uint16	Rte_u16UART_TstPfcOutputVolAdc		= 0;			/* !Comment: 测试: PFC输出电压采样 */
uint16	Rte_u16UART_TstLlcOutputVolAdc		= 0;			/* !Comment: 测试: LLC输出电压采样 */
uint16	Rte_u16UART_TstLlcOutputCurAdc		= 0;			/* !Comment: 测试: LLC输出电流采样 */
uint16	Rte_u16UART_TstHiBatVolAdc		= 0;			/* !Comment: 测试: 动力电池电压采样 */
uint16	Rte_u16UART_TstPfcTempAdc		= 0;			/* !Comment: 测试: PFC温度采样 */
uint16	Rte_u16UART_TstLlcFbTempAdc		= 0;			/* !Comment: 测试: LLC副边温度采样 */
uint16	Rte_u16UART_TstAC220VolAdc		= 0;			/* !Comment: 测试: AC220V电压采样 */


uint16	Rte_u16ASM_CcOhmHiVolAdc		= 0;			/* !Comment: CC电阻测量高电位 */
uint16	Rte_u16ASM_CcOhmLoVolAdc		= 0;			/* !Comment: CC电阻测量低电位 */
uint16	Rte_u16ASM_CpVolAdc		= 0;			/* !Comment: CP电压值/PWM幅值 */
uint16	Rte_u16ASM_HvVolt		= 0;			/* !Comment: DCDC高压侧电压值 */
uint16	Rte_u16ASM_HvCur		= 0;			/* !Comment: DCDC高压侧电流值 */
uint16	Rte_u16ASM_LvVolt		= 0;			/* !Comment: DCDC低压侧电压值 */
uint16	Rte_u16ASM_LvCur		= 0;			/* !Comment: DCDC低压侧电流值 */
uint16	Rte_u16ASM_LvVcc27v		= 0;			/* !Comment: 小蓄电池电压值 */
sint16	Rte_s16ASM_TempS		= 0;			/* !Comment: DCDC原边温度值 */
sint16	Rte_s16ASM_TempP		= 0;			/* !Comment: DCDC副边温度值 */
sint16  Rte_u16ASM_TempMosAdc   = 0;			/* !Comment: MOS旁散热板温度 */
sint16  Rte_u16ASM_TempExtAdc   = 0;			/* !Comment: 外部充电座温度 */
uint16  Rte_u16ASM_CcSense1   = 0;			    /* !Comment: CC电阻检测,需VIN_TEST */
uint16  Rte_u16ASM_VinTest   = 0;			    /* !Comment: CC电阻检测,需CC_SENSE1 */
uint16	Rte_u16ASM_PfcOutputVolAdc		= 0;			/* !Comment: PFC输出电压 */
uint16	Rte_u16ASM_LlcOutputVolAdc		= 0;			/* !Comment: LLC输出电压 */
uint16	Rte_u16ASM_LlcOutputCurAdc		= 0;			/* !Comment: LLC输出电流 */
uint16	Rte_u16ASM_HiBatVolAdc		= 0;			/* !Comment: 动力电池电压 */
sint16	Rte_s16ASM_PfcTempAdc		= 0;			/* !Comment: PFC温度 */
sint16	Rte_s16ASM_LlcFbTempAdc		= 0;			/* !Comment: LLC副边温度 */
uint16	Rte_u16ASM_AC220VolAdc		= 0;			/* !Comment: AC220V电压采样 */


boolean	Rte_bDSM_OBC_Derating		= 0;			/* !Comment: OBC降额运行标记 */
boolean	Rte_bDSM_OBC_HwError		= 0;			/* !Comment: DCDC硬件错误标记 */
boolean	Rte_bDSM_OBC_SwError		= 0;			/* !Comment: DCDC软件错误标记 */
boolean	Rte_bDSM_OBC_InOVP		= 0;			/* !Comment: OBC交流输入电压过压标记 */
boolean	Rte_bDSM_OBC_InUVP		= 0;			/* !Comment: OBC交流输入电压欠压标记 */
boolean	Rte_bDSM_PFC_OutOVP		= 0;			/* !Comment: PFC输出电压过压标记 */
boolean	Rte_bDSM_PFC_OutUVP		= 0;			/* !Comment: PFC输出电压欠压标记 */
boolean	Rte_bDSM_OBC_OutOVP		= 0;			/* !Comment: OBC输出电压过压标记 */
boolean	Rte_bDSM_OBC_OutUVP		= 0;			/* !Comment: OBC输出电压欠压标记 */
boolean	Rte_bDSM_OBC_OutOSP		= 0;			/* !Comment: OBC输出短路标记 */
boolean	Rte_bDSM_ObcOCP		= 0;			/* !Comment: OBC过流标记 */

boolean	Rte_bDSM_CarBatOVP		= 0;			/* !Comment: 车载电池过压标记 */
boolean	Rte_bDSM_CarBatUVP		= 0;			/* !Comment: 车载电池欠压标记 */
boolean	Rte_bDSM_HiBatOVP		= 0;			/* !Comment: 高压电池过压标记 */
boolean	Rte_bDSM_HiBatUVP		= 0;			/* !Comment: 高压电池欠压标记 */

boolean	Rte_bOSM_CC_Fault		= 0;			/* !Comment: CC故障标记 */
boolean	Rte_bOSM_CP_Fault		= 0;			/* !Comment: CP故障标记 */

boolean	Rte_bDSM_Derating		= 0;			/* !Comment: DCDC降额运行标记 */
boolean	Rte_bDSM_SwError		= 0;			/* !Comment: DCDC软件错误标记 */
boolean	Rte_bDSM_HwError		= 0;			/* !Comment: DCDC硬件错误标记 */
boolean	Rte_bDSM_OutOVP		= 0;			/* !Comment: DCDC输出过压标记 */
boolean	Rte_bDSM_OutUV2B1		= 0;			/* !Comment: DCDC输出欠压一档标记 */
boolean	Rte_bDSM_OutUV1BMin		= 0;			/* !Comment: DCDC输出欠压二档标记 */
boolean	Rte_bDSM_OutUVP		= 0;			/* !Comment: DCDC输出欠压标记 */
boolean	Rte_bDSM_InOVP		= 0;			/* !Comment: DCDC输入过压标记 */
boolean	Rte_bDSM_InUVP		= 0;			/* !Comment: DCDC输入欠压标记 */
boolean	Rte_bDSM_TempHigh		= 0;			/* !Comment: DCDC温度过高标记 */
boolean	Rte_bDSM_TempOTP		= 0;			/* !Comment: DCDC温度超出工作范围标记 */
boolean	Rte_bDSM_DcdcOCP		= 0;			/* !Comment: DCDC过流标记 */
sint8	Rte_s8DSM_TempMin		= 0;			/* !Comment: DCDC当前温度传感器检测到的低温 */
sint8	Rte_s8DSM_TempMax		= 0;			/* !Comment: DCDC当前温度传感器检测到的高温 */
uint8	Rte_u8DSM_SWFailSt		= 0;			/* !Comment: DCDC检测到的软件错误码 */

uint8	Rte_u8OSM_CC_ConnectSt  = 0;			/* !Comment: cc连接状态 */
uint8	Rte_u8OSM_CP_ConnectSt  = 0;			/* !Comment: CP连接状态 */

uint8	Rte_u8OSM_WorkingSt		= 0;			/* !Comment: OBC工作模式 */
uint8	Rte_u8FSM_WorkingSt		= 0;			/* !Comment: DCDC工作模式 */
uint8	Rte_u8FSM_DCDCSt		= 0;			/* !Comment: DCDC运行状态码 */
uint8	Rte_u8FSM_DCDCWorkSt    = 1;			/* !Comment: DCDC运行状态 */


uint32	Rte_u32TCM_ObcPowerLimt		= 0;			/* !Comment: OBC可输出最大功率 */
uint32	Rte_u32TCM_PowerLimt		= 0;			/* !Comment: DCDC可输出最大功率 */
uint16	Rte_u16TCM_VoltLim		= 0;			/* !Comment: DCDC限制输出电压 */
uint16	Rte_u16TCM_CurLim		= 0;			/* !Comment: DCDC可输出最大电流 */
sint8	Rte_s8TCM_DcdcTemp		= 0;			/* !Comment: DCDC工作温度 */
uint8	Rte_u8FSM_SWCurrentFaultSt		= 0;			/* !Comment: DCDC正在处理的软件错误代码 */
uint8	Rte_u8FSM_SWFaultProcessCtrlSt		= 0;			/* !Comment: DCDC当前软件错误的处理状态码 */




uint16 u16Debug0;
uint16 u16Debug1;
uint16 u16Debug2;
uint16 u16Debug3;

/* ************************************************************************** */
/*                           SOURCE CODE                                      */
/* ************************************************************************** */



/* ************** End of The File *************************************** */

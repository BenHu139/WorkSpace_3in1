
/* all rights reserved                                                        */
/* ****************************************************************************/

#ifndef RTE_DEF_H
#define RTE_DEF_H

/* !Comment: Included File             */
#include "Std_Types.h"


/* ************************************************************************** */
/*                                 MACROS                                     */
/* ************************************************************************** */
#define Rte_udtHvVolt(udtValue)           (udtValue * 10)
#define Rte_udtLvVolt(udtValue)           (udtValue * 10)
#define Rte_udtLvCur(udtValue)            (udtValue * 10)
#define Rte_udtHvCur(udtValue)            (udtValue * 10)
#define Rte_udtPower(udtValue)            (udtValue * 100)
#define Rte_udtTest(udtValue)             (udtValue * 10)
#define Rte_udtOhm(udtValue)			  (udtValue * 10)
#define Rte_udtVolt(udtValue)			  (udtValue * 10)
#define Rte_udtCur(udtValue)			  (udtValue * 10)
#define Rte_udtSecond(udtValue)			  (udtValue * 100)
#define Rte_udtCpDuty(udtValue)			  (udtValue * 10)


#define Rte_udtTemperature(udtValue)      (udtValue)

#define RTE_NO_SW_FAULT				      ((u8)(0x00))
#define RTE_OUTPUT_OVER_CURRENT			  ((u8)(0x01))
#define RTE_INPUT_OVER_CURRENT			  ((u8)(0x02))
#define RTE_OVER_TEMPERATURE			  ((u8)(0x03))
#define RTE_INPUT_OVER_VOLT				  ((u8)(0x04))
#define RTE_INPUT_UNDER_VOLT		      ((u8)(0x05))
#define RTE_OUTPUT_OVER_VOLT			  ((u8)(0x06))
#define RTE_OUTPUT_VOLT_2B1			      ((u8)(0x07))
#define RTE_OUTPUT_VOLT_1BMin			  ((u8)(0x08))
#define RTE_OUTPUT_UNDER_VOLT			  ((u8)(0x09))
#define RTE_DERATE_TEMPERATURE			  ((u8)(0x0A))
#define RTE_NORMAL_TEMPERATURE			  ((u8)(0x0B))

/* ************************************************************************** */
/*                                 TYPES                                      */
/* ************************************************************************** */


/* ************************************************************************** */
/*                              GLOABAL VARIRABLE                             */
/* ************************************************************************** */

#pragma push
#pragma section data_type ".calib_ram" ".calib_ram"
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcAc220OverTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcAc220OverResume;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcAc220Max;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcAc220Nomal;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcAc220Min;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcAc220UnderTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcAc220UnderResume;

__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcOutVoltOverTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcOutVoltOverResume;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcOutVoltUnderTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16PfcOutVoltUnderResume;

__declspec(section ".calib_ram") extern const uint16 Rte_ou16CloseLlcJdqLlcMinVolt;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16EnableLlcMinPfcOutVolt;

__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutVoltOverTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutVoltOverResume;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutVoltMax;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutVoltNomal;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutVoltMin;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutVoltUnderTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutVoltUnderResume;

__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutCurrOverTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutCurrOverResume;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16LlcOutCurrShortTriger;

__declspec(section ".calib_ram") extern const uint16 Rte_ou16CarBatVoltOverTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16CarBatVoltOverResume;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16CarBatVoltUnderTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16CarBatVoltUnderResume;

__declspec(section ".calib_ram") extern const uint16 Rte_ou16HiBatVoltOverTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16HiBatVoltOverResume;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16HiBatVoltUnderTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16HiBatVoltUnderResume;

__declspec(section ".calib_ram") extern const uint16 Rte_ou16CarBatVoltOverTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16CarBatVoltOverResume;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16CarBatVoltUnderTriger;
__declspec(section ".calib_ram") extern const uint16 Rte_ou16CarBatVoltUnderResume;

__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltMaxProC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltMaxC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltUVP2;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltUVP1;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltMinC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltNormMaxC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltNormMinC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltNormMaxC1;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltNormal;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvVoltNormMinC1;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvDisconVolt;
__declspec(section ".calib_ram") extern const uint16 Rte_ku8LvThrC;

__declspec(section ".calib_ram") extern const uint16 Rte_ku16LvDerateCurH;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16LvDerateCurL;

__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvVoltMaxProC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvVoltMaxC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvVoltMinC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvVoltNormMaxC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvVoltNormMinC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvVoltNormMaxC1;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvVoltNormMinC1;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvThrC;

__declspec(section ".calib_ram") extern const uint16 Rte_ku16LvCurProMaxC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16LvCurMaxC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16LvCurNormMaxC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16LvCurNormMinC;

__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvCurProMaxC;
__declspec(section ".calib_ram") extern const uint16 Rte_ku16HvCurMaxC;

__declspec(section ".calib_ram") extern const uint32 Rte_ku16PowerMaxC;
__declspec(section ".calib_ram") extern const uint32 Rte_ku16PowerNorm;
__declspec(section ".calib_ram") extern const uint32 Rte_ku16PowerMargin;

__declspec(section ".calib_ram") extern const sint8 Rte_ks8TempMinC;
__declspec(section ".calib_ram") extern const sint8 Rte_ks8TempNormC;
__declspec(section ".calib_ram") extern const sint8 Rte_ks8TempNormMaxC;
__declspec(section ".calib_ram") extern const sint8 Rte_ks8TempRecoveryC;
__declspec(section ".calib_ram") extern const sint8 Rte_ks8TempMaxC;
__declspec(section ".calib_ram") extern const sint8 Rte_ks8TempThrC;

#pragma pop


/* ************************************************************************** */
/*                           ProtoType                                        */
/* ************************************************************************** */

/* ************** End of The File *************************************** */

#endif

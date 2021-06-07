
#ifndef EMIOS_DRV_H_
#define EMIOS_DRV_H_

/*****************************************************************************/
/*                                 INCLUDE                                   */
/*****************************************************************************/
//#include "Std_Type.h"

/*****************************************************************************/
/*                                 MACROS                                    */
/*****************************************************************************/

#define EMIOS_MOD_0   0
#define EMIOS_MOD_1   1

#define EMIOS_CH_0    0
#define EMIOS_CH_1    1 
#define EMIOS_CH_2    2
#define EMIOS_CH_3    3
#define EMIOS_CH_4    4
#define EMIOS_CH_5    5
#define EMIOS_CH_6    6
#define EMIOS_CH_7    7
#define EMIOS_CH_8    8
#define EMIOS_CH_9    9
#define EMIOS_CH_10   10
#define EMIOS_CH_11   11
#define EMIOS_CH_12   12
#define EMIOS_CH_13   13
#define EMIOS_CH_14   14
#define EMIOS_CH_15   15
#define EMIOS_CH_16   16
#define EMIOS_CH_17   17
#define EMIOS_CH_18   18
#define EMIOS_CH_19   19
#define EMIOS_CH_20   20
#define EMIOS_CH_21   21
#define EMIOS_CH_22   22
#define EMIOS_CH_23   23
#define EMIOS_CH_24   24
#define EMIOS_CH_25   25
#define EMIOS_CH_26   26
#define EMIOS_CH_27   27

#define EMIOS_MAX_CH  28

#define EMIOS_GPRE_1                 ((u8)0x00) 
#define EMIOS_GPRE_2                 ((u8)0x01) 
#define EMIOS_GPRE_4                 ((u8)0x03)  
#define EMIOS_GPRE_8                 ((u8)0x07) 
#define EMIOS_GPRE_16                ((u8)0x0F) 
#define EMIOS_GPRE_32                ((u8)0x1F) 
#define EMIOS_GPRE_64                ((u8)0x3F) 
#define EMIOS_GPRE_128               ((u8)0x7F) 

#define FLAG_BIT_DIS				 (0)
#define FLAG_BIT_ENA				 (1)

#define FLAG_OVERRUN_AS_CTU			 (1)
#define FLAG_OVERRUN_AS_INT          (0)

#define EMIOS_UCPRE_1                (0)
#define EMIOS_UCPRE_2                (1)
#define EMIOS_UCPRE_3                (2)
#define EMIOS_UCPRE_4                (3)

#define EMIOS_UCIF_BYPASS            (0)
#define EMIOS_UCIF_2                 (1)
#define EMIOS_UCIF_4                 (2)
#define EMIOS_UCIF_8                 (4)
#define EMIOS_UCIF_16                (8)

#define EMIOS_UCBSL_ALL_A            (0)
#define EMIOS_UCBSL_0T7_B            (1)
#define EMIOS_UCBSL_8T15_C           (1)
#define EMIOS_UCBSL_16T23_D          (1)
#define EMIOS_UCBSL_24T27_E          (1)
#define EMIOS_UCBSL_ALL_INTER        (3) // ALL TO internal counter

#define EMIOS_UCMODE_GPIO_INPUT      (0x00)
#define EMIOS_UCMODE_GPIO_OUTPUT     (0x01)
#define EMIOS_UCMODE_MCB             (0x50)
#define EMIOS_UCMODE_OPWMCB          (0x60)
#define EMIOS_UCMODE_IPWM            (0x04)
#define EMIOS_UCMODE_IPM             (0x05)

#define EMIOS_EDSEL_HIGH             (1)
#define EMIOS_EDSEL_LOW              (0)

#define EMIOS_EDPOL_HIGH             (1)
#define EMIOS_EDPOL_LOW              (0)

#define eMIOSModuleEnable(module)                            eMIOSModuleEnableEx(module)
#define eMIOSModuleEnableEx(module)                          (EMIOS_##module##.MCR.B.MDIS = 0)                   // defalut: enable
#define eMIOSModuleEnterLowPower(module)                     eMIOSModuleEnterLowPowerEx(module)
#define eMIOSModuleEnterLowPowerEx(module)                   (EMIOS_##module##.MCR.B.MDIS = 1)

#define eMIOSSetFreezeFlag(module)                           eMIOSSetFreezeFlagEx(module)
#define eMIOSSetFreezeFlagEx(module)                         (EMIOS_##module##.MCR.B.FRZ = 1)                        
#define eMIOSExitFreezeState(module)                         eMIOSExitFreezeStateEx(module)
#define eMIOSExitFreezeStateEx(module)                       (EMIOS_##module##.MCR.B.FRZ = 0)                    // default

#define eMIOSDisableInternalCounter(module)                  eMIOSDisableInternalCounterEx(module)
#define eMIOSDisableInternalCounterEx(module)                (EMIOS_##module##.MCR.B.GTBE = 0)                   // default
#define eMIOSEnableInternalCounter(module)                   eMIOSEnableInternalCounterEx(module)
#define eMIOSEnableInternalCounterEx(module)                 (EMIOS_##module##.MCR.B.GTBE = 1)  

#define eMIOSSetGlobalPrescaler(module, value)               eMIOSSetGlobalPrescalerEx(module, value)
#define eMIOSSetGlobalPrescalerEx(module, value)             (EMIOS_##module##.MCR.B.GPRE = value)          

#define eMIOSDisableGlobalPrescaler(module)                  eMIOSDisableGlobalPrescalerEx(module)
#define eMIOSDisableGlobalPrescalerEx(module)                (EMIOS_##module##.MCR.B.GPREN = 0)                   //default
#define eMIOSEnableGlobalPrescaler(module)                   eMIOSEnableGlobalPrescalerEx(module)
#define eMIOSEnableGlobalPrescalerEx(module)                 (EMIOS_##module##.MCR.B.GPREN = 1)

#define eMIOSDisableOutputUpdateFlag(module, channel)        eMIOSDisableOutputUpdateFlagEx(module, channel)
#define eMIOSDisableOutputUpdateFlagEx(module, channel)      (EMIOS_##module##.OUDR.B.OU##channel## = 1)    
#define eMIOSEnableOutputUpdateFlag(module, channel)         eMIOSEnableOutputUpdateFlagEx(module, channel)
#define eMIOSEnableOutputUpdateFlagEx(module, channel)       (EMIOS_##module##.OUDR.B.OU##channel## = 0)         // default: enable

#define eMIOSGetGlobalFlag(module, channel)                  eMIOSGetGlobalFlagEx(module, channel)
#define eMIOSGetGlobalFlagEx(module, channel)                (EMIOS_##module##.GFR.B.F##channel##) 

#define eMIOSDisableChannel(module, channel)                 eMIOSDisableChannelEx(module, channel)
#define eMIOSDisableChannelEx(module, channel)               (EMIOS_##module##.UCDIS.B.CHDIS##channel## = 1)    
#define eMIOSEnableChannel(module, channel)                  eMIOSEnableChannelEx(module, channel)
#define eMIOSEnableChannelEx(module, channel)                (EMIOS_##module##.UCDIS.B.CHDIS##channel## = 0)    

#define eMIOSSetUCCounter(module, channel, value)            eMIOSSetUCCounterEx(module, channel, value)                // 只能在GPIO模式下设置Counter值
#define eMIOSSetUCCounterEx(module, channel, value)          (EMIOS_##module##.CH[##channel##].CCNTR.B.CCNTR = value)
#define eMIOSGetUCCounter(module, channel)                   eMIOSGetUCCounterEx(module, channel)                       // 在其它模式下只读
#define eMIOSGetUCCounterEx(module, channel)                 (EMIOS_##module##.CH[##channel##].CCNTR.B.CCNTR)

#define eMIOSSetUCReg16A(module, channel, value)             eMIOSSetUCReg16AEx(module, channel, value)
#define eMIOSSetUCReg16AEx(module, channel, value)           (EMIOS_##module##.CH[##channel##].CADR.B.CADR = value)
#define eMIOSGetUCReg16A(module, channel)                    eMIOSGetUCReg16AEx(module, channel)
#define eMIOSGetUCReg16AEx(module, channel)                  (EMIOS_##module##.CH[##channel##].CADR.B.CADR)

#define eMIOSSetUCReg16B(module, channel, value)             eMIOSSetUCReg16BEx(module, channel, value)
#define eMIOSSetUCReg16BEx(module, channel, value)           (EMIOS_##module##.CH[##channel##].CBDR.B.CBDR = value)
#define eMIOSGetUCReg16B(module, channel)                    eMIOSGetUCReg16BEx(module, channel)
#define eMIOSGetUCReg16BEx(module, channel)                  (EMIOS_##module##.CH[##channel##].CBDR.B.CBDR)

#define eMIOSSetReg16ALTA(module, channel, value)            eMIOSSetReg16ALTAEx(module, channel, value)
#define eMIOSSetReg16ALTAEx(module, channel, value)          (EMIOS_##module##.CH[##channel##].ALTCADR.B.ALTCADR = value)
#define eMIOSGetReg16ALTA(module, channel)                   eMIOSGetReg16ALTAEx(module, channel)
#define eMIOSGetReg16ALTAEx(module, channel)                 (EMIOS_##module##.CH[##channel##].ALTCADR.B.ALTCADR)

#define eMIOSSetUCPRE(module, channel, value)                eMIOSSetUCPREEx(module, channel, value)
#define eMIOSSetUCPREEx(module, channel, value)              (EMIOS_##module##.CH[##channel##].CCR.B.UCPRE = value)

#define eMIOSEnableUCPEN(module, channel)                    eMIOSEnableUCPENEx(module, channel)
#define eMIOSEnableUCPENEx(module, channel)                  (EMIOS_##module##.CH[##channel##].CCR.B.UCPEN = 1)
#define eMIOSDisableUCPEN(module, channel)                   eMIOSDisableUCPENEx(module, channel)
#define eMIOSDisableUCPENEx(module, channel)                 (EMIOS_##module##.CH[##channel##].CCR.B.UCPEN = 0)

#define eMIOSSetEDSEL(module, channel, value)                eMIOSSetEDSELEx(module, channel, value)
#define eMIOSSetEDSELEx(module, channel, value)              (EMIOS_##module##.CH[##channel##].CCR.B.EDSEL = value)

#define eMIOSSetEDPOL(module, channel, value)                eMIOSSetEDPOLEx(module, channel, value)
#define eMIOSSetEDPOLEx(module, channel, value)              (EMIOS_##module##.CH[##channel##].CCR.B.EDPOL = value)

#define eMIOSSetBSL(module, channel, value)                  eMIOSSetBSLEx(module, channel, value)
#define eMIOSSetBSLEx(module, channel, value)                (EMIOS_##module##.CH[##channel##].CCR.B.BSL = value)

#define eMIOSSetMODE(module, channel, value)                 eMIOSSetMODEEx(module, channel, value)
#define eMIOSSetMODEEx(module, channel, value)               (EMIOS_##module##.CH[##channel##].CCR.B.MODE = value)

#define eMIOSEnableUCFreeze(module, channel)                 eMIOSEnableUCFreezeEx(module, channel)
#define eMIOSEnableUCFreezeEx(module, channel)               (EMIOS_##module##.CH[##channel##].CCR.B.FREN = 1)
#define eMIOSDisableUCFreeze(module, channel)                eMIOSDisableUCFreezeEx(module, channel)
#define eMIOSDisableUCFreezeEx(module, channel)              (EMIOS_##module##.CH[##channel##].CCR.B.FREN = 0)
/*****************************************************************************/
/*                                 TYPES                                     */
/*****************************************************************************/

/*****************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/*****************************************************************************/


/*****************************************************************************/
/*                                 PROTOTYPES                                */
/*****************************************************************************/


#endif


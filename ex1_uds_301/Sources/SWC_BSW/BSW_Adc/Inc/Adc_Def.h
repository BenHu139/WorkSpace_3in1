
/*****************************************************************************/

#ifndef ADC_DEF_H_
#define ADC_DEF_H_

/*****************************************************************************/
/*                                 INCLUDE                                   */
/*****************************************************************************/
#include "Std_Types.h"

/*****************************************************************************/
/*                                 MACROS                                    */
/*****************************************************************************/

#define ADC_NORMAL            ((uint8)0x00)
/* !comment: Analog module in power down mode*/
#define ADC_POWER_DOWN        ((uint8)0x01)

/* !comment: ADC Clock = MC_PLL_CLOCK (Motor Control Clock)*/
#define ADC_CLK_NORMAL_SYS    ((uint8)0x01)
/* !comment: ADC Clock = MC_PLL_CLOCK (Motor Control Clock) / 2 */
#define ADC_CLK_HALF_SYS      ((uint8)0x00)

/* !comment: Enables converted data to be overwritten by a new conversion*/
#define ADC_OVERWRITE_EN      ((uint8)0x01)
/* !comment: Enable cross triggering unit and the triggered injected conversion*/
#define ADC_CTU_TRIGGER_EN    ((uint8)0x01)
/* !comment: Enable cross triggering unit and the triggered injected conversion*/
#define ADC_CTU_TRIGGER_DIS   ((uint8)0x00)
/* !comment: T_Samp = (INPSAMP - 1) * tClk = (9-1) * 16.67 = 133.4ns*/
#define ADC_INPSAMP           ((uint8)0xFF)
/* !comment: T_Eval = 12 * INPCMP *tClk = 12 * 3 * 16.67  = 600ns*/
#define ADC_INPCMP            ((uint8)0x03)
/* !comment: T_Conv = T_Samp + T_Eval + T_Latch = 733.4ns*/
#define ADC_OFFSHIFT          ((uint8)0x00)
/* !comment: T_Latch= 1 * tClk = 16.67ns*/
#define ADC_INPLATCH          ((uint8)0x01)

/* !Comment: Defines used for MCR[WLSIDE] */
#define ADC_ALIGN_RIGHT       0
#define ADC_ALIGN_LEFT        1

/* !Comment: Defines used for MCR[MODE] */
#define ADC_CONV_MODE_ONESHOT      0
#define ADC_CONV_MODE_SCAN         1

/* !comment: channel num */
#define ADC_CH00_NUM     ((uint8)0)
#define ADC_CH01_NUM     ((uint8)1)
#define ADC_CH02_NUM     ((uint8)2)
#define ADC_CH03_NUM     ((uint8)3)
#define ADC_CH04_NUM     ((uint8)4)
#define ADC_CH05_NUM     ((uint8)5)
#define ADC_CH06_NUM     ((uint8)6)
#define ADC_CH07_NUM     ((uint8)7)
#define ADC_CH08_NUM     ((uint8)8)
#define ADC_CH09_NUM     ((uint8)9)
#define ADC_CH10_NUM     ((uint8)10)
#define ADC_CH11_NUM     ((uint8)11)
#define ADC_CH12_NUM     ((uint8)12)
#define ADC_CH13_NUM     ((uint8)13)
#define ADC_CH14_NUM     ((uint8)14)
#define ADC_CH15_NUM     ((uint8)15)

#define ADC_CH32_NUM     ((uint8)32)
#define ADC_CH33_NUM     ((uint8)33)
#define ADC_CH34_NUM     ((uint8)34)
#define ADC_CH35_NUM     ((uint8)35)
#define ADC_CH36_NUM     ((uint8)36)
#define ADC_CH37_NUM     ((uint8)37)
#define ADC_CH38_NUM     ((uint8)38)
#define ADC_CH39_NUM     ((uint8)39)
#define ADC_CH40_NUM     ((uint8)40)
#define ADC_CH41_NUM     ((uint8)41)
#define ADC_CH42_NUM     ((uint8)42)
#define ADC_CH43_NUM     ((uint8)43)
#define ADC_CH44_NUM     ((uint8)44)
#define ADC_CH45_NUM     ((uint8)45)
#define ADC_CH46_NUM     ((uint8)46)
#define ADC_CH47_NUM     ((uint8)47)

#define ADC_CH64_NUM     ((uint8)64)
#define ADC_CH65_NUM     ((uint8)65)
#define ADC_CH66_NUM     ((uint8)66)
#define ADC_CH67_NUM     ((uint8)67)
#define ADC_CH68_NUM     ((uint8)68)
#define ADC_CH69_NUM     ((uint8)69)
#define ADC_CH70_NUM     ((uint8)70)
#define ADC_CH71_NUM     ((uint8)71)
#define ADC_CH72_NUM     ((uint8)72)
#define ADC_CH73_NUM     ((uint8)73)
#define ADC_CH74_NUM     ((uint8)74)
#define ADC_CH75_NUM     ((uint8)75)
#define ADC_CH76_NUM     ((uint8)76)
#define ADC_CH77_NUM     ((uint8)77)
#define ADC_CH78_NUM     ((uint8)78)
#define ADC_CH79_NUM     ((uint8)79)

#define ADC_CH80_NUM     ((uint8)80)
#define ADC_CH81_NUM     ((uint8)81)
#define ADC_CH82_NUM     ((uint8)82)
#define ADC_CH83_NUM     ((uint8)83)
#define ADC_CH84_NUM     ((uint8)84)
#define ADC_CH85_NUM     ((uint8)85)
#define ADC_CH86_NUM     ((uint8)86)
#define ADC_CH87_NUM     ((uint8)87)
#define ADC_CH88_NUM     ((uint8)88)
#define ADC_CH89_NUM     ((uint8)89)
#define ADC_CH90_NUM     ((uint8)90)
#define ADC_CH91_NUM     ((uint8)91)
#define ADC_CH92_NUM     ((uint8)92)
#define ADC_CH93_NUM     ((uint8)93)
#define ADC_CH94_NUM     ((uint8)94)
#define ADC_CH95_NUM     ((uint8)95)

#define ADC_GPI00_NUM     ((uint8)0)
#define ADC_GPI01_NUM     ((uint8)1)
#define ADC_GPI02_NUM     ((uint8)2)
#define ADC_GPI03_NUM     ((uint8)3)
#define ADC_GPI04_NUM     ((uint8)4)
#define ADC_GPI05_NUM     ((uint8)5)
#define ADC_GPI06_NUM     ((uint8)6)
#define ADC_GPI07_NUM     ((uint8)7)
#define ADC_GPI08_NUM     ((uint8)8)
#define ADC_GPI09_NUM     ((uint8)9)
#define ADC_GPI10_NUM     ((uint8)10)
#define ADC_GPI11_NUM     ((uint8)11)
#define ADC_GPI12_NUM     ((uint8)12)
#define ADC_GPI13_NUM     ((uint8)13)
#define ADC_GPI14_NUM     ((uint8)14)
#define ADC_GPI15_NUM     ((uint8)15)

#define ADC_ANS00_NUM     ((uint8)32)
#define ADC_ANS01_NUM     ((uint8)33)
#define ADC_ANS02_NUM     ((uint8)34)
#define ADC_ANS03_NUM     ((uint8)35)
#define ADC_ANS04_NUM     ((uint8)36)
#define ADC_ANS05_NUM     ((uint8)37)
#define ADC_ANS06_NUM     ((uint8)38)
#define ADC_ANS07_NUM     ((uint8)39)
#define ADC_ANS08_NUM     ((uint8)40)
#define ADC_ANS09_NUM     ((uint8)41)
#define ADC_ANS10_NUM     ((uint8)42)
#define ADC_ANS11_NUM     ((uint8)43)
#define ADC_ANS12_NUM     ((uint8)44)
#define ADC_ANS13_NUM     ((uint8)45)
#define ADC_ANS14_NUM     ((uint8)46)
#define ADC_ANS15_NUM     ((uint8)47)




/* !comment: enable the channel xxxxx */
#define ADC_CH00_ENABLE     ((uint32)0x00000001)
#define ADC_CH01_ENABLE     ((uint32)0x00000002)
#define ADC_CH02_ENABLE     ((uint32)0x00000004)
#define ADC_CH03_ENABLE     ((uint32)0x00000008)
#define ADC_CH04_ENABLE     ((uint32)0x00000010)
#define ADC_CH05_ENABLE     ((uint32)0x00000020)
#define ADC_CH06_ENABLE     ((uint32)0x00000040)
#define ADC_CH07_ENABLE     ((uint32)0x00000080)
#define ADC_CH08_ENABLE     ((uint32)0x00000100)
#define ADC_CH09_ENABLE     ((uint32)0x00000200)
#define ADC_CH10_ENABLE     ((uint32)0x00000400)
#define ADC_CH11_ENABLE     ((uint32)0x00000800)
#define ADC_CH12_ENABLE     ((uint32)0x00001000)
#define ADC_CH13_ENABLE     ((uint32)0x00002000)
#define ADC_CH14_ENABLE     ((uint32)0x00004000)
#define ADC_CH15_ENABLE     ((uint32)0x00008000)

#define ADC_CH32_ENABLE     ((uint32)0x00000001)
#define ADC_CH33_ENABLE     ((uint32)0x00000002)
#define ADC_CH34_ENABLE     ((uint32)0x00000004)
#define ADC_CH35_ENABLE     ((uint32)0x00000008)
#define ADC_CH36_ENABLE     ((uint32)0x00000010)
#define ADC_CH37_ENABLE     ((uint32)0x00000020)
#define ADC_CH38_ENABLE     ((uint32)0x00000040)
#define ADC_CH39_ENABLE     ((uint32)0x00000080)
#define ADC_CH40_ENABLE     ((uint32)0x00000100)
#define ADC_CH41_ENABLE     ((uint32)0x00000200)
#define ADC_CH42_ENABLE     ((uint32)0x00000400)
#define ADC_CH43_ENABLE     ((uint32)0x00000800)
#define ADC_CH44_ENABLE     ((uint32)0x00001000)
#define ADC_CH45_ENABLE     ((uint32)0x00002000)
#define ADC_CH46_ENABLE     ((uint32)0x00004000)
#define ADC_CH47_ENABLE     ((uint32)0x00008000)

#define ADC_CH64_ENABLE     ((uint32)0x00000001)
#define ADC_CH65_ENABLE     ((uint32)0x00000002)
#define ADC_CH66_ENABLE     ((uint32)0x00000004)
#define ADC_CH67_ENABLE     ((uint32)0x00000008)
#define ADC_CH68_ENABLE     ((uint32)0x00000010)
#define ADC_CH69_ENABLE     ((uint32)0x00000020)
#define ADC_CH70_ENABLE     ((uint32)0x00000040)
#define ADC_CH71_ENABLE     ((uint32)0x00000080)
#define ADC_CH72_ENABLE     ((uint32)0x00000100)
#define ADC_CH73_ENABLE     ((uint32)0x00000200)
#define ADC_CH74_ENABLE     ((uint32)0x00000400)
#define ADC_CH75_ENABLE     ((uint32)0x00000800)
#define ADC_CH76_ENABLE     ((uint32)0x00001000)
#define ADC_CH77_ENABLE     ((uint32)0x00002000)
#define ADC_CH78_ENABLE     ((uint32)0x00004000)
#define ADC_CH79_ENABLE     ((uint32)0x00008000)

#define ADC_CH80_ENABLE     ((uint32)0x00010000)
#define ADC_CH81_ENABLE     ((uint32)0x00020000)
#define ADC_CH82_ENABLE     ((uint32)0x00040000)
#define ADC_CH83_ENABLE     ((uint32)0x00080000)
#define ADC_CH84_ENABLE     ((uint32)0x00100000)
#define ADC_CH85_ENABLE     ((uint32)0x00200000)
#define ADC_CH86_ENABLE     ((uint32)0x00400000)
#define ADC_CH87_ENABLE     ((uint32)0x00800000)
#define ADC_CH88_ENABLE     ((uint32)0x01000000)
#define ADC_CH89_ENABLE     ((uint32)0x02000000)
#define ADC_CH90_ENABLE     ((uint32)0x04000000)
#define ADC_CH91_ENABLE     ((uint32)0x08000000)
#define ADC_CH92_ENABLE     ((uint32)0x10000000)
#define ADC_CH93_ENABLE     ((uint32)0x20000000)
#define ADC_CH94_ENABLE     ((uint32)0x40000000)
#define ADC_CH95_ENABLE     ((uint32)0x80000000)

#define ADC_GPI00_ENABLE     ((uint32)0x00000001)
#define ADC_GPI01_ENABLE     ((uint32)0x00000002)
#define ADC_GPI02_ENABLE     ((uint32)0x00000004)
#define ADC_GPI03_ENABLE     ((uint32)0x00000008)
#define ADC_GPI04_ENABLE     ((uint32)0x00000010)
#define ADC_GPI05_ENABLE     ((uint32)0x00000020)
#define ADC_GPI06_ENABLE     ((uint32)0x00000040)
#define ADC_GPI07_ENABLE     ((uint32)0x00000080)
#define ADC_GPI08_ENABLE     ((uint32)0x00000100)
#define ADC_GPI09_ENABLE     ((uint32)0x00000200)
#define ADC_GPI10_ENABLE     ((uint32)0x00000400)
#define ADC_GPI11_ENABLE     ((uint32)0x00000800)
#define ADC_GPI12_ENABLE     ((uint32)0x00001000)
#define ADC_GPI13_ENABLE     ((uint32)0x00002000)
#define ADC_GPI14_ENABLE     ((uint32)0x00004000)
#define ADC_GPI15_ENABLE     ((uint32)0x00008000)

#define ADC_ANS00_ENABLE     ((uint32)0x00000001)
#define ADC_ANS01_ENABLE     ((uint32)0x00000002)
#define ADC_ANS02_ENABLE     ((uint32)0x00000004)
#define ADC_ANS03_ENABLE     ((uint32)0x00000008)
#define ADC_ANS04_ENABLE     ((uint32)0x00000010)
#define ADC_ANS05_ENABLE     ((uint32)0x00000020)
#define ADC_ANS06_ENABLE     ((uint32)0x00000040)
#define ADC_ANS07_ENABLE     ((uint32)0x00000080)
#define ADC_ANS08_ENABLE     ((uint32)0x00000100)
#define ADC_ANS09_ENABLE     ((uint32)0x00000200)
#define ADC_ANS10_ENABLE     ((uint32)0x00000400)
#define ADC_ANS11_ENABLE     ((uint32)0x00000800)
#define ADC_ANS12_ENABLE     ((uint32)0x00001000)
#define ADC_ANS13_ENABLE     ((uint32)0x00002000)
#define ADC_ANS14_ENABLE     ((uint32)0x00004000)
#define ADC_ANS15_ENABLE     ((uint32)0x00008000)

/*****************************************************************************/
/*                                 TYPES                                     */
/*****************************************************************************/

/*****************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/*****************************************************************************/

/* ***************************************************************************/
/*                                 PROTOTYPES                                */
/* ***************************************************************************/

#endif


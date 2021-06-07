

/* ***************************************************************************/

#ifndef MCU_CFG_H_
#define MCU_CFG_H_

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Std_Types.h"
#include "Mcu_Def.h"

/* ***************************************************************************/
/*                                 MACROS                                    */
/* ***************************************************************************/
/* !Comment : Flash operating mode : Low-power Mode                           */
#define MCU_ME_FLASH_ON                 ((uint8)0x03)
/* !Comment : Flash operating mode : Low-power Mode                           */
#define MCU_ME_FLASH_LPM                ((uint8)0x02)
/* !Comment : Flash operating mode : Power-down Mode                          */
#define MCU_ME_FLASH_OFF                ((uint8)0x01)
/* !Comment : Crystal oscillator On                                           */
#define MCU_ME_XOSCON_ON                ((uint8)0x01)
/* !Comment : Crystal oscillator Off                                          */
#define MCU_ME_XOSCON_OFF               ((uint8)0x00)
/* !Comment : Internal RC oscillator On                                       */
#define MCU_ME_IRCOSCON_ON              ((uint8)0x01)
/* !Comment : Internal RC oscillator Off                                      */
#define MCU_ME_IRCOSCON_OFF             ((uint8)0x00)
/* !Comment : System clock source                                             */
#define MCU_ME_SYSCLK_16MHZ_RC          ((uint8)0x00)
/* !Comment : Internal RC oscillator Off                                      */
#define MCU_ME_SYSCLK_SYSPLL            ((uint8)0x04)
/* !Comment : Secondary FMPLL On                                              */
#define MCU_ME_SECONDARY_FMPLL_ON       ((uint8)0x01)
/* !Comment : Secondary FMPLL Off                                             */
#define MCU_ME_SECONDARY_FMPLL_OFF      ((uint8)0x00)
/* !Comment : System FMPLL On                                                 */
#define MCU_ME_SYSTEM_FMPLL_ON          ((uint8)0x01)
/* !Comment : System FMPLL Off                                                */
#define MCU_ME_SYSTEM_FMPLL_OFF         ((uint8)0x00)
/* !Comment : MER Configuration                                                */
#define MCU_ME_MER_CONFIGURATION        ((uint32)0x000025FFU)

/* !comment: define CGM RC clock division */
#define MCU_CGM_RC_NO_DIV               ((uint32)0x00000000)
#define MCU_CGM_RC_DIV_2                ((uint32)0x00000002)
#define MCU_CGM_RC_DIV_4                ((uint32)0x00000004)
#define MCU_CGM_RC_DIV_8                ((uint32)0x00000006)

/* !comment: define CGM output clock  */
#define MCU_CGM_OUTCLK_NO_DIV           ((uint8)0x00)
#define MCU_CGM_OUTCLK_DIV_2            ((uint8)0x01)
#define MCU_CGM_OUTCLK_DIV_4            ((uint8)0x02)
#define MCU_CGM_OUTCLK_DIV_8            ((uint8)0x03)

#define MCU_CGM_OUTCLK_SRC_IRC          ((uint8)0x00)
#define MCU_CGM_OUTCLK_SRC_XOSC         ((uint8)0x01)
#define MCU_CGM_OUTCLK_SRC_FMPLL0       ((uint8)0x02)
#define MCU_CGM_OUTCLK_SRC_FMPLL1       ((uint8)0x03)

/* !comment: define Auxiliary Clock 0 */
#define MCU_CGM_AC0_SRC_IRC             ((uint8)0x00)
#define MCU_CGM_AC0_SRC_XOSC            ((uint8)0x02)
#define MCU_CGM_AC0_SRC_FMPLL0          ((uint8)0x04)
#define MCU_CGM_AC0_SRC_FMPLL1_120      ((uint8)0x05)
#define MCU_CGM_AC0_SRC_FMPLL1_80       ((uint8)0x08)
/* !comment: define Auxiliary Clock 0 DIVIDER */
#define MCU_CGM_AC0_DIV_DISABLE         ((uint8)0x00)
#define MCU_CGM_AC0_DIV_ENABLE          ((uint8)0x01)

#define MCU_CGM_AC0_NO_DIV              ((uint8)0x00)

/* !comment: define FMPLL DIVIDER */
#define MCU_CGM_PLL_DIV_IPF1            ((uint8)0x00)
#define MCU_CGM_PLL_DIV_IPF2            ((uint8)0x01)
#define MCU_CGM_PLL_DIV_ODF4            ((uint8)0x02)//0x02
#define MCU_CGM_PLL_DIV_NDIF64          ((uint8)0x40)

#define MCU_CGM_PLL_SW_EN               ((uint8)0x01)

#define MCU_CLK_OUT_DISABLE             ((uint8)0x00)
#define MCU_CLK_OUT_ENABLE              ((uint8)0x01)

/* ******** Definitions for CRGFLG **********/
/* !Comment : Mask configuration of the Real Time Interrupt Flag bit          */
#define  MCU_RTIF_CLEAR                 ((uint8)0x01)
/* !Comment : Mask configuration of the Power on Reset Flag bit               */
#define  MCU_PORF_CLEAR                 ((uint8)0x01)
/* !Comment : Mask configuration of the Low Voltage Reset Flag bit            */
#define  MCU_LVRF_CLEAR                 ((uint8)0x01)

/* !Comment : PCTL Ids                     */
#define    DSPI_0_ID                    ((uint8)4)
#define    DSPI_1_ID                    ((uint8)5)
#define    DSPI_2_ID                    ((uint8)6)
#define    FLEXCAN_0_ID                 ((uint8)16)
#define    FLEXCAN_1_ID                 ((uint8)17)
//#define    DMA_MUX_ID                   ((uint8)23)
//#define    FLEXRAY_ID                   ((uint8)24)
//#define    BAM_ID                       ((uint8)31)
#define    ADC_0_ID                     ((uint8)32)
//#define    ADC_1_ID                     ((uint8)33)

//#define    ETIMER_0_ID                  ((uint8)38)
//#define    ETIMER_1_ID                  ((uint8)39)
//#define    ETIMER_2_ID                  ((uint8)40)
//#define    FLEXPWM_0_ID                 ((uint8)41)
//#define    FLEXPWM_1_ID                 ((uint8)42)
#define    I2C_ID                       ((uint8)44)
#define    LINFLEXD_0_ID                ((uint8)48)
#define    LINFLEXD_1_ID                ((uint8)49)
#define    LINFLEXD_2_ID                ((uint8)50)
#define    CTU_ID                       ((uint8)57)
//#define    CRC_ID                       ((uint8)58)
//#define    FCCU_ID                      ((uint8)59)
#define    CAN_SAMPLE_ID                ((uint8)60)
//#define    SWG_ID                       ((uint8)62)
//#define    FLASH0_ID                    ((uint8)66)
#define    SIU_ID                       ((uint8)68)
#define    WKPU_ID                      ((uint8)69)
#define    EMIOS_0_ID                   ((uint8)72)
#define    EMIOS_1_ID                   ((uint8)73)

//#define    SSCM_ID                      ((uint8)86)
//#define    MC_ME_ID                     ((uint8)87)
//#define    MC_CGM_ID                    ((uint8)88)
//#define    MC_RGM_ID                    ((uint8)89)
//#define    MC_PCU_ID                    ((uint8)90)
#define    RTC_API_ID                   ((uint8)91)
#define    PIT_ID                       ((uint8)92)
//#define    STCU_ID                      ((uint8)93)
#define    CMU_ID                       ((uint8)104)


/* ***************************************************************************/
/*                                 TYPES                                     */
/* ***************************************************************************/
typedef struct
{
  uint8 u8PCTL_ID;
  uint8 u8DBG_F;
  uint8 u8LP_CFG;
  uint8 u8RUNPC_CFG;
} MCU_tstrPCTL_CFG;
/* ***************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/* ***************************************************************************/
extern const MCU_tstrPCTL_CFG MCU_Peripherals_Config [MCU_PCTL_MAX];
/* ***************************************************************************/
/*                                 PROTOTYPES                                */
/* ***************************************************************************/


#endif


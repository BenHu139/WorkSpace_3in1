
/* ***************************************************************************/

#ifndef PORT_DEF_H_
#define PORT_DEF_H_

/* ***************************************************************************/
/*                                 INCLUDE                                   */
/* ***************************************************************************/
#include "Std_Types.h"

/* ***************************************************************************/
/*                                 MACROS                                    */
/* ***************************************************************************/
#define MOCKUP_BOARD         0
#define PROTO_BOARD          1

/* !Comment: Pad direction*/
#define INPUT            0x0100
#define OUTPUT           0x0200
#define BIDIR            0x0300
#define EN_OUTPUT        0x4000

#define ADC_D            0x2000   //

#define EN_WEAKPULL_DOWN 0x0002 /* Enable Weak Pull by Default Pull Down*/
#define SELECT_PULL_UP   0x0001 /* Change Pull Down -> Pull Up when EN_WEAKPULL_DOWN*/
#define OPENDRAINOUT     0x0020

/* !Comment: Pad function*/
#define PCR_SMC     0x4000		/* PCRx SMC: safe mode control */
#define PCR_APC     0x2000		/* PCRx APC: Analog pad control */
#define GPIO        0x0000
#define INPUT_ONLY  0x0000
#define ALT0        0x0000
#define ALT1        0x0400
#define ALT2        0x0800
#define ALT3        0x0C00
#define PCR_ODE		0x0020		/* PCRx ODE: OPEN DRAIN OUTPUT ENABLE */
#define PCR_SRC		0x0004		/* PCRx SRC: SLEW RATE CONTROL */
#define PCR_WPE		0x0002		/* PCRx WPE: WEAK PULL UP/DOWN ENABLE */
#define PCR_WPU		0x0001		/* PCRx WPS: WEAK PULL UP SELECT */
#define PCR_WPD     0x0000      /* PCRx WPS: WEAK PULL DOWN SELECT */
#define CANTX       0x0600
#define CANRX       0x0100
#define IIC_SCL		0x0B23
#define IIC_SDA		0x0B23

/* !Comment: Pad sel*/
#define PADSEL_0    0
#define PADSEL_1    1
#define PADSEL_2    2
#define PADSEL_3    3

/* !Comment:  NB Max Register*/
#define PCR_MAX     79   /* 0-78 */
#define PSMI_MAX    32    /* 0-31 */
#define GPDO_MAX    79   /* 0-78 */
#define GPIO_MAX    79   /* 0-78 */
#define PGPDO_MAX   4     /* 0-3 */
#define MPGPDO_MAX  8     /* 0-7 */
#define IFMC_MAX    16    /* 0-15 */

/* !Comment: pad list Name versus PCR[ID]*/
#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7
#define PA8     8
#define PA9     9
#define PA10    10
#define PA11    11
#define PA12    12
#define PA13    13
#define PA14    14
#define PA15    15
#define PB0     16
#define PB1     17
#define PB2     18
#define PB3     19
#define PB4     20
#define PB5     21
#define PB6     22
#define PB7     23
#define PB8     24
#define PB9     25
#define PB10    26
#define PB11    27
#define PB12    28
#define PB13    29
#define PB14    30
#define PB15    31
#define PC0     32
#define PC1     33
#define PC2     34
#define PC3     35
#define PC4     36
#define PC5     37
#define PC6     38
#define PC7     39
#define PC8     40
#define PC9     41
#define PC10    42
#define PC11    43
#define PC12    44
#define PC13    45
#define PC14    46
#define PC15    47
#define PD0     48
#define PD1     49
#define PD2     50
#define PD3     51
#define PD4     52
#define PD5     53
#define PD6     54
#define PD7     55
#define PD8     56
#define PD9     57
#define PD10    58
#define PD11    59
#define PD12    60
#define PD13    61
#define PD14    62
#define PD15    63
#define PE0     64
#define PE1     65
#define PE2     66
#define PE3     67
#define PE4     68
#define PE5     69
#define PE6     70
#define PE7     71
#define PE8     72
#define PE9     73
#define PE10    74
#define PE11    75
#define PE12    76
#define PE13    77
#define PE14    78
#define PE15    79
#define PF0     80
#define PF1     81
#define PF2     82
#define PF3     83
#define PF4     84
#define PF5     85
#define PF6     86
#define PF7     87
#define PF8     88
#define PF9     89
#define PF10    90
#define PF11    91
#define PF12    92
#define PF13    93
#define PF14    94
#define PF15    95
#define PG0     96
#define PG1     97
#define PG2     98
#define PG3     99
#define PG4     100
#define PG5     101
#define PG6     102
#define PG7     103
#define PG8     104
#define PG9     105
#define PG10    106
#define PG11    107
#define PG12    108
#define PG13    109
#define PG14    110
#define PG15    111
#define PH0     112
#define PH1     113
#define PH2     114
#define PH3     115
#define PH4     116
#define PH5     117
#define PH6     118
#define PH7     119
#define PH8     120
#define PH9     121
#define PH10    122
#define PH11    123
#define PH12    124
#define PH13    125
#define PH14    126
#define PH15    127
#define PI0     128
#define PI1     129
#define PI2     130
#define PI3     131
#define PI4     132
#define PI5     133
#define PI6     134
#define PI7     135
#define PI8     136
#define PI9     137
#define PI10    138
#define PI11    139
#define PI12    140
#define PI13    141
#define PI14    142
#define PI15    143
#define PJ0     144
#define PJ1     145
#define PJ2     146
#define PJ3     147
#define PJ4     148


#define PORT_IF_ALL_CLEAR       ((u32)0xFFFFFFFF)

#define PORT_INT_ALL_DISABLE    ((u32)0x00000000)
#define PORT_INT_ENABLE         ((u32)0x00000001)

#define PORT_EDGE_EVENT_DISABLE ((u32)0x00000000)

#define PORT_FILTER_DISABLE     ((u32)0x00000000)

#define PROT_INT_FILTER_CLK_0   ((u32)0x00000000)

/* ***************************************************************************/
/*                                 TYPES                                     */
/* ***************************************************************************/

/* ***************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/* ***************************************************************************/


/* ***************************************************************************/
/*                                 PROTOTYPES                                */
/* ***************************************************************************/


#endif


/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_Cfg.h
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Can module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Can module configuration File
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   04.03.00    06/09/2016     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/
#ifndef _CAN_CFG_H_
#define _CAN_CFG_H_

#define CAN_DEV_ERROR_DETECT                 STD_OFF
#define CAN_HW_TRANSMIT_CANCELLATION         STD_OFF
#define CAN_IDENTICAL_ID_CANCELLATION        STD_OFF
#define CAN_MULTIPLEXED_TRANSMISSION         STD_OFF
#define CAN_TIMEOUT_DURATION                 ((uint16)100U)
#define CAN_VERSION_INFO_API                 STD_OFF
#define CAN_AUTOSET_INTERRUPT_PRIORITY       STD_OFF
#define CAN_ENABLE_EXTENDED_ID               STD_ON

#define CAN_MAIN_FUNCTION_BUS_OFF_PERIOD     (1U)
#define CAN_MAIN_FUNCTION_MODE_PERIOD        (1U)
#define CAN_MAIN_FUNCTION_READ_PERIOD        (1U)
#define CAN_MAIN_FUNCTION_WAKEUP_PERIOD      (1U)
#define CAN_MAIN_FUNCTION_WRITE_PERIOD       (1U)

#define CAN_VENDOR_ID_VALUE                  ((uint16)26)
#define CAN_MODULE_ID_VALUE                  ((uint16)80)
#define CAN_INSTANCE_ID_VALUE_0              ((uint8)0)

#define CAN_INTERRUPT                        (1U)
#define CAN_POLLING                          (0U)

#define CAN0_WAKEUP_SUPPORT                  STD_ON
#define CAN0_BUSOFF_AUTO_RECOVERY            STD_OFF

#define CAN_USED_CONTROLLER_NUM              (1U)

#define CAN0_BUSOFF_PROCESSING               CAN_INTERRUPT
#define CAN0_RX_PROCESSING                   CAN_INTERRUPT
#define CAN0_TX_PROCESSING                   CAN_INTERRUPT
#define CAN0_WAKEUP_PROCESSING               CAN_INTERRUPT

#define CAN0_CONTROLLER_ACTIVATION           STD_ON 
#define CAN0_CONTROLLER_BAUD_RATE            (250U)
#define CAN0_CONTROLLER_BASE_ADDRESS         ((uint32)0x6000UL)

#define CAN_PHY0_TO_LOGIC                    (0U)
#define CAN_PHY0_ACTIVATION                  CAN0_CONTROLLER_ACTIVATION 
#define CAN_PHY0_RX_PROCESSING               CAN0_RX_PROCESSING 
#define CAN_PHY0_TX_PROCESSING               CAN0_TX_PROCESSING 
#define CAN_PHY0_BUSOFF_PROCESSING           CAN0_BUSOFF_PROCESSING 
#define CAN_PHY0_WAKEUP_PROCESSING           CAN0_WAKEUP_PROCESSING 

#define CAN_PHY1_TO_LOGIC                    (0U)
#define CAN_PHY1_ACTIVATION                  STD_OFF 
#define CAN_PHY1_RX_PROCESSING               CAN_INTERRUPT 
#define CAN_PHY1_TX_PROCESSING               CAN_INTERRUPT 
#define CAN_PHY1_BUSOFF_PROCESSING           CAN_INTERRUPT 
#define CAN_PHY1_WAKEUP_PROCESSING           CAN_INTERRUPT 

#define CAN_TOTAL_MB_NUM                     (320U)
#define CAN_PER_CONTROLLER_MB_NUM            (64u)   /*wenxc add 20170427*/
#define CAN_USED_HOH_NUM                     (320U)

#define Can_DisableGlobalInterrupts()        //Can_DisableGlobalInterrupt()
#define Can_EnableGlobalInterrupts()         //Can_EnableGlobalInterrupt()
#define CAN_DATA_DLC   (8U)

extern void CAN_CFG_Init(void);

#endif  /* _CAN_CFG_H_ */ 

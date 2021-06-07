/**
 * @file VERSION.c 产品版本模块源文件
 * @ingroup FWS_VERSION 
 */
#include "includes.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "VERSION.h"

#define BIN2BCD(val) (((u8)((val) / 10u) << 4u) + (val) % 10u)
#define BCD2BIN(val) (((val)&0x0Fu) + ((val) >> 4u) * 10u)


/*************************************************************************/
/*软硬件版本号以十六进制进行编写，如版本16则写为0X16*/
static const u8 HardVerMajor = 0x01U;  /*硬件主版本号*/
static const u8 HardVerMinorH = 0x00U; /*硬件次版本号高字节*/
static u8 HardVerMinorL = 0x00U;       /*硬件次版本号低字节*/
static const u8 SoftVerMinor = 0x21U;  /* 软件次版本号*/
static const u8 SoftVerMajor = 0x00U;  /* 软件主版本号*/

static const u8 s_uds_sw_ver[16] = {(u8)'P', (u8)'C', (u8)'M', (u8)'2', (u8)'0', (u8)'1',
                                    (u8)'_', (u8)'V', (u8)'0', (u8)'.', (u8)'1',
                                    (u8)' 1', (u8)' ', (u8)' ', (u8)' ', (u8)' '};
/**************************************************************************/
static u8 s_sw_year = 20u; /*软件定型日期：年*/
static u8 s_sw_month = 5u; /*软件定型日期：月*/
static u8 s_sw_day = 15u;   /*软件定型日期：日*/


/**
 * 产品型号
 */
const u8 MajorProductModel = 0x01U; /*主版本 */
const u8 MinorProductModel = 0x02U; /*次版本 */

#if !PHEV
const u8 VehicleInfo = 0x01U; /*0001(纯电动)，0010(单电源插电式)，0011（复合电源插电式）*/
#else
const u8 VehicleInfo = 0x03U;       /*0001(纯电动)，0010(单电源插电式)，0011（复合电源插电式）*/
#endif

const u8 SourceAddress = 0xF4U; /*设备源地址：244*/


static u8 GetHardwareMinorVerL(void);

/**
 * 获取BMS配置版本信息
 * @ingroup APP_HCU_MGR
 * @param  type: -> 0.HardVerM_Index 硬件主版本号  \n
                    1.HardVerHigh_Index 硬件版本号高字节  \n
                    2.SoftVerS_Index 软件次版本号 \n
                    3.SoftVerM_Index 软件主版本号 \n
                    4.SoftVerDate_Index 软件定型日期 \n
                    5.VehicleInfo_Index 车辆信息  \n
                    6.SourceAddress_Index 设备源地址 \n
                    7.MajorProductModel_Index 产品型号主版本 \n
                    8.MinorProductModel_Index 产品型号次版本  \n
 * @return info：获取的相应的信息
 */
u16 FWS_GetVerInfo(u8 type)
{
   u16 info = 0U;
   u8 tmp = 0;
   switch (type)
   {
   case HardVerM_Index: /*硬件主版本号*/
   {
      info = HardVerMajor;
      break;
   }
   case HardVerMinorH_Index: /*硬件次版本号高字节*/
   {
      info = HardVerMinorH;
      break;
   }
   case HardVerMinorL_Index: /*硬件次版本号低字节*/
   {
      HardVerMinorL = GetHardwareMinorVerL();
      info = HardVerMinorL;
      break;
   }
   case SoftVerS_Index: /* 软件次版本号*/
   {
      info = SoftVerMinor;
      break;
   }
   case SoftVerM_Index: /* 软件主版本号*/
   {
      info = SoftVerMajor;
      break;
   }
   case SoftVerDate_Index: /* 软件定型日期，2015.4.9*/
   {
      tmp = (s_sw_year & 0X7Fu) | ((s_sw_day & 0x01u) << 7u);
      info = tmp;
      tmp = (s_sw_day >> 1u) & 0x0Fu;
      tmp = tmp | (s_sw_month << 4u);
      info = ((u16)tmp << 8u) | info;
      break;
   }
   case VehicleInfo_Index: /*车辆信息->0001(纯电动) 0010(油电混合)  0011（气电混合）*/
   {
      info = VehicleInfo;
      break;
   }
   case SourceAddress_Index: /*设备源地址：243*/
   {
      info = SourceAddress;
      break;
   }
   case MajorProductModel_Index: /*产品型号主版本*/
   {
      info = MajorProductModel;
      break;
   }
   case MinorProductModel_Index: /*产品型号次版本*/
   {
      info = MinorProductModel;
      break;
   }
   default:
   {
      break;
   }
   }
   return info;
}

/**
 * 计算硬件次版本低字节号
 * @ingroup APP_HCU_MGR
 * @return u8_version + 1U
 */
static u8 GetHardwareMinorVerL(void)
{
   u8 i = 0U;
   u8 u8_temp = 0U;
   u8 u8_version = 0U;

   for (i = 3U; i < 6U; i++)
   {
      //u8_temp = (u8)DIO_DIGet(i);
      u8_version = (u8)(((u16)u8_temp << (i - 3U)) + u8_version);
   }
   return u8_version + 1U;
}




/**
 * @ingroup FWS_EEPROM EEPROM
 * @brief 获取UDS需要相关信息：应用软件版本号
 * @param    info 数据     
 */
void FWS_VER_GetAppSWV(u8 info[])
{
   u8 loop = 0u;
   for (loop = 0u; loop < 16u; loop++)
   {
      info[loop] = s_uds_sw_ver[loop];
   }
   info[8] = (u8)(FWS_GetVerInfo(SoftVerM_Index) + 48u);                   /*软件主版本号转换为ASCII码*/
   info[10] = (u8)((BCD2BIN(FWS_GetVerInfo(SoftVerS_Index)) / 10u) + 48U); /*软件从版本高位*/
   info[11] = (u8)((BCD2BIN(FWS_GetVerInfo(SoftVerS_Index)) % 10u) + 48U); /*软件从版本低位*/
}

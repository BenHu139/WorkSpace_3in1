/**
 * @file VERSION.c ��Ʒ�汾ģ��Դ�ļ�
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
/*��Ӳ���汾����ʮ�����ƽ��б�д����汾16��дΪ0X16*/
static const u8 HardVerMajor = 0x01U;  /*Ӳ�����汾��*/
static const u8 HardVerMinorH = 0x00U; /*Ӳ���ΰ汾�Ÿ��ֽ�*/
static u8 HardVerMinorL = 0x00U;       /*Ӳ���ΰ汾�ŵ��ֽ�*/
static const u8 SoftVerMinor = 0x21U;  /* ����ΰ汾��*/
static const u8 SoftVerMajor = 0x00U;  /* ������汾��*/

static const u8 s_uds_sw_ver[16] = {(u8)'P', (u8)'C', (u8)'M', (u8)'2', (u8)'0', (u8)'1',
                                    (u8)'_', (u8)'V', (u8)'0', (u8)'.', (u8)'1',
                                    (u8)' 1', (u8)' ', (u8)' ', (u8)' ', (u8)' '};
/**************************************************************************/
static u8 s_sw_year = 20u; /*����������ڣ���*/
static u8 s_sw_month = 5u; /*����������ڣ���*/
static u8 s_sw_day = 15u;   /*����������ڣ���*/


/**
 * ��Ʒ�ͺ�
 */
const u8 MajorProductModel = 0x01U; /*���汾 */
const u8 MinorProductModel = 0x02U; /*�ΰ汾 */

#if !PHEV
const u8 VehicleInfo = 0x01U; /*0001(���綯)��0010(����Դ���ʽ)��0011�����ϵ�Դ���ʽ��*/
#else
const u8 VehicleInfo = 0x03U;       /*0001(���綯)��0010(����Դ���ʽ)��0011�����ϵ�Դ���ʽ��*/
#endif

const u8 SourceAddress = 0xF4U; /*�豸Դ��ַ��244*/


static u8 GetHardwareMinorVerL(void);

/**
 * ��ȡBMS���ð汾��Ϣ
 * @ingroup APP_HCU_MGR
 * @param  type: -> 0.HardVerM_Index Ӳ�����汾��  \n
                    1.HardVerHigh_Index Ӳ���汾�Ÿ��ֽ�  \n
                    2.SoftVerS_Index ����ΰ汾�� \n
                    3.SoftVerM_Index ������汾�� \n
                    4.SoftVerDate_Index ����������� \n
                    5.VehicleInfo_Index ������Ϣ  \n
                    6.SourceAddress_Index �豸Դ��ַ \n
                    7.MajorProductModel_Index ��Ʒ�ͺ����汾 \n
                    8.MinorProductModel_Index ��Ʒ�ͺŴΰ汾  \n
 * @return info����ȡ����Ӧ����Ϣ
 */
u16 FWS_GetVerInfo(u8 type)
{
   u16 info = 0U;
   u8 tmp = 0;
   switch (type)
   {
   case HardVerM_Index: /*Ӳ�����汾��*/
   {
      info = HardVerMajor;
      break;
   }
   case HardVerMinorH_Index: /*Ӳ���ΰ汾�Ÿ��ֽ�*/
   {
      info = HardVerMinorH;
      break;
   }
   case HardVerMinorL_Index: /*Ӳ���ΰ汾�ŵ��ֽ�*/
   {
      HardVerMinorL = GetHardwareMinorVerL();
      info = HardVerMinorL;
      break;
   }
   case SoftVerS_Index: /* ����ΰ汾��*/
   {
      info = SoftVerMinor;
      break;
   }
   case SoftVerM_Index: /* ������汾��*/
   {
      info = SoftVerMajor;
      break;
   }
   case SoftVerDate_Index: /* ����������ڣ�2015.4.9*/
   {
      tmp = (s_sw_year & 0X7Fu) | ((s_sw_day & 0x01u) << 7u);
      info = tmp;
      tmp = (s_sw_day >> 1u) & 0x0Fu;
      tmp = tmp | (s_sw_month << 4u);
      info = ((u16)tmp << 8u) | info;
      break;
   }
   case VehicleInfo_Index: /*������Ϣ->0001(���綯) 0010(�͵���)  0011�������ϣ�*/
   {
      info = VehicleInfo;
      break;
   }
   case SourceAddress_Index: /*�豸Դ��ַ��243*/
   {
      info = SourceAddress;
      break;
   }
   case MajorProductModel_Index: /*��Ʒ�ͺ����汾*/
   {
      info = MajorProductModel;
      break;
   }
   case MinorProductModel_Index: /*��Ʒ�ͺŴΰ汾*/
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
 * ����Ӳ���ΰ汾���ֽں�
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
 * @brief ��ȡUDS��Ҫ�����Ϣ��Ӧ������汾��
 * @param    info ����     
 */
void FWS_VER_GetAppSWV(u8 info[])
{
   u8 loop = 0u;
   for (loop = 0u; loop < 16u; loop++)
   {
      info[loop] = s_uds_sw_ver[loop];
   }
   info[8] = (u8)(FWS_GetVerInfo(SoftVerM_Index) + 48u);                   /*������汾��ת��ΪASCII��*/
   info[10] = (u8)((BCD2BIN(FWS_GetVerInfo(SoftVerS_Index)) / 10u) + 48U); /*����Ӱ汾��λ*/
   info[11] = (u8)((BCD2BIN(FWS_GetVerInfo(SoftVerS_Index)) % 10u) + 48U); /*����Ӱ汾��λ*/
}

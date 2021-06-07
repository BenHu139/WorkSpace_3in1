/**
 * @file VERSION.h 产品版本模块头文件
 * @ingroup FWS_VERSION 
 */

#ifndef VERSION_H__
#define VERSION_H__



/*user define*/
//************************************************************************************************

//************************************************************************************************
#define WuLingIpsType 		0x09U /*IPS型号,0x0：2kwOBC 
								0x1：3.3kwOBC 
								0x2：6.6kwOBC 
								0x3：2kwOBC+1.5kwDC/DC 
								0x4：6.6kwOBC+1.5kwDC/DC 
								0x5：6.6kwOBC+1.5kwDC/DC+2kwDC/AC 
								0x6：6.6kwOBC+1.5kwDC/DC+PDU 
								0x7：6.6kwOBC+2kwDC/DC+PDU 
								0x8：6.6kwOBC+1.5kwDC/DC+2kwDC/AC+ PDU 
								0x9：1.5kwOBC+0.8kwDC/DC++PDU 
								0xA：2kwOBC+1kwDC/DC++PDU*/
#define WuLingSupCode		0x03U /*供应商代码0x0：杭州铁城 
										0x1：重庆力华 
										0x2：珠海英搏尔 
										0x3：保留*/

enum  _ConfigInfo_/*配置信息索引*/
{
   HardVerM_Index = 0U,
   HardVerMinorH_Index,
   HardVerMinorL_Index,
   SoftVerS_Index,
   SoftVerM_Index,
   SoftVerDate_Index,
   VehicleInfo_Index,
   SourceAddress_Index,
   MajorProductModel_Index,
   MinorProductModel_Index
};

typedef struct
{
    u16 product_id; /*产品代号*/
    u8 fuel_type;   /*燃料类型*/
    u8 purpose;     /*用途*/
    u8 sp_function; /*特殊功能*/
    u8 derivate;    /*衍生版本*/
} DEV_INFO;

extern const DEV_INFO DEVICE_INFO;

extern u16 FWS_GetVerInfo(u8 type);
extern void FWS_VER_GetAppSWV(u8 info[]);

#endif /* __VERSION_H__ */

/*
 * JYD_CRC16.h
 *
 *  Created on: Aug 31, 2016
 *      Author: wenxc
 */

#ifndef JYD_CRC16_H_
#define JYD_CRC16_H_

extern u8 JYD_data_crc16(u8 lenth, u8 *pdata, u8 mode);
extern u16 JYD_data_crc16_follow(u8 *pdata, u32 lenth, u16 last_result);
extern u8 JYD_CalSumCheckFollow(u8 *pdata, u32 lenth, u8 last_result);

#endif /* JYD_CRC16_H_ */

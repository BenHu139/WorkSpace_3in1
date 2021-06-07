/*
 * @Author: your name
 * @Date: 2020-04-03 10:31:41
 * @LastEditTime: 2020-04-03 14:40:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \PLF5604\Sources\FWS\BUS_OFF\CanSM_Cfg.c
 */
#include "CanSM.h"

CanSM_NetConfigType CanSM_NetConfig[6] =
    {
        /*CAN0*/
        {
            /* 快速恢复时间 */
            5,
            /* 慢速恢复时间 */
            200,
            /* 从快速恢复进入到慢速busoff计数界限值 */
            5,
            /* 进行产品报错的busoff计数界限值 */
            15,
            /* Can硬件复位超时 */
            15,
            /* CanSMBorTimeTxEnsured */
            200},
        /*CAN1*/
        {
            /* 快速恢复时间 */
            5,
            /* 慢速恢复时间 */
            200,
            /* 从快速恢复进入到慢速busoff计数界限值 */
            5,
            /* 进行产品报错的busoff计数界限值 */
            15,
            /* Can硬件复位超时 */
            15,
            /* CanSMBorTimeTxEnsured */
            200},
        /*CAN2*/
        {
            /* 快速恢复时间 */
            5,
            /* 慢速恢复时间 */
            200,
            /* 从快速恢复进入到慢速busoff计数界限值 */
            5,
            /* 进行产品报错的busoff计数界限值 */
            15,
            /* Can硬件复位超时 */
            15,
            /* CanSMBorTimeSTxEnsured */
            200},
        /*CAN3*/
        {
            /* 快速恢复时间 */
            5,
            /* 慢速恢复时间 */
            200,
            /* 从快速恢复进入到慢速busoff计数界限值 */
            5,
            /* 进行产品报错的busoff计数界限值 */
            15,
            /* Can硬件复位超时 */
            15,
            /* CanSMBorTimeTxEnsured */
            200},
        /*CAN4*/
        {
            /* 快速恢复时间 */
            5,
            /* 慢速恢复时间 */
            200,
            /* 从快速恢复进入到慢速busoff计数界限值 */
            5,
            /* 进行产品报错的busoff计数界限值 */
            15,
            /* Can硬件复位超时 */
            15,
            /* CanSMBorTimeTxEnsured  */
            200},

        /*CAN5*/
        {
            /* 快速恢复时间 */
            5,
            /* 慢速恢复时间 */
            200,
            /* 从快速恢复进入到慢速busoff计数界限值 */
            5,
            /* 进行产品报错的busoff计数界限值 */
            15,
            /* Can硬件复位超时 */
            15,
            /* CanSMBorTimeTxEnsured */
            200}};

CanSM_ConfigType CanSM_Config =
    {
        CANSM_STATUS_INIT,
        &CanSM_NetConfig[0]};

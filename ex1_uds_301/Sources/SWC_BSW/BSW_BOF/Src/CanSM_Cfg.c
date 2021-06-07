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
            /* ���ٻָ�ʱ�� */
            5,
            /* ���ٻָ�ʱ�� */
            200,
            /* �ӿ��ٻָ����뵽����busoff��������ֵ */
            5,
            /* ���в�Ʒ�����busoff��������ֵ */
            15,
            /* CanӲ����λ��ʱ */
            15,
            /* CanSMBorTimeTxEnsured */
            200},
        /*CAN1*/
        {
            /* ���ٻָ�ʱ�� */
            5,
            /* ���ٻָ�ʱ�� */
            200,
            /* �ӿ��ٻָ����뵽����busoff��������ֵ */
            5,
            /* ���в�Ʒ�����busoff��������ֵ */
            15,
            /* CanӲ����λ��ʱ */
            15,
            /* CanSMBorTimeTxEnsured */
            200},
        /*CAN2*/
        {
            /* ���ٻָ�ʱ�� */
            5,
            /* ���ٻָ�ʱ�� */
            200,
            /* �ӿ��ٻָ����뵽����busoff��������ֵ */
            5,
            /* ���в�Ʒ�����busoff��������ֵ */
            15,
            /* CanӲ����λ��ʱ */
            15,
            /* CanSMBorTimeSTxEnsured */
            200},
        /*CAN3*/
        {
            /* ���ٻָ�ʱ�� */
            5,
            /* ���ٻָ�ʱ�� */
            200,
            /* �ӿ��ٻָ����뵽����busoff��������ֵ */
            5,
            /* ���в�Ʒ�����busoff��������ֵ */
            15,
            /* CanӲ����λ��ʱ */
            15,
            /* CanSMBorTimeTxEnsured */
            200},
        /*CAN4*/
        {
            /* ���ٻָ�ʱ�� */
            5,
            /* ���ٻָ�ʱ�� */
            200,
            /* �ӿ��ٻָ����뵽����busoff��������ֵ */
            5,
            /* ���в�Ʒ�����busoff��������ֵ */
            15,
            /* CanӲ����λ��ʱ */
            15,
            /* CanSMBorTimeTxEnsured  */
            200},

        /*CAN5*/
        {
            /* ���ٻָ�ʱ�� */
            5,
            /* ���ٻָ�ʱ�� */
            200,
            /* �ӿ��ٻָ����뵽����busoff��������ֵ */
            5,
            /* ���в�Ʒ�����busoff��������ֵ */
            15,
            /* CanӲ����λ��ʱ */
            15,
            /* CanSMBorTimeTxEnsured */
            200}};

CanSM_ConfigType CanSM_Config =
    {
        CANSM_STATUS_INIT,
        &CanSM_NetConfig[0]};

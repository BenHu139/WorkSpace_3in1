/**
 * @file CAN_STACK.c CANջģ��Դ�ļ�
 * @ingroup FWS_FWS_CAN_STACK
 */

#include "includes.h"

#include "App_Boot.h"
#include "CAN.h"
#include "CAN_STACK.h"
#include "CanSM.h"
#include "Dcm.h"
#include "Dcm_Types.h"
#include "debug_only.h"

#define SENDMONUM 			12u 	/*���ͱ��Ļ�����CAN�����*/
#define SENDMONUM1          (SENDMONUM + 1u)

/****************************************************************************/
static S_CAN_FIFO s_can_rx_fifo_manager[CAN_FIFO_MAX_CHN];
static S_CAN_FIFO s_can_tx_fifo_manager[CAN_FIFO_MAX_CHN];

static u8 s_can_tx_state[CAN_FIFO_MAX_CHN];

static u8 s_u8_global_com_en = 1u;

/****************************************************************************/

static bool FWS_CAN_STACK_PutTxMsg(CAN_CHANNEL chn, STRU_CAN_MESSAGE *msg);
static bool FWS_CAN_STACK_GetTxMsg(CAN_CHANNEL chn, STRU_CAN_MESSAGE *msg);
static void SetCanChnRxTxBuffer(u8 chn);

/****************************************************************************/

/**
 * ��ʼ��CAN���յ�fifo������
 * @ingroup   FWS_CAN_STACK
 * @return void  ��
 */
void FWS_CAN_STACK_Init(void)
{
    u8 i = 0u;
    u32 j = 0u;

    s_u8_global_com_en = 1u;
    //for (i = 0; i < CAN_FIFO_MAX_CHN; i++)  
    for (i = 0; i < CAN_FIFO_MAX_CHN - 1; i++) // Ŀǰֻʹ��CAN0
    {
        s_can_rx_fifo_manager[i].head = 0;
        s_can_rx_fifo_manager[i].tail = 0;

        s_can_tx_fifo_manager[i].head = 0;
        s_can_tx_fifo_manager[i].tail = 0;

        s_can_tx_state[i] = CAN_IDLE;

        for (j = 0; j < CAN_FIFO_BUF_MAX_SIZE; j++)
        {
            s_can_rx_fifo_manager[i].buffer[j].id = 0u;
            s_can_rx_fifo_manager[i].buffer[j].len = 0u;
            s_can_rx_fifo_manager[i].buffer[j].ide = 0u;
            s_can_rx_fifo_manager[i].buffer[j].rtr = 0u;
            s_can_rx_fifo_manager[i].buffer[j].buf[0] = 0u;
            s_can_rx_fifo_manager[i].buffer[j].buf[1] = 0u;
            s_can_rx_fifo_manager[i].buffer[j].buf[2] = 0u;
            s_can_rx_fifo_manager[i].buffer[j].buf[3] = 0u;
            s_can_rx_fifo_manager[i].buffer[j].buf[4] = 0u;
            s_can_rx_fifo_manager[i].buffer[j].buf[5] = 0u;
            s_can_rx_fifo_manager[i].buffer[j].buf[6] = 0u;
            s_can_rx_fifo_manager[i].buffer[j].buf[7] = 0u;

            s_can_tx_fifo_manager[i].buffer[j].id = 0u;
            s_can_tx_fifo_manager[i].buffer[j].len = 0u;
            s_can_tx_fifo_manager[i].buffer[j].ide = 0u;
            s_can_tx_fifo_manager[i].buffer[j].rtr = 0u;
            s_can_tx_fifo_manager[i].buffer[j].buf[0] = 0u;
            s_can_tx_fifo_manager[i].buffer[j].buf[1] = 0u;
            s_can_tx_fifo_manager[i].buffer[j].buf[2] = 0u;
            s_can_tx_fifo_manager[i].buffer[j].buf[3] = 0u;
            s_can_tx_fifo_manager[i].buffer[j].buf[4] = 0u;
            s_can_tx_fifo_manager[i].buffer[j].buf[5] = 0u;
            s_can_tx_fifo_manager[i].buffer[j].buf[6] = 0u;
            s_can_tx_fifo_manager[i].buffer[j].buf[7] = 0u;
        }

        SetCanChnRxTxBuffer(i);
    }
}

/**
 * ��CAN���ķ�����ն�����,���ж������
 * @ingroup   FWS_CAN_STACK
 * @param chn  CANͨ����
 * @param msg  ���Ĳ���
 * @return  TRUE �ɹ�    FALSE ʧ��
 */
bool FWS_CAN_STACK_PutRxMsg(u8 chn, STRU_CAN_MESSAGE *msg)
{
    STRU_CAN_MESSAGE *fifo_buf = DEF_NULL;
    S_CAN_FIFO *fifo_handle = DEF_NULL;
    int32_t temp_w = 0;
    bool ret = FALSE;

    if (chn < CAN_FIFO_MAX_CHN)
    {

        fifo_handle = &s_can_rx_fifo_manager[chn];

        temp_w = fifo_handle->tail; /*�Ƚ��ȳ������������β*/
        temp_w++;
        if (temp_w >= CAN_FIFO_BUF_MAX_SIZE)
        {
            temp_w = 0;
        }

        if (temp_w != fifo_handle->head) /*дָ��Ͷ�ָ����ȣ��������Ĳ�д*/
        {
            fifo_buf = &(fifo_handle->buffer[fifo_handle->tail]);
            if (DEF_NULL != fifo_buf)
            {
                fifo_buf->id = msg->id;
                fifo_buf->len = msg->len;
                fifo_buf->ide = msg->ide;
                fifo_buf->rtr = msg->rtr;
                fifo_buf->buf[0] = msg->buf[0];
                fifo_buf->buf[1] = msg->buf[1];
                fifo_buf->buf[2] = msg->buf[2];
                fifo_buf->buf[3] = msg->buf[3];
                fifo_buf->buf[4] = msg->buf[4];
                fifo_buf->buf[5] = msg->buf[5];
                fifo_buf->buf[6] = msg->buf[6];
                fifo_buf->buf[7] = msg->buf[7];

                fifo_handle->tail = temp_w;

                ret = TRUE;
            }
            else
            {
                ret = FALSE;
            }
        }
        else
        {
            ret = FALSE;
        }
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

/**
 * �ӽ��ն����ж�ȡһ��CAN����
 * @ingroup   FWS_CAN_STACK
 * @param chn  CANͨ����
 * @param msg   ���Ĳ���
 * @return TRUE �ɹ�     FALSE  ʧ��
 */
bool FWS_CAN_STACK_GetRxMsg(u8 chn, STRU_CAN_MESSAGE *msg)
{
    STRU_CAN_MESSAGE *fifo_buf;
    S_CAN_FIFO *fifo_handle;
    int32_t temp_r = 0;
    bool ret = FALSE;

    if (chn < CAN_FIFO_MAX_CHN)
    {
        fifo_handle = &s_can_rx_fifo_manager[chn];

        temp_r = fifo_handle->head; /*�Ƚ��ȳ����ȶ�����ͷ*/

        if (temp_r != fifo_handle->tail) /*�Ƚ��ȳ���ͷβ��ȣ������ޱ����账��*/
        {
            fifo_buf = &(fifo_handle->buffer[temp_r]);
            if (fifo_buf != DEF_NULL)
            {
                msg->id = fifo_buf->id;
                msg->len = fifo_buf->len;
                msg->ide = fifo_buf->ide;
                msg->rtr = fifo_buf->rtr;
                msg->buf[0] = fifo_buf->buf[0];
                msg->buf[1] = fifo_buf->buf[1];
                msg->buf[2] = fifo_buf->buf[2];
                msg->buf[3] = fifo_buf->buf[3];
                msg->buf[4] = fifo_buf->buf[4];
                msg->buf[5] = fifo_buf->buf[5];
                msg->buf[6] = fifo_buf->buf[6];
                msg->buf[7] = fifo_buf->buf[7];

                temp_r++;
                if (temp_r >= CAN_FIFO_BUF_MAX_SIZE)
                {
                    temp_r = 0;
                }

                fifo_handle->head = temp_r;

                ret = TRUE;
            }
            else
            {
                ret = FALSE;
            }
        }
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

/**
 * ��CAN���ķ��뷢�Ͷ�����
 * @ingroup   FWS_CAN_STACK
 * @param chn  CANͨ����
 * @param msg  ���Ĳ���
 * @return  TRUE �ɹ�    FALSE ʧ��
 */
static bool FWS_CAN_STACK_PutTxMsg(CAN_CHANNEL chn, STRU_CAN_MESSAGE *msg)
{
    STRU_CAN_MESSAGE *fifo_buf = DEF_NULL;
    S_CAN_FIFO *fifo_handle = DEF_NULL;
    int32_t temp_w = 0;
    bool ret = FALSE;

    STRU_CAN_MESSAGE fifomsg;
    Can_PduType_SELF txmsg;

    u8 i = 0u;

    if (chn < CAN_FIFO_MAX_CHN)
    {
        fifo_handle = &s_can_tx_fifo_manager[chn];

        temp_w = fifo_handle->tail; /*�Ƚ��ȳ������������β*/
        temp_w++;
        if (temp_w >= CAN_FIFO_BUF_MAX_SIZE)
        {
            temp_w = 0;
        }

        if (temp_w != fifo_handle->head) /*дָ��Ͷ�ָ����ȣ��������Ĳ�д*/
        {
            fifo_buf = &(fifo_handle->buffer[fifo_handle->tail]);
            if (DEF_NULL != fifo_buf)
            {
                fifo_buf->id = msg->id;
                fifo_buf->len = msg->len;
                fifo_buf->ide = msg->ide;
                fifo_buf->rtr = msg->rtr;
                fifo_buf->buf[0] = msg->buf[0];
                fifo_buf->buf[1] = msg->buf[1];
                fifo_buf->buf[2] = msg->buf[2];
                fifo_buf->buf[3] = msg->buf[3];
                fifo_buf->buf[4] = msg->buf[4];
                fifo_buf->buf[5] = msg->buf[5];
                fifo_buf->buf[6] = msg->buf[6];
                fifo_buf->buf[7] = msg->buf[7];

                fifo_handle->tail = temp_w;

                ret = TRUE;
            }
            else
            {
                ret = FALSE;
            }
        }
        else
        {
            ret = FALSE;
        }
    }
    else
    {
        ret = FALSE;
    }

    if (CAN_IDLE == s_can_tx_state[chn]) /*�����������У�֮���жϼ�����ɷ��Ͷ���*/
    {
        if (TRUE == FWS_CAN_STACK_GetTxMsg(chn, &fifomsg))
        {
            s_can_tx_state[chn] = CAN_BUSY_SELF;

            txmsg.IDE = fifomsg.ide;
            txmsg.MB_NUM = SENDMONUM;
            txmsg.RTR = fifomsg.rtr;
            txmsg.CANID = fifomsg.id;
            txmsg.LENGTH = fifomsg.len;
            for (i = 0u; i < fifomsg.len; i++)
            {
                txmsg.DATA[i] = fifomsg.buf[i];
            }
            (void)Can_Write_Self(chn, &txmsg);
        }
    }

    return ret;
}

/**
 * �ӷ��Ͷ����ж�ȡһ��CAN����
 * @ingroup   FWS_CAN_STACK
 * @param chn  CANͨ����
 * @param msg   ���Ĳ���
 * @return TRUE �ɹ�     FALSE  ʧ��
 */
static bool FWS_CAN_STACK_GetTxMsg(CAN_CHANNEL chn, STRU_CAN_MESSAGE *msg)
{
    STRU_CAN_MESSAGE *fifo_buf;
    S_CAN_FIFO *fifo_handle;
    int32_t temp_r = 0;
    bool ret = FALSE;

    if (chn < CAN_FIFO_MAX_CHN)
    {
        fifo_handle = &s_can_tx_fifo_manager[chn];

        temp_r = fifo_handle->head; /*�Ƚ��ȳ����ȶ�����ͷ*/

        if (temp_r != fifo_handle->tail) /*�Ƚ��ȳ���ͷβ��ȣ������ޱ����账��*/
        {
            fifo_buf = &(fifo_handle->buffer[temp_r]);
            if (fifo_buf != DEF_NULL)
            {
                msg->id = fifo_buf->id;
                msg->len = fifo_buf->len;
                msg->ide = fifo_buf->ide;
                msg->rtr = fifo_buf->rtr;
                msg->buf[0] = fifo_buf->buf[0];
                msg->buf[1] = fifo_buf->buf[1];
                msg->buf[2] = fifo_buf->buf[2];
                msg->buf[3] = fifo_buf->buf[3];
                msg->buf[4] = fifo_buf->buf[4];
                msg->buf[5] = fifo_buf->buf[5];
                msg->buf[6] = fifo_buf->buf[6];
                msg->buf[7] = fifo_buf->buf[7];

                temp_r++;
                if (temp_r >= CAN_FIFO_BUF_MAX_SIZE)
                {
                    temp_r = 0;
                }

                fifo_handle->head = temp_r;

                ret = TRUE;
            }
            else
            {
                ret = FALSE;
            }
        }
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

/**
 * ���͵�֡����
 * @ingroup FWS_CAN_STACK
 * @param chn
 * @param msg
 * @return void  ��
 */
void FWS_CAN_STACK_SendMessage(u8 chn, STRU_CAN_MESSAGE *msg)
{
    CanSM_ComStatuType result = CANSM_BSM_S_UFULLCOM;

    CanSM_GetComState(chn, &result);

    if (CANSM_BSM_S_FULLCOM == result)
    {
        if (1u == s_u8_global_com_en)
        {
            (void)FWS_CAN_STACK_PutTxMsg(chn, msg);
        }
    }
}

/**
 * ��ձ��Ļ����ջ
 * @ingroup   FWS_CAN_STACK
 * @param chn  CANͨ����
 * @return  void
 */
void FWS_CAN_STACK_ClearMsg(u8 chn)
{
    S_CAN_FIFO *fifo_handle = DEF_NULL;
    if (chn < CAN_FIFO_MAX_CHN)
    {
        fifo_handle = &s_can_rx_fifo_manager[chn];
        fifo_handle->tail = fifo_handle->head;
    }
}

/**
 * �����жϻص�����
 * @ingroup   FWS_CAN_STACK
 * @param chn  CANͨ����
 * @return  void
 */
void FWS_CAN_STACK_CallBackTx(u8 chn)
{
    STRU_CAN_MESSAGE fifomsg;
    Can_PduType_SELF txmsg;

    u8 i = 0u;

    if ((CAN_BUSY_SELF == s_can_tx_state[chn]) && (chn < CAN_FIFO_MAX_CHN)) /*��������ֱ������Ϊ��*/
    {
        if (TRUE == FWS_CAN_STACK_GetTxMsg(chn, &fifomsg))
        {
            txmsg.IDE = fifomsg.ide;
            txmsg.MB_NUM = SENDMONUM;
            txmsg.RTR = fifomsg.rtr;
            txmsg.CANID = fifomsg.id;
            txmsg.LENGTH = fifomsg.len;
            for (i = 0u; i < fifomsg.len; i++)
            {
                txmsg.DATA[i] = fifomsg.buf[i];
            }
            (void)Can_Write_Self(chn, &txmsg);
        }
        else
        {
            s_can_tx_state[chn] = CAN_IDLE;
        }
    }
}

/**
 * ѡ��Ҫ��ʼ��CAN���շ��͵�fifo������
 * @ingroup   FWS_CAN_STACK
 * @param stack_start ��ʼ��CANջ
 * @param stack_end  ��ֹ��CANջ
 * @return void  ��
 */
bool FWS_CAN_STACK_InitSel(u8 stack_start, u8 stack_end)
{
    u8 i = 0u;
    u32 j = 0u;
    bool result = TRUE;
    if (stack_end < stack_start)
    {
        result = FALSE;
    }
    else
    {
        result = TRUE;
        for (i = stack_start; i <= stack_end; i++)
        {
            s_can_rx_fifo_manager[i].head = 0;
            s_can_rx_fifo_manager[i].tail = 0;

            s_can_tx_fifo_manager[i].head = 0;
            s_can_tx_fifo_manager[i].tail = 0;

            s_can_tx_state[i] = CAN_IDLE;

            for (j = 0; j < CAN_FIFO_BUF_MAX_SIZE; j++)
            {
                s_can_rx_fifo_manager[i].buffer[j].id = 0u;
                s_can_rx_fifo_manager[i].buffer[j].len = 0u;
                s_can_rx_fifo_manager[i].buffer[j].ide = 0u;
                s_can_rx_fifo_manager[i].buffer[j].rtr = 0u;
                s_can_rx_fifo_manager[i].buffer[j].buf[0] = 0u;
                s_can_rx_fifo_manager[i].buffer[j].buf[1] = 0u;
                s_can_rx_fifo_manager[i].buffer[j].buf[2] = 0u;
                s_can_rx_fifo_manager[i].buffer[j].buf[3] = 0u;
                s_can_rx_fifo_manager[i].buffer[j].buf[4] = 0u;
                s_can_rx_fifo_manager[i].buffer[j].buf[5] = 0u;
                s_can_rx_fifo_manager[i].buffer[j].buf[6] = 0u;
                s_can_rx_fifo_manager[i].buffer[j].buf[7] = 0u;

                s_can_tx_fifo_manager[i].buffer[j].id = 0u;
                s_can_tx_fifo_manager[i].buffer[j].len = 0u;
                s_can_tx_fifo_manager[i].buffer[j].ide = 0u;
                s_can_tx_fifo_manager[i].buffer[j].rtr = 0u;
                s_can_tx_fifo_manager[i].buffer[j].buf[0] = 0u;
                s_can_tx_fifo_manager[i].buffer[j].buf[1] = 0u;
                s_can_tx_fifo_manager[i].buffer[j].buf[2] = 0u;
                s_can_tx_fifo_manager[i].buffer[j].buf[3] = 0u;
                s_can_tx_fifo_manager[i].buffer[j].buf[4] = 0u;
                s_can_tx_fifo_manager[i].buffer[j].buf[5] = 0u;
                s_can_tx_fifo_manager[i].buffer[j].buf[6] = 0u;
                s_can_tx_fifo_manager[i].buffer[j].buf[7] = 0u;
            }

            SetCanChnRxTxBuffer(i);
        }
    }
    return result;
}

/**
 * ����CAN�ķ��ͽ��ջ�����
 * @ingroup   FWS_CAN_STACK
 * @param chn  CANͨ����
 * @return void  ��
 */
static void SetCanChnRxTxBuffer(u8 chn)
{
    MB_ConfigType canmsg;
    switch (chn)
    {
    case INTERNAL_CAN:
        {
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 1u;
            canmsg.IRQ = 1u;
            canmsg.CANID = LCM1_CAN_ID;
            canmsg.MASK = 0xffffffffu;
            canmsg.MB_NUM = LCM1_MB_NUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg); /*lcm_A_can1_send_msg1,����LCM���͵ı���1*/
            
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 1u;
            canmsg.IRQ = 1u;
            canmsg.CANID = LCM2_CAN_ID;
            canmsg.MASK = 0xffffffffu;
            canmsg.MB_NUM = LCM2_MB_NUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg); /*lcm_can1_send_msg1������LCM���͵ı���2*/
            
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 1u;
            canmsg.IRQ = 1u;
            canmsg.CANID = BMS_CAN_ID;
            canmsg.MASK = 0xffffffffu;
            canmsg.MB_NUM = BMS_MB_NUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg);   
            
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 0u;
            canmsg.IRQ = 1u;
            canmsg.CANID = PWRCTRL_CAN_ID;
            canmsg.MASK = 0xffffffffu;
            canmsg.MB_NUM = PWRCTRL_MB_NUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg);   
            
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 0u;
            canmsg.IRQ = 1u;
            canmsg.CANID = DEBUG_CAN_ID;
            canmsg.MASK = 0xffffffffu;
            canmsg.MB_NUM = DEBUG_MB_NUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg);   
            
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 0u;
            canmsg.IRQ = 1u;
            canmsg.CANID = TEST_DIO_CAN_ID;
            canmsg.MASK = 0xffffffffu;
            canmsg.MB_NUM = TEST_DIO_MB_NUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg);   
            
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 0u;
            canmsg.IRQ = 1u;
            canmsg.CANID = TEST_ADC1_CAN_ID;
            canmsg.MASK = 0xffffffffu;
            canmsg.MB_NUM = TEST_ADC1_MB_NUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg);   
            
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 0u;
            canmsg.IRQ = 1u;
            canmsg.CANID = TEST_ADC2_CAN_ID;
            canmsg.MASK = 0xffffffffu;
            canmsg.MB_NUM = TEST_ADC2_MB_NUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg);   
            
            canmsg.RX_FLAG = 1u;
			canmsg.IDE = 0u;
			canmsg.IRQ = 1u;
			canmsg.CANID = TEST_ADC3_CAN_ID;
			canmsg.MASK = 0xffffffffu;
			canmsg.MB_NUM = TEST_ADC3_MB_NUM;
			Can_SetBuffer(INTERNAL_CAN, &canmsg);   
                        
            canmsg.RX_FLAG = 1u;
			canmsg.IDE = 0u;
			canmsg.IRQ = 1u;
			canmsg.CANID = TEST_ADC4_CAN_ID;
			canmsg.MASK = 0xffffffffu;
			canmsg.MB_NUM = TEST_ADC4_MB_NUM;
			Can_SetBuffer(INTERNAL_CAN, &canmsg);   
            
            canmsg.RX_FLAG = 1u;
            canmsg.IDE = 1u;
            canmsg.IRQ = 1u;
            canmsg.CANID = UDS_PHY_ADDR_RX_ID;
            canmsg.MASK = ~(UDS_PHY_ADDR_RX_ID ^ UDS_FUNC_ADDR_RX_ID);
            canmsg.MB_NUM = 10u;
            Can_SetBuffer(INTERNAL_CAN, &canmsg); /*UDS��ؽ��ձ���*/

            canmsg.RX_FLAG = 0u;
            canmsg.IDE = 0u;
            canmsg.IRQ = 1u;
            canmsg.CANID = 0u;
            canmsg.MASK = 0x0u;
            canmsg.MB_NUM = SENDMONUM;
            Can_SetBuffer(INTERNAL_CAN, &canmsg); /*���÷��ͻ�����*/

            canmsg.RX_FLAG = 0u;
            canmsg.IDE = 0u;
            canmsg.IRQ = 1u;
            canmsg.CANID = 0u;
            canmsg.MASK = 0x0u;
            canmsg.MB_NUM = SENDMONUM1;
            Can_SetBuffer(INTERNAL_CAN, &canmsg); /*���÷�UDS��ط��ͻ�����*/
            
            canmsg.RX_FLAG = 1u;
			canmsg.IDE = 0u;
			canmsg.IRQ = 1u;
			canmsg.CANID = BMS_VA_CAN_ID;
			canmsg.MASK = 0xffffffffu;
			canmsg.MB_NUM = BMS_VA_MB_NUM;
			Can_SetBuffer(INTERNAL_CAN, &canmsg);   
			
			canmsg.RX_FLAG = 1u;
			canmsg.IDE = 0u;
			canmsg.IRQ = 1u;
			canmsg.CANID = BMS_HEATST_CAN_ID;
			canmsg.MASK = 0xffffffffu;
			canmsg.MB_NUM = BMS_HEATST_MB_NUM;
			Can_SetBuffer(INTERNAL_CAN, &canmsg); 
			
			canmsg.RX_FLAG = 1u;
			canmsg.IDE = 0u;
			canmsg.IRQ = 1u;
			canmsg.CANID = VCU_VEHST_CAN_ID;
			canmsg.MASK = 0xffffffffu;
			canmsg.MB_NUM = VCU_VEHST_MB_NUM;
			Can_SetBuffer(INTERNAL_CAN, &canmsg);   
			
			canmsg.RX_FLAG = 1u;
			canmsg.IDE = 0u;
			canmsg.IRQ = 1u;
			canmsg.CANID = DCDC_ENST_CAN_ID;
			canmsg.MASK = 0xffffffffu;
			canmsg.MB_NUM = DCDC_ENST_MB_NUM;
			Can_SetBuffer(INTERNAL_CAN, &canmsg); 

            break;
        }
    case EXTERNAL_CAN:
    {//������CAN����ͨ��

        canmsg.RX_FLAG = 1u;
        canmsg.IDE = 1u;
        canmsg.IRQ = 1u;
        canmsg.CANID = 0x18FF5C49u;
        canmsg.MASK = 0xffffffffu;
        canmsg.MB_NUM = 0u;
        Can_SetBuffer(EXTERNAL_CAN, &canmsg); /**/

        canmsg.RX_FLAG = 0u;
        canmsg.IDE = 0u;
        canmsg.IRQ = 1u;
        canmsg.CANID = 0u;
        canmsg.MASK = 0x0u;
        canmsg.MB_NUM = SENDMONUM;
        Can_SetBuffer(EXTERNAL_CAN, &canmsg); /*���÷��ͻ�����*/

        break;
    }

    

    default:
    {
        break;
    }
    }
}

/**
 * ����ȫ��ͨ��ʹ��״̬
 * @ingroup FWS_CAN_STACK
 * @param flag 0:��ʹ��    1��ʹ��
 * @return void  ��
 */
void FWS_CAN_STACK_SetGlobalComEnFlag(u8 flag)
{
    s_u8_global_com_en = flag;
}

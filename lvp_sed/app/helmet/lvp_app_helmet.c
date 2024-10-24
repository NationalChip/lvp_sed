/* Voice Signal Preprocess
 * Copyright (C) 2001-2020 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * lvp_app_Helmet.c
 *
 */

#include <lvp_app.h>
#include <lvp_buffer.h>
#include <lvp_pmu.h>
#include <button_simulate.h>
#include <button_simulate.h>
#include <driver/gx_gpio.h>
#include <driver/gx_delay.h>
#include "../lvp/common/uart_message_v2.h"
//#include "resource/resource.h"
#define LOG_TAG "[HELMET_APP]"
#define STANDBY_TIME 167
#define UART_PORT0 0
#define UART_PORT1 1
#define VERSION 6
static unsigned char s_uart_cmd_data[24] = {0x64,0X65,0X66,0X67,0X68,0X69,0X6a,0X6b,0X6c,0X6d,0X6e,0X6f, 0X70,
                                            0x71,0X72,0x73,0X74,0X75,0x76,0x77,0x78,0x79,0x7a,0x7b};
static UART_MSG_INIT_CONFIG init_config ={UART_PORT0,115200,MSG_HOST_MAGIC,1};

//=================================================================================================
typedef enum {
    MSG_NTF_SEND    = NEW_MSG(MSG_TYPE_NTF, 0x90),
    MSG_NTF_RCV         = NEW_MSG(MSG_TYPE_NTF, 0x91),
    MSG_NTF_MCUBACK     =   NEW_MSG(MSG_TYPE_NTF, 0x92),
} SIMULATOR_UART_MSG_ID;
static void _Cmd_Send(unsigned char* data)
{
    MSG_PACK msg_pack;
    msg_pack.msg_header.magic     = MSG_HOST_MAGIC;
    msg_pack.msg_header.cmd       = MSG_NTF_SEND;
    //msg_pack.msg_header.cmd       = MSG_NTF_RCV;
    msg_pack.msg_header.flags     = 0;
    msg_pack.body_addr            = data;
    msg_pack.port                 = UART_PORT0;
    msg_pack.len                  = 1;
    UartMessageAsyncSend(&msg_pack);
    //printf(" *%#x \n",*msg_pack.body_addr);
}

static void _Mcu_Version_Back(unsigned char* data)
{
    MSG_PACK msg_pack;
    msg_pack.msg_header.magic     = MSG_HOST_MAGIC;
    msg_pack.msg_header.cmd       = MSG_NTF_MCUBACK;
    msg_pack.msg_header.flags     = 0;
    msg_pack.body_addr            = data;
    msg_pack.port                 = UART_PORT0;
    msg_pack.len                  = 2;
    UartMessageAsyncSend(&msg_pack);
    //printf(" *%#x \n",*msg_pack.body_addr);

}
static void _Mcu_Back(unsigned char* data)
{
    MSG_PACK msg_pack;
    msg_pack.msg_header.magic     = MSG_HOST_MAGIC;
    msg_pack.msg_header.cmd       = MSG_NTF_MCUBACK;
    msg_pack.msg_header.flags     = 0;
    msg_pack.body_addr            = data;
    msg_pack.port                 = UART_PORT0;
    msg_pack.len                  = 1;
    UartMessageAsyncSend(&msg_pack);
    //printf(" *%#x \n",*msg_pack.body_addr);

}
static unsigned char mcu_bck_data[3] = {0x10,0x20,0x40};
static unsigned char mcu_bck_ver_data[2] = {0x30,VERSION};

static int _uartRecvCallback(MSG_PACK * pack, void *priv)
{

    if(*(pack->body_addr) != 0) {
        switch(*(pack->body_addr)) {
        case 0x01:
            _Mcu_Back((unsigned char *)mcu_bck_data);
            break;
        case 0x02:
            _Mcu_Back((unsigned char *)mcu_bck_data + 1);
            break;
        case 0x03:
            _Mcu_Version_Back((unsigned char *) mcu_bck_ver_data);
            break;
        case 0x04:
            _Mcu_Back((unsigned char *)mcu_bck_data + 2);
            break;
        }

    }
    return 0;
}
static unsigned char rcv_data = 0;



static int HelmetAppSuspend(void *priv)
{
    return 0;
}

static int HelmetAppResume(void *priv)
{
    return 0;
}

static int s_suspend_lock = 0;
static int HelmetAppInit(void)
{
    UART_MSG_REGIST regist_info = {
        .msg_id = MSG_NTF_RCV,
        .port = UART_PORT0,
        .msg_buffer = &rcv_data,
        .msg_buffer_length = 1,
        .msg_pack_callback = _uartRecvCallback,
    };

    UartMessageAsyncRegist(&regist_info);
    UartMessageAsyncInit(&init_config);
    LvpPmuSuspendLockCreate(&s_suspend_lock);
    return 0;
}

static int s_short_state = 0;
// App Event Process
static int HelmetAppEventResponse(APP_EVENT *app_event)
{
    s_short_state = s_short_state > 0 ? s_short_state - 1 : 0;

    if(s_short_state != 0)
        LvpPmuSuspendLock(s_suspend_lock);
    else
        LvpPmuSuspendUnlock(s_suspend_lock);

    if(app_event->event_id < 100) {
        return 0;
    }
    switch(app_event->event_id)
    {
        case 111:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 11);
            return 0;
        case 112:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 12);
            return 0;
    }
    if(s_short_state == 0) {
        if(app_event->event_id  == 100) {
            s_short_state = STANDBY_TIME;
        }
        else
            return 0;
    }
    else
        s_short_state = STANDBY_TIME;
    switch(app_event->event_id) {
        case 100:
            _Cmd_Send((unsigned char *)s_uart_cmd_data);
            break;
        case 101:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 1);
            break;
        case 102:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 2);
            break;
        case 103:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 3);
            break;
        case 104:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 4);
            break;
        case 105:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 5);
            break;
        case 106:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 6);
            break;
        case 107:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 7);
            break;
        case 108:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 8);
            break;
        case 109:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 9);
            break;
        case 110:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 10);
            break;
        case 113:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 13);
            break;
        case 114:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 14);
            break;
        case 115:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 15);
            break;
        case 116:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 16);
            break;
        case 117:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 17);
            break;
        case 118:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 18);
            break;
        case 119:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 19);
            break;
        case 120:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 20);
            break;
        case 121:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 21);
            break;
        case 122:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 22);
            break;
        case 123:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 23);
            break;
        case 124:
            _Cmd_Send((unsigned char *)s_uart_cmd_data + 24);
            break;

    }


    return 0;
}

// APP Main Loop
static int HelmetAppTaskLoop(void)
{

    return 0;
}


LVP_APP Helmet_app = {
    .app_name = "Helmet app",
    .AppInit = HelmetAppInit,
    .AppEventResponse = HelmetAppEventResponse,
    .AppTaskLoop = HelmetAppTaskLoop,
    .AppSuspend = HelmetAppSuspend,
    .suspend_priv = NULL,
    .AppResume = HelmetAppResume,
    .resume_priv = NULL,
};

LVP_REGISTER_APP(Helmet_app);


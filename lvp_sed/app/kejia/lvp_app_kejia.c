/* Voice Signal Preprocess
 * Copyright (C) 2001-2020 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * lvp_app_kejia.c
 *
 */

#include <lvp_app.h>
#include <lvp_buffer.h>
#include <lvp_pmu.h>
#include <button_simulate.h>
#include <button_simulate.h>
#include <driver/gx_gpio.h>
#include <driver/gx_delay.h>
//#include "lvp_voice_player.h"
#include "resource/resource.h"
#define LOG_TAG "[KEJIA_APP]"
#define STANDBY_TIME 167

//=================================================================================================


int keypress(SIMULATE_EVENT event){
    return 0;
}
static int KejiaAppSuspend(void *priv)
{
/*
    for(int j = 3; j < 13; j++) {
         gx_gpio_set_direction(j, GX_GPIO_DIRECTION_OUTPUT);
    }
    for(int i = 3; i < 13; i++) {
            gx_gpio_set_level(i, GX_GPIO_LEVEL_HIGH);
    }
    */
    return 0;
}

static int KejiaAppResume(void *priv)
{

    return 0;
}
static int s_suspend_lock = 0;
static int KejiaAppInit(void)
{

    LvpPmuSuspendLockCreate(&s_suspend_lock);
    return 0;
}

static int s_short_state = 0;

static int KejiaAppEventResponse(APP_EVENT *app_event)
{
    s_short_state = s_short_state > 0 ? s_short_state - 1 : 0;

    if(s_short_state != 0)
        LvpPmuSuspendLock(s_suspend_lock);
    else
        LvpPmuSuspendUnlock(s_suspend_lock);

    if(app_event->event_id < 100) {
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
        case 100://你好小可
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            break;
        case 101://衣架全关
            gx_gpio_set_level(5, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(5, GX_GPIO_LEVEL_HIGH);
            break;
        case 102://打开风干
            gx_gpio_set_level(9, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(180);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(9, GX_GPIO_LEVEL_HIGH);
            break;
        case 103://关闭风干
            gx_gpio_set_level(9, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(180);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(9, GX_GPIO_LEVEL_HIGH);
            break;
        case 104://打开热风
            //printf("dakairefeng\n");
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(10, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(10, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);

            break;
        case 105://关闭热风
            //printf("GUANBIrefeng\n");
            gx_gpio_set_level(10, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(10, GX_GPIO_LEVEL_HIGH);
            break;
        case 106://打开消毒
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(12, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);

            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(12, GX_GPIO_LEVEL_HIGH);
            break;
        case 107://关闭消毒
            gx_gpio_set_level(12, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(12, GX_GPIO_LEVEL_HIGH);
            break;
        case 108://衣架上升
            gx_gpio_set_level(6, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);  ///////////////////////////////////
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(6, GX_GPIO_LEVEL_HIGH);
            break;
        case 109://衣架停止
            gx_gpio_set_level(7, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);/////////////////////////////////////
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(7, GX_GPIO_LEVEL_HIGH);
            break;
        case 110://衣架下降
            gx_gpio_set_level(8, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(8, GX_GPIO_LEVEL_HIGH);
            break;

        case 111://打开灯光
            gx_gpio_set_level(11, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(11, GX_GPIO_LEVEL_HIGH);
            break;
        case 112://关闭灯光
            gx_gpio_set_level(11, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_level(11, GX_GPIO_LEVEL_HIGH);
            break;
        case 113://打开语音
            gx_gpio_set_level(5, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_mdelay(200);
            gx_gpio_set_level(5, GX_GPIO_LEVEL_HIGH);
            break;
        case 114://关闭语音
            gx_gpio_set_level(5, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_mdelay(200);
            gx_gpio_set_level(5, GX_GPIO_LEVEL_HIGH);
            break;
        case 115://遥控器对码
            gx_gpio_set_level(5, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_mdelay(200);
            gx_gpio_set_level(5, GX_GPIO_LEVEL_HIGH);
            break;
        case 116://遥控器解码
            gx_gpio_set_level(7, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_mdelay(200);
            gx_gpio_set_level(7, GX_GPIO_LEVEL_HIGH);
            break;
            /*
        case 117://恢复出厂设置
            gx_gpio_set_level(7, GX_GPIO_LEVEL_LOW);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(3, GX_GPIO_LEVEL_HIGH);
            gx_mdelay(200);
            gx_gpio_set_level(7, GX_GPIO_LEVEL_HIGH);
            gx_mdelay(200);
            gx_gpio_set_level(11, GX_GPIO_LEVEL_LOW);
            gx_mdelay(200);
            gx_gpio_set_level(11, GX_GPIO_LEVEL_HIGH);
            break;
            */
    }


    return 0;
}

// APP Main Loop
static int KejiaAppTaskLoop(void)
{
    return 0;
}


LVP_APP kejia_app = {
    .app_name = "kejia app",
    .AppInit = KejiaAppInit,
    .AppEventResponse = KejiaAppEventResponse,
    .AppTaskLoop = KejiaAppTaskLoop,
    .AppSuspend = KejiaAppSuspend,
    .suspend_priv = NULL,
    .AppResume = KejiaAppResume,
    .resume_priv = NULL,
};

LVP_REGISTER_APP(kejia_app);


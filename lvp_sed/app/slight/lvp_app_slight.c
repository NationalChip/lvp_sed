/* Voice Signal Preprocess
 * Copyright (C) 2001-2020 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * lvp_app_other_v1_0.c
 *
 */

#include <lvp_app.h>
#include <lvp_context.h>
#include <lvp_buffer.h>

//=================================================================================================
// App Event Process
#include "slight_led/slight_led.h"
#include <gpio_func.h>
#include "multi_button/src/multi_button.h"
#include <board_misc_config.h>
#include <driver/gx_timer.h>
#include <driver/gx_delay.h>
#ifdef BOARD_HAS_SLIGHT_LED

#define LOG_TAG "[SlightApp]"

static Button warm_key;
static Button cold_key;
static Button mode_key;
static Button switch_key;
#if defined(LED_WARM_MODE_PIN)&& defined(LED_COLD_MODE_PIN)
static Button warm_mode_key;
static Button cold_mode_key;
#endif

static unsigned char ReadBrightenkeyVal(void)
{
    return gx_gpio_get_level(LED_BRIGHTEN_PIN);
}

static unsigned char ReadDimkeyVal(void)
{
    return gx_gpio_get_level(LED_DIM_PIN);
}

static unsigned char ReadModekeyVal(void)
{
    return gx_gpio_get_level(LED_MODE_PIN);
}

static unsigned char ReadSwitchkeyVal(void)
{
    return gx_gpio_get_level(LED_SWITCH_PIN);
}

#if defined(LED_WARM_MODE_PIN)&& defined(LED_COLD_MODE_PIN)
static unsigned char ReadWarmModekeyVal(void)
{
    return gx_gpio_get_level(LED_WARM_MODE_PIN);
}

static unsigned char ReadColdModekeyVal(void)
{
    return gx_gpio_get_level(LED_COLD_MODE_PIN);
}
#endif

void BrightenKeySingleClickHandler(void* btn)
{
    enum SlightledMode mode = GetSlightLedMode();
    if(mode >= SLIGHT_LED_MODE_GEAR1 && mode < SLIGHT_LED_MODE_GEAR30)
        SetSlightLedMode(++mode);
    printf("%s %d set mode :%d\n", __func__,__LINE__,mode);
}

void BrightenKeyLongPressHoldHandler(void* btn)
{
    printf("%s %d\n", __func__,__LINE__);
    int brightness_perthousand;
    do
    {
        brightness_perthousand = GetSlightLedBrightness();
        if(brightness_perthousand == 1000)
        {
            break;
        }
        // start_us = gx_get_time_us();

        SetSlightLedBrightness(++brightness_perthousand);
        gx_udelay(500);
    }while(ReadBrightenkeyVal() == LVP_SLIGHT_KEY_PRESSED_VAL);
}

void DimKeySingleClickHandler(void* btn)
{
    enum SlightledMode mode = GetSlightLedMode();
    if(mode > SLIGHT_LED_MODE_GEAR1 && mode <= SLIGHT_LED_MODE_GEAR30)
        SetSlightLedMode(--mode);
    printf("%s %d set mode :%d\n", __func__,__LINE__,mode);

}

void DimKeyLongPressHoldHandler(void* btn)
{
    printf("%s %d\n", __func__,__LINE__);

    int brightness_perthousand;
    do
    {
        brightness_perthousand = GetSlightLedBrightness();
        if(brightness_perthousand == 0)
        {
            break;
        }
        SetSlightLedBrightness(--brightness_perthousand);
        gx_udelay(500);
    }while(ReadDimkeyVal() == LVP_SLIGHT_KEY_PRESSED_VAL);
}

void ModeKeySingleClickHandler(void* btn)
{
    printf("%s %d\n", __func__,__LINE__);
    enum SlightWorkMode work_mode = GetSlightWorkMode();
    if(work_mode == SLIGHT_WORKMODE_NORMAL)
    {
        work_mode = SLIGHT_WORKMODE_WARM;
    }
    else if(work_mode == SLIGHT_WORKMODE_WARM)
    {
        work_mode = SLIGHT_WORKMODE_COLD;
    }
    else if(work_mode == SLIGHT_WORKMODE_COLD)
    {
        work_mode = SLIGHT_WORKMODE_NORMAL;
    }
    SetSlightWorkmode(work_mode);
}

void SwitchKeySingleClickHandler(void* btn)
{
    printf("%s %d\n", __func__,__LINE__);
    enum SlightledMode mode = GetSlightLedMode();
    if(mode != SLIGHT_LED_MODE_OFF)
    {
        SetSlightLedMode(SLIGHT_LED_MODE_OFF);
    }
    else
    {
        SetSlightLedMode(SLIGHT_LED_MODE_GEAR1);
    }
}

#if defined(LED_WARM_MODE_PIN)&& defined(LED_COLD_MODE_PIN)
void WarmModeKeySingleClickHandler(void* btn)
{
    printf("%s %d\n", __func__,__LINE__);
    SetSlightWorkmode(SLIGHT_WORKMODE_WARM);
}

void ColdModeKeySingleClickHandler(void* btn)
{
    printf("%s %d\n", __func__,__LINE__);
    SetSlightWorkmode(SLIGHT_WORKMODE_COLD);
}
#endif

static int LvpAppButtonRegister(void)
{
    // gx_gpio_set_direction(LED_DIM_PIN, GX_GPIO_DIRECTION_INPUT);
    // button_init(&cold_key, ReadDimkeyVal, LVP_SLIGHT_KEY_PRESSED_VAL);
    // button_attach(&cold_key, SINGLE_CLICK, DimKeySingleClickHandler);
    // button_attach(&cold_key, LONG_PRESS_HOLD, DimKeyLongPressHoldHandler);
    // button_start(&cold_key);

    // gx_gpio_set_direction(LED_BRIGHTEN_PIN, GX_GPIO_DIRECTION_INPUT);
    // button_init(&warm_key, ReadBrightenkeyVal, LVP_SLIGHT_KEY_PRESSED_VAL);
    // button_attach(&warm_key, SINGLE_CLICK, BrightenKeySingleClickHandler);
    // button_attach(&warm_key, LONG_PRESS_HOLD, BrightenKeyLongPressHoldHandler);
    // button_start(&warm_key);


    // gx_gpio_set_direction(LED_MODE_PIN, GX_GPIO_DIRECTION_INPUT);
    // button_init(&mode_key, ReadModekeyVal, LVP_SLIGHT_KEY_PRESSED_VAL);
    // button_attach(&mode_key, SINGLE_CLICK, ModeKeySingleClickHandler);
    // button_start(&mode_key);

    gx_gpio_set_direction(LED_SWITCH_PIN, GX_GPIO_DIRECTION_INPUT);
    button_init(&switch_key, ReadSwitchkeyVal, LVP_SLIGHT_KEY_PRESSED_VAL);
    button_attach(&switch_key, SINGLE_CLICK, SwitchKeySingleClickHandler);
    button_start(&switch_key);

#if defined(LED_WARM_MODE_PIN)&& defined(LED_COLD_MODE_PIN)
    gx_gpio_set_direction(LED_WARM_MODE_PIN, GX_GPIO_DIRECTION_INPUT);
    button_init(&warm_mode_key, ReadWarmModekeyVal, LVP_SLIGHT_KEY_PRESSED_VAL);
    button_attach(&warm_mode_key, SINGLE_CLICK, WarmModeKeySingleClickHandler);
    button_start(&warm_mode_key);

    gx_gpio_set_direction(LED_COLD_MODE_PIN, GX_GPIO_DIRECTION_INPUT);
    button_init(&cold_mode_key, ReadColdModekeyVal, LVP_SLIGHT_KEY_PRESSED_VAL);
    button_attach(&cold_mode_key, SINGLE_CLICK, ColdModeKeySingleClickHandler );
    button_start(&cold_mode_key);
#endif
    LvpButtonInit();
    return 0;
}

static int SlightAppInit(void)
{
    LvpSlightLedInit(LED_WARM_PIN, LED_COLD_PIN);
    LvpAppButtonRegister();
    return 0;
}

static int SlightAppEventResponse(APP_EVENT *plc_event)
{
    if(plc_event->event_id < 100)
        return 0;
    if(100 == plc_event->event_id)//da kai deng guang
    {
        enum SlightledMode mode = GetSlightLedMode();
        if(mode == SLIGHT_LED_MODE_OFF)
        {
            SetSlightLedMode(SLIGHT_LED_MODE_GEAR1);
        }
    }
    else if(101 == plc_event->event_id)//guan bi deng guang
    {
        enum SlightledMode mode = GetSlightLedMode();
        if(mode != SLIGHT_LED_MODE_OFF)
        {
            SetSlightLedMode(SLIGHT_LED_MODE_OFF);
        }
    }
    else if(102 == plc_event->event_id) //deng liang yi dian
    {
        enum SlightledMode mode = GetSlightLedMode();
        if(mode >= SLIGHT_LED_MODE_GEAR1 && mode < SLIGHT_LED_MODE_GEAR30)
        {
            if(mode >= SLIGHT_LED_MODE_GEAR22)
            {
                mode = SLIGHT_LED_MODE_GEAR24;
                 SetSlightLedMode(mode);
            }
            else
            {
                mode += 3;
                SetSlightLedMode(mode);
            }
            printf("set mode =%d\n", mode);
        }
    }
    else if(103 == plc_event->event_id)//deng an yi dian
    {
        enum SlightledMode mode = GetSlightLedMode();
        if(mode > SLIGHT_LED_MODE_GEAR1 && mode <= SLIGHT_LED_MODE_GEAR30)
        {
            if(mode <= SLIGHT_LED_MODE_GEAR3)
            {
                 mode = SLIGHT_LED_MODE_GEAR1;
                 SetSlightLedMode(mode);
            }
            else
            {
                mode -=3;
                SetSlightLedMode(mode);
            }
            printf("set mode =%d\n", mode);
        }
    }
    else if(104 == plc_event->event_id)//nuan guang mo shi
    {
        SetSlightWorkmode(SLIGHT_WORKMODE_WARM);
    }
    else if(105 == plc_event->event_id)//leng guang mo shi
    {
        SetSlightWorkmode(SLIGHT_WORKMODE_COLD);
    }
    else if(106 == plc_event->event_id)//deng guang quan kai
    {
        SetSlightWorkmode(SLIGHT_WORKMODE_NORMAL);
        SetSlightLedMode(SLIGHT_LED_MODE_GEAR30);
    }
    else if(107 == plc_event->event_id)//qie huan mo shi
    {
        enum SlightWorkMode work_mode = GetSlightWorkMode();
        if(work_mode == SLIGHT_WORKMODE_NORMAL)
        {
            work_mode = SLIGHT_WORKMODE_WARM;
        }
        else if(work_mode == SLIGHT_WORKMODE_WARM)
        {
            work_mode = SLIGHT_WORKMODE_COLD;
        }
        else if(work_mode == SLIGHT_WORKMODE_COLD)
        {
            work_mode = SLIGHT_WORKMODE_NORMAL;
        }
        SetSlightWorkmode(work_mode);
    }
    return 0;
}

static int SlightAppTaskLoop(void)
{
    return 0;
}

LVP_APP slight_app = {
    .app_name = "smart light",
    .AppInit = SlightAppInit,
    .AppEventResponse = SlightAppEventResponse,
    .AppTaskLoop = SlightAppTaskLoop,
};

LVP_REGISTER_APP(slight_app);
#endif

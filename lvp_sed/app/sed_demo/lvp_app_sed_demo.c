/* Voice Signal Preprocess
* Copyright (C) 2001-2023 NationalChip Co., Ltd
* ALL RIGHTS RESERVED!
*
* lvp_app_sed_demo.c
*
*/

#include <lvp_app.h>
#include <lvp_buffer.h>

#include <driver/gx_gpio.h>
#include <sed_decode.h>

#ifdef CONFIG_LVP_FACTORY_MIC_TEST
#include "lvp_mic_test.h"
#endif

#define LOG_TAG "[SED_DEMO_APP]"

//=================================================================================================

static int SedDemoAppSuspend(void *priv)
{
    printf(LOG_TAG" ---- %s ----\n", __func__);
    printf("%s\n", (unsigned char *)priv);
    return 0;
}

static int SedDemoAppResume(void *priv)
{
    printf(LOG_TAG" ---- %s ----\n", __func__);
    printf("%s\n", (unsigned char *)priv);
    return 0;
}

#define SNORING_LED     (CONFIG_LVP_APP_SED_DEMO_SNORING_LED)
#define BABYCRYING_LED  (CONFIG_LVP_APP_SED_DEMO_BABYCRYING_LED)

static int SedDemoAppInit(void)
{
    printf(LOG_TAG" ---- %s ----\n", __func__);
            gx_gpio_set_direction(SNORING_LED, GX_GPIO_DIRECTION_OUTPUT);
            gx_gpio_set_level(SNORING_LED, GX_GPIO_LEVEL_HIGH);
            gx_gpio_set_direction(BABYCRYING_LED, GX_GPIO_DIRECTION_OUTPUT);
            gx_gpio_set_level(BABYCRYING_LED, GX_GPIO_LEVEL_HIGH);

    return 0;
}

// App Event Process
static int SedDemoAppEventResponse(APP_EVENT *app_event)
{
    if (app_event->event_id == LVP_SED_DONE_ID) {
//        printf("app_event->sed_out %d\n", app_event->sed_out);
        static int snoring_count = 0;
        static int babycrying_count = 0;

        LVP_CONTEXT *context;
        unsigned int ctx_size;
        LvpGetContext(app_event->ctx_index, &context, &ctx_size);

        static int sonring_flag = 0; 
        if (context->sed & SED_SNORING) {
            if (sonring_flag == 0)
                printf(LOG_TAG"Sonring start\n ");
            sonring_flag = 1; 
            snoring_count = 20;
        } else {
            if (sonring_flag == 1)
                printf(LOG_TAG"Sonring end\n");
            sonring_flag = 0; 
        }
        static int babycrying_flag = 0;
        if (context->sed & SED_BABYCRYING) {
            if (babycrying_flag == 0)
                printf(LOG_TAG"Babycrying start\n");
            babycrying_flag = 1; 
            babycrying_count = 20;
        } else {
            if (babycrying_flag == 1)
                printf(LOG_TAG"Babycrying end\n");
            babycrying_flag = 0; 
        }

        if (snoring_count) {
            snoring_count--;

            gx_gpio_set_level(SNORING_LED, GX_GPIO_LEVEL_LOW);
        } else {
            gx_gpio_set_level(SNORING_LED, GX_GPIO_LEVEL_HIGH);
        }
        if (babycrying_count) {
            babycrying_count--;
            gx_gpio_set_level(BABYCRYING_LED, GX_GPIO_LEVEL_LOW);
        } else {
            gx_gpio_set_level(BABYCRYING_LED, GX_GPIO_LEVEL_HIGH);
        }
    }

    return 0;
}

// APP Main Loop
static int SedDemoAppTaskLoop(void)
{
    return 0;
}


LVP_APP sed_demo_app = {
    .app_name = "sed demo app",
    .AppInit = SedDemoAppInit,
    .AppEventResponse = SedDemoAppEventResponse,
    .AppTaskLoop = SedDemoAppTaskLoop,
    .AppSuspend = SedDemoAppSuspend,
    .suspend_priv = "SedDemoAppSuspend",
    .AppResume = SedDemoAppResume,
    .resume_priv = "SedDemoAppResume",
};

LVP_REGISTER_APP(sed_demo_app);


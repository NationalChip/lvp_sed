/* Voice Signal Preprocess
 * Copyright (C) 2001-2020 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * lvp_app_sample.c
 *
 */
#include <stdio.h>
#include <lvp_app.h>
#include <lvp_buffer.h>
#include <lvp_mp3_player.h>
#include "types.h"
#include "resource/resource.h"

#define LOG_TAG "[MP3_PLAYER_APP]"
static int app_init = 0;
#include <lvp_attr.h>
#include <soc_config.h>

#include <driver/gx_timer.h>
static int is_finish = 1;
static void PlayerEventCallback(int player_event_id, void *data)
{
    if(player_event_id == EVENT_PLAYER_FINISH)
    {
        printf("player_event_id = %d\n", player_event_id);
        is_finish = 1;
    }
}

static unsigned int start_ms, end_ms;
static int Mp3PlayerAppInit(void)
{
    if (!app_init)
    {
        printf(LOG_TAG" ---- %s ----\n", __func__);
        LvpMp3PlayerInit(PlayerEventCallback);
        #if 0
        extern const unsigned char mp3_44100[];
        extern const unsigned int mp3_44100_len;
        LvpMp3PlayerPlay(mp3_44100, mp3_44100_len, 1);
        //start_ms = gx_get_time_ms();
        #endif

        #if 0
        extern const unsigned char mp3_16000[];
        extern const unsigned int mp3_16000_len;
        LvpMp3PlayerPlay(mp3_16000, mp3_16000_len, 1);
        #endif

#if 1
        extern const unsigned char caiquan_44100_mp3[];
        extern const unsigned int caiquan_44100_mp3_len;
        LvpMp3PlayerPlay(caiquan_44100_mp3, caiquan_44100_mp3_len, 1);
#endif
        app_init = 1;
    }
    return 0;
}

// App Event Process
static int Mp3PlayerAppEventResponse(APP_EVENT *app_event)
{
    return 0;
}

// APP Main Loop
static int Mp3PlayerAppTaskLoop(void)
{

#ifdef TEST_VOLUME
    static int i = 0;
    int volume;
    end_ms = gx_get_time_ms();
    unsigned int use_time = end_ms - start_ms;
    if(use_time > 2000*i && use_time < 2000*i +1000)
    {
        volume = LvpMp3PlayerGetVolume();
        int set_volume = (volume + 10)%100;
        printf("get volume =%d set_volume =%d\n", volume, set_volume);
        LvpMp3PlayerSetVolume(set_volume);
        i++;
    }
#endif

#ifdef TEST_STOP
    static int is_stoped = 0;
    end_ms = gx_get_time_ms();
    unsigned int use_time = end_ms - start_ms;
    if(end_ms > 4000 && end_ms < 5000 && !is_stoped )
    {
        printf("stop !!!\n");
        LvpMp3PlayerStop();
        is_stoped = 1;
    }
#endif

#ifdef TEST_STATUS
    int status = LvpMp3PlayerGetStatus();
    printf("status =%d\n",  status);
#endif

    // extern const unsigned char mp3_caiquan_44100_mp3[];
    // extern const unsigned int mp3_caiquan_44100_mp3_len;
    // if(is_finish)
    // {
    //     is_finish = 0;
    //     LvpMp3PlayerPlay(mp3_caiquan_44100_mp3, mp3_caiquan_44100_mp3_len, 0);
    // }


    return 0;
}


LVP_APP mp3_player_app = {
    .app_name = "mp3 player",
    .AppInit = Mp3PlayerAppInit,
    .AppEventResponse = Mp3PlayerAppEventResponse,
    .AppTaskLoop = Mp3PlayerAppTaskLoop,
};

LVP_REGISTER_APP(mp3_player_app);

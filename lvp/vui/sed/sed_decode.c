/* Grus
 * Copyright (C) 2001-2021 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * decode.c: decode sound event from module output
 *
 */

#include <autoconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <driver/gx_timer.h>
#include <driver/gx_cache.h>

#include <lvp_context.h>
#include <lvp_buffer.h>
#include <lvp_param.h>

#include <sed_model.h>
#include "sed_decode.h"
#include "driver/dsp/csky_math.h"
#include "driver/dsp/csky_const_structs.h"
#ifdef CONFIG_ENABLE_POST_PROCESSING
#include "post_processing.h"
#endif

#define LOG_TAG "[LVP_Decoder]"

int SedDecodeInit(void)
{
#ifdef CONFIG_ENABLE_POST_PROCESSING
    LvpRnnSedPostProcessingInit();
#endif
    return 0;
}

unsigned int SedDecodeSed(LVP_CONTEXT *context)
{
    float *module_out = (float *)LvpSedModelGetSnpuOutBuffer(context->snpu_buffer);
    int size = LvpSedModelGetOutBufferSize((void*)context->snpu_buffer);
    gx_dcache_invalid_range((uint32_t *)module_out, size);
    int ret = 0;

#ifdef CONFIG_SED_CYCLES_DEBUG
    int start = gx_get_time_us();
#endif
#ifdef CONFIG_ENABLE_POST_PROCESSING
    ret = LvpRnnSedPostProcessingRun(module_out);
#endif
//    printf("%f %f\n", module_out[0], module_out[1]);
    //printf("%f %f %d\n", module_out[0], module_out[1], ret);
//    printf("%d\n", ret);
#if 1
    if (ret & SED_SNORING) {
#if 0
        printf (LOG_TAG"[CTC] Activation ctx:%d,Kws:%s[%d],th:%d,S:%d,%d\n"
                , context->ctx_index
                , "SonringTest"
                , ret
                , (int)(CONFIG_VED_SNORING_THRESHOLD * 0.01f)//g_kws_list.kws_param_list[i].threshold
                , (int)(module_out[0])
                , 0);
#endif
    }
    if (ret & SED_BABYCRYING) {
#if 0
        printf (LOG_TAG"[CTC] Activation ctx:%d,Kws:%s[%d],th:%d,S:%f,%f\n"
                , context->ctx_index
                , "BabyCryingTest"
                , ret
                , (int)(CONFIG_VED_SNORING_THRESHOLD * 0.01f)//g_kws_list.kws_param_list[i].threshold
                , (int)(module_out[1])
                , 0);
#endif
    }
#endif
    context->sed = ret;

#ifdef CONFIG_SED_CYCLES_DEBUG
    int end = gx_get_time_us();
    reco_time[0] = end - start;

    start = gx_get_time_us();
#endif

    return ret;
}


int SedDecodeDone(void)
{
#ifdef CONFIG_ENABLE_POST_PROCESSING
    LvpRnnSedPostProcessingDone();
#endif
    return 0;
}

/* Grus
 * Copyright (C) 2001-2021 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * recover.c: recover wav data from module output
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
#include <post_processing.h>

#define LOG_TAG "[SED]"

#define CRY_NUM (150)
#define CRY_BAK_NUM (50)
static float s_his_cry[CRY_NUM] = {0};
static int s_index = 0;

int LvpRnnSedPostProcessingInit(void)
{
    return 0;
}

int LvpRnnSedPostProcessingRun(float *module_out)
{

    int ret = 0;
//   printf("%f %f\n", module_out[0], module_out[1]);
    if (module_out[0] >= (CONFIG_VED_SNORING_THRESHOLD * 0.01f)) {
        ret |= 0x1;
//        printf("snoring\n");
    }
    s_his_cry[s_index] = module_out[1];
    s_index = (s_index + 1) % CRY_NUM;
    if (module_out[1] >= (CONFIG_VED_BABYCRYING_THRESHOLD * 0.01f)) {
        int back_index = (s_index + 1) % CRY_NUM;
        for (int i = 0; i < CRY_BAK_NUM; i++) {
            if (s_his_cry[(back_index + i) % CRY_NUM] >= (CONFIG_VED_BABYCRYING_THRESHOLD * 0.01f)) {
                ret |= 0x2;
                //        printf("babycrying\n");
                break;
            }
        }
    }

    return ret;
}

int LvpRnnSedPostProcessingDone(void)
{
    return 0;
}

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
#include "agc.h"
#include "common_function.h"
#include "vma_utinity_const_structs.h"
#include "vad.h"
#include "wiener.h"
#include "hamming.h"

int LvpRnnSedPostProcessingInit(void)
{
    return 0;
}

int LvpRnnSedPostProcessingRun(float *module_out)
{
    return 0;
}

int LvpRnnSedPostProcessingDone(void)
{
    return 0;
}

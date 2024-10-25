/* Grus
 * Copyright (C) 2001-2021 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * post processing.h: post processing
 *
 */

#ifndef __POST_PROCESSING_H__
#define __POST_PROCESSING_H__
#include<lvp_context.h>

int LvpRnnSedPostProcessingInit(void);
int LvpRnnSedPostProcessingRun(float *module_out);
int LvpRnnSedPostProcessingDone(void);
#endif /* __POST_PROCESSING__ */

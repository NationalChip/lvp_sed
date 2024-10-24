/* Grus
 * Copyright (C) 2001-2020 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * sed_model.h: SED(Sound Event Detection) Model
 *
 */

#ifndef __SED_MODEL_H__
#define __SED_MODEL_H__

#include <driver/gx_snpu.h>

int LvpSedModelGetOpsSize(void);
int LvpSedModelGetDataSize(void);
int LvpSedModelGetTmpSize(void);
int LvpSedModelGetCmdSize(void);
int LvpSedModelGetWeightSize(void);
void LvpSetSnpuTask(GX_SNPU_TASK* snpu_task);
int LvpSedModelInitSnpuTask(GX_SNPU_TASK *snpu_task);
const char *LvpSedModelGetVersion(void);
void *LvpSedModelGetSnpuFeatsBuffer(void *snpu_buffer);
void *LvpSedModelGetSnpuOutBuffer(void *snpu_buffer);
int LvpSedModelGetSnpuFeatsSize(void *snpu_buffer);
int LvpSedModelGetOutBufferSize(void *snpu_buffer);
void *LvpSedModelGetSnpuStatesBuffer(void *snpu_buffer);
int LvpSedModelGetSnpustatesSize(void *snpu_buffer);
void *LvpSedModelGetFixStateBuffer(void);



#endif /* __CTC_MODEL_H__ */

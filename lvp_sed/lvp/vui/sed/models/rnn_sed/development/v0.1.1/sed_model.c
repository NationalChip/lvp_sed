/* Voice Signal Preprocess
 * Copyright (C) 2001-2020 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * ctc_model.c: Kws Model
 *
 */

#include <autoconf.h>
#include <stdio.h>
#include <string.h>
#include <csi_core.h>
#include <lvp_buffer.h>
#include <sed_model.h>

#include <driver/gx_snpu.h>
#include <driver/gx_pmu_ctrl.h>

#include "model.h"

#define LOG_TAG "[SED]"


static GX_SNPU_TASK s_snpu_task;

int LvpSedModelGetCmdSize(void)
{
    return sizeof(cmd_content);
}

int LvpSedModelGetWeightSize(void)
{
    return sizeof(weight_content);
}

int LvpSedModelGetOpsSize(void)
{
    return sizeof(ops_content);
}

int LvpSedModelGetDataSize(void)
{
    return sizeof(data_content);
}

int LvpSedModelGetTmpSize(void)
{
    return sizeof(tmp_content);
}

void LvpSedSetSnpuTask(GX_SNPU_TASK *snpu_task)
{
#ifdef CONFIG_NPU_RUN_IN_FLASH
#else
    memcpy(&s_snpu_task, snpu_task, sizeof(GX_SNPU_TASK));
#endif
}

int LvpSedModelInitSnpuTask(GX_SNPU_TASK *snpu_task)
{
    if (CONFIG_SED_SNPU_BUFFER_SIZE != sizeof(struct in_out)) {
        printf ("snpu buffer size is need set:%d\n", sizeof(struct in_out));
        return -1;
    }
    snpu_task->module_id = 0x100;

#ifdef CONFIG_NPU_RUN_IN_FLASH
    snpu_task->cmd       = (void *)MCU_TO_DEV((unsigned int)kws_cmd_content);

#if 0
    for (int i = 0; i < 32; i++) {
        printf("%x ", *(((unsigned char *)kws_cmd_content) + i));
    }
    printf("cmd \n");

    for (int i = 0; i < 32; i++) {
        printf("%x ", *(((unsigned char *)kws_weight_content) + i));
    }
    printf("weight \n");
#endif

    snpu_task->weight    = (void *)MCU_TO_DEV((unsigned int)kws_weight_content);
    snpu_task->ops       = (void *)MCU_TO_DEV((unsigned int)(void *)(NPU_SRAM_ADDR/4*4));
    void *data = (void *)(((unsigned int)snpu_task->ops + LvpSedModelGetDataSize())/4*4);
    void *tmp_mem = (void *)(((unsigned int)snpu_task->data + LvpSedModelGetOpsSize())/4*4);
    snpu_task->data      = (void *)MCU_TO_DEV((unsigned int)data);
    snpu_task->tmp_mem   = (void *)MCU_TO_DEV((unsigned int)tmp_mem);
    memcpy(&s_snpu_task, snpu_task, sizeof(GX_SNPU_TASK));
#else
    snpu_task->cmd       = (void *)MCU_TO_DEV(s_snpu_task.cmd);
    snpu_task->weight    = (void *)MCU_TO_DEV(s_snpu_task.weight);
    snpu_task->ops       = (void *)MCU_TO_DEV(s_snpu_task.ops);
    snpu_task->data      = (void *)MCU_TO_DEV(s_snpu_task.data);
    snpu_task->tmp_mem   = (void *)MCU_TO_DEV(s_snpu_task.tmp_mem);

//    printf("\n\ncmd: 0x%x, 0x%x, 0x%x\n\n", *((unsigned char *)s_snpu_task.cmd), *((unsigned char *)s_snpu_task.cmd+1), *((unsigned char *)s_snpu_task.cmd+2));
//    printf("cmd: 0x%x, 0x%x, 0x%x\n\n", *((unsigned char *)s_snpu_task.cmd+2657), *((unsigned char *)s_snpu_task.cmd+2658), *((unsigned char *)s_snpu_task.cmd+2659));
//    printf("weight: 0x%x, 0x%x, 0x%x\n\n", *((unsigned char *)s_snpu_task.weight), *((unsigned char *)s_snpu_task.weight+1), *((unsigned char *)s_snpu_task.weight+2));
//    printf("weight: 0x%x, 0x%x, 0x%x\n\n", *((unsigned char *)s_snpu_task.weight+11631), *((unsigned char *)s_snpu_task.weight+11632), *((unsigned char *)s_snpu_task.weight+11633));
#endif

    unsigned int chipid = 0;
    gx_pmu_ctrl_get_chipid(&chipid);
    if (chipid != 0x8002) {
        snpu_task->cmd       = (void *)0;
        snpu_task->weight    = (void *)0;
        snpu_task->ops       = (void *)0;
        snpu_task->data      = (void *)0;
        snpu_task->tmp_mem   = (void *)0;
    }
    return 0;
}

const char *LvpSedModelGetVersion(void)
{
    return model_version;
}

void *LvpSedModelGetSnpuOutBuffer(void *snpu_buffer)
{
    return (void *)(((struct in_out*)snpu_buffer)->model_probOut);
}

int LvpSedModelGetOutBufferSize(void *snpu_buffer)
{
    return sizeof(((struct in_out*)snpu_buffer)->model_probOut);
}


void *LvpSedModelGetSnpuFeatsBuffer(void *snpu_buffer)
{
    return (void *)(((struct in_out*)snpu_buffer)->Feats);
}

int LvpSedModelGetSnpuFeatsSize(void *snpu_buffer)
{
    return sizeof(((struct in_out*)snpu_buffer)->Feats);
}

void *LvpSedModelGetSnpuStatesBuffer(void *snpu_buffer)
{
    return (void *)(((struct in_out*)snpu_buffer)->State_c0);
}

int LvpSedModelGetSnpustatesSize(void *snpu_buffer)
{
    return sizeof(((struct in_out*)snpu_buffer)->State_c0);
}

void *LvpSedModelGetFixStateBuffer(void)
{
    return NULL;
}

/* Grus
 * Copyright (C) 2001-2021 NationalChip Co., Ltd
 * ALL RIGHTS RESERVED!
 *
 * sed_decode.h: decode ved
 *
 */

#ifndef __SED_DECODE_H__
#define __SED_DECODE_H__

#include <autoconf.h>
typedef enum {
    SED_UNDEFINE        = 0x0,
    SED_SNORING         = 0x1,
    SED_BABYCRYING      = 0x2,
} SED_RESULT;


int SedDecodeInit(void);
unsigned int SedDecodeSed(LVP_CONTEXT *context);
int SedDecodeDone(void);
#endif /* __SED_DECODE_H__ */

#ifndef __AMR_H__
#define __AMR_H__

#include <autoconf.h>

int Amr_Decoder_Init(int sample_rate, int channels, int bytes_rate);
void Amr_Decode(const unsigned char *in, int amr_len, short *out, int pcm_len);

#endif

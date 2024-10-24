#include <stdio.h>
#ifdef USE_AMR_NB
#include "interf_dec.h"
#endif
#ifdef USE_AMR_WB
#include "dec_if.h"
#endif

typedef struct {
    int sample_rate;
    int bytes_rate;
    int channels;
    void *state;
}amr_state;

amr_state st = {
    .sample_rate = 0,
    .bytes_rate = 0,
    .channels = 0,
    .state = NULL
};

int Amr_Decoder_Init(int sample_rate, int channels, int bytes_rate)
{
    st.sample_rate = 0;
    st.bytes_rate = 0;
    st.channels = channels;
    st.state = NULL;

#ifdef CONFIG_USE_AMR_NB
    if (sample_rate == 8000 && bytes_rate == 4750) {
        st.sample_rate = sample_rate;
        st.channels = channels;
        st.bytes_rate = bytes_rate;
        st.state = Decoder_Interface_init();
    }
#endif

#ifdef CONFIG_USE_AMR_WB
    if (sample_rate == 16000 && bytes_rate == 6600) {
        st.sample_rate = sample_rate;
        st.channels = channels;
        st.bytes_rate = bytes_rate;
        st.state = D_IF_init();
    }
#endif

    if (st.state == NULL)
    {
        printf("%s failed\n", __func__);
        return -1;
    }
    return 0;
}

void Amr_Decode(const unsigned char *in, int amr_len, short *out, int pcm_len)
{
#ifdef CONFIG_USE_AMR_NB
    if (st.sample_rate == 8000 && st.state != NULL)
    {
        Decoder_Interface_Decode(st.state, in, out, 0);
    }
#endif

#ifdef CONFIG_USE_AMR_WB
    if (st.sample_rate == 16000 && st.state != NULL)
    {
        D_IF_decode(st.state, in, out, 0);
    }
#endif
}

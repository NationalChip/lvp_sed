/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */

#include "dec_if.h"
#include <stdlib.h>
#include <string.h>
#include <pvamrwbdecoder_api.h>
#include <pvamrwbdecoder.h>
#include <pvamrwbdecoder_cnst.h>
#include <dtx.h>

/* This is basically a C rewrite of decode_amr_wb.cpp */

struct state {
	void *st; /*   State structure  */
	unsigned char *pt_st;
	int16 *ScratchMem;

	uint8* iInputBuf;
	int16* iInputSampleBuf;
	int16* iOutputBuf;

	uint8 quality;
	int16 mode;
	int16 mode_old;
	int16 frame_type;

	int16 reset_flag;
	int16 reset_flag_old;
	int16 status;
	RX_State rx_state;
};

static struct state amrwb_st;
static int16 inputSampleBuf[KAMRWB_NB_BITS_MAX];

void* D_IF_init(void) {
	memset(&amrwb_st, 0, sizeof(amrwb_st));

    memset(inputSampleBuf, 0, sizeof(inputSampleBuf));
	amrwb_st.iInputSampleBuf = inputSampleBuf;
	amrwb_st.reset_flag = 0;
	amrwb_st.reset_flag_old = 1;
	amrwb_st.mode_old = 0;
	amrwb_st.rx_state.prev_ft = RX_SPEECH_GOOD;
	amrwb_st.rx_state.prev_mode = 0;
	amrwb_st.pt_st = pvDecoder_InitAmrWbMem();

	pvDecoder_AmrWb_Init(&amrwb_st.st, amrwb_st.pt_st, &amrwb_st.ScratchMem);
	return &amrwb_st;
}

void D_IF_decode(void* s, const unsigned char* in, short* out, int bfi) {
	struct state* state = (struct state*) s;

	state->mode = (in[0] >> 3) & 0x0f;
	in++;
	if (bfi) {
		state->mode = 15; // NO_DATA
	}

	state->quality = 1; /* ? */
	mime_unsorting((uint8*) in, state->iInputSampleBuf, &state->frame_type, &state->mode, state->quality, &state->rx_state);

    state->mode_old = state->mode;

    /* if homed: check if this frame is another homing frame */
    if (state->reset_flag_old == 1) {
        /* only check until end of first subframe */
        state->reset_flag = pvDecoder_AmrWb_homing_frame_test_first(state->iInputSampleBuf);
    }

	/* produce encoder homing frame if homed & input=decoder homing frame */
	if ((state->reset_flag != 0) && (state->reset_flag_old != 0)) {
		/* set homing sequence ( no need to decode anything */

		for (int16 i = 0; i < AMR_WB_PCM_FRAME; i++) {
			out[i] = EHF_MASK;
		}
	} else {
		int16 frameLength;
		state->status = pvDecoder_AmrWb(state->iInputSampleBuf,
						   out,
						   &frameLength,
						   state->st,
						   state->ScratchMem);
	}

	for (int16 i = 0; i < AMR_WB_PCM_FRAME; i++) {  /* Delete the 2 LSBs (14-bit output) */
		out[i] &= 0xfffC;
	}

	/* if not homed: check whether current frame is a homing frame */
	if (state->reset_flag_old == 0) {
		/* check whole frame */
		state->reset_flag = pvDecoder_AmrWb_homing_frame_test(state->iInputSampleBuf);
	}
	/* reset decoder if current frame is a homing frame */
	if (state->reset_flag != 0) {
		pvDecoder_AmrWb_Reset(state->st, 1);
	}
	state->reset_flag_old = state->reset_flag;

}


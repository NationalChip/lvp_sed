/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/****************************************************************************************
Portions of this file are derived from the following 3GPP standard:

    3GPP TS 26.073
    ANSI-C code for the Adaptive Multi-Rate (AMR) speech codec
    Available from http://www.3gpp.org

(C) 2004, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TTA, TTC)
Permission to distribute, modify and use this file under the standard license
terms listed above has been obtained from the copyright holder.
****************************************************************************************/
/*
------------------------------------------------------------------------------


 Filename: amrdecode.cpp

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "amrdecode.h"
#include "cnst.h"
#include "typedef.h"
#include "frame.h"
#include "sp_dec.h"
#include "wmf_to_ets.h"
#include "if2_to_ets.h"
#include "frame_type_3gpp.h"

/*----------------------------------------------------------------------------
; MACROS
; Define module specific macros here
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; DEFINES
; Include all pre-processor statements here. Include conditional
; compile variables also.
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; LOCAL FUNCTION DEFINITIONS
; Function Prototype declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; LOCAL STORE/BUFFER/POINTER DEFINITIONS
; Variable declaration - defined here and used outside this module
----------------------------------------------------------------------------*/

DRAM0_STAGE2_SRAM_ATTR static void wmf_to_ets(
    enum Frame_Type_3GPP frame_type_3gpp,
    UWord8   *wmf_input_ptr,
    Word16   *ets_output_ptr,
    CommonAmrTbls* common_amr_tbls)
{

    Word16 i;
    const Word16* const* reorderBits_ptr = common_amr_tbls->reorderBits_ptr;
    const Word16* numOfBits_ptr = common_amr_tbls->numOfBits_ptr;

    /*
     * The following section of code accesses bits in the WMF method of
     * bit ordering. Each bit is given its own location in the buffer pointed
     * to by ets_output_ptr. If the frame_type_3gpp is less than MRDTX then
     * the elements are reordered within the buffer pointed to by ets_output_ptr.
     */

        /* The table numOfBits[] can be found in bitreorder.c. */
    for (i = numOfBits_ptr[frame_type_3gpp] - 1; i >= 0; i--)
    {
        /* The table reorderBits[][] can be found in bitreorder.c. */
        ets_output_ptr[reorderBits_ptr[frame_type_3gpp][i]] =
            (wmf_input_ptr[i>>3] >> ((~i) & 0x7)) & 0x01;
    }

    return;
}


DRAM0_STAGE2_SRAM_ATTR Word16 AMRDecode(
    void                      *state_data,
    enum Frame_Type_3GPP      frame_type,
    UWord8                    *speech_bits_ptr,
    Word16                    *raw_pcm_buffer,
    bitstream_format          input_format
)
{
    enum Mode mode = (enum Mode)MR475;
    enum RXFrameType rx_type = RX_NO_DATA;
    Word16 dec_ets_input_bfr[MAX_SERIAL_SIZE];
    Word16 byte_offset = -1;

    /* Type cast state_data to Speech_Decode_FrameState rather than passing
     * that structure type to this function so the structure make up can't
     * be viewed from higher level functions than this.
     */
    Speech_Decode_FrameState *decoder_state
    = (Speech_Decode_FrameState *) state_data;

    /* Determine type of de-formatting */
    /* WMF or IF2 frames */
    if (input_format == MIME_IETF)
    {
        /* Convert incoming packetized raw WMF data to ETS format */
        wmf_to_ets(frame_type, speech_bits_ptr, dec_ets_input_bfr, &(decoder_state->decoder_amrState.common_amr_tbls));

        /* Address offset of the start of next frame */
        byte_offset = 12;
    }

    /* At this point, input data is in ETS format     */
    /* Determine AMR codec mode and AMR RX frame type */
    mode = (enum Mode) frame_type;
    rx_type = RX_SPEECH_GOOD;

    /* ETS frames */
    /* Proceed with decoding frame, if there are no errors */
    if (byte_offset != -1)
    {
        /* Decode a 20 ms frame */

        /* Use PV version of sp_dec.c */
        GSMFrameDecode(decoder_state, mode, dec_ets_input_bfr, rx_type,
                       raw_pcm_buffer);

        /* Save mode for next frame */
        decoder_state->prev_mode = mode;
    }

    return (byte_offset);
}




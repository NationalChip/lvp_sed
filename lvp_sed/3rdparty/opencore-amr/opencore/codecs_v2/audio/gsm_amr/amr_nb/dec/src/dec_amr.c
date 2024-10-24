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

 Filename: dec_amr.cpp
 Funtions: Decoder_amr_init
           Decoder_amr_reset
           Decoder_amr

------------------------------------------------------------------------------
 MODULE DESCRIPTION

 This file contains the function used to decode one speech frame using a given
 codec mode. The functions used to initialize, reset, and exit are also
 included in this file.

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "dec_amr.h"
#include "typedef.h"
#include "cnst.h"
#include "set_zero.h"
#include "syn_filt.h"
#include "d_plsf.h"
#include "agc.h"
#include "int_lpc.h"
#include "dec_gain.h"
#include "dec_lag3.h"
#include "d2_9pf.h"
#include "pred_lt.h"
#include "d_gain_p.h"
#include "d_gain_c.h"
#include "dec_gain.h"
#include "ec_gains.h"
#include "ph_disp.h"
#include "c_g_aver.h"
#include "int_lsf.h"
#include "lsp_lsf.h"
#include "lsp_avg.h"
#include "sqrt_l.h"
#include "frame.h"
#include "basic_op.h"
#include "oscl_mem.h"

#define NB_PULSE  2

DRAM0_STAGE2_SRAM_ATTR static void decode_2i40_9bits(
    Word16 subNr,  /* i : subframe number                          */
    Word16 sign,   /* i : signs of 2 pulses.                       */
    Word16 index,  /* i : Positions of the 2 pulses.               */
    const Word16* startPos_ptr, /*  i: ptr to read only table          */
    Word16 cod[],  /* o : algebraic (fixed) codebook excitation    */
    Flag  *pOverflow  /* o : Flag set when overflow occurs         */
)
{
    Word16 i;
    Word16 j;
    Word16 k;

    Word16 pos[NB_PULSE];

    /* Decode the positions */
    /* table bit  is the MSB */

    j = (Word16)(index & 64);

    j >>= 3;

    i = index & 7;

    k =
        shl(
            subNr,
            1,
            pOverflow);

    k += j;

    /* pos0 =i*5+startPos_ptr[j*8+subNr*2] */
    pos[0] = i * 5 + startPos_ptr[k++];


    index >>= 3;

    i = index & 7;

    /* pos1 =i*5+startPos_ptr[j*8+subNr*2 + 1] */
    pos[1] = i * 5 + startPos_ptr[k];


    /* decode the signs  and build the codeword */

    for (i = L_SUBFR - 1; i >= 0; i--)
    {
        cod[i] = 0;
    }

    for (j = 0; j < NB_PULSE; j++)
    {
        i = sign & 0x1;

        /* This line is equivalent to...
         *
         *
         *  if (i == 1)
         *  {
         *      cod[pos[j]] = 8191;
         *  }
         *  if (i == 0)
         *  {
         *      cod[pos[j]] = -8192;
         *  }
         */

        cod[pos[j]] = i * 16383 - 8192;

        sign >>= 1;
    }

    return;
}


Word16 Decoder_amr_init(Decoder_amrState *s)
{
    if (s == (Decoder_amrState *) NULL)
    {
        /* fprint(stderr, "Decoder_amr_init: invalid parameter\n");  */
        return(-1);
    }

    get_const_tbls(&s->common_amr_tbls);

    s->T0_lagBuff = 40;
    s->voicedHangover = 0;

    /* Initialize overflow Flag */

    s->overflow = 0;

    D_plsf_reset(&s->lsfState, s->common_amr_tbls.mean_lsf_5_ptr);
    ec_gain_pitch_reset(&s->ec_gain_p_st);
    ec_gain_code_reset(&s->ec_gain_c_st);
    Cb_gain_average_reset(&s->Cb_gain_averState);
    lsp_avg_reset(&s->lsp_avg_st, s->common_amr_tbls.mean_lsf_5_ptr);
    ph_disp_reset(&s->ph_disp_st);
    gc_pred_reset(&s->pred_state);

    Decoder_amr_reset(s, MR475);

    return(0);
}

/****************************************************************************/


Word16 Decoder_amr_reset(Decoder_amrState *state, enum Mode mode)
{
    if (state == (Decoder_amrState *) NULL || mode != MR475)
    {
        /* fprint(stderr, "Decoder_amr_reset: invalid parameter\n");  */
        return(-1);
    }

    /* Initialize static pointer */
    state->exc = state->old_exc + PIT_MAX + L_INTERPOL;

    /* Static vectors to zero */
    oscl_memset(state->old_exc, 0, sizeof(Word16)*(PIT_MAX + L_INTERPOL));

    oscl_memset(state->mem_syn, 0, sizeof(Word16)*M);
    /* initialize pitch sharpening */
    state->sharp = SHARPMIN;
    state->old_T0 = 40;

    /* Initialize overflow Flag */

    state->overflow = 0;

    /* Initialize state->lsp_old [] */

    state->lsp_old[0] = 30000;
    state->lsp_old[1] = 26000;
    state->lsp_old[2] = 21000;
    state->lsp_old[3] = 15000;
    state->lsp_old[4] = 8000;
    state->lsp_old[5] = 0;
    state->lsp_old[6] = -8000;
    state->lsp_old[7] = -15000;
    state->lsp_old[8] = -21000;
    state->lsp_old[9] = -26000;

    /* Initialize memories of bad frame handling */
    state->prev_bf = 0;
    state->prev_pdf = 0;
    state->state = 0;

    state->T0_lagBuff = 40;
    state->voicedHangover = 0;

    Cb_gain_average_reset(&(state->Cb_gain_averState));
    lsp_avg_reset(&(state->lsp_avg_st), state->common_amr_tbls.mean_lsf_5_ptr);
    D_plsf_reset(&(state->lsfState), state->common_amr_tbls.mean_lsf_5_ptr);
    ec_gain_pitch_reset(&(state->ec_gain_p_st));
    ec_gain_code_reset(&(state->ec_gain_c_st));

    gc_pred_reset(&(state->pred_state));

    ph_disp_reset(&(state->ph_disp_st));

    return(0);
}

/****************************************************************************/


DRAM0_STAGE2_SRAM_ATTR void Decoder_amr(
    Decoder_amrState *st,      /* i/o : State variables                   */
    enum Mode mode,            /* i   : AMR mode                          */
    Word16 parm[],             /* i   : vector of synthesis parameters
                                        (PRM_SIZE)                        */
    enum RXFrameType frame_type, /* i   : received frame type             */
    Word16 synth[],            /* o   : synthesis speech (L_FRAME)        */
    Word16 A_t[]               /* o   : decoded LP filter in 4 subframes
                                        (AZ_SIZE)                         */
)
{
    /* LPC coefficients */

    Word16 *Az;                /* Pointer on A_t */

    /* LSPs */

    Word16 lsp_new[M];

    /* LSFs */

    Word16 prev_lsf[M];
    Word16 lsf_i[M];

    /* Algebraic codevector */

    Word16 code[L_SUBFR];

    /* excitation */

    Word16 excp[L_SUBFR];
    Word16 exc_enhanced[L_SUBFR];

    /* Scalars */

    Word16 i;
    Word16 i_subfr;
    Word16 T0;
    Word16 T0_frac;
    Word16 index;
    Word16 index_mr475 = 0;
    Word16 gain_pit;
    Word16 gain_code;
    Word16 gain_code_mix;
    Word16 pit_sharp;
    Word16 pit_flag;
    Word16 pitch_fac;
    Word16 t0_min;
    Word16 t0_max;
    Word16 delta_frc_low;
    Word16 delta_frc_range;
    Word16 tmp_shift;
    Word16 temp;
    Word32 L_temp;
    Word16 subfrNr;
    Word16 evenSubfr = 0;

    Word16 pdfi = 0;  /* potential degraded bad frame flag                  */

    Flag   *pOverflow = &(st->overflow);     /* Overflow flag            */

    if (frame_type != RX_SPEECH_GOOD)
        return;



    if (st->state == 6)

    {
        st->state = 5;
    }
    else
    {
        st->state = 0;
    }


    if (st->state > 6)
    {
        st->state = 6;
    }

    /* If this frame is the first speech frame after CNI period,     */
    /* set the BFH state machine to an appropriate state depending   */
    /* on whether there was DTX muting before start of speech or not */
    /* If there was DTX muting, the first speech frame is muted.     */
    /* If there was no DTX muting, the first speech frame is not     */
    /* muted. The BFH state machine starts from state 5, however, to */
    /* keep the audible noise resulting from a SID frame which is    */
    /* erroneously interpreted as a good speech frame as small as    */
    /* possible (the decoder output in this case is quickly muted)   */


    /* save old LSFs for CB gain smoothing */
    oscl_memmove((void *)prev_lsf, st->lsfState.past_lsf_q, M*sizeof(*st->lsfState.past_lsf_q));

    /* decode LSF parameters and generate interpolated lpc coefficients
       for the 4 subframes */

    D_plsf_3(
            &(st->lsfState),
            mode,
            0,
            parm,
            &st->common_amr_tbls,
            lsp_new,
            pOverflow);

    /* Advance synthesis parameters pointer */
    parm += 3;

    Int_lpc_1to3(
            st->lsp_old,
            lsp_new,
            A_t,
            pOverflow);

    /* update the LSPs for the next frame */
    for (i = 0; i < M; i++)
    {
        st->lsp_old[i] = lsp_new[i];
    }

    /*------------------------------------------------------------------------*
     *          Loop for every subframe in the analysis frame                 *
     *------------------------------------------------------------------------*
     * The subframe size is L_SUBFR and the loop is repeated L_FRAME/L_SUBFR  *
     *  times                                                                 *
     *     - decode the pitch delay                                           *
     *     - decode algebraic code                                            *
     *     - decode pitch and codebook gains                                  *
     *     - find the excitation and compute synthesis speech                 *
     *------------------------------------------------------------------------*/

    /* pointer to interpolated LPC parameters */
    Az = A_t;

    evenSubfr = 0;
    subfrNr = -1;
    for (i_subfr = 0; i_subfr < L_FRAME; i_subfr += L_SUBFR)
    {
        subfrNr += 1;
        evenSubfr = 1 - evenSubfr;

        /* flag for first and 3th subframe */
        pit_flag = i_subfr;


        /* pitch index */
        index = *parm++;

        /*-------------------------------------------------------*
         * - decode pitch lag and find adaptive codebook vector. *
         *-------------------------------------------------------*/

        /* flag4 indicates encoding with 4 bit resolution;     */
        /* this is needed for mode MR475, */


        /*-------------------------------------------------------*
         * - get ranges for the t0_min and t0_max                *
         * - only needed in delta decoding                       *
         *-------------------------------------------------------*/

        delta_frc_low = 5;
        delta_frc_range = 9;

        t0_min = st->old_T0 - delta_frc_low;

        if (t0_min < PIT_MIN)
        {
            t0_min = PIT_MIN;
        }
        t0_max = t0_min + delta_frc_range;

        if (t0_max > PIT_MAX)
        {
            t0_max = PIT_MAX;
            t0_min = t0_max - delta_frc_range;
        }

        Dec_lag3(index, t0_min, t0_max, pit_flag, st->old_T0,
                &T0, &T0_frac, pOverflow);

        st->T0_lagBuff = T0;

        Pred_lt_3or6(st->exc, T0, T0_frac, L_SUBFR, 1, pOverflow);

        /*-------------------------------------------------------*
         * - (MR122 only: Decode pitch gain.)                    *
         * - Decode innovative codebook.                         *
         * - set pitch sharpening factor                         *
         *-------------------------------------------------------*/
        index = *parm++;        /* index of position */
        i = *parm++;            /* signs             */

        decode_2i40_9bits(subfrNr, i, index, st->common_amr_tbls.startPos_ptr, code, pOverflow);

        L_temp = (Word32)st->sharp << 1;
        if (L_temp != (Word32)((Word16) L_temp))
        {
            pit_sharp = (st->sharp > 0) ? MAX_16 : MIN_16;
        }
        else
        {
            pit_sharp = (Word16) L_temp;
        }
        /*-------------------------------------------------------*
         * - Add the pitch contribution to code[].               *
         *-------------------------------------------------------*/
        for (i = T0; i < L_SUBFR; i++)
        {
            temp = mult(*(code + i - T0), pit_sharp, pOverflow);
            *(code + i) = add_16(*(code + i), temp, pOverflow);

        }

        /*------------------------------------------------------------*
         * - Decode codebook gain (MR122) or both pitch               *
         *   gain and codebook gain (all others)                      *
         * - Update pitch sharpening "sharp" with quantized gain_pit  *
         *------------------------------------------------------------*/
            /* read and decode pitch and code gain */

        if (evenSubfr != 0)
        {
            index_mr475 = *parm++;         /* index of gain(s) */
        }

        Dec_gain(
                &(st->pred_state),
                mode,
                index_mr475,
                code,
                evenSubfr,
                &gain_pit,
                &gain_code,
                pOverflow);

        ec_gain_pitch_update(
                &st->ec_gain_p_st,
                0,
                &gain_pit,
                pOverflow);

        ec_gain_code_update(
                &st->ec_gain_c_st,
                0,
                &gain_code);

        pit_sharp = gain_pit;

        if (pit_sharp > SHARPMAX)
        {
            pit_sharp = SHARPMAX;
        }


        /* store pitch sharpening for next subframe             */
        /* (for modes which use the previous pitch gain for     */
        /* pitch sharpening in the search phase)                */
        /* do not update sharpening in even subframes for MR475 */
        if (evenSubfr == 0)
        {
            st->sharp = gain_pit;

            if (st->sharp > SHARPMAX)
            {
                st->sharp = SHARPMAX;
            }
        }

        pit_sharp = shl(pit_sharp, 1, pOverflow);

        if (pit_sharp > 16384)
        {
            for (i = 0; i < L_SUBFR; i++)
            {
                temp = mult(st->exc[i], pit_sharp, pOverflow);
                L_temp = L_mult(temp, gain_pit, pOverflow);

                *(excp + i) = pv_round(L_temp, pOverflow);
            }
        }

        /*-------------------------------------------------------*
         * - Store list of LTP gains needed in the source        *
         *   characteristic detector (SCD)                       *
         *-------------------------------------------------------*/

        /*-------------------------------------------------------*
        * - Limit gain_pit if in background noise and BFI       *
        *   for MR475 *
        *-------------------------------------------------------*/

        /*-------------------------------------------------------*
         *  Calculate CB mixed gain                              *
         *-------------------------------------------------------*/
        Int_lsf(
            prev_lsf,
            st->lsfState.past_lsf_q,
            i_subfr,
            lsf_i,
            pOverflow);

        gain_code_mix =
            Cb_gain_average(
                &(st->Cb_gain_averState),
                mode,
                gain_code,
                lsf_i,
                st->lsp_avg_st.lsp_meanSave,
                pOverflow);

        /*-------------------------------------------------------*
         * - Find the total excitation.                          *
         * - Find synthesis speech corresponding to st->exc[].   *
         *-------------------------------------------------------*/
        pitch_fac = gain_pit;
        tmp_shift = 1;

        /* copy unscaled LTP excitation to exc_enhanced (used in phase
         * dispersion below) and compute total excitation for LTP feedback
         */
        for (i = 0; i < L_SUBFR; i++)
        {
            exc_enhanced[i] = st->exc[i];

            /* st->exc[i] = gain_pit*st->exc[i] + gain_code*code[i]; */
            L_temp = L_mult(st->exc[i], pitch_fac, pOverflow);
            /* 12.2: Q0 * Q13 */
            /*  7.4: Q0 * Q14 */
            L_temp = L_mac(L_temp, code[i], gain_code, pOverflow);
            /* 12.2: Q12 * Q1 */
            /*  7.4: Q13 * Q1 */
            L_temp = L_shl(L_temp, tmp_shift, pOverflow);     /* Q16 */
            st->exc[i] = pv_round(L_temp, pOverflow);
        }

        /*-------------------------------------------------------*
         * - Adaptive phase dispersion                           *
         *-------------------------------------------------------*/
        ph_disp_release(&(st->ph_disp_st)); /* free phase dispersion adaption */

        /* apply phase dispersion to innovation (if enabled) and
           compute total excitation for synthesis part           */
        ph_disp(
            &(st->ph_disp_st),
            mode,
            exc_enhanced,
            gain_code_mix,
            gain_pit,
            code,
            pitch_fac,
            tmp_shift,
            &(st->common_amr_tbls),
            pOverflow);

        /*-------------------------------------------------------*
         * - The Excitation control module are active during BFI.*
         * - Conceal drops in signal energy if in bg noise.      *
         *-------------------------------------------------------*/
        L_temp = 0;
        for (i = 0; i < L_SUBFR; i++)
        {
            L_temp = L_mac(L_temp, *(exc_enhanced + i), *(exc_enhanced + i), pOverflow);
        }

        /* excEnergy = sqrt(L_temp) in Q0 */
        if (L_temp < 0)
        {
            L_temp = ~((~L_temp) >> 1);
        }
        else
        {
            L_temp = L_temp >> 1;
        }

        L_temp = sqrt_l_exp(L_temp, &temp, pOverflow);
        /* To cope with 16-bit and scaling in ex_ctrl() */
        L_temp = L_shr(L_temp, (Word16)((temp >> 1) + 15), pOverflow);

        /*-------------------------------------------------------*
         * Excitation control module end.                        *
         *-------------------------------------------------------*/
        if (pit_sharp > 16384)
        {
            for (i = 0; i < L_SUBFR; i++)
            {
                *(excp + i) = add_16(*(excp + i), *(exc_enhanced + i), pOverflow);

            }
            agc2(exc_enhanced, excp, L_SUBFR, pOverflow);
            Syn_filt(Az, excp, &synth[i_subfr], L_SUBFR,
                     st->mem_syn, 0);
        }
        else
        {
            Syn_filt(Az, exc_enhanced, &synth[i_subfr], L_SUBFR,
                     st->mem_syn, 0);
        }
        *pOverflow = 0;

        oscl_memmove((void *)st->mem_syn, &synth[i_subfr+L_SUBFR-M], M*sizeof(synth[0]));

        /*--------------------------------------------------*
         * Update signal for next frame.                    *
         * -> shift to the left by L_SUBFR  st->exc[]       *
         *--------------------------------------------------*/

        oscl_memmove((void *)&st->old_exc[0], &st->old_exc[L_SUBFR], (PIT_MAX + L_INTERPOL)*sizeof(st->old_exc[0]));

        /* interpolated LPC parameters for next subframe */
        Az += MP1;

        /* store T0 for next subframe */
        st->old_T0 = T0;
    }

    /*-------------------------------------------------------*
     * Call the Source Characteristic Detector which updates *
     * st->inBackgroundNoise and st->voicedHangover.         *
     *-------------------------------------------------------*/

    /* store bfi for next subframe */
    st->prev_bf = 0;
    st->prev_pdf = pdfi;

    /*--------------------------------------------------*
     * Calculate the LSF averages on the eight          *
     * previous frames                                  *
     *--------------------------------------------------*/
    lsp_avg(
        &(st->lsp_avg_st),
        st->lsfState.past_lsf_q,
        pOverflow);

//    return(0);
}

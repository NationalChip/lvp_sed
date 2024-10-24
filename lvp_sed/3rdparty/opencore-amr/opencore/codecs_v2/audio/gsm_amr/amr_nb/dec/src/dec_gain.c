#include "dec_gain.h"
#include "typedef.h"
#include "mode.h"
#include "cnst.h"
#include "pow2.h"
#include "log2.h"
#include "basic_op.h"
#include "qua_gain_tbl.h"
#include "qgain475_tab.h"
#include <stdio.h>

#define NPRED 4  /* number of prediction taps */

/* average innovation energy.                               */
/* MEAN_ENER  = 36.0/constant, constant = 20*Log10(2)       */
#define MEAN_ENER_MR122  783741L  /* 36/(20*log10(2)) (Q17) */

/* minimum quantized energy: -14 dB */
#define MIN_ENERGY       -14336       /* 14                 Q10 */
#define MIN_ENERGY_MR122  -2381       /* 14 / (20*log10(2)) Q10 */

/*----------------------------------------------------------------------------
; LOCAL FUNCTION DEFINITIONS
; Function Prototype declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; LOCAL VARIABLE DEFINITIONS
; Variable declaration - defined here and used outside this module
----------------------------------------------------------------------------*/

/* MA prediction coefficients (Q13) */
static const Word16 pred[NPRED] = {5571, 4751, 2785, 1556};

/* MA prediction coefficients (Q6)  */


Word16 gc_pred_reset(gc_predState *state)
{
    Word16 i;

    if (state == (gc_predState *) NULL)
    {
        /* fprintf(stderr, "gc_pred_reset: invalid parameter\n"); */
        return -1;
    }

    for (i = 0; i < NPRED; i++)
    {
        state->past_qua_en[i] = MIN_ENERGY;
        state->past_qua_en_MR122[i] = MIN_ENERGY_MR122;
    }

    return(0);
}

/****************************************************************************/


void gc_pred(
    gc_predState *st,   /* i/o: State struct                           */
    enum Mode mode,     /* i  : AMR mode                               */
    Word16 *code,       /* i  : innovative codebook vector (L_SUBFR)   */
    /*      MR122: Q12, other modes: Q13           */
    Word16 *exp_gcode0, /* o  : exponent of predicted gain factor, Q0  */
    Word16 *frac_gcode0,/* o  : fraction of predicted gain factor  Q15 */
    /*      (only calculated for MR795)            */
    Flag   *pOverflow
)
{
    register Word16 i;
    register Word32 L_temp1, L_temp2;
    register Word32 L_tmp;
    Word32 ener_code;
    Word16 exp, frac;
    Word16 exp_code, gcode0;
    Word16 tmp;
    Word16 *p_code = &code[0];

    if (mode != MR475)
        return;

    /*-------------------------------------------------------------------*
     *  energy of code:                                                  *
     *  ~~~~~~~~~~~~~~~                                                  *
     *  ener_code = sum(code[i]^2)                                       *
     *-------------------------------------------------------------------*/
    ener_code = 0;

    /* MR122:  Q12*Q12 -> Q25 */
    /* others: Q13*Q13 -> Q27 */

    for (i = L_SUBFR >> 2; i != 0; i--)
    {
        tmp = *(p_code++);
        ener_code += ((Word32) tmp * tmp) >> 3;
        tmp = *(p_code++);
        ener_code += ((Word32) tmp * tmp) >> 3;
        tmp = *(p_code++);
        ener_code += ((Word32) tmp * tmp) >> 3;
        tmp = *(p_code++);
        ener_code += ((Word32) tmp * tmp) >> 3;
    }

    ener_code <<= 4;

    if ((ener_code >> 31))     /*  Check for saturation */
    {
        ener_code = MAX_32;
    }

    {
        /*-----------------------------------------------------------------*
         *  Compute: means_ener - 10log10(ener_code/ L_sufr)               *
         *-----------------------------------------------------------------*/

        exp_code = norm_l(ener_code);
        ener_code = L_shl(ener_code, exp_code, pOverflow);

        /* Log2 = log2 + 27 */
        Log2_norm(ener_code, exp_code, &exp, &frac);

        /* fact = 10/log2(10) = 3.01 = 24660 Q13 */
        /* Q0.Q15 * Q13 -> Q14 */

        L_temp2 = (((Word32) exp) * -24660) << 1;
        L_tmp = (((Word32) frac) * -24660) >> 15;

        /* Sign-extend resulting product */
        if (L_tmp & (Word32) 0x00010000L)
        {
            L_tmp = L_tmp | (Word32) 0xffff0000L;
        }

        L_tmp = L_tmp << 1;
        L_tmp = L_add(L_tmp, L_temp2, pOverflow);


        /*   L_tmp = means_ener - 10log10(ener_code/L_SUBFR)
         *         = means_ener - 10log10(ener_code) + 10log10(L_SUBFR)
         *         = K - fact * Log2(ener_code)
         *         = K - fact * log2(ener_code) - fact*27
         *
         *   ==> K = means_ener + fact*27 + 10log10(L_SUBFR)
         *
         *   means_ener =       33    =  540672    Q14  (MR475, MR515, MR59)
         *   means_ener =       28.75 =  471040    Q14  (MR67)
         *   means_ener =       30    =  491520    Q14  (MR74)
         *   means_ener =       36    =  589824    Q14  (MR795)
         *   means_ener =       33    =  540672    Q14  (MR102)
         *   10log10(L_SUBFR) = 16.02 =  262481.51 Q14
         *   fact * 27                = 1331640    Q14
         *   -----------------------------------------
         *   (MR475, MR515, MR59)   K = 2134793.51 Q14 ~= 16678 * 64 * 2
         *   (MR67)                 K = 2065161.51 Q14 ~= 32268 * 32 * 2
         *   (MR74)                 K = 2085641.51 Q14 ~= 32588 * 32 * 2
         *   (MR795)                K = 2183945.51 Q14 ~= 17062 * 64 * 2
         *   (MR102)                K = 2134793.51 Q14 ~= 16678 * 64 * 2
         */

        {
            /* mean = 33 dB */
            L_temp2 = (Word32) 16678 << 7;
            L_tmp = L_add(L_tmp, L_temp2, pOverflow);     /* Q14 */
        }

        /*-------------------------------------------------------------*
         * Compute gcode0.                                              *
         *  = Sum(i=0,3) pred[i]*past_qua_en[i] - ener_code + mean_ener *
         *--------------------------------------------------------------*/
        /* Q24 */
        if (L_tmp > (Word32) 0X001fffffL)
        {
            *pOverflow = 1;
            L_tmp = MAX_32;
        }
        else if (L_tmp < -2097152)
        {
            *pOverflow = 1;
            L_tmp = MIN_32;
        }
        else
        {
            L_tmp = L_tmp << 10;
        }

        for (i = 0; i < 4; i++)
        {
            L_temp2 = ((((Word32) pred[i]) * st->past_qua_en[i]) << 1);
            L_tmp = L_add(L_tmp, L_temp2, pOverflow);  /* Q13 * Q10 -> Q24 */
        }

        gcode0 = (Word16)(L_tmp >> 16);               /* Q8  */

        /*-----------------------------------------------------------*
         * gcode0 = pow(10.0, gcode0/20)                             *
         *        = pow(2, 3.3219*gcode0/20)                         *
         *        = pow(2, 0.166*gcode0)                             *
         *-----------------------------------------------------------*/

        /* 5439 Q15 = 0.165985                                       */
        /* (correct: 1/(20*log10(2)) 0.166096 = 5443 Q15)            */

        {
            L_tmp = (((Word32) gcode0) * 5443) << 1;  /* Q8 * Q15 -> Q24 */
        }

        if (L_tmp < 0)
        {
            L_tmp = ~((~L_tmp) >> 8);
        }
        else
        {
            L_tmp = L_tmp >> 8;     /* -> Q16 */
        }

        *exp_gcode0 = (Word16)(L_tmp >> 16);
        if (L_tmp < 0)
        {
            L_temp1 = ~((~L_tmp) >> 1);
        }
        else
        {
            L_temp1 = L_tmp >> 1;
        }
        L_temp2 = (Word32) * exp_gcode0 << 15;
        *frac_gcode0 = (Word16)(L_sub(L_temp1, L_temp2, pOverflow));
        /* -> Q0.Q15 */
    }

    return;
}


OSCL_EXPORT_REF void gc_pred_update(
    gc_predState *st,      /* i/o: State struct                     */
    Word16 qua_ener_MR122, /* i  : quantized energy for update, Q10 */
    /*      (log2(qua_err))                  */
    Word16 qua_ener        /* i  : quantized energy for update, Q10 */
    /*      (20*log10(qua_err))              */
)
{
    st->past_qua_en[3] = st->past_qua_en[2];
    st->past_qua_en_MR122[3] = st->past_qua_en_MR122[2];

    st->past_qua_en[2] = st->past_qua_en[1];
    st->past_qua_en_MR122[2] = st->past_qua_en_MR122[1];

    st->past_qua_en[1] = st->past_qua_en[0];
    st->past_qua_en_MR122[1] = st->past_qua_en_MR122[0];

    st->past_qua_en_MR122[0] = qua_ener_MR122; /*    log2 (qua_err), Q10 */

    st->past_qua_en[0] = qua_ener;            /* 20*log10(qua_err), Q10 */

    return;
}


OSCL_EXPORT_REF void gc_pred_average_limited(
    gc_predState *st,       /* i: State struct                    */
    Word16 *ener_avg_MR122, /* o: everaged quantized energy,  Q10 */
    /*    (log2(qua_err))                 */
    Word16 *ener_avg,       /* o: averaged quantized energy,  Q10 */
    /*    (20*log10(qua_err))             */
    Flag *pOverflow
)
{
    Word16 av_pred_en;
    register Word16 i;

    /* do average in MR122 mode (log2() domain) */
    av_pred_en = 0;
    for (i = 0; i < NPRED; i++)
    {
        av_pred_en =
            add_16(av_pred_en, st->past_qua_en_MR122[i], pOverflow);
    }

    /* av_pred_en = 0.25*av_pred_en  (with sign-extension)*/
    if (av_pred_en < 0)
    {
        av_pred_en = (av_pred_en >> 2) | 0xc000;
    }
    else
    {
        av_pred_en >>= 2;
    }

    /* if (av_pred_en < -14/(20Log10(2))) av_pred_en = .. */
    if (av_pred_en < MIN_ENERGY_MR122)
    {
        av_pred_en = MIN_ENERGY_MR122;
    }
    *ener_avg_MR122 = av_pred_en;

    /* do average for other modes (20*log10() domain) */
    av_pred_en = 0;
    for (i = 0; i < NPRED; i++)
    {
        av_pred_en = add_16(av_pred_en, st->past_qua_en[i], pOverflow);
    }

    /* av_pred_en = 0.25*av_pred_en  (with sign-extension)*/
    if (av_pred_en < 0)
    {
        av_pred_en = (av_pred_en >> 2) | 0xc000;
    }
    else
    {
        av_pred_en >>= 2;
    }

    /* if (av_pred_en < -14) av_pred_en = .. */
    if (av_pred_en < MIN_ENERGY)
    {
        av_pred_en = MIN_ENERGY;
    }
    *ener_avg = av_pred_en;
}

void Dec_gain(
    gc_predState *pred_state, /* i/o: MA predictor state           */
    enum Mode mode,           /* i  : AMR mode                     */
    Word16 index,             /* i  : index of quantization.       */
    Word16 code[],            /* i  : Innovative vector.           */
    Word16 evenSubfr,         /* i  : Flag for even subframes      */
    Word16 * gain_pit,        /* o  : Pitch gain.                  */
    Word16 * gain_cod,        /* o  : Code gain.                   */
    Flag   * pOverflow
)
{
    Word16 frac;
    Word16 gcode0;
    Word16 exp;
    Word16 qua_ener;
    Word16 qua_ener_MR122;
    Word16 g_code;
    Word32 L_tmp;
    Word16 temp1;
    Word16 temp2;

    /* Read the quantized gains (table depends on mode) */
    index = shl(index, 2, pOverflow);

    index += (1 ^ evenSubfr) << 1; /* evenSubfr is 0 or 1 */

    if (index > (MR475_VQ_SIZE*4 - 2))
    {
        index = (MR475_VQ_SIZE * 4 - 2); /* avoid possible buffer overflow */
    }

    *gain_pit = table_gain_MR475[index];
    g_code = table_gain_MR475[index+1];

    /*---------------------------------------------------------*
     *  calculate predictor update values (not stored in 4.75  *
     *  quantizer table to save space):                        *
     *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  *
     *                                                         *
     *   qua_ener       = log2(g)                              *
     *   qua_ener_MR122 = 20*log10(g)                          *
     *---------------------------------------------------------*/

    /* Log2(x Q12) = log2(x) + 12 */
    temp1 = g_code;
    Log2(temp1, &exp, &frac, pOverflow);
    exp -= 12;

    temp1 = shr_r(frac, 5, pOverflow);
    temp2 = shl(exp, 10, pOverflow);
    qua_ener_MR122 = add_16(temp1, temp2, pOverflow);

    /* 24660 Q12 ~= 6.0206 = 20*log10(2) */
    L_tmp = Mpy_32_16(exp, frac, 24660, pOverflow);
    L_tmp = L_shl(L_tmp, 13, pOverflow);
    qua_ener = pv_round(L_tmp, pOverflow);
    /* Q12 * Q0 = Q13 -> Q10 */

    gc_pred(pred_state, mode, code, &exp, &frac, pOverflow);

    gcode0 = (Word16) Pow2(14, frac, pOverflow);

    /*------------------------------------------------------------------*
     *  read quantized gains, update table of past quantized energies   *
     *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   *
     *  st->past_qua_en(Q10) = 20 * Log10(g_fac) / constant             *
     *                       = Log2(g_fac)                              *
     *                       = qua_ener                                 *
     *                                           constant = 20*Log10(2) *
     *------------------------------------------------------------------*/

    L_tmp = L_mult(g_code, gcode0, pOverflow);
    temp1 = 10 - exp;
    L_tmp = L_shr(L_tmp, temp1, pOverflow);
    *gain_cod = (Word16)(L_tmp >> 16);

    /* update table of past quantized energies */

    gc_pred_update(pred_state, qua_ener_MR122, qua_ener);

    return;
}








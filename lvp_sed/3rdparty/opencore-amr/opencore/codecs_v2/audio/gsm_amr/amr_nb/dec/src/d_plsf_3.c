#include "d_plsf.h"
#include "typedef.h"
#include "basic_op.h"
#include "lsp_lsf.h"
#include "reorder.h"
#include "oscl_mem.h"
#include "q_plsf_3_tbl.h"


#define ALPHA     29491     /* ALPHA    ->  0.9                            */
#define ONE_ALPHA 3277      /* ONE_ALPHA-> (1.0-ALPHA)                     */



extern const Word16 table[];
extern const Word16 slope[];

    /*--------------------------------------------------------------------------*/

static OSCL_EXPORT_REF void Lsf_lsp(
    Word16 lsf[],       /* (i) : lsf[m] normalized (range: 0.0<=val<=0.5) */
    Word16 lsp[],       /* (o) : lsp[m] (range: -1<=val<1)                */
    Word16 m           /* (i) : LPC order                                */
)
{
    Word16 i, ind, offset;
    Word32 L_tmp;

    for (i = 0; i < m; i++)
    {
        ind = lsf[i] >> 8;           /* ind    = b8-b15 of lsf[i] */
        offset = lsf[i] & 0x00ff;    /* offset = b0-b7  of lsf[i] */

        /* lsp[i] = table[ind]+ ((table[ind+1]-table[ind])*offset) / 256 */

        L_tmp = ((Word32)(table[ind + 1] - table[ind]) * offset) >> 8;
        lsp[i] = table[ind] + (Word16) L_tmp;

    }

    return;
}

static OSCL_EXPORT_REF void Reorder_lsf(
    Word16 *lsf,        /* (i/o)    : vector of LSFs   (range: 0<=val<=0.5) */
    Word16 min_dist,    /* (i)      : minimum required distance             */
    Word16 n,           /* (i)      : LPC order                             */
    Flag   *pOverflow   /* (i/o)    : Overflow flag                         */
)
{
    Word16 i;
    Word16 lsf_min;
    Word16 *p_lsf = &lsf[0];
    OSCL_UNUSED_ARG(pOverflow);

    lsf_min = min_dist;
    for (i = 0; i < n; i++)
    {
        if (*(p_lsf) < lsf_min)
        {
            *(p_lsf++) = lsf_min;
            lsf_min +=  min_dist;
        }
        else
        {
            lsf_min = *(p_lsf++) + min_dist;
        }
    }
}


DRAM0_STAGE2_SRAM_ATTR void D_plsf_3(
        D_plsfState *st,   /* i/o: State struct                               */
        enum Mode mode,    /* i  : coder mode                                 */
        Word16 bfi,        /* i  : bad frame indicator (set to 1 if a         */
        /*      bad frame is received)                     */
        Word16 * indice,   /* i  : quantization indices of 3 submatrices, Q0  */
        CommonAmrTbls* common_amr_tbls, /* i : structure containing ptrs to read-only tables */
        Word16 * lsp1_q,   /* o  : quantized 1st LSP vector,              Q15 */
        Flag  *pOverflow   /* o : Flag set when overflow occurs               */
        )
{
    Word16 i;
    Word16 temp;
    Word16 index;

    Word16 lsf1_r[M];
    Word16 lsf1_q[M];

    const Word16* mean_lsf_3_ptr = common_amr_tbls->mean_lsf_3_ptr;
    const Word16* pred_fac_3_ptr = common_amr_tbls->pred_fac_3_ptr;
    const Word16* dico1_lsf_3_ptr = common_amr_tbls->dico1_lsf_3_ptr;
    const Word16* dico2_lsf_3_ptr = common_amr_tbls->dico2_lsf_3_ptr;
    const Word16* mr515_3_lsf_ptr = common_amr_tbls->mr515_3_lsf_ptr;
    if (mode != MR475 || bfi != 0)
        return;


    {

        Word16 index_limit_1 = 0;
        Word16 index_limit_2 = (DICO2_SIZE - 1) * 3;
        Word16 index_limit_3 = 0;

        const Word16 *p_cb1;
        const Word16 *p_cb2;
        const Word16 *p_cb3;
        const Word16 *p_dico;


        p_cb2 = dico2_lsf_3_ptr;    /* size DICO2_SIZE*3 */

        p_cb1 = dico1_lsf_3_ptr;    /* size DICO1_SIZE*3 */
        p_cb3 = mr515_3_lsf_ptr;    /* size MR515_3_SIZE*4 */

        index_limit_1 = (DICO1_SIZE - 1) * 3;
        index_limit_3 = (MR515_3_SIZE - 1) * 4;


        /* decode prediction residuals from 3 received indices */

        index = *indice++;

        /* temp = 3*index; */
        temp = index + (index << 1);

        if (temp > index_limit_1)
        {
            temp = index_limit_1;  /* avoid buffer overrun */
        }

        p_dico = &p_cb1[temp];

        lsf1_r[0] = *p_dico++;
        lsf1_r[1] = *p_dico++;
        lsf1_r[2] = *p_dico++;

        index = *indice++;

        //index <<= 1;

        /* temp = 3*index */
        temp = index + (index << 1);

        if (temp > index_limit_2)
        {
            temp = index_limit_2;  /* avoid buffer overrun */
        }

        p_dico = &p_cb2[temp];

        lsf1_r[3] = *p_dico++;
        lsf1_r[4] = *p_dico++;
        lsf1_r[5] = *p_dico++;

        index = *indice++;

        temp = index << 2;

        if (temp > index_limit_3)
        {
            temp = index_limit_3;  /* avoid buffer overrun */
        }


        p_dico = &p_cb3[temp];

        lsf1_r[6] = *p_dico++;
        lsf1_r[7] = *p_dico++;
        lsf1_r[8] = *p_dico++;
        lsf1_r[9] = *p_dico++;

        /* Compute quantized LSFs and update the past quantized residual */

        for (i = 0; i < M; i++)
        {
            temp =
                mult(
                        st->past_r_q[i],
                        pred_fac_3_ptr[i],
                        pOverflow);

            temp =
                add_16(
                        mean_lsf_3_ptr[i],
                        temp,
                        pOverflow);

            lsf1_q[i] =
                add_16(
                        lsf1_r[i],
                        temp,
                        pOverflow);

            st->past_r_q[i] = lsf1_r[i];
        }

    }

    /* verification that LSFs has minimum distance of LSF_GAP Hz */

    Reorder_lsf(
        lsf1_q,
        LSF_GAP,
        M,
        pOverflow);

    oscl_memmove(
        (void *)st->past_lsf_q,
        lsf1_q,
        M*sizeof(*lsf1_q));

    /*  convert LSFs to the cosine domain */

    Lsf_lsp(
        lsf1_q,
        lsp1_q,
        M);

    return;
}

void Init_D_plsf_3(
    D_plsfState *st,      /* i/o: State struct                */
    Word16       index,   /* i  : past_rq_init[] index [0, 7] */
    const Word16* past_rq_init_ptr /* ptr to read-only table */)
{
    oscl_memmove(
        (void *)st->past_r_q,
        &past_rq_init_ptr[index * M],
        M*sizeof(*past_rq_init_ptr));
}

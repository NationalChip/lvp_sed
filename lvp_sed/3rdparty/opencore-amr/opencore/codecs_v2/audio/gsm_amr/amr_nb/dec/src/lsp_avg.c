#include "lsp_avg.h"
#include "basic_op.h"
#include "oper_32b.h"
#include "oscl_mem.h"
#include "q_plsf_5_tbl.h"


DRAM0_STAGE2_SRAM_ATTR Word16 lsp_avg_reset(lsp_avgState *st, const Word16* mean_lsf_5_ptr)
{
    if (st == (lsp_avgState *) NULL)
    {
        /* fprintf(stderr, "lsp_avg_reset: invalid parameter\n"); */
        return -1;
    }

    oscl_memmove((void *)&st->lsp_meanSave[0], mean_lsf_5_ptr, M*sizeof(*mean_lsf_5_ptr));

    return 0;
}


DRAM0_STAGE2_SRAM_ATTR void lsp_avg(
    lsp_avgState *st,         /* i/o : State struct                 Q15 */
    Word16 *lsp,              /* i   : state of the state machine   Q15 */
    Flag   *pOverflow         /* o   : Flag set when overflow occurs    */
)
{
    Word16 i;
    Word32 L_tmp;            /* Q31 */

    for (i = 0; i < M; i++)
    {

        /* mean = 0.84*mean */
        L_tmp = ((Word32)st->lsp_meanSave[i] << 16);
        L_tmp = L_msu(L_tmp, EXPCONST, st->lsp_meanSave[i], pOverflow);

        /* Add 0.16 of newest LSPs to mean */
        L_tmp = L_mac(L_tmp, EXPCONST, lsp[i], pOverflow);

        /* Save means */
        st->lsp_meanSave[i] = pv_round(L_tmp, pOverflow);   /* Q15 */
    }

    return;
}

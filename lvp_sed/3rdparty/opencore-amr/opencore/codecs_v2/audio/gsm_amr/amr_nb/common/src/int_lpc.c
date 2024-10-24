#include "int_lpc.h"
#include "cnst.h"
#include "basic_op.h"
#include "typedef.h"

static void Get_lsp_pol(
    Word16 *lsp,
    Word32 *f,
    Flag   *pOverflow)
{
    register Word16 i;
    register Word16 j;

    Word16 hi;
    Word16 lo;
    Word32 t0;
    OSCL_UNUSED_ARG(pOverflow);

    /* f[0] = 1.0;             */
    *f++ = (Word32) 0x01000000;
    *f++ = (Word32) - *(lsp++) << 10;       /* f[1] =  -2.0 * lsp[0];  */
    lsp++;                                  /* Advance lsp pointer     */

    for (i = 2; i <= 5; i++)
    {
        *f = *(f - 2);

        for (j = 1; j < i; j++)
        {
            hi = (Word16)(*(f - 1) >> 16);

            lo = (Word16)((*(f - 1) >> 1) - ((Word32) hi << 15));

            t0  = ((Word32)hi * *lsp);
            t0 += ((Word32)lo * *lsp) >> 15;

            *(f) +=  *(f - 2);          /*      *f += f[-2]      */
            *(f--) -=  t0 << 2;         /*      *f -= t0         */

        }

        *f -= (Word32)(*lsp++) << 10;

        f  += i;
        lsp++;
    }

    return;
}

/****************************************************************************/

static OSCL_EXPORT_REF void Lsp_Az(
    Word16 lsp[],        /* (i)  : line spectral frequencies            */
    Word16 a[],          /* (o)  : predictor coefficients (order = 10)  */
    Flag  *pOverflow     /* (o)  : overflow flag                        */
)
{
    register Word16 i;
    register Word16 j;

    Word32 f1[6];
    Word32 f2[6];
    Word32 t0;
    Word32 t1;
    Word16 *p_a = &a[0];
    Word32 *p_f1;
    Word32 *p_f2;

    Get_lsp_pol(&lsp[0], f1, pOverflow);

    Get_lsp_pol(&lsp[1], f2, pOverflow);

    p_f1 = &f1[5];
    p_f2 = &f2[5];

    for (i = 5; i > 0; i--)
    {
        *(p_f1--) += f1[i-1];
        *(p_f2--) -= f2[i-1];
    }

    *(p_a++) = 4096;
    p_f1 = &f1[1];
    p_f2 = &f2[1];

    for (i = 1, j = 10; i <= 5; i++, j--)
    {
        t0 = *(p_f1) + *(p_f2);               /* f1[i] + f2[i] */
        t1 = *(p_f1++) - *(p_f2++);           /* f1[i] - f2[i] */

        t0 = t0 + ((Word32) 1 << 12);
        t1 = t1 + ((Word32) 1 << 12);

        *(p_a++) = (Word16)(t0 >> 13);
        a[j]     = (Word16)(t1 >> 13);
    }

    return;
}

OSCL_EXPORT_REF void Int_lpc_1to3(
    Word16 lsp_old[], /* input : LSP vector at the 4th SF of past frame    */
    Word16 lsp_new[], /* input : LSP vector at the 4th SF of present frame */
    Word16 Az[],      /* output: interpolated LP parameters in all SFs     */
    Flag   *pOverflow
)
{
    Word16 i;
    Word16 temp;

    Word16 lsp[M];

    for (i = 0; i < M; i++)
    {
        temp = lsp_old[i] - (lsp_old[i] >> 2);
        lsp[i] = temp + (lsp_new[i] >> 2);
    }

    Lsp_Az(lsp,Az,pOverflow);        /* Subframe 1 */

    Az += MP1;


    for (i = 0; i < M; i++)
    {
        lsp[i] = (lsp_new[i] >> 1) + (lsp_old[i] >> 1);

    }

    Lsp_Az(lsp, Az, pOverflow);        /* Subframe 2 */

    Az += MP1;

    for (i = 0; i < M; i++)
    {

        temp = lsp_new[i] - (lsp_new[i] >> 2);
        lsp[i] = temp + (lsp_old[i] >> 2);

    }

    Lsp_Az(lsp, Az, pOverflow);        /* Subframe 3 */

    Az += MP1;

    Lsp_Az(lsp_new, Az, pOverflow);    /* Subframe 4 */

    return;
}

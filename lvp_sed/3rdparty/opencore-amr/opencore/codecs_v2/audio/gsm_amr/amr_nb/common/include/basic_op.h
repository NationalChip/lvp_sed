#ifndef BASIC_OP_H
#define BASIC_OP_H

#include    "basicop_malloc.h"

#if   ((PV_CPU_ARCH_VERSION >=5) && (PV_COMPILER == EPV_ARM_GNUC))
#include "basic_op_arm_gcc_v5.h"

#else
#include "basic_op_c_equivalent.h"

#endif



#include    "add.h"
#include    "div_s.h"
#include    "l_shr_r.h"
#include    "mult_r.h"
#include    "norm_l.h"
#include    "norm_s.h"
#include    "round.h"
#include    "shr_r.h"
#include    "sub.h"
#include    "shr.h"
#include    "l_negate.h"
#include    "l_extract.h"
/*--------------------------------------------------------------------------*/
    static inline Word16 negate(Word16 var1)
    {
        return (((var1 == MIN_16) ? MAX_16 : -var1));
    }

    static inline Word16 shl(Word16 var1, Word16 var2, Flag *pOverflow)
    {
        Word16 var_out = 0;

        OSCL_UNUSED_ARG(pOverflow);

        if (var2 < 0)
        {
            var2 = -var2;
            if (var2 < 15)
            {
                var_out = var1 >> var2;
            }

        }
        else
        {
            var_out = var1 << var2;
            if (var_out >> var2 != var1)
            {
                var_out = (var1 >> 15) ^ MAX_16;
            }
        }
        return (var_out);
    }


    static inline Word32 L_shl(Word32 L_var1, Word16 var2, Flag *pOverflow)
    {
        Word32 L_var_out = 0;

        OSCL_UNUSED_ARG(pOverflow);

        if (var2 > 0)
        {
            L_var_out = L_var1 << var2;
            if (L_var_out >> var2 != L_var1)
            {
                L_var_out = (L_var1 >> 31) ^ MAX_32;
            }
        }
        else
        {
            var2 = -var2;
            if (var2 < 31)
            {
                L_var_out = L_var1 >> var2;
            }

        }

        return (L_var_out);
    }


    static inline Word32 L_shr(Word32 L_var1, Word16 var2, Flag *pOverflow)
    {
        Word32 L_var_out = 0;

        OSCL_UNUSED_ARG(pOverflow);

        if (var2 > 0)
        {
            if (var2 < 31)
            {
                L_var_out = L_var1 >> var2;
            }
        }
        else
        {
            var2 = -var2;

            L_var_out = L_var1 << (var2) ;
            if ((L_var_out >> (var2)) != L_var1)
            {
                L_var_out = (L_var1 >> 31) ^ MAX_32;
            }

        }

        return (L_var_out);
    }

    static inline Word16 abs_s(Word16 var1)
    {

        Word16 y = var1 - (var1 < 0);
        y = y ^(y >> 15);
        return (y);

    }
    /*----------------------------------------------------------------------------
    ; END
    ----------------------------------------------------------------------------*/
#endif /* BASIC_OP_H */



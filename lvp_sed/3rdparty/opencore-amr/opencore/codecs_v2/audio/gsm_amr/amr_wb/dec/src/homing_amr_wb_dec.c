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

    3GPP TS 26.173
    ANSI-C code for the Adaptive Multi-Rate - Wideband (AMR-WB) speech codec
    Available from http://www.3gpp.org

(C) 2007, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TTA, TTC)
Permission to distribute, modify and use this file under the standard license
terms listed above has been obtained from the copyright holder.
****************************************************************************************/
/*
------------------------------------------------------------------------------



 Filename: homing_amr_wb_dec.cpp

------------------------------------------------------------------------------



INPUT AND OUTPUT DEFINITIONS

Input
    int16 input_frame[],            16-bit input frame
    int16 mode                      16-bit mode
    int16 nparms                    16-bit number of parameters
Returns
    Int16 i             number of leading zeros on x


------------------------------------------------------------------------------
 FUNCTION DESCRIPTION

    Performs the homing routines

    int16 dhf_test(int16 input_frame[], int16 mode, int16 nparms)
    int16 decoder_homing_frame_test(int16 input_frame[], int16 mode)
    int16 decoder_homing_frame_test_first(int16 input_frame[], int16 mode)

------------------------------------------------------------------------------
 REQUIREMENTS


------------------------------------------------------------------------------
 REFERENCES

------------------------------------------------------------------------------
 PSEUDO-CODE

------------------------------------------------------------------------------
*/


/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/

#include "pv_amr_wb_type_defs.h"
#include "pvamrwbdecoder_cnst.h"
#include "pvamrwbdecoder.h"
#include "pvamrwbdecoder_basic_op.h"
#include "get_amr_wb_bits.h"
#include "pvamrwbdecoder_api.h"
#include "pvamrwbdecoder.h"

/*----------------------------------------------------------------------------
; MACROS
; Define module specific macros here
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; DEFINES
; Include all pre-processor statements here. Include conditional
; compile variables also.
----------------------------------------------------------------------------*/
#define DHF_PARMS_MAX 32 /* homing frame pattern             */
#define NUM_OF_SPMODES 9

#define PRML 15
#define PRMN_7k NBBITS_7k/PRML + 1

/*----------------------------------------------------------------------------
; LOCAL FUNCTION DEFINITIONS
; Function Prototype declaration
----------------------------------------------------------------------------*/
int16 dhf_test(int16 input_frame[], int16 nparms);

/*----------------------------------------------------------------------------
; LOCAL STORE/BUFFER/POINTER DEFINITIONS
; Variable declaration - defined here and used outside this module
----------------------------------------------------------------------------*/
static const int16 dfh_M7k[PRMN_7k] =
{
    3168, 29954, 29213, 16121,
    64, 13440, 30624, 16430,
    19008
};

/*----------------------------------------------------------------------------
; EXTERNAL FUNCTION REFERENCES
; Declare functions defined elsewhere and referenced in this module
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; EXTERNAL GLOBAL STORE/BUFFER/POINTER REFERENCES
; Declare variables used in this module but defined elsewhere
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; FUNCTION CODE
----------------------------------------------------------------------------*/

DRAM0_STAGE2_SRAM_ATTR int16 dhf_test(int16 input_frame[], int16 nparms)
{
    int16 i, j, tmp, shift;
    int16 param[DHF_PARMS_MAX];
    int16 *prms;

    /* overall table with the parameters of the
    decoder homing frames for all modes */

    prms = input_frame;
    j = 0;
    i = 0;

    /* convert the received serial bits */
    tmp = nparms - 15;
    while (tmp > j)
    {
        param[i] = Serial_parm(15, &prms);
        j += 15;
        i++;
    }
    tmp = nparms - j;
    param[i] = Serial_parm(tmp, &prms);
    shift = 15 - tmp;
    param[i] = shl_int16(param[i], shift);

    /* check if the parameters matches the parameters of the corresponding decoder homing frame */
    tmp = i;
    j = 0;
    for (i = 0; i < tmp; i++)
    {
        j = (param[i] ^ dfh_M7k[i]);
        if (j)
        {
            break;
        }
    }
    tmp = 0x7fff;
    tmp >>= shift;
    tmp = shl_int16(tmp, shift);
    tmp = (dfh_M7k[i] & tmp);
    tmp = (param[i] ^ tmp);
    j = (int16)(j | tmp);

    return (!j);
}

/*----------------------------------------------------------------------------
; FUNCTION CODE
----------------------------------------------------------------------------*/


DRAM0_STAGE2_SRAM_ATTR int16 pvDecoder_AmrWb_homing_frame_test(int16 input_frame[])
{
    /* perform test for COMPLETE parameter frame */
    return dhf_test(input_frame, NBBITS_7k);
}

/*----------------------------------------------------------------------------
; FUNCTION CODE
----------------------------------------------------------------------------*/


DRAM0_STAGE2_SRAM_ATTR int16 pvDecoder_AmrWb_homing_frame_test_first(int16 input_frame[])
{
    /* perform test for FIRST SUBFRAME of parameter frame ONLY */
    return dhf_test(input_frame, 63);
}

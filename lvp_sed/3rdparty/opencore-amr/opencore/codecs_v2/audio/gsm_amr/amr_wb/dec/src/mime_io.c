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


 Pathname: ./src/mime_io.cpp

------------------------------------------------------------------------------
 INPUT AND OUTPUT DEFINITIONS

 Inputs:
    [input_variable_name] = [description of the input to module, its type
                 definition, and length (when applicable)]

 Local Stores/Buffers/Pointers Needed:
    [local_store_name] = [description of the local store, its type
                  definition, and length (when applicable)]
    [local_buffer_name] = [description of the local buffer, its type
                   definition, and length (when applicable)]
    [local_ptr_name] = [description of the local pointer, its type
                definition, and length (when applicable)]

 Global Stores/Buffers/Pointers Needed:
    [global_store_name] = [description of the global store, its type
                   definition, and length (when applicable)]
    [global_buffer_name] = [description of the global buffer, its type
                definition, and length (when applicable)]
    [global_ptr_name] = [description of the global pointer, its type
                 definition, and length (when applicable)]

 Outputs:
    [return_variable_name] = [description of data/pointer returned
                  by module, its type definition, and length
                  (when applicable)]

 Pointers and Buffers Modified:
    [variable_bfr_ptr] points to the [describe where the
      variable_bfr_ptr points to, its type definition, and length
      (when applicable)]
    [variable_bfr] contents are [describe the new contents of
      variable_bfr]

 Local Stores Modified:
    [local_store_name] = [describe new contents, its type
                  definition, and length (when applicable)]

 Global Stores Modified:
    [global_store_name] = [describe new contents, its type
                   definition, and length (when applicable)]

------------------------------------------------------------------------------
 FUNCTION DESCRIPTION

 [Describe what the module does by using the variable names
 listed in the Input and Output Definitions Section above.]

------------------------------------------------------------------------------
 REQUIREMENTS

 [List requirements to be satisfied by this module.]

------------------------------------------------------------------------------
 REFERENCES

 [List all references used in designing this module.]

------------------------------------------------------------------------------
 PSEUDO-CODE

 ------------------------------------------------------------------------------
 RESOURCES USED

 STACK USAGE:

 DATA MEMORY USED: x words

 PROGRAM MEMORY USED: x words

 CLOCK CYCLES:

------------------------------------------------------------------------------
*/


/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/

#include "pv_amr_wb_type_defs.h"
#include "pvamrwbdecoder_api.h"
#include "pvamrwbdecoder.h"
#include "pvamrwbdecoder_mem_funcs.h"
#include "pvamrwbdecoder_cnst.h"
#include "dtx.h"
#include "mime_io.h"

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

/* sorting tables for all modes */

static const int16 sort_660[132] =
{
    0,   5,   6,   7,  61,  84, 107, 130,  62,  85,
    8,   4,  37,  38,  39,  40,  58,  81, 104, 127,
    60,  83, 106, 129, 108, 131, 128,  41,  42,  80,
    126,   1,   3,  57, 103,  82, 105,  59,   2,  63,
    109, 110,  86,  19,  22,  23,  64,  87,  18,  20,
    21,  17,  13,  88,  43,  89,  65, 111,  14,  24,
    25,  26,  27,  28,  15,  16,  44,  90,  66, 112,
    9,  11,  10,  12,  67, 113,  29,  30,  31,  32,
    34,  33,  35,  36,  45,  51,  68,  74,  91,  97,
    114, 120,  46,  69,  92, 115,  52,  75,  98, 121,
    47,  70,  93, 116,  53,  76,  99, 122,  48,  71,
    94, 117,  54,  77, 100, 123,  49,  72,  95, 118,
    55,  78, 101, 124,  50,  73,  96, 119,  56,  79,
    102, 125
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

DRAM0_STAGE2_SRAM_ATTR void mime_unsorting(uint8 unsorted_bits[],
                    int16 sorted_bits_into_int16[],
                    int16 * frame_type,
                    int16 * mode,
                    uint8 quality,
                    RX_State *st)
{

    int16 i;
    int16 j;
    uint8 temp = 0;
    uint8 *unsorted_bits_ptr = (uint8*)unsorted_bits;

    /* pointer table for bit sorting tables */

    const int16 * pt_AmrWbSortingTables  = sort_660;
    const int16 unpacked_size = 132;

    /* clear compressed speech bit buffer */
    pv_memset(sorted_bits_into_int16,
              0,
              unpacked_size * sizeof(*sorted_bits_into_int16));

    /* unpack and unsort speech or SID bits */


    for (i = 16; i != 0; i--) //132 66 33 16
    {
        temp = *(unsorted_bits_ptr++);
        for (j = 7; j >= 0; j--) {
            if ((temp >> j) & 0x01)
                sorted_bits_into_int16[*(pt_AmrWbSortingTables++)] = BIT_1;
            else
                pt_AmrWbSortingTables++;
        }
    }

    temp = *unsorted_bits_ptr; /* convert the remaining 0 to 7 bits */
    for (i = 4; i != 0; i--) //unpacked_size % 8
    {
        if (temp & 0x80)
        {
            sorted_bits_into_int16[*(pt_AmrWbSortingTables++)] = BIT_1;
        }
        else
        {
            pt_AmrWbSortingTables++;
        }

        temp <<= 1;
    }

    /* set frame type */
    switch (*mode)
    {
        case MODE_7k:
            if (quality)
            {
                *frame_type = RX_SPEECH_GOOD;
            }
            break;
        default:        /* replace frame with unused mode index by NO_DATA frame */
            break;
    }

    st->prev_mode = *mode;

}




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
#include "qisf_ns.h"


/*
 * Tables for function q_gain2()
 *
 *  g_pitch(Q14),  g_code(Q11)
 *
 * pitch gain are ordered in table to reduce complexity
 * during quantization of gains.
 */




DRAM0_STAGE2_SRAM_ATTR const int16 t_qua_gain6b[NB_QUA_GAIN6B*2] =
{
    1566,  1332,
    1577,  3557,
    3071,  6490,
    4193, 10163,
    4496,  2534,
    5019,  4488,
    5586, 15614,
    5725,  1422,
    6453,   580,
    6724,  6831,
    7657,  3527,
    8072,  2099,
    8232,  5319,
    8827,  8775,
    9740,  2868,
    9856,  1465,
    10087, 12488,
    10241,  4453,
    10859,  6618,
    11321,  3587,
    11417,  1800,
    11643,  2428,
    11718,   988,
    12312,  5093,
    12523,  8413,
    12574, 26214,
    12601,  3396,
    13172,  1623,
    13285,  2423,
    13418,  6087,
    13459, 12810,
    13656,  3607,
    14111,  4521,
    14144,  1229,
    14425,  1871,
    14431,  7234,
    14445,  2834,
    14628, 10036,
    14860, 17496,
    15161,  3629,
    15209,  5819,
    15299,  2256,
    15518,  4722,
    15663,  1060,
    15759,  7972,
    15939, 11964,
    16020,  2996,
    16086,  1707,
    16521,  4254,
    16576,  6224,
    16894,  2380,
    16906,   681,
    17213,  8406,
    17610,  3418,
    17895,  5269,
    18168, 11748,
    18230,  1575,
    18607, 32767,
    18728, 21684,
    19137,  2543,
    19422,  6577,
    19446,  4097,
    19450,  9056,
    20371, 14885
};


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

 Filename: int_lpc.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 This file contains all the constant definitions and prototype definitions
 needed by the lsp_avg.c

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef int_lpc_h
#define int_lpc_h "$Id $"

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "typedef.h"

/*--------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------
    ; MACROS
    ; Define module specific macros here
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; DEFINES
    ; Include all pre-processor statements here.
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; EXTERNAL VARIABLES REFERENCES
    ; Declare variables used in this module but defined elsewhere
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; SIMPLE TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; ENUMERATED TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; STRUCTURES TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; GLOBAL FUNCTION DEFINITIONS
    ; Function Prototype declaration
    ----------------------------------------------------------------------------*/


    /*
    **************************************************************************
    *
    *  Function    : Int_lpc_1to3
    *  Purpose     : Interpolates the LSPs and converts to LPC parameters
    *                to get a different LP filter in each subframe.
    *  Description : The 20 ms speech frame is divided into 4 subframes.
    *                The LSPs are quantized and transmitted at the 4th
    *                subframes (once per frame) and interpolated at the
    *                1st, 2nd and 3rd subframe.
    *
    *                      |------|------|------|------|
    *                         sf1    sf2    sf3    sf4
    *                   F0                          F1
    *
    *                 sf1:   3/4 F0 + 1/4 F1         sf3:   1/4 F0 + 3/4 F1
    *                 sf2:   1/2 F0 + 1/2 F1         sf4:       F1
    *  Returns     : void
    *
    **************************************************************************
    */
    OSCL_IMPORT_REF void Int_lpc_1to3(
        Word16 lsp_old[], /* i : LSP vector at the 4th SF of past frame (M)      */
        Word16 lsp_new[], /* i : LSP vector at the 4th SF of present frame (M)   */
        Word16 Az[],      /* o : interpolated LP parameters in all SFs (AZ_SIZE) */
        Flag   *pOverflow
    );

    /*----------------------------------------------------------------------------
    ; END
    ----------------------------------------------------------------------------*/
#endif /* _INT_LPC_H_ */



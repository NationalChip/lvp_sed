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
#ifndef GET_CONST_TBLS_H
#include "get_const_tbls.h"
#endif

extern const Word16 dico1_lsf_3[];
extern const Word16 dico2_lsf_3[];
extern const Word16 mean_lsf_3[];
extern const Word16 mean_lsf_5[];
extern const Word16 mr515_3_lsf[];
extern const Word16 past_rq_init[];
extern const Word16 pred_fac_3[];
extern const Word16 startPos[];
extern const Word16 prmno[];
extern const Word16* const bitno[];
extern const Word16 numOfBits[];
extern const Word16* const reorderBits[];
extern const Word16 ph_imp_low[];
extern const Word16 ph_imp_mid[];

OSCL_EXPORT_REF void get_const_tbls(CommonAmrTbls* tbl_struct_ptr)
{
    tbl_struct_ptr->dico1_lsf_3_ptr = dico1_lsf_3;
    tbl_struct_ptr->dico2_lsf_3_ptr = dico2_lsf_3;
    tbl_struct_ptr->mean_lsf_3_ptr = mean_lsf_3;
    tbl_struct_ptr->mean_lsf_5_ptr = mean_lsf_5;
    tbl_struct_ptr->mr515_3_lsf_ptr = mr515_3_lsf;
    tbl_struct_ptr->past_rq_init_ptr = past_rq_init;
    tbl_struct_ptr->pred_fac_3_ptr = pred_fac_3;
    tbl_struct_ptr->startPos_ptr = startPos;
    tbl_struct_ptr->prmno_ptr = prmno;
    tbl_struct_ptr->bitno_ptr = bitno;
    tbl_struct_ptr->numOfBits_ptr = numOfBits;
    tbl_struct_ptr->reorderBits_ptr = reorderBits;
    tbl_struct_ptr->ph_imp_low_ptr = ph_imp_low;
    tbl_struct_ptr->ph_imp_mid_ptr = ph_imp_mid;
}

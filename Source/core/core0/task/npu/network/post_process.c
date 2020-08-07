
/*
    This is generated at 2020-07-13 12:34:51.729328
    Openedges Enlight post process main
*/

#include "stdint.h"
#include "npu_data_type.h"
#include "quantized_network_oact.h"
#include "quantized_prior_box.h"
void detector_run(
    uint8_t *prior_box,
    uint8_t *loc_buf_32,
    uint8_t *score_buf_32,
    int log2_prior_scl,
    int log2_loc_scl,
    int log2_score_scl,
    int num_class);


void run_post_process(void *oact_base)
{
    uint8_t* oact_base_addr;
    uint8_t* loc_buf_addr;
    uint8_t* score_buf_addr;
    uint8_t* prior_box_addr;

    int log2_prior_scl;
    int log2_score_scl;
    int log2_loc_scl;
    int num_class;
    act_tensor_t *oact_score = &oact_Concat_290;
    act_tensor_t *oact_loc = &oact_Concat_291;

    oact_base_addr = (uint8_t*)oact_base;
    loc_buf_addr = oact_base_addr + (unsigned long)(oact_loc->buf);
    score_buf_addr = oact_base_addr + (unsigned long)(oact_score->buf);
    prior_box_addr = prior_box;
    log2_prior_scl = (8 - 1 - 6); 
    log2_score_scl = (8 - 1 - oact_score->log2_scale);
    log2_loc_scl = (8 - 1 - oact_loc->log2_scale);
    num_class = 21;
    detector_run(prior_box_addr, loc_buf_addr, score_buf_addr,
        log2_prior_scl, log2_loc_scl, log2_score_scl, num_class);
}
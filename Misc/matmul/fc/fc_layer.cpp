#include "fc_layer.h"

/**
 * math
 * output_i = activation (sum of {weights_ij * input_j over input_dim: j } + bias_i)
 */

float relu(float x) {
    return (x>0.0f) ? x : 0.0f;
}

void fc_layer(const float input[INPUT_SIZE],
        const float weights[OUTPUT_SIZE][INPUT_SIZE],
        const float bias[OUTPUT_SIZE],
        float output[OUTPUT_SIZE]) {
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=m_axi port=input offset=slave bundle=gmem
#pragma HLS INTERFACE mode=m_axi port=weights offset=slave bundle=gmem
#pragma HLS INTERFACE mode=m_axi port=bias offset=slave bundle=gmem
#pragma HLS INTERFACE mode=m_axi port=output offset=slave bundle=gmem

    // offset = slave -> memory address is provided by host
    // bundle = gmem -> group ports onto a single AXI interface -> for external memory communication

fc_output_loop: for(int i=0; i<OUTPUT_SIZE; ++i) {
#pragma HLS PIPELINE
                    float sum = bias[i];
fc_inner_loop: for(int j=0; j<INPUT_SIZE; ++j) {
                   sum += weights[i][j] * input[j];
               }

               output[i] = relu(sum);
                }
}

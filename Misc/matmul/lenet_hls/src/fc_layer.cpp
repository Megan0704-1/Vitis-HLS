#include "fc_layer.h"

/**
 * math
 * output_i = activation (sum of {weights_ij * input_j over input_dim: j } + bias_i)
 */

data_t relu(data_t x) {
    return x > 0 ? x : data_t(0);
}

template<int IN_DIM, int OUT_DIM>
void fc_layer(
        hls::stream<data_t>& in_stream,
        hls::stream<data_t>& out_stream,
        const data_t weights[OUT_DIM][IN_DIM],
        data_t bias[OUT_DIM],
        bool use_relu
        ) {
    #pragma HLS INLINE OFF
    #pragma HLS ARRAY_PARTITION variable=weights cyclic factor=8 dim=2
    #pragma HLS ARRAY_PARTITION variable=bias complete dim=1

    for(int i=0; i<IN_DIM; ++i) {
        #pragma HLS PIPELINE II=1
        data_t val = in_stream.read();
        for(int j=0; j<OUT_DIM; ++j) {
            #pragma HLS UNROLL factor=4
            bias[j] += weight[j][i] * val;
        }
    }

    for(int j=0; j<OUT_DIM; ++j) {
        data_t result = use_relu ? relu(bias[j]) : bias[j];
        out_stream.write(result);
    }
}

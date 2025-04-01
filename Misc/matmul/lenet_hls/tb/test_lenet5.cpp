#include <iostream>
#include "lenet5.h"
#include "test_utils.h"


int main() {
    hls::stream<data_t> in_stream, out_stream;
    data_t conv1_weights[6][5][5], conv1_bias[6];
    data_t conv2_weights[16][6][5][5], conv2_bias[16];
    data_t fc1_weights[120][400], fc1_bias[120];
    data_t fc2_weights[84][120], fc2_bias[84];
    data_t fc3_weights[10][84], fc_bias[10];

    // channel, kernel size
    // bias size
    load_conv2d_weights<6, 5>(CONV1_WEIGHT_BIN, conv1_weights);
    load_bias<6>(CONV1_BIAS_BIN, conv1_bias);

    load_conv2d_weights<16, 5>(CONV2_WEIGHT_BIN, conv2_weights);
    load_bias<16>(CONV2_BIAS_BIN, conv2_bias);

    // out dim, in dim
    // bias size
    load_fc_weights<120, 400>(FC1_WEIGHT_BIN, fc1_weights);
    load_bias<120>(FC1_BIAS_BIN, fc1_bias);

    load_fc_weights<84, 120>(FC2_WEIGHT_BIN, fc2_weights);
    load_bias<84>(FC2_BIAS_BIN, fc2_bias);

    load_fc_weights<10, 84>(FC3_WEIGHT_BIN, fc3_weights);
    load_bias<10>(FC3_BIAS_BIN, fc3_bias);

    // input dimension
    load_input_to_stream<28>(DATASET, in_stream);

    lenet5(in_stream, out_stream, conv1_weights, conv1_bias, conv2_weights, conv2_bias, fc1_weights, fc1_bias, fc2_weights, fc2_bias, fc3_weights, fc3_bias);

    int predict_class = -1;
    data_t max_val = -999;

    for(int i=0; i<10; ++i) {
        data_t val = output.read();
        if(val > max_val) {
            max_val = val;
            predicted_class = i;
        }
    }

    std::cout << "Predicted class: " << predict_class << std::endl;
    return check_against_golden(predicted_class);
}

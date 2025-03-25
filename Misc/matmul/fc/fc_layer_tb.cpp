#include "fc_layer.h"
#include <iostream>

int main() {
    float input[INPUT_SIZE];
    float weights[OUTPUT_SIZE][INPUT_SIZE];
    float bias[OUTPUT_SIZE];
    float output[OUTPUT_SIZE];

    for(int i=0; i<INPUT_SIZE; ++i) {
        input[i] = static_cast<float>(i) / INPUT_SIZE;
    }

    for(int i=0; i<OUTPUT_SIZE; ++i) {
        bias[i] = 0.1f * i;
        for(int j=0; j<INPUT_SIZE; ++j) {
            weights[i][j] = 0.01f * (i+j);
        }
    }

    fc_layer(input, weights, bias, output);

    std::cout << "Inference Output:\n";
    bool success=true;
    for(int i=0; i<OUTPUT_SIZE; ++i) {
        float expected = bias[i];
        for(int j=0; j<INPUT_SIZE; ++j) {
            expected += weights[i][j] * input[j];
        }
        expected = relu(expected);
        std::cout << "output[" << i << "] = " << output[i] << std::endl;
        if(output[i] != expected) {
            success=false;
            break;
        }
    }

    return success ? 0 : 1;
}

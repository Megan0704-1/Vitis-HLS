#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <fstream>
#include <ap_fixed.h>

typedef ap_fixed<8, 3> data_t;

#define IN_DIM 28

template<int C, int KERNEL_SIZE>
void load_conv2d_weights(
        const char* filename,
        data_t weights[C][KERNEL_SIZE][KERNEL_SIZE]
        ) {
    std::ifstream file(filename, std::ios::binary);

    for(int channel=0; channel<C; ++channel) {
        for(int i=0; i<KERNEL_SIZE; ++i) {
            for(int j=0; j<KERNEL_SIZE; ++j) {
                float val;
                file.read(reinterpret_cast<char*>(&val), sizeof(float));
                weights[channel][i][j] = data_t(val);
            }
        }
    }
}

template<int SIZE>
void load_bias(
        const char* filename,
        data_t bias[SIZE]
        ) {
    std::ifstream file(filename, std::ios::binary);

    for(int i=0; i<SIZE; ++i) {
        float val;
        file.read(reinterpret_cast<char*>(&val), sizeof(float));
        bias[i] = data_t(val);
    }
}

void load_input_to_stream(
        const char* filename,
        hls::stream<data_t>& in_stream
        ) {
    std::ifstream file(filename, std::ios::binary);

    for(int i=0; i<IN_DIM * IN_DIM; ++i) {
        unsigned char pixel;
        file.read(reinterpret_cast<char*>(&pixel), 1);
        data_t val = data_t(pixel) / 255.0;
        in_stream.write(val);
    }
}

#endif

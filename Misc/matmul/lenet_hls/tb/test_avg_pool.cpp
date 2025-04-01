#include <iostream>
#include "avg_pool.h"

#define IN_ROWS 28
#define IN_COLS 28
#define CHANNELS 6
#define POOL_SIZE 2

int main() {
    hls::stream<data_t> in_steam, out_stream;

    for(int c=0; c<CHANNELS; ++c) {
        for(int i=0; i<IN_ROWS; ++i) {
            in_stream.write(i%4 + 1.0); // 1,2,3,4,1,2,3,4
        }
    }

    avg_pool<POOL_SIZE>(in_stream, out_stream, IN_ROWS, IN_COLS, CHANNELS);

    int errs = 0;
    for(int i=0; i<(IN_ROWS/POOL_SIZE) * (IN_COLS/POOL_SIZE) * CHANNELS; ++i) {
        data_t val = out_stream.read();
        if(abs(val-2.5) > 0.01) errs ++;
    }

    std::cout << "Pooling Test: " << (errs ? "Fail" : "Pass") 
        << "(" << errs << " errors)\n";

    return errs;
}

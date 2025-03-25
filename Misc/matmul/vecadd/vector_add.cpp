#include "vector_add.h"

void vector_add(int a[], int b[], int c[], int size) {
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=m_axi depth=1024 port=a offset=slave
#pragma HLS INTERFACE mode=m_axi depth=1024 port=b offset=slave
#pragma HLS INTERFACE mode=m_axi depth=1024 port=c offset=slave

loop: for (int i=0; i<size; ++i) {
#pragma HLS PIPELINE
          c[i] = a[i] + b[i];
      }

}

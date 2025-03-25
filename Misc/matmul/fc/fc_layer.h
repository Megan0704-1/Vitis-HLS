#ifndef FC_LAYER_H
#define FC_LAYER_H

#define INPUT_SIZE 16
#define OUTPUT_SIZE 8

void fc_layer(const float input[INPUT_SIZE],
              const float weights[OUTPUT_SIZE][INPUT_SIZE],
              const float bias[OUTPUT_SIZE],
              float output[OUTPUT_SIZE]);

float relu(float x);
#endif

# choose a model
LeNet-5
- input [28x28x1]
- conv1 [5x5x6] -> output [24x24x6]
- avg_pool1 [2x2x6] (stride=2) -> output [12x12x6]
- conv2 [5x5x16] -> output [8x8x6]
- avg_pool2 [2x2x16] (stride=2) -> output [4x4x16]
- fc1 [256x120] -> 120
- fc2 [120x84] -> 84
- fc3 [84*10] -> 10

# pytorch model code
# train -> validate -> deploy
# convert weights to c arrays
# implmenet model in HLS
# test bench

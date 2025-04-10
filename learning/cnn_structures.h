#include <vector>

#ifndef CNN_STRUCTURES_H
#define CNN_STRUCTURES_H

#include "../application/src/learning/imageadapter.h"

#define NUM_CLASSES 3

#define FILTERS_LAYER1 8
#define FILTERS_LAYER2 16
#define FILTERS_LAYER3 32

#define KERNEL_SIZE 3
#define BATCH_SIZE 8
#define NUM_EPOCH 1
#define INPUT_CHANNELS 1
#define ADAPTIVE_POOL_WIDTH 2

struct ImageData {
    picture_vector pixelValues;
    int class_value;
};

#define weight_tensor std::vector<std::vector<std::vector<std::vector<greyscale_value>>>>  // n filters, n channels, kernel height, kernel width
#define tensor_2D std::vector<std::vector<greyscale_value>>
#define tensor_1D std::vector<greyscale_value>

// Structure pour stocker les poids du modele
struct LayerParams {
    weight_tensor weights;
    tensor_1D biases;
    tensor_1D bn_weight;
    tensor_1D bn_bias;
    tensor_1D bn_running_mean;
    tensor_1D bn_running_var;
};

struct ModelWeights {
    LayerParams layer1;
    LayerParams layer2;
    LayerParams layer3;
    // Add fully connected layer params if necessary
    tensor_2D fc_weights;
    tensor_1D fc_biases;
};

#endif // CNN_STRUCTURES_H

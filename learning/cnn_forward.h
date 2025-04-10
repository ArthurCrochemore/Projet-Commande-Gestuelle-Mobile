#include <iostream>

#ifndef CNN_FORWARD_H
#define CNN_FORWARD_H

#include "cnn_structures.h"

class CNNForward {
public:
	static std::vector<picture_vector> apply_convolution(
        const std::vector<picture_vector>& inputs,
        const weight_tensor& weights,
        const tensor_1D& biases, int kernel_size);

    static void apply_batch_norm(
        std::vector<picture_vector>& feature_maps,
        const tensor_1D& bn_weight,
        const tensor_1D& bn_bias,
        const tensor_1D& bn_running_mean,
        const tensor_1D& bn_running_var);

    static void apply_relu(std::vector<picture_vector>& feature_maps);

    static void apply_max_pooling_2D(std::vector<picture_vector>& feature_maps, int param = 2, int stride = 2);

    static void apply_adaptive_avg_pool(std::vector<picture_vector>& feature_maps, int new_width, int new_height);

    static tensor_1D flatten(const std::vector<picture_vector>& feature_maps);

    static tensor_2D apply_fully_connected(const tensor_2D& inputs,
        const tensor_2D& weights,
        const tensor_1D& biases);
};

#endif // CNN_FORWARD_H
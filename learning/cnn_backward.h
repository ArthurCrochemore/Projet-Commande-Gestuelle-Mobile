#include <iostream>

#ifndef CNN_BACKWARD_H
#define CNN_BACKWARD_H

#include "cnn_structures.h"

class CNNBackward {
    public:
    static tensor_1D backward_fully_connected(
        const tensor_1D& d_out,
        const tensor_2D& weights,
        const tensor_1D& biases,
        tensor_2D& grad_weights,
        tensor_1D& grad_biases,
        const tensor_1D& input);

    static std::vector<picture_vector> unflatten(
        const tensor_1D& flat,
        int channels,
        int height,
        int width);

    static std::vector<picture_vector> backward_convolution(
        const std::vector<picture_vector>& d_out,
        const std::vector<picture_vector>& input,
        const std::vector<std::vector<picture_vector>>& weights,
        std::vector<std::vector<picture_vector>>& grad_weights,
        std::vector<float>& grad_biases);

    static void backward_batch_norm(
        const std::vector<picture_vector>& d_out,
        const std::vector<picture_vector>& input,
        const tensor_1D& gamma,
        const tensor_1D& beta,
        const tensor_1D& mean,
        const tensor_1D& variance,
        std::vector<picture_vector>& d_input,
        tensor_1D& grad_gamma,
        tensor_1D& grad_beta);

    static void backward_relu(
        const std::vector<picture_vector>& d_out,
        const std::vector<picture_vector>& input,
        std::vector<picture_vector>& d_input);

    static void backward_max_pooling(
        const std::vector<picture_vector>& d_out,
        const std::vector<picture_vector>& input,
        std::vector<picture_vector>& d_input);
};

#endif // CNN_BACKWARD_H
#include <random>

#ifndef CNNMODEL_H
#define CNNMODEL_H

#include "cnn_forward.h"
#include "cnn_backward.h"
#include "../application/src/learning/imageadapter.h"

/**
 * Modèle CNN utilisant BatchNorm2d et ReLU. 
 */
class CNNModel {
private:
    std::vector<weight_tensor> conv_weights;
    std::vector<tensor_1D> conv_biases;

    tensor_2D fc_weights;
    tensor_1D fc_biases;

    std::vector<tensor_1D> bn_weights;
    std::vector<tensor_1D> bn_biases;
    std::vector<tensor_1D> bn_running_means;
    std::vector<tensor_1D> bn_running_vars;

    int kernel_size;

    size_t num_train;

    // Utile au backward
    int last_conv_width;
    int last_conv_height;
    int last_conv_channels;

    tensor_2D flattened_batch; // chaque ligne = un élément du batch

    // Pour stocker les gradients à apprendre
    tensor_2D grad_fc_weights;
    tensor_1D grad_fc_biases;

    std::vector<std::vector<std::vector<picture_vector>>> grad_conv_weights;
    std::vector<std::vector<float>> grad_conv_biases;

    std::vector<tensor_1D> grad_bn_weights;
    std::vector<tensor_1D> grad_bn_biases;

public:
    CNNModel(const int num_conv_layers, const std::vector<int>& conv_layers_filters,
        const int kernel_size, const size_t num_train);
    ~CNNModel() = default;

    tensor_2D forward(const std::vector<std::vector<picture_vector>>& batch_pictures,
        std::vector<std::vector<std::vector<picture_vector>>>& all_feature_maps_batch);
    void initialize_gradients();
    void backward(const tensor_2D& batch_predicted, const tensor_2D& batch_expected,
        const std::vector<std::vector<std::vector<picture_vector>>>& all_feature_maps_batch);
    void learn(const std::vector<ImageData>& inputs, const int64_t num_classes,
        const int64_t batch_size, const size_t num_epochs,
        const double learning_rate = 1e-3, const double weight_decay = 1e-3);

    int predict(const ImageData& input_image);
};

#endif // CNNMODEL_H
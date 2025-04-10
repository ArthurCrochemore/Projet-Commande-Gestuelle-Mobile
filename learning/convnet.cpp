// Bas� sur le projet pytorch-cpp (https://github.com/prabhuomkar/pytorch-cpp/tree/master)
// Copyright (c) 2020-present, pytorch-cpp Authors
// Sous licence MIT
#include "convnet.h"
#include <torch/torch.h>

auto extract = [](const torch::Tensor& tensor) {
    std::vector<greyscale_value> vec(tensor.numel());
    auto tensor_a = tensor.flatten();
    for (int i = 0; i < tensor.numel(); i++) {
        vec[i] = static_cast<greyscale_value>(tensor_a[i].item<float>());
    }
    return vec;
    };

ModelWeights ConvNetImpl::extract_weights() {
    ModelWeights weights;

    auto extract_layer_params = [](const torch::nn::Conv2dImpl* conv_layer, const torch::nn::BatchNorm2dImpl* bn_layer) {
        LayerParams params;

        const auto& conv_weights = conv_layer->weight;
        int num_filters = conv_weights.size(0);
        int input_channels = conv_weights.size(1);
        int kernel_size = conv_weights.size(2);

        params.weights.resize(num_filters,
            std::vector<std::vector<std::vector<greyscale_value>>>(
                input_channels, std::vector<std::vector<greyscale_value>>(kernel_size, std::vector<greyscale_value>(kernel_size)))
        );

        for (int f = 0; f < num_filters; f++) {
            for (int c = 0; c < input_channels; c++) {
                for (int i = 0; i < kernel_size; i++) {
                    for (int j = 0; j < kernel_size; j++) {
                        params.weights[f][c][i][j] = conv_weights[f][c][i][j].item<float>();
                    }
                }
            }
        }

        params.biases = extract(conv_layer->bias);
        params.bn_weight = extract(bn_layer->weight);
        params.bn_bias = extract(bn_layer->bias);
        params.bn_running_mean = extract(bn_layer->running_mean);
        params.bn_running_var = extract(bn_layer->running_var);

        return params;
        };

    weights.layer1 = extract_layer_params(layer1[0]->as<torch::nn::Conv2d>(), layer1[1]->as<torch::nn::BatchNorm2d>());
    weights.layer2 = extract_layer_params(layer2[0]->as<torch::nn::Conv2d>(), layer2[1]->as<torch::nn::BatchNorm2d>());
    weights.layer3 = extract_layer_params(layer3[0]->as<torch::nn::Conv2d>(), layer3[1]->as<torch::nn::BatchNorm2d>());

    // Extraction des poids et biais de la couche FC
    const auto& fc_weights = fc->weight;
    const auto& fc_biases = fc->bias;

	std::cout << "FC weights size: " << fc_weights.sizes() << std::endl;

    weights.fc_weights.resize(fc_weights.size(0), std::vector<greyscale_value>(fc_weights.size(1)));

    for (int i = 0; i < fc_weights.size(0); ++i) {
        weights.fc_weights[i] = extract(fc_weights[i]);
    }

    weights.fc_biases = extract(fc_biases);

    return weights;
}

ConvNetImpl::ConvNetImpl(int64_t num_classes)
    : fc(FILTERS_LAYER3* ADAPTIVE_POOL_WIDTH* ADAPTIVE_POOL_WIDTH, num_classes) {
    register_module("layer1", layer1);
    register_module("layer2", layer2);
    register_module("layer3", layer3);
    register_module("pool", pool),
    register_module("fc", fc);
}

torch::Tensor ConvNetImpl::forward(torch::Tensor x) {
    x = layer1->forward(x);
    x = layer2->forward(x);
    x = layer3->forward(x);
    x = pool->forward(x);
    x = x.view({ -1, FILTERS_LAYER3 * ADAPTIVE_POOL_WIDTH * ADAPTIVE_POOL_WIDTH });
    return fc->forward(x);
}
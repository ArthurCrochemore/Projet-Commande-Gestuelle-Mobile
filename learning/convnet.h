// Bas� sur le projet pytorch-cpp (https://github.com/prabhuomkar/pytorch-cpp/tree/master)
// Copyright (c) 2020-present, pytorch-cpp Authors
// Sous licence MIT
#pragma once

#ifndef COVNET_H
#define COVNET_H

#include <torch/torch.h>
#include "cnn_forward.h"
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

class ConvNetImpl : public torch::nn::Module {
 public:
    explicit ConvNetImpl(int64_t num_classes = NUM_CLASSES);
    torch::Tensor forward(torch::Tensor x);
	ModelWeights extract_weights();

 private:
    torch::nn::Sequential layer1{
		torch::nn::Conv2d(torch::nn::Conv2dOptions(INPUT_CHANNELS, FILTERS_LAYER1, KERNEL_SIZE).stride(1)), // Modifi� � un canal pour les images en noir et blanc
        torch::nn::BatchNorm2d(FILTERS_LAYER1),
        torch::nn::ReLU(),
        torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(2).stride(2))
    };

    torch::nn::Sequential layer2{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(FILTERS_LAYER1, FILTERS_LAYER2, KERNEL_SIZE).stride(1)),
        torch::nn::BatchNorm2d(FILTERS_LAYER2),
        torch::nn::ReLU(),
        torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(2).stride(2))
    };

    torch::nn::Sequential layer3{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(FILTERS_LAYER2, FILTERS_LAYER3, KERNEL_SIZE).stride(1)),
        torch::nn::BatchNorm2d(FILTERS_LAYER3),
        torch::nn::ReLU(),
    };

    torch::nn::AdaptiveAvgPool2d pool{torch::nn::AdaptiveAvgPool2dOptions({ADAPTIVE_POOL_WIDTH, ADAPTIVE_POOL_WIDTH})};

    torch::nn::Linear fc;
};

TORCH_MODULE(ConvNet);

#endif // COVNET_H
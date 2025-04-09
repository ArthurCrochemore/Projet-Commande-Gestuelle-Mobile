#include <vector>
#include <iostream>
#include "../application/src/learning/imageadapter.h"

#ifndef CUSTOM_CONV_H
#define CUSTOM_CONV_H

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

class CustomConv {
private:
    static int last_output_width;
    static int last_output_height;

public:
	static std::vector<picture_vector> apply_convolution(
        const std::vector<picture_vector>& inputs,
        const weight_tensor& weights, // Correction
        const tensor_1D& biases,
        int input_width, int input_height, int input_channels, int kernel_size);

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

    static tensor_1D apply_fully_connected(
        const tensor_1D& input,
        const tensor_2D& weights,
        const tensor_1D& biases);

	static int get_last_output_width() {
		return last_output_width;
	}

	static int get_last_output_height() {
		return last_output_height;
	}
};

#endif // CUSTOM_CONV_H
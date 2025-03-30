#include <vector>
#include <iostream>
#include "../application/src/learning/imageadapter.h"

#ifndef CUSTOM_CONV_H
#define CUSTOM_CONV_H

// Structure pour stocker les poids du modele
struct LayerParams {
    std::vector < std::vector < std::vector< std::vector<greyscale_value>>>> weights;
    std::vector<greyscale_value> biases;
    std::vector<greyscale_value> bn_weight;
    std::vector<greyscale_value> bn_bias;
    std::vector<greyscale_value> bn_running_mean;
    std::vector<greyscale_value> bn_running_var;
};

struct ModelWeights {
    LayerParams layer1;
    LayerParams layer2;
    LayerParams layer3;
    // Add fully connected layer params if necessary
    std::vector<std::vector<greyscale_value>> fc_weights;
    std::vector<greyscale_value> fc_biases;
};

class CustomConv {
private:
    static int last_output_width;
    static int last_output_height;

public:
	static std::vector<std::vector<std::vector<greyscale_value>>> apply_convolution(
        const std::vector<std::vector<std::vector<greyscale_value>>>& inputs,
        const std::vector<std::vector<std::vector<std::vector<greyscale_value>>>>& weights, // Correction
        const std::vector<greyscale_value>& biases,
        int input_width, int input_height, int input_channels, int kernel_size);

    static void apply_batch_norm(
        std::vector<std::vector<std::vector<greyscale_value>>>& feature_maps,
        const std::vector<greyscale_value>& bn_weight,
        const std::vector<greyscale_value>& bn_bias,
        const std::vector<greyscale_value>& bn_running_mean,
        const std::vector<greyscale_value>& bn_running_var);

    static void apply_relu(std::vector<std::vector<std::vector<greyscale_value>>>& feature_maps);

    static std::vector<greyscale_value> flatten(const std::vector<std::vector<std::vector<greyscale_value>>>& feature_maps);

    static std::vector<greyscale_value> apply_fully_connected(
        const std::vector<greyscale_value>& input,
        const std::vector<std::vector<greyscale_value>>& weights,
        const std::vector<greyscale_value>& biases);

	static int get_last_output_width() {
		return last_output_width;
	}

	static int get_last_output_height() {
		return last_output_height;
	}
};

#endif // CUSTOM_CONV_H
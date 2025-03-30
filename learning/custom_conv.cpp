#include "custom_conv.h"

std::vector<std::vector<std::vector<greyscale_value>>> CustomConv::apply_convolution(
    const std::vector<std::vector<std::vector<greyscale_value>>>& inputs,
    const std::vector<std::vector<std::vector<std::vector<greyscale_value>>>>& weights,
    const std::vector<greyscale_value>& biases,
    int input_width, int input_height, int input_channels, int kernel_size) {

    int output_width = input_width - kernel_size + 1;
    int output_height = input_height - kernel_size + 1;
    int num_filters = weights.size();

    // Initialise une matrice 3D pour stocker les r�sultats
    std::vector<std::vector<std::vector<greyscale_value>>> output(
        num_filters, std::vector<std::vector<greyscale_value>>(output_height, std::vector<greyscale_value>(output_width, 0))
    );

    // Applique la convolution sur chaque filtre
    for (int f = 0; f < num_filters; ++f) {
        for (int i = 0; i < output_height; ++i) {
            for (int j = 0; j < output_width; ++j) {
                greyscale_value sum = biases[f];

                // Appliquer le filtre sur tous les canaux d'entr�e
                for (int c = 0; c < input_channels; ++c) {
                    for (int ki = 0; ki < kernel_size; ++ki) {
                        for (int kj = 0; kj < kernel_size; ++kj) {
                            int input_x = j + kj;
                            int input_y = i + ki;

                            greyscale_value input_value = inputs[c][input_y][input_x];
                            greyscale_value weight_value = weights[f][c][ki][kj];

                            sum += input_value * weight_value;
                        }
                    }
                }

                output[f][i][j] = sum;
            }
        }
    }

    return output;
}

void CustomConv::apply_batch_norm(
    std::vector<std::vector<std::vector<greyscale_value>>>& feature_maps,
    const std::vector<greyscale_value>& bn_weight,
    const std::vector<greyscale_value>& bn_bias,
    const std::vector<greyscale_value>& bn_running_mean,
    const std::vector<greyscale_value>& bn_running_var) {

    int num_filters = feature_maps.size();
    int height = feature_maps[0].size();
    int width = feature_maps[0][0].size();

    for (int f = 0; f < num_filters; ++f) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                feature_maps[f][i][j] = bn_weight[f] *
                    (feature_maps[f][i][j] - bn_running_mean[f]) /
                    sqrt(bn_running_var[f] + 1e-5) + bn_bias[f];
            }
        }
    }
}

void CustomConv::apply_relu(std::vector<std::vector<std::vector<greyscale_value>>>& feature_maps) {
    int num_filters = feature_maps.size();
    int height = feature_maps[0].size();
    int width = feature_maps[0][0].size();

    for (int f = 0; f < num_filters; ++f) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                feature_maps[f][i][j] = std::max(feature_maps[f][i][j], static_cast<greyscale_value>(0));
            }
        }
    }
}

std::vector<greyscale_value> CustomConv::flatten(
    const std::vector<std::vector<std::vector<greyscale_value>>>& feature_maps) {

    std::vector<greyscale_value> flat_vector;

    for (const auto& channel : feature_maps) {
        for (const auto& row : channel) {
            flat_vector.insert(flat_vector.end(), row.begin(), row.end());
        }
    }
    return flat_vector;
}

std::vector<greyscale_value> CustomConv::apply_fully_connected(
    const std::vector<greyscale_value>& input,
    const std::vector<std::vector<greyscale_value>>& weights,
    const std::vector<greyscale_value>& biases) {

    int output_size = biases.size();
    int input_size = input.size();

    // TODO : Corriger bug ici : problème entre la taille des poids de la couche FC et la taille de l'entrée
    if (weights.size() != output_size) {
        std::cerr << "Error: The weight matrix has incorrect number of rows" << std::endl;
        return {};
    }
    for (const auto& row : weights) {
        if (row.size() != input_size) {
			std::cout << "Row size: " << row.size() << " Input size: " << input_size << std::endl;
            std::cerr << "Error: The weight matrix has incorrect number of columns" << std::endl;
            return {};
        }
    }

    std::vector<greyscale_value> output(output_size, 0);

    for (int i = 0; i < output_size; ++i) {
        greyscale_value sum = biases[i];

        for (int j = 0; j < input_size; ++j) {
            sum += input[j] * weights[i][j];
        }

        output[i] = sum;
    }

    return output;
}
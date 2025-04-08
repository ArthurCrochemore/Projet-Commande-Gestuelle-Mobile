#include "custom_conv.h"

std::vector<picture_vector> CustomConv::apply_convolution(
    const std::vector<picture_vector>& inputs, // 3 dimensions : n feature_maps
	const weight_tensor& weights, // 4 dimensions : n filters, n channels, kernel height, kernel width
    const tensor_1D& biases,
    int input_width, int input_height, int input_channels, int kernel_size) {

    int output_width = input_width - kernel_size + 1;
    int output_height = input_height - kernel_size + 1;
    int num_filters = weights.size(); // Nombres de channels de sortie 

    // Initialise une matrice 3D pour stocker les r�sultats
    std::vector<picture_vector> output(
        num_filters, picture_vector(output_height, picture_vector1D(output_width, 0))
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
    std::vector<picture_vector>& feature_maps,
    const tensor_1D& bn_weight,
    const tensor_1D& bn_bias,
    const tensor_1D& bn_running_mean,
    const tensor_1D& bn_running_var) {

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

void CustomConv::apply_relu(std::vector<picture_vector>& feature_maps) {
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

tensor_1D CustomConv::flatten(
    const std::vector<picture_vector>& feature_maps) {

    tensor_1D flat_vector;

    for (const auto& channel : feature_maps) {
        for (const auto& row : channel) {
            flat_vector.insert(flat_vector.end(), row.begin(), row.end());
        }
    }
    return flat_vector;
}

tensor_1D CustomConv::apply_fully_connected(
    const tensor_1D& input,
    const tensor_2D& weights,
    const tensor_1D& biases) {

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

    tensor_1D output(output_size, 0);

    for (int i = 0; i < output_size; ++i) {
        greyscale_value sum = biases[i];

        for (int j = 0; j < input_size; ++j) {
            sum += input[j] * weights[i][j];
        }

        output[i] = sum;
    }

    return output;
}
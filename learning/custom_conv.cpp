#include "custom_conv.h"

std::vector<picture_vector> CustomConv::apply_convolution(
	const std::vector<picture_vector>& inputs, // 3 dimensions : n feature_maps, height, width
	const weight_tensor& weights, // 4 dimensions : n filters, n channels, kernel height, kernel width
    const tensor_1D& biases,
    int input_width, int input_height, int input_channels, int kernel_size) {

	int output_width = input_width - kernel_size + 1; // Longueur des feature maps de sortie
	int output_height = input_height - kernel_size + 1; // Hauteur des feature maps de sortie
    int num_filters = weights.size(); // Nombres de channels de sortie 

    // Initialise une matrice 3D pour stocker les résultats
    std::vector<picture_vector> output(
        num_filters, picture_vector(output_height, picture_vector1D(output_width, 0))
    );

    // On calcule nos canaux de sortie 1 par 1
    for (int f = 0; f < num_filters; ++f) {
		// Pour le calcul du canal de sortie f, on va utilisé le filtre f et calculé chachune de ses activations
        for (int i = 0; i < output_height; ++i) {
            for (int j = 0; j < output_width; ++j) {
                greyscale_value sum = biases[f]; // On récupère le biais lié au filtre f

				// Pour l'activation (i, j) du canal de sortie f, on traite les canaux d'entrée 1 par 1
                for (int c = 0; c < input_channels; ++c) {
					auto input_feature_map = inputs[c]; // On récupère le canal d'entrée c

					// Pour ce canal d'entrée, on applique le filtre de taille kernel_size x kernel_size
                    for (int kx = 0; kx < kernel_size; ++kx) {
                        for (int ky = 0; ky < kernel_size; ++ky) {
                            int idx_i = i + kx;
                            int idx_j = j + ky;

                            greyscale_value input_value = input_feature_map[idx_i][idx_j];
                            greyscale_value weight_value = weights[f][c][kx][ky];

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
                float inv_sqrt_var = 1.0f / sqrt(bn_running_var[f] + 1e-5);
                feature_maps[f][i][j] = bn_weight[f] * 
                    (feature_maps[f][i][j] - bn_running_mean[f]) * 
                    inv_sqrt_var + bn_bias[f];
            }
        }
    }
}

void CustomConv::apply_relu(std::vector<picture_vector>& feature_maps) {
    int num_filters = feature_maps.size();
    int height = feature_maps[0].size();
    int width = feature_maps[0][0].size();

    const greyscale_value zero = static_cast<greyscale_value>(0);

    for (int f = 0; f < num_filters; ++f) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                feature_maps[f][i][j] = std::max(feature_maps[f][i][j], zero);
            }
        }
    }
}

void CustomConv::apply_max_pooling_2D(
    std::vector<picture_vector>& feature_maps,  // Les feature maps à traiter
    int kernel_size,  // Taille du noyau de max pooling (par défaut 2x2)
    int stride        // Le stride (pas de déplacement) du max pooling (par défaut 2)
) {
    int num_filters = feature_maps.size(); // Nombre de feature maps
    int height = feature_maps[0].size();   // Hauteur des feature maps
    int width = feature_maps[0][0].size(); // Largeur des feature maps

    int output_height = (height - kernel_size) / stride + 1;
    int output_width = (width - kernel_size) / stride + 1;

    std::vector<picture_vector> pooled_feature_maps(
        num_filters, picture_vector(output_height, picture_vector1D(output_width, 0))
    );

    for (int f = 0; f < num_filters; ++f) {
        for (int i = 0; i < output_height; ++i) {
            for (int j = 0; j < output_width; ++j) {
                greyscale_value max_val = -std::numeric_limits<greyscale_value>::infinity(); 

                for (int kx = 0; kx < kernel_size; ++kx) {
                    for (int ky = 0; ky < kernel_size; ++ky) {
                        int idx_i = i * stride + kx;
                        int idx_j = j * stride + ky;

                        if (idx_i < height && idx_j < width) {
                            greyscale_value value = feature_maps[f][idx_i][idx_j];
                            max_val = std::max(max_val, value);
                        }
                    }
                }

                pooled_feature_maps[f][i][j] = max_val;
            }
        }
    }

    feature_maps = std::move(pooled_feature_maps);
}

void CustomConv::apply_adaptive_avg_pool(std::vector<picture_vector>& feature_maps, int new_width, int new_height) {
    int num_filters = feature_maps.size();
    int input_height = feature_maps[0].size();
    int input_width = feature_maps[0][0].size();

    int pool_height = input_height / new_height;
    int pool_width = input_width / new_width;

    std::vector<picture_vector> pooled_output(
        num_filters, picture_vector(new_height, picture_vector1D(new_width, 0))
    );

    for (int f = 0; f < num_filters; ++f) {
        for (int i = 0; i < new_height; ++i) {
            for (int j = 0; j < new_width; ++j) {
                greyscale_value sum = 0;
                for (int ph = 0; ph < pool_height; ++ph) {
                    for (int pw = 0; pw < pool_width; ++pw) {
                        int idx_h = i * pool_height + ph;
                        int idx_w = j * pool_width + pw;
                        sum += feature_maps[f][idx_h][idx_w];
                    }
                }

                pooled_output[f][i][j] = sum / (pool_height * pool_width);
            }
        }
    }

    feature_maps = pooled_output;
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
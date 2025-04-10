#include "cnn_backward.h"

tensor_1D CNNBackward::backward_fully_connected(
    const tensor_1D& d_out,
    const tensor_2D& weights,
    const tensor_1D& biases,
    tensor_2D& grad_weights,
    tensor_1D& grad_biases,
    const tensor_1D& input) {

    int output_size = d_out.size();
    int input_size = input.size();
    
    grad_weights.assign(output_size, std::vector<float>(input_size, 0.0f));
    grad_biases.assign(output_size, 0.0f);
    tensor_1D d_input(input_size, 0.0f);

    for (int i = 0; i < output_size; ++i) {
        grad_biases[i] = d_out[i];

        for (int j = 0; j < input_size; ++j) {
            grad_weights[i][j] += d_out[i] * input[j];
            d_input[j] += d_out[i] * weights[i][j];
        }
    }

    return d_input;
}

std::vector<picture_vector> CNNBackward::unflatten(
    const tensor_1D& flat,
    int channels,
    int height,
    int width) {

    std::vector<picture_vector> output(channels,
        picture_vector(height, std::vector<greyscale_value>(width)));

    int index = 0;
    int expected_size = channels * height * width;

    for (int c = 0; c < channels; ++c) {
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                output[c][h][w] = flat[index++];
            }
        }
    }
    return output;
}

std::vector<picture_vector> CNNBackward::backward_convolution(
    const std::vector<picture_vector>& d_out,
    const std::vector<picture_vector>& input,
    const std::vector<std::vector<picture_vector>>& weights,
    std::vector<std::vector<picture_vector>>& grad_weights,
    std::vector<float>& grad_biases) {

    int out_channels = d_out.size();
    int in_channels = input.size();
    int kernel_size = weights[0][0].size();

    int out_height = d_out[0].size();
    int out_width = d_out[0][0].size();
    int in_height = input[0].size();
    int in_width = input[0][0].size();

    grad_weights.assign(out_channels, std::vector<picture_vector>(in_channels,
        picture_vector(kernel_size, std::vector<greyscale_value>(kernel_size, 0.0f))));
    grad_biases.assign(out_channels, 0.0f);

    std::vector<picture_vector> d_input(in_channels,
        picture_vector(in_height, std::vector<greyscale_value>(in_width, 0.0f)));

    for (int oc = 0; oc < out_channels; ++oc) {
        for (int i = 0; i < out_height; ++i) {
            for (int j = 0; j < out_width; ++j) {
                float delta = d_out[oc][i][j];
                grad_biases[oc] += delta;

                for (int ic = 0; ic < in_channels; ++ic) {
                    for (int ki = 0; ki < kernel_size; ++ki) {
                        for (int kj = 0; kj < kernel_size; ++kj) {
                            int in_i = i + ki;
                            int in_j = j + kj;
                            if (in_i < in_height && in_j < in_width) {
                                grad_weights[oc][ic][ki][kj] += input[ic][in_i][in_j] * delta;
                                d_input[ic][in_i][in_j] += weights[oc][ic][ki][kj] * delta;
                            }
                        }
                    }
                }
            }
        }
    }

    return d_input;
}

void CNNBackward::backward_batch_norm(
    const std::vector<picture_vector>& d_out,
    const std::vector<picture_vector>& input,
    const tensor_1D& gamma,
    const tensor_1D& beta,
    const tensor_1D& mean,
    const tensor_1D& variance,
    std::vector<picture_vector>& d_input,
    tensor_1D& grad_gamma,
    tensor_1D& grad_beta) {

    int channels = input.size();
    int height = input[0].size();
    int width = input[0][0].size();

    grad_gamma.assign(channels, 0.0f);
    grad_beta.assign(channels, 0.0f);

    for (int c = 0; c < channels; ++c) {
        float inv_std = 1.0f / sqrt(variance[c] + 1e-5f);

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                float normalized = (input[c][i][j] - mean[c]) * inv_std;
                grad_gamma[c] += d_out[c][i][j] * normalized;
                grad_beta[c] += d_out[c][i][j];
                d_input[c][i][j] = gamma[c] * inv_std * (d_out[c][i][j] - grad_beta[c] / (height * width) -
                    normalized * grad_gamma[c] / (height * width));
            }
        }
    }
}

void CNNBackward::backward_relu(
    const std::vector<picture_vector>& d_out,
    const std::vector<picture_vector>& input,
    std::vector<picture_vector>& d_input) {

    int channels = input.size();
    int height = input[0].size();
    int width = input[0][0].size();

    for (int c = 0; c < channels; ++c) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                d_input[c][i][j] = (input[c][i][j] > 0) ? d_out[c][i][j] : 0.0f;
            }
        }
    }
}

void CNNBackward::backward_max_pooling(
    const std::vector<picture_vector>& d_out,
    const std::vector<picture_vector>& input,
    std::vector<picture_vector>& d_input) {

    int channels = input.size();
    int height = input[0].size();
    int width = input[0][0].size();
    int pool_size = 2;
    int stride = 2;

    for (int c = 0; c < channels; ++c) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                d_input[c][i][j] = 0.0f;
            }
        }
    }

    for (int c = 0; c < channels; ++c) {
        for (int i = 0; i < height / stride; ++i) {
            for (int j = 0; j < width / stride; ++j) {
                float max_val = -std::numeric_limits<float>::infinity();
                int max_i = -1, max_j = -1;

                for (int di = 0; di < pool_size; ++di) {
                    for (int dj = 0; dj < pool_size; ++dj) {
                        int ni = i * stride + di;
                        int nj = j * stride + dj;
                        if (input[c][ni][nj] > max_val) {
                            max_val = input[c][ni][nj];
                            max_i = ni;
                            max_j = nj;
                        }
                    }
                }

                d_input[c][max_i][max_j] += d_out[c][i][j];
            }
        }
    }
}



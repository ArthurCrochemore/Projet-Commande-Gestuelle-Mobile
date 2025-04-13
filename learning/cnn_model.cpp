#include "cnn_model.h"

CNNModel::CNNModel(const int num_conv_layers, const std::vector<int>& conv_layers_filters, 
	const int kernel_size, const size_t num_train) {
    // TODO : am�liorer le parametrage

    conv_weights.resize(num_conv_layers);
    conv_biases.resize(num_conv_layers);

	this->num_train = num_train;

    for (int i = 0; i < num_conv_layers; ++i) {
        int num_filters = conv_layers_filters[i];
        int input_channels = (i == 0) ? num_train : conv_layers_filters[i - 1];

        conv_weights[i].resize(num_filters);
        conv_biases[i].resize(num_filters, 0.0f); // Initialisation des biais à 0

        for (int f = 0; f < num_filters; ++f) {
            conv_weights[i][f].resize(input_channels);
            for (int c = 0; c < input_channels; ++c) {
                conv_weights[i][f][c] = picture_vector(kernel_size, picture_vector1D(kernel_size, 0.0f));
                // Initialisation aléatoire des poids
                for (int kx = 0; kx < kernel_size; ++kx) {
                    for (int ky = 0; ky < kernel_size; ++ky) {
                        conv_weights[i][f][c][kx][ky] = static_cast<float>(rand()) / RAND_MAX * 0.01f;
                    }
                }
            }
        }
    }

    // TODO : Vérifier l'initialisation
	this->last_conv_channels = conv_layers_filters.back();
	this->last_conv_height = kernel_size;
	this->last_conv_width = kernel_size;

    // Vérification des dimensions des poids après initialisation
    for (int i = 0; i < num_conv_layers; ++i) {
        int num_filters = conv_weights[i].size();
        int input_channels = conv_weights[i][0].size();
        int kernel_h = conv_weights[i][0][0].size();
        int kernel_w = conv_weights[i][0][0][0].size();

        std::cout << "Layer " << i << ": Filters=" << num_filters
                  << ", Input Channels=" << input_channels
                  << ", Kernel Size=" << kernel_h << "x" << kernel_w << std::endl;
    }

    bn_weights.resize(num_conv_layers);
    bn_biases.resize(num_conv_layers);
    bn_running_means.resize(num_conv_layers, tensor_1D(conv_layers_filters[0], 0.0f)); // Initialisation à 0
    bn_running_vars.resize(num_conv_layers, tensor_1D(conv_layers_filters[0], 1.0f)); // Initialisation à 1

    for (int i = 0; i < num_conv_layers; ++i) {
        bn_weights[i].resize(conv_layers_filters[i], 1.0f); // Initialisation des poids de batch norm à 1
        bn_biases[i].resize(conv_layers_filters[i], 0.0f);  // Initialisation des biais de batch norm à 0
        bn_running_means[i].resize(conv_layers_filters[i], 0.0f); // Initialisation des moyennes à 0
        bn_running_vars[i].resize(conv_layers_filters[i], 1.0f);  // Initialisation des variances à 1
    }

    // Define fc_input_size based on the last convolutional layer's output
    int fc_input_size = conv_layers_filters.back() * ADAPTIVE_POOL_WIDTH * ADAPTIVE_POOL_WIDTH; // Corrected size

    std::cout << "fc_input_size: " << fc_input_size << std::endl;

    fc_weights.resize(NUM_CLASSES, tensor_1D(fc_input_size, 0.0f)); // Initialize weights with correct size
    fc_biases.resize(NUM_CLASSES, 0.0f); // Initialize biases with correct size

    this->kernel_size = kernel_size;
}

/**
 * Déroule le forward du CNN sur un batch d'images
 * 
 * @param batch_pictures : batch d'images à traiter
 * @param all_feature_maps_batch : feature maps pour chaque image du batch
 * @return : le batch de prédictions
 */
tensor_2D CNNModel::forward(const std::vector<std::vector<picture_vector>>& batch_pictures, 
    std::vector<std::vector<std::vector<picture_vector>>>& all_feature_maps_batch) {

    tensor_2D batch_flattened;
    all_feature_maps_batch.clear();

    for (const auto& pictures : batch_pictures) {
        std::vector<picture_vector> feature_maps = pictures;
        std::vector<std::vector<picture_vector>> all_feature_maps;

        for (size_t i = 0; i < conv_weights.size(); ++i) {
            feature_maps = CNNForward::apply_convolution(
                feature_maps, conv_weights[i], conv_biases[i], kernel_size);

            CNNForward::apply_batch_norm(feature_maps,
                bn_weights[i], bn_biases[i],
                bn_running_means[i], bn_running_vars[i]);

            CNNForward::apply_relu(feature_maps);

            if (i != conv_weights.size() - 1) {
                CNNForward::apply_max_pooling_2D(feature_maps);
            }

            all_feature_maps.push_back(feature_maps);
        }

        CNNForward::apply_adaptive_avg_pool(feature_maps, ADAPTIVE_POOL_WIDTH, ADAPTIVE_POOL_WIDTH);
        tensor_1D flat = CNNForward::flatten(feature_maps);
        batch_flattened.push_back(flat);
        all_feature_maps_batch.push_back(all_feature_maps);
    }

    return CNNForward::apply_fully_connected(batch_flattened, fc_weights, fc_biases);
}

/**
 * Initialise les gradients pour la rétropropagation
 */
void CNNModel::initialize_gradients() {
    grad_conv_weights.resize(conv_weights.size());
    grad_conv_biases.resize(conv_weights.size());
    for (size_t i = 0; i < conv_weights.size(); ++i) {
        grad_conv_weights[i] = std::vector<std::vector<picture_vector>>(
            conv_weights[i].size(), std::vector<picture_vector>(
                conv_weights[i][0].size(), picture_vector(
                    conv_weights[i][0][0].size(), std::vector<float>(conv_weights[i][0][0][0].size(), 0.0f)
                )
            )
        );
        grad_conv_biases[i] = std::vector<float>(conv_weights[i].size(), 0.0f);
    }

    grad_bn_weights.resize(bn_weights.size());
    grad_bn_biases.resize(bn_biases.size());
    for (size_t i = 0; i < bn_weights.size(); ++i) {
        grad_bn_weights[i].resize(bn_weights[i].size(), 0.0f);
        grad_bn_biases[i].resize(bn_biases[i].size(), 0.0f);
    }

    grad_fc_weights = tensor_2D(fc_weights.size(), tensor_1D(fc_weights[0].size(), 0.0f));
    grad_fc_biases = tensor_1D(fc_biases.size(), 0.0f);
}

/**
 * Effectue la rétropropagation du CNN sur un batch d'images
 * 
 * @param batch_predicted : batch de prédictions
 * @param batch_expected : batch de valeurs attendues
 * @param all_feature_maps_batch : feature maps pour chaque image du batch
 */
void CNNModel::backward(const tensor_2D& batch_predicted, const tensor_2D& batch_expected, 
    const std::vector<std::vector<std::vector<picture_vector>>>& all_feature_maps_batch) {

    // TODO : Poursuivre la correction du backward
    this->initialize_gradients();

    for (size_t b = 0; b < batch_predicted.size(); ++b) {
        const tensor_1D& predicted = batch_predicted[b];
        const tensor_1D& expected = batch_expected[b];
        const auto& all_feature_maps = all_feature_maps_batch[b];

        tensor_1D loss_gradient(predicted.size());
        for (size_t i = 0; i < predicted.size(); ++i) {
            loss_gradient[i] = 2.0f * (predicted[i] - expected[i]);
        }

        tensor_1D d_fc_input = CNNBackward::backward_fully_connected(
            loss_gradient, fc_weights, fc_biases, grad_fc_weights, grad_fc_biases, flattened_batch[b]);

        std::vector<picture_vector> d_feature_maps = CNNBackward::unflatten(
            d_fc_input, last_conv_channels, last_conv_height, last_conv_width);

        for (int i = conv_weights.size() - 1; i >= 0; --i) {
            CNNBackward::backward_relu(
                d_feature_maps, all_feature_maps[i + 1], d_feature_maps);

            CNNBackward::backward_batch_norm(
                d_feature_maps, all_feature_maps[i + 1], bn_weights[i], bn_biases[i],
                bn_running_means[i], bn_running_vars[i],
                d_feature_maps, grad_bn_weights[i], grad_bn_biases[i]);

            d_feature_maps = CNNBackward::backward_convolution(
                d_feature_maps, all_feature_maps[i], conv_weights[i],
                grad_conv_weights[i], grad_conv_biases[i]);

            if (i > 0) {
                CNNBackward::backward_max_pooling(
                    d_feature_maps, all_feature_maps[i], d_feature_maps);
            }
        }
    }

    for (size_t i = 0; i < grad_fc_weights.size(); ++i) {
        for (size_t j = 0; j < grad_fc_weights[i].size(); ++j) {
            grad_fc_weights[i][j] /= batch_predicted.size();
        }
        grad_fc_biases[i] /= batch_predicted.size();
    }

    for (size_t i = 0; i < grad_conv_weights.size(); ++i) {
        for (size_t f = 0; f < grad_conv_weights[i].size(); ++f) {
            for (size_t c = 0; c < grad_conv_weights[i][f].size(); ++c) {
                for (size_t h = 0; h < grad_conv_weights[i][f][c].size(); ++h) {
                    for (size_t w = 0; w < grad_conv_weights[i][f][c][h].size(); ++w) {
                        grad_conv_weights[i][f][c][h][w] /= batch_predicted.size();
                    }
                }
            }
            grad_conv_biases[i][f] /= batch_predicted.size();
        }
    }
}

/**
 * Entraine le modèle CNN sur un ensemble d'images
 * 
 * @param inputs : ensemble d'images à traiter
 * @param num_classes : nombre de classes
 * @param batch_size : taille du batch
 * @param num_epochs : nombre d'epochs
 * @param learning_rate : taux d'apprentissage
 * @param weight_decay : taux de décroissance du poids
 */
void CNNModel::learn(const std::vector<ImageData>& inputs, const int64_t num_classes,
	const int64_t batch_size, const size_t num_epochs,
	const double learning_rate, const double weight_decay) {

    // On mélange les inputs
    std::vector<ImageData> shuffled_inputs = inputs;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled_inputs.begin(), shuffled_inputs.end(), g);

    // On créé nos ensembles d'entrainement et de test
    std::vector<ImageData> train_inputs(shuffled_inputs.begin(), shuffled_inputs.begin() + num_train);
    std::vector<ImageData> test_inputs(shuffled_inputs.begin() + num_train, shuffled_inputs.end());

    for (size_t epoch = 0; epoch < num_epochs; ++epoch) {
        double running_loss = 0.0;
        size_t num_correct = 0;

        for (size_t batch_start = 0; batch_start < train_inputs.size(); batch_start += batch_size) {
            size_t batch_end = std::min(batch_start + batch_size, train_inputs.size());
            std::vector<ImageData> batch(train_inputs.begin() + batch_start, train_inputs.begin() + batch_end);

            std::vector<std::vector<picture_vector>> batch_images;
            tensor_2D batch_labels;
            for (const auto& data : batch) {
                batch_images.push_back({data.pixelValues});
                tensor_1D label(num_classes, 0.0f);
                label[data.class_value] = 1.0f;
                batch_labels.push_back(label);
            }

            // Forward
            std::vector<std::vector<std::vector<picture_vector>>> all_feature_maps_batch;
            tensor_2D predictions = forward(batch_images, all_feature_maps_batch);

            // Calcul de la loss (MSE)
            double batch_loss = 0.0;
            for (size_t i = 0; i < predictions.size(); ++i) {
                for (size_t j = 0; j < predictions[i].size(); ++j) {
                    batch_loss += std::pow(predictions[i][j] - batch_labels[i][j], 2);
                }
            }
            batch_loss /= predictions.size();
            running_loss += batch_loss;

            // Backward
            backward(predictions, batch_labels, all_feature_maps_batch);

            // Mise à jour des poids
            for (size_t i = 0; i < conv_weights.size(); ++i) {
                for (size_t f = 0; f < conv_weights[i].size(); ++f) {
                    for (size_t c = 0; c < conv_weights[i][f].size(); ++c) {
                        for (size_t h = 0; h < conv_weights[i][f][c].size(); ++h) {
                            for (size_t w = 0; w < conv_weights[i][f][c][h].size(); ++w) {
                                conv_weights[i][f][c][h][w] -= learning_rate * grad_conv_weights[i][f][c][h][w];
                            }
                        }
                    }
                    conv_biases[i][f] -= learning_rate * grad_conv_biases[i][f];
                }
            }

            for (size_t i = 0; i < fc_weights.size(); ++i) {
                for (size_t j = 0; j < fc_weights[i].size(); ++j) {
                    fc_weights[i][j] -= learning_rate * grad_fc_weights[i][j];
                }
                fc_biases[i] -= learning_rate * grad_fc_biases[i];
            }
        }

        std::cout << "Epoch [" << (epoch + 1) << "/" << num_epochs << "], Loss: " << running_loss / train_inputs.size() << '\n';
    }
}

/**
 * Prédit la classe d'une image donnée
 * 
 * @param input_image : image à prédire
 * @return : classe prédite
 */
int CNNModel::predict(const picture_vector& input_image) {
    auto pre = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<picture_vector>> input_batch = {{input_image}};

    std::vector<std::vector<std::vector<picture_vector>>> all_feature_maps_batch;
    tensor_2D predictions = forward(input_batch, all_feature_maps_batch);

    int predicted_class = std::distance(predictions[0].begin(), std::max_element(predictions[0].begin(), predictions[0].end()));

    auto post = std::chrono::high_resolution_clock::now();
    std::cout << "Durée pour la prédiction: " 
             << std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count() 
             << " ms";

    return predicted_class;
}

/**
 * Extrait les poids du modèle CNN et les sauvegarde dans un fichier
 * 
 * @param type_name_classified : nom du type de classification (ex: "volume", "brightness")
 */
void CNNModel::extract_weights(const QString& type_name_classified) {
    QString path = QDir::cleanPath(QDir(QDir::currentPath()).absoluteFilePath("../database/" + type_name_classified));
    std::string absolute_path = path.toStdString();
    std::string weights_file = absolute_path + type_name_classified.toStdString() + "_weights.bin";

    std::ofstream file(weights_file, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'écrire dans: " + weights_file);
    }

    for (const auto& layer_weights : conv_weights) {
        for (const auto& filter_weights : layer_weights) {
            for (const auto& channel_weights : filter_weights) {
                for (const auto& row : channel_weights) {
                    file.write(reinterpret_cast<const char*>(row.data()), row.size() * sizeof(float));
                }
            }
        }
    }
    for (const auto& layer_biases : conv_biases) {
        file.write(reinterpret_cast<const char*>(layer_biases.data()), layer_biases.size() * sizeof(float));
    }

    for (const auto& layer_weights : bn_weights) {
        file.write(reinterpret_cast<const char*>(layer_weights.data()), layer_weights.size() * sizeof(float));
    }
    for (const auto& layer_biases : bn_biases) {
        file.write(reinterpret_cast<const char*>(layer_biases.data()), layer_biases.size() * sizeof(float));
    }

    for (const auto& class_weights : fc_weights) {
        file.write(reinterpret_cast<const char*>(class_weights.data()), class_weights.size() * sizeof(float));
    }
    file.write(reinterpret_cast<const char*>(fc_biases.data()), fc_biases.size() * sizeof(float));

    file.close();
    std::cout << "Poids extraits à: " << weights_file << std::endl;
}

/**
 * Charge les poids pré-entraînés dans le modèle CNN
 * 
 * @param type_name_classified : nom du type de classification (ex: "volume", "brightness")
 */
void CNNModel::load_weights(const std::string& type_name_classified) {
    QString path = QDir::cleanPath(QDir(QDir::currentPath()).absoluteFilePath("../database/"));
    std::string absolute_path = path.toStdString() + type_name_classified;
    std::string weights_file = absolute_path + type_name_classified + "_weights.bin";

    std::ifstream file(weights_file, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible de charger à partir de: " + weights_file);
    }

    for (auto& layer_weights : conv_weights) {
        for (auto& filter_weights : layer_weights) {
            for (auto& channel_weights : filter_weights) {
                for (auto& row : channel_weights) {
                    file.read(reinterpret_cast<char*>(row.data()), row.size() * sizeof(float));
                }
            }
        }
    }
    for (auto& layer_biases : conv_biases) {
        file.read(reinterpret_cast<char*>(layer_biases.data()), layer_biases.size() * sizeof(float));
    }

    for (auto& layer_weights : bn_weights) {
        file.read(reinterpret_cast<char*>(layer_weights.data()), layer_weights.size() * sizeof(float));
    }
    for (auto& layer_biases : bn_biases) {
        file.read(reinterpret_cast<char*>(layer_biases.data()), layer_biases.size() * sizeof(float));
    }

    for (auto& class_weights : fc_weights) {
        file.read(reinterpret_cast<char*>(class_weights.data()), class_weights.size() * sizeof(float));
    }
    file.read(reinterpret_cast<char*>(fc_biases.data()), fc_biases.size() * sizeof(float));

    file.close();
    std::cout << "Poids chargés depuis: " << weights_file << std::endl;
}

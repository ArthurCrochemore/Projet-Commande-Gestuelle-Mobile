#include <torch/torch.h>
#include <QApplication>
#include <QMainWindow>
#include <QImage>
#include <QDebug>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <cstring>
#include <random>
#include "convnet.h"
#include "custom_conv.h"
#include "../application/src/learning/imageadapter.h"

struct ImageData {
    std::vector<std::vector<greyscale_value>> pixelValues;
    int class_value;
};

struct Type {
    std::vector<QString> classes_names;
    uint8_t classes_count;
    uint8_t classes_size;
};

std::unordered_map<QString, Type> types = {
    {"volume", {{"null", "down", "up"}, 3, 100}} // Dimensions des images : 3000 x 4000
    // ajouter d'autres types ici ...
};

std::vector<ImageData> initialization(QString type_name, Type type) {
    using namespace std;

    vector<ImageData> pictures_vectorized;

    uint8_t class_idx = 0;
    for (QString str : type.classes_names) {
        for (uint8_t i = 0; i != type.classes_size; i++) {

            QString filename = "S:\\Sherbrooke\\Semestre_2\\Projet-Commande-Gestuelle-Mobile\\learning\\database\\"
                + type_name + "\\" + str + QString::number(i) + "_" + type_name + ".jpg"; // Chemin absolu vers les images

            QImage image(filename);
            if (image.isNull()) {
                qDebug() << "Image : " + filename + " is null";
                return {};
            }

            ImageData data;
            data.pixelValues = QImageToVectorAdapter{}.vectorize(image);
            data.class_value = class_idx;

            pictures_vectorized.push_back(data);
        }
        class_idx++;
    }

    return pictures_vectorized;
}

class CustomDataset : public torch::data::datasets::Dataset<CustomDataset> {
private:
    torch::Tensor images_, labels_;

public:
    CustomDataset(torch::Tensor images, torch::Tensor labels)
        : images_(std::move(images)), labels_(std::move(labels)) {
    }

    // Nombre total d'échantillons
    torch::optional<size_t> size() const override {
        return images_.size(0);
    }

    // Retourne un élément du dataset (image + label)
    torch::data::Example<> get(size_t index) override {
        return { images_[index], labels_[index] };
    }
};

// Basé sur le projet pytorch-cpp (https://github.com/prabhuomkar/pytorch-cpp/tree/master)
// Copyright (c) 2020-present, pytorch-cpp Authors
// Sous licence MIT
ConvNet training(const std::vector<ImageData>& inputs, const int64_t num_classes = 3, 
    const int64_t batch_size = BATCH_SIZE, const size_t num_epochs = NUM_EPOCH,
    const double learning_rate = 1e-3, const double weight_decay = 1e-3) {

    // Device
    auto cuda_available = torch::cuda::is_available();
    torch::Device device(cuda_available ? torch::kCUDA : torch::kCPU);
    std::cout << (cuda_available ? "CUDA available. Training on GPU." : "Training on CPU.") << '\n';

    // Début du chronomètre
    auto pre = std::chrono::high_resolution_clock::now();

    // Conversion des données en tenseurs
    auto convert_to_tensors = [](const std::vector<ImageData>& dataset) {
        std::vector<torch::Tensor> data_tensors;
        std::vector<int64_t> labels_vector;

        for (const auto& data : dataset) {
            std::vector<float> float_pixel_values;
            for (const auto& row : data.pixelValues) {
                float_pixel_values.insert(float_pixel_values.end(), row.begin(), row.end());
            }

            // Création du tenseur avec les dimensions appropriées [1, HEIGHT, WIDTH]
            torch::Tensor image_tensor = torch::from_blob(float_pixel_values.data(), { 1, HEIGHT, WIDTH }, torch::kFloat).clone();
            
            image_tensor = (image_tensor - 0.5) / 0.5;  // Normalisation [-1,1]

            data_tensors.push_back(image_tensor);
            labels_vector.push_back(static_cast<int64_t>(data.class_value));
        }

        // Empile les images et les labels
        torch::Tensor images = torch::stack(data_tensors).to(torch::kFloat);
        torch::Tensor labels = torch::tensor(labels_vector, torch::kLong);

        return std::make_pair(images, labels);
    };

    // Chargement des données (train / test)
    std::vector<ImageData> shuffled_inputs = inputs;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled_inputs.begin(), shuffled_inputs.end(), g);

    size_t num_train = static_cast<size_t>(0.8 * shuffled_inputs.size());
    std::vector<ImageData> train_inputs(shuffled_inputs.begin(), shuffled_inputs.begin() + num_train);
    std::vector<ImageData> test_inputs(shuffled_inputs.begin() + num_train, shuffled_inputs.end());

    // Conversion en tenseurs
    auto [train_images, train_labels] = convert_to_tensors(train_inputs);
    auto [test_images, test_labels] = convert_to_tensors(test_inputs);

    // Création des datasets
    auto train_dataset = CustomDataset(train_images, train_labels)
        .map(torch::data::transforms::Stack<>());
    auto test_dataset = CustomDataset(test_images, test_labels)
        .map(torch::data::transforms::Stack<>());

    // Nombre d'échantillons dans le testset
    auto num_train_samples = train_dataset.size().value();
    auto num_test_samples = test_dataset.size().value();

    // Data loader
    auto train_loader = torch::data::make_data_loader<torch::data::samplers::RandomSampler>(
        std::move(train_dataset), batch_size);
    auto test_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
        std::move(test_dataset), batch_size);

    qDebug() << "Samples crées";

    // Model
    ConvNet model(num_classes);
    model->to(device);

    // Optimizer
    torch::optim::Adam optimizer(
        model->parameters(), torch::optim::AdamOptions(learning_rate).weight_decay(weight_decay));

    // Set floating point output precision
    std::cout << std::fixed << std::setprecision(4);

    std::cout << "Training...\n";

    // Train the model
    for (size_t epoch = 0; epoch != num_epochs; ++epoch) {
        // Initialize running metrics
        double running_loss = 0.0;
        size_t num_correct = 0;

        for (auto& batch : *train_loader) {
            // Transfer images and target labels to device
            auto data = batch.data.to(device);
            auto target = batch.target.to(device);

            // Forward pass
            auto output = model->forward(data);

            // Calculate loss
            auto loss = torch::nn::functional::cross_entropy(output, target);

            // Update running loss
            running_loss += loss.item<double>() * data.size(0);

            // Calculate prediction
            auto prediction = output.argmax(1);

            // Update number of correctly classified samples
            num_correct += prediction.eq(target).sum().item<int64_t>();

            // Backward pass and optimize
            optimizer.zero_grad();
            loss.backward();
            optimizer.step();
        }

        auto sample_mean_loss = running_loss / num_train_samples;
        auto accuracy = static_cast<double>(num_correct) / num_train_samples;

        std::cout << "Epoch [" << (epoch + 1) << "/" << num_epochs << "], Trainset - Loss: "
            << sample_mean_loss << ", Accuracy: " << accuracy << '\n';
    }

    // Fin du chronomètre
    auto post = std::chrono::high_resolution_clock::now();

    qDebug() << "Training terminée en " << QString::number(std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count()) << " ms";

    std::cout << "Testing...\n";

    // Test the model
    model->eval();
    torch::InferenceMode no_grad;

    double running_loss = 0.0;
    size_t num_correct = 0;

    for (const auto& batch : *test_loader) {
        auto data = batch.data.to(device);
        auto target = batch.target.to(device);

        auto output = model->forward(data);

        auto loss = torch::nn::functional::cross_entropy(output, target);
        running_loss += loss.item<double>() * data.size(0);

        auto prediction = output.argmax(1);
        num_correct += prediction.eq(target).sum().item<int64_t>();
    }

    std::cout << "Testing finished!\n";

    auto test_accuracy = static_cast<double>(num_correct) / num_test_samples;
    auto test_sample_mean_loss = running_loss / num_test_samples;

    std::cout << "Testset - Loss: " << test_sample_mean_loss << ", Accuracy: " << test_accuracy << '\n';

    return model;
}

int prediction(ModelWeights& model, ImageData image) {
    // Début du chronomètre
    auto pre = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<std::vector<greyscale_value>>> input_image(1, image.pixelValues); // On passe l'image ene 3D

	std::cout << "Image width: " << WIDTH << " Image height: " << HEIGHT << std::endl;

    // Etape 1: Convolution Layer 1
    auto conv1_output = CustomConv::apply_convolution(input_image, model.layer1.weights, model.layer1.biases,
        WIDTH, HEIGHT, INPUT_CHANNELS, KERNEL_SIZE);

    int conv1_height = conv1_output[0].size();
    int conv1_width = conv1_output[0][0].size();
    int conv1_channels = conv1_output.size();

    std::cout << "Conv1 width: " << conv1_width << " Conv1 height: " << conv1_height << " Channels: " << conv1_channels << std::endl;

    CustomConv::apply_batch_norm(conv1_output, model.layer1.bn_weight, model.layer1.bn_bias, model.layer1.bn_running_mean, model.layer1.bn_running_var);
    CustomConv::apply_relu(conv1_output);

    // Etape 2: Convolution Layer 2
    auto conv2_output = CustomConv::apply_convolution(conv1_output, model.layer2.weights, model.layer2.biases,
        conv1_width, conv1_height, conv1_channels, KERNEL_SIZE);

    int conv2_channels = conv2_output.size();
    int conv2_height = conv2_output[0].size();
    int conv2_width = conv2_output[0][0].size();

    std::cout << "Conv2 width: " << conv2_width << " Conv2 height: " << conv2_height << " Channels: " << conv2_channels << std::endl;

    CustomConv::apply_batch_norm(conv2_output, model.layer2.bn_weight, model.layer2.bn_bias, model.layer2.bn_running_mean, model.layer2.bn_running_var);
    CustomConv::apply_relu(conv2_output);

    // Etape 3: Convolution Layer 3
    auto conv3_output = CustomConv::apply_convolution(conv2_output, model.layer3.weights, model.layer3.biases,
        conv2_width, conv2_height, conv2_channels, KERNEL_SIZE);

    int conv3_channels = conv3_output.size();
    int conv3_height = conv3_output[0].size();
    int conv3_width = conv3_output[0][0].size();

    std::cout << "Conv3 width: " << conv3_width << " Conv3 height: " << conv3_height << " Channels: " << conv3_channels << std::endl;

    CustomConv::apply_batch_norm(conv3_output, model.layer3.bn_weight, model.layer3.bn_bias, model.layer3.bn_running_mean, model.layer3.bn_running_var);
    CustomConv::apply_relu(conv3_output);

    // Etape 4: Applatissage de la sortie de la couche de convolution 3
    std::vector<float> flattened = CustomConv::flatten(conv3_output);
    
	std::cout << "Flattened size: " << flattened.size() << std::endl;
    
    // Etape 5: Fully Connected Layer
    auto fc_output = CustomConv::apply_fully_connected(flattened, model.fc_weights, model.fc_biases);

    // Etape 6: Calcule de la classe prédite
    int predicted_class = std::distance(fc_output.begin(), std::max_element(fc_output.begin(), fc_output.end()));

    // Fin du chronomètre
    auto post = std::chrono::high_resolution_clock::now();
    qDebug() << "Prediction terminée en " << QString::number(std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count()) << " ms";

    return predicted_class;
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QString type_name_classified = "volume";

    if (types.find(type_name_classified) == types.end()) {
        qDebug() << "Type name not found in types map.";
        return -1;
    }

    // Recuperation des donnees d'entrainement
    qDebug() << "Initialisation des donnees...";
    std::vector<ImageData> pictures_vectorized = initialization(type_name_classified, types[type_name_classified]);

    if (pictures_vectorized.empty()) {
        qDebug() << "Initialization failed. No images were loaded.";
        return -1;
    }

    // Entrainement du modele
    qDebug() << "Entrainement du modele...";
    auto model = training(pictures_vectorized, 3);
    qDebug() << "Entrainement termine.";

	auto extracted_model = model->extract_weights();

    // Test du modele
	qDebug() << "Test du modele...";
    std::unordered_map<int, int> predicted_classes{ {0, 0}, {1, 0}, {2, 0} };
    for (const auto& data : pictures_vectorized) {
        int predicted_class = prediction(extracted_model, data);
        qDebug() << "Classe predite : " << predicted_class << " vs Vraie classe : " << data.class_value;
		predicted_classes[predicted_class]++;
	}
	qDebug() << "Classes prédites : ";
	for (const auto& class_tuple : predicted_classes) {
		qDebug() << "Classe " << class_tuple.first << " prédites " << class_tuple.second << "fois";
	}

    return app.exec();
}
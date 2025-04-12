#include <torch/torch.h>
#include <QApplication>
#include <QImage>
#include <QDebug>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include "cnn_model.h"

#include <torch/torch.h>
#include "../application/src/learning/imageadapter.h"

struct Type {
    std::vector<QString> classes_names;
    uint8_t classes_count;
    uint8_t classes_size;
};

std::unordered_map<QString, Type> types = {
    {"volume", {{"null", "down", "up"}, 3, 10}} // Dimensions des images : 3000 x 4000
    // ajouter d'autres types ici ...
};


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

    // Initialisation du modèle CNN
    qDebug() << "Initialisation du modèle CNN...";
    const int num_conv_layers = 3;
    const std::vector<int> conv_layers_filters = {8, 16, 32};
    const int kernel_size = 3;
    const int num_train = 24; // Nb d'images en entrainement

    CNNModel model(num_conv_layers, conv_layers_filters, kernel_size, num_train);

    // Entrainement du modèle
    qDebug() << "Entrainement du modèle...";
    const int64_t num_classes = 3;
    const int64_t batch_size = 32;
    const size_t num_epochs = 10;
    const double learning_rate = 1e-3;
    const double weight_decay = 1e-3;

    model.learn(pictures_vectorized, num_classes, batch_size, num_epochs, learning_rate, weight_decay);
    qDebug() << "Entrainement terminé.";

    // Test du modèle
    qDebug() << "Test du modèle...";
    std::unordered_map<int, int> predicted_classes{{0, 0}, {1, 0}, {2, 0}};
    for (int i = 0; i < 300; i += 20) {
        const auto& data = pictures_vectorized[i];
        int predicted_class = model.predict(data);
        qDebug() << "Classe prédite : " << predicted_class << " vs Vraie classe : " << data.class_value;
        predicted_classes[predicted_class]++;
    }

    qDebug() << "Classes prédites : ";
    for (const auto& class_tuple : predicted_classes) {
        qDebug() << "Classe " << class_tuple.first << " prédites " << class_tuple.second << " fois";
    }

    return app.exec();
}
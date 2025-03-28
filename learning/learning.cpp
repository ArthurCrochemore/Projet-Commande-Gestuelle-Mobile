#include <torch/torch.h>
#include <QApplication>
#include <QMainWindow>
#include <QImage>
#include <QDebug>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include "../application/src/learning/imageadapter.h"

// Varaiables globales pour les dimensions des images
#define WIDTH 300
#define HEIGHT 400

struct ImageData {
    std::vector<double> pixelValues;
    int classe;
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

    vector<ImageData> pictures_vectorized{};

    uint8_t idx_classe = 0;
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
            data.classe = idx_classe;

            pictures_vectorized.push_back(data);
        }
		idx_classe++;
    }

    return pictures_vectorized;
}

// D�finition du mod�le CNN
struct Net : torch::nn::Module {
    torch::nn::Linear fc1{ nullptr };
    torch::nn::Linear fc2{ nullptr };
    torch::nn::Linear fc3{ nullptr };

    Net() {
            fc1 = register_module("fc1", torch::nn::Linear(WIDTH * HEIGHT, 4096)); // Taille adapt�e � 300x400 pixels
            fc2 = register_module("fc2", torch::nn::Linear(4096, 1024));
            fc3 = register_module("fc3", torch::nn::Linear(1024, 3));
    }

    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(fc1->forward(x));
        x = torch::relu(fc2->forward(x));
        x = fc3->forward(x);
        return torch::log_softmax(x, 1);
    }
};

Net entrainement(std::vector<ImageData> inputs) {
    // Conversion des donn�es en tenseurs
    std::vector<torch::Tensor> data_tensors;
    std::vector<torch::Tensor> labels_tensors;

    for (const auto& data : inputs) {
        torch::Tensor image_tensor = torch::tensor(data.pixelValues).view({ 1, WIDTH * HEIGHT });
        torch::Tensor label_tensor = torch::tensor({ data.classe }, torch::kLong);
        data_tensors.push_back(image_tensor);
        labels_tensors.push_back(label_tensor);
    }

    auto images = torch::cat(data_tensors, 0);
    auto labels = torch::cat(labels_tensors, 0);

    Net model;
    model.train();

    // D�finition de l'optimiseur et de la fonction de perte
    torch::optim::SGD optimizer(model.parameters(), torch::optim::SGDOptions(0.01));
    auto loss_function = torch::nn::NLLLoss();

    // Entra�nement du mod�le
    for (size_t epoch = 0; epoch < 10; ++epoch) {
        optimizer.zero_grad();
        torch::Tensor output = model.forward(images);
        torch::Tensor loss = loss_function(output, labels);
        loss.backward();
        optimizer.step();

        std::cout << "Epoch: " << epoch + 1 << " Loss: " << loss.item<float>() << std::endl;
    }

    return model;
}

int prediction(Net& model, ImageData image) {
    model.eval(); 

    torch::Tensor image_tensor = torch::tensor(image.pixelValues).view({ 1, WIDTH * HEIGHT });

    torch::Tensor output = model.forward(image_tensor);

    int predicted_class = output.argmax(1).item<int>();

    return predicted_class;
}

int main(int argc, char *argv[]) {
    QString type_name_classified = "volume";

    QApplication app(argc, argv);

	// R�cup�rations des donn�es d'entrainement
	qDebug() << "Initialisation des donn�es...";
    std::vector<ImageData> pictures_vectorized = initialization(type_name_classified, types[type_name_classified]);

    // Entrainement du modele
	qDebug() << "Entrainement du mod�le...";
	auto model = entrainement(pictures_vectorized);
	qDebug() << "Entrainement termin�.";

	// Test du mod�le
    std::unordered_map<int, int> classes_predites{ {0, 0}, {1, 0}, {2, 0} };
	for (const auto& data : pictures_vectorized) {
		int predicted_class = prediction(model, data);
		qDebug() << "Classe pr�dite : " << predicted_class << " vs Vraie classe : " << data.classe;
		classes_predites[predicted_class]++;
	}
	qDebug() << "Classes pr�dites : ";
	for (const auto& classe : classes_predites) {
		qDebug() << "Classe " << classe.first << " pr�dites " << classe.second << "fois";
	}

    return app.exec();
}
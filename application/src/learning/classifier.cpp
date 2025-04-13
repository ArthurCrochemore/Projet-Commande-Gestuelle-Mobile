#include "classifier.h"

const uint8_t BrightnessClassifier::NOTHING;
const uint8_t BrightnessClassifier::UP;
const uint8_t BrightnessClassifier::DOWN;

const uint8_t VolumeClassifier::NOTHING;
const uint8_t VolumeClassifier::UP;
const uint8_t VolumeClassifier::DOWN;

IClassifier::IClassifier() {
    cnnModel = new CNNModel(3, {8, 16, 32}, 3, 240);
}

/**
 * Fonction réalisant la classification d'une image pour le contrôle du volume
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
void IClassifier::initialize(QString type_name_classified) {
    QString path = QDir::cleanPath(QDir(QDir::currentPath()).absoluteFilePath("../database/"));
    std::string absolute_path = path.toStdString() + type_name_classified.toStdString();
    std::string weights_file = absolute_path + type_name_classified.toStdString() + "_weights.bin";

    cnnModel->load_weights(weights_file);
}

/**
 * Fonction réalisant la classification d'une image pour le contrôle du volume
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t VolumeClassifier::predict(picture_vector& features) {
    // TODO : Implémentation du modèle de prédiction entrainé pour interpréter des signes pour le volume

    return VolumeClassifier::UP;
}


/**
 * Fonction réalisant la classification d'une image pour le contrôle de la luminosité
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t BrightnessClassifier::predict(picture_vector&  features) {
    // TODO : Implémentation du modèle de prédiction entrainé pour interpréter des signes pour la luminosité

    return BrightnessClassifier::UP;
}

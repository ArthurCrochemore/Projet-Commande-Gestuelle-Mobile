#include "classifier.h"
#include "../../../learning/cnn_model.h"

const uint8_t BrightnessClassifier::NOTHING;
const uint8_t BrightnessClassifier::UP;
const uint8_t BrightnessClassifier::DOWN;

const uint8_t VolumeClassifier::NOTHING;
const uint8_t VolumeClassifier::UP;
const uint8_t VolumeClassifier::DOWN;

static CNNModel model(3, {8, 16, 32}, 3, 240);

/**
 * Fonction réalisant la classification d'une image pour le contrôle du volume
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
void Classifier::initialize(QString type_name_classified) {
    QString path = QDir::cleanPath(QDir(QDir::currentPath()).absoluteFilePath("../database/"));
    std::string absolute_path = path.toStdString() + type_name_classified;
    std::string weights_file = absolute_path + type_name_classified + "_weights.bin";

    cnnModel.load_weights(weights_file);
}

/**
 * Fonction réalisant la classification d'une image pour le contrôle du volume
 * 
 * @param features : image vectorisée
 * @param actionType : type d'action (volume ou luminosité)
 * @return : classe prédite
 */
uint8_t Classifier::predict(const picture_vector& features, const uint8_t actionType) {
    switch(actionType) {
        case Classifier::VOLUME:
            this.initialize("volume");
            break;
        case Classifier::BRIGHTNESS:
            this.initialize("brightness");
            break;
        default:
            return -1; // Erreur : type d'action inconnu
    }
    return cnnModel.predict(features);
}

#include "classifier.h"

const uint8_t BrightnessClassifier::NOTHING;
const uint8_t BrightnessClassifier::UP;
const uint8_t BrightnessClassifier::DOWN;

const uint8_t VolumeClassifier::NOTHING;
const uint8_t VolumeClassifier::UP;
const uint8_t VolumeClassifier::DOWN;


/**
 * Fonction réalisant la classification d'une image pour le contrôle du volume
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t VolumeClassifier::predict(const picture_vector& features) {
    // TODO : Implémentation du modèle de prédiction entrainé pour interpréter des signes pour le volume

    return VolumeClassifier::UP;
}


/**
 * Fonction réalisant la classification d'une image pour le contrôle de la luminosité
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t BrightnessClassifier::predict(const picture_vector&  features) {
    // TODO : Implémentation du modèle de prédiction entrainé pour interpréter des signes pour la luminosité

    return BrightnessClassifier::UP;
}

uint8_t Classifier::predict(const picture_vector& features, const uint8_t actionType) {
    switch(actionType) {
        case Classifier::VOLUME:
            return VolumeClassifier::predict(features);
        case Classifier::BRIGHTNESS:
            return BrightnessClassifier::predict(features);
        default:
            return -1; // Erreur : type d'action inconnu
    }
}

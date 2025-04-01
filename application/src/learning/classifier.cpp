#include "./classifier.h"

/**
 * Fonction réalisant la classification d'une image pour le contrôle du volume
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t VolumeClassifier::predict(std::vector<std::vector<greyscale_value>>& features) {
    // TODO : Implémentation du modèle de prédiction entrainé pour interpréter des signes pour le volume

    return VolumeClassifier::UP;
}


/**
 * Fonction réalisant la classification d'une image pour le contrôle de la luminosité
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t BrightnessClassifier::predict(std::vector<std::vector<greyscale_value>>&  features) {
    // TODO : Implémentation du modèle de prédiction entrainé pour interpréter des signes pour la luminosité

    return BrightnessClassifier::UP;
}
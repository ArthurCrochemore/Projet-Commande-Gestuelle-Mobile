#include "serviceidentify.h"

/**
 * Fonction initialisant le service d'identification de l'action lié au volume à réaliser en fonction de l'image
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t ServiceIdentifyActionVolume::identify(picture_vector& features) {
    // TODO : Implémentation de l'identification d'une action lié au volume
    return VolumeClassifier::UP;
}

/**
 * Fonction initialisant le service d'identification de l'action lié à la luminosité à réaliser en fonction de l'image
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t ServiceIdentifyActionBrightness::identify(picture_vector& features) {
    // TODO : Implémentation de l'identification d'une action lié au volume
    return BrightnessClassifier::UP;
}

/**
 * Fonction initialisant le service d'identification de l'action à réaliser en fonction de l'image
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t ServiceIdentifyAction::identify(picture_vector& features, uint8_t actionType) {
    switch (actionType) {
        case ServiceIdentifyAction::VOLUME:
            return ServiceIdentifyActionVolume::identify(features);
        case ServiceIdentifyAction::BRIGHTNESS:
            return ServiceIdentifyActionBrightness::identify(features);
        default:
            break;
    }
    return VolumeClassifier::UP;
}

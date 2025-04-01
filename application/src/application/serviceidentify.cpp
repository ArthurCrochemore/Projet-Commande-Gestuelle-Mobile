#include "serviceidentify.h"

/**
 * Fonction initialisant le service d'identification de l'action lié au volume à réaliser en fonction de l'image
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t ServiceIdentifyActionVolume::identify(std::vector<std::vector<greyscale_value>>& features) {
    // TODO : Implémentation de l'identification d'une action lié au volume
    return VolumeClassifier::UP;
}

/**
 * Fonction initialisant le service d'identification de l'action lié à la luminosité à réaliser en fonction de l'image
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t ServiceIdentifyActionBrightness::identify(std::vector<std::vector<greyscale_value>>& features) {
    // TODO : Implémentation de l'identification d'une action lié au volume
    return BrightnessClassifier::UP;
}

/**
 * Fonction responsable de la création d'une action d'identification en fonction du type d'action
 * 
 * @param actionType : type d'action à réaliser
 * @return : action d'identification à réaliser
 */
IServiceIdentifyAction* IdentifyActionFactory::createIdentifyAction(uint8_t actionType) {
    switch (actionType) {
        case IdentifyActionFactory::VOLUME: return new ServiceIdentifyActionVolume();
        case IdentifyActionFactory::BRIGHTNESS: return new ServiceIdentifyActionBrightness();
        default: return nullptr;
    }
}

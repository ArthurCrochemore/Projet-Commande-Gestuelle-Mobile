#include "executeactioncommand.h"

/**
 * Fonction réalisant les actions sur le volume de l'appareil, en fontion de la classification
 * 
 * @param predicted : classification de l'image
 * @return : void
 */
void ExecuteActionCommandVolume::execute(uint8_t predicted) {
    switch(predicted) {
        case VolumeClassifier::NOTHING:
            break;
        case VolumeClassifier::UP:
            // TODO : Implémentation de l'action pour augmenter le volume
            break;
        case VolumeClassifier::DOWN:
            // TODO : Implémentation de l'action pour diminuer le volume
            break;
        default:
            // TODO : gestion d'erreur ? 
            break;
    }
}

/**
 * Fonction réalisant les actions sur la luminosité de l'appareil, en fontion de la classification
 * 
 * @param predicted : classification de l'image
 * @return : void
 */
void ExecuteActionCommandBrightness::execute(uint8_t predicted) {
    switch(predicted) {
        case BrightnessClassifier::NOTHING:
            break;
        case BrightnessClassifier::UP:
            // TODO : Implémentation de l'action pour augmenter la brightness
            break;
        case BrightnessClassifier::DOWN:
            // TODO : Implémentation de l'action pour diminuer la brightness
            break;
        default:
            // TODO : gestion d'erreur ? 
            break;
    }
}

/**
 * Fonction réalisant les actions sur l'appareil, en fontion de la classification
 * 
 * @param predicted : classification de l'image
 * @param actionType : type d'action à réaliser (volume ou luminosité)
 * @return : void
 */
void ExecuteActionCommand::execute(uint8_t predicted, uint8_t actionType) {
    switch(actionType) {
        case ServiceIdentifyAction::VOLUME:
            ExecuteActionCommandVolume().execute(predicted);
            break;
        case ServiceIdentifyAction::BRIGHTNESS:
            ExecuteActionCommandBrightness().execute(predicted);
            break;
        default:
            // TODO : gestion d'erreur ? 
            break;
    }
}

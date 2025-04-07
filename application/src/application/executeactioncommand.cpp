#include "executeactioncommand.h"

/**
 * Fonction réalisant les actions sur le volume de l'appareil, en fontion de la classification
 * 
 * @param predicted : classification de l'image
 * @return : void
 */
void ExecuteActionCommandVolume::execute(uint8_t predicted) const {
    switch(predicted) {
        case VolumeClassifier::NOTHING:
            qDebug() << "Aucune action pour le volume";

            break;
        case VolumeClassifier::UP:
            // TODO : Implémentation de l'action pour augmenter le volume
            qDebug() << "Augmenter le volume";
            break;
        case VolumeClassifier::DOWN:
            // TODO : Implémentation de l'action pour diminuer le volume
            qDebug() << "Diminuer le volume";
            break;
        default:
            throw std::invalid_argument("Action inconnue pour le volume : " + std::to_string(predicted));
            break;
    }
}

/**
 * Fonction réalisant les actions sur la luminosité de l'appareil, en fontion de la classification
 * 
 * @param predicted : classification de l'image
 * @return : void
 */
void ExecuteActionCommandBrightness::execute(uint8_t predicted) const {
    switch(predicted) {
        case BrightnessClassifier::NOTHING:
            qDebug() << "Aucune action pour la brightness";
            
            break;
        case BrightnessClassifier::UP:
            // TODO : Implémentation de l'action pour augmenter la brightness
            qDebug() << "Augmenter la brightness";
            break;
        case BrightnessClassifier::DOWN:
            // TODO : Implémentation de l'action pour diminuer la brightness
            qDebug() << "Diminuer la brightness";
            break;
        default:
            throw std::invalid_argument("Action inconnue pour la brightness : " + std::to_string(predicted)); 
            break;
    }
}

IExecuteActionCommand* ExecuteActionCommandFactory::createAction(uint8_t actionType) {
    switch (actionType) {
        case IdentifyActionFactory::VOLUME: 
            return new ExecuteActionCommandVolume();
        case IdentifyActionFactory::BRIGHTNESS: 
            return new ExecuteActionCommandBrightness();
        default: 
            throw std::invalid_argument("Type d'action inconnu : " + std::to_string(actionType));
            return nullptr;
    }
}

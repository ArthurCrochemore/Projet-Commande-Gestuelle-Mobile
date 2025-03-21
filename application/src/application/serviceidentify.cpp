#include "serviceidentify.h"

uint8_t ServiceIdentifyActionVolume::identify(const QImage& image) {
    // TODO : Implémentation de l'identification d'une action lié au volume
}

uint8_t ServiceIdentifyActionBrightness::identify(const QImage& image) {
    // TODO : Implémentation de l'identification d'une action lié au volume
}

IServiceIdentifyAction* IdentifyActionFactory::createAction(int actionType) {
    switch (actionType) {
        case IdentifyActionFactory::VOLUME: return new ServiceIdentifyActionVolume();
        case IdentifyActionFactory::BRIGHTNESS: return new ServiceIdentifyActionBrightness();
        default: return nullptr;
    }
}

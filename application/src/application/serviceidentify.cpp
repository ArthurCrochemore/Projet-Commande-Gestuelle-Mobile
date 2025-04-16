#include "serviceidentify.h"

/**
 * Fonction initialisant le service d'identification de l'action lié au volume à réaliser en fonction de l'image
 * 
 * @param features : image vectorisée
 * @return : classe prédite
 */
uint8_t ServiceIdentifyActionVolume::identify(picture_vector& features) {
    // TODO : Implémentation de l'identification d'une action lié au volume
    auto classifier = VolumeClassifier();
    // classifier.initialize("volume");  TODO : ne pas initialiser à partir d'un fichier pas sur le smartphone

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
    auto classifier = VolumeClassifier();
    // classifier.initialize("brightness");  TODO : ne pas initialiser à partir d'un fichier pas sur le smartphone

    return BrightnessClassifier::UP;
}

std::unique_ptr<IServiceIdentifyAction> ServiceIdentifyActionVolumeFactory::create() {
    return std::make_unique<ServiceIdentifyActionVolume>();
}

std::unique_ptr<IServiceIdentifyAction> ServiceIdentifyActionBrightnessFactory::create() {
    return std::make_unique<ServiceIdentifyActionBrightness>();
}

IdentifyActionProvider& IdentifyActionProvider::instance() {
    static IdentifyActionProvider provider;
    return provider;
}

void IdentifyActionProvider::registerFactory(uint8_t actionType, std::unique_ptr<IServiceIdentifyActionFactory> factory) {
    factories[actionType] = std::move(factory);
}

std::unique_ptr<IServiceIdentifyAction> IdentifyActionProvider::createIdentifyAction(uint8_t actionType) {
    auto it = factories.find(actionType);
    if (it != factories.end()) {
        return it->second->create();
    }
    throw std::invalid_argument("Type d'action inconnu : " + std::to_string(actionType));
}

// Enregistrement des factories
static void registerFactories() {
    auto& provider = IdentifyActionProvider::instance();
    provider.registerFactory(IServiceIdentifyAction::VOLUME, std::make_unique<ServiceIdentifyActionVolumeFactory>());
    provider.registerFactory(IServiceIdentifyAction::BRIGHTNESS, std::make_unique<ServiceIdentifyActionBrightnessFactory>());
}

// Appel de l'enregistrement au démarrage
static const bool factoriesRegistered = (registerFactories(), true);

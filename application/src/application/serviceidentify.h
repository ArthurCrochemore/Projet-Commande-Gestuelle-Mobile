#include <QImage>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <functional>

#ifndef SERVICEIDENTIFY_H
#define SERVICEIDENTIFY_H

#include "../learning/classifier.h"
#include "../learning/imageadapter.h"

class IServiceIdentifyAction {
public:
    static const uint8_t VOLUME = 1;
    static const uint8_t BRIGHTNESS = 2;

    virtual uint8_t identify(picture_vector& features) = 0;
    virtual ~IServiceIdentifyAction() = default;
};

class ServiceIdentifyActionVolume : public IServiceIdentifyAction {
public:
    uint8_t identify(picture_vector& features) override;
};

class ServiceIdentifyActionBrightness : public IServiceIdentifyAction {
public:
    uint8_t identify(picture_vector& features) override;
};

// Interface pour les factories spécifiques
class IServiceIdentifyActionFactory {
public:
    virtual std::unique_ptr<IServiceIdentifyAction> create() = 0;
    virtual ~IServiceIdentifyActionFactory() = default;
};

// Factory pour les actions liées au volume
class ServiceIdentifyActionVolumeFactory : public IServiceIdentifyActionFactory {
public:
    std::unique_ptr<IServiceIdentifyAction> create() override;
};

// Factory pour les actions liées à la luminosité
class ServiceIdentifyActionBrightnessFactory : public IServiceIdentifyActionFactory {
public:
    std::unique_ptr<IServiceIdentifyAction> create() override;
};

// Provider pour gérer les factories
class IdentifyActionProvider {
public:
    static IdentifyActionProvider& instance();

    void registerFactory(uint8_t actionType, std::unique_ptr<IServiceIdentifyActionFactory> factory);
    std::unique_ptr<IServiceIdentifyAction> createIdentifyAction(uint8_t actionType);

private:
    std::unordered_map<uint8_t, std::unique_ptr<IServiceIdentifyActionFactory>> factories;
};

#endif // SERVICEIDENTIFY_H

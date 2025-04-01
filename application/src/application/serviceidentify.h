#include <QImage>
#include <cstdint>

#ifndef SERVICEIDENTIFY_H
#define SERVICEIDENTIFY_H

#include "../learning/classifier.h"
#include "../learning/imageadapter.h"

class IServiceIdentifyAction {
public:
    virtual uint8_t identify(std::vector<std::vector<greyscale_value>>& features) = 0;
    virtual ~IServiceIdentifyAction() = default;
};

class ServiceIdentifyActionVolume : public IServiceIdentifyAction {
public:
    uint8_t identify(std::vector<std::vector<greyscale_value>>& features) override;
};

class ServiceIdentifyActionBrightness : public IServiceIdentifyAction {
public:
    uint8_t identify(std::vector<std::vector<greyscale_value>>& features) override;
};

class IdentifyActionFactory {
public:
    static const uint8_t VOLUME = 1;
    static const uint8_t BRIGHTNESS = 2;

    static IServiceIdentifyAction* createIdentifyAction(uint8_t actionType);
};

#endif // SERVICEIDENTIFY_H

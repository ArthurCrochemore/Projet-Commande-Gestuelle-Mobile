#include <cstdint>
#include <QImage>

#ifndef SERVICEIDENTIFY_H
#define SERVICEIDENTIFY_H

class IServiceIdentifyAction {
public:
    virtual uint8_t identify(const QImage& image) = 0;
    virtual ~IServiceIdentifyAction() = default;
};

class ServiceIdentifyActionVolume : public IServiceIdentifyAction {
public:
    uint8_t identify(const QImage& image) override;
};

class ServiceIdentifyActionBrightness : public IServiceIdentifyAction {
public:
    uint8_t identify(const QImage& image) override;
};

class IdentifyActionFactory {
public:
    static const uint8_t VOLUME = 1;
    static const uint8_t BRIGHTNESS = 2;

    static IServiceIdentifyAction* createAction(int actionType);
};

#endif // SERVICEIDENTIFY_H
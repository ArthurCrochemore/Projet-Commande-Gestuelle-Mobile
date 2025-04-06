#include <QImage>
#include <cstdint>

#ifndef SERVICEIDENTIFY_H
#define SERVICEIDENTIFY_H

#include "../learning/classifier.h"
#include "../learning/imageadapter.h"

class ServiceIdentifyActionVolume {
public:
    static uint8_t identify(picture_vector& features);
};

class ServiceIdentifyActionBrightness {
public:
    static uint8_t identify(picture_vector& features);
};

class ServiceIdentifyAction {
public:
    static const uint8_t VOLUME = 1;
    static const uint8_t BRIGHTNESS = 2;

    static uint8_t identify(picture_vector& features, uint8_t actionType);
};

#endif // SERVICEIDENTIFY_H

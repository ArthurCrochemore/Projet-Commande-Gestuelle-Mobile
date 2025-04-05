#include <cstdint>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "../learning/imageadapter.h"

class IClassifier {
public:
    virtual uint8_t predict(picture_vector& features) = 0;
};

class VolumeClassifier : public IClassifier {
public:
    const static uint8_t NOTHING = 0;
    const static uint8_t UP = 1;
    const static uint8_t DOWN = 2;

    uint8_t predict(picture_vector& features) override;
};

class BrightnessClassifier : public IClassifier {
public:
    const static uint8_t NOTHING = 0;
    const static uint8_t UP = 1;
    const static uint8_t DOWN = 2;

    uint8_t predict(picture_vector& features) override;
};

#endif // CLASSIFIER_H

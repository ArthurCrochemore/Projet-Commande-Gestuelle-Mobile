#include <cstdint>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "../learning/imageadapter.h"

class VolumeClassifier {
public:
    const static uint8_t NOTHING = 0;
    const static uint8_t UP = 1;
    const static uint8_t DOWN = 2;

    static uint8_t predict(picture_vector& features);
};

class BrightnessClassifier {
public:
    const static uint8_t NOTHING = 0;
    const static uint8_t UP = 1;
    const static uint8_t DOWN = 2;

    static uint8_t predict(picture_vector& features);
};

class Classifier {
public:    
    static const uint8_t VOLUME = 1;
    static const uint8_t BRIGHTNESS = 2;

    static uint8_t predict(picture_vector& features, uint8_t actionType);
};

#endif // CLASSIFIER_H

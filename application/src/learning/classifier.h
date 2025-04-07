#include <cstdint>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "../learning/imageadapter.h"

class VolumeClassifier {
public:
    constexpr static uint8_t NOTHING = 0; // Added constexpr
    constexpr static uint8_t UP = 1;     // Added constexpr
    constexpr static uint8_t DOWN = 2;   // Added constexpr

    static uint8_t predict(const picture_vector& features);
};

class BrightnessClassifier {
public:
    constexpr static uint8_t NOTHING = 0; // Added constexpr
    constexpr static uint8_t UP = 1;     // Added constexpr
    constexpr static uint8_t DOWN = 2;   // Added constexpr

    static uint8_t predict(const picture_vector& features);
};

class Classifier {
public:    
    constexpr static uint8_t VOLUME = 1;     // Added constexpr
    constexpr static uint8_t BRIGHTNESS = 2; // Added constexpr

    static uint8_t predict(const picture_vector& features, const uint8_t actionType);
};

#endif // CLASSIFIER_H

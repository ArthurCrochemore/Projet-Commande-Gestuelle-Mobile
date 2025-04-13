#include <cstdint>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "../learning/imageadapter.h"
#include "../../../learning/cnn_model.h"

class VolumeClassifier {
public:
    constexpr static uint8_t NOTHING = 0;
    constexpr static uint8_t UP = 1;
    constexpr static uint8_t DOWN = 2;
};

class BrightnessClassifier {
public:
    constexpr static uint8_t NOTHING = 0;
    constexpr static uint8_t UP = 1;
    constexpr static uint8_t DOWN = 2;
};

class Classifier {
public:    
    constexpr static uint8_t VOLUME = 1;
    constexpr static uint8_t BRIGHTNESS = 2;

    static void initialize(QString type_name_classified);
    static uint8_t predict(const picture_vector& features, const uint8_t actionType);
};

#endif // CLASSIFIER_H

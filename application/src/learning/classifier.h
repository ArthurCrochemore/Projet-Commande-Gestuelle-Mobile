#include <cstdint>
#include <vector>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

class IClassifier {
public:
    virtual uint8_t predict(std::vector<double> features) = 0;
};

class VolumeClassifier : public IClassifier {
public:
    const uint8_t NOTHING = 0;
    const uint8_t UP = 1;
    const uint8_t DOWN = 2;

    uint8_t predict(std::vector<double> features) override;
};

class BrightnessClassifier : public IClassifier {
public:
    const uint8_t NOTHING = 0;
    const uint8_t UP = 1;
    const uint8_t DOWN = 2;

    uint8_t predict(std::vector<double> features) override;
};

#endif // CLASSIFIER_H
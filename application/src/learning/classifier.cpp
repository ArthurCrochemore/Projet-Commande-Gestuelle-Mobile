#include <cstdint>
#include <vector>

class IClassifier {
public:
    virtual uint8_t predict(std::vector<double> features) = 0;
};

class VolumeClassifier : public IClassifier {
public:
    const uint8_t NOTHING = 0;
    const uint8_t UP = 1;
    const uint8_t DOWN = 2;

    uint8_t predict(std::vector<double> features) override {
        // TODO : Implémentation du modèle de prédiction entrainé pour interpréter des signes pour le volume
    }
};

class BrightnessClassifier : public IClassifier {
public:
    const uint8_t NOTHING = 0;
    const uint8_t UP = 1;
    const uint8_t DOWN = 2;

    uint8_t predict(std::vector<double> features) override {
        // TODO : Implémentation du modèle de prédiction entrainé pour interpréter des signes pour la luminosité
    }
};
#include <algorithm>
#include <vector>
#include <QImage>

#ifndef PREPROCESSINGDECORATOR_H
#define PREPROCESSINGDECORATOR_H

// Variables globales pour les dimensions des images
#define WIDTH 150
#define HEIGHT 200

// Variable pour le type de valeur de gris
#define greyscale_value float
#define picture_vector std::vector<std::vector<greyscale_value>>
#define picture_vector1D std::vector<greyscale_value>

class IPreprocessingDecorator {
    public:
    virtual void process(picture_vector& data) = 0;
    virtual ~IPreprocessingDecorator() = default;
};

class NormalizationPreprocessor : public IPreprocessingDecorator {
public:
    void process(picture_vector& data) override;
};
    
#endif // PREPROCESSINGDECORATOR_H

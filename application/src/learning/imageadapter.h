#ifndef IMAGEADAPTER_H
#define IMAGEADAPTER_H

#include "preprocessingdecorator.h"

// Variables globales pour les dimensions des images
#define WIDTH 150
#define HEIGHT 200

// Variable pour le type de valeur de gris
#define greyscale_value float
#define picture_vector std::vector<std::vector<greyscale_value>>
#define picture_vector1D std::vector<greyscale_value>

class IImageAdapter {
    public:
    virtual picture_vector vectorize(QImage image) = 0;
};

class QImageToVectorAdapter : IImageAdapter {
    public:
    picture_vector vectorize(QImage image) override;
};

#endif // IMAGEADAPTER_H

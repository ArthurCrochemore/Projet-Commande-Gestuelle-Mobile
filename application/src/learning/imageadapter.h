#include <vector>
#include <QImage>

#include <QDebug> // TODO : a suppr

#ifndef IMAGEADAPTER_H
#define IMAGEADAPTER_H

// Variables globales pour les dimensions des images
#define WIDTH 150
#define HEIGHT 200

// Variable pour le type de valeur de gris
#define greyscale_value float
#define picture_vector std::vector<std::vector<greyscale_value>>
#define picture_vector1D std::vector<greyscale_value>

class IImageAdapter {
    public:
    virtual std::vector<std::vector<greyscale_value>> vectorize(QImage image) = 0;
};

class QImageToVectorAdapter : IImageAdapter {
    public:
    std::vector<std::vector<greyscale_value>> vectorize(QImage image) override;
};

#endif // IMAGEADAPTER_H

#include <vector>
#include <QImage>

#include <QDebug> // TODO : a suppr

#ifndef IMAGEADAPTER_H
#define IMAGEADAPTER_H

// Variables globales pour les dimensions des images
#define WIDTH 300
#define HEIGHT 400

// Variable pour le type de valeur de gris
#define greyscale_value float

class IImageAdapter {
    public:
    virtual std::vector<std::vector<greyscale_value>> vectorize(QImage image) = 0;
};

class QImageToVectorAdapter : IImageAdapter {
    public:
    std::vector<std::vector<greyscale_value>> vectorize(QImage image) override;
};

#endif // IMAGEADAPTER_H

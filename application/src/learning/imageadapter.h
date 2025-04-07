#include <algorithm>
#include <vector>
#include <QImage>

#ifndef IMAGEADAPTER_H
#define IMAGEADAPTER_H

// Variables globales pour les dimensions des images
constexpr int WIDTH = 300;  // Added constexpr
constexpr int HEIGHT = 400; // Added constexpr

// Variable pour le type de valeur de gris
#define greyscale_value float
#define picture_vector std::vector<std::vector<greyscale_value>>
#define picture_vector1D std::vector<greyscale_value>

class QImageToVectorAdapter {
    public:
    static void vectorize(const QString &imagePath, QImage& image, picture_vector& pixelValues, picture_vector1D& pixelRow);
};

#endif // IMAGEADAPTER_H

#include "imageadapter.h"

/**
 * Fonction responsable de la vectorisation d'une image
 * 
 * @param image : image à vectoriser
 * @return : image vectorisée
 */
void QImageToVectorAdapter::vectorize(const QString &imagePath, QImage& image, picture_vector& pixelValues) {
    image = QImage(imagePath).scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if (image.format() != QImage::Format_Grayscale8) {
        image = image.convertToFormat(QImage::Format_Grayscale8);
    }

    for (int y = 0; y < HEIGHT; ++y) {
        const uchar* rowData = image.scanLine(y);
        // picture_vector1D pixelRow = pixelValues[y]; // Accès direct à la ligne pour éviter les multiples indexations
        for (int x = 0; x < WIDTH; ++x) {
            // pixelRow[x] = rowData[x] * normalizationFactor; // Multiplication au lieu de division
            pixelValues[y][x] = rowData[x] / 255.0f; // Normalisation de l'intensité
        }
    }
}

#include "imageadapter.h"

/**
 * Fonction responsable de la vectorisation d'une image
 * 
 * @param image : image à vectoriser
 * @return : image vectorisée
 */
void QImageToVectorAdapter::vectorize(const QString &imagePath, QImage& image, picture_vector& pixelValues, picture_vector1D& pixelRow) {
    image = QImage(imagePath).scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if (image.format() != QImage::Format_Grayscale8) {
        image = image.convertToFormat(QImage::Format_Grayscale8);
    }

    for (int y = 0; y < HEIGHT; ++y) {
        const uchar* rowData = image.scanLine(y);
        picture_vector1D pixelRow = pixelValues[y]; // Récupération de la ligne correspondante dans le vecteur 2D
        for (int x = 0; x < WIDTH; ++x) {
            pixelRow[x] = rowData[x] / 255.0f; // Normalisation de la valeur de gris
        }
    }
}

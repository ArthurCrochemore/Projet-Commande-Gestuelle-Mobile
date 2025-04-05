#include "imageadapter.h"

/**
 * Fonction responsable de la vectorisation d'une image
 * 
 * @param image : image à vectoriser
 * @return : image vectorisée
 */
picture_vector QImageToVectorAdapter::vectorize(QImage image) {
    picture_vector pixelValues(HEIGHT, picture_vector1D(WIDTH));

    image = image.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if (image.format() != QImage::Format_Grayscale8) {
        image = image.convertToFormat(QImage::Format_Grayscale8);
    }

    for (int y = 0; y < HEIGHT; ++y) {
        const uchar* rowData = image.scanLine(y);
        for (int x = 0; x < WIDTH; ++x) {
            pixelValues[y][x] = rowData[x] / 255.0;
        }
    }

    return pixelValues;
}

#include "imageadapter.h"

/**
 * Fonction responsable de la vectorisation d'une image
 * 
 * @param image : image à vectoriser
 * @return : image vectorisée
 */
std::vector<std::vector<greyscale_value>> QImageToVectorAdapter::vectorize(QImage image) {
    std::vector<std::vector<greyscale_value>> pixelValues(HEIGHT, std::vector<greyscale_value>(WIDTH));

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

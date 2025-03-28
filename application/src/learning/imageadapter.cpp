#include "imageadapter.h"

std::vector<double> QImageToVectorAdapter::vectorize(QImage image) {
    std::vector<double> pixelValues;

    image = image.scaled(WIDTH, HEIGHT);

    if (image.format() != QImage::Format_Grayscale8) {
        image = image.convertToFormat(QImage::Format_Grayscale8);
    }

    pixelValues.reserve(image.width() * image.height());
    
    for (int y = 0; y < image.height(); ++y) {
        const uchar* rowData = image.scanLine(y);
        for (int x = 0; x < image.width(); ++x) {
            pixelValues.push_back(static_cast<double>(rowData[x]) / 255.0);
        }
    }

    return pixelValues;
}
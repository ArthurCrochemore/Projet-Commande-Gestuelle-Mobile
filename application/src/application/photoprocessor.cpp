#include "./photoprocessor.h"

std::vector<double> PhotoProcessor::process(const QString &imagePath) {
    QImage image = QImage(imagePath);

    return QImageToVectorAdapter().vectorize(image);
}
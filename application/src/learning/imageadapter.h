#include <vector>
#include <QImage>

#include <qDebug> // TODO : a suppr

#ifndef IMAGEADAPTER_H
#define IMAGEADAPTER_H

#define WIDTH 300
#define HEIGHT 400

class IImageAdapter {
    public:
    virtual std::vector<double> vectorize(QImage image) = 0;
};

class QImageToVectorAdapter : IImageAdapter {
    public:
    std::vector<double> vectorize(QImage image) override;
};

#endif // IMAGEADAPTER_H

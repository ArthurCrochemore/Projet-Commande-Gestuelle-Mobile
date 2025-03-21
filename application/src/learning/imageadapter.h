#include <vector>
#include <QImage>

#ifndef IMAGEADAPTER_H
#define IMAGEADAPTER_H

class IImageAdapter {
    public:
    virtual std::vector<double> vectorize(QImage image) = 0;
};

class QImageToVectorAdapter : IImageAdapter {
    public:
    std::vector<double> vectorize(QImage image) override;
};

#endif // IMAGEADAPTER_H
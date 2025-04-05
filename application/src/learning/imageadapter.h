#include <QDebug> // TODO : a suppr

#ifndef IMAGEADAPTER_H
#define IMAGEADAPTER_H

#include "preprocessingdecorator.h"

class IImageAdapter {
    public:
    virtual picture_vector vectorize(QImage image) = 0;
};

class QImageToVectorAdapter : IImageAdapter {
    public:
    picture_vector vectorize(QImage image) override;
};

#endif // IMAGEADAPTER_H
